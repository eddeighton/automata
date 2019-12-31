
#ifndef AUTOMATA_16_11_2019
#define AUTOMATA_16_11_2019

#include <cstdint>
#include <tuple>
#include <utility>

namespace automata
{
    
    
    /*
    using State         = std::int32_t;
    using Action        = std::int32_t;
    
    static const State DEAD_STATE = -1;
    
    template< std::size_t TotalActions, std::size_t TotalStates >
    struct TransitionTable
    {
        using Actions = std::array< State, TotalActions >;
        using Table = std::array< Actions, TotalStates >;
    };
    
    enum GridActions
    {
        eUp,
        eDown,
        eLeft,
        eRight,
        TOTAL_ACTIONS
    };
    
    template< std::size_t Size >
    inline std::int32_t gridMoveState( State szState, State szHori, State szVert )
    {
        
        if( ( szState % Size  ) + szHori < 0 )
            return DEAD_STATE;
        if( ( szState % Size  ) + szHori >= Size )
            return DEAD_STATE;
        
        if( ( szState / Size  ) + szVert < 0 )
            return DEAD_STATE;
        if( ( szState / Size  ) + szVert >= Size )
            return DEAD_STATE;
        
        State sz = szState + szHori + szVert * Size;
        if( ( sz >= 0 ) && sz < ( Size * Size ) )
            return sz;
        else
            return DEAD_STATE;
    }
    
    template< std::size_t Size >
    inline typename TransitionTable< TOTAL_ACTIONS, Size * Size >::Table generateGrid()
    {
        using Table = TransitionTable< TOTAL_ACTIONS, Size * Size >;
        typename Table::Table table;
        
        for( State x = 0; x < Size; ++x )
        {
            for( State y = 0; y < Size; ++y )
            {
                const State szState = gridMoveState< Size >( 0, x, y );
                if( szState >= 0 && szState < ( Size * Size ) )
                {
                    typename Table::Actions& actions = table[ szState ];
                    
                    actions[ eUp ]      = gridMoveState< Size >( szState, 0, 1 );
                    actions[ eDown ]    = gridMoveState< Size >( szState, 0, -1 );
                    actions[ eLeft ]    = gridMoveState< Size >( szState, -1, 0 );
                    actions[ eRight ]   = gridMoveState< Size >( szState, 1, 0 );
                }
            }
        }
        
        return table;
    }
    */
    
    
    
    
    
    
}


#endif //AUTOMATA_16_11_2019