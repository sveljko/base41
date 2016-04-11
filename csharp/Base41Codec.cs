using System;

/// <summary>
///   Base41 codec.
/// </summary>
/// <remarks>
///   <para>
///     Provides two static functions - one to encode and one to
///     decode a Base41 string.
///   </para>
/// </remarks>
class Base41Codec {
    /// <summary>
    ///  Decode from a Base41 string to an array of bytes
    /// </summary>
    /// <remarks>
    ///   <para>
    ///     Will throw exception on (some) illegal inputs.
    ///   </para>
    /// </remarks>
    /// <example>
    ///    byte[] decoded = Base41Codec.FromBase41String("BABA.DEDA.DECA.");
    /// </example>
    /// <param name="s">Base41 string to decode</param>
    /// <returns>encoded array</returns>
    public static byte[] FromString(string s) {
	if (s.Length % 3 != 0) {
	    throw new ArgumentException("Invalid Base41 string length");
	}
	var result = new byte[(s.Length / 3) * 2];
	int j = 0;
	for (int i = 0; i < s.Length; i += 3) {
	    ushort x = (ushort)(Convert.ToByte(s[i]) - 41 + 41 * (Convert.ToByte(s[i+1]) - 41) + 1681 * (Convert.ToByte(s[i+2]) - 41));
	    result[j++] = (byte)(x % 256);
	    result[j++] = (byte)(x / 256);
	}
	return result;
    }

    /// <summary>
    ///   Encode from an array of bytes to a string
    /// </summary>
    /// <remarks>
    ///   <para>
    ///     Will throw exception on (some) illegal inputs.
    ///   </para>
    /// </remarks>
    /// <example>
    ///    string encoded = Base41Codec.FromBase41String(new byte[]{26,168,48,178,7,162,52,188,199,36});
    /// </example>
    /// <param name="b">Bytes to encode</param>
    /// <returns>encoded array</returns>
    public static string ToString(byte[] b) {
	if (b.Length % 2 != 0) {
	    throw new ArgumentException("Invalid Base41 byte array length");
	}
	string s="";
	for (int i = 0; i < b.Length; i += 2) {
	    ushort x = (ushort)(b[i] + 256 * b[i+1]);
	    s += Convert.ToChar((x%41) + 41);
	    x /= 41;
	    s += Convert.ToChar((x%41) + 41);
	    s += Convert.ToChar((x/41) + 41);
	}
	return s;
    }
}