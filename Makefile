CC=g++
LIBS=-lpthread -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
SRCDIR=src
INCLUDEDIR=include
all:
	$(CC) $(SRCDIR)/*.cpp -I$(INCLUDEDIR) $(LIBS) -o dogoo -std=c++11

clean:
	rm dogoo 
runCli:
	./dogoo cli
run:
	./dogoo 
