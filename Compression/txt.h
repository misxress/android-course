//
// Created by misxr on 2020/3/20.
//

#ifndef COMPRESSION_TXT_H
#define COMPRESSION_TXT_H


#include "lzw.h"

class txt {
private:
    Data txtBuf;
    LZWData lzwBuf;
public:
    int readTxt(char* txtName);

    int writeTxt(char* txtName);

    int readLzw(char* lzwName);

    int writeLzw(char* lzwName);

    Data getTxtBuf();

    LZWData getLzwBuf();

    void setTxt(Data inData);

    void setLzw(LZWData inLzw);
};


#endif //COMPRESSION_TXT_H
