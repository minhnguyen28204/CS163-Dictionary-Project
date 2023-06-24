#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Trie.hpp"

void Dataset::Trie::insert(Node* root, std::wstring word, int n, int pos) {
	if (n == word.size()) {
		root->exist = pos;
		return;
	}
	root->cnt++;
	int i{ 0 };
	for (; i < root->key.size() && root->key[i] != word[n]; ++i);
	if (i == root->key.size()) {
		root->key.push_back(word[n]);
		int j{ i - 1 };
		Node* tmp;
		tmp = new Node;
		root->children.push_back(tmp);
		for (; j >= 0 && root->key[j] > word[n]; --j) {
			root->key[j + 1] = root->key[j];
			root->children[j + 1] = root->children[j];
		}
		root->key[j + 1] = word[n];
		root->children[j + 1] = tmp;
		insert(tmp, word, n + 1, pos);
	}
	else {
		insert(root->children[i], word, n + 1, pos);
	}
}

Dataset::Trie::Node* Dataset::Trie::search(Node* root, std::wstring word, int n) {
	if (n == word.size()) {
		return (root->exist != 0) ? root : nullptr;
	}
	int i{ 0 };
	for (; i < root->key.size() && root->key[i] != word[n]; ++i);
	if (i == root->key.size())
		return nullptr;
	return search(root->children[i], word, n + 1);
}

bool Dataset::Trie::remove(Node* root, std::wstring word, int n) {
	if (n == word.size()) {
		root->exist = 0;
		if (root->children.size() == 0) {
			delete root;
			return true;
		}
		return false;
	}
	int i{ 0 };
	for (; i < root->key.size() && root->key[i] != word[n]; ++i);
	if (i == root->key.size())
		return false;
	if (remove(root->children[i], word, n + 1) && root->children.size() <= 1) {
		delete root;
		return true;
	}
	return false;
}

void Dataset::Trie::displayTree(Node* root, std::wstring& word) {
	if (root->exist != 0) {
		std::wcout << word << '\n';
	}
	for (int i{ 0 }; i < root->children.size(); ++i) {
		word.push_back(root->key[i]);
		displayTree(root->children[i], word);
		word.pop_back();
	}
}

void Dataset::Trie::displayTree(Node* root, std::wstring& word, int& num) {
	if (num == 0)
		return;
	if (root->exist != 0) {
		std::wcout << word << '\n';
		num--;
	}
	for (int i{ 0 }; i < root->children.size(); ++i) {
		word.push_back(root->key[i]);
		displayTree(root->children[i], word, num);
		word.pop_back();
	}
}

void Dataset::Trie::displayTree(std::wstring word) {
	Node* cur{ search(trueRoot, word, 0) };
	if (!cur)
		return;
	displayTree(cur, word);
}

void Dataset::Trie::displayTree(std::wstring word, int num) {
	Node* cur{ search(trueRoot, word, 0) };
	if (!cur)
		return;
	displayTree(cur, word, num);
}

void Dataset::Trie::deleteTree(Node* root) {
	for (int i{ 0 }; i < root->children.size(); ++i) {
		deleteTree(root->children[i]);
	}
	root = nullptr;
}

void Dataset::switchDataSet(int n) {
	switch (n) {
	case 1:
		Dataset::curDataSet = Path::emoji;
		break;
	case 2:
		Dataset::curDataSet = Path::slang;
		break;
	case 3:
		Dataset::curDataSet = Path::engToEng;
		break;
	case 4:
		Dataset::curDataSet = Path::engToVie;
		break;
	case 5:
		Dataset::curDataSet = Path::vieToEng;
	}
}

void Dataset::loadDataSet(Trie* root) {
	std::wifstream fwout(curDataSet + L"/Words.bin", std::ios::binary | std::ios::in);
	std::ifstream fcout(curDataSet + L"/WordsColumn.bin", std::ios::binary | std::ios::in);
	int n{};
	fcout.read((char*)&n, sizeof(int));
	int curLen{};
	for (int i{ 0 }; i < n; ++i) {
		int size{};
		fcout.read((char*)&size, sizeof(int));
		wchar_t* word = new wchar_t[size - curLen];
		fwout.read((wchar_t*)word, (size - curLen) / 2);
		std::wstring input{ word };
		curLen = size + sizeof(int);
		fwout.read((wchar_t*)&size, sizeof(int) / 2);
		root->insert(root->trueRoot, input, 0, size);
		delete[] word;
	}
	fwout.close();
	fcout.close();
}
