#include "stdafx.h"
#include "Common.h"

static _bstr_t sample_xslt1("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
	"<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">"
		"<xsl:param name=\"p1\" select=\"''\" />"
		"<xsl:param name=\"p2\" select=\"111\" />"
		"<xsl:output method=\"xml\" version=\"1.0\" encoding=\"UTF-8\" indent=\"yes\" />"
		"<xsl:template match=\"/\"><Result><xsl:apply-templates /></Result></xsl:template>"
	"<xsl:template xmlns:z=\"urn:fakemsxml:test:ns1\" match=\"//@z:a\"><xsl:if test=\"$p2 != 111\"><xsl:attribute name=\"z\"><xsl:value-of select=\"concat($p1, '-', $p2)\" /></xsl:attribute></xsl:if></xsl:template>"
	"<xsl:template match=\"@*|node()\"><xsl:copy><xsl:apply-templates select=\"@*|node()\" /></xsl:copy></xsl:template>"
	"</xsl:stylesheet>");
static _bstr_t sample_res1("<?xml version=\"1.0\"?>"
	"<Result><root xmlns:na=\"urn:fakemsxml:test:ns1\">"
		"<el>First</el><!-- comment -->"
		"<el at=\"some attr\">Second</el>"
		"<el xmlns=\"urn:fakemsxml:test:ns2\">Third</el>"
	"</root></Result>");
static _bstr_t sample_res_params("<?xml version=\"1.0\"?>"
	"<Result><root xmlns:na=\"urn:fakemsxml:test:ns1\">"
		"<el>First</el><!-- comment -->"
		"<el at=\"some attr\" z=\"v1-666\">Second</el>"
		"<el xmlns=\"urn:fakemsxml:test:ns2\">Third</el>"
	"</root></Result>");

TEST(XSLT, OutputString)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_TRUE(LoadSampleDoc(dom));

	CComPtr<IXMLDOMDocument2> xsl;
	ASSERT_HRESULT_SUCCEEDED(xsl.CoCreateInstance(DOMDocumentCLSID()));
	VARIANT_BOOL succ;
	ASSERT_HRESULT_SUCCEEDED(xsl->loadXML(sample_xslt1, &succ));
	ASSERT_TRUE(!!succ);

	ASSERT_HRESULT_SUCCEEDED(xsl->put_resolveExternals(VARIANT_TRUE));
	ASSERT_HRESULT_SUCCEEDED(xsl->setProperty(_T("AllowDocumentFunction"), _variant_t(true)));

	CComPtr<IXSLTemplate> tpl;
	ASSERT_HRESULT_SUCCEEDED(tpl.CoCreateInstance(XSLTemplateCLSID()));
	ASSERT_HRESULT_SUCCEEDED(tpl->putref_stylesheet(xsl));

	CComPtr<IXSLProcessor> proc;
	ASSERT_HRESULT_SUCCEEDED(tpl->createProcessor(&proc));

	ASSERT_HRESULT_SUCCEEDED(proc->put_input(_variant_t(dom)));
	//proc->addParameter(it->first, it->second)
	//proc->addObject(objdisp, objns)

	ASSERT_HRESULT_SUCCEEDED(proc->transform(&succ));
	ASSERT_TRUE(!!succ);

	_variant_t res;
	ASSERT_HRESULT_SUCCEEDED(proc->get_output(&res));
	ASSERT_EQ(VT_BSTR, res.vt);

	std::wstring tst(sample_res1);
	strip_xml_declaration(tst);
	std::wstring str((BSTR)_bstr_t(res));
	strip_xml_declaration(str);
	ASSERT_STREQ(tst.c_str(), str.c_str());
}

bool PrepareXSLT(IXSLProcessor** pProc)
{
	CComPtr<IXMLDOMDocument2> xsl;
	if(FAILED(xsl.CoCreateInstance(DOMDocumentCLSID())))
		return false;
	VARIANT_BOOL succ;
	if(FAILED(xsl->loadXML(sample_xslt1, &succ)) || !succ)
		return false;

	xsl->put_resolveExternals(VARIANT_TRUE);
	xsl->setProperty(_T("AllowDocumentFunction"), _variant_t(true));

	CComPtr<IXSLTemplate> tpl;
	if(FAILED(tpl.CoCreateInstance(XSLTemplateCLSID())))
		return false;
	if(FAILED(tpl->putref_stylesheet(xsl)))
		return false;

	return SUCCEEDED(tpl->createProcessor(pProc));
}

TEST(XSLT, OutputDOM)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_TRUE(LoadSampleDoc(dom));

	CComPtr<IXSLProcessor> proc;
	ASSERT_TRUE(PrepareXSLT(&proc));

	ASSERT_HRESULT_SUCCEEDED(proc->put_input(_variant_t(dom)));

	CComPtr<IXMLDOMDocument2> resdom;
	resdom.CoCreateInstance(DOMDocumentCLSID());
	proc->put_output(_variant_t(resdom));

	VARIANT_BOOL succ = VARIANT_FALSE;
	ASSERT_HRESULT_SUCCEEDED(proc->transform(&succ));
	ASSERT_TRUE(!!succ);

	_variant_t res;
	ASSERT_HRESULT_SUCCEEDED(proc->get_output(&res));
	ASSERT_EQ(VT_UNKNOWN, res.vt);

	CComQIPtr<IXMLDOMDocument2> outdom(res.punkVal);
	ASSERT_NE(nullptr, outdom);
	ASSERT_EQ(resdom, outdom);

	CComBSTR resstr;
	ASSERT_HRESULT_SUCCEEDED(outdom->get_xml(&resstr));

	std::wstring tst(sample_res1);
	strip_xml_declaration(tst);
	std::wstring str((BSTR)resstr);
	strip_xml_declaration(str);
	ASSERT_STREQ(tst.c_str(), str.c_str());
}

TEST(XSLT, Parameters)
{
	CComPtr<IXMLDOMDocument2> dom;
	ASSERT_TRUE(LoadSampleDoc(dom));

	CComPtr<IXSLProcessor> proc;
	ASSERT_TRUE(PrepareXSLT(&proc));

	ASSERT_HRESULT_SUCCEEDED(proc->put_input(_variant_t(dom)));
	ASSERT_HRESULT_SUCCEEDED(proc->addParameter(_bstr_t("p1"), _variant_t("v1")));
	ASSERT_HRESULT_SUCCEEDED(proc->addParameter(_bstr_t("p2"), _variant_t(666)));
	//proc->addObject(objdisp, objns)

	VARIANT_BOOL succ = VARIANT_FALSE;
	ASSERT_HRESULT_SUCCEEDED(proc->transform(&succ));
	ASSERT_TRUE(!!succ);

	_variant_t res;
	ASSERT_HRESULT_SUCCEEDED(proc->get_output(&res));
	ASSERT_EQ(VT_BSTR, res.vt);

	std::wstring tst(sample_res_params);
	strip_xml_declaration(tst);
	std::wstring str((BSTR)_bstr_t(res));
	strip_xml_declaration(str);
	ASSERT_STREQ(tst.c_str(), str.c_str());
}

