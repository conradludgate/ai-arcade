IDIR=include
CC=g++
CFLAGS=-I $(IDIR)

ODIR=build/obj
SDIR=src

LIBS=-std=c++1z -lsfml-graphics -lsfml-window -lsfml-system

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.cpp $(DEPS)
	mkdir -p ${ODIR}
	$(CC) -c -o $@ $< $(CFLAGS)

build/shooter: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~