//bmp.cpp

#include <cstdio>
#include "bmp.h"

/**
 * 读函数
 */
int bmp::readBmp(char *bmpName) {
    
    //打开文件
    FILE *fp = fopen(bmpName, "rb");

    if(fp == nullptr)
        return 0;

    //读取文件头
    fread(&header, sizeof(Header), 1, fp);
    
    //读取信息头
    fread(&info, sizeof(Info), 1, fp);

    //计算图片行数和数据长度
    int lineByte = (info.biWidth * info.biBitCount / 8 + 3) / 4 * 4;
    this->BmpBuf.length = lineByte * info.biHeight;

    //获取颜色板
    pColorTable = new Quad[256];
    fread(pColorTable, sizeof(RGBQuad), 256, fp);
    
    //获取数据
    this->BmpBuf.oneChar = new unsigned char[this->BmpBuf.length];
    fread(this->BmpBuf.oneChar, 1, this->BmpBuf.length, fp);
    
    //关闭流
    fclose(fp);
}

int bmp::readLzw(char *lzwName) {

    //打开文件
    FILE *fp = fopen(lzwName, "rb");

    if(fp == nullptr)
        return 0;

    //读取文件头
    fread(&header, sizeof(Header), 1, fp);

    //读取信息头
    fread(&info, sizeof(Info), 1, fp);

    //计算图片行数和数据长度
//    int lineByte = (info.biWidth * info.biBitCount / 8 + 3) / 4 * 4;
//    this->DataLength = lineByte * info.biHeight;

    //获取颜色板
    pColorTable = new Quad[256];
    fread(pColorTable, sizeof(RGBQuad), 256, fp);

    //获取数据
    unsigned long length;
    fread(&length, sizeof(unsigned long), 1, fp);
    this->LzwBuf.length = length + 1;
    this->LzwBuf.oneLong = new unsigned long[length + 1];
    fread(this->LzwBuf.oneLong+1, sizeof(unsigned long), length, fp);
    this->LzwBuf.oneLong[0] = length;

    //关闭流
    fclose(fp);
}

Header bmp::getHeader() {
    return this->header;
}

Quad* bmp::getColorTable() {
    return this->pColorTable;
}

Info bmp::getInfo() {
    return this->info;
}

Data bmp::getData() {
    return this->BmpBuf;
}

LZWData bmp::getLzw() {
    return this->LzwBuf;
}

/**
 * 写函数
 */
int bmp::writeBmp(char *bmpName) {
    //打开文件
    FILE *fp = fopen(bmpName, "wb");

    if(fp == nullptr)
        return 0;

    //输出文件头
    fwrite(&header, sizeof(Header), 1, fp);

    //输出信息头
    fwrite(&info, sizeof(Info), 1, fp);

    //写颜色板
    fwrite(this->pColorTable, sizeof(RGBQuad), 256, fp);

    //获取数据
    fwrite(this->BmpBuf.oneChar, 1, this->BmpBuf.length, fp);

    //关闭流
    fclose(fp);
}

int bmp::writeLzw(char *lzwName) {

    //打开文件
    FILE *fp = fopen(lzwName, "wb");

    if(fp == nullptr)
        return 0;

    //读取文件头
    fwrite(&header, sizeof(Header), 1, fp);

    //读取信息头
    fwrite(&info, sizeof(Info), 1, fp);

    //获取颜色板
    fwrite(pColorTable, sizeof(RGBQuad), 256, fp);

    //获取数据
    fwrite(this->LzwBuf.oneLong, sizeof(unsigned long), this->LzwBuf.length, fp);

    //关闭流
    fclose(fp);
}

void bmp::setHeader(Header inHeader) {
    this->header = inHeader;
}

void bmp::setInfo(Info inInfo) {
    this->info = inInfo;
}

void bmp::setColorTable(Quad *inQuad) {
    this->pColorTable = inQuad;
}

void bmp::setData(Data inData) {
    this->BmpBuf = inData;
}

void bmp::setLzw(LZWData inLzw) {
    this->LzwBuf = inLzw;
}

