//
//  main.cpp
//  FindCycleInGraph
//
//  Created by vlad on 18.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include "Graph/Graph.hpp"
#include <chrono>

using namespace std;
using namespace Alghorithms;






int main(int argc, const char * argv[]) {
   
  
    Math::Graph<long> graph = {
        0,0,0,1,
        0,0,0,0,
        0,1,0,0,
        0,0,1,0
    };
    graph.outputGraph();
    auto vec = FindingShortestWay<long>::find(graph, 0, 1);
    

    return 0;
}
