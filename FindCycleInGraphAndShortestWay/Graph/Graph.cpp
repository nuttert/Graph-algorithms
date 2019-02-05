//
//  Graph.cpp
//  FindCycleInGraph
//
//  Created by vlad on 18.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//
#ifndef Graph_cpp
#define Graph_cpp

#include "Graph.hpp"
#include <iostream>

//Constructors
template<class Element>
Math::Graph<Element>::Graph(std::initializer_list<unsigned>&& list){
    const auto square = Utilities::isSquare(list.size());
    assert(square);
    auto size = std::move(*square);
    this->size = size;
    for(size_t rawNumber = 0;rawNumber<size;++rawNumber){
        vector raw(size);
        auto beginOfRaw = list.begin()+size*rawNumber;
        std::copy(beginOfRaw,beginOfRaw+size, raw.begin());
        graph.push_back(std::move(raw));
    }
    
}


//VERTEX
template<class Element>
template<class ValueType>
void Math::Graph<Element>::addVertex(ValueType&& value){
    constexpr auto isSame =  Utilities::RemoveReferenceAndCompareTypes<ValueType, Element>();
    static_assert(isSame, "Different types!");
    ++size;
    //update matrix
    vector newRaw(size,false);
    graph.push_back(std::move(newRaw));
    for (size_t index = 0; index < size-1; ++index) graph[index].push_back(false);
    //update labels
    labels.push_back(std::forward<ValueType>(value));
}

//EDGE
template<class Element>
template<class Indecies>
void  Math::Graph<Element>::addEdge(Indecies&& source,Indecies&& to){
    assert(source < size &&
           to < size);
    graph[source][to] = true;
}



//OUTPUT
template<class Element>
void Math::Graph<Element>::outputGraph()const{
    std::cout<<"WAYS"<< std::endl;
    for(const auto& raw :graph){
        for(const auto element : raw)
            std::cout << element << " ";
        std::cout<<std::endl;
    }
     std::cout<<"VALUES"<< std::endl;
    
    for (size_t index = 0; index < labels.size(); ++index) {
        std::cout << "Vertex "<<index << ": "
        << labels[index] << " "<<std::endl;
    }
}

template<class Element>
size_t Math::Graph<Element>::getSize()const{
    return graph.size();
}

#endif /* Graph_cpp */
