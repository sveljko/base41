#include "base41.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>


static void print_array(uint8_t const *dec_data, size_t n)
{
  int i;
  for (i = 0; i < n; ++i) {
    printf("%d,", dec_data[i]);
  }
}

static void torture_test(void)
{
  int i, j, k, l;
  uint8_t data[4];

  for (i = 0; i < 256; ++i) {
    data[0] = i;
    for (j = 0; j < 256; ++j) {
      data[1] = j;
      for (k = 0; k < 256; ++k) {
	data[2] = k;
	// full test takes too long
	for (l = 0; l < 4; ++l) {
	  char s[(sizeof data / 2) * 3 + 1];
	  uint8_t dec[sizeof data];
	  data[3] = l;
	  base41_encode_32(data, sizeof data, s);
	  base41_decode(s, dec);
	  assert(0 == memcmp(data, dec, sizeof data));
	}
      }
    }
  }
  puts("End torture");
}


int main()
{
  uint8_t const data[] = {26,168,48,178,7,162,52,188,199,36};
#define STR "BABA.DEDA.DECA."

  uint8_t dec_data[sizeof data];
  char enc_str[sizeof STR + 1];

  base41_decode(STR, dec_data);
  printf("'%s' = Base41(", STR);
  print_array(dec_data, sizeof dec_data);
  printf(")\n");

  base41_encode(data, sizeof data, enc_str);
  printf("Base41(");
  print_array(data, sizeof data);
  printf(") = '%s'\n", enc_str);

  assert(strcmp(STR, enc_str) == 0);
  assert(memcmp(data, dec_data, sizeof data) == 0);

  base41_encode_32(data, sizeof data, enc_str);
  printf("Base41_optimised32(");
  print_array(data, sizeof data);
  printf(") = '%s'\n", enc_str);

  assert(memcmp(data, dec_data, sizeof data) == 0);

  torture_test();

  return 0;
}
