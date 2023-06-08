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
languages may follow.


## Misc

### Invention, patents, whatever

AFAIK, I invented this encoding. If I haven't, great, let the glory
go to the other guy.

But, if I did invent it, I hereby put it to public domain as of
2014-05-06 (the actual date of invention in ISO8601 format). That
should make any patent claims for it invalid.  Don't laugh, I've seen
software patents that are much more silly.

### Paper on a similar encoding with the same name

Botta and Cavagnino published a paper in [2022](https://doi.org/10.1002/eng2.12606) 
about a slightly different encoding with the same name. The differences are:

1. They have a "hand-picked" alphabet, making it possible for the Base41
   encoded string to be part of an URL. Interesting, but, we avoided having
   an "alphabet table" by design, to reduce memory footprint.
2. Their encoding is not "byte oriented" but "bit-oriented". That is, data
   need not have `8 x N` bits. Again, interesting, but complicates things for 
   a somewhat rare use-case (well, I guess for them it was not so rare).

Thus, we can think of that as a variant/dialect of the same encoding, which
one would use if the differences mentioned above favour it in some application.

They were kind enough to mention this code repo as "apriori art" of sorts.
It's an interesting read, with a different focus and presentation style
than our specification. Here's the full reference to the paper:

> Botta, Marco, and Davide Cavagnino. "Base41: A proposal for printable encoding of bit strings." 
> Engineering Reports (2022): e12606.   

### Age before beauty

No, I was not 41 when I invented it. :)
