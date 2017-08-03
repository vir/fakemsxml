#pragma once

class XStr
{
public:
	explicit XStr(BSTR bs)
	{
		const int bslen = ::SysStringLen(bs);
		len = ::WideCharToMultiByte(CP_UTF8, 0, bs, bslen, NULL, 0, NULL, NULL);
		s = new xmlChar[len + 1];
		len = ::WideCharToMultiByte(CP_UTF8, 0, bs, bslen, (LPSTR)s, len, NULL, NULL);
		s[len] = '\0';
	}
	~XStr()
	{
		delete[] s;
	}
	operator xmlChar*()
	{
		return s;
	}
	int length() const { return len;  }
	inline static HRESULT Put(const xmlChar* s, BSTR* pBstr) { return Put((const char*)s, pBstr); }
	static HRESULT Put(const char* s, BSTR* pBstr)
	{
		if(!pBstr)
			return E_POINTER;
		int lwc = ::MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
		*pBstr = ::SysAllocStringLen(NULL, lwc);
		::MultiByteToWideChar(CP_UTF8, 0, (const char*)s, -1, *pBstr, lwc);
		return S_OK;
	}
private:
	int len;
	xmlChar* s;
};


