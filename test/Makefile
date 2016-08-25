TARGET := test

SRC := $(wildcard *.c)
SRC += ../matrix.c

OBJ := $(SRC:.c=.o)

CC := gcc

CFLAG  := -g
LDFLAG := -lm

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAG)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@
%.o: ../%.c
	$(CC) $(CFLAG) -c $< -o $@

.PHONY: clean run
clean:
	-rm -rf $(OBJ)

run:
	./$(TARGET)
