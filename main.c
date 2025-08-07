#include <stdio.h>
#include <string.h>

int read_key(char *string);
int read_flag(char *flag);
int key_oscillator(char *key_string, int oscindex);
int str_match(char *str1, char *str2);
void print_help(void);

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

int read_key(char *string) {
  if (NULL == string) {
    return 1;
  }
  return 0;
}

int read_flag(char *flag) {
  if (('e' == flag[1] || 'd' == flag[1]) && '-' == flag[0]) {
    return 0;
  };
  printf("Bad option or no option chosen\n");
  print_help();
  return 1;
}

int key_oscillator(char *key, int tracker) {
  if ('0' == key[tracker])
    tracker = 0;
  return (int)key[tracker++];
}

// Returns 0 input strings do not match
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
