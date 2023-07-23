#ifndef FAVOURITElIST_HPP
#define FAVOURITELIST_HPP
#include<vector>
#include<string>
#include<fstream>
#include <stdio.h>
using namespace std;

bool addWordToFavList(std::string& word);
bool removeWordFromFavList(std::string& word);
vector<string> favouriteList();

#endif