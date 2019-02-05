//
//  Graph.hpp
//  FindCycleInGraph
//
//  Created by vlad on 18.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <vector>
#include <optional>
#include <set>
#include <queue>
#include <optional>
namespace Utilities {
    template<class T1,class T2>
    constexpr bool RemoveReferenceAndCompareTypes(){
        using withoutRefT1 = typename std::remove_reference<std::remove_cv_t<T1>>::type;
        using withoutRefT2 = typename std::remove_reference<std::remove_cv_t<T2>>::type;
        [[maybe_unused]] constexpr bool is_same = std::is_same<withoutRefT1,withoutRefT2>::value;
        return is_same;
    };
    
    inline decltype(auto) unlikely(bool expr){
        return __builtin_expect(expr,0);
    }
    

    template<typename Element>
    constexpr std::optional<size_t> isSquare(const Element&& value){
        using withoutQualifier = std::remove_reference_t<std::remove_cv_t<Element>>;
        static_assert(std::is_scalar<withoutQualifier>::value, "Isn't scalar type!");
        size_t accumulator = 0;
        size_t square = 0;
        bool isSquare = false;
        bool cycleIsNotEnd = true;
        auto cycleLimit = value/2+2;
        for( size_t index = 1;cycleIsNotEnd; index += 2,++square){
            accumulator += index;
            cycleIsNotEnd = index < cycleLimit &&
            !(isSquare |= accumulator == value);
        }
        if(isSquare) return {square};
        else return std::nullopt;
    }
    
   
    constexpr size_t amountOfArgs(){
        return 0;
    }
    
    template<typename Arg,typename ...Args>
    constexpr size_t amountOfArgs(Arg&& arg,Args&& ...args){
        return amountOfArgs(args...)+1;
    }
    
}

namespace Math{
    template<class Element>
    class Graph{
        using vector = std::vector<unsigned>;
        using Matrix = std::vector<vector>;
        using Data = std::vector<Element>;
    public:
         using valueType = Element;
        //DATA
    private:
        Matrix graph{};
        Data labels{};
        size_t size = 0;
        //Methods
    public:
        Graph(std::initializer_list<unsigned>&& list);
        
        template<class ValueType>
        void addVertex(ValueType&& value);
        
        template<class Indecies = size_t>
        void addEdge(Indecies&& source,Indecies&& to);
        
        void outputGraph()const;
        size_t getSize()const;
        bool isEmpty()const{ return size == 0;}
        
        const vector& operator[](size_t index)const{
            return graph[index];
        }
    };
    
    
    

}


namespace Alghorithms{
    //Cycle
    template<typename Element>
    class FindingGraphCycle{
        using Graph = Math::Graph<Element>;
        using Set = std::set<size_t>;
        FindingGraphCycle() = delete;
        
    public:
        static bool cycleExist(const  Graph& graph);
    private:
        static bool subFunctionFindCycle(Set& traversedVert,
                                         const Graph& graph,
                                         size_t source,
                                         size_t currentRaw);
    };
    
    template<class Element>
    bool cycleExist(const Math::Graph<Element>& graph){
        return FindingGraphCycle<Element>::cycleExist(graph);
    }
    
    
    
    
    
    
    
    //The shortest way
    template<typename Element>
    class FindingShortestWay{
        using Graph = Math::Graph<Element>;
        using Vector = std::vector<size_t>;
        using ReturnTrip = std::vector<std::optional<size_t>>;
        using Queue = std::queue<size_t>;
        FindingShortestWay() = delete;
    private:
        //Utility structures
        struct Collections{
            Vector way{};
            ReturnTrip traversedVertex;
            Queue nextVertixes{};
            Collections(size_t graphDimension):traversedVertex(graphDimension,std::nullopt){}
        };
        
        //The main functions
    public:
        static Vector find(const Graph& graph,
                           const size_t from,
                           const size_t to);
    private:
        static void subFunctionFind(const Graph& graph,
                                    Collections& collections,
                                    const size_t destination);
        
        static void findReturnTrip(Vector& way,
                                   const ReturnTrip& trip,
                                   const size_t destination);
    };
    
    template<class Element>
    typename FindingShortestWay<Element>::Vector
    findShortestWay(const Math::Graph<Element>& graph,
                    const size_t from,
                    const size_t to){
        return FindingShortestWay<Element>::find(graph,
                                                 from,
                                                 to);
    }
    
    
    
    
    
    
    
    
    
    
    template<typename Element>
    class FindingOptimalStructure{
        using Vector = std::vector<Element>;
        using Queue = std::queue<Element>;
        using Graph = Math::Graph<Element>;
        using Condition = bool (Element,Element);
        FindingOptimalStructure() = delete;
    public:
        static Vector find(const Graph& graph);
    private:
        struct Collections{
            Queue nextVertices{};
            Vector way{};
            Vector traversedVertex;
            Collections(size_t amountOfVertices):traversedVertex(Vector(amountOfVertices,std::nullopt)){}
        };
        
        static void findImplementation(const Graph& graph,Collections& collections,Condition& condition);
    };
    
}









#include "Graph.cpp"
#include "GraphAlghorithms.cpp"
#endif /* Graph_hpp */
