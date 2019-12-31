
#include <array>
#include <cstdint>
#include <stdexcept>

#define CHECK_COMPONENT_RANGE( value, bound )                      \
if( value < 0 )                                                    \
{                                                                  \
    throw std::runtime_error( "Negative component value" );        \
}                                                                  \
if( value >= bound )                                               \
{                                                                  \
    throw std::out_of_range( "Out of bounds component value: " );  \
}

namespace automata
{
    template< typename T, std::size_t Size >
    using Product = std::array< T, Size >;
    
    template< typename T, std::size_t Size >
    inline T fromProduct( const Product< T, Size >& product, const Product< T, Size >& bounds )
    {
        T value = T();
        T bound = 1U;
        for( std::size_t sz = 0u; sz != Size; ++sz )
        {
            CHECK_COMPONENT_RANGE( product[ sz ], bounds[ sz ] )
            
            value += product[ sz ] * bound;
            bound *= bounds[ sz ];
        }
        return value;
    }
    
    template< typename T, std::size_t Size >
    inline Product< T, Size > fromValue( const T value, const Product< T, Size >& bounds )
    {
        Product< T, Size > product;
        T bound = 1U;
        for( std::size_t sz = 0u; sz != Size; ++sz )
        {
            T priorBound = bound;
            bound *= bounds[ sz ];
            product[ sz ] = ( value % bound ) / priorBound;
        }
        CHECK_COMPONENT_RANGE( value, bound )
        return product;
    }
    
    
    using State         = std::int32_t; //zero indexed
    using Action        = std::int32_t; //zero indexed
    
}
