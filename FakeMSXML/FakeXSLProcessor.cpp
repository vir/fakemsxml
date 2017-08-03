// FakeXSLProcessor.cpp : Implementation of CFakeXSLProcessor

#include "stdafx.h"
#include "FakeXSLProcessor.h"
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include "FakeDOMDocument.h"
#include "FakeXMLNode.h"

void CXsltParams::add(BSTR name, VARIANT val)
{
	while(!vec.empty() && *vec.rbegin() == nullptr)
		vec.pop_back();
	{
		int nmlen = ::WideCharToMultiByte(CP_UTF8, 0, name, -1, NULL, 0, NULL, NULL);
		char* n = new char[nmlen + 1];
		nmlen = ::WideCharToMultiByte(CP_UTF8, 0, name, -1, (LPSTR)n, nmlen, NULL, NULL);
		n[nmlen] = '\0';
		vec.push_back(n);
	}
	_bstr_t vstr { val };
	if(val.vt == VT_BSTR)
		vstr = _bstr_t("\'") + vstr + _bstr_t("\'");
	{
		int vlen = ::WideCharToMultiByte(CP_UTF8, 0, (BSTR)vstr, -1, NULL, 0, NULL, NULL);
		char* v = new char[vlen + 1];
		vlen = ::WideCharToMultiByte(CP_UTF8, 0, (BSTR)vstr, -1, (LPSTR)v, vlen, NULL, NULL);
		v[vlen] = '\0';
		vec.push_back(v);
	}
}

// CFakeXSLProcessor
HRESULT CFakeXSLProcessor::Init(IXMLDOMNode * doc, IUnknown* keepRef)
{
	m_keep_stylesheet_dom_referenced = keepRef;
	xmlDocPtr d = (xmlDocPtr)GetInternalNode(doc);
	if(!d)
		return E_UNEXPECTED;
	m_stylesheet = xsltParseStylesheetDoc(d);
	return m_stylesheet ? S_OK : E_FAIL;
}


HRESULT CFakeXSLProcessor::FinalConstruct()
{
	CObjectCounter::instance().inc();
	return CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p);
}

void CFakeXSLProcessor::FinalRelease()
{
	CObjectCounter::instance().dec();
	m_pUnkMarshaler.Release();
}

inline HRESULT CFakeXSLProcessor::UnimplementedMethod(const char * name)
{
	return ::ReportUnimplementedMethod("XSLProcessor", name);
}

STDMETHODIMP CFakeXSLProcessor::InterfaceSupportsErrorInfo(REFIID riid)
{
	return InlineIsEqualGUID(__uuidof(IXSLProcessor), riid) ? S_OK : S_FALSE;
}


// IXSLProcessor
STDMETHODIMP CFakeXSLProcessor::put_input(/* [in] */ VARIANT var)
{
	m_input = NULL;
	switch(var.vt) {
	case VT_UNKNOWN:
	case VT_DISPATCH:
		m_input = (xmlDocPtr)GetInternalNode(var.punkVal);
		break;
	default:
		break;
	}
	return m_input ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CFakeXSLProcessor::get_input(/* [retval][out] */ VARIANT *pVar)
{
	return UnimplementedMethod("get_input");
}

STDMETHODIMP CFakeXSLProcessor::get_ownerTemplate(/* [retval][out] */ IXSLTemplate **ppTemplate)
{
	return UnimplementedMethod("get_ownerTemplate");
}

STDMETHODIMP CFakeXSLProcessor::setStartMode(/* [in] */ BSTR mode, /* [defaultvalue][in] */ BSTR namespaceURI /* = L"" */)
{
	return UnimplementedMethod("setStartMode");
}

STDMETHODIMP CFakeXSLProcessor::get_startMode(/* [retval][out] */ BSTR *mode)
{
	return UnimplementedMethod("get_startMode");
}

STDMETHODIMP CFakeXSLProcessor::get_startModeURI(/* [retval][out] */ BSTR *namespaceURI)
{
	return UnimplementedMethod("get_startModeURI");
}

STDMETHODIMP CFakeXSLProcessor::put_output(/* [in] */ VARIANT output)
{
	m_output = output;
	return S_OK;
}

STDMETHODIMP CFakeXSLProcessor::get_output(/* [retval][out] */ VARIANT *pOutput)
{
	return CComVariant(m_output).Detach(pOutput);
}

STDMETHODIMP CFakeXSLProcessor::transform(/* [retval][out] */ VARIANT_BOOL *pDone)
{
	xmlDocPtr result = xsltApplyStylesheet(m_stylesheet, m_input, m_params);
	if(pDone)
		*pDone = result ? VARIANT_TRUE : VARIANT_FALSE;
	if(!result)
		return S_FALSE;
	switch(m_output.vt) {
	case VT_EMPTY:	{
		xmlBufferPtr buf = xmlBufferCreate();
		xmlNodeDump(buf, result, (xmlNodePtr)result, 0, 0);
		m_output.vt = VT_BSTR;
		XStr::Put(buf->content, &m_output.bstrVal);
		xmlBufferFree(buf);
		return S_OK;
	}
	case VT_UNKNOWN:
	case VT_DISPATCH: {
		CComQIPtr<IFakeXMLInternalNode> docint(m_output.punkVal);
		if(!docint)
			return E_UNEXPECTED;
		docint->put_InternalNode(result);
		m_output.vt = VT_UNKNOWN; // XXX ??? MSXML always returns IUnknown here
		return S_OK;
	}
	default:
		break;
	}
	return UnimplementedMethod("get_output");
}

STDMETHODIMP CFakeXSLProcessor::reset(void)
{
	return UnimplementedMethod("reset");
}

STDMETHODIMP CFakeXSLProcessor::get_readyState(/* [retval][out] */ long *pReadyState)
{
	return UnimplementedMethod("get_readyState");
}

STDMETHODIMP CFakeXSLProcessor::addParameter(/* [in] */ BSTR baseName, /* [in] */ VARIANT parameter, /* [defaultvalue][in] */ BSTR namespaceURI /* = L"" */)
{
	if(namespaceURI && *namespaceURI)
		return E_INVALIDARG;
	m_params.add(baseName, parameter);
	return S_OK;
}

STDMETHODIMP CFakeXSLProcessor::addObject(/* [in] */ IDispatch *obj, /* [in] */ BSTR namespaceURI)
{
	return UnimplementedMethod("addObject");
}

STDMETHODIMP CFakeXSLProcessor::get_stylesheet(/* [retval][out] */ IXMLDOMNode **stylesheet)
{
	return UnimplementedMethod("get_stylesheet");
}
