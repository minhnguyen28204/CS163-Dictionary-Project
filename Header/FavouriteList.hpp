#ifndef FAVOURITElIST_HPP
#define FAVOURITELIST_HPP
#include<vector>
#include<string>
#include<fstream>
#include <stdio.h>
#include "Trie.hpp"
using namespace std;

extern std::string pathEmoji;
extern std::string pathSlang;
extern std::string pathEngToEng;
extern std::string pathEngToVie;
extern std::string pathVieToEng;
extern std::vector<std::string> mode;
extern std::string FolEmoji;
extern std::string FolSlang;
extern std::string FolEngToEng;
extern std::string FolEngToVie;
extern std::string FolVieToEng;
extern std::vector<std::string> folder;

bool addWordToFavList(std::string& word);
bool removeWordFromFavList(std::string& word);
vector<string> favouriteList();

#endif
