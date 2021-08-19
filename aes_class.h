#pragma once

#define aes_size 16
class AES_key {
	uint8_t key[aes_size];
public:
	AES_key();
	operator const uint8_t*() const;
	AES_key(const char* k);
};
/** This class is intended to pass the data safely to the web-service. Th correct pattern of usage:
 * On the c++ side:
 *
 * \code
 * AES_key k("16Characters Key");// there should be exactly 16 characters
 * AES_buffer b;
 * b << "The string to encode";
 * b.EncryptAES_ECB(k);
 * std::string b64 = b.toBase64();//we pass that string to server, pay attention that + is incorrect URL sign, the string should be URL encoded
 * //we get ""BeqQb5e6PKt2IFM5WTLnDj/PRNRxN7U24+MT28ZTdZQ="" in b64, pay attention to "+" that should be URL encoded or replaced to be passed correctly in the URL.
 * \code
 *
 * on the Node.js server side
 * 
 * \code
 * const base64string = "BeqQb5e6PKt2IFM5WTLnDj/PRNRxN7U24+MT28ZTdZQ=";//we got it from the c++ side
 * const value =  CryptoJS.enc.Base64.parse(base64string);
 * const key  = CryptoJS.enc.Utf8.parse("16Characters Key");
 * console.log(CryptoJS.AES.decrypt({ ciphertext: value },key, { keySize: 16, mode: CryptoJS.mode.ECB }).toString(CryptoJS.enc.Utf8));
 * // we get "The string to encode" on console
 * \code
 * 
 */

class AES_buffer {
	std::vector<uint8_t> buf;
	int actual;
public:
	AES_buffer();;
	operator uint8_t*();
	size_t length() const;
	void operator <<(uint8_t b);;
	void operator <<(const char* str);
	std::string toHEX();
	std::string toBase64();
	void EncryptAES_ECB(const AES_key& key);
};

/**
 * And the supershort version of encrypted passing :
 * The previous example reduces to:
 * \code
 * std::string b64 = aes_base64_encrypt("The string to encode", "16Characters Key");//we pass that string to server, pay attention that + is incorrect URL sign, the string should be URL encoded
 * //we get ""BeqQb5e6PKt2IFM5WTLnDj/PRNRxN7U24+MT28ZTdZQ="" in b64, pay attention to "+" that should be URL encoded or replaced to be passed correctly in the URL.
 * std::string toServer = encodeURL(b64.c_str()); // ready to be part of URL
 * \code
 */

std::string aes_base64_encrypt(const char* string, const char* key16chars);
std::string encodeURL(const char* str);
