// FakeXMLNode.cpp : Implementation of CFakeXMLNode

#include "stdafx.h"
#include "FakeXMLNode.h"

#include "FakeDOMElement.h"
#include "FakeDOMProcInstr.h"
#include "FakeDOMAttribute.h"

// CFakeXMLNode

void BuildNodeCOMObject(xmlNodePtr node, IXMLDOMNode ** ppInt)
{
	switch(node->type) {
		case XML_ELEMENT_NODE:
		{
			CComObject<CFakeDOMElement>* obj;
			CComObject<CFakeDOMElement>::CreateInstance(&obj);
			obj->AddRef();
			obj->Init(node);
			*ppInt = obj;
		}
		break;
		case XML_ATTRIBUTE_NODE:
		{
			CComObject<CFakeDOMAttribute>* obj;
			CComObject<CFakeDOMAttribute>::CreateInstance(&obj);
			obj->AddRef();
			obj->Init(reinterpret_cast<xmlAttributePtr>(node));
			*ppInt = obj;
		}
		break;
		case XML_PI_NODE:
		{
			CComObject<CFakeDOMProcInstr>* obj;
			CComObject<CFakeDOMProcInstr>::CreateInstance(&obj);
			obj->AddRef();
			obj->Init(node);
			*ppInt = obj;
		}
		break;
	default:
		break;
	}
}

xmlNodePtr GetInternalNode(IUnknown* obj)
{
	CComQIPtr<IFakeXMLInternalNode> intnode(obj);
	if(!intnode)
		return nullptr;
	xmlNodePtr r = nullptr;
	intnode->get_InternalNode((void**)&r);
	return r;
}
