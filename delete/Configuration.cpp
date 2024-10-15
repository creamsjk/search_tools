/*************************************************************************
    > File Name: Configuration.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 10时09分33秒

    success
 ************************************************************************/

#include "../include/Configuration.h"
#include <fstream>
#include <iostream>


Configuration::Configuration(){ 


}

Configuration::~Configuration(){ 

    if(instance)
        delete instance;

}

//静态元素 要在类外初始化
Configuration * Configuration::instance = nullptr;

 Configuration * Configuration::getInstance(){ 
    
     if(instance == nullptr)
         instance = new Configuration();

     return instance;
 }

void Configuration::readConfigur(const std::string & configureFile){ 

    //将配置文件读进来
    this->_configFilePath.append(configureFile);
}

std::map<std::string, std::string>&  Configuration::getConfigMap(){ 


    std::ifstream ifs(this->_configFilePath);
    //判断是否可以读取文件
    if(!ifs.good()){ 

        std::cout<< " Configuration open failed \n";
    }

    std::string tmp;
    // conf格式:port 9999\n
    while(std::getline(ifs, tmp, '\n')){ 

        std::string key = tmp.substr(0, tmp.find(" "));
        std::string value = tmp.substr(tmp.find(" ") + 1);
        this->_configs[key] = value;
    }

    return this->_configs;
}















