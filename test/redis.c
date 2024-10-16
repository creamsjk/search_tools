/*************************************************************************
    > File Name: redis.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月16日 星期三 20时43分44秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<hiredis/hiredis.h>

int main(int argc, char **argv) {
    unsigned int j, isunix = 1;
    redisContext *c;		
    redisReply *reply;
    const char *hostname =  "127.0.0.1";
    int port = 6379;

       
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
        //该函数用来连接redis数据库， 两个参数分别是redis数据库的ip和端口，端口号一般为6379。
        c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);	
            redisFree(c);	//释放redisConnect()所产生的连接。
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

	 /* PING server */
    reply =(redisReply*)redisCommand(c,"PING");	
    //该函数用于执行redis数据库中的命令，第一个参数为连接数据库返回的redisContext，剩下的参数为变参.。
	//此函数的返回值为void*，但是一般会强制转换为redisReply类型，以便做进一步的处理。
    
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);	//释放redisCommand执行后返回的的redisReply所占用的内存。

    reply = (redisReply*)redisCommand(c,"INCR counter");
    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);
    /* again ... */
    reply = (redisReply*)redisCommand(c,"INCR counter");
    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(c, "HGET word hello");
    printf("HGET word hello: %s \n", reply->str);

    reply = (redisReply*)redisCommand(c, "smembers whello");

    //返回类型 为 Arry
    for (size_t i = 0; i < reply->elements; i++) {
            printf("%zu) %s\n", i + 1, reply->element[i]->str);
        }

    freeReplyObject(reply);

    /* Disconnects and frees the context */
    redisFree(c);

    return 0;
}

