#include <iostream>
#include<string> // for string class
#include <fstream>
#include <cstdlib>
#include<vector>
#include<numeric>
#include <cmath>

using namespace std;

void createGraph();

int main(){
  createGraph();
  return 0;
}

void createGraph(){
    ofstream MyFile("filename.txt");
    srand((unsigned) time(0));

    auto range = 15000; 
    auto numberNodes = 10000 + (rand() * range) / RAND_MAX;
    auto edges = numberNodes/3;
    vector<int> nodesEdges;

    MyFile <<numberNodes<<endl;

    for(int i = 0; i<numberNodes; i++){
      auto numEdges = (rand() % edges) + 1;

      nodesEdges.push_back(numEdges);

      MyFile <<numEdges<<" ";
    }

    MyFile<<endl;
      
    long accumulateEdgesSum = accumulate(nodesEdges.begin(),nodesEdges.end(),0);

    MyFile<<2<<endl;
    MyFile<<accumulateEdgesSum<<endl;

    for(int i = 0; i<accumulateEdgesSum; i++){
      auto tmp = rand() / (RAND_MAX - 1.);
      auto node =(rand() % numberNodes);
      auto weight =(rand() % edges) + 1;;

      MyFile<<node<<" "<<weight<<endl;
    }

    //Close file
    MyFile.close();
}