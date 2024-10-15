/*************************************************************************
    > File Name: DictProducer.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 21时14分07秒
 ************************************************************************/

#include "DictProducer.h"
#include <fstream>
#include <sstream>
#include <codecvt>

using std::vector;
using std::string;
using std::unordered_map;
using std::map;
using std::set;

const string stop_en = "../messgae/yuliao/stop_words_eng.txt";
const string stop_cn = "../messgae/yuliao/stop_words_zh.txt";


DictProducer::DictProducer(string tool, SplitTool * sp) :_cuttor(sp){ 

    //初始化_index 英文部分
    for(int i = 0; i < 26; ++i){ 
        std::string s(1,'a'+i);
        this->_index[s];
    }
    
    
    DirScanner dir;
    dir.traverse(tool, "txt");
    this->_pathfile = dir.getFiles();

    /* for(auto s: this->_pathfile) */
    /*     std::cout << s << "\n"; */

    for(auto &s: this->_pathfile){ 

    std::ifstream ifs(s);
    /* std::cout << s << " \n"; */

    if(!ifs.good()){ 

        std::cout << "DictProducer:: open file  \n";
        exit(-1);

    }
    
    // 将文件中的每一行都读入到_files中
    string res_message;
    string tmp;
    while(std::getline(ifs,tmp, '\r')){ 
        res_message.append(tmp);
    }
       this->_files.push_back(res_message);
       /* std::cout << res_message << "\n"; */

       ifs.close();
    }

    if(this->_cuttor == nullptr){ 

        std::cout << "SplitTool is  nullptr \n";
        exit(-1);
    }


    /* for(auto s: this->_files) */
    /*     std::cout << s << "\n"; */




/*     std::ifstream ifs(tool); */

/*     // 将文件中的每一行都读入到_files中 */
/*     string tmp; */
/*     while(std::getline(ifs,tmp, '\n')){ */ 
/*         this->_files.push_back(tmp); */
/*     } */

/*     if(this->_cuttor == nullptr){ */ 

/*         std::cout << "SplitTool is  nullptr \n"; */
/*         exit(-1); */
/*     } */

}

DictProducer::~DictProducer(){ 


}

//good  英语分词
void DictProducer::buildEnDict(){ 

    //清洗 所有大写字母消除  符号消除
    
    for(auto &s : this->_files){ 
        for(char &c: s){ 

            if(c >= 'A' && c <= 'Z')
                c += 32;
            else if(c < 'a' || c > 'z' )
                c = ' ';
        }
    }

    std::ifstream ifs(stop_en);
    if(!ifs.good()){ 

        std::cout << "DictProducer::buildEnDict  open stop_cn failed \n";
        exit(-1);
    }

    //停用词
    set<string> stop;
    string stop_world;
    while(std::getline(ifs, stop_world, '\n')){ 

        /* //消除掉 \r  中文文档是以 \r\n结尾的话 */
        if(stop_world.find('\r'))
            stop_world.erase(stop_world.size()-1);
        stop.insert(stop_world);
        /* std::cout << stop_world  << " \n"; */
    }

    ifs.close();


    //分词 and  索引
    for(size_t i = 0; i < this->_files.size(); ++i){ 

        string s = this->_files[i];
        vector<string> words = this->_cuttor->cut(s);
        for(const string &t : words){ 

            //空格不参与分词
            if(t == " ")
                continue;
            else if(stop.find(t) != stop.end()){ 

                this->_dict[t]++;
            }
            /* this->_index[t].insert(i); */
        }
    }

    /* //打印测试 */
    /* for(auto &s : this->_files){ */ 
    /*     std::cout << s << "\n"; */
    /* } */

    /* //_dict */
    /* std::cout << "\n_dict \n"; */

    /* for(auto &s : this->_dict){ */ 
    /*     std::cout << "first: " << s.first << "  second: " << s.second << "\n"; */
    /* } */

    
    /* std::cout << " \n _index \n"; */

    /* for(auto &s : this->_index){ */ 
    /*     std::cout << "first: " << s.first ; */
    /*     for(auto i: s.second) */
    /*         std::cout << "  " <<  i; */
    /*     std::cout << " \n"; */
    /* } */


}

void DictProducer::buildCnDict(){ 

 //清洗 所有\r\n 消除
    
    for(auto &s : this->_files){ 
        for(char &c: s){ 

            if(c == '\r' || c == '\n' || c == '.' || c == '?' || c == '!' ||  c == ',' )
                c = ' ';
        }
    }

    std::ifstream ifs(stop_cn);
    if(!ifs.good()){ 

        std::cout << "DictProducer::buildCnDict  open stop_cn failed \n";
        exit(-1);
    }

    //停用词
    set<string> stop;
    string stop_world;
    while(std::getline(ifs, stop_world, '\n')){ 

        //消除掉 \r  中文文档是以 \r\n结尾的话
        if(stop_world.find('\r'))
            stop_world.erase(stop_world.size()-1);
        stop.insert(stop_world);
        /* std::cout << stop_world  << " \n"; */
    }



    //分词 and  索引
    for(size_t i = 0; i < this->_files.size(); ++i){ 

        string s = this->_files[i];
        vector<string> words = this->_cuttor->cut(s);
        for(const string &t : words){ 

            //空格不参与分词
            if(t == " ")
                continue;
            else if(stop.find(t) == stop.end()){ 

                this->_dict[t]++;
            }
            /* this->_index[t].insert(i); */
        }
    }

    /* //打印测试 */
    /* for(auto &s : this->_files){ */ 
    /*     std::cout << s << "\n"; */
    /* } */

    /* //_dict */
    /* std::cout << "\n_dict \n"; */

    /* for(auto &s : this->_dict){ */ 
    /*     std::cout << "first: " << s.first << "  second: " << s.second << "\n"; */
    /* } */

    
    /* std::cout << " \n _index \n"; */

    /* for(auto &s : this->_index){ */ 
    /*     std::cout << "first: " << s.first ; */
    /*     for(auto i: s.second) */
    /*         std::cout << "  " <<  i; */
    /*     std::cout << " \n"; */
    /* } */


}

//将字典存到 ../data/dict.dat  文件内
void DictProducer::createIndex(){ 



    //先把中文字存起来
    set<string> chinese_one_wordl;
    for(auto &i : this->_dict){ 

        //将每个词分成单字 但是存在不是单字的词 还需要再分一次
        vector<string> tmp = withoutChineseWorld(i.first);

        //tmp里面大于4的代表不是单字 继续分 再加入tmp
        for(auto &j: tmp){ 
            if(j.size() >= 4){ 
                vector<string> tmp_two = withoutChineseWorld(j);
                for(auto l: tmp_two)
                    tmp.push_back(l);
            }
        }

        for(auto &j : tmp){ 
            if(j.size() < 4)
                chinese_one_wordl.insert(j);
        }
    }
    
    //现在中英文下标都存好了  分词成功 现在是一个个单个字
    //给单字插入 -1 可以后面消除  -1数组并不存在
    for(auto &i: chinese_one_wordl)
        this->_index[i];


    for(auto &i: this->_dict)
        this->_res_index.push_back(i.first);


        //遍历所有 存词的_res_index
        for(size_t l = 0; l <= this->_res_index.size(); ++l){ 

            vector<string> tmp = withoutChineseWorld(this->_res_index[l]);
            //tmp里面大于4的代表不是单字 继续分 再加入tmp
            for(auto &j: tmp){ 
                if(j.size() >= 4){ 
                    vector<string> tmp_two = withoutChineseWorld(j);
                    for(auto l: tmp_two)
                        tmp.push_back(l);
                }
            }

            
            /* for(auto &j: tmp) */
            /*     std::cout << " " << j ; */
            /* std::cout << "\n\n"; */

            
            /* //从拆分的单字中找到一样的说明 原本的文本含有这个 将_res_index  下标 传入_index set内 */
           for(auto &j:tmp){ 
                   
                   if(this->_index.find(j) != this->_index.end())
                       _index[j].insert(l);
           }
        }

/*         for(auto &jj: this->_dict) */
/*             std::cout << jj.first << "  " << jj.second << " \n"; */

/*         std::cout << " \n"; */
/*         std::cout << " \n"; */

     
/*     std::cout << " \n _index \n"; */

/*     for(auto &s : this->_index){ */ 
/*         std::cout << "first: " << s.first ; */
/*         for(auto &i: s.second) */
/*             std::cout << "  " <<  i; */
/*         std::cout << " \n"; */
/*     } */
/*         std::cout << " \n"; */
/*         std::cout << " \n"; */

/*     for(size_t ff = 0; ff < this->_res_index.size();  ++ff) */
/*         std::cout << ff << "  " << this->_res_index[ff] << "\n"; */

        //词典成功  中英文混合词典

}

//succes 存储到指定路径 必须是绝对路径 //file path 是查找文件的路径  还有有存储的词典
void DictProducer::store(string  filepath , string  dictPath){ 

    std::ofstream ofs(filepath);
    if(!ofs.good()){ 

        std::cout << "DictProducer::store open failed \n";
        exit(-1);
    }
    string res;
    for(auto &s : this->_index){ 
        string tmp;
        tmp.append(s.first);
        for(auto i: s.second)
            /* std::cout << "  " <<  i; */
            tmp.append(" ").append(std::to_string(i));
        tmp.append("\n");
        res.append(tmp);
    }

    ofs << res;

    ofs.close();


    std::ofstream ofs_dict(dictPath);
    if(!ofs.good()){ 

        std::cout << "DictProducer::store open failed \n";
        exit(-1);
    }

    for(auto &s: this->_dict){ 

        ofs_dict << s.first << " " << s.second << "\n";
    }


    ofs_dict.close();



}






//中文分字
vector<string> DictProducer::withoutChineseWorld(const string &source){ 
   
    vector<string> res;
    /* std::cout << source << "\n"; */
    for(size_t i = 0; i < source.size(); ){ 

        int n = nBytesCodes(source[i]);
        
        res.push_back(source.substr(i, i + n));

        i += n;
    }

    /* for(auto &i : res) */
    /*     std::cout << "  " << i; */
    /* std::cout <<"\n\n"; */

    //res 内容并不是每个都是单字
    return res;

}








size_t DictProducer::nBytesCodes(const char ch){ 

    if(ch & (1 << 7)){ 

        int nBytes = 1;
        for(int idx = 0; idx != 6; ++idx){ 

            if(ch & (1 << (6 - idx))){ 

                ++nBytes;
            }else{ 
                break;
            }
        }
         return nBytes;

    }

    return 1;

}









