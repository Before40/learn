#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/evp.h>


int main(){

    char *msg = "hello world\n";
    char result[EVP_MAX_MD_SIZE]="\0";
    BIO * bio_md, *bio_null;

    bio_null = BIO_new(BIO_s_null());
    bio_md = BIO_new(BIO_f_md());
    BIO_set_md(bio_md, EVP_md5());

    BIO_push(bio_md, bio_null);

    BIO_write(bio_md, msg, strlen(msg));
    BIO_flush(bio_md);

    BIO_gets(bio_md, result, EVP_MAX_MD_SIZE);

    printf("%d\n", strlen(result));

    return 0;
}