/*************************************************************************
    > File Name: test_curl.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月14日 星期一 23时46分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <curl/curl.h>
#define true 1
#define false 0
/* typedef unsigned int bool; */
bool getUrl(char *filename)
{
        CURL *curl;
        CURLcode res;
        FILE *fp;
        if ((fp = fopen(filename, "w")) == NULL)  // 返回结果用文件存储
                return false;
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: Agent-007");
        curl = curl_easy_init();    // 初始化
        if (curl)
        {
                //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");// 代理
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);// 改协议头
                curl_easy_setopt(curl, CURLOPT_URL,"http://www.baidu.com");
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); //将返回的http头输出到fp指向的文件
                curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp); //将返回的html主体数据输出到fp指向的文件
                res = curl_easy_perform(curl);   // 执行
                if (res != 0) {

                        curl_slist_free_all(headers);
                        curl_easy_cleanup(curl);
                }
                fclose(fp);
                return true;
        }
}
int main(void)
{
        getUrl("./abc.html");
}

