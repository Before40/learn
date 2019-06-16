#include <stdio.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>


int main(){

    char *msg = "hello world\n";
    char result[512]="\0";
    BIO * bio_md, *bio_null;

    BIO *bio_b64;
    BIO *bio_mem;

    bio_null = BIO_new(BIO_s_null());

    bio_md = BIO_new(BIO_f_md());
    BIO_set_md(bio_md, EVP_sha1());

    bio_b64 = BIO_new(BIO_f_base64());

    bio_mem = BIO_new(BIO_s_mem());

    bio_b64 = BIO_push(bio_b64, bio_mem);
    bio_md = BIO_push(bio_md, bio_b64);

    BIO_write(bio_md, msg, strlen(msg));
    BIO_flush(bio_md);

    BUF_MEM *bptr = NULL;
    BIO_get_mem_ptr(bio_mem, &bptr);
    size_t len = bptr->length;

    memcpy(result, bptr->data, len);
    printf("%s\n", result);
    BIO_free_all(bio_md);
    return 0;

    

    return 0;
}