/*************************************************************************
  > File Name: PageLibPreprocessor.cpp
  > Author: sunrie
  > Mail: 1102490208@qq.com 
  > Created Time: 2024年10月13日 星期日 17时40分27秒
 ************************************************************************/

#include <iostream>
#include <fstream>

#include "PageLibPreprocessor.h"

using std::string;
using std::vector;
using std::map;
using std::unordered_map;
using std::pair;
using std::set;

const string stop_zn = "../messgae/yuliao/stop_words_zh.txt";
const string stop_en = "../messgae/yuliao/stop_words_eng.txt";

PageLibPreprocessor::PageLibPreprocessor(SplitTool & sp):_wordCutter(&sp){ 

}

PageLibPreprocessor::~PageLibPreprocessor(){ 

}

void PageLibPreprocessor::readInfoFromFile(string pagePath, string ripepagePath){ 

    std::ifstream ifs(ripepagePath);
    if(!ifs.good()){ 

        std::cout << "PageLibPreprocessor::readInfoFromFile open failed \n" ;
        exit(-1);
    }

    string tmp;
    //将网页都读入 _pageList 里面
    while(std::getline(ifs, tmp, '\n')){ 

        string s_index = tmp.substr(0, tmp.find(' ')); 
        int index = atoi(s_index.c_str());
        string start_end = tmp.substr(tmp.find(' ') + 1); 

        string s_start = start_end.substr(0, start_end.find(' ')); 
        int start = atoi(s_start.c_str());

        string s_end = start_end.substr(start_end.find(' ') + 1); 
        int end = atoi(s_end.c_str());

        /* std::cout << "index=" << index << "  start=" << start << "  end=" << end << "\n"; */
        /* std::cout <<"pagePath:" << pagePath << "\n"; */



        WebPage page(pagePath, index, start, end);
        /* WebPage page(pagePath, ripepagePath, index ); */
        _pageList.push_back(page);
    }

    /* std::cout << "size=" << this->_pageList.size() << "\n"; */
    /* for(auto &s : this->_pageList) */
    /*     std::cout << s.getTitle() << "\n"; */

    ifs.close();
}

void PageLibPreprocessor::cutRedundantPage(){ 

    vector<uint64_t> figurs;
    for(auto &s: this->_pageList){ 
        //将每篇的文文章进行提取指纹
        string f = s.getContent();
        /* std::cout << f << "\n"; */

        figurs.push_back(this->_wordCutter->getFignerPrint(s.getContent()));

    }

    //全部指纹放入 figurs中
    /* for(auto &s:figurs) */
    /*     std::cout << s << "\n"; */

    //对比去重
    vector<WebPage> newPages;
    for(size_t i = 0; i < this->_pageList.size(); ++i ){ 

        bool isunique = true;
        for(size_t j = i + 1; j < this->_pageList.size(); ++j){ 

            if(this->_wordCutter->isEqual(figurs[i], figurs[j])){ 
                isunique = false;
                break;
            }

        }
        if(isunique)
            newPages.push_back(this->_pageList[i]);
    }

    /* std::cout << "pagesizei= " << this->_pageList.size() << "\n"; */
    /* for(auto &s:newPages) */
    /*     std::cout << s.getTitle() << "\n"; */
    /* std::cout << newPages.size() << "\n"; */


    //去重之后放入_offsetLib
    int id = 1;
    int end = 0;
    for(auto &s:newPages){ 

        s.setDocid(id);
        this->_offsetLib[id];
        int page_size = s.getDoc().size();
        /* std::cout  << id << " " << end << " " <<  end + page_size  << "\n"; */

        this->_offsetLib[id] = pair<int, int>(end, end + page_size);

        //会产生偏差
        end += page_size + 1;
        ++id;
    }
    this->_pageList = newPages;
}

//先运行 readInfoFromFile  cutRedundantPage  再运行本函数不然不行
void PageLibPreprocessor::buildInvertIndexMap(){ 



    //读取停用词
    std::ifstream ifs(stop_zn);                                                                                    
    if(!ifs.good()){ 

        std::cout << "DictProducer::buildEnDict  open stop_cn failed \n";
        exit(-1);
    } 

    //停用词
    set<string> stop;
    string stop_world;
    while(std::getline(ifs, stop_world, '\n')){ 

        /* //消除掉 \r  中文文档是以 \r\n结尾的话 */
        if(stop_world.find('\r'))
            stop_world.erase(stop_world.size()-1);
        stop.insert(stop_world);
        /* std::cout << stop_world  << " \n"; */
    } 

    ifs.close();

    std::ifstream ifs_en(stop_en);                                                                                    
    if(!ifs_en.good()){ 

        std::cout << "DictProducer::buildEnDict  open stop_cn failed \n";
        exit(-1);
    } 

    //停用词
    while(std::getline(ifs, stop_world, '\n')){ 

        /* //消除掉 \r  中文文档是以 \r\n结尾的话 */
        if(stop_world.find('\r'))
            stop_world.erase(stop_world.size()-1);
        stop.insert(stop_world);
        /* std::cout << stop_world  << " \n"; */
    } 

    ifs.close();





    /* std::cout << "begin TF \n"; */
    /* std::cout <<  "StopWord.size() = " << stop.size() << " \n"; */

    //vector  下标+1 代表的是 _pageList 里面的文章
    vector<unordered_map<string, int>> TF;
    set<string> all_word;
    for(auto &s: this->_pageList){ 

        vector<string> split_res = this->_wordCutter->cut(s.getContent());
        unordered_map<string , int> words;
        for(auto &w :split_res){ 

            words[w]++;
            //所有词 都加入set里面  除去停用词
            if(!stop.count(w))
                all_word.insert(w);
        }


        TF.push_back(words);
    } 

    /* for(auto &s: all_word) */
    /*     std::cout << s  << "\n"; */

    /* std::cout << "ALLWord.size() = " <<all_word.size() << " \n"; */

    /* std::cout << "begin DF \n"; */
    //包含 词的 文档的数量
    unordered_map<string ,int> DF;

    for(auto &s : all_word){ 

        //遍历TF 查看每篇文章是否含有s
        for(auto &paper : TF){ 
            if(paper.count(s))
                ++DF[s];
        }
        /* std::cout << ind++ << "\n"; */
    }

    /* std::cout << "DF.size() = "<< DF.size() << " \n"; */

    int N = TF.size();




    /* std::cout << "begin IDF \n"; */


    //每篇文章每个词的权重
    vector<pair<int, unordered_map<string, double>>> preTpre;
    for(size_t i = 0 ; i < TF.size(); ++i){ 

        preTpre.push_back(make_pair(i, unordered_map<string, double>()));
        for(auto &s : TF[i]){ 

            string word = s.first;
            int a = s.second;
            /* int b = DF[word]; */
            int b = 2;
            double IDF = log2(double(N)/double(b + 1));
            double w = a * IDF;
            preTpre[i].second[word] = w;

        }

    }
    /* std::cout << "IDF end \n"; */

    //归化权重
    for(size_t i =0; i < preTpre.size(); ++i ){ 

        double sumW = 0;

        for(auto &s : preTpre[i].second){ 
            //求每一篇文章的权重w 的平方和
            sumW += s.second * s.second;

        }

        double sqrt_sumW = sqrt(sumW);

        //重新计算每篇文章每个词的权重
        for(auto &s: preTpre[i].second){ 

            double newW = s.second/sqrt_sumW;
            s.second = newW;
        }

    }

    /* std::cout << "归化结束 \n"; */

    for(size_t i = 0; i < preTpre.size(); ++i){ 

        for(auto &umap : preTpre[i].second){ 

            this->_invertIndexTable[umap.first].insert(std::make_pair((preTpre[i].first + 1), umap.second));

        }
    }


    /* std::cout << "写入倒排索引 结束 \n"; */


    /* //测试打印 成功 */
    /* for(auto &s: this->_invertIndexTable){ */ 

    /*     std::cout << s.first << "\n"; */
    /*     for(auto &j : s.second) */
    /*         std::cout << j.first << "  " << j.second << "\n"; */

    /*     /1* break; *1/ */
    /* } */


}





//good
void PageLibPreprocessor::storeOnDisk(string newSourcePath, string  newRipage, string indexPath){ 

    std::ofstream ofs(newSourcePath);
    if(!ofs.good()){ 

        std::cout << "PageLibPreprocessor::storeOnDisk  open file  failed \n";
        exit(-1);
    }

    for(auto &s: this->_pageList)
        ofs << s.getDoc();

    ofs.close();


    std::ofstream ofs_ripage(newRipage);
    if(!ofs_ripage.good()){ 

        std::cout << "PageLibPreprocessor::storeOnDisk  open file  failed \n";
        exit(-1);
    }


    for(size_t i = 1; i <= this->_pageList.size(); ++i){ 

        ofs_ripage << i  << " " << this->_offsetLib[i].first << " " << this->_offsetLib[i].second  << "\n";

    }
    ofs_ripage.close();

    //写入倒排索引
    std::ofstream ofs_index(indexPath);
    if(!ofs.good()){ 

        std::cout << "PageLibPreprocessor::storeOnDisk  open file  failed \n";
        exit(-1);
    }

    //写入磁盘
    for(auto &s: this->_invertIndexTable){ 

        ofs_index << s.first ;
        for(auto &j : s.second){ 

            ofs_index << " " << j.first << " " << j.second;
        }
        ofs_index<< "\n";
    }

    ofs_index.close();

}




