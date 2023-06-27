#ifndef TRIE_HPP
#define TRIE_HPP

namespace Path {
	std::wstring const emoji{};
	std::wstring const slang{};
	std::wstring const engToEng{};
	std::wstring const engToVie{};
	std::wstring const vieToEng{};
}
namespace Dataset {
	struct Trie {
		struct Node {
			std::vector<wchar_t> key{};
			std::vector<Node*> children{};
			int exist{};
			int cnt{};
		};
		Node* trueRoot{};
		Trie() {
			trueRoot = new Node;
		}
		void insert(std::wstring word, int pos);
		Node* search(std::wstring word);
		bool remove(Node* root, std::wstring word, int n);
		void displayTree(Node* root, std::wstring& word);
		void displayTree(Node* root, std::wstring& word, int& num);
		void displayTree(std::wstring word);
		void displayTree(std::wstring, int num);
		void deleteTree(Node* root);
		~Trie() {
			deleteTree(trueRoot);
		}
	};



	inline std::wstring curDataSet{};
	void loadDataSet(Trie* root);
	void switchDataSet(int n);
	std::wstring definition(Trie* root, std::wstring word);
	void inputNewWord(Trie* root, std::wstring& word, std::wstring& definition);
}



#endif