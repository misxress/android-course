//bmp.h

#include "lzw.h"

#ifndef COMPRESSION_BMP_H
#define COMPRESSION_BMP_H

#pragma pack(1)
typedef struct BMPHeader{
    unsigned char bfType[2];//文件格式
    unsigned long bfSize;//文件大小
    unsigned short bfReserved1;//保留
    unsigned short bfReserved2;
    unsigned long bfOffBits; //DIB数据在文件中的偏移量
}Header;

typedef struct BMPInfo{
    unsigned long biSize;//该结构的大小
    long biWidth;//文件宽度
    long biHeight;//文件高度
    unsigned short biPlanes;//平面数
    unsigned short biBitCount;//颜色位数
    unsigned long biCompression;//压缩类型
    unsigned long biSizeImage;//DIB数据区大小
    long biXPixPerMeter;
    long biYPixPerMeter;
    unsigned long biClrUsed;//多少颜色索引表
    unsigned long biClrImporant;//多少重要颜色
}Info;

typedef struct RGBQuad{
    unsigned char rgbBlue; //蓝色分量亮度
    unsigned char rgbGreen;//绿色分量亮度
    unsigned char rgbRed;//红色分量亮度
    unsigned char rgbReserved;
}Quad;
#pragma pack()

class bmp {
private:
    Header header;
    Info info;
    Quad *pColorTable;
    Data BmpBuf;
    LZWData LzwBuf;
public:
    int readBmp(char* bmpName);

    int readLzw(char* lzwName);

    int writeBmp(char* bmpName);

    int writeLzw(char* lzwName);

    Header getHeader();

    Info getInfo();

    Quad* getColorTable();

    Data getData();

    LZWData getLzw();

    void setHeader(Header inHeader);

    void setInfo(Info inInfo);

    void setColorTable(Quad* inQuad);

    void setData(Data inData);

    void setLzw(LZWData inLzw);
};


#endif //COMPRESSION_BMP_H
