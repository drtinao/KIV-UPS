gameserver: game_logic.o  game_room_part.o main.o player_part.o server.o
	gcc game_logic.o  game_room_part.o main.o player_part.o server.o -lm -o gameserver

game_logic.o: game_logic.c game_logic.h
	gcc game_logic.c -lm -c

game_room_part.o: game_room_part.c game_room_part.h
	gcc game_room_part.c -lm -c

main.o: main.c
	gcc main.c -lm -c

player_part.o: player_part.c player_part.h
	gcc player_part.c -lm -c

server.o: server.c server.h
	gcc server.c -lm -c
	 
