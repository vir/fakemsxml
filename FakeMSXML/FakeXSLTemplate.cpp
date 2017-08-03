// FakeXSLTemplate.cpp : Implementation of CFakeXSLTemplate

#include "stdafx.h"
#include "FakeXSLTemplate.h"
#include "FakeXSLProcessor.h"
#include "FakeXMLNode.h"

// CFakeXSLTemplate

STDMETHODIMP CFakeXSLTemplate::InterfaceSupportsErrorInfo(REFIID riid)
{
	return InlineIsEqualGUID(__uuidof(IXSLTemplate), riid) ? S_OK : S_FALSE;
}

inline HRESULT CFakeXSLTemplate::FinalConstruct()
{
	CObjectCounter::instance().inc();
	return CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p);
}

inline void CFakeXSLTemplate::FinalRelease()
{
	m_pUnkMarshaler.Release();
	CObjectCounter::instance().dec();
}

HRESULT CFakeXSLTemplate::UnimplementedMethod(const char * name)
{
	return ::ReportUnimplementedMethod("FakeXSLTemplate:", name);
}

STDMETHODIMP CFakeXSLTemplate::createProcessor(IXSLProcessor ** ppProcessor)
{
	CComObject<CFakeXSLProcessor>* obj;
	CComObject<CFakeXSLProcessor>::CreateInstance(&obj);
	HRESULT hr = obj->Init(m_stylesheet, static_cast<IXSLTemplate*>(this));
	if(FAILED(hr)) {
		delete obj;
		return hr;
	}
	obj->AddRef();
	*ppProcessor = obj;
	return S_OK;
}
