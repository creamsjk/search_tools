/*************************************************************************
    > File Name: PageLib_test.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 22时47分39秒
    g++ PageLib_test.cpp  PageLib.cpp  DirScanner.cpp  XmlRss.cpp ../tools/tinyxml2-master/tinyxml2.cpp   -o PageLib_test

    success

 ************************************************************************/

#include <iostream>
#include "../include/PageLib.h"
#include <string>

using namespace std;

int main(){ 

    string s = "../messgae/人民网语料/";

    //递归读取 s目录下面的所有xml文件
    PageLib pag(s);

    pag.create("../data/page.xml");
    pag.store("../data/ripepage.dat");
    

   return 0;
}

