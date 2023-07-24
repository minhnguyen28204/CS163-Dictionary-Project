#ifndef TRIE_HPP
#define TRIE_HPP
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <codecvt>
#include <iomanip>
#include <chrono>
#include <stack>

namespace Path {
	extern int curPath;
	extern std::vector<std::string> path;
	void loadPath(int n = 0);
}

int getLength(std::wstring ws);
int getLength(std::u16string ws);
int getLength(std::u32string ws);

template <typename T = int> int position(std::vector<T> nums, T key) {
	int b{ 0 }, e{ static_cast<int>(nums.size()) - 1 };
	while (b <= e) {
		int mid = b + (e - b) / 2;
		if (nums[mid] == key)
			return mid;
		if (nums[mid] > key)
			e = mid - 1;
		else b = mid + 1;
	}
	return -1;
}

namespace Character {
	extern char wordSplit[];
	
	// Change a unicode character into hex form with proper length
	template <typename T> std::string load(T ch) {
		std::ostringstream fout{};
		fout.setf(fout.hex, fout.basefield);
		fout.setf(fout.right, fout.adjustfield);
		fout.fill('0');
		fout << std::setw(sizeof(T) * 2) << ch;
		return fout.str();
	}

	template <typename T> std::string cpp11_codepoint_to_utf8(T cp) // C++11 Sandard
	{
		char utf8[4];
		char* end_of_utf8;

		T const* from = &cp;

		std::mbstate_t mbs;
		std::codecvt_utf8<T> ccv;

		if (ccv.out(mbs, from, from + 1, from, utf8, utf8 + 4, end_of_utf8))
			throw std::runtime_error("bad conversion");

		return { utf8, end_of_utf8 };
	}

	//Change a string in hex form back as unicode characters
	template <typename T> std::string encodeStr(std::string s) {
		std::string result{};
		for (int i{ 0 }; i < s.length() / (sizeof(T) * 2); ++i) {
			std::string tmp{};
			for (int j = 0; j < sizeof(T) * 2; ++j)
				tmp.push_back(s[j + i * sizeof(T) * 2]);
			T u32 = std::stoul(tmp, 0, 16);
			tmp = cpp11_codepoint_to_utf8<T>(u32);
			result += tmp;
		}
		return result;
	}

	//Change a string of unicode characters into hex form
	template <typename T = std::wstring, typename U = wchar_t> std::string decodeStr(T str, U ch) {
		std::string result{};
		int l = getLength(str);
		for (int i{ 0 }; i < l; ++i) {
			result += load<U>(str[i]);
		}
		return result;
	}

	std::wstring stringToWString(std::string str);

	std::u16string stringTou16String(std::string str);

	std::u32string stringTou32String(std::string str);

	std::string backToString(std::wstring& str);
	std::string backToString(std::u16string& str);
	std::string backToString(std::u32string& str);

	template <typename T> bool wordBreaker(T ch) {
		for (int i{ 0 }; i < 16; ++i) {
			if (ch == static_cast<T>(wordSplit[i]))
				return true;
		}
		return false;
	}

	template <typename T = int> void mergeVector(std::vector<T>& origin, std::vector<T> addition) {
		if (origin.size() == 0) {
			origin = addition;
			return;
		}
		int i{ 0 };
		while(i < origin.size()) {
			if (position(addition, origin[i]) == -1) {
				origin.erase(origin.begin() + i);
			}
			else {
				i++;
			}
		}
	}
}

namespace DefinitionSet {
	struct Trie {
		struct Node {
			std::vector<int> wordNum{};
			Node* children[16];
			Node() {
				for (int i{ 0 }; i < 16; ++i)
					children[i] = nullptr;
			}
		};
		Node* trueRoot;
		Trie() {
			trueRoot = new Node;
		}

		void insert(std::string word, int wordNum);
		Node* search(std::string word);
		void deleteTree(Node*& root);
		void remove(std::string str, int n);
		void editDefinition(std::string newDefinition, int n);
		std::vector<int> allWordContain(std::string word);
		~Trie() {
			deleteTree(trueRoot);
		}

	};

	extern Trie* definitionTrie;

	void loadTrieFromString();
	std::vector<std::string> allWord(std::vector<int> nums);
	std::vector<std::string> displayTree();

	template <typename T = std::wstring, typename U = wchar_t> void splitLineToTrie(T& source, U ch, int n) {
		std::string output{};
		int i{ 0 };
		/*while (i < source.length() && source[i] != static_cast<U>(')'))
			i++;*/
		//i++;
		for (; i < source.length(); ++i) {
			if (!Character::wordBreaker<U>(source[i])) {
				output += Character::load<U>(source[i]);
			}
			else {
				if (output.length() != 0) {
					definitionTrie->insert(output, n);
				}
				output.clear();
			}
		}
		if (output.length() != 0) {
			definitionTrie->insert(output, n);
		}
	}

	template <typename T = std::wstring> void loadDefinitionSet(T definit, int n) {
		if (definit.length() == 0)
			return;
		splitLineToTrie(definit, definit[0], n);
	}

	template <typename T = std::wstring> void containField(T str) {
		std::string word{};
		if (getLength(str) != 0) {
			word = Character::decodeStr(str, str[0]);
		}
		return definitionTrie->allWordContain(word);
	}

	template <typename T = std::wstring, typename U = wchar_t> void splitToRemove(T& source, U ch, int n) {
		std::string output{};
		int i{ 0 };
		if (source[i] == '(')
			while (i < source.length() && source[i] != static_cast<U>(')'))
				i++;
		Trie::Node* tmp{};
		for (i++; i < source.length(); ++i) {
			if (!Character::wordBreaker<U>(source[i])) {
				output += Character::load<U>(source[i]);
			}
			else {
				if (output.length() != 0) {
					definitionTrie->remove(output, n);
				}
				output.clear();
			}
		}
		if (output.length() != 0) {
			definitionTrie->remove(output, n);
		}
	}

	template <typename T = std::wstring> void removeDefinition(T str, int n) {
		if (getLength(str) == 0)
			return;
		splitToRemove(str, str[0], n);
	}

	template <typename T = std::wstring, typename U = wchar_t> std::vector<int> searchWord(T& str, U ch) {
		std::string output{};
		std::vector<int> result{};
		for (int i{ 0 }; i < str.length(); ++i) {
			if (!Character::wordBreaker<U>(str[i])) {
				output += Character::load<U>(str[i]);
			}
			else {
				if (output.length() != 0) {
					Character::mergeVector(result, definitionTrie->allWordContain(output));
				}
				output.clear();
			}
		}
		if (output.length() != 0) {
			Character::mergeVector(result, definitionTrie->allWordContain(output));
		}
		return result;
	}

	template <typename T = std::wstring> std::vector<int> allWord(T str) {
		std::vector<int> result{};
		if (getLength(str) == 0)
			return result;
		result = searchWord(str, str[0]);
		return result;
	}

	template <typename T = std::wstring> std::vector<std::string> allDefinitionContain(T str) {
		return allWord(allWord(str));
	}
}

namespace WordSet {

	struct Trie {

		struct Node {
			Node* children[16];
			int exist{-1};
			int num{};
			Node() {
				for (int i{ 0 }; i < 16; ++i) {
					children[i] = nullptr;
				}
			}
		};
		Node* trueRoot{};
		Trie() {
			trueRoot = new Node;
		};

		void insert(std::string word, int pos, int n);
		Node* search(std::string word);
		void remove(std::string word);
		std::vector<std::string> displayTree(std::string word);
		std::vector<std::string> displayTree(std::string word, int num);
		void deleteTree(Node* root);
		~Trie() {
			deleteTree(trueRoot);
		}
	};

	void switchWordSet(int n);
	void loadWordSet();
	void loadNewData();
	void loadAllData();
	void loadWordCount();
	std::string definition(Trie::Node* root);
	std::string getWord(int n);
	std::string getOneWordFromBinFile(int n);
	std::string getOneWordFromTextFile(int n);
	void buildSerialFile();
	void loadTrieFromString();
	void reset();

	extern Trie* wordTrie;
	extern int wordOrigCount;
	extern int wordNewCount;

	template <typename T = std::wstring> void insert(T str, int pos, int n) {
		if (n < 0 || n > wordOrigCount + wordNewCount || getLength(str) == 0)
			return;
		wordTrie->insert(Character::decodeStr(str, str[0]), pos, n);
	}

	template <typename T = std::wstring> void remove(T str) {
		if (getLength(str) == 0)
			return;
		wordTrie->remove(Character::decodeStr(str, str[0]));
	}

	template <typename T = std::wstring> std::string definition(T str) {
		if (getLength(str) == 0)
			return "";
		Trie::Node* tmp = wordTrie->search(Character::decodeStr(str, str[0]));
		if (!tmp || tmp->exist == -1)
			return "";
		return definition(tmp);
	}

	template <typename T = std::wstring> std::vector<std::string> displayWordTree(T str, int num = -1) {
		std::string word{};
		if (getLength(str) != 0) {
			word = Character::decodeStr(str, str[0]);
		}
		if (num <= 0)
			return wordTrie->displayTree(word);
		return wordTrie->displayTree(word, num);
	}

	//Used for both adding a new word AND modify a word's definition
	template <typename T = std::wstring> void addNew(T word, T definition) {
		if (getLength(word) == 0 || getLength(definition) == 0)
			return;
		wordNewCount++;
		std::fstream fout(Path::path[Path::curPath] + "/New.txt", std::ios::ate | std::ios::in | std::ios::out);
		fout << '\n' << Character::backToString(word) << '\t';
		fout << Character::backToString(definition);
		fout.close();
		fout.open(Path::path[Path::curPath] + "/New.txt");
		fout << wordNewCount;
		fout.close();
		DefinitionSet::loadDefinitionSet(definition, wordOrigCount + wordNewCount - 1);
		insert(word, wordNewCount - 1, wordOrigCount + wordNewCount - 1);
	}

	template <typename T = std::wstring> void erase(T str) {
		if (getLength(str) == 0)
			return;
		wordNewCount++;
		std::fstream fout(Path::path[Path::curPath] + "/New.txt", std::ios::ate | std::ios::in | std::ios::out);
		fout << '\n' << Character::backToString(str) << '\t';
		fout.close();
		fout.open(Path::path[Path::curPath] + "/New.txt");
		fout << wordNewCount;
		fout.close();
		insert(str, -1, wordOrigCount + wordNewCount - 1);
	}

}

std::string randomWordFromFile();

#endif

