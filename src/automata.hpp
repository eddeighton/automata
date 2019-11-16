
#ifndef AUTOMATA_16_11_2019
#define AUTOMATA_16_11_2019


#include <cstdint>
#include <vector>
#include <string>


namespace automata
{
    
    using State         = std::int32_t;
    using StateVector   = std::vector< State >;
    using Action        = std::int32_t;
    using ActionVector  = std::vector< Action >;
    
    
    
    
    std::string getVersion();
    
    
    
    
    
}


#endif //AUTOMATA_16_11_2019