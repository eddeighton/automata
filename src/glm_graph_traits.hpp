

#ifndef GLM_GRAPH_02_01_2019
#define GLM_GRAPH_02_01_2019

#include "alphabet.hpp"
#include "automata.hpp"


#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <array>
#include <istream>
#include <ostream>

namespace glmGrid
{
    enum Actions : automata::Symbol
    {
        LEFT,
        UP,
        RIGHT,
        DOWN,
        SIZE
    };
    
    static const std::array< const char*, SIZE > actionStrings = 
    {
        "Left",
        "Up",
        "Right",
        "Down"
    };

    struct State
    {
        int index;
        automata::Symbol label;
        glm::vec2 position;
    };
    
    struct Action
    {
        int index;
        Actions action;
        Actions continuation;
        float weight;
    };
    
    using GraphTraits = automata::AutomataTraits< State, Action >;

    static inline boost::dynamic_properties get_dynamic_properties( GraphTraits::Graph& graph )
    {
        boost::dynamic_properties dynamicProperties;
        
        dynamicProperties.property( "State.index",             boost::get( &State::index,          graph ) );
        dynamicProperties.property( "State.label",             boost::get( &State::label,          graph ) );
        dynamicProperties.property( "State.position",          boost::get( &State::position,       graph ) );
        
        dynamicProperties.property( "Action.index",            boost::get( &Action::index,         graph ) );
        dynamicProperties.property( "Action.action",           boost::get( &Action::action,        graph ) );
        dynamicProperties.property( "Action.continuation",     boost::get( &Action::continuation,  graph ) );
        dynamicProperties.property( "Action.weight",           boost::get( &Action::weight,        graph ) );
        
        return dynamicProperties;
    }
    
    inline int xyIndex( int x, int y, int xSize )
    {
        return x * xSize + y;
    }

    inline GraphTraits::Graph generate_grid( int xSize, int ySize )
    {
        GraphTraits::Graph graph( xSize * ySize );
        
        int iIndex = 0;
        for( int x = 0; x < xSize; ++x )
        {
            for( int y = 0; y < ySize; ++y )
            {
                iIndex = xyIndex( x, y, xSize );
                graph[ iIndex ].index = iIndex;
                graph[ iIndex ].label = iIndex;
                graph[ iIndex ].position = glm::vec2( x - xSize / 2, y - ySize / 2 );
            }
        }
        
        int iEdgeIndex = 0;
        for( int x = 0; x < xSize; ++x )
        {
            for( int y = 0; y < ySize; ++y )
            {
                iIndex = xyIndex( x, y, xSize );
                
                if( x > 0 )
                {
                    auto e = boost::add_edge( iIndex, xyIndex( x - 1, y, xSize ), graph );
                    graph[ e.first ].index = iEdgeIndex++;
                    graph[ e.first ].action = LEFT;
                    graph[ e.first ].continuation = LEFT;
                    graph[ e.first ].weight = 1.0f;
                }
                
                if( y > 0 )
                {
                    auto e = boost::add_edge( iIndex, xyIndex( x, y - 1, xSize ), graph );
                    graph[ e.first ].index = iEdgeIndex++;
                    graph[ e.first ].action = UP;
                    graph[ e.first ].continuation = UP;
                    graph[ e.first ].weight = 1.0f;
                }
                
                if( x < xSize - 1 )
                {
                    auto e = boost::add_edge( iIndex, xyIndex( x + 1, y, xSize ), graph );
                    graph[ e.first ].index = iEdgeIndex++;
                    graph[ e.first ].action = RIGHT;
                    graph[ e.first ].continuation = RIGHT;
                    graph[ e.first ].weight = 1.0f;
                }
                
                if( y < ySize - 1 )
                {
                    auto e = boost::add_edge( iIndex, xyIndex( x, y + 1, xSize ), graph );
                    graph[ e.first ].index = iEdgeIndex++;
                    graph[ e.first ].action = DOWN;
                    graph[ e.first ].continuation = DOWN;
                    graph[ e.first ].weight = 1.0f;
                }
            }
        }
        return graph;
    }   
}


namespace glmMultiGrid
{
    struct State
    {
        int index;
        automata::SymbolProduct label;
        std::vector< glm::vec2 > position;
    };
    
    struct Action
    {
        int index;
        std::vector< glmGrid::Actions > action;
        std::vector< glmGrid::Actions > continuation;
        float weight;
    };
    
    using GraphTraits = automata::AutomataTraits< State, Action >;

    static inline boost::dynamic_properties get_dynamic_properties( GraphTraits::Graph& graph )
    {
        boost::dynamic_properties dynamicProperties;
        
        dynamicProperties.property( "State.index",             boost::get( &State::index,          graph ) );
        dynamicProperties.property( "State.label",             boost::get( &State::label,          graph ) );
        dynamicProperties.property( "State.position",          boost::get( &State::position,       graph ) );
        
        dynamicProperties.property( "Action.index",            boost::get( &Action::index,         graph ) );
        dynamicProperties.property( "Action.action",           boost::get( &Action::action,        graph ) );
        dynamicProperties.property( "Action.continuation",     boost::get( &Action::continuation,  graph ) );
        dynamicProperties.property( "Action.weight",           boost::get( &Action::weight,        graph ) );
        
        return dynamicProperties;
    }
    
    
    inline int xyIndex( int x, int y, int xSize )
    {
        return x * xSize + y;
    }

    inline GraphTraits::Graph generate_grid( int xSize, int ySize, int iComponents )
    {
        const int iArea = xSize * ySize;
        int iNumVertices = 1;
        int iNumActions = 1;
        
        automata::AlphabetProduct alphabetProduct;
        automata::AlphabetProduct actionAlphabetProduct;
        
        for( int iComponent = 0; iComponent < iComponents; ++iComponent )
        {
            iNumVertices *= iArea;
            iNumActions *= glmGrid::SIZE;
            alphabetProduct.components.push_back( automata::Alphabet{ iArea } );
            actionAlphabetProduct.components.push_back( automata::Alphabet{ glmGrid::SIZE } );
        }
        
        GraphTraits::Graph graph( iNumVertices );
        
        //int iConnectivity = iNumVertices / iArea;
        
        automata::Symbol symbol = 0;
        std::vector< glm::vec2 > position( iComponents );
        std::vector< glmGrid::Actions > actions( iComponents );
        
        int iEdgeIndex = 0;
        
        //go through ALL vertices in order
        while( symbol < iNumVertices )
        {
            //determine the product symbol for the vertex 
            automata::SymbolProduct symbolProduct = 
                fromSymbol( symbol, alphabetProduct );
            
            graph[ symbol ].index = symbol;
            graph[ symbol ].label = symbolProduct;
            
            //for each product component calculate the corresponding coordinate
            int iSymbolCounter = 0;
            for( automata::Symbol s : symbolProduct )
            {
                const int x = s / xSize;
                const int y = s % xSize;
                position[ iSymbolCounter++ ] = glm::vec2( x, y );
            }
            graph[ symbol ].position = position;
            
            for( automata::Symbol iAction = 0; iAction < iNumActions; ++iAction )
            {
                const automata::SymbolProduct actionProduct = 
                    fromSymbol( iAction, actionAlphabetProduct );
                
                automata::SymbolProduct adjacent = symbolProduct;
                
                int iActionComponent = 0;
                bool bAddEdge = true;
                for( automata::Symbol s : actionProduct )
                {
                    switch( s )
                    {
                        case glmGrid::LEFT:  
                            if( adjacent[ iActionComponent ] >= xSize )
                            {
                                adjacent[ iActionComponent ] -= xSize;
                                actions[ iActionComponent ] = glmGrid::LEFT;
                            }
                            else
                                bAddEdge = false;
                            break;
                        case glmGrid::UP:    
                            if( adjacent[ iActionComponent ] > 0 )
                            {
                                adjacent[ iActionComponent ] --;
                                actions[ iActionComponent ] = glmGrid::UP;
                            }
                            else
                                bAddEdge = false;   
                            break;
                        case glmGrid::RIGHT: 
                            if( adjacent[ iActionComponent ] < ( iArea - xSize ) )
                            {
                                adjacent[ iActionComponent ] += xSize;   
                                actions[ iActionComponent ] = glmGrid::RIGHT;
                            }
                            else
                                bAddEdge = false;     
                            break;
                        case glmGrid::DOWN:  
                            if( adjacent[ iActionComponent ] < ( iArea - 1 ) )
                            {
                                adjacent[ iActionComponent ] ++; 
                                actions[ iActionComponent ] = glmGrid::DOWN;  
                            }
                            else
                                bAddEdge = false;       
                            break;
                    }
                    if( !bAddEdge )
                        break;
                    ++iActionComponent;
                }
                if( bAddEdge )
                {
                    auto e = boost::add_edge( symbol, fromProduct( adjacent, alphabetProduct ), graph );
                    graph[ e.first ].index          = iEdgeIndex++;
                    graph[ e.first ].action         = actions;
                    graph[ e.first ].continuation   = actions;
                    graph[ e.first ].weight         = 1.0f;
                }
            }
            
            ++symbol;
        }
        
        return graph;
    }   
}

namespace std
{
    inline std::ostream& operator<<( std::ostream& os, const glm::vec2& pos )
    {
        return os << '{' << pos.x << ',' << pos.y << '}';
    }
    inline std::istream& operator>>( std::istream& is, glm::vec2& pos )
    {
        char c;
        return is >> c >> pos.x >> c >> pos.y >> c;
    }
    
    inline std::ostream& operator<<( std::ostream& os, const glmGrid::Actions& action )
    {
        return os << glmGrid::actionStrings[ action ];
    }
    inline std::istream& operator>>( std::istream& is, glmGrid::Actions& action )
    {
        std::string strAction;
        is >> strAction;
        action = static_cast< glmGrid::Actions >( 
            std::distance( glmGrid::actionStrings.begin(), 
                std::find( glmGrid::actionStrings.begin(), glmGrid::actionStrings.end(), strAction ) ) );
        return is;
    }
    
    template< typename T >
    inline std::ostream& operator<<( std::ostream& os, const std::vector< T >& actions )
    {
        os << '{';
        bool bFirst = true;
        for( const T& a : actions )
        {
            if( bFirst ) bFirst = false;
            else os << ',';
            os << a;
        }
        os << '}';
        return os;
    }
    
    template< typename T >
    inline std::istream& operator>>( std::istream& is, std::vector< T >& actions )
    {
        char c;
        is >> c;
        while( is.peek() != '}' )
        {
            T a;
            is >> a;
            actions.push_back( a );
            if( is.peek() == ',' )
                is >> c;
        }
        return is >> c;
    }
}

#endif //GLM_GRAPH_02_01_2019