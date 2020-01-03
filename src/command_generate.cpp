

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

glmGrid::GraphTraits::Graph generate_grid( int xSize, int ySize )
{
    glmGrid::GraphTraits::Graph graph( xSize * ySize );
    
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
                graph[ e.first ].action = glmGrid::LEFT;
                graph[ e.first ].continuation = glmGrid::LEFT;
                graph[ e.first ].weight = 1.0f;
            }
            
            if( y > 0 )
            {
                auto e = boost::add_edge( iIndex, xyIndex( x, y - 1, xSize ), graph );
                graph[ e.first ].index = iEdgeIndex++;
                graph[ e.first ].action = glmGrid::UP;
                graph[ e.first ].continuation = glmGrid::UP;
                graph[ e.first ].weight = 1.0f;
            }
            
            if( x < xSize - 1 )
            {
                auto e = boost::add_edge( iIndex, xyIndex( x + 1, y, xSize ), graph );
                graph[ e.first ].index = iEdgeIndex++;
                graph[ e.first ].action = glmGrid::RIGHT;
                graph[ e.first ].continuation = glmGrid::RIGHT;
                graph[ e.first ].weight = 1.0f;
            }
            
            if( y < ySize - 1 )
            {
                auto e = boost::add_edge( iIndex, xyIndex( x, y + 1, xSize ), graph );
                graph[ e.first ].index = iEdgeIndex++;
                graph[ e.first ].action = glmGrid::DOWN;
                graph[ e.first ].continuation = glmGrid::DOWN;
                graph[ e.first ].weight = 1.0f;
            }
        }
    }
    return graph;
}    

void command_generate( bool bHelp, const std::vector< std::string >& args )
{
    boost::filesystem::path inputFilePath;
    boost::filesystem::path inputFilePath2;
    
    namespace po = boost::program_options;
    po::options_description commandOptions(" Generate Graph Command");
    {
        commandOptions.add_options()
            ("file",    po::value< boost::filesystem::path >( &inputFilePath ), "GraphML file to generate")
            ("file2",    po::value< boost::filesystem::path >( &inputFilePath2 ), "GraphML file to generate")
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
        const boost::filesystem::path graphFilePath = 
            boost::filesystem::edsCannonicalise(
                boost::filesystem::absolute( inputFilePath ) );
                
        const int xSize = 25;
        const int ySize = 25;
            
        {
            glmGrid::GraphTraits::Graph graph = generate_grid( xSize, ySize );
            std::ofstream outputFileStream( graphFilePath.string() );
            std::cout << "Generating file: " << graphFilePath.string() << std::endl;
            glmGrid::GraphTraits::save( outputFileStream, graph );
        }
        
        
        {
            glmGrid::GraphTraits::Graph graph2;
            {
                std::ifstream inputFileStream( graphFilePath.string() );
                std::cout << "Loading file: " << graphFilePath.string() << std::endl;
                glmGrid::GraphTraits::load( inputFileStream, graph2 );
            }
            
            const boost::filesystem::path graphFilePath2 = 
                boost::filesystem::edsCannonicalise(
                    boost::filesystem::absolute( inputFilePath2 ) );
            std::ofstream outputFileStream( graphFilePath2.string() );
            std::cout << "Generating file: " << graphFilePath2.string() << std::endl;
            glmGrid::GraphTraits::save( outputFileStream, graph2 );
        }
    }
}
