// look about the minimal AES at https://github.com/kokke/tiny-AES-c
#include "aes.h"
#include <vector>
#include <string>
#include "aes_class.h"

using namespace std;
static const char _hex_chars[] = "0123456789ABCDEF";

void AES_buffer::EncryptAES_ECB(const AES_key& key) {
	if(buf.size() % 16 == 0) {
		/// need to add zero othervice the JS side will not be able to convert to utf-8 because the string is not zero-terminated
		(*this) << uint8_t(0);
	}
	AES_ctx ctx;
	AES_init_ctx(&ctx, key);
	for (int i = 0; i < length(); i += aes_size)AES_ECB_encrypt(&ctx, (*this) + i);
}

string aes_base64_encrypt(const char* string, const char* key16chars) {
	AES_key k(key16chars);
	AES_buffer b;
	b << string;
	b.EncryptAES_ECB(k);	
	return b.toBase64();
}

string encodeURL(const char* str) {
	string s;
	size_t L = strlen(str);
	for(int i=0;i<L;i++) {
		uint8_t b = (uint8_t)str[i];
		if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z') || (b >= '0' && b <= '9') || b == '-' || b == '_' || b == '.' || b == '~') {
			s += (char)b;
		}else {
			s += "%";
			s += _hex_chars[b >> 4];
			s += _hex_chars[b & 15];
		}
	}
	return s;
}

AES_key::AES_key() {
	memset(key, 0, sizeof(key));
}

AES_key::operator const unsigned char*() const {
	return key;
}

AES_key::AES_key(const char* k) {
	size_t L = strlen(k);
	if (L > 0) {
		for (int i = 0; i < aes_size; i++) {
			key[i] = k[i % L];
		}
	}
}

AES_buffer::AES_buffer() {
	actual = 0;
}

AES_buffer::operator unsigned char*() {
	return buf.data();
}

size_t AES_buffer::length() const {
	return buf.size();
}

void AES_buffer::operator<<(uint8_t b) {
	if (actual >= buf.size()) {
		buf.insert(buf.end(), 16, 0);
	}
	buf[actual++] = b;
}

void AES_buffer::operator<<(const char* str) {
	size_t L = strlen(str);
	for (size_t i = 0; i < L; i++) {
		(*this) << (uint8_t)str[i];
	}
}

string AES_buffer::toHEX() {
	string s;
	for (int i = 0; i < buf.size(); i++) {
		uint8_t u = buf[i];
		s += _hex_chars[u >> 4];
		s += _hex_chars[u & 15];
	}
	return s;
}
static char base64cs[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };

void ToBase64(uint8_t* buf, size_t Len, string& dest) {
	size_t sz = Len;
	size_t sz0 = sz;
	int pp = 0;
	sz = ((sz + 2) / 3) * 3;
	int p = 1;
	int pos = 0;
	for (int i = 0; i < sz; i += 3) {
		int nn = 0;
		if (pp++ < sz0)nn++;
		int b1 = pos < Len ? buf[pos++] : 0;
		if (pp++ < sz0)nn++;
		int b2 = pos < Len ? buf[pos++] : 0;
		if (pp++ < sz0)nn++;
		int b3 = pos < Len ? buf[pos++] : 0;
		if (nn == 1)b2 = b3 = 0;
		if (nn == 2)b3 = 0;
		if (nn < 3) {
			nn++;
			nn--;
		}
		unsigned int  DD = (b1 << 16) + (b2 << 8) + b3;
		int n3 = (nn * 4 + 2) / 3;
		for (int j = 0; j < n3; j++) {
			int p = (DD >> ((3 - j) * 6)) & 63;
			dest += base64cs[p];
		}
		nn = 3 - nn;
		for (int k = 0; k < nn; k++)dest += '=';
		p++;
	}
}

string AES_buffer::toBase64() {
	string res;
	ToBase64(buf.data(), buf.size(), res);
	return res;
}
