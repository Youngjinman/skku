# Makefile

TARGET=p7
CXX=gcc
OBJECTS=sig.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^
sig.o: sig.c
	$(CXX) -c sig.c
.PHONY: clean
clean:
	rm *.o p7

