
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
    template< typename ActionType_, typename StateType_, typename GeometryTraits_ >
    struct AutomataTraits
    {
        using ActionType  = ActionType_;
        using StateType   = StateType_;
        using GeometryTraits = GeometryTraits_;
        
        struct State
        {
            int index;
            StateType label;
            typename GeometryTraits::point2d position;
        };
        
        struct Action
        {
            int index;
            ActionType action;
            ActionType continuation;
            int weight;
        };
        
        using Graph = boost::adjacency_list< 
            boost::vecS, boost::vecS, boost::bidirectionalS,
            State, Action >;
            
        static void getDynamicProperties( boost::dynamic_properties& dynamicProperties, Graph& graph )
        {
            dynamicProperties.property( "State.index",             boost::get( &State::index,          graph ) );
            dynamicProperties.property( "State.label",             boost::get( &State::label,          graph ) );
            dynamicProperties.property( "State.position",          boost::get( &State::position,       graph ) );
            
            dynamicProperties.property( "Action.index",            boost::get( &Action::index,         graph ) );
            dynamicProperties.property( "Action.action",           boost::get( &Action::action,        graph ) );
            dynamicProperties.property( "Action.continuation",     boost::get( &Action::continuation,  graph ) );
            dynamicProperties.property( "Action.weight",           boost::get( &Action::weight,        graph ) );
        }
        
        
        static inline void load( std::istream& is, Graph& graph )
        {
            std::unique_ptr< boost::dynamic_properties > dynamicProperties = 
                std::make_unique< boost::dynamic_properties >();
            getDynamicProperties( *dynamicProperties, graph );
            boost::read_graphml( is, graph, *dynamicProperties );
        }
        
        static inline void save( std::ostream& os, Graph& graph )
        {
            std::unique_ptr< boost::dynamic_properties > dynamicProperties = 
                std::make_unique< boost::dynamic_properties >();
            getDynamicProperties( *dynamicProperties, graph );
            boost::write_graphml( os, graph, *dynamicProperties, true );
        }
            
        using Vertex = typename boost::graph_traits< Graph >::vertex_descriptor;
        using VertexIter = typename boost::graph_traits< Graph >::vertex_iterator;
        using EdgeIter = typename boost::graph_traits< Graph >::edge_iterator;
        
    };
    
    
    
    /*
    template< typename TraitsOne, typename TraitsTwo, typename TraitsResult >
    inline TraitsResult::Graph product( const TraitsOne::Graph& graphLeft, const TraitsTwo::Graph& graphRight )
    {
        
    }*/
        
        
    
}


#endif //AUTOMATA_31_12_2019