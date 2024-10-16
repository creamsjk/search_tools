#ifndef __ECHOSERVER_H__
#define __ECHOSERVER_H__

#include "ThreadPool.h"
#include "TcpServer.h"
#include <hiredis/hiredis.h>


class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con,  TcpServer * server);
    void process();
private:
    string _msg;
    TcpConnectionPtr _con; //tcp 连接
    TcpServer * _server; //服务器连接 使用服务器函数
    redisContext * _redis_con;	//redis 连接

};

class Echoserver
{
public:
    Echoserver(size_t threadNum, size_t queSize
               , const string &ip
               , unsigned short port
               ,SplitTool * sp);
    ~Echoserver();

    //服务器的启动与停止
    void start();
    void stop();

    //三个回调
    void onNewConnection(const TcpConnectionPtr &con);
    void onMessage(const TcpConnectionPtr &con);
    void onClose(const TcpConnectionPtr &con);

private:
    ThreadPool _pool;//线程池对象
    TcpServer _server;//TcpServer服务器对象

};

#endif
