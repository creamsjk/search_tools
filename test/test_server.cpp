#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

// 回调函数，用于捕获调试信息
static int debug_callback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr)
{
    (void)handle; // 忽略未使用的参数
    (void)userptr;

    if(type == CURLINFO_HEADER_OUT) {
        printf("==> Sent Header:\n%s\n", data);
    }
    return 0;
}

int main(void)
{
    CURL *curl;
    CURLcode res;

    // 初始化 libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        // 设置请求的 URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");

        // 自定义请求头
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Custom-Header: CustomValue");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 启用查看响应头
        /* curl_easy_setopt(curl, CURLOPT_HEADER, 1L); */

        // 启用详细信息输出
        /* curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); */

        // 设置调试回调函数
        /* curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, debug_callback); */
        /* curl_easy_setopt(curl, CURLOPT_DEBUGDATA, NULL); */

        // 执行请求
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // 清理资源
        curl_slist_free_all(headers); // 释放自定义请求头
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}

