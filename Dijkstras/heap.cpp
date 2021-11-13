#include "heap.h"

using namespace std;

/*
    Husam Almanakly - DSA 2 Program 2

    This program implements a binary heap datastructure using the hash map class implemented in project 1. 
    The heap supports the functions insert, deleteMin, setKey, and remove implemented using average 
    case logarithmic time. 


*/

int heap::showVals(string &out)
{
    // std::ofstream output;
    // output.open(out);

    for(int i = 0; i<nodes.size(); i++)
    {
        // output<< i << "      " << nodes[i].id << '\n';
        cout << nodes[i].key << "       " << nodes[i].id << '\n';
    }
    // output.close();
    return 0; 
}

heap::heap(int maxSize):idMappings(maxSize*2)
{
    capacity = maxSize;
    size = 1; 
    nodes.resize(maxSize+1); 
    // nodes.resize(capacity);
}


//Function to percolate up 
void heap::percolateUp(int pos)
{
    heapNode tmp = nodes[pos];
    int tmpKey = tmp.key; 
    // cout << tmpKey << '\n';

    for(; tmpKey<nodes[pos/2].key; pos = pos/2)
    {
        if(pos == 1)
            break;
        // cout << pos << '\n';
        // tmpKey = nodes[pos/2].key;
        nodes[pos] = nodes[pos/2];
        idMappings.setPointer(nodes[pos].id, &nodes[pos]);
    }
    nodes[pos] = tmp;
    idMappings.setPointer(nodes[pos].id, &nodes[pos]);
}

//Function to percolate down
void heap::percolateDown(int pos)
{
    heapNode tmp = nodes[pos];  
    
    // cout << "delete called" << '\n';
    int smallChild;
    for( ; 2*pos<=size-1; pos=smallChild)
    {   
        smallChild = 2*pos; 
        // cout << smallChild << "         " << tmp.key << '\n';
        if(smallChild < size-1 && nodes[smallChild+1].key < nodes[smallChild].key)
            smallChild++;
        
        if(nodes[smallChild].key < tmp.key)
        {
            // cout << smallChild << '\n';
            nodes[pos] = nodes[smallChild];
            // cout << nodes[pos].key <<  '\n';
            idMappings.setPointer(nodes[pos].id, &nodes[pos]);
        }
        else
            break; 
    }
    

    nodes[pos] = tmp; 
    idMappings.setPointer(nodes[pos].id, &nodes[pos]);
}

int heap::insert(const string &id, int key, void* pv)
{   
    //Check exit conditions
    if (size-1 == capacity)
        return 1;
    else if (idMappings.contains(id))
        return 2; 


    //Create a node object with all the info needed/inputted
    //add it to the nodes vector
    heapNode tmp; 
    tmp.id = id; 
    tmp.key = key; 
    if (pv != nullptr)
        tmp.pData = pv; 
    
    //Percolate up or not
    nodes[size] = tmp; 
    
    //Add the key and its index to the mappings hash map
    idMappings.insert(id, &nodes[size]);
    
    int hole = size; 
    size++; 

    
    // hole = percolateUp(hole, tmpKey);
    percolateUp(hole);
    // nodes[hole] = tmp;


    return 0; 
}

int heap::getPos(heapNode *pn)
{
    int pos = pn - &nodes[0];
    return pos;
}


int heap::deleteMin(std::string *pid, int *pKey, void *ppData)
{
    if(size == 1)
        return 1; 
    if(pid!=nullptr)
        *pid = nodes[1].id;
    if(pid!=nullptr)
        *pKey = nodes[1].key;
    if(ppData != nullptr)
        *(static_cast<void **> (ppData)) = nodes[1].pData;


    //Delete last node and move to the root
    idMappings.remove(nodes[1].id);
    nodes[1] = nodes[size-1];
    nodes[size-1] = heapNode(); 
    size--;
    // cout << size << '\n';
    percolateDown(1);


    return 0; 

}

int heap::setKey(const std::string &id, int key)
{   
    if(idMappings.contains(id) == false)
        return 1; 
    
    heapNode* object = static_cast<heapNode *> (idMappings.getPointer(id)); 

    int tmp = object->key; 
    object->key = key; 

    int pos = getPos(object);

    // cout << "KEY CHANGED: " << object->key << '\n';
    // cout << pos << '\n';

    if(tmp>key)
        percolateUp(pos);
    else if(tmp<key)
        percolateDown(pos);

    return 0; 
}


int heap::remove(std::string id, int *pKey, void *ppData)
{
    if(idMappings.contains(id) == false)
        return 1; 
    
    heapNode* object = static_cast<heapNode *> (idMappings.getPointer(id)); 
    
    if(pKey!=nullptr)
        *pKey = object->key; 
    if(ppData != nullptr)
        *(static_cast<void **> (ppData)) = object->pData;

    
    setKey(id, nodes[1].key-1);
    deleteMin();
    
    return 0; 

}
