#Directorios
OBJ_DIR=obj
BIN_DIR=bin
SRC_DIR=src

#Archivos
FILES = main algoritmo_bresenham keys dibujar cargar_provincias
OBJECTS=$(patsubst %, $(OBJ_DIR)/%.o, $(FILES))
OUTPUT=$(BIN_DIR)/main

######
CFLAGS=-I/usr/local/Mesa-3.4/include $(shell pkg-config --cflags json-c)
LDLIBS=-lX11 -lglut -lGLU -lGL -lm -lXext -lXmu
LDFLAGS=-L/usr/local/Mesa-3.4/lib -L/usr/X11R6/lib $(shell pkg-config --libs json-c)

######
$(OUTPUT): $(OBJECTS)
	mkdir -p bin
	gcc $(OBJECTS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p obj
	gcc -g  $(shell pkg-config --cflags json-c) -c -MMD $< -o $@


-include $(OBJ_DIR)/*.d

run: $(OUTPUT)
	./$(OUTPUT) $(r)

valgrind: $(OUTPUT)
	valgrind ./$(OUTPUT) $(r)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)