/***********************************************************************************************************************
*
* Copyright (c) 2016 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to Tech Soft 3D, LLC., and considered a trade secret
* as defined under civil and criminal statutes. Tech Soft 3D shall pursue its civil and criminal remedies in the event
* of unauthorized use or misappropriation of its trade secrets. Use of this information by anyone other than authorized 
* employees of Tech Soft 3D, LLC. is granted only under a written non-disclosure agreement, expressly prescribing the 
* scope and manner of such use.
*
***********************************************************************************************************************/

/*!
\file
\brief      Header file for the error codes module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.

As a general rule, every negative value for return codes <b>must be handled as an
error</b>, and not simply passed by. When possible, a brief explanation on every 
case has been provided. 

*/

#include <string.h>
#include <stdio.h>

#if defined INITIALIZE_A3D_API || defined INITIALIZE_A3D_API_STATIC

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifdef INITIALIZE_A3D_API_STATIC
#define PF_TYPE static
#else
#define PF_TYPE
#endif

#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif

#ifndef A3D_API
#define A3D_API(returntype,name,params)\
	typedef returntype (*PF##name) params;\
	PF_TYPE PF##name name = NULL

#include <A3DSDKAllIncludes.h>

// all Exchange headers available if Exchange or Advanced
// just a restricted set if Lite
#ifdef HOOPS_PRODUCT_PUBLISH_LITE 
#undef __A3DPDFERRORCODES_H__
#undef __A3DPDFLITERESTRICTED_H__
#undef __A3DPDFBASE_H__
#undef __A3DSDKLICENSE_H__
#undef __A3DPRCREADWRITE_H__
#else 
#undef __A3DPRCTYPES_H__
#undef __A3DPRCERRORCODES_H__
#undef __A3DPRCBASE_H__
#undef __A3DPRCROOTENTITIES_H__
#undef __A3DPRCGEOMETRY_H__
#undef __A3DPRCMISC_H__
#undef __A3DPRCGEOMETRYCRV_H__
#undef __A3DPRCGEOMETRYSRF_H__
#undef __A3DPRCTOPOLOGY_H__
#undef __A3DPRCREPITEMS_H__
#undef __A3DPRCTESSELLATION_H__
#undef __A3DPRCGRAPHICS_H__
#undef __A3DPRCMARKUP_H__
#undef __A3DPRCSTRUCTURE_H__
#undef __A3DSDKFEATURE_H__
#undef __A3DPRCTOOLS_H__
#undef __A3DPRCREADWRITE_H__
#undef __A3DPRCGLOBALDATA_H__
#undef __A3DPRCTEXTURE_H__
#undef __A3DPRCDRAWMODELFILE_H__
#undef __A3DPRCMATH_H__
#undef __A3DPRCINTERNALPROTECTION_H__
#undef __A3DSDKLICENSE_H__
#undef __A3DPRCMARKUPDEFINITION__
#undef __A3DPRCMARKUPLEADERDEFINITION__
#undef __A3D_MARKUPTEXTPOSITION__
#undef __A3D_MARKUPTEXT__
#undef __A3DPRCMarkupText_H__
#undef __A3D_MARKUPCOORDINATE__
#undef __A3D_MARKUPRICHTEXT__
#undef __A3DPRCMARKUPSYMBOL_H__
#undef __A3D_MARKUPROUGHNESS__
#undef __A3D_MARKUPBALLOON__
#undef __A3D_MARKUPFASTENER__
#undef __A3D_MARKUPLOCATOR__
#undef __A3D_MARKUPMEASUREMENTPOINT__
#undef __A3DPRCMARKUPDIMENSION_H__
#undef __A3DPRCMARKUPDEFINITIONDATA__
#undef __A3DPRCMarkupDimension_H__
#undef __A3DPRCDIMENSIONVALUE_H__
#undef __A3DPRCDIMENSIONLINE_H__
#undef __A3DPRCDIMENSIONEXTLINE_H__
#undef __A3D_MARKUPPOSITIONDATA__
#undef __A3D_MARKUPLEADERDATA__
#undef __A3D_MARKUPTEXTPROPERTIESDATA__
#undef __A3DPRCMARKUPTOLERANCE_H__
#undef __A3D_MARKUPDATUMN__
#undef __A3D_MARKUPGDT__
#undef __A3D_MARKUPWELDING__
#undef __A3DPRCMarkupWelding_H__
#undef __A3DSDKADVANCEDTOOLS_H__
#undef __A3DPRCDRAWING_H__
#endif

// only for Publish products
#if defined HOOPS_PRODUCT_PUBLISH_LITE || defined HOOPS_PRODUCT_PUBLISH_ADVANCED || defined HOOPS_PRODUCT_PUBLISHPLUSEXCHANGE
#undef __A3DPDFPUBLISHSDK_H__
#endif

#undef A3D_API
#endif // A3D_API


//////////////////////////////////////////////////////////////////////////
//
//	Loading function 
//
//////////////////////////////////////////////////////////////////////////

static void A3DSDKFunctionPointersInitialize(HMODULE hModule) 
{
#ifdef WIN32
#ifndef A3D_API
#define A3D_API(returntype,name,params) \
	name = (PF##name)GetProcAddress(hModule,#name)

#include <A3DSDKAllIncludes.h>

#undef A3D_API
#endif // A3D_API
#else // WIN32
#ifndef A3D_API
#define A3D_API(returntype,name,params) \
	name = (PF##name)dlsym(hModule,#name)

#include <A3DSDKAllIncludes.h>
#undef A3D_API
#endif // A3D_API



#endif // WIN32
	A3DSDKInitializeInternalPointer(hModule);
}

#ifndef _MAX_PATH
#define _MAX_PATH 1000
#endif
//////////////////////////////////////////////////////////////////////////
//
//	Windows specific to find address of corresponding DLL
//	
static HMODULE st_A3DSDKLibrary_hModule = NULL;

#ifdef WIN32
// pSDKDirectory: SDK UTF8 path terminated with backslash
static bool A3DSDKLoadLibrary(const char *pSDKDirectory = NULL)
{
	wchar_t sSDKPath[_MAX_PATH];
	sSDKPath[0] = 0;
	if(pSDKDirectory != NULL)
	{
		size_t iLen = MultiByteToWideChar(CP_UTF8, 0, pSDKDirectory, int(strlen(pSDKDirectory)), sSDKPath, sizeof(sSDKPath));
		sSDKPath[iLen] = 0;
		if (iLen > 1 && sSDKPath[iLen-1] != L'\\')
		{
			wcsncat_s(sSDKPath, L"\\", _MAX_PATH);
		}
	}

	wcsncat_s(sSDKPath, L"A3DLIBS.dll", _MAX_PATH);
	st_A3DSDKLibrary_hModule = LoadLibraryExW(sSDKPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (!st_A3DSDKLibrary_hModule)
	{
		return false;
	}

	A3DSDKFunctionPointersInitialize(st_A3DSDKLibrary_hModule);

	return true;
}

// pSDKDirectory: SDK UNICODE path terminated with backslash
static bool A3DSDKLoadLibrary(const wchar_t *pSDKDirectory)
{
	wchar_t sSDKPath[_MAX_PATH];
	sSDKPath[0] = 0;
	if(pSDKDirectory != NULL)
	{
		wcsncpy_s(sSDKPath, pSDKDirectory, _MAX_PATH);

		size_t iLen = wcslen(sSDKPath);
		if (iLen > 1 && sSDKPath[iLen-1] != L'\\')
		{
			wcsncat_s(sSDKPath, L"\\", _MAX_PATH);
		}
	}

	wcsncat_s(sSDKPath, L"A3DLIBS.dll", _MAX_PATH);
	st_A3DSDKLibrary_hModule = LoadLibraryExW(sSDKPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (!st_A3DSDKLibrary_hModule)
	{
		return false;
	}

	A3DSDKFunctionPointersInitialize(st_A3DSDKLibrary_hModule);

	return true;
}
#else // WIN32

// pSDKDirectory: SDK path terminated with backslash
static bool A3DSDKLoadLibrary(const A3DUTF8Char *pSDKDirectory = NULL) 
{
	A3DUTF8Char sSDKPath[_MAX_PATH];
	sSDKPath[0] = 0;
	if (pSDKDirectory != NULL)
	{
		strncpy(sSDKPath, pSDKDirectory, _MAX_PATH);
		size_t iLen = strlen(sSDKPath);
		if (iLen > 1 && sSDKPath[iLen-1] != '/')
			strncat(sSDKPath, "/", _MAX_PATH);
	}
#ifdef __APPLE__
	strncat(sSDKPath,"libA3DLIBS.dylib", _MAX_PATH);
#else // Apple
	strncat(sSDKPath,"libA3DLIBS.so", _MAX_PATH);
#endif	//
	st_A3DSDKLibrary_hModule = dlopen(sSDKPath, RTLD_LAZY);

	if (!st_A3DSDKLibrary_hModule)
	{
		printf("ERROR: %s\n", dlerror());
		return false;
	}

	A3DSDKFunctionPointersInitialize(st_A3DSDKLibrary_hModule);

	return true;
}
#endif // WIN32

static void A3DSDKUnloadLibrary() 
{
	if (st_A3DSDKLibrary_hModule)
	{
#ifdef WIN32
		FreeLibrary(st_A3DSDKLibrary_hModule);
		st_A3DSDKLibrary_hModule = NULL;
#else
		dlclose(st_A3DSDKLibrary_hModule);
#endif // WIN32
	}
}


#ifndef INITIALIZE_A3D_API_STATIC
#include <A3DSDKInternalConvert.hxx>
#endif

#else // INITIALIZE_A3D_API

#define A3D_API(returntype,name,params)\
	typedef returntype (*PF##name) params;\
	extern PF##name name


#include <A3DSDKAllIncludes.h>

#endif // INITIALIZE_A3D_API
