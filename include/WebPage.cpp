/*************************************************************************
    > File Name: WebPage.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月13日 星期日 14时52分21秒

    只写好了 第一个构造函数 因为xml原因 忘记提取title 了 
    故没有测试title 其他均以测试 正常


 ************************************************************************/

#include <fstream>
#include <vector>
#include <iostream>

#include "../include/WebPage.h"


using std::string;
using std::vector;

//源文件  索引文件  索引id
WebPage::WebPage(string sourceFilepath, string indexFilepath, int index){ 


    /* std::cout << "sourceFilepath: " <<  sourceFilepath << "\n"; */
    /* std::cout << "indexFilepath: " << indexFilepath << "\n"; */
    /* std::cout << "index=" << index << "\n"; */
    std::ifstream ifs_index(indexFilepath);
    
    string tmp;
    for(int i = 0; i < index; ++i){ 
        std::getline(ifs_index, tmp, '\n');
    }
    /* std::cout << "tmp: " << tmp << "\n"; */

    //tmp  = 10 29129 29736 
    int start = 0;
    int end = 0;

    string start_end = tmp.substr(tmp.find(' ') + 1);
    
    /* std::cout << "start_end: " << start_end << "\n"; */
    int possion = start_end.find(' ');

    string s_start = start_end.substr(0, possion);
    string s_end = start_end.substr(possion + 1);

    start = atoi(s_start.c_str());
    end = atoi(s_end.c_str());

    /* std::cout << "start=" << start << "\n"; */
    /* std::cout << "end=" << end << "\n"; */

    ifs_index.close();

    std::ifstream ifs(sourceFilepath);

    if(!ifs.good()){ 

        std::cout << "WebPage::WebPage  open failden failed \n";
        exit(-1);
    }


    /* if(start != 0) */
    /*     start--; */

    //修正PagLib  存放偏移库的误差  
    start -= index;
    end -= index;

    //第一个遍历的时候 会出现 start < 0 的情况 额外修正
    if(start < 0 )
        start = 0;

    ifs.seekg(start);
    int len = end -start + 1;
    char buf[len];

    ifs.read(buf, end - start + 1);
    buf[len -1] = '\0';

    this->_doc = buf;
    
    /* std::cout << "doc:" << this->_doc << "\n"; */
    /* std::cout << "doc:" << this->_doc.size() << "\n"; */
    /* std::cout << "len:" <<  len << "\n"; */

    //用字符串处理 出来 id  title  url  内容
    
    string tmp_docid = this->_doc.substr( this->_doc.find("<docid>"), this->_doc.find("</docid>"));
    string s_docid = tmp_docid.substr(tmp_docid.find('>') + 1);
    this->_docid = atoi(s_docid.substr(0, s_docid.find('<')).c_str());
    /* std::cout << "_docid:" << this->_docid << "\n"; */
     
    string tmp_title = this->_doc.substr( this->_doc.find("<title>"), this->_doc.find("</title>"));
    string s_title = tmp_title.substr(tmp_title.find('>') + 1);
    this->_docTitle = s_title.substr(0, s_title.find("</title>")).c_str();
    /* std::cout << "title:" << this->_docTitle << "\n"; */

    string tmp_link = this->_doc.substr( this->_doc.find("<link>"), this->_doc.find("</link>"));
    /* std::cout << "tmp_link:" << tmp_link << "\n"; */

    string s_link = tmp_link.substr(tmp_link.find('>') + 1);
    /* std::cout << "s_link:" << s_link << "\n"; */

    this->_docUrl = s_link.substr(0, s_link.rfind("</link>")).c_str();
    /* std::cout << "url:" << this->_docUrl << "\n"; */
    

    string tmp_docContent = this->_doc.substr( this->_doc.find("<content>"), this->_doc.find("</content>"));
    string s_content = tmp_docContent.substr(tmp_docContent.find('>') + 1);
    this->_docContent = s_content.substr(0, s_content.rfind("</content>")).c_str();
    /* std::cout << "content:" << this->_docContent << "\n"; */


}

WebPage::WebPage(string sourceFilepath, int index , int start, int end){ 

/*     std::cout << "sourceFilepath: " <<  sourceFilepath << "\n"; */
/*     std::cout << "index: " <<  index << "\n"; */
/*     std::cout << "start: " <<  start << "\n"; */
/*     std::cout << "end : " <<  end<< "\n"; */

    /* std::cout << "-2\n"; */

    std::ifstream ifs(sourceFilepath);
    if(!ifs.good()){ 

        std::cout << "WebPage::WebPage  open failden failed \n";
        exit(-1);
    }

    //修正PagLib  存放偏移库的误差  
    start -= index;
    end -= index;

    if(start < 0 )
        start = 0;
    

    ifs.seekg(start);
    int len = end -start + 1;
    char buf[len];

    ifs.read(buf, end - start + 1);
    buf[len -1] = '\0';

    this->_doc = buf;
    //用字符串处理 出来 id  title  url  内容
    
    string tmp_docid = this->_doc.substr( this->_doc.find("<docid>"), this->_doc.find("</docid>"));
    
    string s_docid = tmp_docid.substr(tmp_docid.find('>') + 1);
    this->_docid = atoi(s_docid.substr(0, s_docid.find('<')).c_str());
     
    string tmp_title = this->_doc.substr( this->_doc.find("<title>"), this->_doc.find("</title>"));
    string s_title = tmp_title.substr(tmp_title.find('>') + 1);
    this->_docTitle = s_title.substr(0, s_title.find("</title>")).c_str();

    string tmp_link = this->_doc.substr( this->_doc.find("<link>"), this->_doc.find("</link>"));
    string s_link = tmp_link.substr(tmp_link.find('>') + 1);
    this->_docUrl = s_link.substr(0, s_link.rfind("</link>")).c_str();
    

    string tmp_docContent = this->_doc.substr( this->_doc.find("<content>"), this->_doc.find("</content>"));
    string s_content = tmp_docContent.substr(tmp_docContent.find('>') + 1);
    this->_docContent = s_content.substr(0, s_content.rfind("</content>")).c_str();

}

WebPage::~WebPage(){ 


}

string WebPage::getDoc(){ 
    
    return this->_doc;
}

int WebPage::getDocid(){ 
    
    return this->_docid;
}

string WebPage::getTitle(){ 
    
    return this->_docTitle;
}


string WebPage::getDocUrl(){ 
    
    return this->_docUrl;
}

string WebPage::getContent(){ 
    
    return this->_docContent;
}

void WebPage::setDocid(int id){ 

    //重新组装一个字符串吧

    string res;
        res.append("<doc>\n");
        res.append("    ");

        res.append("<docid>");
        res.append(std::to_string(id));
        res.append("</docid>\n");

        res.append("    ");
        res.append("<title>");
        res.append(this->_docTitle);
        res.append("</title>\n");

        res.append("    ");
        res.append("<link>");
        res.append(this->_docUrl);
        res.append("</link>\n");

        res.append("    ");
        res.append("<content>");
        res.append(this->_docContent);
        res.append("</content>\n");

        res.append("</doc>\n");

        this->_doc = res;
        this->_docid = id;

}

















