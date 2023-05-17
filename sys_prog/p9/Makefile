# Makefile

TARGET=p9
CXX=gcc
OBJECTS=p9.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^
p9.o: p9.c
	$(CXX) -c p9.c
.PHONY: clean
clean:
	rm *.o p9

