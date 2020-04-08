//txt.cpp
#include "txt.h"

int txt::readTxt(char *txtName) {
    //打开文件
    FILE *fp = fopen(txtName, "rb");

    if(fp == nullptr)
        return 0;

    fseek(fp,0L,SEEK_END); /* 定位到文件末尾 */
    this->txtBuf.length = ftell(fp);
    fseek(fp,0L,SEEK_SET); /* 定位到文件开头 */

    this->txtBuf.oneChar = new unsigned char[this->txtBuf.length];

    fread(this->txtBuf.oneChar, 1, this->txtBuf.length, fp);

    fclose(fp);
}

int txt::writeTxt(char *txtName) {
    //打开文件
    FILE *fp = fopen(txtName, "wb");

    if(fp == nullptr)
        return 0;

    fwrite(this->txtBuf.oneChar, 1, this->txtBuf.length, fp);

    fclose(fp);
}

int txt::readLzw(char *lzwName) {
    //打开文件
    FILE *fp = fopen(lzwName, "rb");

    if(fp == nullptr)
        return 0;

    fseek(fp,0L,SEEK_END); /* 定位到文件末尾 */
    this->lzwBuf.length = ftell(fp)/4;
    fseek(fp,0L,SEEK_SET); /* 定位到文件开头 */

    this->lzwBuf.oneLong = new unsigned long[this->txtBuf.length];

    fread(this->lzwBuf.oneLong, sizeof(unsigned long), this->lzwBuf.length, fp);

    fclose(fp);
}

int txt::writeLzw(char *lzwName) {
    //打开文件
    FILE *fp = fopen(lzwName, "wb");

    if(fp == nullptr)
        return 0;

    fwrite(this->lzwBuf.oneLong, sizeof(unsigned long), this->lzwBuf.length, fp);

    fclose(fp);
}

Data txt::getTxtBuf() {
    return this->txtBuf;
}

LZWData txt::getLzwBuf() {
    return this->lzwBuf;
}

void txt::setTxt(Data inData) {
    this->txtBuf = inData;
}

void txt::setLzw(LZWData inLzw) {
    this->lzwBuf = inLzw;
}
