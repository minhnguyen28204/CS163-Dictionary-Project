#include "FavouriteList.hpp"
#include <fstream>
#include <stdio.h>

bool addWordToFavList(std::string& word)
{
    ifstream fin;
    std::string path = "\\FavouriteList\\" + word + ".bin";
    fin.open(path);
    if(fin.is_open()) 
    {
        fin.close();
        throw 'x';
    }
    else fin.close();
    ofstream fout;
    fout.open("\\FavouriteList\\FavouriteList.bin",ios::binary|ios::app);
    if(!fout.is_open()) return false;
    fout.write((char*)&word,sizeof(word));
    fout.close();
    fout.open(path,ios::binary);
    if(!fout.is_open()) return false;
    fout.close();
    return true;
}

bool removeWordFromFavList(std::string& word)
{
    std::string path = "\\FavouriteList\\" + word + ".bin";
    if(!remove(path)) return true;
    return false;
}