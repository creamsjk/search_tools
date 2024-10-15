/*************************************************************************
    > File Name: server.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月15日 星期二 11时27分40秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main(){ 

    string a = "1\r\n张三 王五\r\n<html>asdasdasa</html>\r\n";                          
                  
                  
    /* string status = _msg.substr(0, _msg.find( "\r\n")); */
    /* string  status_id = status.substr(0, status.find('\r')); */
    /* cout<<"status_id: " << status_id << endl; */
    /* cout<<"status " << status << endl; */
                  
    string status = a.substr(0, a.find( "\r\n"));
    string  status_id = status.substr(0, status.find('\r'));
                  
    cout<<"a: " << a << endl;
    cout<<"status_id: " << status_id << endl;
                 
    string b = a.substr(a.find("\r\n") + 2);
    string message_keys = b.substr(0, b.find("\r\n"));
    cout<<"b: " << b << endl;
    cout<<"message_keys: " << message_keys<< endl;
                  
    string c = b.substr(b.find("\r\n") + 2);
    string body_html = c.substr(0 ,c.find("\r\n"));
    cout<<"c: " << c << endl;
    cout << "body_html: " << body_html << endl;


    return 0;
}

