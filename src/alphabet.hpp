
#ifndef ALPHABET_31_12_2019
#define ALPHABET_31_12_2019


#include <cstdint>
#include <vector>

/*
#include <array>
#include <cstdint>
#include <stdexcept>
#include <type_traits>
*/

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
    
    using Symbol = int;
    using SymbolProduct = std::vector< Symbol >;
    
    struct Alphabet
    {
        Symbol size;
    };
    
    struct AlphabetProduct
    {
        std::vector< Alphabet > components;
    };
    
    
    inline Symbol fromProduct( const SymbolProduct& symbolProduct, const AlphabetProduct& alphabetProduct )
    {
        Symbol value = 0U;
        Symbol bound = 1U;
        
        if( alphabetProduct.components.size() != symbolProduct.size() )
        {
            throw std::runtime_error( "Incompatible alphabet product with symbol product" );
        }
        
        for( std::size_t sz = 0u; sz != symbolProduct.size(); ++sz )
        {
            CHECK_COMPONENT_RANGE( symbolProduct[ sz ], alphabetProduct.components[ sz ].size )
            value += symbolProduct[ sz ] * bound;
            bound *= alphabetProduct.components[ sz ].size;
        }
        return value;
    }
    
    inline SymbolProduct fromSymbol( Symbol value, const AlphabetProduct& alphabetProduct )
    {
        SymbolProduct symbolProduct( alphabetProduct.components.size() );
        Symbol bound = 1U;
        for( std::size_t sz = 0u; sz != symbolProduct.size(); ++sz )
        {
            Symbol priorBound = bound;
            bound *= alphabetProduct.components[ sz ].size;
            symbolProduct[ sz ] = ( value % bound ) / priorBound;
        }
        CHECK_COMPONENT_RANGE( value, bound )
        return symbolProduct;
    }
    
    
    inline AlphabetProduct combine( const AlphabetProduct& left, const AlphabetProduct& right )
    {
        AlphabetProduct result( left );
        std::copy( right.components.begin(), right.components.end(), std::back_inserter( result.components ) );
        return result;
    }
       
    inline AlphabetProduct combine( const Alphabet& left, const Alphabet& right )
    {
        AlphabetProduct result;
        result.components.push_back( left );
        result.components.push_back( right );
        return result;
    } 
}

#endif //ALPHABET_31_12_2019