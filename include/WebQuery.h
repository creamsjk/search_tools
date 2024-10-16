/*************************************************************************
    > File Name: WebQuery.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月15日 星期二 23时22分13秒
 ************************************************************************/

#ifndef  __WEBQUERY_H_
#define  __WEBQUERY_H_

#include "SplitTool.h"
#include "WebPage.h"

#include <set>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>



class WebQuery{ 

public:
    WebQuery(SplitTool * sp, 
    std::unordered_set<std::string> & stop_word,
    std::unordered_map<int, std::pair<int, int>> & offsetLib,
    std::unordered_map<std::string, std::set<std::pair<int, double>>> & invertIndexTable
    ,std::string sourceFilepath
    ,std::string indexFilePath
    );
    std::vector<std::string> query(std::string s, int num = 10);

private:
    void cutSence(std::string s); //对句子进行分词
    std::vector<double> getQueryWordsWeight(); //计算权重
    std::set<int> gewAllContent(); //获得所有词 文章的集合
    std::vector<int> getDocID(std::set<int> all_pages, int num = 10); //返回 最符合的number个 网页id
    std::vector<std::string> getContent(std::vector<int> id); //把id所属的文章取出来


private:
    SplitTool * _sp; //分词
    std::vector<std::string> _all_word; //存储所有词
    std::unordered_set<std::string> & _stop_word; //存储停用词
    std::unordered_map<int, std::pair<int, int>> & _offsetLib; //便宜库
    std::unordered_map<std::string, std::set<std::pair<int, double>>> & _invertIndexTable; //倒排索引库
    std::string _sourceFilepath;
    std::string _indexFilepath;


};


#endif
