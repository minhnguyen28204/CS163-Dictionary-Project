#include "Header/MainFunction.hpp"
#include "Header/Trie.hpp"
using namespace std;

int main()
{
    Path::loadPath();
    WordSet::loadAllData();
    Dictionary dictionary;
    dictionary.run();
    return 0;
}
