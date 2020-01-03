

#include "automata.hpp"
#include "glm_graph_traits.hpp"

#include "common/file.hpp"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/graph/graphml.hpp>

#include <iostream>
#include <string>
#include <vector>
 

void command_generate( bool bHelp, const std::vector< std::string >& args )
{
    boost::filesystem::path inputFilePath;
    boost::filesystem::path inputFilePath2;
    
    int xSize = 4;
    int ySize = 4;
    int components = 1;
            
    namespace po = boost::program_options;
    po::options_description commandOptions(" Generate Graph Command");
    {
        commandOptions.add_options()
            ("file",        po::value< boost::filesystem::path >( &inputFilePath ),     "GraphML file to generate"  )
            ("file2",       po::value< boost::filesystem::path >( &inputFilePath2 ),    "GraphML file to generate"  )
            ("x",           po::value< int >( &xSize ),                                 "Size in x dimension"       )
            ("y",           po::value< int >( &ySize ),                                 "Size in y dimension"       )
            ("components",  po::value< int >( &components ),                            "Number of components"      )
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
                
        if( components == 1 )
        {
            glmGrid::GraphTraits::Graph graph = glmGrid::generate_grid( xSize, ySize );
            std::ofstream outputFileStream( graphFilePath.string() );
            std::cout << "Generating file: " << graphFilePath.string() << std::endl;
            glmGrid::GraphTraits::save( outputFileStream, graph, glmGrid::get_dynamic_properties( graph ) );
            
            if( !inputFilePath2.empty() )
            {
                glmGrid::GraphTraits::Graph graph2;
                {
                    std::ifstream inputFileStream( graphFilePath.string() );
                    std::cout << "Loading file: " << graphFilePath.string() << std::endl;
                    glmGrid::GraphTraits::load( inputFileStream, graph2, glmGrid::get_dynamic_properties( graph2 ) );
                }
                
                const boost::filesystem::path graphFilePath2 = 
                    boost::filesystem::edsCannonicalise(
                        boost::filesystem::absolute( inputFilePath2 ) );
                std::ofstream outputFileStream( graphFilePath2.string() );
                std::cout << "Generating file: " << graphFilePath2.string() << std::endl;
                glmGrid::GraphTraits::save( outputFileStream, graph2, glmGrid::get_dynamic_properties( graph2 ) );
            }
            
        }
        else
        {
            
            glmMultiGrid::GraphTraits::Graph graph = glmMultiGrid::generate_grid( xSize, ySize, components );
            {
                std::pair< glmMultiGrid::GraphTraits::VertexIter, glmMultiGrid::GraphTraits::VertexIter >
                    vertices = boost::vertices( graph );
                    
                std::pair< glmMultiGrid::GraphTraits::EdgeIter, glmMultiGrid::GraphTraits::EdgeIter >
                    edges = boost::edges( graph );
                    
                std::cout << "Generated: " << std::distance( vertices.first, vertices.second ) << 
                    " vertices with: " << std::distance( edges.first, edges.second ) << " edges." << std::endl;
            }
            
            std::ofstream outputFileStream( graphFilePath.string() );
            std::cout << "Generating file: " << graphFilePath.string() << std::endl;
            glmMultiGrid::GraphTraits::save( outputFileStream, graph, glmMultiGrid::get_dynamic_properties( graph ) );
        }
        
    }
}
