#include <iostream>
#include <vector>
#include <queue>
#include<string>
#include <fstream>
#include <iomanip>  

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
    ofstream MyFile("Resultados_Test.txt");
    MyFile << "Printing the shortest paths for node "<< start <<endl;
    for(int i = 0; i < dist.size(); i++){
        op++;
        if(dist[i]==1000000007){continue;}
        MyFile << "The distance from node " << start << " to node " << i << " is: " << dist[i] << endl;   
    }
    cout << "Total of operations: " << op <<endl;
    MyFile << "Total of operations: " << op <<endl;
}
    
int main(){

    time_t start, end;
    time(&start);

    cout << "Program started.\n";
    
    // Our adjacency list.
    vector< vector<pair<int, int> > > adjList;
    vector< pair <int,int> > vPairs;
    
    int n, c, r;
    cin >> n;

    int appearance[n];

    for (int i = 0; i < n; i++){
        cin >> appearance[i];
    }

    cin >> c;
    cin >> r;

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
    
    // Print the list.
    PrintShortestPath(dist, node);

    time(&end);

    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(10);
    cout << " sec " << endl;
    
    cout << "Program ended.\n";
    
    return 0;
}