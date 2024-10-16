#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "Acceptor.h"
#include "EventLoop.h"
#include "Configuration.h"
#include "SplitTool.h"
#include "DictProducer.h"
#include "DirScanner.h"
#include "WebPage.h"
#include "PageLib.h"
#include "XmlRss.h"
#include "PageLibPreprocessor.h"
#include "KeyRecommander.h"
#include "WebQuery.h"

class TcpServer
{
public:
    TcpServer(const string &ip, unsigned short port, SplitTool* sp);
    ~TcpServer();

    //服务器的启动与停止
    void start();
    void stop();

    //设置三个注册
    void setAllCallback(TcpConnectionCallback &&cb1
                        , TcpConnectionCallback &&cb2
                        , TcpConnectionCallback &&cb3);
private:
    void preheatServer();

private:
    Acceptor _acceptor;
    EventLoop _loop;


private:
public:
    std::unordered_map<std::string, int> _dict; // 词  频率
    std::vector<std::string> _res_index; // 存放dict 所有元素的数组
    std::map<std::string, std::set<int>> _index; // 单字 在res_index中的位置
    std::unordered_set<std::string> _stop_word; //停用词
    std::unordered_map<int, std::pair<int, int>>  _offsetLib; //便宜库
    std::unordered_map<std::string, std::set<std::pair<int, double>>>  _invertIndexTable;
    std::string _sourceFilepath;
    std::string _indexFilepath;

public:
    SplitTool * _sp;
    KeyRecommander _key;
    WebQuery _web_query;


};

#endif
