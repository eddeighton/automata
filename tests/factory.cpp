
#include <gtest/gtest.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <boost/system/config.hpp>

#include "src/alphabet.hpp"
#include "src/automata.hpp"
#include "src/factory.hpp"

namespace boost
{
    void assertion_failed( char const * expr, char const * function, char const * file, long line )
    {
        //THROW_RTE( "Boost called abort with: " << expr << " : " << function << " : " << file << ":" << line ); 
        //::abort();
    }
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line)
    {
        //THROW_RTE( "Boost called abort with: " << expr << " : " << function << " : " << file << ":" << line << " : " << msg ); 
        //::abort();
    }
}

using StateType = automata::Product< int, 1 >;

struct GeometryTraits
{
    using point2d = glm::vec2;
};

using Grid2D = automata::SimpleGrid< StateType, GeometryTraits >;


TEST( AutomataTests, FactoryTests )
{
    //ASSERT_TRUE( false );
    
    Grid2D::Graph graph = automata::constructSimpleGrid< StateType, GeometryTraits >();
    
    
}
