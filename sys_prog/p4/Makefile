# Makefile

TARGET=ex4
CXX=gcc
OBJECTS=main.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^
main.o: main.c
	$(CXX) -c main.c
.PHONY: clean
clean:
	rm *.o ex4 
