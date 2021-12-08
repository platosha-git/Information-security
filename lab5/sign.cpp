#include <cstring>
#include "sign.h"

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

int verify(const unsigned char *msg, size_t mlen, const unsigned char *sig, size_t slen, EVP_PKEY *pkey) {
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

void print_labeled(const char *label, const unsigned char *buff, size_t len) {
    if (!buff || !len) {
        return;
    }

    if (label) {
        printf("%s: ", label);
    }

    for (size_t i = 0; i < len; ++i) {
        printf("%02X", buff[i]);
    }

    printf("\n");
}

void generateKeys(EVP_PKEY **skey, EVP_PKEY **vkey)
{
    *skey = EVP_PKEY_new();
    *vkey = EVP_PKEY_new();

    RSA *rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    EVP_PKEY_assign_RSA(*skey, RSAPrivateKey_dup(rsa));
    EVP_PKEY_assign_RSA(*vkey, RSAPublicKey_dup(rsa));

    RSA_free(rsa);
}

void read_keys(EVP_PKEY **public_k, EVP_PKEY **private_k) {
    FILE *pFile = nullptr;

    pFile = fopen("/home/platosha/Desktop/BMSTU/7sem/Information-security/lab5/private.key", "rt");
    *private_k = PEM_read_PUBKEY(pFile, nullptr, nullptr, nullptr);
    fclose(pFile);

    pFile = fopen("/home/platosha/Desktop/BMSTU/7sem/Information-security/lab5/public.key", "rt");
    *public_k = PEM_read_PUBKEY(pFile, nullptr, nullptr, nullptr);
}

void write_sign(unsigned char *sign, size_t len, char *filename) {
    std::ofstream file(filename);
    for (size_t i = 0; i < len; i++) {
        file.put(static_cast<char>(sign[i]));
    }
    file.close();
}

size_t read_sign(unsigned char **sign, char *filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(static_cast<unsigned long>(size));
    file.read(reinterpret_cast<char *>(buffer.data()), size);
    *sign = static_cast<unsigned char *>(malloc(buffer.size()));
    memcpy(*sign, buffer.data(), buffer.size());

    return buffer.size();
}
