// Package base41 implements the Base41 encoding
package base41

import (
	"io"
	"strconv"
)


/*
 * Encoder
 */


// Encode encodes src, writing EncodedLen(len(src)) bytes to dst.
// If src has and odd number of bytes, will pad assuming that the
// last byte in src is followed by 0.
// It assumes that dst is large enough to accept the encoded bytes.
func Encode(dst, src []byte) {
	for len(src) > 1 {
		x := int(src[0]) + 256*int(src[1])
		dst[0] = byte((x % 41) + 41)
		x /= 41
		dst[1] = byte((x % 41) + 41)
		dst[2] = byte(x / 41 + 41)
		
		src = src[2:]
		dst = dst[3:]
	}
	if len(src) == 1 {
		x := src[0]
		dst[0] = (x % 41) + 41
		x /= 41
		dst[1] = (x % 41) + 41
		dst[2] = x / 41 + 41
	}
}


// EncodeToString returns the base41 encoding of src
func EncodeToString(src []byte) string {
	buf := make([]byte, EncodedLen(len(src)))
	Encode(buf, src)
	return string(buf)
}


// EncodedLen returns the length in bytes of the base41 encoding
// of an input buffer of length n.
func EncodedLen(n int) int {
	return 3 * ((n+1) / 2)
}

type encoder struct {
	err error
	w io.Writer
	buf [3]byte
	nbuf int
	out [1024]byte
}

func (e *encoder) Write(p []byte) (n int, err error) {
	if e.err != nil {
		return 0, e.err
	}

	if e.nbuf > 0 {
		var i int
		for i = 0; i < len(p) && e.nbuf < 2; i++ {
			e.buf[e.nbuf] = p[i]
			e.nbuf++
		}
		n += i
		p = p[i:]
		if e.nbuf < 3 {
			return
		}
		Encode(e.out[0:], e.buf[0:])
		if _, e.err = e.w.Write(e.out[0:3]); e.err != nil {
			return n, e.err
		}
		e.nbuf = 0
	}

	for len(p) >= 2 {
		inChunk := len(e.out) / 3 * 2
		if inChunk > len(p) {
			inChunk = len(p)
			inChunk -= inChunk % 2
		}
		Encode(e.out[0:], p[0:inChunk])
		if _, e.err = e.w.Write(e.out[0 : inChunk/2*3]); e.err != nil {
			return n, e.err
		}
		n += inChunk
		p = p[inChunk:]
	}

	for i := 0; i < len(p); i++ {
		e.buf[i] = p[i]
	}
	e.nbuf = len(p)
	n += len(p)

	return
}


// Close flushes any pending output from encoder.
// It is an error to call Write after calling Close.
func (e *encoder) Close() error {
	if e.err == nil && e.nbuf > 0 {
		Encode(e.out[0:], e.buf[0:e.nbuf])
		e.nbuf = 0
		_, e.err = e.w.Write(e.out[0:3])
	}
	return e.err
}



// NewEncoder returns a new base41 stream encoder.  Data written to
// the returned writer will be encoded  and then written to w.
// Base41 encodings operate in 2-byte blocks; when finished
// writing, the caller must Close the returned encoder to flush any
// partially written blocks.
func NewEncoder(w io.Writer) io.WriteCloser {
	return &encoder{w: w}
}


/*
 * Decoder
 */


type CorruptInputError int64

func (e CorruptInputError) Error() string {
	return "illegal base41 data at input byte " + strconv.FormatInt(int64(e), 10)
}


// Decode decodes src to dst using base41 encoding. Returns the number
// of bytes writtten and indicates if an error was found
func Decode(dst, src []byte) (n int, err error) {
	for len(src) > 2 {
		x := (int(src[0]) - 41) + 41 * (int(src[1]) - 41) + 41*41*(int(src[2]) - 41)
		if x >= 256*256 {
			return n, CorruptInputError(len(src))
		}
		dst[0], dst[1] = byte(x % 256), byte(x / 256)
		src = src[3:]
		dst = dst[2:]
		n += 2
	}
	return n, nil
}


// DecodeString returns the bytes represented by the base41 string s.
func DecodeString(s string) ([]byte, error) {
	dbuf := make([]byte, DecodedLen(len(s)))
	_, err := Decode(dbuf, []byte(s))
	return dbuf, err
}

	
type decoder struct {
	err    error
	r      io.Reader
	end    bool       // saw end of message
	buf    [1024]byte // leftover input
	nbuf   int
	out    []byte // leftover decoded output
	outbuf [1024 / 3 * 2]byte
}


func (d *decoder) Read(p []byte) (n int, err error) {
	if d.err != nil {
		return 0, d.err
	}
	
	// Use leftover decoded output from last read.
	if len(d.out) > 0 {
		n = copy(p, d.out)
		d.out = d.out[n:]
		return n, nil
	}
	
	// Read a chunk.
	nn := len(p) / 2 * 3
	if nn < 3 {
		nn = 3
	}
	if nn > len(d.buf) {
		nn = len(d.buf)
	}
	nn, d.err = io.ReadAtLeast(d.r, d.buf[d.nbuf:nn], 3-d.nbuf)
	d.nbuf += nn
	if d.nbuf < 3 {
		return 0, d.err
	}
	
	// Decode chunk into p, or d.out and then p if p is too small.
	nr := d.nbuf / 3 * 3
	nw := d.nbuf / 3 * 2
	if nw > len(p) {
		nw, d.err = Decode(d.outbuf[0:], d.buf[0:nr])
		d.out = d.outbuf[0:nw]
		n = copy(p, d.out)
		d.out = d.out[n:]
	} else {
		n, d.err = Decode(p, d.buf[0:nr])
	}
	d.nbuf -= nr
	for i := 0; i < d.nbuf; i++ {
		d.buf[i] = d.buf[i+nr]
	}
	
	if d.err == nil {
		d.err = err
	}
	return n, d.err
}

// NewDecoder constructs a new base41 stream decoder.
func NewDecoder(r io.Reader) io.Reader {
	return &decoder{r: r}
}


// DecodedLen returns the maximum length in bytes of the decoded data
// corresponding to n bytes of base41-encoded data.
func DecodedLen(n int) int { return n / 3 * 2 }
