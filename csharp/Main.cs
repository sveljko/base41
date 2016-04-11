using System;
using System.Linq;

class Base41Test {
    static void Main(string[] args) 
    {
	byte[] data = {26,168,48,178,7,162,52,188,199,36};
	var s = "BABA.DEDA.DECA."; 
	var decoded = Base41Codec.FromString(s);
	if (!data.SequenceEqual(decoded)) {
	    Console.WriteLine("Bad decoding");
	}
	var encoded = Base41Codec.ToString(data);
	if (s != encoded) {
	    Console.WriteLine("bad encoding");
	}
	Console.WriteLine("Base41 test done.");
    }
}