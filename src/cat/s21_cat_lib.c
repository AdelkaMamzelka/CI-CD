#include "s21_cat.h"

int show_hidden_symbols(char c) {
  int result = 0;
  if ((0 <= c && c < 32) && (c != 9 && c != 10)) {
    printf("^%c", c + 64);
    result = 1;
  } else if (c == 127) {
    printf("^?");
    result = 1;
  }
  return result;
}

void print_file(char* name, struct flags fl) {
  FILE* f = fopen(name, "rt");
  if (f == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n", name);
    return;
  }

  char c;
  int line_number = 1;  // Нумерация строк начинается с 1
  int nonblank_n = 1;  //непустые строки
  char prev_prev_c = ' ';
  char prev_c = '\n';
  // Попытка прочесть файл
  while ((c = fgetc(f)) != EOF) {
    bool nprintc_flag = false;  //не печатать теккущий символ

    if (fl.squeeze_blank && prev_prev_c == '\n' && prev_c == '\n' &&
        c == '\n') {
      nprintc_flag = true;
    } else {
      if (fl.number_nonblank) {
        if (prev_c == '\n' && c != '\n')  // the string is not empty
          printf("%6d\t", nonblank_n++);
        else if (fl.big_show_money && (prev_c == '\n' && c == '\n'))
          printf("      \t");
      } else if (fl.numbered && prev_c == '\n') {
        printf("%6d\t", line_number++);
      }

      // Проверка на табуляцию
      if (fl.big_tab && c == '\t') {
        putchar('^');
        putchar('I');
        nprintc_flag = true;
      }

      if (fl.flag_v) {
        int cod = show_hidden_symbols(c);
        if (cod == 1) nprintc_flag = true;
      }

      prev_prev_c = prev_c;
      prev_c = c;
      if (fl.big_show_money && c == '\n') putchar('$');
    }
    if (!nprintc_flag) putchar(c);
  }
  fclose(f);
}

int reading_arguments(int argc, char* argv[], struct flags* fl) {
  int result = 0;

  for (int i = 1; i < argc && result == 0; i++) {
    if (argv[i][0] == '-') {
      int len = strlen(argv[i]);
      if (len > 1) {
        if (argv[i][1] == '-') {
          if (strcmp(argv[i], "--number-nonblank") == 0) {  // -b
            fl->number_nonblank = true;
            fl->numbered = false;
          } else if (strcmp(argv[i], "--number") == 0) {  // -n
            if (fl->number_nonblank == false) fl->numbered = true;
          } else if (strcmp(argv[i], "--squeeze-blank") == 0) {  // -s
            fl->squeeze_blank = true;
          }
        } else {
          for (int j = 1; j < len; j++) {
            switch (argv[i][j]) {
              case 'b':
                fl->number_nonblank = true;
                fl->numbered = false;
                break;
              case 'n':
                if (fl->number_nonblank == false) fl->numbered = true;
                break;
              case 'e':
                fl->big_show_money = true;
                fl->flag_v = true;
                break;
              case 'E':
                fl->big_show_money = true;
                break;
              case 's':
                fl->squeeze_blank = true;
                break;
              case 't':
                fl->big_tab = true;
                fl->flag_v = true;
                break;
              case 'T':
                fl->big_tab = true;
                break;
              case 'v':
                fl->flag_v = true;
                break;
              default:
                printf("cat: illegal option -- %c", argv[i][1]);
                result = 1;
            }
          }
        }
      }
    }
  }
  return result;
}
