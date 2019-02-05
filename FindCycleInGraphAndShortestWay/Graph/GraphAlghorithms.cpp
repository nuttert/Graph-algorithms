//
//  GraphAlghorithms.cpp
//  FindCycleInGraph
//
//  Created by vlad on 20.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#ifndef GraphAlghorithms_cpp
#define GraphAlghorithms_cpp

#include "Graph.hpp"
#include <set>
#include <future>
#include <iostream>
using std::set;

template<typename Element>
using FindWay =  Alghorithms::FindingShortestWay<Element>;

template<class Element>
using FindCycle = Alghorithms::FindingGraphCycle<Element>;
using Utilities::unlikely;

template<class Element>
using FindingOptimalStructure = Alghorithms::FindingOptimalStructure<Element>;



template<class Element>
bool FindCycle<Element>::cycleExist(const Graph& graph){
    set<size_t> traversedVertex{};
    if( unlikely(graph.isEmpty()) ) return false;
    return  subFunctionFindCycle(traversedVertex,
                                 graph,
                                 0, 0);
}

template<class Element>
bool FindCycle<Element>::subFunctionFindCycle(set<size_t>& traversedVert,
                                              const Graph& graph,
                                              size_t source,
                                              size_t current){
    size_t index(0);
    traversedVert.insert(current);
    bool forwardResult = false;
    const auto& currentRaw = graph[current];
    for(const auto value:currentRaw){
        if(index != current &&
           index != source &&
           value){
            bool isCycle = traversedVert.find(index) != traversedVert.end();
            if(unlikely(isCycle))return true;
            forwardResult = subFunctionFindCycle(traversedVert,
                                                 graph,
                                                 current,index);
        }
        ++index;
    }
    return forwardResult;
}




//#1 Enrty
template<typename Element>
typename FindWay<Element>::Vector
FindWay<Element>::find(const Graph& graph,
                       const size_t from,
                       const size_t to){
    Collections wayAndTraversedVert{graph.getSize()};
    wayAndTraversedVert.nextVertixes.push(from);

    subFunctionFind(graph,
                    wayAndTraversedVert,
                    to);
    
    findReturnTrip(wayAndTraversedVert.way,
                   wayAndTraversedVert.traversedVertex,
                   to);
    return wayAndTraversedVert.way;
}



//#2 Find
template<typename Element>
void FindWay<Element>::subFunctionFind(const Graph& graph,
                                       Collections& collections,
                                       const size_t destination){
    //_______Initialization
    auto& traversedVert = collections.traversedVertex;
    size_t index(0);
    auto currentRaw = collections.nextVertixes.front();
    collections.nextVertixes.pop();
    const auto& neighbours = graph[currentRaw];
    //_______
    for(const auto vertex : neighbours){
        const bool wayExist =
        index != currentRaw &&
        vertex &&
        !(bool)traversedVert[index];
        
        const bool endIsReached =
        wayExist &&
        index == destination;
        
        if(wayExist) {
            collections.nextVertixes.push(index);
            collections.traversedVertex[index] = currentRaw;
        }
        if(unlikely(endIsReached)) return;
        ++index;
    }
    if(!collections.nextVertixes.empty())
        subFunctionFind(graph,
                        collections,
                        destination);
    
}


//Return #3
template<typename Element>
void FindWay<Element>::findReturnTrip(Vector& way,
                                      const ReturnTrip& trip,
                                      const size_t destination){
    auto parent = trip[destination];
    way.push_back(destination);
    while(parent){
        way.push_back(*parent);
        parent = trip[*parent];
    }
}





#endif
