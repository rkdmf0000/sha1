//
// Created by my_fl on 2021-02-04.
//

#include "hash_enc.h"


HASH_ENC_UINT32 hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE = __MAXIMUM_MESSAGE_BLOCK_SIZE;
HASH_ENC_UINT32 hash_enc::MAXIMUM_HASH_SIZE = __MAXIMUM_HASH_SIZE;
HASH_ENC_UINT32 hash_enc::DEFAULT_HASHSET[] = {0x0F254AC8,
                                               0x648A0CD1,
                                               0xFF450944,
                                               0x33ACC877,
                                               0x00FF4483};
HASH_ENC_UINT32 hash_enc::REFERENCE_PAD[] = {0x80};

hash_enc::hash_enc() {
    this->init();
};

hash_enc::~hash_enc() = default;;

void hash_enc::init() {
    HASH_ENC_SIZE index(0);
    this->result.clear();
    this->ctx.messageBlockBufferSize = 0;
    for (index = 0; index < hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE; ++index) this->ctx.messageBlock[index] = 0;
    for (index = 0; index < hash_enc::MAXIMUM_HASH_SIZE; ++index)
        this->ctx.hash[index] = hash_enc::DEFAULT_HASHSET[index];
};

void hash_enc::update(void *inputPtr, HASH_ENC_SIZE cdSize) {
    HASH_ENC_UINT32 eaten(0);
    const HASH_ENC_MESSAGE_BLOCK *block = static_cast<HASH_ENC_MESSAGE_BLOCK *>(inputPtr);
    while (cdSize) {
        HASH_ENC_UINT32 biteSize = HASH_ENC_MATH_MIN(hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE - eaten, cdSize);
        HASH_ENC_UINT32 limited = ((HASH_ENC_UINT32) block + this->ctx.messageBlockBufferSize + eaten & 0xfffffffff);
        this->printBufferText((char *) "- - - memory copied");
        memcpy((HASH_ENC_UCHAR *) this->ctx.messageBlock, block + this->ctx.messageBlockBufferSize, biteSize);
        eaten += biteSize;
        this->ctx.messageBlockBufferSize += biteSize;
        cdSize -= biteSize;
        if (hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE != eaten) break;
        eaten = 0;
        this->messageBlock(limited);
    };
};


void hash_enc::flush(void *resultHashArray) {
    HASH_ENC_SIZE left_byte = this->ctx.messageBlockBufferSize % hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE;
    if (left_byte != 0) {
        HASH_ENC_SIZE start_point = this->ctx.messageBlockBufferSize - left_byte;
        HASH_ENC_SIZE require_left = hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE - left_byte;
        memcpy(this->ctx.messageBlock + left_byte, hash_enc::REFERENCE_PAD, require_left);
        this->messageBlock(start_point);
    };
    HASH_ENC_UINT32 uint32_size = sizeof(HASH_ENC_UINT32);
    memcpy(&resultHashArray + (uint32_size * 0), this->ctx.hash + (uint32_size * 0), uint32_size);
    memcpy(&resultHashArray + (uint32_size * 1), this->ctx.hash + (uint32_size * 1), uint32_size);
    memcpy(&resultHashArray + (uint32_size * 2), this->ctx.hash + (uint32_size * 2), uint32_size);
    memcpy(&resultHashArray + (uint32_size * 3), this->ctx.hash + (uint32_size * 3), uint32_size);
    memcpy(&resultHashArray + (uint32_size * 4), this->ctx.hash + (uint32_size * 4), uint32_size);
};

void hash_enc::flush() {
    HASH_ENC_SIZE left_byte = this->ctx.messageBlockBufferSize % hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE;
    if (left_byte != 0) {
        HASH_ENC_SIZE start_point = this->ctx.messageBlockBufferSize - left_byte;
        HASH_ENC_SIZE require_left = hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE - left_byte;
        memcpy(this->ctx.messageBlock + left_byte, hash_enc::REFERENCE_PAD, require_left);
        this->messageBlock(start_point);
    };
};

HASH_ENC_STD_STRING hash_enc::getResult() {
    HASH_ENC_STD_STRING sums;
    sums += n2hexstr<unsigned int>(this->ctx.hash[0]);
    sums += n2hexstr<unsigned int>(this->ctx.hash[1]);
    sums += n2hexstr<unsigned int>(this->ctx.hash[2]);
    sums += n2hexstr<unsigned int>(this->ctx.hash[3]);
    sums += n2hexstr<unsigned int>(this->ctx.hash[4]);
    return std::move(sums);
};

void hash_enc::messageBlock(const HASH_ENC_UINT32 limited) {
    HASH_ENC_UINT32 loopIndex(0);
    HASH_ENC_UINT32 _a = this->ctx.hash[0];
    HASH_ENC_UINT32 _b = this->ctx.hash[1];
    HASH_ENC_UINT32 _c = this->ctx.hash[2];
    HASH_ENC_UINT32 _d = this->ctx.hash[3];
    HASH_ENC_UINT32 _e = this->ctx.hash[4];
    HASH_ENC_UCHAR _box[hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE];
    for (loopIndex = 0; loopIndex < hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE; ++loopIndex)
        _box[loopIndex] = 0;
    memcpy(_box, this->ctx.messageBlock, hash_enc::MAXIMUM_MESSAGE_BLOCK_SIZE);
    for (loopIndex = 0; loopIndex < 16; ++loopIndex)
        _box[loopIndex & 0x0f] = _lrotl(_box[loopIndex + 13 & 0x0f]
                                        ^ _box[loopIndex + 8 & 0x0f]
                                        ^ _box[loopIndex + 2 & 0x0f]
                                        ^ _box[loopIndex & 0x0f], 1);
    for (loopIndex = 16; loopIndex < 32; ++loopIndex)
        _box[loopIndex & 0x0f] = _lrotl(_box[loopIndex + 29 & 0x0f]
                                        ^ _box[loopIndex + 24 & 0x0f]
                                        ^ _box[loopIndex + 18 & 0x0f]
                                        ^ _box[loopIndex & 0x0f], 1);
    for (loopIndex = 32; loopIndex < 48; ++loopIndex)
        _box[loopIndex & 0x0f] = _lrotl(_box[loopIndex + 45 & 0x0f]
                                        ^ _box[loopIndex + 40 & 0x0f]
                                        ^ _box[loopIndex + 34 & 0x0f]
                                        ^ _box[loopIndex & 0x0f], 1);
    for (loopIndex = 48; loopIndex < 64; ++loopIndex)
        _box[loopIndex & 0x0f] = _lrotl(_box[loopIndex + 61 & 0x0f]
                                        ^ _box[loopIndex + 56 & 0x0f]
                                        ^ _box[loopIndex + 50 & 0x0f]
                                        ^ _box[loopIndex & 0x0f], 1);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[0]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[1]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[2]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[3]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[4]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[5]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[6]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[7]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[8]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[9]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[10]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[11]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[12]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[13]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[14]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[15]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[16]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[17]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[18]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[19]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[20]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[21]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[22]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[23]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[24]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[25]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[26]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[27]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[28]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[29]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[30]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[31]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[32]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[33]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[34]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[35]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[36]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[37]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[38]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[39]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[40]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[41]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[42]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[43]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[44]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[45]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[46]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[47]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[48]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[49]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[50]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[51]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[52]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[53]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[54]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[55]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[56]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[57]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[58]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[59]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[60]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[61]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[62]);
    HASH_ENC_ROL_RS(_c, _d, _e, _a, _b, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[63]);
    HASH_ENC_ROL_RS(_b, _c, _d, _e, _a, HASH_ENC_F1, HASH_ENC_K1, this->ctx.messageBlock[0]);

    HASH_ENC_ROL_RS(_a, _b, _c, _d, _e, HASH_ENC_F2, HASH_ENC_K2, this->ctx.messageBlock[1]);
    HASH_ENC_ROL_RS(_e, _a, _b, _c, _d, HASH_ENC_F3, HASH_ENC_K3, this->ctx.messageBlock[2]);
    HASH_ENC_ROL_RS(_d, _e, _a, _b, _c, HASH_ENC_F4, HASH_ENC_K4, this->ctx.messageBlock[4]);

    HASH_ENC_UINT32 _trans = HASH_ENC_ROL_MIX(limited, this->ctx.messageBlock) + _e;
    this->ctx.hash[0] = _trans;
    this->ctx.hash[1] = _a;
    this->ctx.hash[2] = _b;
    this->ctx.hash[3] = _c;
    this->ctx.hash[4] = _d;

    this->printBufferText((char *) "- - - message blocked");
};


void hash_enc::printBufferText(char *text) {
    //std::cout << text << '\r' << '\n';
};


void hash_enc::print_hash() {
    std::cout << n2hexstr<unsigned int>(this->ctx.hash[0])
              << n2hexstr<unsigned int>(this->ctx.hash[1])
              << n2hexstr<unsigned int>(this->ctx.hash[2])
              << n2hexstr<unsigned int>(this->ctx.hash[3])
              << n2hexstr<unsigned int>(this->ctx.hash[4])
              << '\n';
};

template<typename I>
HASH_ENC_STD_STRING hash_enc::n2hexstr(I w, HASH_ENC_SIZE hex_len) {
    static const char *digits = "0123456789abcdef";
    std::string rc(hex_len, '0');
    for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
        rc[i] = digits[(w >> j) & 0x0f];
    return rc;
}

void hash_enc::seed(const HASH_ENC_UINT32 *seeds) {

}

