// FakeDOMElement.cpp : Implementation of CFakeDOMElement

#include "stdafx.h"
#include "FakeDOMElement.h"
#include "FakeXMLNode.h"

// CFakeDOMElement

STDMETHODIMP CFakeDOMElement::InterfaceSupportsErrorInfo(REFIID riid)
{
	return InlineIsEqualGUID(IID_IFakeDOMElement, riid) ? S_OK : S_FALSE;
}

CFakeDOMElement::CFakeDOMElement()
	: m_element(NULL)
{
}

CFakeDOMElement::~CFakeDOMElement()
{
}

HRESULT CFakeDOMElement::FinalConstruct()
{
	CObjectCounter::instance().inc();
	return CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p);
}

void CFakeDOMElement::FinalRelease()
{
	m_pUnkMarshaler.Release();
	CObjectCounter::instance().dec();
}

void CFakeDOMElement::Init(xmlNodePtr el)
{
	m_element = el;
}

inline HRESULT CFakeDOMElement::UnimplementedMethod(const char * name)
{
	return ::ReportUnimplementedMethod("DOMElement", name);
}


// IXMLDOMNode
STDMETHODIMP CFakeDOMElement::get_nodeName(/* [retval][out] */ BSTR *name)
{
	if(!m_element->ns)
		return XStr::Put(m_element->name, name);
	std::string qname { (const char*)m_element->ns->prefix };
	qname += ":";
	qname += (const char*)m_element->name;
	return XStr::Put(qname.c_str(), name);
}

STDMETHODIMP CFakeDOMElement::get_nodeValue(/* [retval][out] */ VARIANT *value)
{
	return UnimplementedMethod("get_nodeValue");
}

STDMETHODIMP CFakeDOMElement::put_nodeValue(/* [in] */ VARIANT value)
{
	return UnimplementedMethod("put_nodeValue");
}

STDMETHODIMP CFakeDOMElement::get_nodeType(/* [retval][out] */ DOMNodeType *type)
{
	return UnimplementedMethod("get_nodeType");
}

STDMETHODIMP CFakeDOMElement::get_parentNode(/* [retval][out] */ IXMLDOMNode **parent)
{
	return UnimplementedMethod("get_parentNode");
}

STDMETHODIMP CFakeDOMElement::get_childNodes(/* [retval][out] */ IXMLDOMNodeList **childList)
{
	return UnimplementedMethod("get_childNodes");
}

STDMETHODIMP CFakeDOMElement::get_firstChild(/* [retval][out] */ IXMLDOMNode **firstChild)
{
	return UnimplementedMethod("get_firstChild");
}

STDMETHODIMP CFakeDOMElement::get_lastChild(/* [retval][out] */ IXMLDOMNode **lastChild)
{
	return UnimplementedMethod("get_lastChild");
}

STDMETHODIMP CFakeDOMElement::get_previousSibling(/* [retval][out] */ IXMLDOMNode **previousSibling)
{
	return UnimplementedMethod("get_previousSibling");
}

STDMETHODIMP CFakeDOMElement::get_nextSibling(/* [retval][out] */ IXMLDOMNode **nextSibling)
{
	return UnimplementedMethod("get_nextSibling");
}

STDMETHODIMP CFakeDOMElement::get_attributes(/* [retval][out] */ IXMLDOMNamedNodeMap **attributeMap)
{
	return UnimplementedMethod("get_attributes");
}

STDMETHODIMP CFakeDOMElement::insertBefore(/* [in] */ IXMLDOMNode *newChild, /* [in] */ VARIANT refChild, /* [retval][out] */ IXMLDOMNode **outNewChild)
{
	return UnimplementedMethod("insertBefore");
}

STDMETHODIMP CFakeDOMElement::replaceChild(/* [in] */ IXMLDOMNode *newChild, /* [in] */ IXMLDOMNode *oldChild, /* [retval][out] */ IXMLDOMNode **outOldChild)
{
	return UnimplementedMethod("replaceChild");
}

STDMETHODIMP CFakeDOMElement::removeChild(/* [in] */ IXMLDOMNode *childNode, /* [retval][out] */ IXMLDOMNode **oldChild)
{
	return UnimplementedMethod("removeChild");
}

STDMETHODIMP CFakeDOMElement::appendChild(/* [in] */ IXMLDOMNode *newChild, /* [retval][out] */ IXMLDOMNode **outNewChild)
{
	xmlNodePtr nc = GetInternalNode(newChild);
	if(nc && nc->doc == m_element->doc) { // shortcut for node from same document
		xmlNodePtr nn = xmlAddChild(m_element, nc);
		if(outNewChild)
			BuildNodeCOMObject((xmlNodePtr)nn, outNewChild);
		return S_OK;
	}
#if 0
	if(nc) { // just another FakeMSXML document
		xmlBufferPtr buf = xmlBufferCreate();
		xmlNodeDump(buf, nc->doc, (xmlNodePtr)nc, 0, 0);
// TODO: copy node and sanitize namespaces, then remove new node (as in get_xml(...)
		xmlNodePtr nn = nullptr;
		xmlParserErrors e = xmlParseInNodeContext(m_element, (const char*)buf->content, buf->use, 0, &nn);
		if(nn)
			xmlAddChild(m_element, nn);

		xmlBufferFree(buf);
	}
#endif
	// foreign child - parse newChild's serialized content
	CComBSTR xml;
	HRESULT hr = newChild->get_xml(&xml);
	if(FAILED(hr))
		return hr;
	xmlNodePtr nn = nullptr;
	XStr x(xml);
	xmlParserErrors e = xmlParseInNodeContext(m_element, (const char*)(xmlChar*)x, x.length(), 0, &nn);
	if(nn)
		xmlAddChild(m_element, nn);
	return nn ? S_OK : E_FAIL;

}

STDMETHODIMP CFakeDOMElement::hasChildNodes(/* [retval][out] */ VARIANT_BOOL *hasChild)
{
	return UnimplementedMethod("hasChildNodes");
}

STDMETHODIMP CFakeDOMElement::get_ownerDocument(/* [retval][out] */ IXMLDOMDocument **XMLDOMDocument)
{
	return UnimplementedMethod("get_ownerDocument");
}

STDMETHODIMP CFakeDOMElement::cloneNode(/* [in] */ VARIANT_BOOL deep, /* [retval][out] */ IXMLDOMNode **cloneRoot)
{
	return UnimplementedMethod("cloneNode");
}

STDMETHODIMP CFakeDOMElement::get_nodeTypeString(/* [out][retval] */ BSTR *nodeType)
{
	return UnimplementedMethod("get_nodeTypeString");
}

STDMETHODIMP CFakeDOMElement::get_text(/* [out][retval] */ BSTR *text)
{
	if(!text)
		return E_POINTER;
	xmlChar* t = xmlNodeGetContent(m_element);
	XStr::Put(t, text);
	xmlFree(t);
	return S_OK;
}

STDMETHODIMP CFakeDOMElement::put_text(/* [in] */ BSTR text)
{
	return UnimplementedMethod("put_text");
}

STDMETHODIMP CFakeDOMElement::get_specified(/* [retval][out] */ VARIANT_BOOL *isSpecified)
{
	return UnimplementedMethod("get_specified");
}

STDMETHODIMP CFakeDOMElement::get_definition(/* [out][retval] */ IXMLDOMNode **definitionNode)
{
	return UnimplementedMethod("get_definition");
}

STDMETHODIMP CFakeDOMElement::get_nodeTypedValue(/* [out][retval] */ VARIANT *typedValue)
{
	return UnimplementedMethod("get_nodeTypedValue");
}

STDMETHODIMP CFakeDOMElement::put_nodeTypedValue(/* [in] */ VARIANT typedValue)
{
	return UnimplementedMethod("put_nodeTypedValue");
}

STDMETHODIMP CFakeDOMElement::get_dataType(/* [out][retval] */ VARIANT *dataTypeName)
{
	return UnimplementedMethod("get_dataType");
}

STDMETHODIMP CFakeDOMElement::put_dataType(/* [in] */ BSTR dataTypeName)
{
	return UnimplementedMethod("put_dataType");
}

STDMETHODIMP CFakeDOMElement::get_xml(/* [out][retval] */ BSTR *xmlString)
{
	if(!xmlString)
		return E_POINTER;
	xmlNodePtr x = xmlCopyNode(m_element, 1);
	int rc = xmlDOMWrapReconcileNamespaces(NULL, x, 0);
	xmlBufferPtr buf = xmlBufferCreate();
	xmlNodeDump(buf, m_element->doc, x, 0, 0);
	xmlFreeNode(x);
	XStr::Put(buf->content, xmlString);
	xmlBufferFree(buf);
	return S_OK;
}

STDMETHODIMP CFakeDOMElement::transformNode(/* [in] */ IXMLDOMNode *stylesheet, /* [out][retval] */ BSTR *xmlString)
{
	return UnimplementedMethod("transformNode");
}

STDMETHODIMP CFakeDOMElement::selectNodes(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNodeList **resultList)
{
	return UnimplementedMethod("selectNodes");
}

STDMETHODIMP CFakeDOMElement::selectSingleNode(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNode **resultNode)
{
	return UnimplementedMethod("selectSingleNode");
}

STDMETHODIMP CFakeDOMElement::get_parsed(/* [out][retval] */ VARIANT_BOOL *isParsed)
{
	return UnimplementedMethod("get_parsed");
}

STDMETHODIMP CFakeDOMElement::get_namespaceURI(/* [out][retval] */ BSTR *namespaceURI)
{
	return UnimplementedMethod("get_namespaceURI");
}

STDMETHODIMP CFakeDOMElement::get_prefix(/* [out][retval] */ BSTR *prefixString)
{
	return UnimplementedMethod("get_prefix");
}

STDMETHODIMP CFakeDOMElement::get_baseName(/* [out][retval] */ BSTR *nameString)
{
	return UnimplementedMethod("get_baseName");
}

STDMETHODIMP CFakeDOMElement::transformNodeToObject(/* [in] */ IXMLDOMNode *stylesheet, /* [in] */ VARIANT outputObject)
{
	return UnimplementedMethod("transformNodeToObject");
}


// IXMLDOMElement
STDMETHODIMP CFakeDOMElement::get_tagName(/* [retval][out] */ BSTR *tagName)
{
	return UnimplementedMethod("get_tagName");
}

STDMETHODIMP CFakeDOMElement::getAttribute(/* [in] */ BSTR name, /* [retval][out] */ VARIANT *value)
{
	return UnimplementedMethod("getAttribute");
}

STDMETHODIMP CFakeDOMElement::setAttribute(/* [in] */ BSTR name, /* [in] */ VARIANT value)
{
	xmlSetProp(m_element, XStr(name), XStr(_bstr_t(value)));
	return S_OK;
}

STDMETHODIMP CFakeDOMElement::removeAttribute(/* [in] */ BSTR name)
{
	return UnimplementedMethod("removeAttribute");
}

STDMETHODIMP CFakeDOMElement::getAttributeNode(/* [in] */ BSTR name, /* [retval][out] */ IXMLDOMAttribute **attributeNode)
{
	return UnimplementedMethod("getAttributeNode");
}

STDMETHODIMP CFakeDOMElement::setAttributeNode(/* [in] */ IXMLDOMAttribute *DOMAttribute, /* [retval][out] */ IXMLDOMAttribute **attributeNode)
{
	return UnimplementedMethod("setAttributeNode");
}

STDMETHODIMP CFakeDOMElement::removeAttributeNode(/* [in] */ IXMLDOMAttribute *DOMAttribute, /* [retval][out] */ IXMLDOMAttribute **attributeNode)
{
	return UnimplementedMethod("removeAttributeNode");
}

STDMETHODIMP CFakeDOMElement::getElementsByTagName(/* [in] */ BSTR tagName, /* [retval][out] */ IXMLDOMNodeList **resultList)
{
	return UnimplementedMethod("getElementsByTagName");
}

STDMETHODIMP CFakeDOMElement::normalize(void)
{
	return UnimplementedMethod("normalize");
}



