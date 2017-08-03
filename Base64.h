#pragma once
#include <string>
using namespace std;

class CBase64
{
public:
	CBase64();
	~CBase64();

public:
	bool Encode(const unsigned char *pIn, unsigned long uInLen, unsigned char *pOut, unsigned long *uOutLen);
	bool Encode(const unsigned char *pIn, unsigned long uInLen, string& strOut);
	bool Decode(const string& strIn, unsigned char *pOut, unsigned long *uOutLen);

};