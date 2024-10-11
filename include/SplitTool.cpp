/*************************************************************************
    > File Name: SplitTool.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 20时53分03秒
 ************************************************************************/

#include "../include/SplitTool.h"


const char* const DICT_PATH = "../tools/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../tools/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../tools/dict/user.dict.utf8";                                                       
const char* const IDF_PATH = "../tools/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../tools/dict/stop_words.utf8";


//初始化结巴
SplitTool::SplitTool() :jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH)
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

