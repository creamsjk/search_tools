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

        this->_offsetLib[id] = pair<int, int>(end, end + page_size);

        //会产生偏差
        end += page_size + 1;
        ++id;
    }
    this->_pageList = newPages;
}







