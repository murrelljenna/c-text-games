bat:
	gcc battleship.c tlib.c pst.c -lm -o battleship
tic:
	gcc tictactoe.c tlib.c pst.c -lm -o tictactoe
add:
	git add Makefile tictactoe.c tlib.c pst.c battleship.c tiles.h
	git commit
edit:
	vim -p battleship.c tictactoe.c pst.c tlib.c tiles.h
