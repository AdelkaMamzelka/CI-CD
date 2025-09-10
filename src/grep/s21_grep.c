#include "s21_grep.h"

int main(int argc, char* argv[]) {
  int result = 0;
  struct flags fl = {};  // инициализация
  fl.pattern[0] = '\0';  // strlen конец строки
  if (argc == 1) {
    print_help();
    result = 2;
  } else {
    result = reading_arguments(argc, argv, &fl);
    if (result == 0) {
      int i = optind;
      if (!fl.e && !fl.f) {
        add_pattern(fl.pattern, argv[i]);
        i++;
      }
      if (argc - i < 2)
        fl.h = true;  // сколько файлов, если больше 2х, то печатаем

      for (; i < argc; i++) {
        print_file(argv[i], fl);
      }
    }
  }
  return result;
}
