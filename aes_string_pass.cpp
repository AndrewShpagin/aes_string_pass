#include "aes_string_pass.h"
#include <string>
#include <vector>
#include "aes_class.h"

using namespace std;

int main()
{
	// The task: encode the string using c++ and pass it sequrely to the js code
	const char* test = "This is the string to be encoded and passed to the JS code.";
	cout << aes_base64_encrypt(test, "16_characterskey") << "\n";
	// normally we get "Jo1n0VtY4nAe2QxzbWRp06ouU7AUq8n6vcyIqxVSfuLm75XOw+O7cJIzWHYBQtQBIP9Jcdu5USLCV8ondfkyjQ==" there
	cout << encodeURL(aes_base64_encrypt(test, "16_characterskey").c_str()) << "\n";
	// normally we get "Jo1n0VtY4nAe2QxzbWRp06ouU7AUq8n6vcyIqxVSfuLm75XOw%2BO7cJIzWHYBQtQBIP9Jcdu5USLCV8ondfkyjQ%3D%3D" there
	// 
	// pass the string to js and decrypt using the code:
	// 
	// const base64string = "Jo1n0VtY4nAe2QxzbWRp06ouU7AUq8n6vcyIqxVSfuLm75XOw+O7cJIzWHYBQtQBIP9Jcdu5USLCV8ondfkyjQ==";
	// const value = CryptoJS.enc.Base64.parse(base64string);
	// const key = CryptoJS.enc.Utf8.parse("16_characterskey");
	// console.log(CryptoJS.AES.decrypt({ ciphertext: value }, key, { keySize: 16, mode : CryptoJS.mode.ECB }).toString(CryptoJS.enc.Utf8));
	//
	// URL encoded:
	//
	// const base64string = "Jo1n0VtY4nAe2QxzbWRp06ouU7AUq8n6vcyIqxVSfuLm75XOw%2BO7cJIzWHYBQtQBIP9Jcdu5USLCV8ondfkyjQ%3D%3D";
	// const value = CryptoJS.enc.Base64.parse(decodeURIComponent(base64string));
	// const key = CryptoJS.enc.Utf8.parse("16_characterskey");
	// console.log(CryptoJS.AES.decrypt({ ciphertext: value }, key, { keySize: 16, mode : CryptoJS.mode.ECB }).toString(CryptoJS.enc.Utf8));
	
	return 0;
}
