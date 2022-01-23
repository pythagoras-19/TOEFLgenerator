#include "SemanticDictionary.h"
#include "SemanticDescriptor.h"
#include <chrono>
using std::chrono::milliseconds;
using namespace std;

void printMenu()
{
    cout << "1.  Read the semantic dictionary from storage" << endl;
    cout << "2.  Write the semantic dictionary to storage" << endl;
    cout << "3.  Read and process a text file (get smarter!)" << endl;
    cout << "4.  Solve a TOEFL question" << endl;
    cout << "5.  Quit" << endl;
    cout << "> ";
}

int main()
{
    SemanticDictionary semanticDictionaryObj;//declare SemanticDictionary object
    string choice;//declare string for menu choice
    string dictionaryFilename = "SemanticDictionary.txt";//declare and assign a string for the dictionary file name

    cout << "Welcome to the similarity checker!" << endl;//output some kind of welcome message
    printMenu();//print the menu
    cin >> choice;//input the menu choice

    while (choice != "5")//while not quit
    {
        if(choice == "1")//if 1
        {
            cout << "Reading from " << dictionaryFilename << endl;//output that you are reading the dictionary file
            //cout << "4" << endl;
            ifstream ifObj;//(dictionaryFilename);//construct ifstream object and open the file
            //cout << "5" << endl;
            ifObj.open(dictionaryFilename);
            //cout << "6" << endl;
            if(ifObj.is_open())
            {
                //cout << "7" << endl;
                //cout << "semanticDictionaryObj is = " << semanticDictionaryObj << endl;
                ifObj >> semanticDictionaryObj;//extract from ifstream object into your dictionary object
                cout << "Done reading " << dictionaryFilename << endl;//output that you are done reading
            }
            else
            {
                cout << "Error!" << endl;//error message
                cout << "Could not open " << dictionaryFilename << endl;
            }
        }
        else if(choice == "2") //else if 2
        {
            char proceed = '0';
            //warn the user that this will overwrite the previous file, ask if they want to proceed
            cout << "WARNING: this will overwrite previous file do you want to proceed?" << endl;
            cout << "Enter 1 for yes and 0 for no : " << endl;
            cin >> proceed;
            if (proceed == '0')
            {
                cout << "Exiting write operation" << endl;
            }
            else if (proceed == '1')//if proceed
            {
                cout << "Saving dictionary to SemanticDictionary.txt" << endl;//output that you are writing the dictionary to a file
                //cout << "1" << endl;
                ofstream myFile;//declare and open ofstream object
                myFile.open(dictionaryFilename);
                myFile << semanticDictionaryObj;//insert from the dictionary object into the ofstream object
                //myFile <<
                cout << "Done writing. " << endl;//output that you are done writing
            }
            else
            {
                cout << "Invalid proceed choice" << endl;
            }
        }
        else if(choice == "3")//else if 3
        {
            string fileName; //= "Tolkien.txt";//declare variable for file name
            cout << "Input filename:" ;//prompt and input file name
            cin >> fileName;
            ifstream inFile;//construct ifstream object and open the file
            inFile.open(fileName);
            if(!(inFile.is_open()))//if failed
            {
                cout << "Error!" << endl;//error message
                cout << "Could not open " << fileName << endl;
            }
            else //else
            {
                cout << "Processing..." << endl;//output that you are processing the file
                auto start = std::chrono::high_resolution_clock::now(); //code to record time elapsed
                string allOfText;//declare a variable to hold all of the text
                string wordInFile;
                string line;
                ofstream myOut2;
                myOut2.open("cool.txt");
               // while (inFile >> fileName)//loop to read every word in the file.  Concatenate each word onto text, separated by " "
                //while(getline(inFile, line))
                while(inFile >> wordInFile)
                {
                    //allOfText = wordInFile + " ";
                    allOfText+= wordInFile + " ";
                    //myOut2 << line << endl;
                    //myOut2 << allOfText << endl;
                }
               // ofstream myOut;
               // myOut.open("coool.txt");
                //myOut << allOfText << endl;
                vector<vector<string>>listSentences = getSentenceLists(allOfText);//pass text into getSentenceLists.  (This is a copy paste from the last project)
               
                //Create a double for loop to loop through each word of each sentenceList in sentenceLists and 
                //    process the target word.  (This is also a copy paste from the last project)
                cout << "Processing target word in 3" << endl;
                cout << "listSentences.size() = " << listSentences.size() << endl;
                cout << "listSentences[0].size() = " << listSentences[0].size() << endl;
                for (size_t i=0; i < listSentences.size(); i++)
                {
                    for(size_t j=0; j < listSentences.at(i).size(); j++)
                    {
                        semanticDictionaryObj.processTargetWord(listSentences.at(i).at(j), listSentences.at(i));
                    }
                }
                auto stop = std::chrono::high_resolution_clock::now();  //code to record time elapsed
                auto duration = std::chrono::duration_cast<milliseconds>(stop - start);
                cout << "Done.  Time elapsed: " << duration.count() << " milliseconds" << endl;
                //inFile.close();//ME
            }
        }
        else if(choice == "4")//else if 4
        {
            cout << "Enter a TOEFL question as <word> <answer> <choice1> <choice2> <choice3>:" << endl;
            string word, answer, choice1, choice2, choice3;
            cin >> word >> answer >> choice1 >> choice2 >> choice3;

            try
            {
                string s = semanticDictionaryObj.mostSimilarWord(word, vector<string>{choice1, choice2, choice3});
                cout << "Most similar: " << s << endl;
                cout << "Index: " << semanticDictionaryObj.getSimilarity(word, s) << endl;
                if(s == answer) cout << "Correct answer." << endl;
                else cout << "Incorrect answer." << endl;
            }
            catch(runtime_error& e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            cout << "Invalid menu choice" << endl;
        }

        //print the menu
        cout << "1.  Read the semantic dictionary from storage" << endl;
        cout << "2.  Write the semantic dictionary to storage" << endl;
        cout << "3.  Read and process a text file (get smarter!)" << endl;
        cout << "4.  Solve a TOEFL question" << endl;
        cout << "5.  Quit" << endl;
        cout << "> ";
        //cout << "Enter next choice: " << endl;
        cin >> choice;//input the menu choice
    }
    
    return 0;
}
/*
int main()
{
    SemanticDictionary d;

    string text;
    cout << "Type a paragraph followed by a newline to build semantic descriptors:" << endl;
    //getline(cin, text);
    text = "She was vexed, irritated and angry with his actions!!! He was annoyed and irritated as well, wishing he could explain to her how angry he was.  The dog was amused - gleefully tearing the couch apart and sprinting around the room...  The cat was frightened, trying to hide under the couch that the dog was destroying.";

    vector<vector<string>> sentenceLists = getSentenceLists(text);
    //cout << "In 3" << endl;
    cout << sentenceLists << endl;

    for(vector<string> sentenceList : sentenceLists)
        for(string targetWord : sentenceList) d.processTargetWord(targetWord, sentenceList);
    //cout << "In 11" << endl;
    cout << d << endl;

    cout << "Enter a TOEFL question as <word> <answer> <choice1> <choice2> <choice3>:" << endl;
    string word, answer, choice1, choice2, choice3;
    cin >> word >> answer >> choice1 >> choice2 >> choice3;

    try
    {
        string s = d.mostSimilarWord(word, vector<string>{choice1, choice2, choice3});
        cout << "Most similar: " << s << endl;
        cout << "Index: " << d.getSimilarity(word, s) << endl;
        if(s == answer) cout << "Correct answer." << endl;
        else cout << "Incorrect answer." << endl;
    }
    catch(runtime_error& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
*/