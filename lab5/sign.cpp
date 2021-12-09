#include <cstring>
#include "sign.h"

void generateKeys(EVP_PKEY **skey, EVP_PKEY **vkey)
{
    *skey = EVP_PKEY_new();
    *vkey = EVP_PKEY_new();

    RSA *rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    EVP_PKEY_assign_RSA(*skey, RSAPrivateKey_dup(rsa));
    EVP_PKEY_assign_RSA(*vkey, RSAPublicKey_dup(rsa));

    RSA_free(rsa);
}

int sign(const unsigned char *msg, size_t mlen,
         unsigned char **sig, size_t *slen, EVP_PKEY *pkey)
{
    *sig = nullptr;
    *slen = 0;

    EVP_MD_CTX *ctx = nullptr;

    ctx = EVP_MD_CTX_create();
    const EVP_MD *md = EVP_get_digestbyname(hn);
    EVP_DigestInit_ex(ctx, md, nullptr);
    EVP_DigestSignInit(ctx, nullptr, md, nullptr, pkey);
    EVP_DigestSignUpdate(ctx, msg, mlen);

    size_t req = 0;
    EVP_DigestSignFinal(ctx, nullptr, &req);

    *sig = static_cast<unsigned char *>(OPENSSL_malloc(req));
    *slen = req;
    EVP_DigestSignFinal(ctx, *sig, slen);

    EVP_MD_CTX_destroy(ctx);

    return 0;
}

int verify(const unsigned char *msg, size_t mlen,
           const unsigned char *sig, size_t slen, EVP_PKEY *pkey)
{
    EVP_MD_CTX *ctx = nullptr;

    ctx = EVP_MD_CTX_create();
    const EVP_MD *md = EVP_get_digestbyname(hn);
    EVP_DigestInit_ex(ctx, md, nullptr);

    int rc = EVP_DigestVerifyInit(ctx, nullptr, md, nullptr, pkey);
    if (rc != 1) {
        EVP_MD_CTX_destroy(ctx);
        return -2;
    }

    EVP_DigestVerifyUpdate(ctx, msg, mlen);
    ERR_clear_error();

    rc = EVP_DigestVerifyFinal(ctx, sig, slen);
    if (rc != 1) {
        EVP_MD_CTX_destroy(ctx);
        return -1;
    }

    EVP_MD_CTX_destroy(ctx);
    return 0;
}
