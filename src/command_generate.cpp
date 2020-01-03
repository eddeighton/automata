

#include "automata.hpp"
#include "glm_graph_traits.hpp"

#include "common/file.hpp"


#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/graph/graphml.hpp>

#include <iostream>
#include <string>
#include <vector>

inline int xyIndex( int x, int y, int xSize )
{
    return x * xSize + y;
}

GraphTraits::Graph generate_grid( int xSize, int ySize )
{
    GraphTraits::Graph graph( xSize * ySize );
    
    int iIndex = 0;
    for( int x = 0; x < xSize; ++x )
    {
        for( int y = 0; y < ySize; ++y )
        {
            iIndex = xyIndex( x, y, xSize );
            graph[ iIndex ].index = iIndex;
            graph[ iIndex ].label = iIndex;
            graph[ iIndex ].position = glm::vec2( x - xSize / 2, y - ySize / 2 );
        }
    }
    
    int iEdgeIndex = 0;
    for( int x = 0; x < xSize; ++x )
    {
        for( int y = 0; y < ySize; ++y )
        {
            iIndex = xyIndex( x, y, xSize );
            
            if( x > 0 )
            {
                auto e = boost::add_edge( iIndex, xyIndex( x - 1, y, xSize ), graph );
                graph[ e.first ].index = iEdgeIndex++;
                graph[ e.first ].action = 0;
                graph[ e.first ].continuation = 0;
                graph[ e.first ].weight = 1;
            }
            if( x < xSize - 1 )
            {
                auto e = boost::add_edge( iIndex, xyIndex( x + 1, y, xSize ), graph );
                graph[ e.first ].index = iEdgeIndex++;
                graph[ e.first ].action = 1;
                graph[ e.first ].continuation = 1;
                graph[ e.first ].weight = 1;
            }
            
            if( y > 0 )
            {
                auto e = boost::add_edge( iIndex, xyIndex( x, y - 1, xSize ), graph );
                graph[ e.first ].index = iEdgeIndex++;
                graph[ e.first ].action = 2;
                graph[ e.first ].continuation = 2;
                graph[ e.first ].weight = 1;
            }
            if( y < ySize - 1 )
            {
                auto e = boost::add_edge( iIndex, xyIndex( x, y + 1, xSize ), graph );
                graph[ e.first ].index = iEdgeIndex++;
                graph[ e.first ].action = 3;
                graph[ e.first ].continuation = 3;
                graph[ e.first ].weight = 1;
            }
        }
    }
    return graph;
}    

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
        const int xSize = 25;
        const int ySize = 25;
        
        GraphTraits::Graph graph = generate_grid( xSize, ySize );
        
        const boost::filesystem::path graphFilePath = 
            boost::filesystem::edsCannonicalise(
                boost::filesystem::absolute( inputFilePath ) );
                
        std::ofstream outputFileStream( graphFilePath.string() );
                
        GraphTraits::save( outputFileStream, graph );
        
        std::cout << "Generating GraphML file: " << graphFilePath.string() << std::endl;
        
    }
}
