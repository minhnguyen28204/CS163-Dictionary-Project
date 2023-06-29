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

//All str of Character namespace below store wide chars.

void Character::stringToWString(std::string& str) {
	std::wstring_convert< std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring str2 = converter.from_bytes(str);
	str = decodeStr<std::wstring, wchar_t>(str2);
}

void Character::stringTou16String(std::string& str) {
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	std::u16string str2 = converter.from_bytes(str);
	str = decodeStr<std::u16string, char16_t>(str2);
}

void Character::stringTou32String(std::string& str) {
	std::wstring_convert<std::codecvt<char32_t, char, std::mbstate_t>, char32_t> converter;
	std::u32string str2 = converter.from_bytes(str);
	str = decodeStr<std::u32string, char32_t>(str2);
}

int hexa(int x) {
	if ('0' <= x && x <= '9')
		return x - '0';
	return x - 'a' + 10;
}
// All word in Trie store hex char
void Dataset::Trie::insert(std::string& word, int pos) {
	Node* cur = trueRoot;
	for (int i{ 0 }; i < word.length(); ++i) {
		cur->cnt++;
		int x{ hexa(word[i])};
		if (!cur->key[x]) {
			cur->key[x] = 0;
			cur->children[x] = new Node;
			cur = cur->children[x];
		}
		else {
			cur = cur->children[x];
		}

	}
	cur->exist = pos;
	return;
}

Dataset::Trie::Node* Dataset::Trie::search(std::string& word) {
	Node* cur = trueRoot;
	for (int n{ 0 }; n < word.length(); ++n) {
		int i{ hexa(word[n])};
		if (!cur->key[i])
			return nullptr;
		cur = cur->children[i];
	}
	return cur;
}

bool Dataset::Trie::remove(Node* root, std::string& word, int n) {
	if (n == word.size()) {
		root->exist = 0;
		for (int i{ 0 }; i < 16; ++i) 
			if (root->children[i]) {
				return false;
			}
		delete root;
		return true;
	}
	int i{ hexa(word[n])};
	if (!root->key[i])
		return false;
	root->cnt--;
	if (remove(root->children[i], word, n + 1)) {
		root->key[i] = false;
		root->children[i] = nullptr;
		for (int i{ 0 }; i < 16; ++i) {
			if (root->key[i])
				return false;
		}
		delete root;
		return true;
	}
	return false;
}

void Dataset::Trie::remove(std::string& word) {
	remove(trueRoot, word, 0);
}

void Dataset::Trie::displayTree(Node* root, std::string& word, std::vector<std::string>& ans) {
	if (root->exist != 0) {
		ans.push_back(word);
	}
	for (int i{ 0 }; i < 16; ++i) {
		if (root->key[i]) {
			word.push_back(root->key[i]);
			displayTree(root->children[i], word, ans);
			word.pop_back();
		}
	}
}

void Dataset::Trie::displayTree(Node* root, std::string& word, int& num, std::vector<std::string>& ans) {
	if (num == 0)
		return;
	if (root->exist != 0) {
		ans.push_back(word);
		num--;
	}
	for (int i{ 0 }; i < 16; ++i) {
		if (root->key[i]) {
			word.push_back(root->key[i]);
			displayTree(root->children[i], word, num, ans);
			word.pop_back();
		}
	}
}

std::vector<std::string> Dataset::Trie::displayTree(std::string& word) {
	Node* cur{ search(word) };
	std::vector<std::string> ans{};
	if (!cur)
		return ans;
	displayTree(cur, word, ans);
	return ans;
}

std::vector<std::string> Dataset::Trie::displayTree(std::string& word, int num) {
	Node* cur{ search(word) };
	std::vector<std::string> ans{};
	if (!cur)
		return ans;
	displayTree(cur, word, num, ans);
	return ans;
}

void Dataset::Trie::deleteTree(Node* root) {
	for (int i{ 0 }; i < 16; ++i) {
		if (root->key[i])
			deleteTree(root->children[i]);
	}
	root = nullptr;
}

std::wstring Dataset::curDataSet = L"";

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
	std::ifstream fwout(curDataSet + L"/Words.bin", std::ios::binary | std::ios::in);
	std::ifstream fcout(curDataSet + L"/WordsColumn.bin", std::ios::binary | std::ios::in);
	int n{};
	fcout.read((char*)&n, sizeof(int));
	int curLen{};
	for (int i{ 0 }; i < n; ++i) {
		int size{};
		fcout.read((char*)&size, sizeof(int));
		char* word = new char[size - curLen];
		fwout.read((char*)word, (size - curLen));
		std::string input{ word };
		curLen = size + sizeof(int);
		fwout.read((char*)&size, sizeof(int));
		Character::stringToWString(input);
		root->insert(input, size);
		delete[] word;
	}
	fwout.close();
	fcout.close();
}

// Word here stores characters as hex chars, the function also return the string in the same fashion
std::string Dataset::definition(Trie* root, std::string& word) {
	Trie::Node* tmp{ root->search(word) };
	if (!tmp || tmp->exist == 0) {
		return "";
	}
	std::ifstream fin(curDataSet + L"/Definition.bin", std::ios::binary | std::ios::in);
	fin.seekg(std::ios::beg, tmp->exist);
	int size{};
	fin.read((char*)&size, sizeof(int));
	char* result = new char[size];
	fin.read(result, size);
	std::string str{ result };
	delete[] result;
	fin.close();
	return str;
}


// Both word and definition store characters as wide chars.
void Dataset::inputNewWord(Trie* root, std::string& word, std::string& definition) {
	//Input the definition into the file and return pos as the position of the inputted definition
	std::ofstream fout(curDataSet + L"/Definition.bin", std::ios::binary | std::ios::out);
	fout.seekp(std::ios::end, 0);
	int size{ static_cast<int>(definition.length()) + 1 };
	int pos{ };
	pos = fout.tellp();
	fout.write((char*)&size, sizeof(int));
	fout.write(definition.c_str(), size);
	fout.close();

	std::string tmp = word;
	Character::stringToWString(tmp);
	root->insert(tmp, pos);

	//Input the word and the position of the definition into the file and return the end position of the word
	fout.open(curDataSet + L"Word.bin", std::ios::binary | std::ios::out);
	fout.seekp(std::ios::end, 0);
	fout.write(word.c_str(), (word.length() + 1));
	fout.write((char*)&pos, sizeof(int));
	pos = fout.tellp();
	pos -= sizeof(int);
	fout.close();

	//Read the current number of words and increase it by 1
	std::ifstream fin(curDataSet + L"/WordColumn.bin", std::ios::binary | std::ios::in);
	int num{};
	fin.read((char*)&num, sizeof(int));
	++num;
	fin.close();

	//Change the number of words and input the end position of the word
	std::ofstream fcout(curDataSet + L"/WordColumn.bin", std::ios::binary | std::ios::out);
	fcout.write((char*)&num, sizeof(int));
	fcout.seekp(std::ios::end, 0);
	fcout.write((char*)&pos, sizeof(int));
	fcout.close();
}