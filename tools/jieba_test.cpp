/*************************************************************************
    > File Name: jieba_test.cpp
    > Author: sunrie
    > Mail: 1102490208@qq.com 
    > Created Time: 2024年10月11日 星期五 20时34分24秒
 ************************************************************************/

#include "./simhash/cppjieba/Jieba.hpp"
using namespace std;
const char* const DICT_PATH = "./dict/jieba.dict.utf8";
const char* const HMM_PATH = "./dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./dict/user.dict.utf8";
const char* const IDF_PATH = "./dict/idf.utf8";
const char* const STOP_WORD_PATH = "./dict/stop_words.utf8";

int main(int argc, char** argv) {
    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);//构造了一个jieba对象
    vector<string> words; //将用来存储每个单词
    /* string s = "这部专著的面世， 使“山重水复”的朱自清研究平添活力，步入“柳暗花明”的新境界。"; */
    string s = "hello,bro, i love you";
//    string s = "他来到了网易杭研大厦";
    jieba.Cut(s, words, true); //分词
    for(auto word:words){
        cout << "word = " << word << "\n";
    }
}

