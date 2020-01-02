

#ifndef GLM_GRAPH_02_01_2019
#define GLM_GRAPH_02_01_2019

#include "automata.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

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
}

struct GeometryTraits
{
    using point2d = glm::vec2;
};

using GraphTraits = automata::AutomataTraits< int, int, GeometryTraits >;


#endif //GLM_GRAPH_02_01_2019