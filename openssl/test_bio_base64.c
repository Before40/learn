#include <stdio.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

int base64_encode(unsigned char *data, int inlen, unsigned char *output, int outlen)
{
    int result = -1;
    BIO *bio_b64;
    BIO *bio_mem;
    bio_b64 = BIO_new(BIO_f_base64());
    bio_mem = BIO_new(BIO_s_mem());
    BIO_push(bio_b64, bio_mem);
    BIO_write(bio_b64, data, inlen);
    BIO_flush(bio_b64);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio_mem, &bptr);    
    if(bptr->length > outlen - 1)
    {
        return result;
    }
    memcpy(output, bptr->data, bptr->length);
    result = bptr->length;
    output[result] = '\0';
    BIO_free_all(bio_b64);
    return result;
}


int base64_decode(unsigned char *data, size_t inlen, unsigned char *output, size_t outlen)
{
    int result = -1;
    BIO *b64, *bio_mem;
    b64 = BIO_new(BIO_f_base64());
       
    bio_mem = BIO_new_mem_buf(data, inlen);
    bio_mem = BIO_push(b64, bio_mem);
    BIO_read(bio_mem, output, outlen);
    BIO_free_all(b64);
    return strlen(output);
}

int main()
{
    char *msg = "hello world Hello world\n";
    unsigned char output[512] = "\0";

    int res = base64_encode(msg, strlen(msg), output, 512);
    if(res != -1)
    {
        printf("%s\n", output);
    }

    unsigned char out[512] = "\0";
    res != base64_decode(output, strlen(output), out, 512);
    if(res != -1)
    {
        printf("%s\n", out);
    }
    return 0;

}