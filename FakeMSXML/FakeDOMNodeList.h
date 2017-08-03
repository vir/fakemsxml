// FakeDOMNodeList.h : Declaration of the CFakeDOMNodeList

#pragma once
#include "resource.h"       // main symbols



#include "FakeMSXML_i.h"
#include <vector>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CFakeDOMNodeList

class ATL_NO_VTABLE CFakeDOMNodeList :
	public CComObjectRootEx<CComMultiThreadModel>,
//	public CComCoClass<CFakeDOMNodeList, &CLSID_FakeDOMNodeList>,
	public IDispatchImpl<IXMLDOMNodeList, &__uuidof(IXMLDOMNodeList), &LIBID_MSXML2, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	DECLARE_REGISTRY_RESOURCEID(IDR_FAKEDOMNODELIST)
	BEGIN_COM_MAP(CFakeDOMNodeList)
		COM_INTERFACE_ENTRY(IXMLDOMNodeList)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	CFakeDOMNodeList()
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

	void AddNode(IXMLDOMNode* node)
	{
		m_nodes.push_back(node);
	}
private:
	CComPtr<IUnknown> m_pUnkMarshaler;
	std::vector< CComPtr<IXMLDOMNode> > m_nodes;
public: // IXMLDOMNodeList
	STDMETHOD(get_item)(/* [in] */ long index, /* [retval][out] */ IXMLDOMNode **listItem)
	{
		if(!listItem)
			return E_POINTER;
		if(index < 0 || (unsigned long)index >= m_nodes.size())
			return E_INVALIDARG;
		return m_nodes[index].CopyTo(listItem);
	}
	STDMETHOD(get_length)(/* [retval][out] */ long *listLength)
	{
		if(listLength)
			*listLength = m_nodes.size();
		return m_nodes.empty() ? S_FALSE : S_OK;
	}
	STDMETHOD(nextNode)(/* [retval][out] */ IXMLDOMNode **nextItem)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(reset)(void)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(get__newEnum)(/* [out][retval] */ IUnknown **ppUnk)
	{
		return E_NOTIMPL;
	}



};

//OBJECT_ENTRY_AUTO(__uuidof(FakeDOMNodeList), CFakeDOMNodeList)
