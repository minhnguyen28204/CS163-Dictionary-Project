#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Trie.hpp"

template <typename T> int position(std::vector<T> nums, T key) {
	int b{ 0 }, e{ static_cast<int>(nums.size()) - 1 };
	while (b <= e) {
		int mid = b + (e - b) / 2;
		if (nums[mid] == key)
			return mid;
		if (nums[mid] > key)
			e = mid - 1;
		else b = mid + 1;
	}
	return nums.size();
}

void Dataset::Trie::insert(std::wstring word, int pos) {
	Node* cur = trueRoot;
	for (int j{ 0 }; j < word.length(); ++j) {
		cur->cnt++;
		int i{ position<wchar_t>(cur->key, word[j]) };
		if (i == cur->key.size()) {
			cur->key.push_back(word[j]);
			int r{ i - 1};
			Node* tmp;
			tmp = new Node;
			cur->children.push_back(tmp);
			for (; r >= 0 && cur->key[r] > word[j]; --r) {
				cur->key[r + 1] = cur->key[r];
				cur->children[r + 1] = cur->children[r];
			}
			cur->key[r + 1] = word[j];
			cur->children[r + 1] = tmp;
			cur = tmp;
		}
		else {
			cur = cur->children[i];
		}

	}
	cur->exist = pos;
	return;
}

Dataset::Trie::Node* Dataset::Trie::search(std::wstring word) {
	Node* cur = trueRoot;
	for (int n{ 0 }; n < word.length(); ++n) {
		int i{ position<wchar_t>(cur->key, word[n]) };
		if (i == cur->key.size())
			return nullptr;
		cur = cur->children[i];
	}
	return cur;
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
	int i{ position<wchar_t>(root->key, word[n]) };
	root->cnt--;
	if (i == root->key.size())
		return false;
	if (remove(root->children[i], word, n + 1)) {
		if (root->children.size() <= 1) {
			delete root;
			return true;
		}
		else {
			root->key.erase(root->key.begin() + i);
			root->children.erase(root->children.begin() + i);
		}
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
	Node* cur{ search(word) };
	if (!cur)
		return;
	displayTree(cur, word);
}

void Dataset::Trie::displayTree(std::wstring word, int num) {
	Node* cur{ search(word) };
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
		root->insert(input, size);
		delete[] word;
	}
	fwout.close();
	fcout.close();
}

std::wstring Dataset::definition(Trie* root, std::wstring word) {
	Trie::Node* tmp{ root->search(word) };
	if (!tmp || tmp->exist == 0) {
		std::wstring str{};
		return str;
	}
	std::wifstream fin(curDataSet + L"Definition", std::ios::binary | std::ios::in);
	fin.seekg(std::ios::beg, tmp->exist);
	int size{};
	fin.read((wchar_t*)&size, sizeof(int) / 2);
	wchar_t* result = new wchar_t[size];
	fin.read(result, size / 2);
	std::wstring str{ result };
	delete[] result;
	fin.close();
	return str;
}