/*************************************************************************
    > File Name: SplitTool_test.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 21时06分24秒

    SplitTool  单元测试
    g++ SplitTool_test.cpp SplitTool.cpp  -o SplitTool_test

    测试成功
    simasher通过
    
 ************************************************************************/

#include <iostream>
#include "../include/SplitTool.h"
using namespace std;

int main(){ 


    SplitTool sp;
    /* string s = "其实很多事情，不需要\"有意义\"，吃喝玩乐不等于虚度光阴，吃苦耐劳也不等于意义非凡。当你焦虑内耗时，请一定记得，人生只是各种体验的叠加，只要你想，你就可以去做那些无意义的事，比如发呆，看日出，数星星。你的体验，就是最大的意义。人生不是一定要去做大家世俗认为有意义的事，意义是自己赋予的，人生是旷野不是轨道，只要当下你是享受的就是有意义的。"; */
    /* vector<string> res = sp.cut(s); */
    /* for(auto &word:res){ */ 
        /* cout << "word = " << word << endl; */
    /* } */

    string s1 = "我爱你";
    string s2 = "爱上打算打算打洒洒的";
    string s3 = "我爱你";
    uint64_t u2 = sp.getFignerPrint(s2);
    uint64_t u1 = sp.getFignerPrint(s1);

    cout << "u1=" << u1 << endl;
    cout << "u2=" << u2 << endl;
    cout << "u1 u2 是否相等:" << sp.isEqual(u1, u2) << endl;



}

