#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *binvals[16] = {
  "0000",
  "0001",
  "0010",
  "0011",
  "0100",
  "0101",
  "0110",
  "0111",
  "1000",
  "1001",
  "1010",
  "1011",
  "1100",
  "1101",
  "1110",
  "1111"
};

const char *hexvals = "0123456789ABCDEF";

void hex2bin (const char *str) {
  const size_t len = strlen(str);

  if (len % 2 != 0) {
    printf("not aligned\n");
    exit(EXIT_FAILURE);
  }

  const size_t buflen = len * 4 + 1;
  char buff[buflen];
  memset(buff, 0, buflen);
  size_t i = 0;
  for (; i < len; i++) {
    
    char c = str[i];
    char *hexv = strchr(hexvals, c);

    if (hexv == NULL) {
      printf("bad hex char: %c\n", c);
      exit(EXIT_FAILURE);
    }

    strcat(buff, binvals[hexv - hexvals]);
  }

  printf("%s\n", buff);
}

void bin2hex (const char *str) {
  const size_t len = strlen(str);

  if (len % 4 != 0) {
    printf("not aligned\n");
    exit(EXIT_FAILURE);
  }

  const size_t buflen = len / 4 + 1;
  char buff[buflen];
  memset(buff, 0, buflen);
  size_t i = 0;
  for (; i < buflen - 1; i++) {
    char tmp[5];
    tmp[4] = 0;
    memcpy(tmp, str + (i * 4), 4);

    size_t j = 0;
    for (; j < 16; j++) {
      if (strcmp(tmp, binvals[j]) == 0) {
        buff[i] = hexvals[j];
        break;
      }
    }

    if (j >= 16) {
      printf("bad bin nibble: %s\n", tmp);
      exit(EXIT_FAILURE);
    }
  }

  printf("%s\n", buff);
}

int main (int argc, char **argv) {

  if (argc < 3) {
    printf("missing args\n");
    printf("usage: %s <-b2h|-h2b> <value_to_convert>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *opt = argv[1];
  const char *str = argv[2];

  if (strcmp(opt, "-h2b") == 0) {
    hex2bin(str);
  } else if (strcmp(opt, "-b2h") == 0) {
    bin2hex(str);
  } else {
    printf("bad opt: %s\n", opt);
    printf("usage: %s <-b2h|-h2b> <value_to_convert>\n", argv[0]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

