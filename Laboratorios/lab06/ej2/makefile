# Variables
FLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
COMPILER = gcc
SRC = main.c string.c											#archivos.c a compilar
EXECUTABLE = runp									#nombre del ejecutable -> no cambiar

# Tanto para run, gdb, valgrind, si tiene que tomar un archivo como input hacer make ... FILE=ruta/al/archivo

# Reglas
all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC:.c=.o) 
	$(COMPILER) $(FLAGS) -o $@ $^

%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(FILE)

gdb: $(EXECUTABLE)
	gdb --args ./$(EXECUTABLE) $(FILE)

valgrind: $(EXECUTABLE)
	valgrind --track-origins=yes --leak-check=full ./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) *.o

.PHONY: clean run gdb valgrind
