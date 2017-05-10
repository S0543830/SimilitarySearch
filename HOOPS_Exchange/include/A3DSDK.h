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
\brief      Top-level header file of the \COMPONENT_A3D_API
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCSDK_H__
#define __A3DPRCSDK_H__

#ifdef TF_A3DLIBS
#include "A3DSDKInitializeInternalFunctionsPointer.h"
#endif

#ifndef A3D_API
#ifdef __cplusplus
#	define A3D_API(returnvalue,name,params) extern "C" returnvalue name params
#	define A3D_API_CALL extern "C"
#else
#	define A3D_API 
#	define A3D_API_CALL 
#endif
#endif


#ifndef A3D_NEWAPI
#ifdef WIN32
	#define A3D_NEWAPI __declspec(dllexport) 
#else
	#define A3D_NEWAPI 
#endif
#endif

/*!
\brief DLL Major Version

Major.Minor = 4.0 = Version of the DLL that this header file corresponds to.
*/
#define A3D_DLL_MAJORVERSION 9
/*!
\brief DLL Minor Version

\sa A3D_DLL_MAJORVERSION
*/
#define A3D_DLL_MINORVERSION 1

/*!
\brief Official SDK name
*/
#define A3D_DLL_NAME "A3DLIB"

/*!
\brief Copyright SDK
*/

#define A3D_DLL_COPYRIGHT "Copyright (c) 2015 by Tech Soft 3D, LLC. All rights reserved."



#ifndef FALSE
/*!
\brief Boolean standard false value.
*/
#	define FALSE	0 
#endif

#ifndef TRUE
/*!
\brief Boolean standard true value.
*/
#	define TRUE		1 
#endif

/*!
\brief Maximum length for character string.
*/
#define A3D_MAX_BUFFER	2048


#endif	/*	__A3DPRCSDK_H__ */
