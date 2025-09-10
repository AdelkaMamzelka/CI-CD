C=gcc
CFLAGS=-c -Wall -Werror -Wextra -ggdb
LDFLAGS=
SOURCES=s21_cat.c s21_cat_lib.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=s21_cat
TEST_SOURSES=tests.sh

all: test

test: s21_cat $(TEST_SOURCES)
	bash tests.sh

#s21_cat.a: $(SOURCES)
#	$(CC) $(CFLAGS) -c $(SOURCES)
#	ar cr s21_cat.a *.o

#s21_cat
s21_cat: $(OBJECTS)
	$(C) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

rebuild:
	make cleanall
	make

.c.o: $(CC) $(CFLAGS) $< -o $@

cleanall:
	rm -rf $(OBJECTS) $(EXECUTABLE)

