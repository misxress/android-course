//lzw.h

#include <map>
#include <fstream>
#include <vector>
#include <string>

#ifndef COMPRESSION_LZW_H
#define COMPRESSION_LZW_H

using std::vector;
using std::string;
using std::pair;

struct Data {
    int length;
    unsigned char* oneChar;
};

struct LZWData {
    unsigned long length;
    unsigned long* oneLong;
};

class lzw {
public:

    LZWData encode(Data inData);

    Data decode(LZWData inData);
};


#endif //COMPRESSION_LZW_H
