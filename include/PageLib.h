/*************************************************************************
    > File Name: PageLib.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 17时39分36秒
 ************************************************************************/

#ifndef  __PAGELIB_H_
#define  __PAGELIB_H_

#include "DirScanner.h"
#include "XmlRss.h"

#include <vector>
#include <string>
#include <map>

class PageLib{ 

public:
    PageLib(std::string sourcefilepath); //源路径  或取走路径下面的所有xml文件
    void create(std::string filepath);// 创建网页库
    void store(std::string filepath); //存储网页库位置和偏移

private:
    DirScanner _rdirScanner; //目录扫描对象
    std::vector<std::string> _pages; //存放格式化后网页
    std::map<int, std::pair<int, int>> _offsetLib; //存放每篇文章在网页库的位置信息
    std::string _filepath; //存放xml文件的位置
    

};


#endif
