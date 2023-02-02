#include <stdio.h>
#include <string.h>

void print_binary(unsigned char c) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (c >> i) & 1);
  }
  printf(" ");
}

int main() {
  char utf8_emoji[] = "\u1F923";
  printf("%s\n", utf8_emoji);
  int len = strlen(utf8_emoji);
  for (int i = 0; i < len; i++) {
    print_binary(utf8_emoji[i]);
  }
  return 0;
}