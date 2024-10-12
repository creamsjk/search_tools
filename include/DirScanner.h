/*************************************************************************
    > File Name: DirScanner.h
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 16时03分56秒
 ************************************************************************/

#ifndef  __DIRSCANNER_H_
#define  __DIRSCANNER_H_

#include <vector>
#include <string>

class DirScanner{ 

public:
    DirScanner();
    ~DirScanner();
    std::vector<std::string> & getFiles();//所有文件绝对路径 
    void traverse(std::string dir, std::string filetype); //读取目录下所有txt文件  filetype 是后缀名
private:
    std::vector<std::string> _files;
    
};



#endif
