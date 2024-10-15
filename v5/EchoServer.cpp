#include "../include/Echoserver.h"
#include "../include/TcpConnection.h"

#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

MyTask::MyTask(const string &msg, const TcpConnectionPtr &con, TcpServer * server)
: _msg(msg)
, _con(con)
, _server(server) //使用server 中分词对象与字典 处理问题
{

}
void MyTask::process()
{
    //所有的业务逻辑全部在该函数中进行处理
    //处理完毕之后需要将数据发出去
    
    //处理协议  只处理正确的协议
    //三段式以 \r\n 结尾
    
    //读取第一行
    
    /* string a = "1\r\n张三 王五\r\n<html>asdasdasa</html>\r\n"; */
    string a = _msg;
    

    string status = a.substr(0, a.find( "\r\n"));
    string  status_id = status.substr(0, status.find('\r'));
    
    /* cout<<"a: " << a << endl; */
    /* cout<<"status_id: " << status_id << endl; */

    string b = a.substr(a.find("\r\n") + 2);
    string message_keys = b.substr(0, b.find("\r\n"));
    /* cout<<"b: " << b << endl; */
    /* cout<<"message_keys: " << message_keys<< endl; */

    string c = b.substr(b.find("\r\n") + 2);
    string body_html = c.substr(0, c.find("\r\n"));
    /* cout<<"c: " << c << endl; */
    /* cout << "body_html: " << body_html << endl; */



    string res;
    //接受1 返回推荐关键字
    if(status_id == "1"){ 

        res.append("100\r\n");

        //从库中查找关键字 
        vector<string> ss = this->_server->_key.query(message_keys);
        for(auto& a : ss)
            res.append(" ").append(a);
        
        
        //返回最近的是个关键字到body

    }else if(status_id == "2"){ 
        //接受2 返回关键字 的html网页
        res.append("200\r\n");

        //读取关键字
        //查找相关xml 文件发过去
        


    }else{ 

        res ="000000\r\n";
    }

    

    /* _con->sendInLoop(_msg); */
    _con->sendInLoop(res);
}

Echoserver::Echoserver(size_t threadNum, size_t queSize
                       , const string &ip
                       , unsigned short port
                       , SplitTool * sp)
: _pool(threadNum, queSize)
, _server(ip, port, sp)
{

}

Echoserver::~Echoserver()
{

}

//服务器的启动与停止
void Echoserver::start()
{
    _pool.start();//线程池对象启动起来

    using namespace std::placeholders;
    _server.setAllCallback(std::bind(&Echoserver::onNewConnection, this, _1)
                           , std::bind(&Echoserver::onMessage, this, _1)
                           , std::bind(&Echoserver::onClose, this, _1));
    _server.start();//TcpServer对象启动起来
}

void Echoserver::stop()
{
    _pool.stop();
    _server.stop();
}

//三个回调
void Echoserver::onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!!!" << endl;
}

void Echoserver::onMessage(const TcpConnectionPtr &con)
{
    //接收客户端的数据
    string msg = con->receive();
    cout << ">>>>recv msg from client " << msg << endl;

    //业务逻辑的处理如果比较复杂，可以业务逻辑的处理交个线程池
    MyTask task(msg, con, &this->_server);
    _pool.addTask(bind(&MyTask::process, task));
}

void Echoserver::onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!!" << endl;
}
