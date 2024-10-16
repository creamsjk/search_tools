/*************************************************************************
    > File Name: WebQuery.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月15日 星期二 23时43分41秒
 ************************************************************************/

#include "../include/WebQuery.h"

#include <algorithm>

using std::string;
using std::vector;
using std::map;
using std::set;
using std::unordered_map;
using std::unordered_set;
using std::pair;


WebQuery::WebQuery(SplitTool * sp,                                               
      std::unordered_set<std::string> & stop_word,
      std::unordered_map<int, std::pair<int, int>> & offsetLib,
      std::unordered_map<std::string, std::set<std::pair<int, double>>> &  invertIndexTable
      ,std::string sourceFilepath
      ,std::string indexFilePath
      )
:_sp(sp)
,_stop_word(stop_word)
,_offsetLib(offsetLib)
,_invertIndexTable(invertIndexTable)
,_sourceFilepath(sourceFilepath)
,_indexFilepath(indexFilePath)
{ 



}

void WebQuery::cutSence(string s){ 


    vector<string> tmp = this->_sp->cut(s);
    for(auto &word : tmp){ 

        //如果在停用词中没找到word
        if(!this->_stop_word.count(word)){ 

            this->_all_word.push_back(word);
        }
    }
}


std::vector<double> WebQuery::getQueryWordsWeight(){ 

    /* std::cout << "getQueryWordsWeight begin \n"; */
    vector<string> & queryWords = _all_word;

    // 1.计算TF:词频
    map<string, int> TF;
    for(auto& word : queryWords)
    {
        ++TF[word];
    }
    
    /* std::cout << "TF:\n"; */
    /* for(auto &a: TF) */
    /*     std::cout << a.first << "  " << a.second << "\n"; */
    // 2.计算IDF： TF中词的DF是1
    map<string, double> IDF;
    for(auto& word : TF)
    {
        /* IDF[word.first] = log(1) / log(2); */
        IDF[word.first] = log2(1.0/2.0 + 1 );
        
    }

    /* std::cout << "IDF:\n"; */
    /* for(auto &a: IDF) */
    /*     std::cout << a.first << "  " << a.second << "\n"; */

    // 3.求权重
    // 计录权重的平方和
    double w2_score = 0;
    map<string, double> W;
    for(auto& word : TF)
    {
        W[word.first] = word.second *  IDF[word.first];
        w2_score += (W[word.first]) * (W[word.first]);
    }

    /* std::cout << "W:\n"; */
    /* for(auto &a: W) */
    /*     std::cout << a.first << "  " << a.second << "\n"; */

    // 4.归一化
    map<string, double> W1;
    for(auto& word : W)
    {
        W1[word.first] = word.second / sqrt(w2_score);
    
    }

    /* std::cout << "W1:\n"; */
    vector<double> res;
    for(auto &a: W1){ 

        /* std::cout << a.first << "  " << a.second << "\n"; */
        res.push_back(a.second);
    }
        


    //现在词 与 权重 是一一对应的

    /* std::cout << "getQueryWordsWeight end \n"; */

    return res;

}

//取交集
set<int> WebQuery::gewAllContent(){ 

    /* std::cout << "getAllContent begin\n"; */
    

    vector<set<int>> sets;

    for (auto &s : this->_all_word) {
        std::set<int> tmp;
        for (auto &j : this->_invertIndexTable[s]) {
            tmp.insert(j.first);
        }
        sets.push_back(tmp);
    }

    // 初始化交集集合为第一个集合
    std::set<int> intersection = sets[0];

    // 依次与后续集合计算交集
    for (size_t i = 1; i < sets.size(); ++i) {
        std::set<int> temp;
        std::set_intersection(intersection.begin(), intersection.end(),
                              sets[i].begin(), sets[i].end(),
                              std::inserter(temp, temp.begin()));
        intersection = temp; // 更新交集集合

        /* // 调试输出：打印当前交集结果 */
        /* std::cout << "Intersection after set " << i << ": "; */
        /* for (int elem : intersection) { */
        /*     std::cout << elem << " "; */
        /* } */
        /* std::cout << std::endl; */
    }




    /* std::cout << "getAllContent end \n"; */
    return intersection;

}
vector<int> WebQuery::getDocID(set<int> all_pages, int num){ 

    /* vector<int> resultVec(all_pages.begin(), all_pages.end()); */
    //每篇文章 的 id  对应 的 词 的权重
    vector<pair<int, unordered_map<string, double>>> resultVec;
    for(auto &s : all_pages){ 
        int id = s;
        unordered_map<string, double> tmp;
        for(auto &word : _all_word){ 

            //it 为 word  在id 内的权值
            auto it = this->_invertIndexTable[word].find({ id, 0.0});
            tmp[word] = it->second;
        }
        resultVec.push_back(pair<int, unordered_map<string, double>>(id, tmp));
    }

    // 4.余弦相似算法计算 得到每一个docid 的cos*
    // 获得基准向量
    vector<double> Base = getQueryWordsWeight();
    // 保存一定会用到的基准向量平方根
    double Base_square_root = 0;
    double Base_square = 0;
    for(size_t i = 0; i < Base.size(); ++i)
    {
        Base_square += Base[i] * Base[i];
    }
    Base_square_root = sqrt(Base_square);

    /* std::cout << "Base end \n"; */

    // 定义比较函数，用于根据 pair 的第二个元素进行比较
    auto cmp = [](const std::pair<int, double>& left, const std::pair<int, double>& right) {
        return left.second < right.second; // 大顶堆，最大元素在堆顶
    };

    // 定义优先队列，使用自定义比较函数
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, decltype(cmp)> pq(cmp);


    // 余弦值
    for(size_t i = 0; i < resultVec.size(); ++i)
    {
        
        double cosNum = 0;
        double doc_square_root = 0;
        double sum = 0;
        double square_sum = 0;


        vector<double> tmp;
        for(auto &s: resultVec[i].second){ 

            tmp.push_back(s.second);

        }
        for(size_t i = 0; i < tmp.size(); ++i)
        {
            square_sum += tmp[i] * tmp[i];
            sum += Base[i] * tmp[i];
        }
        doc_square_root = sqrt(square_sum);
        cosNum = sum / (Base_square_root * doc_square_root);

        // 存入优先队列
        pq.push({resultVec[i].first, cosNum});
    }

    /* std::cout << "priority_queue  end \n"; */


    //renturn  num  docid
    int n;
    if((int)pq.size() >= num)
        n = num;
    else
        n = pq.size();

    vector<int> docId;
    for(int i = 0; i < n ; ++i){ 

        int tmp = pq.top().first;
        pq.pop();
        docId.push_back(tmp);
    }

    return docId;

}

vector<string> WebQuery::getContent(vector<int> id){ 


    vector<string> res;

    for(auto &i: id){ 

        WebPage p(this->_sourceFilepath, this->_indexFilepath, i);
        res.push_back(p.getDoc());
    }

    return res;

}

vector<string> WebQuery::query(string s , int num){ 

    this->cutSence(s);
    
    /* this->getQueryWordsWeight(); */
    /* return this->getContent(this->getDocID(this->gewAllContent(), num)); */

    set<int> b = this->gewAllContent();
    vector<int> a = this->getDocID(b);
    vector<string> c = this->getContent(a);

/*     for(auto &f : c) */
/*         std::cout << f <<"  "; */
/*     std::cout << "\n"; */

    
    vector<string> ff;

    return c;


}







