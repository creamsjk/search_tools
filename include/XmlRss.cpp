/*************************************************************************
    > File Name: XmlRss.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 21时08分32秒
 ************************************************************************/

#include "../include/XmlRss.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include "../tools/tinyxml2-master/tinyxml2.h"
#include <cerrno>
#include <cstdlib>
#include <cstring>                                                                                                
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::regex;

using namespace tinyxml2;


void XmlRss::parseRss(const string file){

    /* vector<RssItem> m_rss; */

    /* ifstream ss("./coolshell.xml"); */
    /* ifstream ss("../messgae/人民网语料/culture.xml"); */
    ifstream ss(file);
    if(!ss.good()){ 

        std::cout << "XmlRss::parseRss open file  failed \n";
        exit(-1);
    }
    string xml;
    
    
    string line;
    while(getline(ss, line)){

        xml += line;
    }
   //cout << xml << endl;    
   //while(1);

    RssItem r1;

    XMLDocument doc;
    /* doc.LoadFile("./coolshell.xml"); */
    XMLElement* firstElement = NULL;
    const char * firsttitle=NULL; 

    doc.Parse(  xml.c_str() );

    firstElement = doc.FirstChildElement("rss")->FirstChildElement( "channel" )->FirstChildElement("title");

    if(firstElement != NULL){
        firsttitle = firstElement->GetText();
        r1.title = firsttitle;
    }

    firstElement = doc.FirstChildElement("rss")->FirstChildElement( "channel" )->FirstChildElement("link");

    if(firstElement != NULL){
        firsttitle = firstElement->GetText();
        r1.link = firsttitle;
    }

    firstElement = doc.FirstChildElement("rss")->FirstChildElement( "channel" )->FirstChildElement("description");

    if(firstElement != NULL){
        firsttitle = firstElement->GetText();
        r1.description = firsttitle;
    }

    firstElement = doc.FirstChildElement("rss")->FirstChildElement( "channel" )->FirstChildElement("content:encoded");

    if(firstElement != NULL){

        firsttitle = firstElement->GetText();
        r1.content = firsttitle;
    }


    m_rss.push_back(r1);
    XMLElement* titleElement = NULL;
    const char* title = NULL; 

    XMLElement* rootElement = doc.FirstChildElement("rss")->FirstChildElement( "channel" )->FirstChildElement( "item");
    while(1){

        if(rootElement == nullptr)
            break;

        RssItem rr;
        titleElement = rootElement->FirstChildElement("title");
        if(titleElement != NULL){

            title = titleElement->GetText();
            rr.title = title;
        }


        titleElement = rootElement->FirstChildElement("link");
        if(titleElement != NULL){

            title = titleElement->GetText();
            rr.link = title;
        }



     titleElement = rootElement->FirstChildElement("description");
    if(titleElement != NULL){

     title = titleElement->GetText();
     
     regex reg("<[^>]+>");

     rr.description = title;
     rr.description = regex_replace(rr.description, reg, "");
    }


     titleElement = rootElement->FirstChildElement("content:encoded");
    if(titleElement != NULL){

     title = titleElement->GetText();
     rr.content = title;
     //正则表达式去除多余标签
     regex reg("<[^>]+>");

     rr.content = title;
     rr.content = regex_replace(rr.content, reg, "");
    }

     m_rss.push_back(rr);
     rootElement = rootElement->NextSiblingElement();
    }


    /* XMLText* textNode = titleElement->FirstChild()->ToText(); */
    /* title = textNode->Value(); */
    /* printf( "Name of play (2): %s\n", title ); */

    /* cout<< "识别完毕" << endl; */
    /* cout << m_rss.size() << endl; */
 

}

void XmlRss::store(const string  filename){
    ofstream ofs(filename);

    bool is_good = true;
    int doc_id = 1;
    for(size_t i=0;i < m_rss.size(); ++i){

        //恢复初始状态
        is_good = true;
        string res;
        res.append("<doc>\n");
        res.append("    ");

        res.append("<docid>");
        res.append(std::to_string(doc_id));
        res.append("</docid>\n");

        res.append("    ");
        res.append("<link>");
        res.append(m_rss[i].link);
        res.append("</link>\n");

        res.append("    ");
        if(m_rss[i].description.size() > 0){ 

            res.append("<content>");
            res.append(m_rss[i].description);
            res.append("</content>\n");
        }
        else if (m_rss[i].content.size() > 0){ 

            res.append("<content>");
            res.append(m_rss[i].content);
            res.append("</content>\n");
        }else{ 

            is_good = false;
        }

        res.append("</doc>\n");

        //如果符合就写入 否则不写入
        if(is_good){ 
            ++doc_id;
            this->m_res_message.push_back(res);
            ofs << res;

            
        }
    }
       
        ofs.close();
}

//返回引用减少空间使用
vector<string> & XmlRss::getResMessage(){ 

    return this->m_res_message;
}


