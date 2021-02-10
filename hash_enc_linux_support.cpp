//
// Created by my_fl on 2021-02-10.
//

#include "hash_enc_linux_support.h"


void *hash_enc_linux_support::__hash_enc_memcpy(void *dst, const void *src, size_t len) {
    std::size_t i;
    if ((uintptr_t) dst % sizeof(long) == 0 &&
        (uintptr_t) src % sizeof(long) == 0 &&
        len % sizeof(long) == 0) {
        long* d = (long*)dst;
        const long* s = (const long*)src;
        for (i = 0; i < len / sizeof(long); i++) {
            d[i] = s[i];
        }
    } else {
        char* d = (char*)dst;
        const char* s = (const char*)src;
        for (i = 0; i < len; i++) {
            d[i] = s[i];
        }
    }
    return dst;
};

unsigned hash_enc_linux_support::__hash_enc_rotl (HASH_ENC_UINT32 val, HASH_ENC_INT32 shift)
{
    HASH_ENC_UINT32 hibit;
    HASH_ENC_UINT32 num = val;
    shift &= 0x1f;
    while (shift--) {
        hibit = num & 0x80000000;
        num <<= 1;
        if (hibit) num |= 1;
    }
    return num;
};
unsigned long hash_enc_linux_support::__hash_enc_lrotl (HASH_ENC_ULONG val, HASH_ENC_INT32 shift)
{
    return ((HASH_ENC_ULONG) hash_enc_linux_support::__hash_enc_rotl ((HASH_ENC_UINT32) val, shift));
};
unsigned hash_enc_linux_support::__hash_enc_rotr (HASH_ENC_UINT32 val, HASH_ENC_INT32 shift)
{
    HASH_ENC_UINT32 lobit;
    HASH_ENC_UINT32 num = val;
    shift &= 0x1f;
    while (shift--) {
        lobit = num & 1;
        num >>= 1;
        if (lobit) num |= 0x80000000;
    };
    return num;
}
unsigned long hash_enc_linux_support::__hash_enc_lrotr (HASH_ENC_ULONG val, HASH_ENC_INT32 shift)
{
    return ((HASH_ENC_ULONG) hash_enc_linux_support::__hash_enc_rotr ((HASH_ENC_UINT32) val, shift));
};