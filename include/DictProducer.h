/*************************************************************************
    > File Name: DictProducer.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 20时40分50秒
 ************************************************************************/

#ifndef  __DICTPRODUCER_H_
#define  __DICTPRODUCER_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include "../include/SplitTool.h"


class DictProducer{ 

public:
    DictProducer(std::string tool, SplitTool * sp);
    ~DictProducer();
    void buildEnDict();
    void buildCnDict();
    void createIndex();
    void store(const char * filepath);

private:
    std::vector<std::string> _files;
    std::unordered_map<std::string, int> _dict;
    std::map<std::string, std::set<int>> _index; 
    SplitTool * _cuttor;

private:
    //去除中文中的标点符号
    std::string withoutSymbol(const std::string &source);
    

};



#endif

