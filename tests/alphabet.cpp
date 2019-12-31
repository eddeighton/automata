


#include <gtest/gtest.h>

#include "src/alphabet.hpp"


TEST( AutomataTests, AlphabetProductConversions )
{
    using State = automata::Product< int, 4 >;
    
    const State bounds = { 3, 4, 5, 6 };
    
    const std::vector< int > testValues = 
    {
        0,
        1,
        2,
        3,
        123,
        3 * 4 * 5 * 6 - 1 //359
    };
    
    for( int testValue : testValues )
    {
        const State product = automata::fromValue( testValue, bounds );
        const int value = automata::fromProduct( product, bounds );
        ASSERT_EQ( value, testValue );
    }
}

TEST( AutomataTests, AlphabetProductConversionsExceptionsExceptionsValues )
{
    using State = automata::Product< int, 4 >;
    
    const State bounds = { 3, 4, 5, 6 };
    
    {
        const std::vector< int > testValues = 
        {
            -123123123,
            -1
        };
        
        for( int testValue : testValues )
        {
            ASSERT_THROW( automata::fromValue( testValue, bounds ), std::runtime_error );
        }
    }
    {
        const std::vector< int > testValues = 
        {
            3 * 4 * 5 * 6, //360
            1010101010
        };
        
        for( int testValue : testValues )
        {
            ASSERT_THROW( automata::fromValue( testValue, bounds ), std::out_of_range );
        }
    }
}

TEST( AutomataTests, AlphabetProductConversionsExceptionsExceptionsProducts )
{
    using State = automata::Product< int, 4 >;
    
    const State bounds = { 3, 4, 5, 6 };
    
    {
        const std::vector< State > testProducts = 
        {
            { -1, 0, 0, 0 },
            { 0, -1, 0, 0 },
            { 0, 0, -1, 0 },
            { 0, 0, 0, -1 }
        };
        
        for( const State& product : testProducts )
        {
            ASSERT_THROW( automata::fromProduct( product, bounds ), std::runtime_error );
        }
    }
    {
        const std::vector< State > testProducts = 
        {
            { 3, 0, 0, 0 },
            { 0, 4, 0, 0 },
            { 0, 0, 5, 0 },
            { 0, 0, 0, 6 },
            
            { 101010, 0, 0, 0 },
            { 0, 101010, 0, 0 },
            { 0, 0, 101010, 0 },
            { 0, 0, 0, 101010 }
        };
        
        for( const State& product : testProducts )
        {
            ASSERT_THROW( automata::fromProduct( product, bounds ), std::out_of_range );
        }
    }
}