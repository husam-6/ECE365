#include "heap.h"

using namespace std;

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


//NOTE: Seems to be working, 
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

//NOTE: Seems to be working
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

//NOTE: seems to be working
int heap::insert(const string &id, int key, void* pv)
{   
    //Check exit conditions
    if (size == capacity)
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
    int hole = size; 
    size++; 
    
    // hole = percolateUp(hole, tmpKey);
    percolateUp(hole);
    // nodes[hole] = tmp;

    //Add the key and its index to the mappings hash map
    idMappings.insert(id, &nodes[hole]);

    return 0; 
}

//Works
int heap::getPos(heapNode *pn)
{
    int pos = pn - &nodes[0];
    return pos;
}


//NOTE: seems to be working as well
int heap::deleteMin(std::string *pid, int *pKey, void *ppData)
{
    if(size == 1)
        return 1; 
    if(pid!=nullptr)
        pid = &nodes[1].id;
    if(pid!=nullptr)
        pKey = &nodes[1].key;
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

//NOTE: Seems to be working
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


//NOTE: Seems to be working
int heap::remove(std::string id, int *pKey, void *ppData)
{
    if(idMappings.contains(id) == false)
        return 1; 
    
    heapNode* object = static_cast<heapNode *> (idMappings.getPointer(id)); 
    if(pKey!=nullptr)
        pKey = &object->key; 
    if(ppData != nullptr)
        *(static_cast<void **> (ppData)) = object->pData;

    // cout<<"Changing "<<nodes[0].key<<'\n';
    setKey(id, nodes[1].key-1);
    deleteMin();
    // cout<<"Changed to 69"<<'\n';
    return 0; 

}
