OS := $(shell uname)

$(info $(OS))

G_FLAGZ= -Wall -g -fPIC

ifeq ($(OS), Darwin)
    FLAGZ=$(G_FLAGZ) -ldl -fPIC
else
    FLAGZ=$(G_FLAGZ) -ldl -fPIC
endif

EXEC = vpm
SOURCES := $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

$(info $(OBJECTS_NO_MAIN))

$(EXEC): $(OBJECTS)
	gcc $(OBJECTS) $(FLAGZ) -o $(EXEC) -fPIC

%.o: %.c includes/%.h
	gcc -c $(G_FLAGZ) $< -o $@ -fPIC

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
