#include "SemanticDescriptor.h"
#include "SemanticDictionary.h"
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

void SemanticDescriptor::processContextWord(string s)
{
    //std::cout << "In void SemanticDescriptor::processContextWord(string s)" << std::endl;
    bool flag = false;
    ContextWord obj;
    obj.word = s;
    obj.count = 1;
    if (contextWords.size() > 0)
    {
        for(size_t i=0; i < contextWords.size(); i++)
        {
        //std::cout << contextWords.size() << std::endl;
            if(contextWords[i].word == s)
            {
                contextWords[i].count++;
                flag = true;
                break;
            }
            //else
            //{
                 //s.push_back(obj);//not sure about this 
            //}
        }
    }
    if (flag == false)
    {
        contextWords.push_back(obj);
    }
    //std::cout << "In processContextWords the size of contextWords is: " << contextWords.size() << std::endl;
}

//The dot ( ∙ ) represents the dot product operator, 
//which will multiply corresponding elements of each vector 
//and sum their products
int SemanticDescriptor::operator*(const SemanticDescriptor& desc)
{
    //std::cout << "In int SemanticDescriptor::operator*(const SemanticDescriptor& desc)" <<std::endl;
    int sum = 0;
    for( size_t i=0; i < this->contextWords.size(); i++)//SemanticDescriptor::contextWords.size()
    {
        for (size_t j=0; j < desc.contextWords.size(); j++)
        {
            if (this->contextWords.at(i).word == desc.contextWords.at(j).word)
            {
                 sum += (this->contextWords.at(i).count)* (desc.contextWords.at(j).count);
                 //std::cout << "contextWords[i].count : " << contextWords[i].count << "desc.contextWords[j].count : " << desc.contextWords[j].count << std::endl;
            }  
        }
    }
    return sum;
}
//Output the contents of the SemanticDescriptor as shown in the sample output
ostream& operator<<(ostream& os, const SemanticDescriptor& desc)
{
    //std::cout << "In ostream& operator<<(ostream& os, const SemanticDescriptor& desc)" << std::endl;
    //os << "Semantic Descriptors:\n{ " << std::endl;
    //os << desc.contextWords.size() << std::endl;
    //os << desc.targetWord << std::endl;
   os << desc.targetWord;
   cout  << "desc.contextWords.size()" << desc.contextWords.size() << endl;
   os << " { ";
   
   for(size_t i=0; i < desc.contextWords.size(); i++)
    {
       os << " " << desc.contextWords[i].word << " " << desc.contextWords[i].count << " ";
    }
    
    os << "}" << std::endl;
    os << std::endl;//added a new line 
    

    return os;
}
istream& operator>>(istream& is, SemanticDescriptor& desc)//SP M05-M07
{
    //TODO:
    cout << "in istream& operator>>(istream& is, SemanticDescriptor& desc)//SP M05-M07" << endl;
    ContextWord temp;
    desc.targetWord = "";
    desc.contextWords.clear();
    char c;
    //desc.targetWord = is >> desc.targetWord;
    is >> desc.targetWord;//Extract the targetWord and copy it to desc
    cout << desc.targetWord << endl;
    cout  << "desc.contextWords.size()" << desc.contextWords.size() << endl;
    //is >> c;
    //cout << "c isss=" <<  c << endl;
    //TO DO: read target word
    is >> c;
    if(c != '{')//If it is not '{', call unget() on the istream, set the failbit, and return, as we have done in previous labs
    {
        cout << "in 50 " << endl;
        is.unget();
        //std::cout.setstate(std::ios::failbit);
        is.clear(ios_base::failbit);
        //std::cout << "Fail!\n";  
        return is;
    }
    //for(size_t i=0; i < desc.contextWords.size(); i++)
    //int i=0;
    while (!(is.fail()))
    {
        cout << "in 51" << endl;
        is >> c;
        //cout << c;
        if(c == '}')//If it is '}', we have reached the end of the descriptor.  Return immediately.
        {
            cout << "returning from semanticDescriptor -> semanticDictionary because of }" << endl;
            return is;
        }
        is.unget();
        //is >> c;
       // cout << "here " << c << endl;
        //is >> desc.contextWords[i].word >> desc.contextWords[i].count;
        //cout << desc.contextWords[i].word << desc.contextWords[i].count << endl;

        is >> temp.word >> temp.count;
       // cout << temp.word << " " << temp.count << endl;
        //cout << temp.word << temp.count << endl;
        desc.contextWords.push_back(temp);
        //i++;
    }
    return is;
}
/*
 for(size_t i=0; i < desc.contextWords.size(); i++)
    {
       os >> desc.targetWord >> c >>  desc.contextWords[i].word >> desc.contextWords[i].count;
    }
    os >> c;
*/