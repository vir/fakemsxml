// stdafx.cpp : source file that includes just the standard includes
// FakeMSXML.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

HRESULT ReportUnimplementedMethod(const char * cls, const char * method)
{
	std::string msg(cls);
	msg += "::";
	msg += method;
	::MessageBoxA(NULL, msg.c_str(), "Unimplemented method", MB_OK| MB_ICONWARNING|MB_TASKMODAL|MB_SYSTEMMODAL);
	return E_NOTIMPL;
}

