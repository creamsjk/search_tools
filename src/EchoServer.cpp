#include "../include/EchoServer.h"
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
, _redis_con(nullptr)
{
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    this->_redis_con = redisConnectWithTimeout("127.0.0.1",  6379, timeout);

}
void MyTask::process()
{
    //所有的业务逻辑全部在该函数中进行处理
    //处理完毕之后需要将数据发出去
    
    //处理协议  只处理正确的协议
    //三段式以 \r\n 结尾
    
    //读取第一行
    
    /* string a = "1\r\nhell\r\n<html>asdasdasa</html>\r\n"; */
    /* string a = "2\r\n老年人打车\r\n<html>asdasdasa</html>\r\n"; */
    string a = _msg;
    
    //消除字符结尾的换行
    a.pop_back();
     string status_id = a.substr(0, a.find(" "));
     

     string message_keys = a.substr(a.find(" ") + 1);

     string body_html = "<html>asdasdasd</html>";
     /* std::cout << status_id << "  " << message_keys << "|\n"; */

    /* std::cout << "msg: " << _msg << "|\n"; */

    /* string status = a.substr(0, a.find( "\r\n")); */
    /* string  status_id = status.substr(0, status.find('\r')); */
    

    /* string b = a.substr(a.find("\r\n") + 2); */
    /* string message_keys = b.substr(0, b.find("\r\n")); */

    /* string c = b.substr(b.find("\r\n") + 2); */
    /* string body_html = c.substr(0, c.find("\r\n")); */



    string res;
    //接受1 返回推荐关键字
    if(status_id == "1"){ 

        string s = "HGET WORD";
        s.append(" ").append(message_keys);

        redisReply *r2 = (redisReply*)redisCommand(this->_redis_con, s.c_str());

        if(r2->type == REDIS_REPLY_STRING){ 

            string s2 = "MEMBERS ";
            s2.append(r2->str).append("w");
            //返回值为ARRY 类型
            r2 = (redisReply*)redisCommand(this->_redis_con, s2.c_str());
            
            for(size_t i = 0; i < r2->elements; ++i)
                res.append(" ").append(r2->element[i]->str);


        }else if (r2->type == REDIS_REPLY_NIL){ 

            res.append("100\r\n");
            //从库中查找关键字 
            vector<string> ss = this->_server->_key.query(message_keys);
            string redis_add = "SADD ";
            redis_add.append(message_keys).append("w");
            
            string redis_hset= "HSET WORD ";
            redis_hset.append(message_keys).append("w");


            for(auto& a : ss){ 

                res.append(" ").append(a);
                redis_add.append(" ").append(a); 
                
            }

           //执行插入  现在 HSET WORD  中插入
           //再 再 SET 中插入 衍生的关键词
            r2 = (redisReply*)redisCommand(this->_redis_con, redis_hset.c_str());
            r2 = (redisReply*)redisCommand(this->_redis_con, redis_add.c_str());


            //返回最近的是个关键字到body


        }else if(r2->type == REDIS_REPLY_ERROR){ 



        } 
        //释放资源
        freeReplyObject(r2);
        
    }else if(status_id == "2"){ 



        string s = "HGET SENCE";
        s.append(" ").append(message_keys);

        redisReply *r2 = (redisReply*)redisCommand(this->_redis_con, s.c_str());

        if(r2->type == REDIS_REPLY_STRING){ 

            string s2 = "MEMBERS ";
            s2.append(r2->str).append("s");
            //返回值为ARRY 类型
            r2 = (redisReply*)redisCommand(this->_redis_con, s2.c_str());

            for(size_t i = 0; i < r2->elements; ++i)
                res.append(" ").append(r2->element[i]->str);


        }else if (r2->type == REDIS_REPLY_NIL){ 

            //接受2 返回关键字 的html网页
            res.append("200\r\n");

            //从web查询里面查找符合的网页 并发送过去
            vector<string> ss = this->_server->_web_query.query(message_keys);

            string redis_add = "SADD ";
            redis_add.append(message_keys).append("s");

            string redis_hset= "HSET WORD ";
            redis_hset.append(message_keys).append("s");


            for(auto& a : ss){ 

                res.append(" ").append(a);
                redis_add.append(" ").append(a); 

            }

            //执行插入  现在 HSET WORD  中插入
            //再 再 SET 中插入 衍生的关键词
            r2 = (redisReply*)redisCommand(this->_redis_con, redis_hset.c_str());
            r2 = (redisReply*)redisCommand(this->_redis_con, redis_add.c_str());




            //读取关键字
            //查找相关xml 文件发过去

        }else if(r2->type == REDIS_REPLY_ERROR){ 



        } 
        //释放资源
        freeReplyObject(r2);


    }else{ 

        res ="000000\r\n";
    }

    

    /* std::cout<<"res:" << res << "|\n"; */
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
