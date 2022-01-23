#include "SemanticDictionary.h"
#include "SemanticDescriptor.h"

double SemanticDictionary::getSimilarity(string targetWord1, string targetWord2)
{   
    //std::cout << "In double SemanticDictionary::getSimilarity(string targetWord1, string targetWord2)"<< std::endl;
    double similarity = -999;
    int i1 = searchTargetWord(targetWord1);
    //double a = searchTargetWord(targetWord1);
    int i2 = searchTargetWord(targetWord2);
    //double b = searchTargetWord(targetWord2);
    //std::cout << "a : " << a << " b : " << b << std::endl;
    if ((i1 == -1) || (i2 == -1))//target word is not found
    {
        throw runtime_error("Target word(s) unknown");
    }
    /*
    Access and store the SemanticDescriptors at the given indices
    Return the cosine similarity of the SemanticDescriptors using your * operator:
    */
   //semanticDescriptors[a] = targetWord1;
   //semanticDescriptors[b] = targetWord2;

   SemanticDescriptor a (semanticDescriptors[i1]);
   SemanticDescriptor b (semanticDescriptors[i2]);
   //std::cout << "targetWord1: " << targetWord1 << "  " << "targetWord2: " << targetWord2 << std::endl;

    //double fourth = (a * b);
    double fifth = a * a;
    double sixth = b * b;
    double first = sqrt(fifth);
    double second = sqrt(sixth);
    double third = first * second;
   //std::cout << "IN getSimilarity() : the equation is : " << fourth << " / " << third << std::endl;
   //std::cout << "fourth: " << fourth << " first : " << first << " second : " << second << " third : " << third << std::endl;
   //std::cout << "a " << a<< " " << "b" << b << std::endl;
   //similarity = (static_cast<double>(a*b) / ((sqrt(a*a))* (sqrt(b*b))));
   if(third != 0.0)
   {
       similarity = (static_cast<double>(a*b) / ((sqrt(a*a))* (sqrt(b*b))));
   }
   else
   {
      std::cout << "Can't divide by 0" << std::endl;//my flag
   }
   return similarity;
}

string SemanticDictionary::mostSimilarWord(string word, vector<string> choices)
{
    vector <double> similarity2;
    //double greater = 0.0;//to compare similarity values
    string returnedWord;
    double similarity = 0.0;
    double mostSimilar = 0.0;
    string theMostSimilar;
    for(size_t i = 0; i < choices.size(); i++)
    {
        similarity = getSimilarity(choices[i], word);
        if(similarity > mostSimilar)
        {
            mostSimilar = similarity;
            theMostSimilar = choices[i];
        }
    }
    //std::cout << "theMostSimilar: " << theMostSimilar <<std::endl;
    return theMostSimilar;
    //return choices[greater];//value in choices vector at index greater
}

int SemanticDictionary::searchTargetWord(string targetWord)
{
    //std::cout << "In int SemanticDictionary::searchTargetWord(string targetWord) 12 " << std::endl << std::endl;
//std::cout << "searchTargetWord semanticDescriptors.size() = " << semanticDescriptors.size() << std::endl;
    for (size_t i=0; i < semanticDescriptors.size(); i++)
    {
        //std::cout << "In for loop 13" << std::endl;
        //string cmpWord = SemanticDescriptor::getTargetWord();
        if(semanticDescriptors[i].getTargetWord() == targetWord)
        {
            //std::cout << "In 14 and i is : " << i << std::endl;
            return i;
        }
    }
    return -1;
}

void SemanticDictionary::processTargetWord(string targetWord, vector<string> sentenceList)
{
    int indexOfSd = searchTargetWord(targetWord);
    if (indexOfSd == -1)//targetWord is not found b/c if it was the indexSd would be THAT index and not -999
    {
        //std::cout << "In 8" <<std::endl;
        SemanticDescriptor sObj = SemanticDescriptor(targetWord);
        semanticDescriptors.push_back(sObj);
        //std::cout << "semanticDescriptors in processTargetWord: " << semanticDescriptors.size() << std::endl;
    }
//std::cout << "processTargetWord semanticDescriptors.size() is : " << semanticDescriptors.size() << std::endl;
    indexOfSd = searchTargetWord(targetWord);
    //std::cout << "The size of sentenceList is : " << sentenceList.size() << std::endl;
    for(size_t i=0; i < sentenceList.size(); i++)
    {
        if(sentenceList[i] != targetWord)
        {
            semanticDescriptors[indexOfSd].processContextWord(sentenceList[i]);
        }
    } 
}

ostream& operator<<(ostream& os, const SemanticDictionary& d)
{
    os << "Semantic Descriptors:" << std::endl;
    os << "{" << std::endl;
    
    for (size_t i=0; i < d.semanticDescriptors.size(); i++)//not sure about d.semanticDescriptors.size()
    {
        os <<  d.semanticDescriptors[i];//os << d.semanticDescriptors.at(i).targetWord << "{ " << d.semanticDescriptors[i] << /* the count */<< " }" << std::endl;//semanticDescriptors[i].SemanticDescriptor::getTargetWord()
    }
    os << "}" << std::endl;
    return os;
}

ostream& operator<<(ostream& os, const vector<vector<string>>& sentenceLists)
{
    //std::cout << "In ostream& operator<<(ostream& os, const vector<vector<string>>& sentenceLists)" << std::endl;
    os << "Sentence Lists: " << std::endl;
    os << "[ " << std::endl;
    for (size_t i =0; i < sentenceLists.size(); i++)
    {
        //std::cout << "In for loop in ostream& operator<<(ostream& os, const vector<vector<string>>& sentenceLists) 4 " << std::endl;
        os<< "[ ";
        for(size_t j=0; j < sentenceLists.at(i).size(); j++)
        {
            //std::cout << "In 5" << std::endl;
            os << " " << sentenceLists.at(i).at(j) << " ";
        }
        os << "]\n";
    }
    os << "]\n";
   // std::cout << "In 6" << std::endl;
   return os;
}
  /**
    os << "[" << std::endl;
    for (int i=0; i << sentenceLists.size(); i++) 
    {
        os << "[ " << sentenceLists[i] << " ]" << std::endl;
    }
    os << "]" << std::endl;
**/
bool isStopWord(string s)
{
    if (s == "I"||"a" || "about" || "an" || "are" || "as" || "at" || "be" || "by" || "for" || "from" || "how" || "in" || 
    "is" || "it" || "of" || "on" || "or" || "that" || "the" || "this" || "to" || "was" || "what" || "when" || "where" || 
    "who" || "will" || "with" || "the")
    {
        return true;
    }
    return false;
}
//This function will return a two-dimensional vector where each row represents a sentence and each column represents a word from that sentence
vector<vector<string>> getSentenceLists(string text)
{
    //std::cout << "In vector<vector<string>> getSentenceLists(string text) " << std::endl;
    bool stopWordResult = false;
    vector<vector<string>> sentenceLists;
    vector<string> sentenceList;
    string word = "";
    for(size_t i = 0; i < text.size(); i++)
    {
        //std::cout << "In for loop in 1" << std::endl;
        if(isalpha(text[i]))
        {
            word += tolower(text[i]);//word = word + text[i]
            //stopWordResult = isStopWord(word);//new
        }
        else
        {
            //if(word.size() > 0)
            stopWordResult = isStopWord(word);
            if(word.size() > 0)// && stopWordResult == false)//&& (stopWordResult == false) )//Add logic to getSentenceLists to only push_back a word if isStopWord returns false.
            {
                cout <<"y" <<endl;
                sentenceList.push_back(word);
                word = "";
            }
            if((text[i] == '?' || text[i] == '.' || text[i] == '!') && (sentenceList.size() > 0))
            {
                cout << "b" <<endl;
                sentenceLists.push_back(sentenceList);
                sentenceList.clear();
            }
        }
    }
    ///if the size of word > 0, push it back into sentenceList
    ///if the size of sentenceList > 0, push it back into sentenceLists
    
    if(word.size() > 0 && stopWordResult == false)
    {
        sentenceList.push_back(word);
    }
    if(sentenceList.size() > 0)
    {
        sentenceLists.push_back(sentenceList);
    }
    
    //std::cout << "In 2" << std::endl;
    //std::cout << "sentenceLists.size() = " << sentenceLists.size() << std::endl;
    return sentenceLists;
}

istream& operator>>(istream& is, SemanticDictionary& d)//SP M05-MO7
{
    //TODO:
    d.semanticDescriptors.clear();//Clear the vector of SemanticDescriptors for d to ensure there is no old data in it
    SemanticDescriptor sd("");//Construct a SemanticDescriptor with an empty string for its targetWord parameter
    //int i=0;
    char c = '0';
    //while(is >> d.semanticDescriptors[i])//(c != '{')//Extract one char at a time until you reach '{'.  This will read past the text at the top of the file and past the first '{'
    //is >> c;
   // while(is >> c)
    while (c != '{')
    {
        is >> c;
        cout << c;
        cout << "8" << endl;
        //is >> c;
    }
    size_t i =0;
 
    //while(i != d.semanticDescriptors.size())
    /*
    while(!(is.fail()))
    {
        cout << "12" << endl;
        d.semanticDescriptors.push_back(sd);
        is >> d.semanticDescriptors[i];
        i++;
    }
    */
    d.semanticDescriptors.push_back(sd);
  // while(is >> d.semanticDescriptors[i])
    while (is >> d.semanticDescriptors[i])
   {
       cout << "13" << endl;
       d.semanticDescriptors.push_back(sd);
       i++;
   }
cout << "99" << endl;
cout << "d.semanticDescriptors.size() = " << d.semanticDescriptors.size() << endl;//0

    is >> c;//Once the loop exits, read one more char
    cout << "14 c = " << c;
    if(c != '}')//If it is not the final '}', unget it and set the failbit
    {
        cout << "18" << endl;
        is.unget();
        //std::cout.setstate(std::ios::failbit);
        is.clear(ios_base::failbit);
        //std::cout << "Fail!\n";  
    }
    return is;
}



/////////////////////////////////////////////////////////


/*

 for (int i=0; i < similarity2.size(); i++)
    {
        if(i  = similarity2.size() -1)
        {

        }
    }

*/

  //i=0;
    /*
    while(is)//Use the SemanticDescriptor extraction operator >>, as defined above, in a loop to extract until it fails.
    {
        cout << "9" << endl;
       // d.semanticDescriptors.push_back(sd);//Inside the loop, push_back the SemanticDescriptor into d
        cout <<"10" << endl;
        is >> d.semanticDescriptors[i];
        cout << d.semanticDescriptors[i];
        cout << "11" << endl;
        //d.semanticDescriptors.push_back(sd);//Inside the loop, push_back the SemanticDescriptor into d
        i++;
    }
    */