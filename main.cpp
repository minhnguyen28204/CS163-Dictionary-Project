#include "Header/MainFunction.hpp"
#include "Header/Trie.hpp"
using namespace std;

int main()
{
    WordSet::switchWordSet(3);
    WordSet::loadAllData();
    Dictionary dictionary;
    dictionary.run();
    return 0;
}
