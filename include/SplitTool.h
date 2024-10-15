/*************************************************************************
    > File Name: SplitTool.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 20时48分36秒
 ************************************************************************/

#ifndef __SPLITTOOL_H_
#define __SPLITTOOL_H_

#include "../tools/simhash/cppjieba/Jieba.hpp"
#include "../tools/simhash/Simhasher.hpp"

#include <vector>
#include <string>

class SplitTool{ 

public:
    SplitTool();
    ~SplitTool();
    std::vector<std::string> cut(std::string s); //分词
    uint64_t getFignerPrint(std::string message, int topN = 5); //生成指纹
    bool isEqual(uint64_t left, uint64_t right); //判断指纹是否相等
    std::vector<std::string> cutOne(std::string s); //分字
    
private:
    cppjieba::Jieba jieba;
    simhash::Simhasher simasher;
    
private:
    std::vector<std::string> withoutChineseWorld(const std::string &soource);
    size_t nBytesCodes(const char ch);


};



#endif

