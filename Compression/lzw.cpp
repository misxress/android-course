//lzw.cpp

#include <iostream>
#include <fstream>
#include "lzw.h"

LZWData lzw::encode(Data inData) {

    vector<int> V;

    V.push_back(0);

    string P;
    string C;
    string P_C;
    std::map<string,int> dic;
    int len = 256;
    std::map<string, int>::iterator iter;
    for(int i = 0 ; i < 256 ; i++) {
        string tmp{(char)i};
        dic.insert(pair<string,int>(tmp,i));
    }
    for(int i = 0 ; i < inData.length ; i++) {
        C = inData.oneChar[i];
        P_C =P + C;
        iter = dic.find(P_C);
        if(iter != dic.end()) {
            P = P_C;
        }else {
            V.push_back(dic[P]);
            dic.insert(pair<string,int>(P_C,len++));
            P = C;
        }
    }

    if(P.length() > 0) {
        V.push_back(dic[P]);
    }

    V[0] = V.size() - 1;

    LZWData ans;

    ans.length = V.size();
    ans.oneLong = new unsigned long[ans.length];

    for(int i = 0;i<V.size();i++){
        ans.oneLong[i] = V[i];
    }

    return ans;
}

Data lzw::decode(LZWData inData) {

    vector<int> V;

    for(int i = 0; i < inData.length; i++) {
        V.push_back(inData.oneLong[i]);
    }

    int pW,cW;
    string str;

    string P;
    string C;
    string P_C;
    std::map<int,string> dic;
    int len = 256;
    std::map<int,string>::iterator iter;
    for(int i = 0 ; i < 256 ; i++) {
        string tmp{(char)i};
        dic.insert(pair<int,string>(i,tmp));
    }
    cW = V[1];
    str = dic[cW];
    for(int i = 2 ; i < V.size() ; i++) {
        pW = cW;
        cW = V[i];
        iter = dic.find(cW);
        if(iter != dic.end()) {
            str.append(dic[cW]);
            P = dic[pW];
            C = dic[cW][0];
            dic.insert(pair<int,string>(len++,P + C));
        }else {
            P = dic[pW];
            C = dic[pW][0];
            dic.insert(pair<int,string>(len++,P + C));
            str.append(P + C);
        }
    }

    Data ans;

    ans.length = str.length();
    ans.oneChar = new unsigned char[ans.length];

    for(int i = 0 ; i < str.length() ; i++) {
        ans.oneChar[i] = str.at(i);
    }

    return ans;
}
