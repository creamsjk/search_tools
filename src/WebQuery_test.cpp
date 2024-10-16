/*************************************************************************
    > File Name: PageLibPreprocessor_text.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月13日 星期日 17时56分25秒


    g++ PageLibPreprocessor_test.cpp  PageLibPreprocessor.cpp SplitTool.cpp  WebPage.cpp -o PageLibPreprocessor_test 

    测试通过

 ************************************************************************/

#include <iostream>
#include <string>

#include "../include/PageLibPreprocessor.h"
#include "../include/SplitTool.h"
#include "../include/WebQuery.h"


#include <unordered_set>
#include <string>

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

    
    unordered_set<string> stop;

    WebQuery web(&sp, stop, p._offsetLib, p._invertIndexTable, s3, s4);
    vector<string> s = web.query("老年人打车");

    for(auto &a : s)
        cout << a << endl;




    return 0;
}

