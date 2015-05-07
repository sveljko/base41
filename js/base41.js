function base41_decode(input) {
    	var rslt = []
	var n = input.length
    	for (var i = 0; i < n; i += 3) {
		var x = (input.charCodeAt(i) - 41) + 41 * (input.charCodeAt(i+1) - 41) + 1681*(input.charCodeAt(i+2) - 41);
		rslt.push(x % 256, Math.floor(x / 256))
	}
	return rslt
}
function base41_encode(input) {
	var rslt = ""
	var n = input.length
    	for (var i = 0; i < n; i += 2) {
		var x = input[i] + 256 * input[i+1];
		rslt = rslt.concat(String.fromCharCode((x % 41) + 41))
		x /= 41;
		rslt = rslt.concat(String.fromCharCode((x % 41) + 41), String.fromCharCode((x / 41) + 41))
	}
	return rslt
}

