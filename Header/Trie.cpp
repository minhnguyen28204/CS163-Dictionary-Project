#include "Trie.hpp"
#include "Random.hpp"

std::mt19937 Random::mt{ Random::generate() };
WordSet::Trie* WordSet::wordTrie = new WordSet::Trie;
int WordSet::wordOrigCount = 0;
int WordSet::wordNewCount = 0;
int Path::curPath = 0;
DefinitionSet::Trie* DefinitionSet::definitionTrie = new DefinitionSet::Trie;
std::vector<std::string> Path::path{};
char Character::wordSplit[]{ ',', ' ', '.', ';', '|', ':', '(', ')', '?', '-', '/' , '!', '#', '[', ']', '~'};

int getLength(std::wstring ws) { return ws.length(); }
int getLength(std::u16string ws) { return ws.length(); }
int getLength(std::u32string ws) { return ws.length(); }

//All str of Character namespace below store wide chars.

std::wstring Character::stringToWString(std::string str) {
	std::wstring_convert< std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

std::u16string Character::stringTou16String(std::string str) {
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	return converter.from_bytes(str);
}

std::u32string Character::stringTou32String(std::string str) {
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
	return converter.from_bytes(str);
}

std::string Character::backToString(std::wstring& str) {
	std::wstring_convert< std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(str);
}

std::string Character::backToString(std::u16string& str) {
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	return converter.to_bytes(str);
}

std::string Character::backToString(std::u32string& str) {
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
	return converter.to_bytes(str);
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
void WordSet::Trie::insert(std::string word, int pos, int n) {
	Node* cur = trueRoot;
	for (int i{ 0 }; i < word.length(); ++i) {
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

void DefinitionSet::Trie::insert(std::string word, int wordNum) {
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
	if (position<int>(cur->wordNum, wordNum) != -1)
		return;
	int i = cur->wordNum.size() - 1 ;
	cur->wordNum.push_back(wordNum);
	for (; i >= 0 && cur->wordNum[i] > wordNum; --i) {
		cur->wordNum[i + 1] = cur->wordNum[i];
	}
	cur->wordNum[i + 1] = wordNum;
}

WordSet::Trie::Node* WordSet::Trie::search(std::string word) {
	Node* cur = trueRoot;
	for (int n{ 0 }; n < word.length(); ++n) {
		int i{ hexa(word[n])};
		if (!cur->children[i])
			return nullptr;
		cur = cur->children[i];
	}
	return cur;
}

DefinitionSet::Trie::Node* DefinitionSet::Trie::search(std::string word) {
	Node* cur = trueRoot;
	for (int n{ 0 }; n < word.length(); ++n) {
		int i{ hexa(word[n]) };
		if (!cur->children[i])
			return nullptr;
		cur = cur->children[i];
	}
	return cur;
}

bool removeWordFromTrie(WordSet::Trie::Node* root, std::string& word, int n) {
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
	if (removeWordFromTrie(root->children[i], word, n + 1)) {
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

void WordSet::Trie::remove(std::string word) {
	removeWordFromTrie(trueRoot, word, 0);
}

void displayWordTrie(WordSet::Trie::Node* root, std::string& word, std::vector<std::string>& ans) {
	if (root->exist != -1) {
		if (Path::curPath < 5)
			ans.push_back(Character::encodeStr<wchar_t>(word));
	}
	for (int i{ 0 }; i < 16; ++i) {
		if (root->children[i]) {
			word.push_back(reverseHex(i));
			displayWordTrie(root->children[i], word, ans);
			word.pop_back();
		}
	}
}

void displayWordTrie(WordSet::Trie::Node* root, std::string& word, int& num, std::vector<std::string>& ans) {
	if (num == 0)
		return;
	if (root->exist != -1) {
		if (Path::curPath < 5)
			ans.push_back(Character::encodeStr<wchar_t>(word));
		num--;
	}
	for (int i{ 0 }; i < 16; ++i) {
		if (root->children[i]) {
			word.push_back(reverseHex(i));
			displayWordTrie(root->children[i], word, num, ans);
			word.pop_back();
		}
	}
}

void displayDefiTrie(DefinitionSet::Trie::Node* root, std::string& word, std::vector<std::string>& ans) {
	if (root->wordNum.size() != 0) {
		if (Path::curPath < 5)
			ans.push_back(Character::encodeStr<wchar_t>(word));
	}
	for (int i{ 0 }; i < 16; ++i) {
		if (root->children[i]) {
			word.push_back(reverseHex(i));
			displayDefiTrie(root->children[i], word, ans);
			word.pop_back();
		}
	}
}

std::vector<std::string> WordSet::Trie::displayTree(std::string word) {
	Node* cur{ search(word) };
	std::vector<std::string> ans{};
	if (!cur)
		return ans;
	displayWordTrie(cur, word, ans);
	return ans;
}

std::vector<std::string> WordSet::Trie::displayTree(std::string word, int num) {
	Node* cur{ search(word) };
	std::vector<std::string> ans{};
	if (!cur)
		return ans;
	displayWordTrie(cur, word, num, ans);
	return ans;
}

std::vector<std::string> DefinitionSet::displayTree() {
	std::string word{};
	std::vector<std::string> result{};
	displayDefiTrie(definitionTrie->trueRoot, word, result);
	return result;
}

void WordSet::Trie::deleteTree(Node* root) {
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

void DefinitionSet::Trie::remove(std::string str, int n) {
	Node* tmp = search(str);
	if (!tmp)
		return;
	int pos{ position(tmp->wordNum, n) };
	if (pos == -1)
		return;
	tmp->wordNum.erase(tmp->wordNum.begin() + pos);
}

void WordSet::switchWordSet(int n) {
	if (n == Path::curPath || n < 0 || n >= Path::path.size())
		return;
	Path::curPath = n % Path::path.size();
	loadAllData();
}

void WordSet::loadWordSet() {
	std::ifstream fwout(Path::path[Path::curPath] + "/Words.bin", std::ios::binary | std::ios::in);
	std::ifstream fcout(Path::path[Path::curPath] + "/WordsColumn.bin", std::ios::binary | std::ios::in);
	std::ifstream fdout(Path::path[Path::curPath] + "/Definition.bin", std::ios::binary | std::ios::in);
	int n{};
	fcout.read((char*)&n, sizeof(int));
	int curLen{};
	Trie::Node* cur{ wordTrie->trueRoot };
	std::stack<Trie::Node*> nodeStack{};
	int read{}, cnt{ -1 };
	std::string curStr{};
	for (int i{ 0 }; i < n; ++i) {
		int size{};
		fcout.read((char*)&size, sizeof(int));
		char* word = new char[size - curLen];
		fwout.read((char*)word, (size - curLen));
		std::string input{ word };
		if ((i + 1) % 100 == 0)
			std::cerr << "\b\b\b\b\b\b\b" << i;
		curLen = size + sizeof(int);
		fwout.read((char*)&size, sizeof(int));
		std::wstring tmp = Character::stringToWString(input);
		if (tmp.length() != 0)
			input = Character::decodeStr(tmp, tmp[0]);
		//root->insert(input, size, i);
		if (size != -1) {
			int j{ 0 };
			for (; j < curStr.length() && j < input.length(); ++j) {
				if (curStr[j] != input[j])
					break;
			}
			while (read > j) {
				curStr.pop_back();
				cur = nodeStack.top();
				nodeStack.pop();
				read--;
			}
			for (; read < input.length(); ++read) {
				nodeStack.push(cur);
				curStr.push_back(input[read]);
				int x{ hexa(input[read]) };
				if (!cur->children[x]) {
					cur->children[x] = new Trie::Node;
					cur = cur->children[x];
				}
				else {
					cur = cur->children[x];
				}
			}
		}
		cur->exist = size;
		cur->num = i;
		delete[] word;
		fdout.read((char*)&size, sizeof(int));
		word = new char[size];
		fdout.read(word, size);
		std::string input2{ word };
		delete[] word;

		DefinitionSet::loadDefinitionSet(Character::stringToWString(input2), i);
	}
	fwout.close();
	fcout.close();
	fdout.close();
}

std::string WordSet::definition(Trie::Node* root) {
	if (root->exist < 0 || root->num >= wordOrigCount + wordNewCount)
		return "";
	if (root->num < wordOrigCount) {
		std::ifstream fin(Path::path[Path::curPath] + "/Definition.bin", std::ios::binary | std::ios::in);
		int size{};
		fin.seekg(root->exist, std::ios::beg);
		fin.read((char*)&size, sizeof(int));
		char* tmp = new char[size];
		fin.read(tmp, size);
		std::string input = tmp;
		delete[] tmp;
		fin.close();
		return input;
	}
	std::ifstream fin(Path::path[Path::curPath] + "/New.txt");
	std::string input{};
	for (int i{ 0 }; i <= root->exist; ++i)
		std::getline(fin, input);
	std::getline(fin, input, '\t');
	std::getline(fin, input);
	return input;
}

void DefinitionSet::Trie::editDefinition(std::string newDefinition, int n)
{
	std::fstream ft(Path::path[Path::curPath] + "/Definition.bin", std::ios::binary | std::ios::out | std::ios::in);
	ft.seekp(0, std::ios::end);
	int size = static_cast<int>(newDefinition.length()) + 1;
	int pos;
	pos = ft.tellp(); // position of new definition in definition.bin
	ft.write((char*)&size, sizeof(int));
	ft.write(newDefinition.c_str(), size);
	ft.close();

	ft.open(Path::path[Path::curPath] + "/WordsColumn.bin", std::ios::binary | std::ios::in);
	int pos2; // position of the word in file word.bin
	ft.seekg((n + 1) * sizeof(int), std::ios::beg);
	ft.read((char*)&pos2, sizeof(int));
	ft.close();

	ft.open(Path::path[Path::curPath] + "/Words.bin", std::ios::binary | std::ios::out | std::ios::in);
	ft.seekp(pos2, std::ios::beg);
	ft.write((char*)&pos, sizeof(int));
	ft.close();
}

std::string WordSet::getOneWordFromBinFile(int n) {
	std::ifstream fin(Path::path[Path::curPath] + "/WordsColumn.bin", std::ios::binary | std::ios::in);
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
		prePos += sizeof(int);
	}
	fin.close();
	char* tmp = new char[pos - prePos];
	fin.open(Path::path[Path::curPath] + "/Words.bin", std::ios::binary | std::ios::in);
	fin.seekg(prePos, std::ios::beg);
	fin.read(tmp, pos - prePos);
	fin.read((char*)&pos, sizeof(int));
	fin.close();
	if (pos < 0) {
		delete[] tmp;
		return "";
	}
	std::string result{ tmp };
	delete[] tmp;
	return result;
}

std::string WordSet::getOneWordFromTextFile(int n) {
	std::ifstream fin(Path::path[Path::curPath] + "/New.txt");
	std::string word{}, tmp;
	for (int i{ 0 }; i <= n; ++i) {
		std::getline(fin, tmp);
	}
	std::getline(fin, word, '\t');
	std::getline(fin, tmp);
	if (tmp.length() == 0)
		return "";
	return word;
}

std::string WordSet::getWord(int n) {
	if (n < 0 || n >= wordOrigCount + wordNewCount)
		return "";
	std::string tmp{};
	if (n < wordOrigCount) {
		tmp = getOneWordFromBinFile(n);
	}
	else tmp = getOneWordFromTextFile(n - wordOrigCount);
	if (tmp.length() == 0) {
		return "";
	}
	std::wstring definition = Character::stringToWString(tmp);
	Trie::Node* defi = wordTrie->search(Character::decodeStr(definition, definition[0]));
	if (!defi || defi->exist == -1)
		return "";
	return tmp;
}

std::vector<int> DefinitionSet::Trie::allWordContain(std::string word) {
	std::vector<int> tmp{};
	Node* cur = search(word);
	if (!cur)
		return tmp;
	return cur->wordNum;
}

std::vector<std::string> DefinitionSet::allWord(std::vector<int> nums) {
	std::vector<std::string> result{};
	for (int i{ 0 }; i < nums.size(); ++i) {
		std::string input = WordSet::getWord(nums[i]);
		if (input.length() != 0)
			result.push_back(input);
	}
	return result;
}

std::string randomWordFromFile() {
	std::string result = WordSet::getWord(Random::get(0, WordSet::wordOrigCount + WordSet::wordNewCount - 1));
	if (result.length() == 0) {
		result = WordSet::getWord(Random::get(0, WordSet::wordOrigCount + WordSet::wordNewCount - 1));
	}
	return result;
}

void buildSerialWordTrie(WordSet::Trie::Node* root, std::string& serial) {
	if (root->exist != -1) {
		serial.push_back('[');
		serial += std::to_string(root->exist);
		serial.push_back(',');
		serial += std::to_string(root->num);
		serial.push_back(']');
	}
	for (int i{ 0 }; i < 16; ++i) {
		if (root->children[i]) {
			serial.push_back(reverseHex(i));
			buildSerialWordTrie(root->children[i], serial);
		}
	}
	serial.push_back('>');
}

void buildSerialDefiTrie(DefinitionSet::Trie::Node* root, std::string& serial) {
	if (root->wordNum.size() != 0) {
		serial.push_back('[');
		for (int i{ 0 }; i < root->wordNum.size(); ++i) {
			if (i != 0)
				serial.push_back(',');
			serial += std::to_string(root->wordNum[i]);
		}
		serial.push_back(']');
	}
	for (int i{ 0 }; i < 16; ++i) {
		if (root->children[i]) {
			serial.push_back(reverseHex(i));
			buildSerialDefiTrie(root->children[i], serial);
		}
	}
	serial.push_back('>');
}

void WordSet::buildSerialFile() {
	std::string line{};
	buildSerialWordTrie(wordTrie->trueRoot, line);
	std::ofstream fin(Path::path[Path::curPath] + "/Serial.txt");
	fin << line;
	fin.close();
	line.clear();
	buildSerialDefiTrie(DefinitionSet::definitionTrie->trueRoot, line);
	fin.open(Path::path[Path::curPath] + "/SerialDefi.txt");
	fin << line;
	fin.close();
}

int deserialiseStrToTrie(WordSet::Trie::Node* root, std::string& serial, int& read) {
	int wordSeen = 0;
	if (serial[read] == '[') {
		read++;
		std::string tmp{};
		while (serial[read] != ',') {
			tmp.push_back(serial[read]);
			read++;
		}
		root->exist = std::stoi(tmp);
		read++;
		tmp.clear();
		while (serial[read] != ']') {
			tmp.push_back(serial[read]);
			read++;
		}
		root->num = std::stoi(tmp);
		read++;
	}
	while (serial[read] != '>') {
		int ch = hexa(serial[read]);
		read++;
		root->children[ch] = new WordSet::Trie::Node;
		wordSeen += deserialiseStrToTrie(root->children[ch], serial, read);
	}
	read++;
	return wordSeen;
}

void inputNum(std::vector<int>& ans, std::string& res) {
	std::string tmp{};
	for (int i{ 0 }; i < res.length(); ++i) {
		if (res[i] != ',') {
			tmp.push_back(res[i]);
		}
		else {
			ans.push_back(std::stoi(tmp));
			tmp.clear();
		}
	}

}

int deserialiseStrToDefi(DefinitionSet::Trie::Node* root, std::string& serial, int& read) {
	int wordSeen = 0;
	if (serial[read] == '[') {
		read++;
		std::string tmp{};
		while (serial[read] != ']') {
			tmp.push_back(serial[read]);
			read++;
		}
		tmp.push_back(',');
		read++;
		inputNum(root->wordNum, tmp);
	}
	while (serial[read] != '>') {
		int ch = hexa(serial[read]);
		read++;
		root->children[ch] = new DefinitionSet::Trie::Node;
		wordSeen += deserialiseStrToDefi(root->children[ch], serial, read);
	}
	read++;
	return wordSeen;
}

void WordSet::loadTrieFromString() {
	std::ifstream fin(Path::path[Path::curPath] + "/Serial.txt");
	std::string serial{};
	std::getline(fin, serial);
	fin.close();
	int n{ 0 };
	deserialiseStrToTrie(wordTrie->trueRoot, serial, n);
}

void DefinitionSet::loadTrieFromString() {
	std::ifstream fin(Path::path[Path::curPath] + "/SerialDefi.txt");
	std::string serial{};
	std::getline(fin, serial);
	fin.close();
	int n{ 0 };
	deserialiseStrToDefi(definitionTrie->trueRoot, serial, n);
}

void WordSet::loadWordCount() {
	std::ifstream fin;
	fin.open(Path::path[Path::curPath] + "/WordsColumn.bin", std::ios::binary);
	fin.read((char*)&wordOrigCount, sizeof(int));
	fin.close();
	fin.open(Path::path[Path::curPath] + "/New.txt");
	fin >> wordNewCount;
	fin.close();
}

void WordSet::loadNewData() {
	std::ifstream fin(Path::path[Path::curPath] + "/New.txt");
	std::string word{}, definition{};
	std::getline(fin, word);
	for (int i{ 0 }; i < wordNewCount; ++i) {
		int read{};
		std::getline(fin, word, '\t');
		std::getline(fin, definition);
		if (definition.length() != 0) {
			insert(Character::stringToWString(word), i, wordOrigCount + i);
			DefinitionSet::loadDefinitionSet(Character::stringToWString(definition), wordOrigCount + i);
		}
		else {
			//DefinitionSet::removeDefinition(Character::stringToWString(definition), 0);
			insert(Character::stringToWString(word), -1, wordOrigCount + i);
		}
	}
}

void WordSet::loadAllData() {
	loadWordCount();
	loadTrieFromString();
	DefinitionSet::loadTrieFromString();
	loadNewData();
}

void WordSet::reset() {
	std::ofstream fout(Path::path[Path::curPath] + "/New.txt", std::ios::trunc);
	fout << 0;
	fout.close();
}

void Path::loadPath(int n) {
	path.push_back("Data/emoticon");
	path.push_back("Data/slang");
	path.push_back("Data/engToEng");
	path.push_back("Data/engToVie");
	path.push_back("Data/vieToEng");
	curPath = n % path.size();
}
