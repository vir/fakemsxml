// FakeDOMProcInstr.h : Declaration of the CFakeDOMProcInstr

#pragma once
#include "resource.h"       // main symbols



#include "FakeMSXML_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CFakeDOMProcInstr

class ATL_NO_VTABLE CFakeDOMProcInstr :
	public CComObjectRootEx<CComMultiThreadModel>,
//	public CComCoClass<CFakeDOMProcInstr, &CLSID_FakeDOMProcInstr>,
	public IFakeXMLInternalNode,
	public IDispatchImpl<IXMLDOMProcessingInstruction, &IID_IXMLDOMProcessingInstruction, &LIBID_MSXML2, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	DECLARE_REGISTRY_RESOURCEID(IDR_FAKEDOMPROCINSTR)
	DECLARE_NOT_AGGREGATABLE(CFakeDOMProcInstr)
	BEGIN_COM_MAP(CFakeDOMProcInstr)
		COM_INTERFACE_ENTRY(IXMLDOMProcessingInstruction)
		COM_INTERFACE_ENTRY(IXMLDOMNode)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
		COM_INTERFACE_ENTRY(IFakeXMLInternalNode)
	END_COM_MAP()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	STDMETHOD(get_InternalNode)(void **pInt) { *pInt = m_pi; return S_OK; }
	STDMETHOD(put_InternalNode)(void *pInt) { return E_NOTIMPL; }

	CFakeDOMProcInstr()
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
	void Init(xmlNodePtr n)
	{
		m_pi = n;
	}
	HRESULT UnimplementedMethod(const char * name)
	{
		return ::ReportUnimplementedMethod("DOMProcInstr", name);
	}

private:
	CComPtr<IUnknown> m_pUnkMarshaler;
	xmlNodePtr m_pi;

public: // IXMLDOMNode
	STDMETHOD(get_nodeName)(/* [retval][out] */ BSTR *name);
	STDMETHOD(get_nodeValue)(/* [retval][out] */ VARIANT *value);
	STDMETHOD(put_nodeValue)(/* [in] */ VARIANT value);
	STDMETHOD(get_nodeType)(/* [retval][out] */ DOMNodeType *type);
	STDMETHOD(get_parentNode)(/* [retval][out] */ IXMLDOMNode **parent);
	STDMETHOD(get_childNodes)(/* [retval][out] */ IXMLDOMNodeList **childList);
	STDMETHOD(get_firstChild)(/* [retval][out] */ IXMLDOMNode **firstChild);
	STDMETHOD(get_lastChild)(/* [retval][out] */ IXMLDOMNode **lastChild);
	STDMETHOD(get_previousSibling)(/* [retval][out] */ IXMLDOMNode **previousSibling);
	STDMETHOD(get_nextSibling)(/* [retval][out] */ IXMLDOMNode **nextSibling);
	STDMETHOD(get_attributes)(/* [retval][out] */ IXMLDOMNamedNodeMap **attributeMap);
	STDMETHOD(insertBefore)(/* [in] */ IXMLDOMNode *newChild, /* [in] */ VARIANT refChild, /* [retval][out] */ IXMLDOMNode **outNewChild);
	STDMETHOD(replaceChild)(/* [in] */ IXMLDOMNode *newChild, /* [in] */ IXMLDOMNode *oldChild, /* [retval][out] */ IXMLDOMNode **outOldChild);
	STDMETHOD(removeChild)(/* [in] */ IXMLDOMNode *childNode, /* [retval][out] */ IXMLDOMNode **oldChild);
	STDMETHOD(appendChild)(/* [in] */ IXMLDOMNode *newChild, /* [retval][out] */ IXMLDOMNode **outNewChild);
	STDMETHOD(hasChildNodes)(/* [retval][out] */ VARIANT_BOOL *hasChild);
	STDMETHOD(get_ownerDocument)(/* [retval][out] */ IXMLDOMDocument **XMLDOMDocument);
	STDMETHOD(cloneNode)(/* [in] */ VARIANT_BOOL deep, /* [retval][out] */ IXMLDOMNode **cloneRoot);
	STDMETHOD(get_nodeTypeString)(/* [out][retval] */ BSTR *nodeType);
	STDMETHOD(get_text)(/* [out][retval] */ BSTR *text);
	STDMETHOD(put_text)(/* [in] */ BSTR text);
	STDMETHOD(get_specified)(/* [retval][out] */ VARIANT_BOOL *isSpecified);
	STDMETHOD(get_definition)(/* [out][retval] */ IXMLDOMNode **definitionNode);
	STDMETHOD(get_nodeTypedValue)(/* [out][retval] */ VARIANT *typedValue);
	STDMETHOD(put_nodeTypedValue)(/* [in] */ VARIANT typedValue);
	STDMETHOD(get_dataType)(/* [out][retval] */ VARIANT *dataTypeName);
	STDMETHOD(put_dataType)(/* [in] */ BSTR dataTypeName);
	STDMETHOD(get_xml)(/* [out][retval] */ BSTR *xmlString);
	STDMETHOD(transformNode)(/* [in] */ IXMLDOMNode *stylesheet, /* [out][retval] */ BSTR *xmlString);
	STDMETHOD(selectNodes)(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNodeList **resultList);
	STDMETHOD(selectSingleNode)(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNode **resultNode);
	STDMETHOD(get_parsed)(/* [out][retval] */ VARIANT_BOOL *isParsed);
	STDMETHOD(get_namespaceURI)(/* [out][retval] */ BSTR *namespaceURI);
	STDMETHOD(get_prefix)(/* [out][retval] */ BSTR *prefixString);
	STDMETHOD(get_baseName)(/* [out][retval] */ BSTR *nameString);
	STDMETHOD(transformNodeToObject)(/* [in] */ IXMLDOMNode *stylesheet, /* [in] */ VARIANT outputObject);

	// IXMLDOMProcessingInstruction
	STDMETHOD(get_target)(/* [retval][out] */ BSTR *name);
	STDMETHOD(get_data)(/* [retval][out] */ BSTR *value);
	STDMETHOD(put_data)(/* [in] */ BSTR value);
};

//OBJECT_ENTRY_AUTO(__uuidof(FakeDOMProcInstr), CFakeDOMProcInstr)

