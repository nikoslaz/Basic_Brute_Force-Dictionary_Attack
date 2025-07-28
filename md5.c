#include "md5.h"

#ifndef MD5_DIGEST_LENGTH
#define MD5_DIGEST_LENGTH 16
#endif

char* md5(const char *str, int length) {
    MD5_CTX c;
    uint8_t digest[MD5_DIGEST_LENGTH];
    char *out = (char*)malloc(MD5_DIGEST_LENGTH * 2 + 1);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(out + (i * 2), "%02x", digest[i]);
    }

    out[MD5_DIGEST_LENGTH * 2] = '\0';

    return out;
}