//
// Created by misxr on 2020/3/17.
//
#include <iostream>
#include <cstdio>
#include "lzw.h"
#include "bmp.h"
#include "txt.h"

int main(){
    lzw lzwTest;

//    bmp bmpTest;
//    bmpTest.readBmp("D:\\dongma.bmp");
//    bmpTest.setLzw(lzwTest.encode(bmpTest.getData()));
//    bmpTest.writeLzw("D:\\dongma.bmp.lzw");
//
//    bmp bmpNew;
//    bmpNew.readLzw("D:\\dongma.bmp.lzw");
//    bmpNew.setData(lzwTest.decode(bmpNew.getLzw()));
//    bmpNew.writeBmp("D:\\dongmaa.bmp");

    txt txtTest;
    txtTest.readTxt("D:\\in.txt");
    txtTest.setLzw(lzwTest.encode(txtTest.getTxtBuf()));
    txtTest.writeLzw("D:\\in.txt.lzw");

    txt txtNew;
    txtNew.readLzw("D:\\in.txt.lzw");
    txtNew.setTxt(lzwTest.decode(txtNew.getLzwBuf()));
    txtNew.writeTxt("D:\\new.txt");

}
