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

tuple<string, int> split(string& line, int iterator)
{
    int nonChar = 0; 
    int j = iterator;
    while((isalnum(line[j]) || (line[j] == '\'') || (line[j] == '-'))==false)
    {
        nonChar++;
        j++;
    }

    string out = "";
    for(int i = iterator+nonChar; i<line.size(); i++)
    {
        if(isalnum(line[i]) || (line[i] == '\'') || (line[i] == '-'))
        {
            out+=line[i];
        }
        else
        {
            break; 
        }
    }

    return {out,nonChar}; 
}

int main()
{
    string test = "///////Um-deedledeedledeedle&////// um-deedleday";
    //string test = "/";
    auto [tmp, non] = split(test,0);
    cout << tmp << '\n';
    
    auto [tmp2, non2] = split(test, non+tmp.size());
    cout << tmp2 << '\n';

    //cout << split(test, tmp.size()+1) << '\n';
    return 0;
}