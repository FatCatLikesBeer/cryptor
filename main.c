#include "helpers.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char keybuff[256], *flag;
  int osc_index = 0, buff;

  keybuff[0] = '\0';
  flag = argv[1];

  // If first option is --help or -h or no first argument has been passed.
  // Print help and exit
  if (argc < 2) {
    print_help();
    return 0;
  }
  if (str_match("-h", flag) || str_match("--help", flag)) {
    print_help();
    return 0;
  }
  if (!str_match("-e", flag) && !str_match("-d", flag) &&
      !str_match("--encrypt", flag) && !str_match("--decrypt", flag)) {
    printf("Invalid option: %s\n", flag);
    print_help();
    return 0;
  }

  // Options are valid, but command count is not
  if (argc > 4 || argc < 3) {
    printf("Invalid number of arguments: %d\n", argc - 1);
    printf("3 arguemnts required\n"
           ">_ cryptor <option> <key> <file_location>\n");
    print_help();
    return 0;
  }

  // Key length too long
  if ((sizeof &argv[2] / sizeof argv[2][0])) {
    printf("Key length too long, limit 100 chars\n");
    return 0;
  }

  // Establishing base key, adding appendage to key
  char *defaultKey = argc == 4 ? argv[2] : "I like habamax colorscheme";
  strcat(strcat(keybuff, defaultKey), "NuLlIsHcyPHER");
  fp = argc == 4 ? fopen(argv[3], "r") : fopen(argv[2], "r");

  // No file found
  if (fp == NULL) {
    printf("No file found!\n");
    return 1;
  }

  // Cypher logic && stream ouput
  if ('e' == flag[1]) {
    while ((buff = fgetc(fp)) != EOF) {
      buff = buff + key_oscillator(keybuff, osc_index);
      printf("%c", buff);
    }
  } else if ('d' == flag[1]) {
    while ((buff = fgetc(fp)) != EOF) {
      buff = buff - key_oscillator(keybuff, osc_index);
      printf("%c", buff);
    }
  }

  fclose(fp);
  return 0;
}
