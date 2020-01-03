

#ifndef PRODUCT_03_JAN_2019
#define PRODUCT_03_JAN_2019


#include "alphabet.hpp"
#include "automata.hpp"

namespace automata
{
    
    
    

    template< typename TraitsOne, typename TraitsTwo, typename TraitsResult >
    inline TraitsResult::Graph product( const TraitsOne::Graph& graphLeft, const TraitsTwo::Graph& graphRight )
    {
        TraitsResult::Graph g;
        
        const std::size_t szAlphabetProductComponents = 
            components< typename TraitsOne::Graph::ActionType >() *
            components< typename TraitsTwo::Graph::ActionType >();
            
            
        
        return g;
    }
    
    
}


#endif //PRODUCT_03_JAN_2019