#include "helpers.h"
#include <stdio.h>
#include <string.h>
#define KEYLIMIT 200

int main(int argc, char *argv[]) {
  FILE *fp;
  char keybuff[256], *flag;
  int osc_index = 0, *p_osc_index = &osc_index, buff;

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
    printf("3-4 arguemnts required\n"
           ">_ cryptor <option> <key> <file_location>\n");
    print_help();
    return 0;
  }

  // Key length too long
  int custom_key_length = strlen(argv[2]);
  if (KEYLIMIT < custom_key_length) {
    printf("Key length of %d too long, limit %d chars\n", custom_key_length,
           KEYLIMIT);
    return 0;
  }

  // Establish defaultKey
  char *salt;
  char *defaultKey = argc == 4 ? argv[2]
                               : "I LiKe tHe hAbAmAx cOlOrScHeMe iN LaZyViM. "
                                 "iT Is aLsO AvAiLaBlE In vAnIlLa nViM!";

  // No file found
  fp = fopen(argc == 4 ? argv[3] : argv[2], "r");
  if (fp == NULL) {
    printf("No file found!\n");
    return 1;
  }

  // Cypher logic && stream ouput
  if ('e' == flag[1]) {
    // Salt key
    salt = salt_generate();
    strcat(strcat(keybuff, salt), defaultKey);

    // Output result
    printf("%s", salt);
    while ((buff = fgetc(fp)) != EOF) {
      buff = buff ^ key_oscillator(keybuff, p_osc_index);
      printf("%c", buff);
    }
  } else if ('d' == flag[1]) {
    // Extract salt
    char salt_buff[SALT_LENGTH + 5];
    int salt_extraction_index = 0;
    while (salt_extraction_index < SALT_LENGTH) {
      salt_buff[salt_extraction_index] = fgetc(fp);
      salt_extraction_index++;
    }
    salt_buff[SALT_LENGTH] = '\0';

    salt = &salt_buff[0];

    strcat(strcat(keybuff, salt), defaultKey);

    while ((buff = fgetc(fp)) != EOF) {
      buff = buff ^ key_oscillator(keybuff, p_osc_index);
      printf("%c", buff);
    }
  }

  fclose(fp);
  return 0;
}
