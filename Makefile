TARGET=prog.exe
SDIR=./src
IDIR=./include ./libraries/include
LDIR=./libraries/lib
ODIR=./obj
CC=gcc

LIBS=-l:libglfw3.a -lgdi32
CFLAGS=-Wall $(patsubst %,-I%,$(IDIR))

OBJ = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(wildcard $(SDIR)/*.c))
INC = $(wildcard $(IDIR)/*.h)

.PHONY: default clean
default: $(TARGET)

$(ODIR):
	mkdir $@

$(ODIR)/%.o: $(SDIR)/%.c $(INC) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ) $(INC) | $(ODIR)
	$(CC) $(OBJ) $(CFlAGS) $(patsubst %,-L%,$(LDIR)) $(LIBS) -o $@

clean:
	rm -f $(ODIR)/*.o $(TARGET)
