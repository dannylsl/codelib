#include <openssl/pkcs7.h>
#include <openssl/objects.h>
#include <openssl/pem.h>

int main(){
	BIO *b;
	PKCS7 *p7;

	b = BIO_new_file("p7Digest.pem","r");
	p7 = PEM_read_bio_PKCS7(b,NULL,NULL,NULL);
	BIO_free(b);
	PKCS7_free(p7);
	return 0;
}
