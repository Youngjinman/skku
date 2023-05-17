# Makefile

TARGET=pa2
CXX=gcc
OBJECTS=pa2.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^
pa2.o: pa2.c
	$(CXX) -c pa2.c
.PHONY: clean
clean:
	rm *.o pa2


