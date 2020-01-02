

#ifndef FACTORY_31_12_2019
#define FACTORY_31_12_2019

#include "automata.hpp"


namespace automata
{
    
    
    
    //simple rectilinear grid 
    
    enum FourWay : char
    {
        eEast,
        eNorth,
        eWest,
        eSouth
    };
    
    template< typename StateType, typename GeometryTraits >
    using SimpleGrid = AutomataTraits< automata::Product< FourWay, 1 >, StateType, GeometryTraits >;
    
    template< typename StateType, typename GeometryTraits >
    inline typename SimpleGrid< StateType, GeometryTraits >::Graph constructSimpleGrid()
    {
        
        int totalVerticies = 0;
        
        SimpleGrid< StateType, GeometryTraits >::Graph graph( totalVerticies );
        
        
        
        
        return graph;
    }
    
    
    
    

}

#endif //FACTORY_31_12_2019