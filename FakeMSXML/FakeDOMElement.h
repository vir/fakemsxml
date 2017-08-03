// FakeDOMElement.h : Declaration of the CFakeDOMElement

#pragma once
#include "resource.h"       // main symbols



#include "FakeMSXML_i.h"



using namespace ATL;


// CFakeDOMElement

class ATL_NO_VTABLE CFakeDOMElement :
	public CComObjectRootEx<CComMultiThreadModel>,
//	public CComCoClass<CFakeDOMElement, &CLSID_FakeDOMElement>,
	public ISupportErrorInfo,
	public IFakeXMLInternalNode,
	public IDispatchImpl<IXMLDOMElement, &IID_IXMLDOMElement, &LIBID_MSXML2, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
//	DECLARE_REGISTRY_RESOURCEID(IDR_FAKEDOMELEMENT1)
	BEGIN_COM_MAP(CFakeDOMElement)
		COM_INTERFACE_ENTRY(IXMLDOMNode)
		COM_INTERFACE_ENTRY(IXMLDOMElement)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
		COM_INTERFACE_ENTRY(IFakeXMLInternalNode)
	END_COM_MAP()
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid); // ISupportsErrorInfo
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	STDMETHOD(get_InternalNode)(void **pInt) { *pInt = m_element; return S_OK; }
	STDMETHOD(put_InternalNode)(void *pInt) { return E_NOTIMPL; }

	CFakeDOMElement();
	~CFakeDOMElement();
	HRESULT FinalConstruct();
	void FinalRelease();
	void Init(xmlNodePtr el);
	HRESULT UnimplementedMethod(const char * name);
private:
	CComPtr<IUnknown> m_pUnkMarshaler;
	xmlNodePtr m_element;
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

	// IXMLDOMElement
	STDMETHOD(get_tagName)(/* [retval][out] */ BSTR *tagName);
	STDMETHOD(getAttribute)(/* [in] */ BSTR name, /* [retval][out] */ VARIANT *value);
	STDMETHOD(setAttribute)(/* [in] */ BSTR name, /* [in] */ VARIANT value);
	STDMETHOD(removeAttribute)(/* [in] */ BSTR name);
	STDMETHOD(getAttributeNode)(/* [in] */ BSTR name, /* [retval][out] */ IXMLDOMAttribute **attributeNode);
	STDMETHOD(setAttributeNode)(/* [in] */ IXMLDOMAttribute *DOMAttribute, /* [retval][out] */ IXMLDOMAttribute **attributeNode);
	STDMETHOD(removeAttributeNode)(/* [in] */ IXMLDOMAttribute *DOMAttribute, /* [retval][out] */ IXMLDOMAttribute **attributeNode);
	STDMETHOD(getElementsByTagName)(/* [in] */ BSTR tagName, /* [retval][out] */ IXMLDOMNodeList **resultList);
	STDMETHOD(normalize)(void);
};

//OBJECT_ENTRY_AUTO(__uuidof(FakeDOMElement), CFakeDOMElement)
