#include <main_header.h>

void* my_malloc(int size) {
  return mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);;
}

int main(int ac, char **av) {
  char *src = "hello";
  char *dest = my_malloc(strlen(src) + 1);

  strcpy(dest, src);
  printf("s\n", dest);
  return 0;
}