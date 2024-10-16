#include "../include/TcpServer.h"
#include <iostream>


TcpServer::TcpServer(const string &ip, unsigned short port, SplitTool * sp)
: _acceptor(ip, port)
, _loop(_acceptor)
, _sp(sp)
,_key(*_sp,_dict,_res_index,_index)
,_web_query(sp, _stop_word, _offsetLib, _invertIndexTable, "../data/newpage.xml", "../data/newripage.dat")
{
    //这两个字符串分别为  去重之后xml  和 偏移库
    //后续可以更改 WebQuery库的架构 

    //加载配置文件
    preheatServer();
    
    
}

TcpServer::~TcpServer()
{

}

//服务器的启动与停止
void TcpServer::start()
{
    
    _acceptor.ready();//让服务器处于监听状态
    _loop.loop();//让EventLoop循环起来
}

void TcpServer::stop()
{
    _loop.unloop();
}

//设置三个注册
void TcpServer::setAllCallback(TcpConnectionCallback &&cb1
                                , TcpConnectionCallback &&cb2
                                , TcpConnectionCallback &&cb3)
{
    _loop.setNewConnectionCallback(std::move(cb1));//连接建立
    _loop.setMessageCallback(std::move(cb2));//消息到达
    _loop.setCloseCallback(std::move(cb3));//建立断开
}

//服务器预热 包括 单词分词 创建倒排索引 语料读取 等等
void TcpServer::preheatServer(){ 

    //有全局结巴指针 不需要在创建结巴对象

    //1.读取config 文件 获取 字典 字典索引   语料 语料便宜库 倒排索引表
    Configuration::getInstance()->readConfigur("../conf/myconfig.conf");
    std::cout << "1 begin \n";
    map<string, string> res = Configuration::getInstance()->getConfigMap();
    //读取成功
    /* for(auto &i : res) */
    /*      std::cout << i.first << " " << i.second << "\n"; */
    
    /* std::cout <<"a:"<<res["chinese_words"] <<"111\n"; */

    if(_sp == nullptr)
        std::cout << " nullllllllllllllllll \n";


    /* SplitTool sp; */

    //2. 分词 创建字典 和索引 
    /* DictProducer dict(res["chinese_words"], _sp); */
    DictProducer dict(res["chinese_words"], _sp);
    dict.buildCnDict();
    dict.buildEnDict();
    dict.createIndex();
    dict.store(res["index_dict"] ,res["sourceDict"]);

    /* while(1); */

    std::cout << "3 begin \n";
    //3.读取语料 存语料 和他的偏移库
    PageLib pages(res["yuliao"]);
    pages.create(res["pages"]);
    pages.store(res["ripepage"]);

    
    /* std::cout << "4 begin \n"; */
    //4.倒排索引库  去重之后的页面库 以及 去重后的偏移库
    PageLibPreprocessor p(*_sp);
    p.readInfoFromFile(res["pages"], res["ripepage"]);
    p.cutRedundantPage();
    p.buildInvertIndexMap();
    p.storeOnDisk(res["newpages"], res["newripepage"], res["index"]);

    // 预热完成

    //5.读取字典 和 偏移到数据里面来 还有停用词
    
    /* std::cout << "5 begin \n"; */
    //c初始化关键字查询参数
    _dict = dict._dict;
    _index = dict._index;
    _res_index = dict._res_index;
    _stop_word = dict._stop_word; 

    //初始化网页查询参数
    _sourceFilepath = res["newpages"];
    _indexFilepath = res["newripepage"];

    /* std::cout << "_sourceFilepath:"<< _sourceFilepath << "\n"; */
    /* std::cout << "_indexFilepath:"<< _indexFilepath << "\n"; */

    _offsetLib = p._offsetLib;
    _invertIndexTable = p._invertIndexTable;

    
    

    
    std::cout << "初始化完成 \n";

    


}

