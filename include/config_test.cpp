/*************************************************************************
    > File Name: config_test.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 10时45分56秒
    测试成功 成功读取conf文件
    g++ config_test.cpp  Configuration.cpp  -o config_test


 ************************************************************************/

#include <iostream>
#include "Configuration.h"
#include <string>
#include <map>


using namespace std;

int main(){ 

    string s = "../conf/myconfig.conf";
    Configuration::getInstance()->readConfigur(s);
    map<string,string> res = Configuration::getInstance()->getConfigMap();
    for(auto &i : res)
        cout << "first " << i.first << "  second " << i.second << endl;
    

    return 0;
}

