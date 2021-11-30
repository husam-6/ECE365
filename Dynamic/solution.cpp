#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

/*
    Husam Almanakly - DSA 2 Project 4

    This program implements a Dynamic Programming Algorithm that 
    checks if a set of strings and a proposed "merge" is valid. 
    A merge is defined as a string in which the letters from each word 
    is present, and the order of each string is maintained. This 
    algorithm utilizes a Bottom-Down Strategy to keep track of all the 
    valid merges, and walks back up the array to output the 'separated'
    words in the final answer. If the word is not a valid string, the 
    program outputs "*** NOT A MERGE ***".


*/


using namespace std; 

//Boolean matrix to check if the given merge is valid
//Initialized to maximum size
int check[1001][1001];

//Function to check if the merge is valid
//returns: 1 if valid
//         0 if not
string isValidMerge(const string &first, const string &second, string &merged)
{
    if ((first.size()+second.size())!=merged.size())
        return "*** NOT A MERGE ***"; 

    //Counter for rows => first string
    for(int i = 0; i < first.size()+1; i++)
    {
        //Counter for columns => second string
        for(int j = 0; j< second.size()+1; j++)
        {
            //If its the first item its always valid
            if(j == 0 && i == 0)
                check[i][j] = 1; 
            
            // If its a tie you take the one that occured last (adjacent above or to the right)
            else if ((first[i-1] == merged[i+j-1]) && (second[j-1] == merged[i+j-1]))
                check[i][j] = check[i][j-1] || check[i-1][j];
            
            //If its in only in the first, trail continues down
            else if (first[i-1] == merged[i+j-1])
                check[i][j] = check[i-1][j];
            
            //if its only in the second, trail continues right
            else if (second[j-1] == merged[i+j-1])
                check[i][j] = check[i][j-1];
        }
    }

    string outStr = merged; 
    if(check[first.size()][second.size()])
    {
        int i = first.size()+1;
        int j = second.size()+1;
        
        while((i >= 0 && j >= 0))// && mergeIdx>=0)
        {
            if(check[i][j-1])
            {
                outStr[i+j-1] = merged[i+j-1];
                j--;
            }
            else
            {
                char tmp = toupper(merged[i+j-1]);
                outStr[i+j-1] = tmp;
                i--;
            }
        }
        return outStr;     
    }
    else
        return "*** NOT A MERGE ***"; 
}

// Function to parse and evaluate input/output text
void parseIn(string inTxt, string outTxt)
{ 
    ifstream inp;
    ofstream output;
    
    inp.open(inTxt); 
    output.open(outTxt);

    string strOne, strTwo, merge; 
    while(inp >> strOne >> strTwo >> merge)
    {
        // memset(check, 0, sizeof(check)); 
        for(int i = 0; i<strOne.size()+1; i++)
        {
            for (int j = 0; j < strTwo.size()+1; j++)
                check[i][j] = 0; 
        }
        // cout << strOne << '\t' << strTwo << '\t' << merge << '\n';
        string tmp = isValidMerge(strOne, strTwo, merge);
        output << tmp << '\n';
    }
    
    inp.close();
}


int main()
{   
    string inTxt, outTxt; 

    //Prompt user for input text file
    //Open the file, evaluate each line
    cout << "Enter the name of the input text file: ";
	cin >> inTxt;
    cout << "Enter the name of the output text file: " ;
    cin >> outTxt;

    //Send text file names to be parsed and evaluated
    parseIn(inTxt, outTxt);

    return 0; 
}