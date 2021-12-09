#include <cstring>
#include "sign.h"

void generateKeys(EVP_PKEY *publicKey, EVP_PKEY *privateKey)
{
    RSA *rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);

    EVP_PKEY_assign_RSA(privateKey, RSAPrivateKey_dup(rsa));
    EVP_PKEY_assign_RSA(publicKey, RSAPublicKey_dup(rsa));

    RSA_free(rsa);
}

void sign(const unsigned char *message, size_t msgLen,
         unsigned char **signature, size_t *sigLen, EVP_PKEY *privateKey)
{
    *signature = nullptr;
    *sigLen = 0;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_get_digestbyname(hn);

    EVP_DigestInit_ex(ctx, md, nullptr);
    EVP_DigestSignInit(ctx, nullptr, md, nullptr, privateKey);
    EVP_DigestSignUpdate(ctx, message, msgLen);

    size_t req = 0;
    EVP_DigestSignFinal(ctx, nullptr, &req);

    *signature = static_cast<unsigned char *>(OPENSSL_malloc(req));
    *sigLen = req;
    EVP_DigestSignFinal(ctx, *signature, sigLen);

    EVP_MD_CTX_free(ctx);
}

int verify(const unsigned char *msg, size_t mlen,
           const unsigned char *sig, size_t slen, EVP_PKEY *publicKey)
{
    EVP_MD_CTX *ctx = nullptr;

    ctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_get_digestbyname(hn);
    EVP_DigestInit_ex(ctx, md, nullptr);

    int rc = EVP_DigestVerifyInit(ctx, nullptr, md, nullptr, publicKey);
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

    EVP_MD_CTX_free(ctx);
    return 0;
}
