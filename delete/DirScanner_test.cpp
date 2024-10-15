/*************************************************************************
    > File Name: DirScanner_test.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 16时24分01秒
;
g++ DirScanner_test.cpp  DirScanner.cpp  -o DirScanner_test

test success 
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "DirScanner.h"
using namespace std;

int main(){ 

    DirScanner dirs;
    string  path = "../messgae/yuliao/";
    dirs.traverse(path, "txt");
    cout << "Asdasdas" << endl;

    vector<string> res = dirs.getFiles();
    for(auto &s: res)
        cout << s << endl;


    return 0;
}

