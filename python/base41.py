#! /usr/bin/python2.7

"""Base 41 Data encoding"""


def base41_decode(input):
    """Decode a Base41 string.

    input is the string to decode.

    The decoded data is returned. A TypeError is raised if input
    is not valid (odd number of chars, non-alphabet character present,
    invalid word).
    """
    rslt = bytearray()
    i = 0
    while i + 2 < len(input):
        x = (ord(input[i]) - 41) + 41 * (ord(input[i+1]) - 41) + 1681*(ord(input[i+2]) - 41)
        rslt.extend([x % 256, x / 256])
        i += 3
    if i != len(input):
        raise TypeError("Invalid Base41 string")
    return rslt


def base41_encode(input):
    """Encode an array of bytes to a Base41 string.
    
    input is the array of bytes to encode.

    The encoded string is returned.

    If input has an odd number of bytes, a TypeError is raised.
    """
    rslt = ""
    i = 0
    while i + 1 < len(input):
        x = input[i] + 256 * input[i+1]
        rslt += chr((x % 41) + 41)
        x /= 41
        rslt += chr((x % 41) + 41) + chr((x / 41) + 41)
        i += 2
    if i != len(input):
        raise TypeError("Invalid input length for Base41 encoding")
    return rslt


def test():
    """Test the Base41 codec"""
    data = bytearray([26,168,48,178,7,162,52,188,199,36])
    s = "BABA.DEDA.DECA."
    decoded = base41_decode(s)
    if data != decoded:
        raise RuntimeError("bad decoding")
    encoded = base41_encode(data)
    if s != encoded:
        raise RuntimeError("bad decoding")

if __name__ == '__main__':
    test()
