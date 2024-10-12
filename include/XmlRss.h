/*************************************************************************
    > File Name: XmlRss.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 20时57分21秒
 ************************************************************************/

#ifndef  __XMLRSS_H_
#define  __XMLRSS_H_

#include <vector>
#include <string>

struct RssItem{ 

    std::string title;
    std::string link;
    std::string description;
    std::string content;

};

class XmlRss{ 

public:
    void parseRss(const std::string file);//解析
    void store(const std::string filepath); //存储
    std::vector<std::string> &getResMessage();//返回存储所有正确的 xml 在store后面运行才行


private:
    std::vector<RssItem> m_rss;
    std::string m_openxml_name;
    std::vector<std::string> m_res_message;
};
 

#endif
