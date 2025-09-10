#include <stdbool.h>  // логический тип данных
#include <stdio.h>
#include <string.h>

struct flags {
  bool number_nonblank;  // -b нумерация непустых строк
  bool numbered;  // -n нумерует все выходные строки
  bool big_show_money;  // -E отображает символы конца строки как $
  bool squeeze_blank;  // -s сжатие
  bool big_tab;        // -T проверка на большой таб
  bool flag_v;         // -v
};

int show_hidden_symbols(char c);
void print_file(char* name, struct flags fl);
int reading_arguments(int argc, char* argv[], struct flags* fl);
