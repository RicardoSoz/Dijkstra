#include <iostream>
#include<string> // for string class
#include <fstream>
#include <cstdlib>
#include<vector>
#include<numeric>
#include <cmath>
#include <ctime>

using namespace std;

void createGraph(int nodes, int edges, int nTest);

int main(){
  int nodes, edges, nTest;
  cin >> nodes;
  cin >> edges;
  cin >> nTest;
  createGraph(nodes, edges, nTest);
  return 0;
}

void createGraph(int nodes, int edges, int nTest){
    string test = "Test_" + to_string(nTest) + ".txt";
    ofstream MyFile(test);
    srand((unsigned) time(0));

    //Number of Nodes
    auto numberNodes = nodes;
    //Number of Edges for every node
    auto numberEdges = edges;
    //Vector with each connection
    vector<int> nodesEdges;

    //Write in the Txt the number of nodes;
    MyFile << numberNodes <<endl;

    //Create how many edges every node has and write them in the Txt
    for(int i = 0; i < numberNodes; i++){
      auto qEdges = (rand() % numberEdges) + 1;

      nodesEdges.push_back(qEdges);

      MyFile <<qEdges<<" ";
    }

    MyFile<<endl;

    //The total of Edges  
    long accumulateEdgesSum = accumulate(nodesEdges.begin(),nodesEdges.end(),0);

    MyFile<<2<<endl;
    MyFile<<accumulateEdgesSum<<endl;

    //Create the connection with its weight and write it down in the text
    for(int i = 0; i<accumulateEdgesSum; i++){
      auto tmp = rand() / (RAND_MAX - 1.);
      auto node =(rand() % numberNodes);
      auto weight =(rand() % 10) + 1;;

      MyFile<<node<<" "<<weight<<endl;
    }

    //Close file
    MyFile.close();
}