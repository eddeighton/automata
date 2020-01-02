
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
        
        
        static void load( const std::string& path, Graph& graph )
        {
            std::ifstream inputFileStream( path );
            boost::dynamic_properties dynamicProperties;
            getDynamicProperties( dynamicProperties, graph );
            boost::read_graphml( inputFileStream, graph, dynamicProperties );
        }
        
        static void save( const std::string& path, Graph& graph )
        {
            std::ofstream outputFileStream( path );
            boost::dynamic_properties dynamicProperties;
            getDynamicProperties( dynamicProperties, graph );
            boost::write_graphml( outputFileStream, graph, dynamicProperties, true );
        }
            
        //using Vertex = boost::graph_traits< Graph >::vertex_descriptor;
    };
    
    
    
    
    
    /*
    using State         = std::int32_t;
    using Action        = std::int32_t;
    
    static const State DEAD_STATE = -1;
    
    template< std::size_t TotalActions, std::size_t TotalStates >
    struct TransitionTable
    {
        using Actions = std::array< State, TotalActions >;
        using Table = std::array< Actions, TotalStates >;
    };
    
    enum GridActions
    {
        eUp,
        eDown,
        eLeft,
        eRight,
        TOTAL_ACTIONS
    };
    
    template< std::size_t Size >
    inline std::int32_t gridMoveState( State szState, State szHori, State szVert )
    {
        
        if( ( szState % Size  ) + szHori < 0 )
            return DEAD_STATE;
        if( ( szState % Size  ) + szHori >= Size )
            return DEAD_STATE;
        
        if( ( szState / Size  ) + szVert < 0 )
            return DEAD_STATE;
        if( ( szState / Size  ) + szVert >= Size )
            return DEAD_STATE;
        
        State sz = szState + szHori + szVert * Size;
        if( ( sz >= 0 ) && sz < ( Size * Size ) )
            return sz;
        else
            return DEAD_STATE;
    }
    
    template< std::size_t Size >
    inline typename TransitionTable< TOTAL_ACTIONS, Size * Size >::Table generateGrid()
    {
        using Table = TransitionTable< TOTAL_ACTIONS, Size * Size >;
        typename Table::Table table;
        
        for( State x = 0; x < Size; ++x )
        {
            for( State y = 0; y < Size; ++y )
            {
                const State szState = gridMoveState< Size >( 0, x, y );
                if( szState >= 0 && szState < ( Size * Size ) )
                {
                    typename Table::Actions& actions = table[ szState ];
                    
                    actions[ eUp ]      = gridMoveState< Size >( szState, 0, 1 );
                    actions[ eDown ]    = gridMoveState< Size >( szState, 0, -1 );
                    actions[ eLeft ]    = gridMoveState< Size >( szState, -1, 0 );
                    actions[ eRight ]   = gridMoveState< Size >( szState, 1, 0 );
                }
            }
        }
        
        return table;
    }
    */
    
    
    
    
    
    
}


#endif //AUTOMATA_31_12_2019