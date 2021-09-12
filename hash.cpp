#include "hash.h"
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std; 

//Constructor -> initialize the size using getPrime and make every entry a default hashItem()
//Capacity gets the size of the vector
//seems to be working...
hashTable::hashTable(int size)
{
    int newSize = getPrime(size);
    data.resize(newSize);
    capacity = newSize; 
    filled = 0; 
    for(auto& entry: data)
    {
        entry = hashItem();
    } 
}

//insert function -> check if key exists, if it does - linear probing
//else, insert 
//seems to work NEED TO MAKE LOWERCASE
int hashTable::insert(const string &key, void *pv)
{
    int returnVal = 0;
    filled++; 
    //cout<<double(filled)/double(capacity)<<'\n';
    if((double(filled)/double(capacity))>0.75) 
    {
        bool fail = rehash(); 
        if(fail)
        {
            returnVal = 2; 
        }
    }
    int pos = hash(key);
    if(contains(key))
    {
        returnVal = 1;
        while(data[pos].isOccupied)
        {
            if(pos==capacity-1)
            {
                pos = 0; 
            }
            else
            {
                pos++; 
            }
        }
    }
    data[pos].key = key; 
    data[pos].isOccupied = true; 

    return returnVal; 
}

void hashTable::showVals()
{
    for(int i = 0; i<data.size(); i++)
    {
        cout<< i << "      " << data[i].key << '\n';
    }
}
//Contains function -> checks if the hash table has a hashItem object 
//occupying that position
bool hashTable::contains(const string &key)
{
    int position = hash(key);
    if(data[position].isOccupied)
    {
        return true; 
    }
    return false; 
    
}

//didnt really test, dont need for proj 1
//Lazy delete for linear probing
bool hashTable::remove(const string &key)
{
    int tmp = findPos(key);
    if(tmp>0)
    {
        data[tmp].isDeleted = true; 
        return true; 
    }
    return false; 
}


//seems to work 
//Hash function -> from https://stackoverflow.com/questions/7700400/whats-a-good-hash-function-for-english-words
int hashTable::hash(const string &key)
{
    int hash = 5381;
    char c;

    for(int i = 0; i<key.size(); i++)
        c = key[i];
        hash = ((hash << 5) + hash) + c; /* hashNum * 33 + c */

    return hash%capacity;
}

//Goes to the hashed position and linearly searches for the given
//key until it is either found or an 'empty' box is reached
int hashTable::findPos(const string &key)
{
    int pos = hash(key);
    while(data[pos].isOccupied)
    {
        if(data[pos].key == key && data[pos].isDeleted == false)
        {
            return pos; 
        }
        else
        {
            pos++; 
        }
    }
    return -1;
}

bool hashTable::rehash()
{
    int newSize = getPrime(capacity);
    //cout<<newSize<< "   " << capacity << '\n';
    vector<hashItem> tmp = data; 

    for(int i = 0; i<capacity; i++)
    {
        data[i].key = "";
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }
    filled = 0;  

    try
    {
        data.resize(newSize);
    }
    catch(const bad_alloc &error)
    {
        return false; 
    }
    capacity = newSize;

    for(auto& x : tmp)
    {
        insert(x.key);
    }

    //data = tmp; 
    return true; 
}

//works, gives a prime number at least as large as the given size
unsigned int hashTable::getPrime(int size = 0)
{
    int primeNums[11] = {11, 20, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469};
    for(int i = 0; i<11; i++)
    {
        if(primeNums[i]>size)
        {
            return primeNums[i];
        }
    }
    return primeNums[10];
}