#include "s21_grep.h"

void print_file(char* name, struct flags fl) {
  FILE* f = fopen(name, "r");
  if (f == NULL) {
    if (!fl.s) fprintf(stderr, "grep: %s: No such file or directory\n", name);
    return;
  }
  regex_t re = {};
  regmatch_t rm = {};
  int reti;
  int cflag = REG_EXTENDED | REG_NEWLINE;
  if (fl.i) cflag |= REG_ICASE;
  reti = regcomp(&re, fl.pattern, cflag);
  if (reti == 0) {
    char str[2 * 256];                      // кол-во строк
    int line_number = 0, number_match = 0;  //кол-во совпадающих строк -с
    while (fgets(str, sizeof(str), f) != NULL) {
      line_number++;
      reti =
          regexec(&re, str, 1, &rm, 0);  //поиск регулярного выражения в строке
      if (fl.v) {
        fl.o = false;
        reti = !reti;
      }
      if (reti == 0) {  // если паттерн был найден
        number_match++;
        if (!fl.l && !fl.c && !fl.o) {
          if (!fl.h)
            printf("%s:", name);  // если -h выключен, а кол-во файлов больше
                                  // 1-го, то печатаем названия файлов
          if (fl.n) printf("%d:", line_number);
          printf("%s", str);  // печать строк, соответствующих рег выражению
        }

        if (fl.o) apply_flag_o(str, fl, name, line_number, re, rm);
      }
    }
    if (fl.c) {
      if (!fl.h) printf("%s:", name);
      if (!fl.l)
        printf("%d\n", number_match);
      else
        printf("%d\n", number_match > 0 ? 1 : 0);
    }
    if (fl.l && number_match > 0) printf("%s\n", name);
    regfree(&re);  // освобождние памяти из-под компилированного рег выражению
  } else
    fprintf(stderr, "Ошибка компиляции регулярного выражения\n");
  fclose(f);
}

void apply_flag_o(char* str, struct flags fl, char* name, int line_number,
                  regex_t re, regmatch_t rm) {
  char* s = str;
  int reti = 0;
  while (reti == 0) {
    if (!fl.l && !fl.c) {
      if (!fl.h) printf("%s:", name);
      if (fl.n) printf("%d:", line_number);
      size_t rmlen = rm.rm_eo - rm.rm_so;  // dlina podstroki
      char temp_str[256];
      strncpy(temp_str, s + rm.rm_so, rmlen);
      temp_str[rmlen] = '\0';
      printf("%s\n", temp_str);
    }
    s += rm.rm_eo;  // smeshenie otn-no pred. naidennoy podstroki
    reti = regexec(&re, s, 1, &rm, 0);
  }
}

int reading_arguments(int argc, char* argv[], struct flags* fl) {
  int option = 0;
  int result = 0;
  opterr = 0;
  while ((option = getopt(argc, argv, "e:ivclnhsof:")) != -1) {
    switch (option) {
      case 'e':
        fl->e = true;
        add_pattern(fl->pattern, optarg);
        break;
      case 'i':
        fl->i = true;
        break;
      case 'c':
        fl->c = true;
        break;
      case 'l':
        fl->l = true;
        break;
      case 'v':
        fl->v = true;
        break;
      case 'n':
        fl->n = true;
        break;
      case 'h':
        fl->h = true;
        break;
      case 's':
        fl->s = true;
        break;
      case 'f':  // -f f_name
        fl->f = true;
        read_pat_file(optarg, fl->pattern);
        break;
      case 'o':
        fl->o = true;
        break;
      default:  // '?'
        fprintf(stderr, "grep: invalid option -- %c\n", optopt);
        print_help();
        result = 2;
    }
  }
  return result;
}

void read_pat_file(char* filename, char* patterns) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    return;
  }
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    add_pattern(patterns,
                buffer);  // добавление содержимого файла к паттерну построчно
  }
  fclose(file);
}

void add_pattern(char* patterns, char* pat) {
  int len = strlen(patterns);  // длина паттерна fl.pattern
  if (len > 0) {
    patterns[len] = '|';
    patterns[len + 1] = '\0';  // "main|hello"\0
  }
  strcat(patterns, pat);  // добавление паттерна
}

void print_help() {
  fprintf(stderr,
          "usage: grep [-abcdDEFGHhIiJLlMmnOopqRSsUVvwXxZz] [-A num] [-B num] "
          "[-C[num]]\n");
  fprintf(stderr,
          "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
  fprintf(stderr,
          "\t[--context[=num]] [--directories=action] [--label] "
          "[--line-buffered]\n");
  fprintf(stderr, "\t[--null] [pattern] [file ...]\n");
}
