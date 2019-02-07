#c-text-games

##Introduction:

C-text-games is a set of simple 2-player command line text games for linux. The games are written in C and have no other dependencies. 

The game is played by 2 players either hot-seat style or live with one-another. This is accomplished through a very simple text save file written to, and read from, by each player as they make their turns. Each game session has a corresponding text file created by the player at the beginning of that session.

Usage: ./<game> [-n] [<filename>]
Use [-n] to create new file, omit to load existing file

Use the Makefile to compile the modules. Run the game by running the resulting executables. You must then also pass the name of a save file (it can be any name you want) in as a parameter when running a game. Add the flag '-n' when creating this file for the first time. Omiting the flag tells the program to load an existing save of that name - do this when you want to continue a previously saved game. Also - and this is important - you must give others +rw privileges in order for them to be able to properly load any game files you create. This must currently done manually.

As mentioned before, you can play "hot-seat" or live. The game is played over SSH on a single server computer. The program matches a player in the game to their linux userid, so you can exit and join back at any time without the game losing your information. You and your opponent can make moves whether or not the other player is present in the game. Once you make your move you will simply be prompted to wait for your opponent's move - you can remain in-game and wait or log off and check back later.

##Setup:

Use the Makefile in the source directory. The following commands, run in the source folder, will compile new game executables: 

	- make bat (battleship)
	- make tic (tictactoe).

##GitHub:

https://github.com/murrelljenna/c-text-games 
git@github.com:murrelljenna/c-text-games.git

Written by Jenna Murrell, a Computer Programming & Analysis student at Seneca College, Toronto, ON.
