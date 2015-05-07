#if !defined INC_BASE41
#define      INC_BASE41

#include <stdint.h>
#include <stdlib.h>


void base41_encode(uint8_t const *input, size_t n, char *output);

void base41_decode(char const *input, uint8_t *output);

void base41_encode_32(uint8_t const *input, size_t n, char *output);


#endif /* !defined INC_BASE41 */
