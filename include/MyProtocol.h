/*************************************************************************
    > File Name: MyProtocol.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月15日 星期二 09时48分19秒
 ************************************************************************/

#ifndef __MYPROTOCOL_H_
#define __MYPROTOCOL_H_

#include <string>

struct MyProtocol{ 

    //每个string 均以\r\n 结尾
    std::string  statu_id;
    std::string messages_key; //每个key之间以" "隔开
    std::string message_body;

};


#endif
