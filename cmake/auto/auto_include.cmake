


cmake_minimum_required(VERSION 3.14.2)

function( link_auto targetname )
	target_link_libraries( ${targetname} automatalib )
endfunction( link_auto )
