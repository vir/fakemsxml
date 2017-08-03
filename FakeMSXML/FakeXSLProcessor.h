// FakeXSLProcessor.h : Declaration of the CFakeXSLProcessor

#pragma once
#include "resource.h"       // main symbols



#include "FakeMSXML_i.h"
#include <libxslt/xsltInternals.h>
#include <vector>



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

class CXsltParams
{
public:
	~CXsltParams() { for(auto s : vec) delete[] s; }
	void add(BSTR name, VARIANT val);
	operator const char** () { ensureZ();  return &vec[0]; }
	void ensureZ() { if(vec.empty() || *vec.rbegin() != nullptr) vec.push_back(nullptr); }
public:
	std::vector<const char*> vec;
};

// CFakeXSLProcessor

class ATL_NO_VTABLE CFakeXSLProcessor :
	public CComObjectRootEx<CComMultiThreadModel>,
//	public CComCoClass<CFakeXSLProcessor, &CLSID_FakeXSLProcessor>,
	public ISupportErrorInfo,
	public IDispatchImpl<IXSLProcessor, &__uuidof(IXSLProcessor), &LIBID_MSXML2, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	DECLARE_REGISTRY_RESOURCEID(IDR_FAKEXSLPROCESSOR)
	BEGIN_COM_MAP(CFakeXSLProcessor)
		COM_INTERFACE_ENTRY(IXSLProcessor)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	CFakeXSLProcessor(): m_stylesheet(NULL), m_input(NULL), m_result(NULL)
	{
		m_pUnkMarshaler = NULL;
	}

	HRESULT FinalConstruct();
	void FinalRelease();
	HRESULT UnimplementedMethod(const char * name);

	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid); // ISupportsErrorInfo

	HRESULT Init(IXMLDOMNode* doc, IUnknown* keepRef);

private:
	CComPtr<IUnknown> m_pUnkMarshaler;
	CComPtr<IUnknown> m_keep_stylesheet_dom_referenced;
	xsltStylesheetPtr m_stylesheet;
	xmlDocPtr m_input;
	CComVariant m_output;
	CComPtr<IXMLDOMDocument> m_result;
	CXsltParams m_params;

public: // IXSLProcessor
	STDMETHOD(put_input)(/* [in] */ VARIANT var);
	STDMETHOD(get_input)(/* [retval][out] */ VARIANT *pVar);
	STDMETHOD(get_ownerTemplate)(/* [retval][out] */ IXSLTemplate **ppTemplate);
	STDMETHOD(setStartMode)(/* [in] */ BSTR mode, /* [defaultvalue][in] */ BSTR namespaceURI = L"");
	STDMETHOD(get_startMode)(/* [retval][out] */ BSTR *mode);
	STDMETHOD(get_startModeURI)(/* [retval][out] */ BSTR *namespaceURI);
	STDMETHOD(put_output)(/* [in] */ VARIANT output);
	STDMETHOD(get_output)(/* [retval][out] */ VARIANT *pOutput);
	STDMETHOD(transform)(/* [retval][out] */ VARIANT_BOOL *pDone);
	STDMETHOD(reset)(void);
	STDMETHOD(get_readyState)(/* [retval][out] */ long *pReadyState);
	STDMETHOD(addParameter)(/* [in] */ BSTR baseName, /* [in] */ VARIANT parameter, /* [defaultvalue][in] */ BSTR namespaceURI = L"");
	STDMETHOD(addObject)(/* [in] */ IDispatch *obj, /* [in] */ BSTR namespaceURI);
	STDMETHOD(get_stylesheet)(/* [retval][out] */ IXMLDOMNode **stylesheet);
};

// OBJECT_ENTRY_AUTO(__uuidof(FakeXSLProcessor), CFakeXSLProcessor)
