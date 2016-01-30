package base41

import (
	"bytes"
	"testing"
)


func TestSimple(t *testing.T) {
	data := []byte{26,168,48,178,7,162,52,188,199,36}
	const str = "BABA.DEDA.DECA."

	decoded, err := DecodeString(str)
	if err != nil {
		t.Errorf("unexpected error %q", err.Error())
	}
	if !bytes.Equal(decoded, data) {
		t.Errorf("decoding failed, from %q expected %q but got %q", str, data, decoded)
	}

	encoded := EncodeToString(data)
	if encoded != str {
		t.Errorf("encoding failed, from %q expected %q but got %q", data, str, encoded)
	}
}
