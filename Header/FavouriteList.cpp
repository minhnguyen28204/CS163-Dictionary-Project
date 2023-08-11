#include "FavouriteList.hpp"

std::string favorite::pathEmoji = "FavouriteList\\FavouriteEmoji\\FavouriteEmoji.txt";
std::string favorite::pathSlang = "FavouriteList\\FavouriteSlang\\FavouriteSlang.txt";
std::string favorite::pathEngToEng = "FavouriteList\\FavouriteEngToEng\\FavouriteEngToEng.txt";
std::string favorite::pathEngToVie = "FavouriteList\\FavouriteEngToVie\\FavouriteEngToVie.txt";
std::string favorite::pathVieToEng = "FavouriteList\\FavouriteVieToEng\\FavouriteVieToEng.txt";
std::vector<std::string> favorite::mode{ favorite::pathEmoji,favorite::pathSlang,favorite::pathEngToEng,favorite::pathEngToVie,favorite::pathVieToEng };
std::string favorite::FolEmoji = "FavouriteList\\FavouriteEmoji";
std::string favorite::FolSlang = "FavouriteList\\FavouriteSlang";
std::string favorite::FolEngToEng = "FavouriteList\\FavouriteEngToEng";
std::string favorite::FolEngToVie = "FavouriteList\\FavouriteEngToVie";
std::string favorite::FolVieToEng = "FavouriteList\\FavouriteVieToEng";
std::vector<std::string> favorite::folder{ favorite::FolEmoji,favorite::FolSlang,favorite::FolEngToEng,favorite::FolEngToVie,favorite::FolVieToEng };

vector<string> favouriteList()
{
	vector<string> favorite;
	ifstream fin;
	ifstream fin2;
	fin.open(favorite::mode[Path::curPath], ios::binary | ios::in);
	if (!fin.is_open())
		return favorite;
	int n;
	fin.read((char*)&n, sizeof(int));
	for (int i = 0; i < n; i++)
	{
		int size;
		fin.read((char*)&size, sizeof(int));
		char* word = new char[size + 1];
		fin.read((char*)word, size);
		word[size] = '\0';
		string output = word;
		string fileName = favorite::folder[Path::curPath] + output + ".bin";
		fin2.open(fileName);
		if (fin2)
		{
			favorite.push_back(output);
			fin2.close();
		}
		delete[] word;
	}
	fin.close();
	return favorite;
}

bool isFavourite(std::string& word)
{
	ifstream fin;
	string output = word;
	string fileName = favorite::folder[Path::curPath] + output + ".bin";
	fin.open(fileName);
	if (fin.is_open())
	{
		//cout << "Opened file fav"<<endl;
		fin.close();
		return true;
	}
	//cout << "Could not open file fav"<<endl;
	return false;
}

bool addWordToFavList(std::string& word)
{
    ifstream fin;
	std::string path = favorite::folder[Path::curPath] + word + ".bin";
    fin.open(path);
    if(fin.is_open())
    {
		//cout << "Word have been added!"<<endl;
        fin.close();
		return true;
    }
	fin.open(favorite::mode[Path::curPath],ios::binary|ios::app);
	if (!fin.is_open()) return false;
	int size;
	if (fin.tellg() > 0)
	{
		fin.seekg(0, ios::beg);
		fin.read((char*)&size, sizeof(int));
	}
	else size = 0;
	//cout <<"Size: " <<size << endl;
	size++;
	//cout <<"Size: "<< size << endl;
	fin.close();
    ofstream fout;
	fout.open(favorite::mode[Path::curPath], ios::binary | ios::app);
    if(!fout.is_open()) return false;
	int range = sizeof(word);
	fout.write((char*)&range, sizeof(int));
    fout.write((char*)&word,sizeof(word));
	//cout << "Finish saving word" << endl;
	fout.seekp(0, ios::beg);
	fout.write((char*)&size, sizeof(int));
    fout.close();
    fout.open(path,ios::binary);
    if(!fout.is_open()) return false;
    fout.close();
    return true;
}

bool removeWordFromFavList(std::string& word)
{
    std::string path = favorite::folder[Path::curPath] + word + ".bin";
	if (!remove(path.c_str())) {
		//cout << "Finish moving" << endl;
		return true;
	}
	//else cout << "Could not do" << endl;
    return false;
}
