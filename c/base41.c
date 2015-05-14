/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
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


int base41_encode_s(uint8_t const *input, size_t n, char *output, size_t out_n)
{
    if ((input == NULL) || (output == NULL)) {
        return -1;
    }
    if (n%2 != 0) {
        return -1;
    }
    if (out_n < (3*n)/2 + 1) {
        return -1;
    }
    base41_encode(input, n, output);
}


void base41_decode(char const *input, size_t len, uint8_t *output)
{
    char const *s = input;
    uint8_t *p = output;
    int i;
    
    assert(len % 3 == 0);
    
    for (i = 0; i < len; i += 3) {
        int x = (*s - 41) + 41 * (s[1] - 41) + 41*41*(s[2] - 41);
        *p++ = x % 256;
        *p++ = x / 256;
        s += 3;
    }
}


bool base41_is_string_valid(char const *s, size_t n)
{
    char const *send = s + n;
    if (NULL == s) {
        return false;
    }
    if (n % 3 != 0) {
        return false;
    }
    while (s != send) {
        char c = *s++;
        if ((c < 41) || (c > 82)) {
            return false;
        }
    }
    return true;
}


int base41_decode_s(char const *input, size_t len, uint8_t *output, size_t n)
{
    if (!base41_is_string_valid(input, len)) {
        return -1;
    }
    if (NULL == output) {
        return -1;
    }
    if ((len*2)/3 > n) {
        return -1;
    }
    base41_decode(input, len, output);
}


void base41_encode_opt32(uint8_t const *input, size_t n, char *output)
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


void base41_encode_16(uint16_t const *input, size_t n, char *output)
{
    uint16_t const *p = input;
    char *s = output;
    
    for (p = input; p < input + n; ++p) {
        int x = *p;
        *s++ = (x % 41) + 41;
        x /= 41;
        *s++ = (x % 41) + 41;
        *s++ = x/41 + 41;
    }
    *s = '\0';
}


int base41_encode_16_s(uint16_t const *input, size_t n, char *output, size_t out_n)
{
    if ((input == NULL) || (output == NULL)) {
        return -1;
    }
    if (out_n < 3*n + 1) {
        return -1;
    }
    base41_encode_16(input, n, output);
}


void base41_encode_16_opt32(uint16_t const *input, size_t n, char *output)
{
    uint16_t const *p = input;
    char *s = output;
    
    for (p = input; p < input + n; ++p) {
        int x = *p;
        int q = (x * 0x63e7) >> 20;
        *s++ = (x - q*41) + 41;
        x = q;
        q = (x * 0x63e7) >> 20;
        *s++ = (x - q*41) + 41;
        *s++ = ((x * 0x63e7) >> 20) + 41;
    }
    *s = '\0';
}


void base41_decode_16(char const *input, size_t len, uint16_t *output)
{
    char const *s = input;
    uint16_t *p = output;
    int i;
    
    assert(len % 3 == 0);
    
    for (i = 0; i < len; i += 3) {
        *p++ = (*s - 41) + 41 * (s[1] - 41) + 41*41*(s[2] - 41);
        s += 3;
    }
}


int base41_decode_16_s(char const *input, size_t len, uint16_t *output, size_t n)
{
    if (!base41_is_string_valid(input, len)) {
        return -1;
    }
    if (NULL == output) {
        return -1;
    }
    if (len/3 > n) {
        return -1;
    }
    base41_decode_16(input, len, output);
}


void base41_encode_32(uint32_t const *input, size_t n, char *output)
{
    uint32_t const *p;
    char *s = output;
    
    for (p = input; p < input + n; ++p) {
        uint32_t y = *p;
        uint16_t x = y;
        *s++ = (x % 41) + 41;
        x /= 41;
        *s++ = (x % 41) + 41;
        *s++ = x/41 + 41;
        x = y >> 16;
        *s++ = (x % 41) + 41;
        x /= 41;
        *s++ = (x % 41) + 41;
        *s++ = x/41 + 41;
    }
    *s = '\0';
}


int base41_encode_32_s(uint32_t const *input, size_t n, char *output, size_t out_n)
{
    if ((input == NULL) || (output == NULL)) {
        return -1;
    }
    if (out_n < 6*n + 1) {
        return -1;
    }
    base41_encode_32(input, n, output);
}


void base41_encode_32_opt32(uint32_t const *input, size_t n, char *output)
{
    uint32_t const *p;
    char *s = output;
    
    for (p = input; p < input + n; ++p) {
        uint32_t y = *p;
        uint16_t x = y;

        int q = (x * 0x63e7) >> 20;
        *s++ = (x - q*41) + 41;
        x = q;
        q = (x * 0x63e7) >> 20;
        *s++ = (x - q*41) + 41;
        *s++ = ((x * 0x63e7) >> 20) + 41;

        x = y >> 16;

        q = (x * 0x63e7) >> 20;
        *s++ = (x - q*41) + 41;
        x = q;
        q = (x * 0x63e7) >> 20;
        *s++ = (x - q*41) + 41;
        *s++ = ((x * 0x63e7) >> 20) + 41;
    }
    *s = '\0';
}


void base41_decode_32(char const *input, size_t len, uint32_t *output)
{
    char const *s = input;
    uint32_t *p = output;
    int i;
    
    assert(len % 6 == 0);
    
    for (i = 0; i < len; i += 6) {
        uint16_t x = (*s - 41) + 41 * (s[1] - 41) + 41*41*(s[2] - 41);
        uint16_t y = (s[3] - 41) + 41 * (s[4] - 41) + 41*41*(s[5] - 41);
        *p++ = x | (y << 16);
        s += 6;
    }
}


int base41_decode_32_s(char const *input, size_t len, uint32_t *output, size_t n)
{
    if (!base41_is_string_valid(input, len)) {
        return -1;
    }
    if (NULL == output) {
        return -1;
    }
    if (len/6 > n) {
        return -1;
    }
    base41_decode_32(input, len, output);
}
