// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED

#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit


#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <string>
#include <map>
#include <COMDEF.H>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

#include "XStr.h"

#include <MsXml6.h>
//#import <msxml6.dll> no_smart_pointers no_namespace named_guids raw_interfaces_only
// several constants stolen from msxml6.tlh
extern "C" const GUID __declspec(selectany) LIBID_MSXML2 =
{ 0xf5078f18,0xc551,0x11d3, { 0x89,0xb9,0x00,0x00,0xf8,0x1f,0xe2,0x21 } };
extern "C" const GUID __declspec(selectany) IID_IXMLDOMDocument3 =
{ 0x2933bf96,0x7b36,0x11d2, { 0xb2,0x0e,0x00,0xc0,0x4f,0x98,0x3e,0x60 } };

HRESULT ReportUnimplementedMethod(const char* cls, const char* method);




