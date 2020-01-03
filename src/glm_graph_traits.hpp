

#ifndef GLM_GRAPH_02_01_2019
#define GLM_GRAPH_02_01_2019

#include "automata.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <array>

namespace glmGrid
{
    
    struct GeometryTraits
    {
        using point2d = glm::vec2;
    };

    enum Actions : int
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

    using GraphTraits = automata::AutomataTraits< Actions, int, GeometryTraits >;

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