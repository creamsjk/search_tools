/*************************************************************************
    > File Name: Configuration.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 10时04分08秒
 ************************************************************************/

#ifndef  __CONGIGURATION_H_
#define  __CONGIGURATION_H_

#include <string>
#include <map>

//单例模式
class Configuration{ 

public:
    static Configuration * getInstance();
    std::map<std::string, std::string>  & getConfigMap();
    void readConfigur(const std::string & configureFile);


private:
    Configuration();
    ~Configuration();
    Configuration operator=(Configuration &) = delete ;;

private:
    std::string _configFilePath;
    std::map<std::string, std::string> _configs;
    /* static Configuration * instance; */
    static Configuration  * instance;

};







#endif


