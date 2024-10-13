/*************************************************************************
    > File Name: WebPage.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月13日 星期日 14时38分32秒
 ************************************************************************/

#ifndef  __WEBPAGE_H_
#define  __WEBPAGE_H_


#include <string>

class WebPage{ 

public:
    WebPage(std::string sourceFilePath, std::string indexFilePath , int index);  //
    WebPage(std::string sourceFilepath, int index, int start, int end);
    ~WebPage();
    std::string getDoc(); //返回整篇文章 
    int getDocid(); //返回文档id
    std::string getTitle();  //返回文档标题
    std::string getDocUrl(); //返回文档url
    std::string getContent(); //返回文档内容


private:
    std::string _doc; //整篇文章包含xml
    int _docid;  //文档id
    std::string _docTitle;  //文档标题
    std::string _docUrl;    //文档url
    std::string _docContent; //文档标题



};






#endif
