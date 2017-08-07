#include "stdafx.h"
#include "Common.h"

TEST(XPath, selectSingleNode)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_TRUE(LoadSampleDoc(dom));

	ASSERT_HRESULT_SUCCEEDED(dom->setProperty(_bstr_t("SelectionLanguage"), _variant_t("XPath")));
	_bstr_t ns("xmlns:ns1='urn:fakemsxml:test:ns1' xmlns:ns2='urn:fakemsxml:test:ns2'");
	ASSERT_HRESULT_SUCCEEDED(dom->setProperty(_bstr_t("SelectionNamespaces"), _variant_t(ns)));

	CComPtr<IXMLDOMNode> node;
	ASSERT_HRESULT_SUCCEEDED(dom->selectSingleNode(_bstr_t("/root/el[2]"), &node));
	CComBSTR val;
	ASSERT_HRESULT_SUCCEEDED(node->get_text(&val));
	ASSERT_STREQ(L"Second", val);

#if 0 // This part fails due to a bug in libxml < 2.9.2
	node.Release();
	ASSERT_HRESULT_SUCCEEDED(dom->selectSingleNode(_bstr_t("//@ns1:*"), &node));
	ASSERT_NE(nullptr, (IXMLDOMNode*)node);
	ASSERT_HRESULT_SUCCEEDED(node->get_text(&val));
	ASSERT_STREQ(L"stuff", val);
	CComQIPtr<IXMLDOMAttribute> attr(node);
	ASSERT_NE(nullptr, attr);
	ASSERT_HRESULT_SUCCEEDED(attr->get_name(&val));
	ASSERT_STREQ(L"a", val);
	CComVariant v;
	ASSERT_HRESULT_SUCCEEDED(attr->get_value(&v));
	ASSERT_STREQ(L"stuff", (BSTR)_bstr_t(v));
#endif

	node.Release();
	ASSERT_HRESULT_SUCCEEDED(dom->selectSingleNode(_bstr_t("//ns2:el"), &node));
	ASSERT_HRESULT_SUCCEEDED(node->get_text(&val));
	ASSERT_STREQ(L"Third", val);
}

TEST(XPath, selectNodes)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_TRUE(LoadSampleDoc(dom));

	ASSERT_HRESULT_SUCCEEDED(dom->setProperty(_bstr_t("SelectionLanguage"), _variant_t("XPath")));
	_bstr_t ns("xmlns:ns1='urn:fakemsxml:test:ns1' xmlns:ns2='urn:fakemsxml:test:ns2'");
	ASSERT_HRESULT_SUCCEEDED(dom->setProperty(_bstr_t("SelectionNamespaces"), _variant_t(ns)));

	CComPtr<IXMLDOMNodeList> nodes;
	ASSERT_HRESULT_SUCCEEDED(dom->selectNodes(_bstr_t("/root/el"), &nodes));
	ASSERT_NE(nullptr, nodes);

	long num = 0;
	ASSERT_HRESULT_SUCCEEDED(nodes->get_length(&num));
	EXPECT_EQ(2, num);

	CComPtr<IXMLDOMNode> node;
	ASSERT_HRESULT_SUCCEEDED(nodes->get_item(1, &node));

	CComBSTR val;
	ASSERT_HRESULT_SUCCEEDED(node->get_text(&val));
	ASSERT_STREQ(L"Second", val);

#if 0 // This part fails due to a bug in libxml < 2.9.2
	node.Release();
	ASSERT_HRESULT_SUCCEEDED(dom->selectSingleNode(_bstr_t("//@ns1:*"), &node));
	ASSERT_NE(nullptr, (IXMLDOMNode*)node);
	ASSERT_HRESULT_SUCCEEDED(node->get_text(&val));
	ASSERT_STREQ(L"stuff", val);
	CComQIPtr<IXMLDOMAttribute> attr(node);
	ASSERT_NE(nullptr, attr);
	ASSERT_HRESULT_SUCCEEDED(attr->get_name(&val));
	ASSERT_STREQ(L"a", val);
	CComVariant v;
	ASSERT_HRESULT_SUCCEEDED(attr->get_value(&v));
	ASSERT_STREQ(L"stuff", (BSTR)_bstr_t(v));
#endif

	node.Release();
	ASSERT_HRESULT_SUCCEEDED(dom->selectSingleNode(_bstr_t("//ns2:el"), &node));
	ASSERT_HRESULT_SUCCEEDED(node->get_text(&val));
	ASSERT_STREQ(L"Third", val);
}

