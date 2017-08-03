// FakeDOMAttribute.cpp : Implementation of CFakeDOMAttribute

#include "stdafx.h"
#include "FakeDOMAttribute.h"


// CFakeDOMAttribute


void CFakeDOMAttribute::Init(xmlAttributePtr el)
{
	m_attr = el;
}

HRESULT CFakeDOMAttribute::UnimplementedMethod(const char * name)
{
	return ::ReportUnimplementedMethod("DOMAttribute", name);
}

// IXMLDOMNode
STDMETHODIMP CFakeDOMAttribute::get_nodeName(/* [retval][out] */ BSTR *name)
{
	return UnimplementedMethod("get_nodeName");
}

STDMETHODIMP CFakeDOMAttribute::get_nodeValue(/* [retval][out] */ VARIANT *value)
{
	return UnimplementedMethod("get_nodeValue");
}

STDMETHODIMP CFakeDOMAttribute::put_nodeValue(/* [in] */ VARIANT value)
{
	return UnimplementedMethod("put_nodeValue");
}

STDMETHODIMP CFakeDOMAttribute::get_nodeType(/* [retval][out] */ DOMNodeType *type)
{
	return UnimplementedMethod("get_nodeType");
}

STDMETHODIMP CFakeDOMAttribute::get_parentNode(/* [retval][out] */ IXMLDOMNode **parent)
{
	return UnimplementedMethod("get_parentNode");
}

STDMETHODIMP CFakeDOMAttribute::get_childNodes(/* [retval][out] */ IXMLDOMNodeList **childList)
{
	return UnimplementedMethod("get_childNodes");
}

STDMETHODIMP CFakeDOMAttribute::get_firstChild(/* [retval][out] */ IXMLDOMNode **firstChild)
{
	return UnimplementedMethod("get_firstChild");
}

STDMETHODIMP CFakeDOMAttribute::get_lastChild(/* [retval][out] */ IXMLDOMNode **lastChild)
{
	return UnimplementedMethod("get_lastChild");
}

STDMETHODIMP CFakeDOMAttribute::get_previousSibling(/* [retval][out] */ IXMLDOMNode **previousSibling)
{
	return UnimplementedMethod("get_previousSibling");
}

STDMETHODIMP CFakeDOMAttribute::get_nextSibling(/* [retval][out] */ IXMLDOMNode **nextSibling)
{
	return UnimplementedMethod("get_nextSibling");
}

STDMETHODIMP CFakeDOMAttribute::get_attributes(/* [retval][out] */ IXMLDOMNamedNodeMap **attributeMap)
{
	return UnimplementedMethod("get_attributes");
}

STDMETHODIMP CFakeDOMAttribute::insertBefore(/* [in] */ IXMLDOMNode *newChild, /* [in] */ VARIANT refChild, /* [retval][out] */ IXMLDOMNode **outNewChild)
{
	return UnimplementedMethod("insertBefore");
}

STDMETHODIMP CFakeDOMAttribute::replaceChild(/* [in] */ IXMLDOMNode *newChild, /* [in] */ IXMLDOMNode *oldChild, /* [retval][out] */ IXMLDOMNode **outOldChild)
{
	return UnimplementedMethod("replaceChild");
}

STDMETHODIMP CFakeDOMAttribute::removeChild(/* [in] */ IXMLDOMNode *childNode, /* [retval][out] */ IXMLDOMNode **oldChild)
{
	return UnimplementedMethod("removeChild");
}

STDMETHODIMP CFakeDOMAttribute::appendChild(/* [in] */ IXMLDOMNode *newChild, /* [retval][out] */ IXMLDOMNode **outNewChild)
{
	return UnimplementedMethod("appendChild");
}

STDMETHODIMP CFakeDOMAttribute::hasChildNodes(/* [retval][out] */ VARIANT_BOOL *hasChild)
{
	return UnimplementedMethod("hasChildNodes");
}

STDMETHODIMP CFakeDOMAttribute::get_ownerDocument(/* [retval][out] */ IXMLDOMDocument **XMLDOMDocument)
{
	return UnimplementedMethod("get_ownerDocument");
}

STDMETHODIMP CFakeDOMAttribute::cloneNode(/* [in] */ VARIANT_BOOL deep, /* [retval][out] */ IXMLDOMNode **cloneRoot)
{
	return UnimplementedMethod("cloneNode");
}

STDMETHODIMP CFakeDOMAttribute::get_nodeTypeString(/* [out][retval] */ BSTR *nodeType)
{
	return UnimplementedMethod("get_nodeTypeString");
}

STDMETHODIMP CFakeDOMAttribute::get_text(/* [out][retval] */ BSTR *text)
{
	if(!text)
		return E_POINTER;
	xmlChar* t = xmlNodeGetContent((xmlNodePtr)m_attr);
	XStr::Put(t, text);
	xmlFree(t);
	return S_OK;
}

STDMETHODIMP CFakeDOMAttribute::put_text(/* [in] */ BSTR text)
{
	return UnimplementedMethod("put_text");
}

STDMETHODIMP CFakeDOMAttribute::get_specified(/* [retval][out] */ VARIANT_BOOL *isSpecified)
{
	return UnimplementedMethod("get_specified");
}

STDMETHODIMP CFakeDOMAttribute::get_definition(/* [out][retval] */ IXMLDOMNode **definitionNode)
{
	return UnimplementedMethod("get_definition");
}

STDMETHODIMP CFakeDOMAttribute::get_nodeTypedValue(/* [out][retval] */ VARIANT *typedValue)
{
	return UnimplementedMethod("get_nodeTypedValue");
}

STDMETHODIMP CFakeDOMAttribute::put_nodeTypedValue(/* [in] */ VARIANT typedValue)
{
	return UnimplementedMethod("put_nodeTypedValue");
}

STDMETHODIMP CFakeDOMAttribute::get_dataType(/* [out][retval] */ VARIANT *dataTypeName)
{
	return UnimplementedMethod("get_dataType");
}

STDMETHODIMP CFakeDOMAttribute::put_dataType(/* [in] */ BSTR dataTypeName)
{
	return UnimplementedMethod("put_dataType");
}

STDMETHODIMP CFakeDOMAttribute::get_xml(/* [out][retval] */ BSTR *xmlString)
{
	return UnimplementedMethod("get_xml");
}

STDMETHODIMP CFakeDOMAttribute::transformNode(/* [in] */ IXMLDOMNode *stylesheet, /* [out][retval] */ BSTR *xmlString)
{
	return UnimplementedMethod("transformNode");
}

STDMETHODIMP CFakeDOMAttribute::selectNodes(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNodeList **resultList)
{
	return UnimplementedMethod("selectNodes");
}

STDMETHODIMP CFakeDOMAttribute::selectSingleNode(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNode **resultNode)
{
	return UnimplementedMethod("selectSingleNode");
}

STDMETHODIMP CFakeDOMAttribute::get_parsed(/* [out][retval] */ VARIANT_BOOL *isParsed)
{
	return UnimplementedMethod("get_parsed");
}

STDMETHODIMP CFakeDOMAttribute::get_namespaceURI(/* [out][retval] */ BSTR *namespaceURI)
{
	return UnimplementedMethod("get_namespaceURI");
}

STDMETHODIMP CFakeDOMAttribute::get_prefix(/* [out][retval] */ BSTR *prefixString)
{
	return UnimplementedMethod("get_prefix");
}

STDMETHODIMP CFakeDOMAttribute::get_baseName(/* [out][retval] */ BSTR *nameString)
{
	return UnimplementedMethod("get_baseName");
}

STDMETHODIMP CFakeDOMAttribute::transformNodeToObject(/* [in] */ IXMLDOMNode *stylesheet, /* [in] */ VARIANT outputObject)
{
	return UnimplementedMethod("transformNodeToObject");
}


// IXMLDOMAttribute
STDMETHODIMP CFakeDOMAttribute::get_name(/* [retval][out] */ BSTR *attributeName)
{
	return UnimplementedMethod("get_name");
}

STDMETHODIMP CFakeDOMAttribute::get_value(/* [retval][out] */ VARIANT *attributeValue)
{
	if(!attributeValue)
		return E_POINTER;
	CComBSTR text;
	xmlChar* t = xmlNodeGetContent((xmlNodePtr)m_attr);
	XStr::Put(t, &text);
	xmlFree(t);
	return CComVariant(text).Detach(attributeValue);
}

STDMETHODIMP CFakeDOMAttribute::put_value(/* [in] */ VARIANT attributeValue)
{
	return UnimplementedMethod("put_value");
}


