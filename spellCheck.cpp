#include "hash.h"
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;

string toLower(string &line)
{
    for (int i = 0; i < line.length(); i++)
    {
        line[i] = tolower(line[i]);
    }
    return line; 
}

void readInDict(string &dict, hashTable &table)
{
    string line; 
    ifstream dictionary;
    dictionary.open(dict); 

    while(getline(dictionary, line))
    {
        line = toLower(line);

        table.insert(line);
    }
    
    dictionary.close();
}

string split(string& line, int iterator)
{
    string out = "";
    for(int i = iterator; i<line.size(); i++)
    {
        if(isalnum(line[i]) | (line[i] == '\'') | (line[i] == '-'))
        {
            out+=line[i];
        }
        else
        {
            break; 
        }
    }
    return out; 
}

bool hasDigits(string& word)
{
    for (int i = 0; i < word.size(); i++)
    {
        if(isdigit(word[i]))
        {
            return true;
        }
    }
    return false;
}

void spellCheck(string &doc, string &out, hashTable &table)
{
    string line; 
    ifstream document;
    ofstream output; 
    output.open(out);
    document.open(doc);
    
    int lineNumber = 1; 
    while(getline(document, line))
    {
        //make the entire line lowercase, build
        //the word limiting it to 20 chars 
        line = toLower(line);

        int i = 0;
        while(i<line.size())
        {
            string word; 
            word = split(line, i);
            //cout << word << '\n'; 
            if(word == "")
            {
                break; 
            }
            i += word.size()+1;

            if(hasDigits(word))
            {
                continue; 
            }

            if(word.size()>20)
            {
                //write error
                output << "Long word at line " << lineNumber << ", starts: " << word.substr(0,20) << '\n';
                continue;  
            }
            else
            {
                if(table.contains(word) == false)
                {
                    //word not recognized 
                    output << "Unknown word at line " << lineNumber << ": " << word << '\n';
                    continue; 
                }   
            }
        }
        lineNumber++;
    } 
}

int main()
{   
    //Read in dictionary file and text file... 
    //Note: not checking if file is valid yet...
    string doc, dict, output;
    hashTable table(1000);
    cout << "Enter the name of a dictionary text file: ";
	cin >> dict; 
    
    auto start = high_resolution_clock::now();
    readInDict(dict, table);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Time taken to read in Dictionary (in seconds): " << double(duration.count())/(pow(10,6)) << '\n';

    //spell check the document and report time
	cout<< "Enter the name of a document to spell check: ";
	cin >> doc;
    cout << "Enter the name of an output file: ";
    cin >> output;

    auto start2 = high_resolution_clock::now();
    spellCheck(doc, output, table);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout<<"Time taken to spell check the document (in seconds): " << double(duration2.count())/(pow(10,6)) << '\n';

    //table.showVals(output);

    return 0; 
}