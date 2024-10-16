/*************************************************************************
    > File Name: SplitTool.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 20时53分03秒
 ************************************************************************/

#include "../include/SplitTool.h"

#define LOGGER_LEVEL LL_WARE

using std::vector;
using std::string;

const char* const DICT_PATH = "../tools/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../tools/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../tools/dict/user.dict.utf8";                                                       
const char* const IDF_PATH = "../tools/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../tools/dict/stop_words.utf8";


//初始化结巴 和 simasher
SplitTool::SplitTool() :jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH),
                         simasher(DICT_PATH, HMM_PATH, IDF_PATH, STOP_WORD_PATH)
{ 

}

SplitTool::~SplitTool(){ 

}

//分词
std::vector<std::string> SplitTool::cut( std::string s){ 


    std::vector<std::string> words;
    this->jieba.Cut(s, words, true);

    /* std::cout << words.size() << "\n"; */
    /* for(auto &a: words) */
    /*     std::cout << a << "\n"; */

    return words;

};

//获取指纹 topn
//默认为5
uint64_t SplitTool::getFignerPrint(std::string message, int topN){ 

    /* std::cout << "message=" << message << "\n"; */
    uint64_t u64 = 0;
    simasher.make(message, topN, u64);
    
    return u64;
};

//返回 指纹对比结果
//相等为1  不等为0
bool SplitTool::isEqual(uint64_t left, uint64_t right){ 

    return simhash::Simhasher::isEqual(left, right);
}

//将词分成一个个的
std::vector<std::string> SplitTool::cutOne(std::string s){ 

    vector<string> res = this->withoutChineseWorld(s);

    return res;
    
}

std::vector<std::string> SplitTool::withoutChineseWorld(const std::string &source){ 

   vector<string> res;
    /* std::cout << source << "\n"; */
    for(size_t i = 0; i < source.size(); ){

        int n = nBytesCodes(source[i]);

        if(n <4)
            res.push_back(source.substr(i, i + n));

        i += n;
    }

    return res;

}

size_t SplitTool::nBytesCodes(const char ch){ 

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



