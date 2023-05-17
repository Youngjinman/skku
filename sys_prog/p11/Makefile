# Makefile

TARGET=p11
CXX=gcc
OBJECTS=exercise.o
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ -lpthread
exercise.o: exercise.c
	$(CXX) -c exercise.c
.PHONY: clean
clean:
	rm *.o p11

