#pragma once
#include <string>
#include <msxml6.h>
#include "../FakeMSXML/FakeMSXML_i.h"

std::wstring utf8_to_wstring(const std::string& str);
std::string wstring_to_utf8(const std::wstring& str);
void strip_xml_declaration(std::wstring& x);
CLSID DOMDocumentCLSID();
CLSID XSLTemplateCLSID();

extern _bstr_t sample_doc;

template<class SP> bool LoadSampleDoc(SP& dom)
{
	if(FAILED(dom.CoCreateInstance(DOMDocumentCLSID())))
		return false;
	VARIANT_BOOL succ;
	if(FAILED(dom->loadXML(sample_doc, &succ)))
		return false;
	if(!succ)
		return false;
	return true;
}
