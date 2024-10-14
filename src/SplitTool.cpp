/*************************************************************************
    > File Name: SplitTool.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 20时53分03秒
 ************************************************************************/

#include "../include/SplitTool.h"

#define LOGGER_LEVEL LL_WARE


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




