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

std::wstring Character::stringToWString(std::string& str) {
	std::wstring_convert< std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

std::u16string Character::stringTou16String(std::string& str) {
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	return converter.from_bytes(str);
}

std::u32string Character::stringTou32String(std::string& str) {
	std::wstring_convert<std::codecvt<char32_t, char, std::mbstate_t>, char32_t> converter;
	return converter.from_bytes(str);
}

int hexa(int x) {
	if ('0' <= x && x <= '9')
		return x - '0';
	return x - 'a' + 10;
}

char reverseHex(int x) {
	if (0 <= x && x <= 9)
		return x + '0';
	return x - 10 + 'a';
}
// All word in Trie store hex char
void Dataset::Trie::insert(std::string& word, int pos, int n) {
	Node* cur = trueRoot;
	if (pos == -1)
		return;
	for (int i{ 0 }; i < word.length(); ++i) {
		cur->cnt++;
		int x{ hexa(word[i])};
		if (!cur->children[x]) {
			cur->children[x] = new Node;
			cur = cur->children[x];
		}
		else {
			cur = cur->children[x];
		}

	}
	cur->exist = pos;
	cur->num = n;
	return;
}

void DefinitionSet::Trie::insert(std::string& word, int wordNum) {
	Node* cur = trueRoot;
	for (int i{ 0 }; i < word.length(); ++i) {
		int x{ hexa(word[i]) };
		if (!cur->children[x]) {
			cur->children[x] = new Node;
			cur = cur->children[x];
		}
		else {
			cur = cur->children[x];
		}
	}
	cur->wordNum.push_back(wordNum);
	return;
}

Dataset::Trie::Node* Dataset::Trie::search(std::string& word) {
	Node* cur = trueRoot;
	for (int n{ 0 }; n < word.length(); ++n) {
		int i{ hexa(word[n])};
		if (!cur->children[i])
			return nullptr;
		cur = cur->children[i];
	}
	return cur;
}

DefinitionSet::Trie::Node* DefinitionSet::Trie::search(std::string& word) {
	Node* cur = trueRoot;
	for (int n{ 0 }; n < word.length(); ++n) {
		int i{ hexa(word[n]) };
		if (!cur->children[i])
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
	if (!root->children[i])
		return false;
	root->cnt--;
	if (remove(root->children[i], word, n + 1)) {
		root->children[i] = nullptr;
		for (int i{ 0 }; i < 16; ++i) {
			if (root->children[i])
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
		if (root->children[i]) {
			word.push_back(reverseHex(i));
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
		if (root->children[i]) {
			word.push_back(reverseHex(i));
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
		if (root->children[i])
			deleteTree(root->children[i]);
	}
	root = nullptr;
}

void DefinitionSet::Trie::deleteTree(Node*& root) {
	for (int i{ 0 }; i < 16; ++i) {
		if (root->children[i])
			deleteTree(root->children[i]);
	}
	root = nullptr;
}

std::string Dataset::curDataSet = "";

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

void Dataset::loadDataSet(Trie* root, DefinitionSet::Trie* defiRoot) {
	std::ifstream fwout(curDataSet + "/Words.bin", std::ios::binary | std::ios::in);
	std::ifstream fcout(curDataSet + "/WordsColumn.bin", std::ios::binary | std::ios::in);
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
		std::wstring tmp = Character::stringToWString(input);
		input = Character::decodeStr<std::wstring, wchar_t>(tmp);
		root->insert(input, size, i);
		DefinitionSet::loadDefinitionSet(defiRoot, size, i);
		delete[] word;
	}
	fwout.close();
	fcout.close();
}

// Word here stores characters as hex chars, the function also return the string in the same fashion
std::string Dataset::definition(Trie* root, std::string& word) {
	Trie::Node* tmp{ root->search(word) };
	if (!tmp || tmp->exist == -1) {
		return "";
	}
	return definition(tmp->exist);
}

std::string Dataset::definition(int pos) {
	std::ifstream fin(Dataset::curDataSet + "/Definition.bin", std::ios::binary | std::ios::in);
	int size{};
	fin.seekg(pos, std::ios::beg);
	fin.read((char*)&size, sizeof(int));
	char* tmp = new char[size];
	fin.read(tmp, size);
	std::string input = tmp;
	delete[] tmp;
	fin.close();
	return input;
}

// Both word and definition store characters as wide chars.
void Dataset::inputNewWord(Trie* root, DefinitionSet::Trie* defiRoot, std::string& word, std::string& definition) {
	//Input the definition into the file and return pos as the position of the inputted definition
	std::fstream fout(curDataSet + "/Definition.bin", std::ios::binary | std::ios::out | std::ios::in);
	fout.seekp(0, std::ios::end);
	int size{ static_cast<int>(definition.length()) + 1 };
	int pos{ };
	pos = fout.tellp();
	fout.write((char*)&size, sizeof(int));
	fout.write(definition.c_str(), size);
	fout.close();

	std::wstring tmp = Character::stringToWString(word);
	std::string temp = Character::decodeStr<std::wstring, wchar_t>(tmp);
	root->insert(temp, pos, root->trueRoot->cnt);
	DefinitionSet::loadDefinitionSet(defiRoot, pos, root->trueRoot->cnt);

	//Input the word and the position of the definition into the file and return the end position of the word
	fout.open(curDataSet + "/Words.bin", std::ios::binary | std::ios::out | std::ios::in);
	fout.seekp(0, std::ios::end);
	fout.write(word.c_str(), (word.length() + 1));
	fout.write((char*)&pos, sizeof(int));
	pos = fout.tellp();
	pos -= sizeof(int);
	fout.close();

	//Read the current number of words and increase it by 1
	std::ifstream fin(curDataSet + "/WordsColumn.bin", std::ios::binary | std::ios::in);
	int num{};
	fin.read((char*)&num, sizeof(int));
	++num;
	fin.close();

	//Change the number of words and input the end position of the word
	std::fstream fcout(curDataSet + "/WordsColumn.bin", std::ios::binary | std::ios::out | std::ios::in);
	fcout.write((char*)&num, sizeof(int));
	fcout.seekp(0, std::ios::end);
	fcout.write((char*)&pos, sizeof(int));
	fcout.close();
}

//Change the pos to the definition to -1
void Dataset::removeWordFromFile(int n) {
	//Get the last position of the word, a.k.a the position of pos
	std::fstream ft(curDataSet + "/WordsColumn.bin", std::ios::binary | std::ios::in);
	int pos{};
	ft.seekg((n + 1) * sizeof(int), std::ios::cur);
	ft.read((char*)&pos, sizeof(int));
	ft.close();
	int num = -1;
	//Change the pos of the word to -1
	ft.open(curDataSet + "/Words.bin", std::ios::binary | std::ios::out | std::ios::in);
	ft.seekp(pos, std::ios::beg);
	ft.write((char*)&num, sizeof(int));
	ft.close();
}

std::string Dataset::getOneWordFromFile(int n) {
	std::ifstream fin(curDataSet + "/WordsColumn.bin", std::ios::binary | std::ios::in);
	int num{};
	fin.read((char*)&num, sizeof(int));
	if (n >= num)
		return "";
	int prePos{}, pos{};
	if (n == 0) {
		fin.read((char*)&pos, sizeof(int));
	}
	else {
		fin.seekg((n - 1) * sizeof(int), std::ios::cur);
		fin.read((char*)&prePos, sizeof(int));
		fin.read((char*)&pos, sizeof(int));
	}
	fin.close();
	char* tmp = new char[pos - prePos - sizeof(int)];
	fin.open(curDataSet + "/Words.bin", std::ios::binary | std::ios::in);
	fin.seekg(prePos + sizeof(int), std::ios::beg);
	fin.read(tmp, pos - prePos - sizeof(int));
	fin.close();
	std::string result{ tmp };
	delete[] tmp;
	return result;
}

std::vector<int> DefinitionSet::Trie::allWordContain(std::string& word) {
	Node* cur = search(word);
	return cur->wordNum;
}

void DefinitionSet::loadDefinitionSet(DefinitionSet::Trie*& root, int pos, int n) {
	std::string definit{ Dataset::definition(pos) };
	std::wstring input = Character::stringToWString(definit);
	splitLineToTrie<std::wstring, wchar_t>(input, root, n);
}
	