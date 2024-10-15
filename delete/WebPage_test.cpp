/*************************************************************************
    > File Name: WebPage_test.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月13日 星期日 15时13分45秒
    g++ WebPage_test.cpp  WebPage.cpp  -o WebPage_test

    success 
 ************************************************************************/

#include <iostream>
#include "WebPage.h"
#include <string>
using namespace std;

int main(){ 

    string s1 = "../data/ripepage.dat";
    /* int index = 10; */
    int index = 1;
    string s2 = "../data/page.xml";
    WebPage w(s2, s1, index);
    /* WebPage w(s2,  index, 13974950, 13976016); */
   cout << "doc:\n" << w.getDoc() << endl;
   cout << "id:\n" << w.getDocid() << endl;
   cout << "title:\n" << w.getTitle() << endl;
   cout << "url:\n" << w.getDocUrl() << endl;
   cout << "content:\n" << w.getContent() << endl;
    


    return 0;
}

