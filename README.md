# base41

Base41 encoding can be viewed as a simplified form of Ascii85
encoding. It is simple to code and understand, safe to embed in
strings (like JSON or most programming language's literals), uses
minimal resources and is reasonably efficient (has 50% overhead),
making it a good candidate for use in embedded or otherwise
constrained systems / applications.

See `base41.md` for a detailed treatment of this encoding.

This repository has implementations in several languages. All code is
under the liberal MIT license. Reference implementation is in C. Other
languages may follow.


## Trivia

### Invention, patents, whatever

AFAIK, I invented this encoding. If I haven't, great, let the glory
go to the other guy.

But, if I did invent it, I hereby put it to public domain as of
2014-05-06 (the actual date of invention in ISO8601 format). That
should make any patent claims for it invalid.  Don't laugh, I've seen
software patents that are much more silly.

### I'm not that old

No, I was not 41 when I invented it. :)
