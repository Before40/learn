#include <stdio.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

int main()
{
    BIO *bio_b64;
    BIO *bio_mem;
    bio_b64 = BIO_new(BIO_f_base64());
    bio_mem = BIO_new(BIO_s_mem());

    bio_b64 = BIO_push(bio_b64, bio_mem);
    char *msg = "hello world.\n";

    BIO_write(bio_b64, msg, strlen(msg));
    BIO_flush(bio_b64);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio_mem, &bptr);
    char output[512] = "\0";
    memcpy(output, bptr->data, bptr->length);

    BIO_free_all(bio_b64);
    printf("%s\n", output);
    return 0;

}