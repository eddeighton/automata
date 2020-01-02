
#include <string>
#include <vector>

#include "common/file.hpp"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <iostream>

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
        const boost::filesystem::path graphFilePath = 
            boost::filesystem::edsCannonicalise(
                boost::filesystem::absolute( inputFilePath ) );
                
        std::cout << "Generating GraphML file: " << graphFilePath.string() << std::endl;
        
    }
}
