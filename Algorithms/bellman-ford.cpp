#include <iostream>
#include <vector>
#include <queue>
#include<string>
#include <fstream>
#include <iomanip>  
#include<numeric>  

auto op = 0;

using namespace std;
    
// Given an Adjacency List, find all shortest paths from "start" to all other vertices.
vector<int> BellmanFordSP(vector< vector<pair<int, int> > > &adjList, int &start){
    cout << "\nGetting the shortest path from " << start << " to all other nodes.\n";
    vector<int> dist;

    // Initialize all source->vertex as infinite.
    int n = adjList.size();
    for(int i = 0; i < n; i++){
      dist.push_back(1000000007); // Define "infinity" as necessary by constraints.
    }
        
    dist[start] = 0;    
    
    // Then calculate the shortest distance using...
    // For numNodes-1...
    for(int i = 0; i < n-1; i++){
        // For each node (u)...
        for(int u = 0; u < n; u++){
            // For each of it's neighbors (v)...
            for(int j = 0; j < adjList[u].size(); j++){
                int v = adjList[u][j].first;
                int weight = adjList[u][j].second;
                op++;  
                // If the distance from source to v is bigger than dist[u] + weight of (u,v)...
                if(dist[v] > dist[u] + weight){
                    // Update dist[v] to dist[u] + weight(u,V)
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }            
    // If there's a negative weight cycle in the graph, then report it, by...
    // For each node (u)...
        // For each of u's neighbors (v)...
            // Check if it's possible to get even better (now, that we should be at shortest)
            // If the distance from source to v is bigger than dist[u] + weight of (u,v)...
                // Report problem.
    
    return dist;
}
    
void PrintShortestPath(vector<int> &dist, int &start){
    string str = "Bellman-Ford_Results_Test_.txt";
    string size = to_string(dist.size());
    str.insert(26, size);
    ofstream MyFile(str);
    MyFile << "Printing the shortest paths for node "<< start <<endl;
    for(int i = 0; i < dist.size(); i++){
        if(dist[i]==1000000007){continue;}
        MyFile << "The distance from node " << start << " to node " << i << " is: " << dist[i] << endl;   
    }
    cout << "Total of operations: " << op <<endl;
    MyFile << "Total of operations: " << op <<endl;
}
    
int main(int argc, char** argv){

    time_t start, end;
    time(&start);

    cout << "Program started.\n";
    
    // Our adjacency list.
    vector< vector<pair<int, int> > > adjList;
    vector< pair <int,int> > vPairs;
    
    int n, c, r;
    cin >> n;

    //Vector with the number of edges for every node
    vector<int> appearance; 
    int value;  
    for(int i = 0; i < n; i++){
        cin >> value;
        appearance.push_back(value);
    }


    //Check if the input is correct
    try{
      if(n != appearance.size()) throw "The size of the array appearence is not the same as the number of Nodes";
    }
    catch(char * str){
      cout << "Exception: " << str << endl;
      exit(0);
    }

    //Check if the input is correct
    try{
    cin >> c;
    cin >> r;
    if(c!=2) throw c;
    if(r!= accumulate(appearance.begin(),appearance.end(),0)) throw r;
    }
    catch(int e){
      cout << "Wrong input file"<< endl;
      exit(0);
    }

    //Create a vector with all the pair values
    vector<int> inputMatrix;
    int k;
    int rsqr = r*2;

    for (int i = 0; i < rsqr; i++){
        cin>> k;
        inputMatrix.push_back(k); 
    }

    int range2 = rsqr;
    //The first int is the vertex of the friend, the second int is the edge weight.
    for (int i = 0, j = 1; i < rsqr ; i++, j++){
      //cout << inputMatrix[j];
      vPairs.push_back(make_pair(inputMatrix[i],inputMatrix[j]));
      i++; j++;
    }

    for(int i = 0; i < n; i++){
      vector<pair<int, int> > row;
      adjList.push_back(row);
    }

    //Each adjList[i] holds a all the friends of node i.
    int p = 0;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < appearance[i]; j++){
        adjList[i].push_back(vPairs[p]);
        p++;
        }  
    // Get a list of shortest path distances for node 0.
    int node = 0;
    vector<int> dist = BellmanFordSP(adjList, node);
    
    // Print the vector
    PrintShortestPath(dist, node);

    time(&end);

    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(10);
    cout << " sec " << endl;
    
    cout << "Program ended.\n";
    
    return 0;
}