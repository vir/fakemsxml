#include "stdafx.h"
#include "Common.h"
#include <codecvt>

const static bool use_real_msxml = false;

_bstr_t sample_doc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
	"<root xmlns:na=\"urn:fakemsxml:test:ns1\">"
		"<el>First</el><!-- comment -->"
		"<el at=\"some attr\" na:a=\"stuff\">Second</el>"
		"<el xmlns=\"urn:fakemsxml:test:ns2\">Third</el>"
	"</root>");

std::wstring utf8_to_wstring(const std::string & str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}

std::string wstring_to_utf8(const std::wstring & str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

void strip_xml_declaration(std::wstring & x)
{
	// remove xml prolog
	size_t pos = x.find(L"?>");
	if(pos != x.npos)
		x.erase(0, pos + 2);
	// remove newlines
	pos = 0;
	while((pos = x.find_first_of(L"\n\r", pos)) != x.npos)
		x.erase(pos, 1);
}

CLSID DOMDocumentCLSID()
{
	return use_real_msxml ? __uuidof(FreeThreadedDOMDocument60) : __uuidof(FakeDOMDocument);
}

CLSID XSLTemplateCLSID()
{
	return use_real_msxml ? __uuidof(XSLTemplate60) : __uuidof(FakeXSLTemplate);
}
