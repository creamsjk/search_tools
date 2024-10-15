/*************************************************************************
    > File Name: key_test.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 22时09分47秒
    g++ dict_test.cpp  DictProducer.cpp  SplitTool.cpp DirScanner.cpp  -o dict_test

     text success

 ************************************************************************/

#include "../include/DictProducer.h"
#include "../include/SplitTool.h"
#include "../include/KeyRecommander.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){ 

    SplitTool sp;
    /* DictProducer dict("./dict_text_cn.txt", &sp); */
    DictProducer dict("../messgae/yuliao/art/", &sp);
    /* dict.buildEnDict(); */
    dict.buildCnDict();
    dict.createIndex();
    dict.store("../data/dict.dat", "../data/sourceDict.dat");

    KeyRecommander k(sp, dict._dict, dict._res_index, dict._index);

    string s = "hello";
    vector<string> res = k.query(s);

    cout << s << endl;
    for(auto &a : res)
        cout << a << "  ";
    cout << endl;

    

}

