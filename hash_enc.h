//
// Created by my_fl on 2021-02-04.
//

/**
 * hash_encryption_by_custom
 * */
#ifndef HASH_ENC1_HASH_ENC_H
#define HASH_ENC1_HASH_ENC_H

#ifndef HASH_ENC1_HASH_ENC_H_CONFIG
#define HASH_ENC1_HASH_ENC_H_CONFIG
#define HASH_ENC_CONFIG_STR_OTHER 0x01
#define HASH_ENC_CONFIG_STR_WINDOW 0x02
#define HASH_ENC_CONFIG_STR_LINUX 0x03
#define __MAXIMUM_MESSAGE_BLOCK_SIZE 64
#define __MAXIMUM_HASH_SIZE 5
#endif

#if defined(_WIN32)
#define HASH_ENC_OS HASH_ENC_CONFIG_STR_WINDOW
#elif defined(__linux__)
#define HASH_ENC_OS HASH_ENC_CONFIG_STR_LINUX
#else
#define HASH_ENC_OS HASH_ENC_CONFIG_STR_OTHER
#endif

#include <iostream>
#include <cmath>
#include <string>


#define HASH_ENC_K1 0x5a827999
#define HASH_ENC_K2 0x6ed9eba1
#define HASH_ENC_K3 0x8f1bbcdc
#define HASH_ENC_K4 0xca62c1d6

#include "hash_enc_def.h"

#ifndef HASH_ENC1_HASH_ENC_H_MACRO
#define HASH_ENC1_HASH_ENC_H_MACRO
#if HASH_ENC_OS == HASH_ENC_CONFIG_STR_LINUX
#include <stdlib.h>
#include "hash_enc_linux_support.h"
#define HASH_ENC_FN_MEMCPY hash_enc_linux_support::__hash_enc_memcpy
#define HASH_ENC_FN_ROTL hash_enc_linux_support::__hash_enc_rotl
#define HASH_ENC_FN_LROTL hash_enc_linux_support::__hash_enc_lrotl
#define HASH_ENC_FN_ROTR hash_enc_linux_support::__hash_enc_rotr
#define HASH_ENC_FN_LROTR hash_enc_linux_support::__hash_enc_lrotr
#elif HASH_ENC_OS == HASH_ENC_CONFIG_STR_WINDOW
#define HASH_ENC_FN_MEMCPY memcpy
#define HASH_ENC_FN_ROTL _rotl
#define HASH_ENC_FN_LROTL _lrotl
#define HASH_ENC_FN_ROTR _rotr
#define HASH_ENC_FN_LROTR _lrotr
#else
#define HASH_ENC_FN_MEMCPY memcpy
#define HASH_ENC_FN_ROTL _rotl
#define HASH_ENC_FN_LROTL _lrotl
#define HASH_ENC_FN_ROTR _rotr
#define HASH_ENC_FN_LROTR _lrotr
#endif


#define HASH_ENC_MATH_MIN(na, nb) (na < nb ? na : nb)
#define HASH_ENC_MATH_MAX(na, nb) (na < nb ? nb: na)
#define HASH_ENC_ROL(x, n) (((x) << (n)) | ((HASH_ENC_UINT32) (x) >> (32 - (n))))
#define HASH_ENC_ROL_MIX(I, BOX) ( BOX[I&0x0f] ^ BOX[(I-14)&0x0f] \
                    ^ BOX[(I-8)&0x0f] ^ BOX[(I-3)&0x0f] \
                    , (BOX[I&0x0f] = HASH_ENC_ROL(BOX[I&0x0f], 1)) )
#define HASH_ENC_F1(B, C, D) ( D ^ ( B & ( C ^ D ) ) )
#define HASH_ENC_F2(B, C, D) (B ^ C ^ D)
#define HASH_ENC_F3(B, C, D) ( ( B & C ) | ( D & ( B | C ) ) )
#define HASH_ENC_F4(B, C, D) (B ^ C ^ D)
#define HASH_ENC_ROL_RS(A, B, C, D, E, F, K, M)  do { E += HASH_ENC_ROL( A, 5 )     \
                                      + F( B, C, D )  \
                                      + K              \
                                      + M;              \
                                 B = HASH_ENC_ROL( B, 30 );    \
                               } while(0)
#endif


struct HASH_ENC_CTX {
    HASH_ENC_SIZE messageBlockBufferSize;
    HASH_ENC_MESSAGE_BLOCK messageBlock[__MAXIMUM_MESSAGE_BLOCK_SIZE];
    HASH_ENC_HASH_BLOCK hash[__MAXIMUM_HASH_SIZE];
};

class hash_enc {
public:
    static HASH_ENC_UINT32 DEFAULT_HASHSET[__MAXIMUM_HASH_SIZE];
    static HASH_ENC_UINT32 MAXIMUM_MESSAGE_BLOCK_SIZE;
    static HASH_ENC_UINT32 MAXIMUM_HASH_SIZE;
    static HASH_ENC_UINT32 REFERENCE_PAD[__MAXIMUM_MESSAGE_BLOCK_SIZE];
private:
    HASH_ENC_CTX ctx;
    HASH_ENC_STD_STRING result;

public:
    hash_enc();

    ~hash_enc();

    void init();

    void update(void *, HASH_ENC_SIZE);

    void flush();

    void flush(void *);

    void seed(const HASH_ENC_UINT32[5]);

    void print_hash();

    HASH_ENC_STD_STRING getResult();

private:
    static void printBufferText(char *);

    void messageBlock(HASH_ENC_UINT32);

    template<typename I>
    HASH_ENC_STD_STRING n2hexstr(I, HASH_ENC_SIZE = sizeof(I) << 1);

};


#endif //HASH_ENC1_HASH_ENC_H