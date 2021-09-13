#include "hash.h"
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std; 

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

int main()
{
    string test = "Um-deedledeedledeedle um-deedleday1";

    cout << std::boolalpha;   

    cout<< hasDigits(test) << '\n';
    return 0;
}