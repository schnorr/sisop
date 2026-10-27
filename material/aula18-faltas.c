#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
int main(int argc, char **argv)
{
  size_t mb = argc > 1 ? atol(argv[1]) : 100;  /* MB a reservar */
  int toca = argc > 2 ? atoi(argv[2]) : 1;     /* 1: escreve em cada página */
  size_t tam = mb * 1024 * 1024;
  long pag = sysconf(_SC_PAGESIZE);
  char *v = mmap(NULL, tam, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (v == MAP_FAILED) return 1;
  madvise(v, tam, MADV_NOHUGEPAGE);  /* força páginas de 4 KB */
  if (toca)
    for (size_t i = 0; i < tam; i += pag)
      v[i] = 1;
  printf("%zu MB, %zu páginas de %ld bytes, tocadas: %s\n",
         mb, tam / pag, pag, toca ? "sim" : "não");
  munmap(v, tam);
  return 0;
}
