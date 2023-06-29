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

namespace Path {
	std::wstring const emoji{};
	std::wstring const slang{};
	std::wstring const engToEng{};
	std::wstring const engToVie{};
	std::wstring const vieToEng{};
}

namespace Character {
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
	template <typename T> std::string encodeStr(std::string& s) {
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
	template <typename T, typename U> std::string decodeStr(T& str) {
		std::string result{};
		for (int i{ 0 }; i < str.length(); ++i) {
			result += load<U>(str[i]);
		}
		return result;
	}

	void stringToWString(std::string& str);

	void stringTou16String(std::string& str);

	void stringTou32String(std::string& str);
}

namespace Dataset {
	extern std::wstring curDataSet;

	struct Trie {

		struct Node {
			bool key[16]{};
			Node* children[16];
			int exist{-1};
			int cnt{};
			Node() {
				for (int i{ 0 }; i < 16; ++i) {
					key[i] = 0;
					children[i] = nullptr;
				}
			}
		};
		Node* trueRoot{};
		Trie() {
			trueRoot = new Node;
		};

		void insert(std::string& word, int pos);
		Node* search(std::string& word);
		bool remove(Node* root, std::string& word, int n);
		void remove(std::string& word);
		void displayTree(Node* root, std::string& word, std::vector<std::string>& ans);
		void displayTree(Node* root, std::string& word, int& num, std::vector<std::string>& ans);
		std::vector<std::string> displayTree(std::string& word);
		std::vector<std::string> displayTree(std::string& word, int num);
		void deleteTree(Node* root);
		~Trie() {
			deleteTree(trueRoot);
		}
	};



	void switchDataSet(int n);
	void loadDataSet(Trie* root);
	std::string definition(Trie* root, std::string& word);
	void inputNewWord(Trie* root, std::string& word, std::string& definition);
}
#endif