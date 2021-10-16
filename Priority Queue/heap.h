#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <math.h>
#include <utility>
#include "hash.h" 

class heap 
{
    public: 
        //function to print values in the heap for debugging
        int showVals(std::string &out); 

        //constructor, takes in capacity
        heap(int maxSize);
        
        //Insert item into the heap
        //returns: 0 on success, 
        //         1 when the heap is full
        //         2 if a node exists with the given id (and not full)
        int insert(const std::string &id, int key, void* pv = nullptr);
        

        //Set key of given id to a new key
        //returns: 0 on success
        //         1 when the id doesn't exist
        int setKey(const std::string &id, int key);

        //Deletes min item, written to address of pid if provided
        //returns: 0 on success
        //         1 if heap is empty
        int deleteMin(std::string *pid = nullptr, int *pKey = nullptr, void *ppData = nullptr);

        //removes the specified id from the heap
        //write address of removed item to pKey if given
        //returns: 0 on success
        //         1 if a node with the given id is not in the heap
        int remove(std::string id, int *pKey = nullptr, void *ppData = nullptr); 

    private: 

        //Heap node nested class to store neccesary information for each heap item
        class heapNode
        {
            public: 
                std::string id {""}; 
                int key; 
                void* pData {nullptr}; 

                heapNode() = default;
        };

        void percolateUp(int pos);
        void percolateDown(int pos);
        int getPos(heapNode *pn);
        
        int capacity; 
        int size; 
        std::vector<heapNode> nodes; 

        hashTable idMappings;

};


#endif