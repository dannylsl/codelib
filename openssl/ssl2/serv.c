#include "stdio.h"
#include "string.h"

#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "unistd.h"

int password_callback(char *buf, int size, int rwflag, void *userdata)
{
    /* For the purposes of this demonstration, the password is "ibmdw" */

    printf("*** Callback function called\n");
    strcpy(buf,"123456");
//    printf("\n\n\n\%s\n\n\n\n",buf);
    return strlen(buf);
}

int main()
{
    SSL_CTX *ctx;
    SSL *ssl;
    BIO *sslbio, *acptbio, *out, *bufbio;
    pid_t pid;
    int len;
    char buf[1024];

    int (*callback)(char *, int, int, void *) = &password_callback;

    printf("Secure Programming with the OpenSSL API, Part 4:\n");
    printf("Serving it up in a secure manner\n\n");

    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    ERR_load_SSL_strings();
    OpenSSL_add_all_algorithms();

    printf("Attempting to create SSL context... ");
    ctx = SSL_CTX_new(SSLv23_server_method());
    if(ctx == NULL)
    {
        printf("Failed. Aborting.\n");
        return 0;
    }

    printf("\nLoading certificates...\n");
    SSL_CTX_set_default_passwd_cb(ctx, callback);
    if(!SSL_CTX_use_certificate_file(ctx, "server.csr", SSL_FILETYPE_PEM))
    {
        ERR_print_errors_fp(stdout);
        SSL_CTX_free(ctx);
        return 0;
    }
    else printf("load server.csr successful!\n");
    if((SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM))<=0)
    {
    printf("use private key failed!\n\n");
        ERR_print_errors_fp(stdout);
        SSL_CTX_free(ctx);
        return 0;
    }

    printf("Attempting to create BIO object... ");
    sslbio = BIO_new_ssl(ctx, 0);//0 indicate using server mode
    if(sslbio == NULL)
    {
        printf("Failed. Aborting.\n");
        ERR_print_errors_fp(stdout);
        SSL_CTX_free(ctx);
        return 0;
    }

    printf("\nAttempting to set up BIO for SSL...\n");
    BIO_get_ssl(sslbio, &ssl);
    /*该函数返回SSL类型BIO的内部的SSL结构的指针，
    得到该指针后，可以采用标准的ssl函数对其进行操作*/
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);//不需要任何重试请求
//    bufbio = BIO_new(BIO_f_buffer());
//    sslbio = BIO_push(bufbio,sslbio);
    
    acptbio = BIO_new_accept("4433");
    BIO_set_accept_bios(acptbio, sslbio);

    printf("Waiting for incoming connection...\n");
    /*Begin to listen the port*/
    if(BIO_do_accept(acptbio) <= 0)
    {
        ERR_print_errors_fp(stdout);
        SSL_CTX_free(ctx);
        BIO_free_all(sslbio);
        BIO_free_all(acptbio);
        return 1;
    }
while(1)
{
    /*Waiting for a new connection to establish*/
    if(BIO_do_accept(acptbio) <= 0)
    {
        ERR_print_errors_fp(stdout);
        SSL_CTX_free(ctx);
        BIO_free_all(sslbio);
        BIO_free_all(acptbio);
        return 1;
    }
    out = BIO_pop(acptbio);

  if((pid=fork()))//parent process
  {
     // BIO_free();
     BIO_free(out);
  }
  else
  {
    if(BIO_do_handshake(out) <= 0)
    {
        printf("Handshake failed.\n");
        ERR_print_errors_fp(stdout);
        SSL_CTX_free(ctx);
        BIO_free_all(sslbio);
        BIO_free_all(acptbio);
        return 1;
    }
    for(;;)
    {
        memset(buf,0,1023);
        len = BIO_read(out,buf,1023);
        switch(SSL_get_error(ssl,len))
        {
            case SSL_ERROR_NONE:
                break;
            default:
                printf("Read Problem!\n");
                exit(0);
        }
        if(!strcmp(buf,"\r\n")||!strcmp(buf,"\n"))
            break;
        if(buf[0]=='q') break;
        BIO_write(out,buf,len);
        printf("%s\n",buf);
    }
    //BIO_write(out,"bye",3);
    BIO_free(out);
    BIO_ssl_shutdown(sslbio);
    exit(0);
  }//end else
}
    BIO_ssl_shutdown(sslbio);
    BIO_free_all(sslbio);
    BIO_free_all(acptbio);
    SSL_CTX_free(ctx);
}
