#include <openssl/pkcs7.h>
#include <openssl/objects.h>
#include <openssl/pem.h>

int main(){
	PKCS7 *p7;
	int ret = 0;
	BIO *b;

	p7=PKCS7_new();
	ret=PKCS7_set_type(p7,NID_pkcs7_digest);
	b=BIO_new_file("p7Digest.pem","w");
	PEM_write_bio_PKCS7(b,p7);
	BIO_free(b);
	PKCS7_free(p7);
	return 0;

}
