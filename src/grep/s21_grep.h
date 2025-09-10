#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct flags {
  char pattern[256];  // '\0'  "int|hello|file"
  bool e;             // -е шаблон
  bool i;  // -i игнорирует различия регистра
  bool v;  // -v инвертирует смысл поиска соответствий
  bool c;  // -с вывод только количества совпадающих строк
  bool l;  // -l вывод только совпадающих файлов
  bool n;  // -n предваряет каждую строку вывода номером строки из файла ввода
  bool h;  // -h вывод совпадающих строк, не предваряющих их именами файлов
  bool s;  // -s подавляет сообщения об ошибках о несуществующих или нечитаемых
           // файлах
  bool f;  // -f file получает регулярные выражения из файла
  bool o;  // -o печатает только совпадающие (непустые) части совпавшей строки
};

void print_file(char* name, struct flags flags);
int reading_arguments(int argc, char* argv[], struct flags* flags);
void read_pat_file(char* filename, char* pattern);
void add_pattern(char* patterns, char* pat);
void print_help();
void apply_flag_o(char* str, struct flags fl, char* name, int line_number,
                  regex_t re, regmatch_t rm);
