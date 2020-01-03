
#ifndef AUTOMATA_31_12_2019
#define AUTOMATA_31_12_2019

#include "alphabet.hpp"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphml.hpp>

#include <cstdint>
#include <tuple>
#include <utility>
#include <istream>
#include <ostream>

namespace automata
{    
    template< typename StateType_, typename ActionType_ >
    struct AutomataTraits
    {
        using State   = StateType_;
        using Action  = ActionType_;
        
        using Graph = boost::adjacency_list< 
            boost::vecS, boost::vecS, boost::bidirectionalS,
            State, Action >;
        
        static inline void load( std::istream& is, Graph& graph, boost::dynamic_properties dynamicProperties )
        {
            boost::read_graphml( is, graph, dynamicProperties );
        }
        
        static inline void save( std::ostream& os, Graph& graph, boost::dynamic_properties dynamicProperties )
        {
            boost::write_graphml( os, graph, dynamicProperties, true );
        }
            
        using Vertex = typename boost::graph_traits< Graph >::vertex_descriptor;
        using VertexIter = typename boost::graph_traits< Graph >::vertex_iterator;
        using EdgeIter = typename boost::graph_traits< Graph >::edge_iterator;
        
    };
    
}


#endif //AUTOMATA_31_12_2019