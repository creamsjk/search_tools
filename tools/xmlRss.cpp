/*************************************************************************
    > File Name: xmlRss.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年08月27日 星期二 22时07分18秒
    g++ xmlRss.cpp  tinyxml2-master/tinyxml2.cpp  -o xmlRss

 ************************************************************************/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <regex>
#include "./tinyxml2-master/tinyxml2.h"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

/* using namespace std; */
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::regex;

using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader(){
       m_rss.clear();
    }
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> m_rss;
    string m_openxml_name;
};



void RssReader::parseRss(){

    /* vector<RssItem> m_rss; */

    /* ifstream ss("./coolshell.xml"); */
    ifstream ss("../messgae/人民网语料/culture.xml");
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

void RssReader::dump(const string & filename){
    ofstream ofs(filename);

    bool is_good = true;
    for(size_t i=0;i < m_rss.size(); ++i){

        ofs<<"<doc>"<< "\n";
        
        ofs<<"    "<< "<docid>" << i+1 << "</docid>" << " \n";
        ofs<<"    "<< "<title>" <<m_rss[i].title << "</title>" << " \n";
        ofs<<"    "<< "<link>" << m_rss[i].link << "</link>" <<  "\n";
        /* ofs<<"    "<< "<description>" << m_rss[i].description << "</description>" <<endl;; */
        /* ofs<<"    "<< "<content>" << m_rss[i].content << "</content>" << endl;; */
        if(m_rss[i].description.size() > 0)
            ofs<<"    "<< "<content>" << m_rss[i].description << "</content>" <<"\n";
        else if (m_rss[i].content.size() > 0){ 
            ofs<<"    "<< "<content>" << m_rss[i].content << "</content>" << "\n";
        }else{ 

            is_good = false;
            ofs<<"</doc>"<< "\n";
            break;
        }

        ofs<<"</doc>"<< "\n";
    }
    /* cout << "输出完毕" << endl; */

        ofs.close();
        if(!is_good){ 
            
            //删除掉这个不符合的文件 
            const char * name = filename.c_str();
            remove(name);
        }

}


int main(){

    RssReader s1;
    s1.parseRss();
    s1.dump("./abc.txt");

    return 0;
}




