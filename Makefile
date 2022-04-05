CC = gcc 
FLAGS = -c -Wall -ansi -pedantic
LIBRARY = -lm
T = Tests/

all: juego clean

command.o: command.c command.h
	$(CC) $(FLAGS) $<
	
enemy.o: enemy.c enemy.h
	$(CC) $(FLAGS) $< $(LIBRARY)
	
game_reader.o: game_reader.c game_reader.h command.h space.h types.h game.h
	$(CC) $(FLAGS) $<

game.o: game.c game.h command.h space.h types.h link.h player.h object.h enemy.h inventory.h
	$(CC) $(FLAGS) $<
	
graphic_engine.o: graphic_engine.c graphic_engine.h libscreen.h command.h space.h types.h inventory.h set.h
	$(CC) $(FLAGS) $< $(LIBRARY)

link.o: link.c link.h
	$(CC) $(FLAGS) $<
	
object.o: object.c object.h types.h
	$(CC) $(FLAGS) $< $(LIBRARY)
	
player.o: player.c player.h object.h inventory.h
	$(CC) $(FLAGS) $< $(LIBRARY)
	
set.o: set.c set.h
	$(CC) $(FLAGS) $<

inventory.o: inventory.c inventory.h set.h
	$(CC) $(FLAGS) $<

space.o: space.c space.h types.h set.h object.h
	$(CC) $(FLAGS) $< $(LIBRARY)

game_loop.o: game_loop.c game.h command.h graphic_engine.h
	$(CC) $(FLAGS) $< 

juego: command.o game.o game_reader.o graphic_engine.o object.o link.o player.o space.o game_loop.o libscreen.a enemy.o set.o inventory.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

#GAME
run:
	@echo ">>>>>>Running main"
	./juego hormiguero.dat

runcmd1:
	@echo ">>>>>>Running main from partida1.cmd"
	./juego hormiguero.dat < partida1.cmd 

runcmd2:
	@echo ">>>>>>Running main from partida2.cmd"
	./juego hormiguero.dat < partida2.cmd
	
runlog:
	@echo ">>>>>>Running main and saving commands in file.log"
	./juego hormiguero.dat -l file.log

runcmd1log:
	@echo ">>>>>>Running main from partida1.cmd and saving in file.log"
	./juego hormiguero.dat -l file.log < partida1.cmd 

runvcmd1log:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./juego hormiguero.dat -l file.log < partida1.cmd 

juego_permisos: juego
	chmod u+x ./juego

#ENEMY_TEST
enemy_test.o: $(T)enemy_test.c $(T)enemy_test.h $(T)test.h enemy.h
	$(CC) $(FLAGS) $<

enemy_test: enemy_test.o enemy.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

venemy_test: enemy_test
	valgrind --leak-check=full ./enemy_test


#SET_TEST
set_test.o: $(T)set_test.c $(T)set_test.h $(T)test.h set.h
	$(CC) $(FLAGS) $<

set_test: set_test.o set.o 
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vset_test: set_test
	valgrind --leak-check=full ./set_test


#SPACE_TEST
space_test.o: $(T)space_test.c $(T)space_test.h $(T)test.h space.h
	$(CC) $(FLAGS) $<

space_test: space_test.o space.o object.o set.o link.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vspace_test: space_test
	valgrind --leak-check=full ./space_test


#INVENTORY_TEST
inventory_test.o: $(T)inventory_test.c $(T)inventory_test.h $(T)test.h inventory.h
	$(CC) $(FLAGS) $<

inventory_test: inventory_test.o inventory.o object.o set.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vinventory_test: inventory_test
	valgrind --leak-check=full ./inventory_test
	

#OBJECT_TEST
object_test.o: $(T)object_test.c $(T)object_test.h $(T)test.h object.h
	$(CC) $(FLAGS) $<

object_test: object_test.o space.o object.o set.o link.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vobject_test: object_test
	valgrind --leak-check=full ./object_test
	
	
#PLAYER_TEST
player_test.o: $(T)player_test.c $(T)player_test.h $(T)test.h player.h
	$(CC) $(FLAGS) $<

player_test: player_test.o player.o object.o set.o inventory.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vplayer_test: player_test
	valgrind --leak-check=full ./player_test


#LINK_TEST
link_test.o: $(T)link_test.c $(T)link_test.h $(T)test.h link.h
	$(CC) $(FLAGS) $<

link_test: link_test.o link.o space.o set.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vlink_test: link_test
	valgrind --leak-check=full ./link_test


#GAME_TEST
game_test.o: $(T)game_test.c $(T)game_test.h $(T)test.h game.h
	$(CC) $(FLAGS) $<

game_test: game_test.o game.o object.o space.o player.o enemy.o inventory.o set.o link.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)
	make testclean

vgame_test: game_test
	valgrind --leak-check=full ./game_test
	

all_test:
	make player_test
	make object_test
	make inventory_test
	make set_test
	make enemy_test
	make link_test

#CLEAN
clean:
	rm -f *.o
	rm -f *.h.gch

xclean:
	rm -f juego
	rm -f *_test

sclean: clean xclean

testclean: clean
	rm -f $(T)*.h.gch
