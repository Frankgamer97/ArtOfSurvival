Game: main.o
	g++ -o Game main.o -lncurses

main.o: main.cpp Game.o
	g++ -c main.cpp -lncurses

Game.o: Game.cpp Game.hpp Animazioni.o
	g++ -c Game.cpp -lncurses

Animazioni.o: Animazioni.cpp Animazioni.hpp Livello.o
	g++ -c Animazioni.cpp -lncurses

Livello.o: Livello.cpp Livello.hpp Stanza.o
	g++ -c Livello.cpp -lncurses

Stanza.o: Stanza.cpp Stanza.hpp Giocatore.o
	g++ -c Stanza.cpp -lncurses

Giocatore.o: Giocatore.cpp Giocatore.hpp Personaggio.o
	g++ -c Giocatore.cpp -lncurses

Personaggio.o: Personaggio.cpp Personaggio.hpp IA_Persona.o
	g++ -c Personaggio.cpp -lncurses

IA_Persona.o: IA_Persona.cpp IA_Persona.hpp Persona.o
	 g++ -c IA_Persona.cpp -lncurses

Persona.o: Persona.cpp Persona.hpp Arma.o
	g++ -c Persona.cpp -lncurses

Arma.o: Arma.cpp Arma.hpp
	g++ -c Arma.cpp

clean:
	rm -f *.o Game

ncurses:
	sudo apt-get install ncurses-dev
