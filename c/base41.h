/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#if !defined INC_BASE41
#define      INC_BASE41

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


/** @file Base41 encoding/decoding library

    This library implements Base41 encoding (and decoding) of
    arbitrary data to (from) printable strings. For details, see
    `base41.md` that describes this encoding.

    There are a lot of functions, but, it comes down to just two:
    encode and decode, and a helper function to check the validity of
    a Base41 encoded string. Others are variants:

    - `_16` and `_32` are variants that accept 16-bit and 32-bit
    pointers, which makes processing a little easier and avoids
    the need to cast (to `uint8_t`) if you do have such data.
    Some future version of the library may implement `_64` variant,
    too.

    - `_s` variants are safe variants - they check their parameters
    for validity and return error if some is found invalid, while
    others trust the caller to have done all the checks already.
    There are `_s` variants for all (data element) sizes.

    - `_opt32` are variants optimized for 32-bit processors, only for
    encoding, as decoding is done from characters and there is no
    general optimization for that. There are `_opt32` variants for
    all (data element) sizes. Some future version of library
    may introduce `_opt16` or `_opt64` variants.

    All decoding functions, even the "unsafe" ones, expect the length
    of the string to decode.  Passing the length makes it possible to
    use a part of a larger string. For example if the larger string is
    a JSON value, this could be just the portion where a JSON string
    (Base41 encoded) is situated in that larger string.  Some future
    version of the library may introduce variants that don't need the
    length, but calculate (by way of strlen()) it for themselves.

    It is possible that some future version introduces `_s_opt`
    variants - optimized but checked, though that is somewhat
    strange. One should not optimize if one is not sure of the
    validity of the operation.
 */

/** Encode the input, given as an array of bytes to the output
    string. Assumes all input parameters are correct, so call
    only if you're sure. Otherwise, call base41_encode_s().

    @precondition @c n is even

    @param input The pointer to the beggining of data to encode
    @param n The length, in bytes, of the data to encode. 
    @param output The pointer to the string where to put the
    result of encoding. Allocated by the caller, to at least
    the `(3*n)/2+1` characters.
 */
void base41_encode(uint8_t const *input, size_t n, char *output);

/** This is the safe variant of base41_encode(). It will check
    all parameters for validity.
    @param out_n Added to base41_encode() parameters, the number
    of characters (including NUL) allocated for @c output
    @return 0: OK (all parameter checks passed), -1 error
    (some parameter invalid)
*/
int base41_encode_s(uint8_t const *input, size_t n, char *output, size_t out_n);

/** Decodes a Base41 encoded string to the output array of bytes.
    Assumes all input parameters are correct, so call
    only if you're sure. Otherwise, call base41_decode_s().

    @precondition @c len is a multiple of 3

    @param input The pointer to the beggining of string to decode
    @param len The length (in characters) of the string to decode
    @param output The pointer to the first byte where to put the
    result of decoding. Allocated by the caller, to at least
    the 2/3 bytes to characters in @c input
 */
void base41_decode(char const *input, size_t len, uint8_t *output);

/** Checks if the given string @c s, with its length @c n
    is a valid Base41 encoded string.

*/
bool base41_is_string_valid(char const *s, size_t n);

/** This is the safe variant of base41_decode(). It will check
    all parameters for validity.
    @param n Added to base41_decode() parameters, the number
    of bytes allocated for @c output
    @return 0: OK (all parameter checks passed), -1: error
    (some parameter invalid)
*/
int base41_decode_s(char const *input, size_t len, uint8_t *output, size_t n);

/** This function is the same as base41_encode(), except that it is
    optimised for execution on a 32-bit processor (well, most of them,
    in theory one could construct a 32-bit processor on which this
    function would actually run slower). It could also be faster on
    some 16-bit processor and is also probably faster on 64-bit
    processors, though an even faster variant for those is possible.
*/
void base41_encode_opt32(uint8_t const *input, size_t n, char *output);

/** This function is similar to base41_encode(), except that it takes
    an array of "words" (double-bytes, 16-bit values), which simplifies
    things, as we don't have to check if the number of bytes is even.
    For a safe(r) variant, see base41_encode_16_s().

    @param input The pointer to the beggining of data to encode
    @param n The length, in members (words), of the data to encode. 
    @param output The pointer to the string where to put the
    result of encoding. Allocated by the caller, to at least
    the `3*n+1` characters.
*/
void base41_encode_16(uint16_t const *input, size_t n, char *output);

/** This is the safe variant of base41_encode_16(). It will check
    all parameters for validity.
    @param out_n Added to base41_encode() parameters, the number
    of characters (including NUL) allocated for @c output
    @return 0: OK (all parameter checks passed), -1 error
    (some parameter invalid)
*/
int base41_encode_16_s(uint16_t const *input, size_t n, char *output, size_t out_n);

/** This function is similar to base41_decode(), except that it takes
    an array of "words" (double-bytes, 16-bit values), which simplifies
    things, if we do want to process the data as "words".
    For a safe(r) variant, see base41_encode_16_s().

    @precondition @c len is a multiple of 3

    @param input The pointer to the beggining of string to decode
    @param len The length (in characters) of the string to decode
    @param output The pointer to the first word where to put the
    result of decoding. Allocated by the caller, to at least
    the 1/3 words to characters in @c input
*/
void base41_decode_16(char const *input, size_t len, uint16_t *output);

/** This is the safe variant of base41_decode_16(). It will check
    all parameters for validity.
    @param n Added to base41_decode() parameters, the number
    of words allocated for @c output
    @return 0: OK (all parameter checks passed), -1: error
    (some parameter invalid)
*/
int base41_decode_16_s(char const *input, size_t len, uint16_t *output, size_t n);

/** This function is the same as base41_encode_16(), except that it is
    optimised for execution on a 32-bit processor. Optimization is the
    same as the one in base_encode_opt32().
*/
void base41_encode_16_opt32(uint16_t const *input, size_t n, char *output);


/** This function is similar to base41_encode(), except that it takes
    an array of "dwords" (double-words, 32-bit values), which
    simplifies things, as we don't have to check if the number of
    bytes is even.  For a safe(r) variant, see base41_encode_32_s().

    @param input The pointer to the beggining of data to encode
    @param n The length, in members (dwords), of the data to encode. 
    @param output The pointer to the string where to put the
    result of encoding. Allocated by the caller, to at least
    the `6*n+1` characters.
*/
void base41_encode_32(uint32_t const *input, size_t n, char *output);

/** This function is similar to base41_decode(), except that it takes
    an array of "dwords" (double-bytes, 32-bit values), which simplifies
    things, if we do want to process the data as "words".
    For a safe(r) variant, see base41_encode_32_s().

    @precondition @c len is a multiple of 6

    @param input The pointer to the beggining of string to decode
    @param len The length (in characters) of the string to decode
    @param output The pointer to the first dword where to put the
    result of decoding. Allocated by the caller, to at least
    the 1/6 words to characters in @c input
*/
void base41_decode_32(char const *input, size_t len, uint32_t *output);

/** This is the safe variant of base41_decode_32(). It will check
    all parameters for validity.
    @param n Added to base41_decode() parameters, the number
    of dwords allocated for @c output
    @return 0: OK (all parameter checks passed), -1: error
    (some parameter invalid)
*/
int base41_decode_32_s(char const *input, size_t len, uint32_t *output, size_t n);

/** This function is the same as base41_encode_32(), except that it is
    optimised for execution on a 32-bit processor. Optimization is the
    same as the one in base_encode_opt32().
*/
void base41_encode_32_opt32(uint32_t const *input, size_t n, char *output);


#endif /* !defined INC_BASE41 */
