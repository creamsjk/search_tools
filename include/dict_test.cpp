/*************************************************************************
    > File Name: dict_test.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 22时09分47秒
    g++ dict_test.cpp  DictProducer.cpp  SplitTool.cpp DirScanner.cpp  -o dict_test

     text success

 ************************************************************************/

#include "DictProducer.h"
#include "SplitTool.h"
#include <iostream>

int main(){ 

    SplitTool sp;
    /* DictProducer dict("./dict_text_cn.txt", &sp); */
    DictProducer dict("../messgae/yuliao/art/", &sp);
    /* dict.buildEnDict(); */
    dict.buildCnDict();
    dict.createIndex();
    dict.store("../data/dict.dat");

    

}

