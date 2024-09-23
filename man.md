Instruction Page Manual: man()

NAME
	man: An interface to systems reference manuals

SYNOPSIS
	man[man options]

DESCRIPTION
	Manual instruction framwork for various xv6 functions and programs. Man
	allows for easy documentation and help within the operating system.

EXAMPLES
	man - brings up the man page for man()
	
	man ls - brings up the man page for ls()

	man man grow - brings up the man page for man() then searchs for and highlights
	the word "grow"

OPTIONS
	arg[2] - Word to find and highlight

HISTORY
	9/23/24-Creation
