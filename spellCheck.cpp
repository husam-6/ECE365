#include "hash.h"
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void readInDict(string &dict, hashTable &table)
{
    string Line; 
    ifstream dictionary;
    dictionary.open(dict); 

    while(getline(dictionary, Line))
    {
        for (int i = 0; i < Line.length(); i++)
        {
            Line[i] = tolower(Line[i]);
        }

        table.insert(Line);
    }
    
    dictionary.close();


}


int main()
{   
    //Read in dictionary file and text file... 
    //Note: not checking if file is valid yet...
    string doc, dict;
    cout << "Enter the name of a dictionary text file:" << '\n';
	cin >> dict; 
	cout<< "Enter the name of a document to spell check:" << '\n';
	cin >> doc;

    hashTable table(1000);

    readInDict(dict, table);

    table.showVals(doc);

    return 0; 
}