/*************************************************************************
    > File Name: DirScanner.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月12日 星期六 16时08分56秒
 ************************************************************************/

#include "../include/DirScanner.h"

#include <iostream>

#include <sys/types.h>
#include <dirent.h>


DirScanner::DirScanner(){ 

};

DirScanner::~DirScanner(){ 

};


//递归扫描
void DirScanner::traverse(std::string dir, std::string filetype){ 

   DIR * myDir =  opendir(dir.c_str());
   if(myDir == NULL){ 

       std::cout << "DirScanner::traverse open dir failde \n";
       exit(-1);
   }

   long loc = telldir(myDir);
   struct dirent * pdirent;
   while(1){ 

       long tmploc = telldir(myDir);
       pdirent = readdir(myDir);

       if(pdirent ==  NULL)
           break;

       std::string s = pdirent->d_name;
       /* std::cout << s.substr(s.find('.') + 1) << "\n"; */
       //注意 ..  .  两个目录
       if(pdirent->d_type == DT_DIR && s != "." && s != ".."){ 

           this->traverse(dir + s + "/", filetype);

       }else if(s.substr(s.find('.') + 1) == filetype){ 

           std::string pathTmp = dir + s;
           this->_files.push_back(pathTmp);
       }
   }

   closedir(myDir);

}

std::vector<std::string>& DirScanner::getFiles(){ 

    return this->_files;
}
