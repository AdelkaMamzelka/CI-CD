CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -ggdb
LDFLAGS=
SOURCES=s21_grep.c s21_grep_lib.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=s21_grep
TEST_SOURSES=tests_grep.sh

all: test

test: s21_grep $(TEST_SOURCES)
	bash tests_grep.sh
	
#s21_grep
s21_grep: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

rebuild:
	make cleanall
	make

.c.o: $(CC) $(CFLAGS) $< -o $@

cleanall:
	rm -rf $(OBJECTS) $(EXECUTABLE)
