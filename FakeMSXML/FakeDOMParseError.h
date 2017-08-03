// FakeDOMParseError.h : Declaration of the CFakeDOMParseError

#pragma once
#include "resource.h"       // main symbols



#include "FakeMSXML_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CFakeDOMParseError

class ATL_NO_VTABLE CFakeDOMParseError :
	public CComObjectRootEx<CComMultiThreadModel>,
//	public CComCoClass<CFakeDOMParseError, &CLSID_FakeDOMParseError>,
	public IDispatchImpl<IXMLDOMParseError, &__uuidof(IXMLDOMParseError), &LIBID_MSXML2, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	DECLARE_REGISTRY_RESOURCEID(IDR_FAKEDOMPARSEERROR)
	DECLARE_NOT_AGGREGATABLE(CFakeDOMParseError)
	BEGIN_COM_MAP(CFakeDOMParseError)
		COM_INTERFACE_ENTRY(IXMLDOMParseError)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	CFakeDOMParseError()
	{
		m_pUnkMarshaler = NULL;
	}
	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p);
	}
	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

public:
	STDMETHOD(get_errorCode)(/* [out][retval] */ long *errorCode)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_url)(/* [out][retval] */ BSTR *urlString)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_reason)(/* [out][retval] */ BSTR *reasonString)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_srcText)(/* [out][retval] */ BSTR *sourceString)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_line)(/* [out][retval] */ long *lineNumber)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_linepos)(/* [out][retval] */ long *linePosition)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get_filepos)(/* [out][retval] */ long *filePosition)
	{
		return E_NOTIMPL;
	}
};

//OBJECT_ENTRY_AUTO(__uuidof(FakeDOMParseError), CFakeDOMParseError)
