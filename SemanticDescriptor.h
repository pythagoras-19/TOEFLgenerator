#ifndef SEMANTICDESCRIPTOR_H_INCLUDED
#define SEMANTICDESCRIPTOR_H_INCLUDED
//#include "std_lib_facilities.h"//maybe wrong here
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

struct ContextWord
{
    string word;
    int count;
};

class SemanticDescriptor
{ 
    private:

        string targetWord;
        vector<ContextWord> contextWords;

    public:
        SemanticDescriptor(string _targetWord) : targetWord(_targetWord) {}
        string getTargetWord() {return targetWord;}
        void processContextWord(string s);
        int operator*(const SemanticDescriptor& desc);
        friend ostream& operator<<(ostream& os, const SemanticDescriptor& desc);
        friend istream& operator>>(istream& is, SemanticDescriptor& desc);//NEW
};

#endif // SEMANTICDESCRIPTOR_H_INCLUDED