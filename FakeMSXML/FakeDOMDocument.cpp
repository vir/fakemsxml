// FakeDOMDocument.cpp : Implementation of CFakeDOMDocument

#include "stdafx.h"
#include "FakeDOMDocument.h"
#include <libxml/xpathInternals.h>
#include "FakeXMLNode.h"
#include "FakeDOMParseError.h"
#include "FakeDOMNodeList.h"
#include <regex>

// registration:
//  regsvr32 /s /n /i:user "C:\Projects\FakeMSXML\Debug\FakeMSXML.dll"

// to convert declarations into no-op implementations:
//  '<,'>s/STDMETHOD(\([^)]\+\))(\([^)]*\));/STDMETHODIMP CFakeDOMDocument::\1(\2)\r{\r\treturn UnimplementedMethod("\1");\r}\r

// CFakeDOMDocument

STDMETHODIMP CFakeDOMDocument::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&__uuidof(IXMLDOMDocument),
		&__uuidof(IXMLDOMDocument2),
		&__uuidof(IXMLDOMDocument3),
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

inline CFakeDOMDocument::CFakeDOMDocument()
	: m_doc(NULL)
{
}

CFakeDOMDocument::~CFakeDOMDocument()
{
}

inline HRESULT CFakeDOMDocument::FinalConstruct()
{
	CObjectCounter::instance().inc();
	return CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p);
}

inline void CFakeDOMDocument::FinalRelease()
{
	if(m_doc)
		xmlFreeDoc(m_doc);
	m_pUnkMarshaler.Release();
	CObjectCounter::instance().dec();
}

HRESULT CFakeDOMDocument::UnimplementedMethod(const char * name)
{
	return ::ReportUnimplementedMethod("DOMDocument", name);
}

void CFakeDOMDocument::registerNamespaces(xmlXPathContextPtr xpathCtx)
{
	auto it = m_props.find("SelectionNamespaces");
	if(it == m_props.end())
		return;
	std::string nslist = _bstr_t(it->second);
	std::regex e("\\s*xmlns:([^=]*)=([\"'])(.*?)\\2");

	std::smatch sm;
	std::string::const_iterator sstart(nslist.cbegin());
	while(std::regex_search(sstart, nslist.cend(), sm, e)) {
		sstart += sm.position() + sm.length();
		if(sm.size() == 4) {
			std::string pref = sm[1];
			std::string href = sm[3];
			if(xmlXPathRegisterNs(xpathCtx, (const xmlChar*)pref.c_str(), (const xmlChar*)href.c_str()) != 0) {
//				fprintf(stderr, "Error: unable to register NS with prefix=\"%s\" and href=\"%s\"\n", prefix, href);
				continue;
			}
		}
	}
}

// IXMLDOMNode
STDMETHODIMP CFakeDOMDocument::get_nodeName(/* [retval][out] */ BSTR *name)
{
	return UnimplementedMethod("get_nodeName");
}

STDMETHODIMP CFakeDOMDocument::get_nodeValue(/* [retval][out] */ VARIANT *value)
{
	return UnimplementedMethod("get_nodeValue");
}

STDMETHODIMP CFakeDOMDocument::put_nodeValue(/* [in] */ VARIANT value)
{
	return UnimplementedMethod("put_nodeValue");
}

STDMETHODIMP CFakeDOMDocument::get_nodeType(/* [retval][out] */ DOMNodeType *type)
{
	return UnimplementedMethod("get_nodeType");
}

STDMETHODIMP CFakeDOMDocument::get_parentNode(/* [retval][out] */ IXMLDOMNode **parent)
{
	return UnimplementedMethod("get_parentNode");
}

STDMETHODIMP CFakeDOMDocument::get_childNodes(/* [retval][out] */ IXMLDOMNodeList **childList)
{
	return UnimplementedMethod("get_childNodes");
}

STDMETHODIMP CFakeDOMDocument::get_firstChild(/* [retval][out] */ IXMLDOMNode **firstChild)
{
	xmlNodePtr n = m_doc->children;
	if(!n)
		return S_FALSE;
	BuildNodeCOMObject(n, firstChild);
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::get_lastChild(/* [retval][out] */ IXMLDOMNode **lastChild)
{
	return UnimplementedMethod("get_lastChild");
}

STDMETHODIMP CFakeDOMDocument::get_previousSibling(/* [retval][out] */ IXMLDOMNode **previousSibling)
{
	return UnimplementedMethod("get_previousSibling");
}

STDMETHODIMP CFakeDOMDocument::get_nextSibling(/* [retval][out] */ IXMLDOMNode **nextSibling)
{
	return UnimplementedMethod("get_nextSibling");
}

STDMETHODIMP CFakeDOMDocument::get_attributes(/* [retval][out] */ IXMLDOMNamedNodeMap **attributeMap)
{
	return UnimplementedMethod("get_attributes");
}

STDMETHODIMP CFakeDOMDocument::insertBefore(/* [in] */ IXMLDOMNode *newChild, /* [in] */ VARIANT refChild, /* [retval][out] */ IXMLDOMNode **outNewChild)
{
	return UnimplementedMethod("insertBefore");
}

STDMETHODIMP CFakeDOMDocument::replaceChild(/* [in] */ IXMLDOMNode *newChild, /* [in] */ IXMLDOMNode *oldChild, /* [retval][out] */ IXMLDOMNode **outOldChild)
{
	return UnimplementedMethod("replaceChild");
}

STDMETHODIMP CFakeDOMDocument::removeChild(/* [in] */ IXMLDOMNode *childNode, /* [retval][out] */ IXMLDOMNode **oldChild)
{
	xmlNodePtr root = xmlDocGetRootElement(m_doc);
	if(!root)
		return E_FAIL;
	xmlNodePtr oldChildInternal = GetInternalNode(childNode);
	if(!oldChildInternal)
		return E_UNEXPECTED;
	if(oldChildInternal != root)
		return E_INVALIDARG;
	//xmlDocSetRootElement(m_doc, NULL);
	xmlUnlinkNode(oldChildInternal);
	xmlFreeNode(oldChildInternal);
	return S_OK;
}

/*
 * appendChild on document:
 *  - element: put_documentElement equivalent
 *  - pi: sets document prolog
 */
STDMETHODIMP CFakeDOMDocument::appendChild(/* [in] */ IXMLDOMNode *newChild, /* [retval][out] */ IXMLDOMNode **outNewChild)
{
	{
		CComQIPtr<IXMLDOMElement> el(newChild);
		if(el) {
			HRESULT hr = putref_documentElement(el);
			if(SUCCEEDED(hr) && outNewChild)
				*outNewChild = CComPtr<IXMLDOMNode>(newChild).Detach();
			return hr;
		}
	}
	{
		CComQIPtr<IXMLDOMElement> pi(newChild);
		if(pi)
			return S_FALSE; // Ignore PIs
	}
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::hasChildNodes(/* [retval][out] */ VARIANT_BOOL *hasChild)
{
	return UnimplementedMethod("hasChildNodes");
}

STDMETHODIMP CFakeDOMDocument::get_ownerDocument(/* [retval][out] */ IXMLDOMDocument **XMLDOMDocument)
{
	return UnimplementedMethod("get_ownerDocument");
}

STDMETHODIMP CFakeDOMDocument::cloneNode(/* [in] */ VARIANT_BOOL deep, /* [retval][out] */ IXMLDOMNode **cloneRoot)
{
	return UnimplementedMethod("cloneNode");
}

STDMETHODIMP CFakeDOMDocument::get_nodeTypeString(/* [out][retval] */ BSTR *nodeType)
{
	return UnimplementedMethod("get_nodeTypeString");
}

STDMETHODIMP CFakeDOMDocument::get_text(/* [out][retval] */ BSTR *text)
{
	return UnimplementedMethod("get_text");
}

STDMETHODIMP CFakeDOMDocument::put_text(/* [in] */ BSTR text)
{
	return UnimplementedMethod("put_text");
}

STDMETHODIMP CFakeDOMDocument::get_specified(/* [retval][out] */ VARIANT_BOOL *isSpecified)
{
	return UnimplementedMethod("get_specified");
}

STDMETHODIMP CFakeDOMDocument::get_definition(/* [out][retval] */ IXMLDOMNode **definitionNode)
{
	return UnimplementedMethod("get_definition");
}

STDMETHODIMP CFakeDOMDocument::get_nodeTypedValue(/* [out][retval] */ VARIANT *typedValue)
{
	return UnimplementedMethod("get_nodeTypedValue");
}

STDMETHODIMP CFakeDOMDocument::put_nodeTypedValue(/* [in] */ VARIANT typedValue)
{
	return UnimplementedMethod("put_nodeTypedValue");
}

STDMETHODIMP CFakeDOMDocument::get_dataType(/* [out][retval] */ VARIANT *dataTypeName)
{
	return UnimplementedMethod("get_dataType");
}

STDMETHODIMP CFakeDOMDocument::put_dataType(/* [in] */ BSTR dataTypeName)
{
	return UnimplementedMethod("put_dataType");
}

STDMETHODIMP CFakeDOMDocument::get_xml(/* [out][retval] */ BSTR *xmlString)
{
	xmlBufferPtr buf = xmlBufferCreate();
	xmlNodeDump(buf, m_doc, (xmlNodePtr)m_doc, 0, 0);
	//xmlDocDumpFormatMemoryEnc
	XStr::Put(buf->content, xmlString);
	xmlBufferFree(buf);
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::transformNode(/* [in] */ IXMLDOMNode *stylesheet, /* [out][retval] */ BSTR *xmlString)
{
	return UnimplementedMethod("transformNode");
}

STDMETHODIMP CFakeDOMDocument::selectNodes(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNodeList **resultList)
{
	if(!resultList)
		return E_POINTER;
	xmlXPathContextPtr xpathCtx;
	xmlXPathObjectPtr xpathObj;
	/* Create xpath evaluation context */
	xpathCtx = xmlXPathNewContext(m_doc);
	if(xpathCtx == NULL) {
		//fprintf(stderr, "Error: unable to create new XPath context\n");
		return E_FAIL;
	}

	registerNamespaces(xpathCtx);

	/* Evaluate xpath expression */
	xpathObj = xmlXPathEvalExpression(XStr(queryString), xpathCtx);
	if(xpathObj == NULL) {
		//fprintf(stderr, "Error: unable to evaluate xpath expression \"%s\"\n", queryString);
		xmlXPathFreeContext(xpathCtx);
		return E_FAIL;
	}

	CComObject<CFakeDOMNodeList>* obj;
	CComObject<CFakeDOMNodeList>::CreateInstance(&obj);
	for(long idx = 0; idx < xpathObj->nodesetval->nodeNr; ++idx) {
		CComPtr<IXMLDOMNode> n;
		BuildNodeCOMObject(xpathObj->nodesetval->nodeTab[idx], &n);
		obj->AddNode(n);
	}
	obj->AddRef();
	*resultList = obj;

	/* Cleanup */
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::selectSingleNode(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNode **resultNode)
{
	xmlXPathContextPtr xpathCtx;
	xmlXPathObjectPtr xpathObj;
	/* Create xpath evaluation context */
	xpathCtx = xmlXPathNewContext(m_doc);
	if(xpathCtx == NULL) {
		//fprintf(stderr, "Error: unable to create new XPath context\n");
		return E_FAIL;
	}

	registerNamespaces(xpathCtx);

	/* Evaluate xpath expression */
	xpathObj = xmlXPathEvalExpression(XStr(queryString), xpathCtx);
	if(xpathObj == NULL) {
		//fprintf(stderr, "Error: unable to evaluate xpath expression \"%s\"\n", queryString);
		xmlXPathFreeContext(xpathCtx);
		return E_FAIL;
	}

	if(xpathObj->nodesetval->nodeNr)
		BuildNodeCOMObject(xpathObj->nodesetval->nodeTab[0], resultNode);

	/* Cleanup */
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::get_parsed(/* [out][retval] */ VARIANT_BOOL *isParsed)
{
	return UnimplementedMethod("get_parsed");
}

STDMETHODIMP CFakeDOMDocument::get_namespaceURI(/* [out][retval] */ BSTR *namespaceURI)
{
	return UnimplementedMethod("get_namespaceURI");
}

STDMETHODIMP CFakeDOMDocument::get_prefix(/* [out][retval] */ BSTR *prefixString)
{
	return UnimplementedMethod("get_prefix");
}

STDMETHODIMP CFakeDOMDocument::get_baseName(/* [out][retval] */ BSTR *nameString)
{
	return UnimplementedMethod("get_baseName");
}

STDMETHODIMP CFakeDOMDocument::transformNodeToObject(/* [in] */ IXMLDOMNode *stylesheet, /* [in] */ VARIANT outputObject)
{
	return UnimplementedMethod("transformNodeToObject");
}


// IXMLDOMDocument
STDMETHODIMP CFakeDOMDocument::get_doctype(/* [retval][out] */ IXMLDOMDocumentType **documentType)
{
	return UnimplementedMethod("get_doctype");
}

STDMETHODIMP CFakeDOMDocument::get_implementation(/* [retval][out] */ IXMLDOMImplementation **impl)
{
	return UnimplementedMethod("get_implementation");
}

STDMETHODIMP CFakeDOMDocument::get_documentElement(/* [retval][out] */ IXMLDOMElement **DOMElement)
{
	xmlNodePtr root = xmlDocGetRootElement(m_doc);
	if(!root)
		return S_FALSE;
	CComPtr<IXMLDOMNode> nn;
	BuildNodeCOMObject(root, &nn);
	return nn.QueryInterface(DOMElement);
}

STDMETHODIMP CFakeDOMDocument::putref_documentElement(/* [in] */ IXMLDOMElement *DOMElement)
{
	xmlNodePtr n = GetInternalNode(DOMElement);
	if(!n)
		return E_UNEXPECTED;
	xmlNodePtr oldroot = xmlDocSetRootElement(doc(), n);
	if(oldroot)
		xmlFreeNode(oldroot);
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::createElement(/* [in] */ BSTR tagName, /* [retval][out] */ IXMLDOMElement **element)
{
	xmlNodePtr e = xmlNewDocNode(doc(), NULL, XStr(tagName), NULL);
	CComPtr<IXMLDOMNode> n;
	BuildNodeCOMObject(e, &n);
	return n->QueryInterface(element);
}

STDMETHODIMP CFakeDOMDocument::createDocumentFragment(/* [retval][out] */ IXMLDOMDocumentFragment **docFrag)
{
	return UnimplementedMethod("createDocumentFragment");
}

STDMETHODIMP CFakeDOMDocument::createTextNode(/* [in] */ BSTR data, /* [retval][out] */ IXMLDOMText **text)
{
	return UnimplementedMethod("createTextNode");
}

STDMETHODIMP CFakeDOMDocument::createComment(/* [in] */ BSTR data, /* [retval][out] */ IXMLDOMComment **comment)
{
	return UnimplementedMethod("createComment");
}

STDMETHODIMP CFakeDOMDocument::createCDATASection(/* [in] */ BSTR data, /* [retval][out] */ IXMLDOMCDATASection **cdata)
{
	return UnimplementedMethod("createCDATASection");
}

STDMETHODIMP CFakeDOMDocument::createProcessingInstruction(/* [in] */ BSTR target, /* [in] */ BSTR data, /* [retval][out] */ IXMLDOMProcessingInstruction **pi)
{
	if(!pi)
		return E_POINTER;
	xmlNodePtr n = xmlNewDocPI(doc(), XStr(target), XStr(data));
	CComPtr<IXMLDOMNode> nn;
	BuildNodeCOMObject(n, &nn);
	return nn->QueryInterface(pi);
}

STDMETHODIMP CFakeDOMDocument::createAttribute(/* [in] */ BSTR name, /* [retval][out] */ IXMLDOMAttribute **attribute)
{
	return UnimplementedMethod("createAttribute");
}

STDMETHODIMP CFakeDOMDocument::createEntityReference(/* [in] */ BSTR name, /* [retval][out] */ IXMLDOMEntityReference **entityRef)
{
	return UnimplementedMethod("createEntityReference");
}

STDMETHODIMP CFakeDOMDocument::getElementsByTagName(/* [in] */ BSTR tagName, /* [retval][out] */ IXMLDOMNodeList **resultList)
{
	return UnimplementedMethod("getElementsByTagName");
}

STDMETHODIMP CFakeDOMDocument::createNode(/* [in] */ VARIANT Type, /* [in] */ BSTR name, /* [in] */ BSTR namespaceURI, /* [out][retval] */ IXMLDOMNode **node)
{
	long nodetype = _variant_t(Type);
	switch(nodetype) {
	case NODE_ATTRIBUTE:
	case NODE_CDATA_SECTION:
	case NODE_COMMENT:
		break;
	case NODE_TEXT:
	case NODE_DOCUMENT_TYPE:
		break;
	case NODE_ELEMENT: {
		_bstr_t pref, locn;
		LPWSTR colon = ::wcschr(name, L':');
		if(colon) {
			pref.Attach(CComBSTR(colon - name, name).Detach());
			++colon;
			locn = colon;
		} else {
			locn = name;
		}
		xmlNodePtr e = xmlNewDocNode(doc(), NULL, XStr(locn), NULL);
		if(namespaceURI && *namespaceURI) {
			xmlNsPtr ns = colon
				? xmlNewNs(e, XStr(namespaceURI), XStr(pref))
				: xmlNewNs(e, XStr(namespaceURI), NULL);
			xmlSetNs(e, ns);
		}
		BuildNodeCOMObject(e, node);
		return S_OK;
	}
	case NODE_ENTITY_REFERENCE:
	case NODE_PROCESSING_INSTRUCTION:
		break;
	case NODE_DOCUMENT:
	case NODE_DOCUMENT_FRAGMENT:
	case NODE_ENTITY:
	case NODE_NOTATION:
		return E_INVALIDARG;
	default:
		break;
	}
	return UnimplementedMethod("createNode");
}

STDMETHODIMP CFakeDOMDocument::nodeFromID(/* [in] */ BSTR idString, /* [out][retval] */ IXMLDOMNode **node)
{
	return UnimplementedMethod("nodeFromID");
}

STDMETHODIMP CFakeDOMDocument::load(/* [in] */ VARIANT xmlSource, /* [retval][out] */ VARIANT_BOOL *isSuccessful)
{
	if(m_doc)
		xmlFreeDoc(m_doc);
	m_doc = NULL;
	if(xmlSource.vt == VT_BSTR)
	{
		_bstr_t fn_bstr(xmlSource);
		// Skip "file://" prefix
		const char* fn = fn_bstr;
		if(0 == strncmp(fn, "file://", 7))
			fn += 7;
		m_doc = xmlReadFile(fn, NULL, 0);
		if(isSuccessful)
			*isSuccessful = m_doc ? VARIANT_TRUE : VARIANT_FALSE;
		return S_OK;
	}
	if(xmlSource.vt == (VT_ARRAY | VT_UI1))
	{
		SAFEARRAY* psa = V_ARRAY(&xmlSource);
		m_doc = xmlReadMemory(reinterpret_cast<const char*>(psa->pvData), psa->rgsabound[0].cElements, NULL, NULL, 0);
		if(isSuccessful)
			*isSuccessful = m_doc ? VARIANT_TRUE : VARIANT_FALSE;
		return S_OK;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CFakeDOMDocument::get_readyState(/* [out][retval] */ long *value)
{
	return UnimplementedMethod("get_readyState");
}

STDMETHODIMP CFakeDOMDocument::get_parseError(/* [out][retval] */ IXMLDOMParseError **errorObj)
{
	if(!errorObj)
		return E_POINTER;
	CComObject<CFakeDOMParseError>* obj;
	CComObject<CFakeDOMParseError>::CreateInstance(&obj);
	obj->AddRef();
	*errorObj = obj;
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::get_url(/* [out][retval] */ BSTR *urlString)
{
	return UnimplementedMethod("get_url");
}

STDMETHODIMP CFakeDOMDocument::get_async(/* [out][retval] */ VARIANT_BOOL *isAsync)
{
	return UnimplementedMethod("get_async");
}

STDMETHODIMP CFakeDOMDocument::put_async(/* [in] */ VARIANT_BOOL isAsync)
{
	return UnimplementedMethod("put_async");
}

STDMETHODIMP CFakeDOMDocument::abort(void)
{
	return UnimplementedMethod("abort");
}

STDMETHODIMP CFakeDOMDocument::loadXML(/* [in] */ BSTR bstrXML, /* [retval][out] */ VARIANT_BOOL *isSuccessful)
{
	const char * base = "xml";
	if(m_doc)
		xmlFreeDoc(m_doc);
	m_doc = xmlReadMemory(reinterpret_cast<const char*>(bstrXML), ::SysStringByteLen(bstrXML), base, "UTF-16LE", 0);
	if(isSuccessful)
		*isSuccessful = m_doc ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::save(/* [in] */ VARIANT destination)
{
	_bstr_t fn(destination);
//	int rc = xmlSaveFile(fn, m_doc);
	int rc = xmlSaveFormatFile(fn, m_doc, 0);
	return rc < 0 ? E_FAIL : S_OK;
}

STDMETHODIMP CFakeDOMDocument::get_validateOnParse(/* [out][retval] */ VARIANT_BOOL *isValidating)
{
	return UnimplementedMethod("get_validateOnParse");
}

STDMETHODIMP CFakeDOMDocument::put_validateOnParse(/* [in] */ VARIANT_BOOL isValidating)
{
	return UnimplementedMethod("put_validateOnParse");
}

STDMETHODIMP CFakeDOMDocument::get_resolveExternals(/* [out][retval] */ VARIANT_BOOL *isResolving)
{
	return UnimplementedMethod("get_resolveExternals");
}

STDMETHODIMP CFakeDOMDocument::put_resolveExternals(/* [in] */ VARIANT_BOOL isResolving)
{
	xmlSubstituteEntitiesDefault(isResolving ? 1 : 0);
	xmlLoadExtDtdDefaultValue = isResolving ? 1 : 0;
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::get_preserveWhiteSpace(/* [out][retval] */ VARIANT_BOOL *isPreserving)
{
	return UnimplementedMethod("get_preserveWhiteSpace");
}

STDMETHODIMP CFakeDOMDocument::put_preserveWhiteSpace(/* [in] */ VARIANT_BOOL isPreserving)
{
	return UnimplementedMethod("put_preserveWhiteSpace");
}

STDMETHODIMP CFakeDOMDocument::put_onreadystatechange(/* [in] */ VARIANT readystatechangeSink)
{
	return UnimplementedMethod("put_onreadystatechange");
}

STDMETHODIMP CFakeDOMDocument::put_ondataavailable(/* [in] */ VARIANT ondataavailableSink)
{
	return UnimplementedMethod("put_ondataavailable");
}

STDMETHODIMP CFakeDOMDocument::put_ontransformnode(/* [in] */ VARIANT ontransformnodeSink)
{
	return UnimplementedMethod("put_ontransformnode");
}


// IXMLDOMDocument2
STDMETHODIMP CFakeDOMDocument::get_namespaces(/* [retval][out] */ IXMLDOMSchemaCollection **namespaceCollection)
{
	return UnimplementedMethod("get_namespaces");
}

STDMETHODIMP CFakeDOMDocument::get_schemas(/* [retval][out] */ VARIANT *otherCollection)
{
	return UnimplementedMethod("get_schemas");
}

STDMETHODIMP CFakeDOMDocument::putref_schemas(/* [in] */ VARIANT otherCollection)
{
	return UnimplementedMethod("putref_schemas");
}

STDMETHODIMP CFakeDOMDocument::validate(/* [out][retval] */ IXMLDOMParseError **errorObj)
{
	return UnimplementedMethod("validate");
}

STDMETHODIMP CFakeDOMDocument::setProperty(/* [in] */ BSTR name, /* [in] */ VARIANT value)
{
	m_props[name] = value;
	if(0 == _wcsicmp(name, L"SelectionLanguage") && value.vt == VT_BSTR && 0 != _wcsicmp(value.bstrVal, L"XPath"))
		return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CFakeDOMDocument::getProperty(/* [in] */ BSTR name, /* [retval][out] */ VARIANT *value)
{
	auto it = m_props.find(name);
	if(it == m_props.end())
		return S_FALSE;
	if(value)
		return CComVariant(it->second).Detach(value);
	return S_OK;
}


// IXMLDOMDocument3
STDMETHODIMP CFakeDOMDocument::validateNode(/* [in] */ IXMLDOMNode *node, /* [retval][out] */ IXMLDOMParseError **errorObj)
{
	return UnimplementedMethod("validateNode");
}

STDMETHODIMP CFakeDOMDocument::importNode(/* [in] */ IXMLDOMNode *node, /* [in] */ VARIANT_BOOL deep, /* [retval][out] */ IXMLDOMNode **clone)
{
	return UnimplementedMethod("importNode");
}





