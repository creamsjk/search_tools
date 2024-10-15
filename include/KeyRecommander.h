/*************************************************************************
    > File Name: KeyRecommander.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月15日 星期二 15时18分48秒
 ************************************************************************/

#ifndef  __KEYRECOMMANDER_H_
#define  __KEYRECOMMANDER_H_

#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>

#include "SplitTool.h"

class KeyRecommander{ 

public:
    KeyRecommander(SplitTool &sp,
        std::unordered_map<std::string, int> &dict,
        std::vector<std::string> &res_index,
        std::map<std::string, std::set<int>> &index);
    /* KeyRecommander(SplitTool &sp); */
    ~KeyRecommander();
public:
    std::vector<std::string> query(std::string s); //查询关键字 返回一定数量的相关关键字
    void setData(std::unordered_map<std::string, int> &dict,
        std::vector<std::string> &res_index,
        std::map<std::string, std::set<int>> &index); //设置参数

private:
    int distance(std::string &s1, std::string &s2); //s1 -> 转换成s2需要的距离
    std::vector<std::string>  contentWords(std::string key, int number = 10);// 返回所有和关键字有关吧的词 最多返回number个关键字


private:
        SplitTool &_sp;
        std::unordered_map<std::string, int>& _dict; // 词  频率
        std::vector<std::string>& _res_index; // 存放dict 所有元素的数组
        std::map<std::string, std::set<int>>& _index; // 单字 在res_index中的位置


};


// 定义比较函数对象
struct Compare {
    bool operator()(const std::pair<std::pair<int, int>, std::string>& a, const std::pair<std::pair<int, int>, std::string>& b) {

        if(a.first.first == b.first.first){ 

            // 如果第一个 int 相同，比较第二个 int，从大到小排序
            return a.first.second < b.first.second;
        }
         // 第一个 int 从小到大排序
        return a.first.first > b.first.first;
        
    }
};

#endif
