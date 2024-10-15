/*************************************************************************
    > File Name: KeyRecommander.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月15日 星期二 15时30分40秒
 ************************************************************************/

#include "../include/KeyRecommander.h"
#include <cmath>
#include <stdlib.h>
#include <numeric>
#include <algorithm>

using std::vector;
using std::map;
using std::string;
using std::set;
using std::unordered_map;
using std::pair;


KeyRecommander::KeyRecommander(SplitTool &sp,                                                               
          std::unordered_map<std::string, int> &dict,
          std::vector<std::string> &res_index,
          std::map<std::string, std::set<int>> &index)
    :_sp(sp)
    ,_dict(dict)
    ,_res_index(res_index)
    ,_index(index)
{ 


}


KeyRecommander::~KeyRecommander(){ 

}

// s --> t distance s 到 t 的距离
int KeyRecommander::distance(string &s, string &t){ 

     int m = t.length();
        vector<int> f(m + 1);
        iota(f.begin(), f.end(), 0);
        for (char x : s) {
            int pre = f[0];
            f[0]++;
            for (int j = 0; j < m; j++) {
                int tmp = f[j + 1];
                f[j + 1] = x == t[j] ? pre : std::min(std::min(f[j + 1], f[j]), pre) + 1;
                pre = tmp;
            }
        }
        return f[m];
}

// 返回关键字集合 最多 number个
vector<string> KeyRecommander::contentWords(string key, int number){ 

    //words 里面存的每一个都是单字
    vector<string> words = this->_sp.cutOne(key);

    

    //将所有符合的词都拿出来 放入set里面
    set<int>  good_words;
    for(auto &s: words){ 

        /* std::cout << s  << "  "; */
        for(auto &j : this->_index[s]){ 

            good_words.insert(j);
        }
    }
        /* std::cout  << "\n"; */
    //现在 good_words 里面存放的是所有符合词语的下标
    //
    //
    //优先队列 dis  频率  词
     std::priority_queue<std::pair<std::pair<int, int>, std::string>, 
                        std::vector<std::pair<std::pair<int, int>, std::string>>, 
                        Compare> pq;
    for(auto &s: good_words){ 

        string content = this->_res_index[s];
        int dis = this->distance(content, key);
        /* std::cout << content  << "  " << dis << "\n"; */

        pq.push(pair<pair<int,int> ,string>(pair<int,int>(dis, this->_dict[content]), content));
    }
        /* std::cout  << "\n"; */

    //如果pq 内容大于 10  就返回是个
    vector<string> res;
    int n ;
    if((int)pq.size() >= number){ 

        n = number;
    }else{ 

        n = pq.size();
    }
    for(int i =0; i < n; ++i){ 

        res.push_back(pq.top().second);
        pq.pop();
    }


    return res;

};

//返回查询结果
vector<string> KeyRecommander::query(string s){ 

    return contentWords(s);
}



















