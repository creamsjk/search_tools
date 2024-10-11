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

DictProducer::DictProducer(string tool, SplitTool * sp) :_cuttor(sp){ 

    std::ifstream ifs(tool);

    // 将文件中的每一行都读入到_files中
    string tmp;
    while(std::getline(ifs,tmp, '\n')){ 
        this->_files.push_back(tmp);
    }

    if(this->_cuttor == nullptr){ 

        std::cout << "SplitTool is  nullptr \n";
        exit(-1);
    }

}

DictProducer::~DictProducer(){ 


}

//good
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

    //分词 and  索引
    for(size_t i = 0; i < this->_files.size(); ++i){ 

        string s = this->_files[i];
        vector<string> words = this->_cuttor->cut(s);
        for(const string &t : words){ 

            //空格不参与分词
            if(t == " ")
                continue;
            this->_dict[t]++;
            this->_index[t].insert(i);
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
    /* for(auto &s : this->_files){ */ 

    /*     string tmp = withoutSymbol(s); */
    /*     std::cout << tmp << "\n"; */
    /*     s = tmp; */

    /* } */
    
    for(auto &s : this->_files){ 
        for(char &c: s){ 

            if(c == '\r' || c == '\n' )
                c = ' ';
        }
    }

    //分词 and  索引
    for(size_t i = 0; i < this->_files.size(); ++i){ 

        string s = this->_files[i];
        vector<string> words = this->_cuttor->cut(s);
        for(const string &t : words){ 

            //空格不参与分词
            if(t == " ")
                continue;
            this->_dict[t]++;
            this->_index[t].insert(i);
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


    std::ofstream ofs("../data/dict.dat");
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

}






//去除中文中标点符号 失败
string DictProducer::withoutSymbol(const string &source){ 
    
    string s(source);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

    std::wstring ws = conv.from_bytes(s);
    std::wstring nws;

    for(wchar_t ch : ws){ 

        if(!iswpunct(ch) && !iswspace(ch))
            nws.push_back(ch);
    }

    string res = conv.to_bytes(nws);

    return res;



}
















