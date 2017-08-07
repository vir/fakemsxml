#include "stdafx.h"
#include "Common.h"
#include <fstream>

const char* tmpfn = "c:\\tmp\\testdoc555.xml";

TEST(IO, ParseString)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_HRESULT_SUCCEEDED(dom.CoCreateInstance(DOMDocumentCLSID()));
	VARIANT_BOOL succ;
	ASSERT_HRESULT_SUCCEEDED(dom->loadXML(sample_doc, &succ));
	ASSERT_NE(VARIANT_FALSE, succ);
}

TEST(IO, ParseFile)
{
	std::ofstream out(tmpfn);
	out << wstring_to_utf8((BSTR)sample_doc);
	out.close();

	CComPtr<IXMLDOMDocument2> dom;
	dom.CoCreateInstance(DOMDocumentCLSID());
	VARIANT_BOOL succ;
	ASSERT_HRESULT_SUCCEEDED(dom->load(_variant_t(tmpfn), &succ));
	_unlink(tmpfn);
	ASSERT_NE(VARIANT_FALSE, succ);
}

TEST(IO, WriteString)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_TRUE(LoadSampleDoc(dom));
	CComBSTR xml;
	ASSERT_HRESULT_SUCCEEDED(dom->get_xml(&xml));
	std::wstring tpl(sample_doc);
	strip_xml_declaration(tpl);
	std::wstring ws(xml);
	strip_xml_declaration(ws);
	ASSERT_STREQ(tpl.c_str(), ws.c_str());
}

TEST(IO, WriteFile)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_TRUE(LoadSampleDoc(dom));
	ASSERT_HRESULT_SUCCEEDED(dom->save(_variant_t(tmpfn)));

	// slurp file
	std::ifstream in(tmpfn);
	std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	std::wstring tpl(sample_doc);
	strip_xml_declaration(tpl);
	std::wstring ws = utf8_to_wstring(contents);
	strip_xml_declaration(ws);
	ASSERT_STREQ(tpl.c_str(), ws.c_str());
	_unlink(tmpfn);
}

TEST(IO, ParseByteString)
{
	std::string str(wstring_to_utf8((BSTR)sample_doc));
	// Create variant containing array of utf-8 encoded document
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = strlen(str.c_str());
	SAFEARRAY* psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
	memcpy(psa->pvData, str.c_str(), rgsabound[0].cElements);
	CComVariant v;
	V_VT(&v) = VT_ARRAY | VT_UI1;
	V_ARRAY(&v) = psa;

	CComPtr<IXMLDOMDocument2> dom;
	dom.CoCreateInstance(DOMDocumentCLSID());
	VARIANT_BOOL succ;
	ASSERT_HRESULT_SUCCEEDED(dom->load(v, &succ));
	ASSERT_NE(VARIANT_FALSE, succ);
}

TEST(IO, DISABLED_LoadFileUrl)
{
	//	LPCWSTR fn = L"file://C:/Projects/PiAll/trunk/Client/Data/CfgSea/UI15/ErrorList.xslt";
	LPCWSTR fn = L"C:/Projects/PiAll/trunk/Client/Data/CfgSea/UI15/ErrorList.xslt";
	CComPtr<IXMLDOMDocument2> dom;
	dom.CoCreateInstance(DOMDocumentCLSID());
	VARIANT_BOOL succ;
	ASSERT_HRESULT_SUCCEEDED(dom->load(_variant_t(fn), &succ));
	ASSERT_NE(VARIANT_FALSE, succ);
}
