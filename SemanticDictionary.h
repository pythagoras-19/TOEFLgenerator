#ifndef SEMANTICDICTIONARY_H_INCLUDED
#define SEMANTICDICTIONARY_H_INCLUDED

#include "std_lib_facilities.h"
#include "SemanticDescriptor.h"
#include <sstream>
using namespace std;

vector<vector<string>> getSentenceLists(string text);
bool isStopWord(string s);//NEW

class SemanticDictionary
{
    private:
        vector<SemanticDescriptor> semanticDescriptors;
        int searchTargetWord(string targetWord);

    public:
        void processTargetWord(string targetWord, vector<string> sentenceList);
        double getSimilarity(string targetWord1, string targetWord2);
        string mostSimilarWord(string word, vector<string> choices);
        friend ostream& operator<<(ostream& os, const SemanticDictionary& d);
        friend istream& operator>>(istream& is, SemanticDictionary& d);//NEW
};

ostream& operator<<(ostream& os, const vector<vector<string>>& sentenceLists);

#endif // SEMANTICDICTIONARY_H_INCLUDED