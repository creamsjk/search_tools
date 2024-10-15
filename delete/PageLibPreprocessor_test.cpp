/*************************************************************************
    > File Name: PageLibPreprocessor_text.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月13日 星期日 17时56分25秒
g++ PageLibPreprocessor_test.cpp  PageLibPreprocessor.cpp SplitTool.cpp  WebPage.cpp -o PageLibPreprocessor_test 


 ************************************************************************/

#include <iostream>
#include <string>

#include "PageLibPreprocessor.h"
#include "SplitTool.h"



using namespace std;

int main(){ 

    string s1 = "../data/page.xml";
    string s2 = "../data/ripepage.dat";

    string s3 = "../data/newpage.xml";
    string s4 = "../data/newripage.dat";
    string s5 = "../data/index.dat";
    

    SplitTool sp;

    PageLibPreprocessor p(sp);
    p.readInfoFromFile(s1, s2);
    p.cutRedundantPage();
    p.buildInvertIndexMap();
    p.storeOnDisk(s3, s4, s5);

    return 0;
}

