//  Copyright (c) Deighton Systems Limited. 2019. All Rights Reserved.
//  Author: Edward Deighton
//  License: Please see license.txt in the project root folder.

//  Use and copying of this software and preparation of derivative works
//  based upon this software are permitted. Any copy of this software or
//  of any derivative work must include the above copyright notice, this
//  paragraph and the one after it.  Any distribution of this software or
//  derivative works must comply with all applicable laws.

//  This software is made available AS IS, and COPYRIGHT OWNERS DISCLAIMS
//  ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE, AND NOTWITHSTANDING ANY OTHER PROVISION CONTAINED HEREIN, ANY
//  LIABILITY FOR DAMAGES RESULTING FROM THE SOFTWARE OR ITS USE IS
//  EXPRESSLY DISCLAIMED, WHETHER ARISING IN CONTRACT, TORT (INCLUDING
//  NEGLIGENCE) OR STRICT LIABILITY, EVEN IF COPYRIGHT OWNERS ARE ADVISED
//  OF THE POSSIBILITY OF SUCH DAMAGES.

#include <automata.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <iomanip>
#include <bitset>

extern void command_generate( bool bHelp, const std::vector< std::string >& args );


enum MainCommand
{
    eCmd_Generate,
    TOTAL_MAIN_COMMANDS
};

int main( int argc, const char* argv[] )
{
    bool bWait = false;
    
    std::bitset< TOTAL_MAIN_COMMANDS > cmds;
    MainCommand cmd = TOTAL_MAIN_COMMANDS;
    
    //commands
    
    {
        std::vector< std::string > commandArgs;
    
        namespace po = boost::program_options;
        po::variables_map vm;
        try
        {
            bool bGeneralWait = false;
            
            bool bCmdGenerate = false;
            
            po::options_description genericOptions(" General");
            {
                genericOptions.add_options()
                
                    ("help", "Produce general or command help message")
                    ("wait", po::bool_switch( &bGeneralWait ), "Wait at startup for attaching a debugger" )
                ;
            }
            
            po::options_description commandOptions(" Commands");
            {
                
                commandOptions.add_options()
                        
                    ("generate",  po::bool_switch( &bCmdGenerate ), "Generate a graph" )
                ;
            }
            
            if( cmds.count() > 1 )
            {
                std::cout << "Invalid command combination. Type '--help' for options\n";
                return 1;
            }
            
            po::options_description commandHiddenOptions( "" );
            {
                commandHiddenOptions.add_options()
                    ( "args", po::value< std::vector< std::string > >( &commandArgs ) )
                    ;
            }

            po::options_description visibleOptions( "Allowed options" );
            visibleOptions.add( genericOptions ).add( commandOptions );
            
            po::options_description allOptions( "all" );
            allOptions.add( genericOptions ).add( commandOptions ).add( commandHiddenOptions );

            po::positional_options_description p;
            p.add( "args", -1 );
            
            po::parsed_options parsedOptions =
                po::command_line_parser( argc, argv ).
                            options( allOptions ).
                            positional( p ).
                            allow_unregistered().
                            run();
            
            po::store( parsedOptions, vm );
            po::notify( vm );
            
            if( bGeneralWait )
            {
                std::cout << "Waiting for input..." << std::endl;
                char c;
                std::cin >> c;
            }
            
            if( bCmdGenerate )
            {
                cmds.set( eCmd_Generate );
                cmd = eCmd_Generate;
            }
            
            const bool bShowHelp = vm.count("help");
            
            std::vector< std::string > commandArguments = 
                po::collect_unrecognized( parsedOptions.options, po::include_positional );
                
            switch( cmd )
            {                
                case eCmd_Generate        : command_generate( bShowHelp, commandArguments );                   break;
                case TOTAL_MAIN_COMMANDS  :
                default:
                    if( vm.count( "help" ) )
                    {
                        std::cout << visibleOptions << "\n";
                    }
                    else
                    {
                        std::cout << "Invalid command. Type '--help' for options\n";
                        return 1;
                    }
            }
            return 0;
        }
        catch( boost::program_options::error& e )
        {
            std::cout << "Invalid input. " << e.what() << "\nType '--help' for options" << std::endl;
            return 1;
        }
        /*catch( const xml_schema::parser_exception& e )
        {
            std::cout << e.what() << ": " << e.line () << ":" << e.column ()
             << ": " << e.text() << std::endl;
            return 1;
        }*/
        catch( std::exception& e )
        {
            std::cout << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}
