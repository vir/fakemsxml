// TestMSXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Common.h"


TEST(Basic, Creation)
{
	CComPtr<IXMLDOMDocument2> dom;
	HRESULT hr = dom.CoCreateInstance(DOMDocumentCLSID());
	EXPECT_NE(hr, REGDB_E_CLASSNOTREG) << "MSXML library not registered";
	ASSERT_FALSE(FAILED(hr)) << "CoCreateInstance failed";
}

TEST(Manipulation, CreateFromScratch)
{
	CComPtr<IXMLDOMDocument2> dom;
	HRESULT hr = dom.CoCreateInstance(DOMDocumentCLSID());
	EXPECT_NE(hr, REGDB_E_CLASSNOTREG) << "MSXML library not registered";
	ASSERT_FALSE(FAILED(hr)) << "CoCreateInstance failed";

	// Create fake processing instruction - required to get xml prolog with MSXML
	CComPtr<IXMLDOMProcessingInstruction> pi;
	ASSERT_HRESULT_SUCCEEDED(dom->createProcessingInstruction(_bstr_t(L"xml"), _bstr_t(L"version='1.0' encoding='UTF-8'"), &pi));
	CComPtr<IXMLDOMNode> out;
	ASSERT_HRESULT_SUCCEEDED(dom->appendChild(pi, &out));
	
	CComPtr<IXMLDOMElement> el;
	ASSERT_HRESULT_SUCCEEDED(dom->createElement(_bstr_t("root"), &el));
	ASSERT_HRESULT_SUCCEEDED(dom->putref_documentElement(el));
	ASSERT_HRESULT_SUCCEEDED(el->setAttribute(_bstr_t("a1"), _variant_t("val1")));

	CComPtr<IXMLDOMNode> chldnode1, chldnode1_out;
	ASSERT_HRESULT_SUCCEEDED(dom->createNode(_variant_t((long)NODE_ELEMENT), _bstr_t("c1"), _bstr_t("test:ns1"), &chldnode1));
	ASSERT_HRESULT_SUCCEEDED(el->appendChild(chldnode1, &chldnode1_out));

	CComPtr<IXMLDOMNode> chldnode2, chldnode2_out;
	ASSERT_HRESULT_SUCCEEDED(dom->createNode(_variant_t((long)NODE_ELEMENT), _bstr_t("x:c2"), _bstr_t("test:ns2"), &chldnode2));
	ASSERT_HRESULT_SUCCEEDED(el->appendChild(chldnode2, &chldnode2_out));

	CComBSTR chld2name;
	ASSERT_HRESULT_SUCCEEDED(chldnode2_out->get_nodeName(&chld2name));
	//ASSERT_STREQ(L"x:c2", chld2name);

	CComBSTR xml;
	ASSERT_HRESULT_SUCCEEDED(dom->get_xml(&xml));

	std::wstring x(xml);
	strip_xml_declaration(x);
	ASSERT_STREQ(L"<root a1=\"val1\"><c1 xmlns=\"test:ns1\"/><x:c2 xmlns:x=\"test:ns2\"/></root>", x.c_str());
}

TEST(Manipulation, ReplaceRoot)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_TRUE(LoadSampleDoc(dom));

	CComPtr<IXMLDOMNode> Root_Node;
	CComPtr<IXMLDOMElement> el;
	HRESULT hr = dom->get_documentElement(&el);
	CComPtr<IXMLDOMNode> Out_Root_Node;
	if(SUCCEEDED(hr) && el)	{ // Remove old content
		ASSERT_HRESULT_SUCCEEDED(dom->removeChild(el, &Out_Root_Node));
		Out_Root_Node.Release();
	}
	ASSERT_HRESULT_SUCCEEDED(dom->createNode(_variant_t((long)NODE_ELEMENT), L"Package", L"", &Root_Node));
	ASSERT_HRESULT_SUCCEEDED(dom->appendChild(Root_Node, &Out_Root_Node));

	CComBSTR xml;
	ASSERT_HRESULT_SUCCEEDED(dom->get_xml(&xml));
	std::wstring x(xml);
	strip_xml_declaration(x);
	ASSERT_STREQ(L"<Package/>", x.c_str());
}

TEST(Manipulation, ElementSerialization)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_TRUE(LoadSampleDoc(dom));

	// find victim node
	CComPtr<IXMLDOMNode> n;
	ASSERT_HRESULT_SUCCEEDED(dom->selectSingleNode(_bstr_t("/root/el[2]"), &n));
	ASSERT_NE(nullptr, n);

	CComBSTR resstr;
	ASSERT_HRESULT_SUCCEEDED(n->get_xml(&resstr));

	std::wstring str((BSTR)resstr);
	strip_xml_declaration(str);
	bool ok = (str == L"<el xmlns:na=\"urn:fakemsxml:test:ns1\" at=\"some attr\" na:a=\"stuff\">Second</el>")
		||    (str == L"<el at=\"some attr\" xmlns:na=\"urn:fakemsxml:test:ns1\" na:a=\"stuff\">Second</el>");
	ASSERT_TRUE(ok);
}

TEST(Manipulation, DISABLED_ImportNode)
{
	CComPtr<IXMLDOMDocument2> dom1, dom2;

	// load sample document into dom1
	ASSERT_TRUE(LoadSampleDoc(dom1));

	// create minimal document in dom2
	ASSERT_HRESULT_SUCCEEDED(dom2.CoCreateInstance(DOMDocumentCLSID()));
	CComPtr<IXMLDOMElement> el;
	ASSERT_HRESULT_SUCCEEDED(dom2->createElement(_bstr_t("root"), &el));
	ASSERT_HRESULT_SUCCEEDED(dom2->putref_documentElement(el));

	// find victim node
	CComPtr<IXMLDOMNode> n;
	ASSERT_HRESULT_SUCCEEDED(dom1->selectSingleNode(_bstr_t("/root/el[2]"), &n));
	ASSERT_NE(nullptr, n);

	// import node into second dom
	CComPtr<IXMLDOMNode> n_out;
	ASSERT_HRESULT_SUCCEEDED(el->appendChild(n, &n_out));

	CComBSTR resstr;
	ASSERT_HRESULT_SUCCEEDED(dom2->get_xml(&resstr));
	std::wstring str((BSTR)resstr);
	strip_xml_declaration(str);
	ASSERT_STREQ(L"<root><el at=\"some attr\" xmlns:na=\"urn:fakemsxml:test:ns1\" na:a=\"stuff\">Second</el></root>", str.c_str());
}
