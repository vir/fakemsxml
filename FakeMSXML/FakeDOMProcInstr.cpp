// FakeDOMProcInstr.cpp : Implementation of CFakeDOMProcInstr

#include "stdafx.h"
#include "FakeDOMProcInstr.h"


// CFakeDOMProcInstr

// IXMLDOMNode
STDMETHODIMP CFakeDOMProcInstr::get_nodeName(/* [retval][out] */ BSTR *name)
{
	return UnimplementedMethod("get_nodeName");
}

STDMETHODIMP CFakeDOMProcInstr::get_nodeValue(/* [retval][out] */ VARIANT *value)
{
	return UnimplementedMethod("get_nodeValue");
}

STDMETHODIMP CFakeDOMProcInstr::put_nodeValue(/* [in] */ VARIANT value)
{
	return UnimplementedMethod("put_nodeValue");
}

STDMETHODIMP CFakeDOMProcInstr::get_nodeType(/* [retval][out] */ DOMNodeType *type)
{
	return UnimplementedMethod("get_nodeType");
}

STDMETHODIMP CFakeDOMProcInstr::get_parentNode(/* [retval][out] */ IXMLDOMNode **parent)
{
	return UnimplementedMethod("get_parentNode");
}

STDMETHODIMP CFakeDOMProcInstr::get_childNodes(/* [retval][out] */ IXMLDOMNodeList **childList)
{
	return UnimplementedMethod("get_childNodes");
}

STDMETHODIMP CFakeDOMProcInstr::get_firstChild(/* [retval][out] */ IXMLDOMNode **firstChild)
{
	return UnimplementedMethod("get_firstChild");
}

STDMETHODIMP CFakeDOMProcInstr::get_lastChild(/* [retval][out] */ IXMLDOMNode **lastChild)
{
	return UnimplementedMethod("get_lastChild");
}

STDMETHODIMP CFakeDOMProcInstr::get_previousSibling(/* [retval][out] */ IXMLDOMNode **previousSibling)
{
	return UnimplementedMethod("get_previousSibling");
}

STDMETHODIMP CFakeDOMProcInstr::get_nextSibling(/* [retval][out] */ IXMLDOMNode **nextSibling)
{
	return UnimplementedMethod("get_nextSibling");
}

STDMETHODIMP CFakeDOMProcInstr::get_attributes(/* [retval][out] */ IXMLDOMNamedNodeMap **attributeMap)
{
	return UnimplementedMethod("get_attributes");
}

STDMETHODIMP CFakeDOMProcInstr::insertBefore(/* [in] */ IXMLDOMNode *newChild, /* [in] */ VARIANT refChild, /* [retval][out] */ IXMLDOMNode **outNewChild)
{
	return UnimplementedMethod("insertBefore");
}

STDMETHODIMP CFakeDOMProcInstr::replaceChild(/* [in] */ IXMLDOMNode *newChild, /* [in] */ IXMLDOMNode *oldChild, /* [retval][out] */ IXMLDOMNode **outOldChild)
{
	return UnimplementedMethod("replaceChild");
}

STDMETHODIMP CFakeDOMProcInstr::removeChild(/* [in] */ IXMLDOMNode *childNode, /* [retval][out] */ IXMLDOMNode **oldChild)
{
	return UnimplementedMethod("removeChild");
}

STDMETHODIMP CFakeDOMProcInstr::appendChild(/* [in] */ IXMLDOMNode *newChild, /* [retval][out] */ IXMLDOMNode **outNewChild)
{
	return UnimplementedMethod("appendChild");
}

STDMETHODIMP CFakeDOMProcInstr::hasChildNodes(/* [retval][out] */ VARIANT_BOOL *hasChild)
{
	return UnimplementedMethod("hasChildNodes");
}

STDMETHODIMP CFakeDOMProcInstr::get_ownerDocument(/* [retval][out] */ IXMLDOMDocument **XMLDOMDocument)
{
	return UnimplementedMethod("get_ownerDocument");
}

STDMETHODIMP CFakeDOMProcInstr::cloneNode(/* [in] */ VARIANT_BOOL deep, /* [retval][out] */ IXMLDOMNode **cloneRoot)
{
	return UnimplementedMethod("cloneNode");
}

STDMETHODIMP CFakeDOMProcInstr::get_nodeTypeString(/* [out][retval] */ BSTR *nodeType)
{
	return UnimplementedMethod("get_nodeTypeString");
}

STDMETHODIMP CFakeDOMProcInstr::get_text(/* [out][retval] */ BSTR *text)
{
	return UnimplementedMethod("get_text");
}

STDMETHODIMP CFakeDOMProcInstr::put_text(/* [in] */ BSTR text)
{
	return UnimplementedMethod("put_text");
}

STDMETHODIMP CFakeDOMProcInstr::get_specified(/* [retval][out] */ VARIANT_BOOL *isSpecified)
{
	return UnimplementedMethod("get_specified");
}

STDMETHODIMP CFakeDOMProcInstr::get_definition(/* [out][retval] */ IXMLDOMNode **definitionNode)
{
	return UnimplementedMethod("get_definition");
}

STDMETHODIMP CFakeDOMProcInstr::get_nodeTypedValue(/* [out][retval] */ VARIANT *typedValue)
{
	return UnimplementedMethod("get_nodeTypedValue");
}

STDMETHODIMP CFakeDOMProcInstr::put_nodeTypedValue(/* [in] */ VARIANT typedValue)
{
	return UnimplementedMethod("put_nodeTypedValue");
}

STDMETHODIMP CFakeDOMProcInstr::get_dataType(/* [out][retval] */ VARIANT *dataTypeName)
{
	return UnimplementedMethod("get_dataType");
}

STDMETHODIMP CFakeDOMProcInstr::put_dataType(/* [in] */ BSTR dataTypeName)
{
	return UnimplementedMethod("put_dataType");
}

STDMETHODIMP CFakeDOMProcInstr::get_xml(/* [out][retval] */ BSTR *xmlString)
{
	return UnimplementedMethod("get_xml");
}

STDMETHODIMP CFakeDOMProcInstr::transformNode(/* [in] */ IXMLDOMNode *stylesheet, /* [out][retval] */ BSTR *xmlString)
{
	return UnimplementedMethod("transformNode");
}

STDMETHODIMP CFakeDOMProcInstr::selectNodes(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNodeList **resultList)
{
	return UnimplementedMethod("selectNodes");
}

STDMETHODIMP CFakeDOMProcInstr::selectSingleNode(/* [in] */ BSTR queryString, /* [out][retval] */ IXMLDOMNode **resultNode)
{
	return UnimplementedMethod("selectSingleNode");
}

STDMETHODIMP CFakeDOMProcInstr::get_parsed(/* [out][retval] */ VARIANT_BOOL *isParsed)
{
	return UnimplementedMethod("get_parsed");
}

STDMETHODIMP CFakeDOMProcInstr::get_namespaceURI(/* [out][retval] */ BSTR *namespaceURI)
{
	return UnimplementedMethod("get_namespaceURI");
}

STDMETHODIMP CFakeDOMProcInstr::get_prefix(/* [out][retval] */ BSTR *prefixString)
{
	return UnimplementedMethod("get_prefix");
}

STDMETHODIMP CFakeDOMProcInstr::get_baseName(/* [out][retval] */ BSTR *nameString)
{
	return UnimplementedMethod("get_baseName");
}

STDMETHODIMP CFakeDOMProcInstr::transformNodeToObject(/* [in] */ IXMLDOMNode *stylesheet, /* [in] */ VARIANT outputObject)
{
	return UnimplementedMethod("transformNodeToObject");
}


// IXMLDOMProcessingInstruction
STDMETHODIMP CFakeDOMProcInstr::get_target(/* [retval][out] */ BSTR *name)
{
	return UnimplementedMethod("get_target");
}

STDMETHODIMP CFakeDOMProcInstr::get_data(/* [retval][out] */ BSTR *value)
{
	return UnimplementedMethod("get_data");
}

STDMETHODIMP CFakeDOMProcInstr::put_data(/* [in] */ BSTR value)
{
	return UnimplementedMethod("put_data");
}

