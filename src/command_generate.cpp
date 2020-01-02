

#include "automata.hpp"

#include "common/file.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/graph/graphml.hpp>

#include <iostream>
#include <string>
#include <vector>


namespace std
{
    inline std::ostream& operator<<( std::ostream& os, const glm::vec2& pos )
    {
        return os << '{' << pos.x << ',' << pos.y << '}';
    }
    inline std::istream& operator>>( std::istream& is, glm::vec2& pos )
    {
        char c;
        return is >> c >> pos.x >> c >> pos.y >> c;
    }
}


struct GeometryTraits
{
    using point2d = glm::vec2;
};

using GraphTraits = automata::AutomataTraits< int, int, GeometryTraits >;


void command_generate( bool bHelp, const std::vector< std::string >& args )
{
    boost::filesystem::path inputFilePath;
    
    namespace po = boost::program_options;
    po::options_description commandOptions(" Generate Graph Command");
    {
        commandOptions.add_options()
            ("file",    po::value< boost::filesystem::path >( &inputFilePath ), "GraphML file to generate")
        ;
    }
    
    po::variables_map vm;
    po::store( po::command_line_parser( args ).options( commandOptions ).run(), vm );
    po::notify( vm );
    
    if( bHelp )
    {
        std::cout << commandOptions << "\n";
    }
    else
    {
        
        
        GraphTraits::Graph graph( 4 );
        
        
        {
            graph[ 0 ].index = 123;
            graph[ 1 ].index = 124;
            graph[ 2 ].index = 125;
            graph[ 3 ].index = 126;
            
            graph[ 0 ].label = 23;
            graph[ 1 ].label = 24;
            graph[ 2 ].label = 25;
            graph[ 3 ].label = 26;
            
            graph[ 0 ].position = glm::vec2( 0, 0 );
            graph[ 1 ].position = glm::vec2( 1, 0 );
            graph[ 2 ].position = glm::vec2( 0, 1 );
            graph[ 3 ].position = glm::vec2( 1, 1 );
        }
        
        using Edge = std::pair< int, int >;
        Edge edges[] = 
        {
            Edge( 0, 1 ),
            Edge( 1, 2 ),
            Edge( 2, 3 )
        };
        
        for( const Edge& edge : edges )
        {
            boost::add_edge( edge.first, edge.second, graph );
        }
        
        const boost::filesystem::path graphFilePath = 
            boost::filesystem::edsCannonicalise(
                boost::filesystem::absolute( inputFilePath ) );
                
        GraphTraits::save( graphFilePath.string(), graph );
        
                
        std::cout << "Generating GraphML file: " << graphFilePath.string() << std::endl;
        
    }
}
