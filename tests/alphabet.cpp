
#include <limits>

#include <gtest/gtest.h>

#include "src/alphabet.hpp"


TEST( AutomataTests, AlphabetProductConversions )
{
    using namespace automata;
    
    const AlphabetProduct alphabetProduct = 
    { 
        { 
            Alphabet{ 3 }, //1
            Alphabet{ 4 }, //3
            Alphabet{ 5 }, //12
            Alphabet{ 6 }  //60
        } 
    };
    
    const std::vector< Symbol > testValues = 
    {
        0,
        1,
        2,
        3,
        123,
        1 + 3 + 12 + 60,
        3 * 4 * 5 * 6 - 1 //359
    };
    
    const std::vector< SymbolProduct > expectedValues =
    {
        { 0, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 2 },
        { 1, 1, 1, 1 },
        { 2, 3, 4, 5 },
    };
    
    int iCounter = 0;
    for( int testValue : testValues )
    {
        const SymbolProduct product = fromSymbol( testValue, alphabetProduct );
        ASSERT_EQ( product, expectedValues[ iCounter ] );
        const Symbol value = fromProduct( product, alphabetProduct );
        ASSERT_EQ( value, testValue );
        ++iCounter;
    }
}

TEST( AutomataTests, AlphabetProductConversionsExceptionsExceptionsValues )
{
    using namespace automata;
    
    const AlphabetProduct alphabetProduct = 
    { 
        { 
            Alphabet{ 3 }, //1
            Alphabet{ 4 }, //3
            Alphabet{ 5 }, //12
            Alphabet{ 6 }  //60
        } 
    };
    
    {
        const std::vector< Symbol > testValues = 
        {
            -1,
            -355,
            -360,
            std::numeric_limits< Symbol >::min()
        };
        for( Symbol testValue : testValues )
        {
            ASSERT_THROW( automata::fromSymbol( testValue, alphabetProduct ), std::runtime_error );
        }
    }
    {
        const std::vector< int > testValues = 
        {
            3 * 4 * 5 * 6, //360
            361,
            std::numeric_limits< Symbol >::max()
        };
        for( int testValue : testValues )
        {
            ASSERT_THROW( automata::fromSymbol( testValue, alphabetProduct ), std::out_of_range );
        }
    }
}

TEST( AutomataTests, AlphabetProductConversionsExceptionsExceptionsProducts )
{
    using namespace automata;
    
    const AlphabetProduct alphabetProduct = 
    { 
        { 
            Alphabet{ 3 }, //1
            Alphabet{ 4 }, //3
            Alphabet{ 5 }, //12
            Alphabet{ 6 }  //60
        } 
    };
    
    {
        const std::vector< SymbolProduct > testProducts = 
        {
            { -1, 0, 0, 0 },
            { 0, -1, 0, 0 },
            { 0, 0, -1, 0 },
            { 0, 0, 0, -1 },
            { std::numeric_limits< Symbol >::min(), 0, 0, 0 },
            { 0, std::numeric_limits< Symbol >::min(), 0, 0 },
            { 0, 0, std::numeric_limits< Symbol >::min(), 0 },
            { 0, 0, 0, std::numeric_limits< Symbol >::min() }
        };
        
        for( const SymbolProduct& product : testProducts )
        {
            ASSERT_THROW( automata::fromProduct( product, alphabetProduct ), std::runtime_error );
        }
    }
    {
        const std::vector< SymbolProduct > testProducts = 
        {
            { 3, 0, 0, 0 },
            { 0, 4, 0, 0 },
            { 0, 0, 5, 0 },
            { 0, 0, 0, 6 },
            
            { std::numeric_limits< Symbol >::max(), 0, 0, 0 },
            { 0, std::numeric_limits< Symbol >::max(), 0, 0 },
            { 0, 0, std::numeric_limits< Symbol >::max(), 0 },
            { 0, 0, 0, std::numeric_limits< Symbol >::max() }
        };
        
        for( const SymbolProduct& product : testProducts )
        {
            ASSERT_THROW( automata::fromProduct( product, alphabetProduct ), std::out_of_range );
        }
    }
}