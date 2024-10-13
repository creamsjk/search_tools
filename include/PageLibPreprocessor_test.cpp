/*************************************************************************
    > File Name: PageLibPreprocessor_text.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月13日 星期日 17时56分25秒
 ************************************************************************/

#include <iostream>
#include <string>

#include "PageLibPreprocessor.h"
#include "SplitTool.h"



using namespace std;

int main(){ 

    string s1 = "../data/page.xml";
    string s2 = "../data/ripepage.dat";

    SplitTool sp;

    PageLibPreprocessor p(sp);
    p.readInfoFromFile(s1, s2);
    p.cutRedundantPage();

    return 0;
}

