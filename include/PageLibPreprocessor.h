/*************************************************************************
    > File Name: PageLibPreprocessor.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月13日 星期日 17时14分40秒
 ************************************************************************/

#ifndef  __PAGELIBPREPROCESSOR_H_
#define  __PAGELIBPREPROCESSOR_H_

#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <set>
#include <cmath>

#include "WebPage.h"
#include "SplitTool.h"

class PageLibPreprocessor{ 

public:
    PageLibPreprocessor(SplitTool &sp); //初始化
    ~PageLibPreprocessor();
    void readInfoFromFile(std::string pagePath, std::string ripepagePath); //读取文件数据  和索引数据
    void cutRedundantPage(); //去重
    void buildInvertIndexMap(); //建立倒排索引库
    void storeOnDisk(std::string newSourcePath ,std::string newRipage, std::string indexPath); // 将去重文件库 以及 新的文件库  还有倒排索引文件 放入磁盘

private:
public:
    std::vector<WebPage> _pageList;
    std::unordered_map<int, std::pair<int, int>> _offsetLib;
    std::unordered_map<std::string, std::set<std::pair<int, double>>> _invertIndexTable;
    SplitTool * _wordCutter;





};





#endif
