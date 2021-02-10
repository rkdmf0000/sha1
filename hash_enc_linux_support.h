//
// Created by my_fl on 2021-02-10.
//

#ifndef HASH_ENC1_HASH_ENC_LINUX_SUPPORT_H
#define HASH_ENC1_HASH_ENC_LINUX_SUPPORT_H
#include "hash_enc_def.h"
namespace hash_enc_linux_support{
    void* __hash_enc_memcpy(void *dst, const void *src, size_t len);
    unsigned __hash_enc_rotl(HASH_ENC_UINT32 val, HASH_ENC_INT32 shift);
    unsigned long __hash_enc_lrotl(HASH_ENC_ULONG val, HASH_ENC_INT32 shift);
    unsigned __hash_enc_rotr(HASH_ENC_UINT32 val, HASH_ENC_INT32 shift);
    unsigned long __hash_enc_lrotr(HASH_ENC_ULONG val, HASH_ENC_INT32 shift);
}
#endif //HASH_ENC1_HASH_ENC_LINUX_SUPPORT_H

