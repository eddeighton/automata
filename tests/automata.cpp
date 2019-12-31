

#include <gtest/gtest.h>

#include <glm/glm.hpp>

#include "src/automata.hpp"


struct Point
{
    int x,y;
};

enum Actions
{
    eUp,
    eDown,
    eRight,
    eLeft,
    TOTAL_ACTIONS
};

static const int TotalStates = 16;

using AlphabetType  = automata::Product< int, TOTAL_ACTIONS >;
using StateType     = automata::Product< int, TotalStates >;

struct GeometryTraits
{
    using point2d = glm::vec2;
};

using Automata = automata::AutomataTraits< AlphabetType, StateType, GeometryTraits >;

const Automata::ActionType  AlphabetBounds  = { TOTAL_ACTIONS, TOTAL_ACTIONS, TOTAL_ACTIONS, TOTAL_ACTIONS };
const Automata::StateType   StateBounds     = { TotalStates, TotalStates, TotalStates, TotalStates };

//
//  0  1  2  3
//  4  5  6  7
//  8  9  10 11
//  12 13 14 15
//

const std::pair< int, int > BasicGridEdges[] = 
{
    { 0, 1 }, { 1, 2 }, { 2, 3 },
    { 4, 5 }, { 5, 6 }, { 6, 7 },
    { 8, 9 }, { 9, 10}, { 10,11},
    { 12,13}, { 13,14}, { 14,15},
    
    { 0, 4 }, { 4, 8 }, { 8, 12},
    { 1, 5 }, { 5, 9 }, { 9, 13},
    { 2, 6 }, { 6, 10}, { 10,14},
    { 3 ,7 }, { 7, 11}, { 11,15}
};

TEST( AutomataTests, BasicGraphTests )
{
    //ASSERT_TRUE( false );
    
    Automata::Graph graph( TotalStates );
    
    for( const std::pair< int, int >& edge : BasicGridEdges )
    {
        boost::add_edge( edge.first, edge.second, graph );
        boost::add_edge( edge.second, edge.first, graph );
    }
    
    
}