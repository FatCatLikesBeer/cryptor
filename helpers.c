#include "helpers.h"
#include <ranlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_help(void) {
  printf("Example:\n");
  printf(">_ cryptor -e|-d <symetric_key> ./file_to_be_processed.txt # "
         "Output printeds to stdout\n");
  printf(">_ cryptor -e encryptionKey ./to_be_encrypted.txt > "
         "./encrypted_output.txt # Saves output to file\n");
  printf(">_ cryptor -d encryptionKey ./to_be_decrypted.txt > "
         "./decrypted_output.txt # Saves output to file\n");
  printf(">_ cryptor -h # prints this help message\n");
}

int key_oscillator(char *key, int *tracker) {
  int result;
  if ('\0' == key[*tracker])
    *tracker = 0;
  result = (int)key[*tracker];
  (*tracker)++;
  return result;
}

int str_match(char *str1, char *str2) {
  int index = 0;
  while (str1[index] != '\0') {
    if (str1[index] != str2[index]) {
      return 0;
    }
    index++;
  }
  index = 0;
  while (str2[index] != '\0') {
    if (str2[index] != str1[index]) {
      return 0;
    }
    index++;
  }

  return 1;
}

char *salt_generate(void) {
  char *result = malloc(sizeof(char[SALT_LENGTH + 5]));
  int index = 0;
  srand(time(NULL));

  while (index < SALT_LENGTH) {
    result[index++] = MIN + rand() % (MAX - MIN + 1);
  }

  result[SALT_LENGTH] = '\0';
  return result;
}
