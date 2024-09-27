Instruction Page Manual: man()

NAME
	man: An interface to systems reference manuals

SYNOPSIS
	man[man options]

DESCRIPTION
	Manual instruction framwork for various xv6 functions and programs. Man
	allows for easy documentation and help within the operating system, 
	displaying the requested man page. 

EXAMPLES
	man - brings up the man page for man()
	
	man ls - brings up the man page for ls()

	man man -f grow - brings up the man page for man() then searchs for the 
	word "grow", showing only lines containing it

OPTIONS
	-f - Flag for find

HISTORY
	9/23/24 - Creation

AUTHOR
	Written by Daniel Truong
