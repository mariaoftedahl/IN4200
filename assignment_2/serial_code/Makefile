CC = gcc
FLAGS = -O2
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ 			= serial_main
SRC 			:= $(wildcard *.c)

all: simple-jpeg $(PROJ)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

$(PROJ): $(SRC)
	$(CC) $(FLAGS) $(SRC) -lm -o $@ $(LDFLAGS)

obj-clean:
	$(RM) *.o

exec-clean:
	$(RM) $(PROJ)

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../simple-jpeg clean