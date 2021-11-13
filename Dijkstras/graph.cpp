#include "graph.h"

using namespace std; 

int graph::showVals(const string &out)
{
    ofstream output;
    output.open(out);
    for (auto &x: nodes) 
    {
        output << x.vertexId << ": "; 

        //Display adjacent nodes
        // for (auto &y : x.adjacent)
        //     cout << y.dest << " ";

        //Display path
        string path;
        if (x.distance == INT_MAX)
        {
            path = "NO PATH";
            output << path << '\n';
            continue; 
        }

        output << x.distance << " [";
        graphNode* tmp = x.prev; 
        while(tmp != nullptr)
        {
            string breh = tmp->vertexId + ", ";
            path.insert(0, breh);
            tmp = tmp->prev;
        }
        path.append(x.vertexId);
        output << path << "]" << '\n'; 
    }

    output.close();
    return 0; 
}

int graph::insert(const string &nodeOne, const string &nodeTwo, int edgeCost)
{
    //Check if the two given nodes are in the graph already 
    //Insert them both to the nodes linked list if not
    if(!mapNodes.contains(nodeOne))
    {
        // cout << nodeOne << '\n';
        graphNode tmp; 
        tmp.vertexId = nodeOne; 
        nodes.push_back(tmp);

        mapNodes.insert(nodeOne, &nodes.back());
    }
    if(!mapNodes.contains(nodeTwo))
    {
        // cout << nodeTwo << '\n';
        graphNode tmp; 
        tmp.vertexId = nodeTwo; 
        nodes.push_back(tmp);

        mapNodes.insert(nodeTwo, &nodes.back());
    }

    graphNode* source = static_cast<graphNode *> (mapNodes.getPointer(nodeOne)); 

    edge tmp2; 
    tmp2.dest = nodeTwo; 
    tmp2.cost = edgeCost; 
    source->adjacent.push_back(tmp2);

    return 0; 
}

//Check if the starting vertex is a valid node in the graph
//Returns 1 if it is valid, 0 if invalid
int graph::isValid(const string &startId)
{
    if(!mapNodes.contains(startId))
        return 0;
    return 1; 
}

int graph::shortestPath(const string &startId)
{
    // string test = "test";

    //Set starting node given as a parameter
    graphNode* source = static_cast<graphNode *> (mapNodes.getPointer(startId)); 
    source->distance = 0; 
    source->known = true; 

    //Set up binary heap using number of nodes 
    //in the linked list as its size
    int n = nodes.size(); 
    heap unknown(n);

    unknown.insert(source->vertexId, source->distance, mapNodes.getPointer(startId));

    // unknown.showVals(test);
    // cout << tmp->vertexId << '\n';

    //Remove the unknown vertex with the smallest distance
    void* tmp; 
    int val; 
    string key; 
    while(!unknown.deleteMin(&key, &val, &tmp))
    {
        graphNode* v = static_cast<graphNode *> (tmp); 

        v->known = true; 
        for(auto &x : v->adjacent)
        {
            graphNode* w = static_cast<graphNode *> (mapNodes.getPointer(x.dest)); 
            if((v->distance + x.cost)< w->distance)
            {
                w->distance = v->distance + x.cost; 
                w->prev = v; 
                unknown.insert(w->vertexId, w->distance, mapNodes.getPointer(x.dest));
            }
        }
    }

    return 0; 
}