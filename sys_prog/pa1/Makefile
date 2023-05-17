# Makefile

TARGET=pa1
CXX=gcc
OBJECTS=pa1.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^
pa1.o: pa1.c
	$(CXX) -c pa1.c
.PHONY: clean
clean:
	rm *.o pa1

