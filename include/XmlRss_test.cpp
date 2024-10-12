/*************************************************************************
    > File Name: XmlRss_test.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 21时14分36秒
    
    g++ XmlRss_test.cpp  ../tools/tinyxml2-master/tinyxml2.cpp XmlRss.cpp  -o XmlRss_test
    test success 
 ************************************************************************/

#include <iostream>
#include "XmlRss.h"
#include <string>
using namespace std;

int main(){ 

   string s1 = "../messgae/人民网语料/edu.xml"; 
   string s2 = "../messgae/人民网语料/book.xml"; 

   XmlRss r;
   r.parseRss(s1);
   r.parseRss(s2);
   r.store("../data/qq.xml");
   vector<string> ff = r.getResMessage();
   /* for(auto &a: ff) */
   /*     cout << a << endl; */


    return 0;
}

