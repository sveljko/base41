#include "base41.h"

#include <string.h>
#include <assert.h>


void base41_encode(uint8_t const *input, size_t n, char *output)
{
  uint8_t const *p = input;
  char *s = output;
  
  assert(n % 2 == 0);
  
  for (p = input; p < input + n; p += 2) {
    int x = *p + 256 * p[1];
    *s++ = (x % 41) + 41;
    x /= 41;
    *s++ = (x % 41) + 41;
    *s++ = x/41 + 41;
  }
  *s = '\0';
}

void base41_decode(char const *input, uint8_t *output)
{
  char const *s = input;
  size_t n = strlen(s);
  uint8_t *p = output;
  int i;
  
  assert(n % 3 == 0);
  
  for (i = 0; i < n; i += 3) {
    int x = (*s - 41) + 41 * (s[1] - 41) + 41*41*(s[2] - 41);
    *p++ = x % 256;
    *p++ = x / 256;
    s += 3;
  }
}


void base41_encode_32(uint8_t const *input, size_t n, char *output)
{
  uint8_t const *p = input;
  char *s = output;
  
  assert(n % 2 == 0);
  
  for (p = input; p < input + n; p += 2) {
    int x = *p + 256 * p[1];
    int q = (x * 0x63e7) >> 20;
    *s++ = (x - q*41) + 41;
    x = q;
    q = (x * 0x63e7) >> 20;
    *s++ = (x - q*41) + 41;
    *s++ = ((x * 0x63e7) >> 20) + 41;
  }
  *s = '\0';
}


