#include "s21_cat.h"

int main(int argc, char* argv[]) {
  struct flags fl = {false, false, false, false, false, false};
  int result = reading_arguments(argc, argv, &fl);
  if (result == 0) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
        continue;
      }
      print_file(argv[i], fl);
    }
  }
  return result;
}
