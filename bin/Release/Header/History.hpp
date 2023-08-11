#ifndef HISTORY_HPP
#define HISTORY_HPP
#include <vector>
#include <string>
using namespace std;

vector<std::string> loadHistory(std::string& word,bool& exist);
bool saveWordToTextFile(std::string& word);
vector<std::string> SearchHistory();
bool deleteSearchHistory();
bool deleteWordInHistory(std::string& word);

#endif
