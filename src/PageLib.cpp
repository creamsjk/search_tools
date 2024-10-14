/*************************************************************************
    > File Name: PageLib.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 21时46分47秒
 ************************************************************************/

#include <iostream>
#include <fstream>

#include "../include/PageLib.h"


using std::string;
using std::vector;
using std::pair;

PageLib::PageLib(string sourcefilepath):_filepath(sourcefilepath){ 


}

void PageLib::create(string filepath){ 

    //从一个目录下面取出来所有 xml文件位置 放入file
    this->_rdirScanner.traverse(this->_filepath, "xml");
    vector<string> file = this->_rdirScanner.getFiles();
    XmlRss xml;
    
    //读取所有xml位置
    for(auto &s: file){ 
        xml.parseRss(s);
    }

    //在store中 将page 存起来的
    xml.store(filepath);
    //将所有正确xml 放入_pages
    /* vector<string> t = xml.getResMessage(); */
    this->_pages = xml.getResMessage();
    /* std::cout << "t=" << t.size() << "\n"; */
    /* for(auto &s: t) */
    /*     this->_pages.push_back(s); */

    //将网页库 存储起来

}

void PageLib::store(string filepath){ 

    int id = 1;
    int  end = 0;
    for(auto &s: _pages){ 

        this->_offsetLib[id];
        int page_size = s.size();
        
       this->_offsetLib[id] = pair<int, int>(end, end + page_size); 
        
       //会产生偏差
       end += page_size + 1;
       ++id;
       /* std::cout << s <<"\n"; */
       /* std::cout << s.size() << "\n"; */
       /* return ; */
    }

    /* return; */
    /* std::cout << "page  " << this->_pages.size() << "\n"; */
    /* std::cout << "asdasd  " << this->_offsetLib.size() << "\n"; */

    /* for(auto &s: this->_offsetLib){ */ 

    /*    std::cout << s.first << " " << s.second.first << " " << s.second.second; */
    /*    std::cout << "\n"; */
    /* } */

    std::ofstream ofs(filepath);
    
    if(!ofs.good()){ 

        std::cout << "PageLib::store open file failed \n";
        exit(-1);
    }

    for(auto &s: this->_offsetLib){ 

        ofs << s.first << " " << s.second.first << " " << s.second.second <<  "\n";
    }

    ofs.close();

    



}






