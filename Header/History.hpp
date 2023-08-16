#ifndef HISTORY_HPP
#define HISTORY_HPP
#include <vector>
#include <string>
#include "Trie.hpp"
using namespace std;

namespace history {
	extern std::string pathEmoji;
	extern std::string pathSlang;
	extern std::string pathEngToEng;
	extern std::string pathEngToVie;
	extern std::string pathVieToEng;
	extern std::vector<std::string> mode;
}

void setPath();
vector<std::string> loadHistory(std::string& word,bool& exist);
bool saveWordToTextFile(std::string& word);
vector<std::string> SearchHistory();
bool deleteSearchHistory();
bool deleteWordInHistory(std::string& word);

#endif

