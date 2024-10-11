/*************************************************************************
    > File Name: SplitTool.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 20时48分36秒
 ************************************************************************/

#ifndef __SPLITTOOL_H_
#define __SPLITTOOL_H_

#include "../tools/simhash/cppjieba/Jieba.hpp"

#include <vector>
#include <string>

class SplitTool{ 

public:
    SplitTool();
    ~SplitTool();
    std::vector<std::string> cut(std::string s);
    
private:
    cppjieba::Jieba jieba;


};



#endif

