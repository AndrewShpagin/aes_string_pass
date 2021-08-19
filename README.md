This is the super minimal and library-independent solution of the task:

- We have string, we are writing c++ code. 
- We need to pass it sequrely to js code using AES.

The AES encryption based on the tiny-AES: https://github.com/kokke/tiny-AES-c

On the c++ side:

```c++
const char* test = "This is the string to be encoded and passed to the JS code.";
cout << aes_base64_encrypt(test, "16_characterskey");
// normally we get "Jo1n0VtY4nAe2QxzbWRp06ouU7AUq8n6vcyIqxVSfuLm75XOw+O7cJIzWHYBQtQBIP9Jcdu5USLCV8ondfkyjQ==" there
```
On the js side:
```js
const base64string = "Jo1n0VtY4nAe2QxzbWRp06ouU7AUq8n6vcyIqxVSfuLm75XOw+O7cJIzWHYBQtQBIP9Jcdu5USLCV8ondfkyjQ==";
const value = CryptoJS.enc.Base64.parse(base64string);
const key = CryptoJS.enc.Utf8.parse("16_characterskey");
console.log(CryptoJS.AES.decrypt({ ciphertext: value }, key, { keySize: 16, mode : CryptoJS.mode.ECB }).toString(CryptoJS.enc.Utf8));
// we get "This is the string to be encoded and passed to the JS code."
```
Sidenote:
base64 may produce + sign that is not good to pass via URL, so need to URL encode the string:

```c++
const char* test = "This is the string to be encoded and passed to the JS code.";
cout << aes_base64_encrypt(test, "16_characterskey");
// normally we get "Jo1n0VtY4nAe2QxzbWRp06ouU7AUq8n6vcyIqxVSfuLm75XOw+O7cJIzWHYBQtQBIP9Jcdu5USLCV8ondfkyjQ==" there
```
On the js side:
```js
const base64string = "Jo1n0VtY4nAe2QxzbWRp06ouU7AUq8n6vcyIqxVSfuLm75XOw%2BO7cJIzWHYBQtQBIP9Jcdu5USLCV8ondfkyjQ%3D%3D";
const value = CryptoJS.enc.Base64.parse(decodeURIComponent(base64string));
const key = CryptoJS.enc.Utf8.parse("16_characterskey");
console.log(CryptoJS.AES.decrypt({ ciphertext: value }, key, { keySize: 16, mode : CryptoJS.mode.ECB }).toString(CryptoJS.enc.Utf8));
// we get "This is the string to be encoded and passed to the JS code."
```
