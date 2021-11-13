#include "graph.h"

using namespace std; 

//function to get the number of seconds 
double getCpuTime() {
    return (double) clock() / CLOCKS_PER_SEC;
}

//function reads in the text file and creates the graph
//Inserts nodes and edges in respective locations ie
//linked list for nodes and adjacency list for edges
void readInGraph(string &textFile, graph &outGraph)
{
    string line; 
    ifstream graphFile;
    graphFile.open(textFile); 

    while(getline(graphFile, line))
    {
        string strOne, strTwo, tmp; 
        int cost; 
        
        stringstream iss(line);
    
        iss >> strOne; 
        iss >> strTwo;
        iss >> cost; 

        outGraph.insert(strOne, strTwo, cost);
    }
    
    graphFile.close();
}


int main()
{
    graph vertices; 
    string fileName, start, out; 

    //Prompt user for input text file representing graph
    //Open the file, insert each vertex and edge into the graph class
    cout << "Enter a graph text file: ";
	cin >> fileName; 
    readInGraph(fileName, vertices);

    //Prompt for starting point
    cout << "Enter the starting vertex: ";
    cin >> start; 
    while(!vertices.isValid(start))
    {
        cout << "Please enter a valid vertex: ";
        cin >> start; 
    }

    //Track timing of Dijktras Algorithm
    double startTime = getCpuTime();
    vertices.shortestPath(start);
    double end = getCpuTime();
    double duration = end-startTime;
    cout<<"Time taken to apply Dijkstra's Algorithm (in seconds): " << duration << '\n';

    //Prompt user for an output file
    cout << "Enter the name of an output file: "; 
    cin>>out; 
    vertices.showVals(out); 

    return 0; 
}