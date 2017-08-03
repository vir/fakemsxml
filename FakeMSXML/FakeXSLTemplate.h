// FakeXSLTemplate.h : Declaration of the CFakeXSLTemplate

#pragma once
#include "resource.h"       // main symbols



#include "FakeMSXML_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CFakeXSLTemplate

class ATL_NO_VTABLE CFakeXSLTemplate :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFakeXSLTemplate, &CLSID_FakeXSLTemplate>,
	public ISupportErrorInfo,
	public IDispatchImpl<IXSLTemplate, &__uuidof(IXSLTemplate), &LIBID_MSXML2, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	DECLARE_REGISTRY_RESOURCEID(IDR_FAKEXSLTEMPLATE)
	BEGIN_COM_MAP(CFakeXSLTemplate)
		COM_INTERFACE_ENTRY(IXSLTemplate)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid); // ISupportsErrorInfo

	CFakeXSLTemplate()
	{
		m_pUnkMarshaler = NULL;
	}
	HRESULT FinalConstruct();
	void FinalRelease();
	HRESULT UnimplementedMethod(const char* name);

	CComPtr<IUnknown> m_pUnkMarshaler;

public: // IXSLTemplate
	STDMETHOD(putref_stylesheet)(/* [in] */ IXMLDOMNode *stylesheet)
	{
		m_stylesheet = stylesheet;
		return S_OK;
	}
	STDMETHOD(get_stylesheet)(/* [retval][out] */ IXMLDOMNode **stylesheet)
	{
		return m_stylesheet.CopyTo(stylesheet);
	}
	STDMETHOD(createProcessor)(/* [retval][out] */ IXSLProcessor **ppProcessor);
private:
	CComPtr<IXMLDOMNode> m_stylesheet;
};

OBJECT_ENTRY_AUTO(__uuidof(FakeXSLTemplate), CFakeXSLTemplate)
