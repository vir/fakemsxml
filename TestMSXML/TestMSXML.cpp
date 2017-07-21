// TestMSXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gtest/gtest.h>

#include <msxml6.h>
//#include <atlstr.h>
#include <COMDEF.H>

static _bstr_t sample_doc("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root><el>First</el><!-- comment --><el at=\"some attr\">Second</el></root>");

static CLSID DOMDocumentCLSID()
{
	return __uuidof(FreeThreadedDOMDocument60);
}

void CreateDOM(IXMLDOMDocument2** ppInt)
{
}

TEST(Basic, Creation)
{
	CComPtr<IXMLDOMDocument2> dom;
	HRESULT hr = dom.CoCreateInstance(DOMDocumentCLSID());
	EXPECT_NE(hr, REGDB_E_CLASSNOTREG) << "MSXML library not registered";
	ASSERT_FALSE(FAILED(hr)) << "CoCreateInstance failed";
}

TEST(Parse, ParseString)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_HRESULT_SUCCEEDED(dom.CoCreateInstance(DOMDocumentCLSID()));
	VARIANT_BOOL succ;
	ASSERT_HRESULT_SUCCEEDED(dom->loadXML(sample_doc, &succ));
	ASSERT_TRUE((bool)succ);

}

TEST(XPath, selectSingleNode)
{
	CComPtr<IXMLDOMDocument2> dom;
	dom.CoCreateInstance(DOMDocumentCLSID());
	VARIANT_BOOL succ;
	dom->loadXML(sample_doc, &succ);
	if(! succ)
		FAIL() << "Can't parse same document again";
	CComPtr<IXMLDOMNode> node;
	ASSERT_HRESULT_SUCCEEDED(dom->selectSingleNode(_bstr_t("/root/el[2]"), &node));
	CComBSTR val;
	ASSERT_HRESULT_SUCCEEDED(node->get_text(&val));
	ASSERT_STREQ(L"Second", val);
}

TEST(Creation, FromScratch)
{
	CComPtr<IXMLDOMDocument2> dom;
	HRESULT hr = dom.CoCreateInstance(DOMDocumentCLSID());
	EXPECT_NE(hr, REGDB_E_CLASSNOTREG) << "MSXML library not registered";
	ASSERT_FALSE(FAILED(hr)) << "CoCreateInstance failed";

	CComPtr<IXMLDOMProcessingInstruction> pi;
	ASSERT_FALSE(FAILED(dom->createProcessingInstruction(L"xml", L"version='1.0' encoding='UTF-8'", &pi)));
	CComPtr<IXMLDOMNode> out;
	ASSERT_FALSE(FAILED(dom->appendChild(pi, &out)));
}

class Environment : public ::testing::Environment
{
protected:
	// запускается перед выполнением ВСЕХ тестов
	virtual void SetUp()
	{
		if(0)
		{
			FAIL() << "Can't Load";
		}
	}
};

int main(int argc, _TCHAR* argv[])
{
	::CoInitialize(NULL);
	::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(new Environment());
	int rc = RUN_ALL_TESTS();
	::CoUninitialize();
	return rc;
}

