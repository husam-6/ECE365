#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include "heap.h"
#include "hash.h"
#include <list>

class graph
{
    public: 
        graph() = default; 

        //Function to insert a node into the graph
        int insert(const std::string &nodeOne, const std::string &nodeTwo, int edgeCost);

        //function to print or write vertices and distances to a given file
        int showVals(const std::string &out); 
        
        //Function to conduct Dijkstras Algorithm given a starting index id
        int shortestPath(const std::string &startId);

        //Function to check if the starting vertex is a valid node
        //Returns 0 if the given key is invalid, 1 if valid
        int isValid(const std::string &startId); 
    
    private:
        class edge
        {
            public:
                int cost = 0; 
                std::string dest = "";

                edge() = default; 
        };

        class graphNode
        {
            public: 
                std::string vertexId = ""; 
                std::list<edge> adjacent; 
                int distance = INT_MAX; 
                graphNode* prev = nullptr;
                bool known = false; 

                graphNode() = default; 

        };
        std::list<graphNode> nodes; 
        hashTable mapNodes;
};


#endif


