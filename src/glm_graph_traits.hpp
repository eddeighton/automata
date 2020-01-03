

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
}

#endif //GLM_GRAPH_02_01_2019