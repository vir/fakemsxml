// FakeDOMDocument.h : Declaration of the CFakeDOMDocument

#pragma once
#include "resource.h"       // main symbols

#include "FakeMSXML_i.h"
#include "_IFakeDOMDocumentEvents_CP.h"

using namespace ATL;

// CFakeDOMDocument
class ATL_NO_VTABLE CFakeDOMDocument :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFakeDOMDocument, &CLSID_FakeDOMDocument>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CFakeDOMDocument>,
	public CProxy_IFakeDOMDocumentEvents<CFakeDOMDocument>,
	public IObjectWithSiteImpl<CFakeDOMDocument>,
	public IFakeXMLInternalNode,
	public IDispatchImpl<IXMLDOMDocument3, &IID_IXMLDOMDocument3, &LIBID_MSXML2, /*wMajor =*/ 1, /*wMinor =*/ 0>
//	, public IFakeDOMDocument
{
public:
	DECLARE_REGISTRY_RESOURCEID(IDR_FAKEDOMDOCUMENT)
	BEGIN_COM_MAP(CFakeDOMDocument)
	//	COM_INTERFACE_ENTRY(IFakeDOMDocument)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IObjectWithSite)
		COM_INTERFACE_ENTRY(IXMLDOMNode)
		COM_INTERFACE_ENTRY(IXMLDOMDocument)
		COM_INTERFACE_ENTRY(IXMLDOMDocument2)
		COM_INTERFACE_ENTRY(IXMLDOMDocument3)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
		COM_INTERFACE_ENTRY(IFakeXMLInternalNode)
	END_COM_MAP()
	BEGIN_CONNECTION_POINT_MAP(CFakeDOMDocument)
		CONNECTION_POINT_ENTRY(__uuidof(_IFakeDOMDocumentEvents))
	END_CONNECTION_POINT_MAP()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid); // ISupportsErrorInfo
	STDMETHOD(get_InternalNode)(void **pInt) { *pInt = (xmlNodePtr)m_doc; return S_OK; }
	STDMETHOD(put_InternalNode)(void *Int) { if(m_doc) xmlFreeDoc(m_doc); m_doc = (xmlDocPtr)Int; return S_OK; }

	CFakeDOMDocument();
	~CFakeDOMDocument();
	HRESULT FinalConstruct();
	void FinalRelease();

	void Init(xmlDocPtr doc)
	{
		if(m_doc)
			xmlFreeDoc(m_doc);
		m_doc = doc;
	}
	HRESULT UnimplementedMethod(const char* name);
protected:
	xmlDocPtr doc()
	{
		if(!m_doc)
			m_doc = xmlNewDoc((const xmlChar*)"1.0");
		return m_doc;
	}
	void registerNamespaces(xmlXPathContextPtr xpathCtx);
private:
	CComPtr<IUnknown> m_pUnkMarshaler;
	std::map<_bstr_t, _variant_t> m_props;
	xmlDocPtr m_doc;
public:
	// IXMLDOMNode
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

	// IXMLDOMDocument
	STDMETHOD(get_doctype)(/* [retval][out] */ IXMLDOMDocumentType **documentType);
	STDMETHOD(get_implementation)(/* [retval][out] */ IXMLDOMImplementation **impl);
	STDMETHOD(get_documentElement)(/* [retval][out] */ IXMLDOMElement **DOMElement);
	STDMETHOD(putref_documentElement)(/* [in] */ IXMLDOMElement *DOMElement);
	STDMETHOD(createElement)(/* [in] */ BSTR tagName, /* [retval][out] */ IXMLDOMElement **element);
	STDMETHOD(createDocumentFragment)(/* [retval][out] */ IXMLDOMDocumentFragment **docFrag);
	STDMETHOD(createTextNode)(/* [in] */ BSTR data, /* [retval][out] */ IXMLDOMText **text);
	STDMETHOD(createComment)(/* [in] */ BSTR data, /* [retval][out] */ IXMLDOMComment **comment);
	STDMETHOD(createCDATASection)(/* [in] */ BSTR data, /* [retval][out] */ IXMLDOMCDATASection **cdata);
	STDMETHOD(createProcessingInstruction)(/* [in] */ BSTR target, /* [in] */ BSTR data, /* [retval][out] */ IXMLDOMProcessingInstruction **pi);
	STDMETHOD(createAttribute)(/* [in] */ BSTR name, /* [retval][out] */ IXMLDOMAttribute **attribute);
	STDMETHOD(createEntityReference)(/* [in] */ BSTR name, /* [retval][out] */ IXMLDOMEntityReference **entityRef);
	STDMETHOD(getElementsByTagName)(/* [in] */ BSTR tagName, /* [retval][out] */ IXMLDOMNodeList **resultList);
	STDMETHOD(createNode)(/* [in] */ VARIANT Type, /* [in] */ BSTR name, /* [in] */ BSTR namespaceURI, /* [out][retval] */ IXMLDOMNode **node);
	STDMETHOD(nodeFromID)(/* [in] */ BSTR idString, /* [out][retval] */ IXMLDOMNode **node);
	STDMETHOD(load)(/* [in] */ VARIANT xmlSource, /* [retval][out] */ VARIANT_BOOL *isSuccessful);
	STDMETHOD(get_readyState)(/* [out][retval] */ long *value);
	STDMETHOD(get_parseError)(/* [out][retval] */ IXMLDOMParseError **errorObj);
	STDMETHOD(get_url)(/* [out][retval] */ BSTR *urlString);
	STDMETHOD(get_async)(/* [out][retval] */ VARIANT_BOOL *isAsync);
	STDMETHOD(put_async)(/* [in] */ VARIANT_BOOL isAsync);
	STDMETHOD(abort)(void);
	STDMETHOD(loadXML)(/* [in] */ BSTR bstrXML, /* [retval][out] */ VARIANT_BOOL *isSuccessful);
	STDMETHOD(save)(/* [in] */ VARIANT destination);
	STDMETHOD(get_validateOnParse)(/* [out][retval] */ VARIANT_BOOL *isValidating);
	STDMETHOD(put_validateOnParse)(/* [in] */ VARIANT_BOOL isValidating);
	STDMETHOD(get_resolveExternals)(/* [out][retval] */ VARIANT_BOOL *isResolving);
	STDMETHOD(put_resolveExternals)(/* [in] */ VARIANT_BOOL isResolving);
	STDMETHOD(get_preserveWhiteSpace)(/* [out][retval] */ VARIANT_BOOL *isPreserving);
	STDMETHOD(put_preserveWhiteSpace)(/* [in] */ VARIANT_BOOL isPreserving);
	STDMETHOD(put_onreadystatechange)(/* [in] */ VARIANT readystatechangeSink);
	STDMETHOD(put_ondataavailable)(/* [in] */ VARIANT ondataavailableSink);
	STDMETHOD(put_ontransformnode)(/* [in] */ VARIANT ontransformnodeSink);

	// IXMLDOMDocument2
	STDMETHOD(get_namespaces)(/* [retval][out] */ IXMLDOMSchemaCollection **namespaceCollection);
	STDMETHOD(get_schemas)(/* [retval][out] */ VARIANT *otherCollection);
	STDMETHOD(putref_schemas)(/* [in] */ VARIANT otherCollection);
	STDMETHOD(validate)(/* [out][retval] */ IXMLDOMParseError **errorObj);
	STDMETHOD(setProperty)(/* [in] */ BSTR name, /* [in] */ VARIANT value);
	STDMETHOD(getProperty)(/* [in] */ BSTR name, /* [retval][out] */ VARIANT *value);

	// IXMLDOMDocument3
	STDMETHOD(validateNode)(/* [in] */ IXMLDOMNode *node, /* [retval][out] */ IXMLDOMParseError **errorObj);
	STDMETHOD(importNode)(/* [in] */ IXMLDOMNode *node, /* [in] */ VARIANT_BOOL deep, /* [retval][out] */ IXMLDOMNode **clone);
};

OBJECT_ENTRY_AUTO(__uuidof(FakeDOMDocument), CFakeDOMDocument)
