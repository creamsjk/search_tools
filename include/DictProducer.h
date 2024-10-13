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
#include "../include/DirScanner.h"


class DictProducer{ 

public:
    DictProducer(std::string tool, SplitTool * sp);
    ~DictProducer();
    void buildEnDict();
    void buildCnDict();
    void createIndex();
    void store(const char * filepath);

private:
    std::vector<std::string> _files; //所有语料内容
    std::unordered_map<std::string, int> _dict; // 词  频率
    std::map<std::string, std::set<int>> _index; // 单字 在res_index中的位置 set 存的是_res_index的下标
    std::vector<std::string> _res_index; // 存放dict 所有元素的数组
    std::vector<std::string> _pathfile; // 所有语料路径
    SplitTool * _cuttor; //分词对象指针

private:
    //给中文一个词 分成不同的单字
    std::vector<std::string>  withoutChineseWorld(const std::string &source);
    size_t nBytesCodes(const char ch);
    

};



#endif

