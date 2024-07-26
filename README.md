# base41

Base41 encoding can be viewed as a simplified form of Ascii85
encoding. It is simple to code and understand, safe to embed in
strings (like JSON or most programming language's literals), uses
minimal resources and is reasonably efficient (has 50% overhead),
making it a good candidate for use in embedded or otherwise
constrained systems / applications.

See [Base41 Encoding Specification](base41.md) for a detailed
treatment of this encoding. Постоји и [Спецификација на српском](base41.sr.md).

This repository has implementations in several languages. All code is
under the liberal MIT license. Reference implementation is in C. Other
language implementations are references for their perspective languages.

## Bring Your Own Alphabet variant

To reduce code size and potential configuration issues (i.e. encoder
using a different alphabet than the decoder) _and_ increase
performance, the Base41 Specification fixes a particular Alphabet.

Of course, that Alphabet is not good for all purposes. So, a variant
of Base41 is to "bring your own Alphabet" (BYOA) of 41 ASCII
characters. In the following sections there are some examples thereof.

### Paper on a similar encoding with the same name

Botta and Cavagnino published a paper in
[2022](https://doi.org/10.1002/eng2.12606) which uses the BYOA
variant, with Alphabet selected so that Base41 encoded string can be
part of an URL. This was the first inspiration for having a BYOA
variant of Base41 spec.

They also define the encoding to not be "byte oriented" but
"bit-oriented".  That is, data need not have `8 x N`
bits. Interesting, but complicates things for a somewhat rare use-case
(well, I guess for them it was not so rare).

They were kind enough to mention this code repo as "apriori art" of sorts.
It's an interesting read, with a different focus and presentation style
than our specification. Here's the full reference to the paper:

> Botta, Marco, and Davide Cavagnino. "Base41: A proposal for printable encoding of bit strings."
> Engineering Reports (2022): e12606.

### BYOA for QR Codes

Philippe Majerus (github user `PhMajerus`) proposes an Alphabet with
characters used in alphanumeric QR Codes _and_ which can be part of an
URL. To be precise:

    0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$*-.:

Thus one can encode an URL with some binary data in an alphanumeric QR
code. Caveats:

* Dollar (`$`) and asterisk (`*`) are URL sub-delimiters, thus
  reserved mostly because of file naming conventions, but should be OK
  for most servers which are aware that URL paths are not the same as
  file system paths.
* Colon (`:`) is a delimiter, _could_ interfere with the server's path
  processing, so some care should be taken.

One of the above can be replaced with `+` if that helps HTTP server's
URL processing.


## Misc

### Invention, patents, whatever

AFAIK, I invented this encoding. If I haven't, great, let the glory
go to the other guy.

But, if I did invent it, I hereby put it to public domain as of
2014-05-06 (the actual date of invention in ISO8601 format). That
should make any patent claims for it invalid.  Don't laugh, I've seen
software patents that are much more silly.

I did not invent any of the BYOA Alphabets mentioned above.


### Age before beauty

No, I was not 41 when I invented it. :)
