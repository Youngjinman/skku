# Makefile

TARGET=ex3
CXX=gcc
OBJECTS=p5.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^
p5.o: p5.c
	$(CXX) -c p5.c
.PHONY: clean
clean:
	rm *.o 
