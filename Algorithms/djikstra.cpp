#include <iostream>
#include <vector>
#include <queue>
#include<string>
#include <fstream>
#include <iomanip> 
#include<numeric>  

auto op = 0;

using namespace std;

// An adjacency list. Each adjList[i] holds a all the friends of node i.
// The first int is the vertex of the friend, the second int is the edge weight.

    
// Given an Adjacency List, find all shortest paths from "start" to all other vertices.
vector<int> DijkstraSP(vector< vector<pair<int, int> > > &adjList, int &start){
    cout << "\nGetting the shortest path from " << start << " to all other nodes.\n";
    vector<int> dist;
    
    // Initialize all source->vertex as infinite.
    int n = adjList.size();
    for(int i = 0; i < n; i++){
        dist.push_back(1000000007); // Define "infinity" as necessary by constraints.
    }
        
    // Create a PQ.
    priority_queue<pair<int, int>, vector< pair<int, int> >, greater<pair<int, int> > > pq;
    
    // Add source to pq, where distance is 0.
    pq.push(make_pair(start, 0));
    dist[start] = 0;
    
    // While pq isn't empty...
    while(pq.empty() == false){
      // Get min distance vertex from pq. (Call it u.)
      int u = pq.top().first;
      pq.pop();
        
      // Visit all of u's friends. For each one (called v)....
      for(int i = 0; i < adjList[u].size(); i++){
        int v = adjList[u][i].first;
        int weight = adjList[u][i].second;
            
        // If the distance to v is shorter by going through u...
        if(dist[v] > dist[u] + weight){
          // Update the distance of v.
          dist[v] = dist[u] + weight;
          // Insert v into the pq. 
          pq.push(make_pair(v, dist[v]));
        }
      }
    }
    
    return dist;
}

void PrintShortestPath(vector<int> &dist, int &start){
    string str = "Dijkstra_Results_Test_.txt";
    string size = to_string(dist.size());
    str.insert(22, size);
    ofstream MyFile(str);
    MyFile << "Printing the shortest paths for node "<< start <<endl;
    for(int i = 0; i < dist.size(); i++){
        op++;
        if(dist[i]==1000000007){continue;}
        MyFile << "The distance from node " << start << " to node " << i << " is: " << dist[i] << endl;   
    }
    cout << "Total of operations: " << op <<endl;
    MyFile << "Total of operations: " << op <<endl;
}
    
int main(int argc, char** argv) {

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
      vPairs.push_back(make_pair(inputMatrix[i],inputMatrix[j]));
      i++; j++;
    }

    for(int i = 0; i < n; i++){
      vector<pair<int, int> > row;
      adjList.push_back(row);
    }

    //Each adjList[i] holds a all the friends of node i.
    int p = 0;
    for(int i = 0; i < n; i++){
      for(int j = 0; j <  appearance.at(i); j++){
        adjList[i].push_back(vPairs[p]);
        p++;
      }
    }
    // Get a list of shortest path distances for node 0.
    int node = 0;
    vector<int> dist = DijkstraSP(adjList, node);
    
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