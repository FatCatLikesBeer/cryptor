#include <stdio.h>

int read_key(char *string);
int read_flag(char *flag);
int key_oscillator(char *key, int oscillator_tracker);

int main(int argc, char *argv[]) {
  FILE *fp;
  char buffer[256], *flag, *key;
  int osc_index = 0, buff;

  fp = fopen(argv[3], "r");
  key = argv[2];
  flag = argv[1];

  if (read_key(key)) {
    printf("Invalid key\n");
    return 1;
  }
  if (read_flag(flag))
    return 1;

  if (fp == NULL) {
    printf("No file found!\n");
    return 1;
  }

  if ('e' == flag[1]) {
    while ((buff = fgetc(fp)) != EOF) {
      buff = buff + key_oscillator(key, osc_index);
      printf("%c", buff);
    }
  } else if ('d' == flag[1]) {
    while ((buff = fgetc(fp)) != EOF) {
      buff = buff - key_oscillator(key, osc_index);
      printf("%c", buff);
    }
  }

  fclose(fp);
  return 0;
}

int read_key(char *string) {
  if (NULL == string) {
    return 1;
  }
  return 0;
}

int read_flag(char *flag) {
  if ('e' == flag[1] || 'd' == flag[1]) {
    return 0;
  };
  printf("Bad option or no option chosen\n");
  return 1;
}

int key_oscillator(char *key, int tracker) {
  if ('0' == key[tracker])
    tracker = 0;
  return (int)key[tracker++];
}
