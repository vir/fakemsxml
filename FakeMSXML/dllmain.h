// dllmain.h : Declaration of module class.

class CFakeMSXMLModule : public ATL::CAtlDllModuleT< CFakeMSXMLModule >
{
public :
	DECLARE_LIBID(LIBID_FakeMSXMLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FAKEMSXML, "{0114E170-0508-43AD-BBD6-77D25A472621}")
};

extern class CFakeMSXMLModule _AtlModule;
