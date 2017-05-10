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
\brief      Header file for definitions restricted to Publish Lite.
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPDFLITERESTRICTED_H__
#define __A3DPDFLITERESTRICTED_H__


/*
Table of Contents for the Doxygen "Modules" page.
*/

/*!
\defgroup a3d_types_def Type Definitions
*/
/*!
\defgroup a3d_base_module Library Access Module
*/
/*!
\defgroup a3d_publishpdf_module PDF Module
*/
/*!
\defgroup a3d_publish_modelfile_loadexport Model File Load-Export Module
*/
/*!
\defgroup a3d_misctypes_def Model File Type Definitions
*/






/*!
\addtogroup a3d_types_def Type Definitions

This section describes the types defined by the \COMPONENT_A3D_API. 
These type definitions concern fundamental types such as int, float, and strings and 
types specific to the \COMPONENT_A3D_API entities such as 3D Annots or Images.
*/

/*!
\defgroup a3d_fundamental_types Fundamental Type Definitions
\ingroup a3d_types_def
\version 2.0

@{
*/
typedef signed char			A3DBool;		/*!< Standard boolean type. */
typedef void*				A3DPtr;			/*!< Void pointer. */
typedef void				A3DVoid;		/*!< Void. */

typedef signed char			A3DInt8;		/*!< Signed integer guaranteed to be 8-bit on all platforms. */
typedef unsigned char		A3DUns8;		/*!< Unsigned integer guaranteed to be 8-bit on all platforms. */

typedef short int			A3DInt16;		/*!< Signed integer guaranteed to be 16-bit on all platforms. */
typedef unsigned short int	A3DUns16;		/*!< Unsigned integer guaranteed to be 16-bit on all platforms. */

/* These are compiler specific */
#if POINTER_64_BITS
typedef int					A3DInt32;		/*!< Signed integer guaranteed to be 32-bit on all platforms. */
typedef unsigned int		A3DUns32;		/*!< Unsigned integer guaranteed to be 32-bit on all platforms. */
#else
typedef long int			A3DInt32;		/*!< Signed integer guaranteed to be 32-bit on all platforms. */
typedef unsigned long int	A3DUns32;		/*!< Unsigned integer guaranteed to be 32-bit on all platforms. */
#endif

typedef float				A3DFloat;		/*!< Standard C \c float type. */
typedef double				A3DDouble;		/*!< Standard C \c double type. */


/* Strings chars */

typedef char				A3DUTF8Char;	/*!< Standard UTF-8 \c char type. */

#if defined(WIN32) && !defined(WINCE)
#	include <windows.h>
#	include <tchar.h>
#else
# 	define HMODULE void*
#endif
#if defined _UNICODE || defined UNICODE
typedef wchar_t A3DUniChar;	/*!< Standard Unicode \c char type. */
#else
typedef char A3DUniChar;	/*!< Standard Non-Unicode \c char type. */
#endif

/*!
@} <!-- end of a3d_fundamental_types -->
*/

/*!
\addtogroup a3d_misctypes_def Model File Type Definitions
\ingroup a3d_types_def
This section describes the entity types used with the model file entity.
\version 2.0

@{
*/
typedef void A3DAsmModelFile;				/*!< Model file entity. */
typedef void A3DRWParamsPrcWriteHelper;		/*!< Reserved for Publish Advanced use. */

/*!
@} <!-- end of a3d_misctypes_def -->
*/





// A3DVector3dData should be part of publish.h but is shared in another header file for Advanced.
/*!
\brief Structure for a 3D vector
\ingroup a3d_publish_views
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dX;		/*!< x coordinate. */
	A3DDouble m_dY;		/*!< y coordinate. */
	A3DDouble m_dZ;		/*!< z coordinate. */
} A3DVector3dData;



/*!
\defgroup a3d_misc_module Miscellaneous Module
\brief Tools functions 

This module describes tools functions.
*/


#ifndef __A3D_UTF8UNICODE__

/*!
\defgroup a3d_UTF8_utilities UTF-8 Conversion Utilities
\ingroup a3d_misc_module
\brief Functions for converting between UTF-8 and UTF-16 strings on Windows.
@{
*/

/*!
\brief Converts UTF-8 encoded characters to UTF-16 strings on Windows.
\version 2.0

This function returns a UTF-16 string on Windows.

You must cast the string to a wide char pointer (\c wchar_t*) depending on the target computer's characteristics.

\warning On Linux, this API simply copies the input \c A3DUTF8Char* string into the output \c A3DUTF8Char* string.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
*/
A3D_API (A3DStatus, A3DMiscUTF8ToUnicode,(const A3DUTF8Char* pcInputBuffer,
														A3DUTF8Char acOutputBuffer[]));

/*!
\brief Converts UTF-16 strings to an array UTF-8 encoded characters on Windows.
\version 2.0

This function returns an array of UTF-8 encoded characters. 

The input buffer is cast and interpreted as a Unicode string (\c wchar_t*). 

\warning On Linux, this API simply copies the input \c A3DUTF8Char* string into the output \c A3DUTF8Char* string.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
*/
A3D_API (A3DStatus, A3DMiscUnicodeToUTF8,(const A3DUTF8Char* pcInputBuffer,
														A3DUTF8Char acOutputBuffer[]));

/*!
\brief Converts a UTF-8 string to a UTF-16 string on Windows.
\version 7.0

This function returns a UTF-16 string. 

\warning On Linux, this API simply returns A3D_ERROR.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
*/
A3D_API (A3DStatus, A3DMiscUTF8ToUTF16,(const A3DUTF8Char* pcInputBuffer,
														A3DUniChar acOutputBuffer[]));

/*!
\brief Converts a UTF-16 string to a UTF-8 string on Windows.
\version 7.0

This function returns a UTF-8 string.

\warning On Linux, this API simply returns A3D_ERROR.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
*/
A3D_API (A3DStatus, A3DMiscUTF16ToUTF8,(const A3DUniChar* pcInputBuffer,
														A3DUTF8Char acOutputBuffer[]));
/*!
@} <!-- end of a3d_UTF8_utilities -->
*/

#endif /* __A3D_UTF8UNICODE__ */

 /*!
 \defgroup a3d_error_debug_utilities Debug Utilities
\ingroup a3d_misc_module
\brief Functions to aid in debugging
@{
 */

/*!
\brief Returns the text description of an error code

\version 2.0
*/

A3D_API (A3DUTF8Char*, A3DMiscGetErrorMsg,(A3DStatus));


/*!
@} <!-- end of a3d_error_msg_utilities module -->
*/


/*!
\brief Deletes the entire \ref A3DAsmModelFile entity from memory
\ingroup a3d_publish_modelfile_loadexport
\par

Every entity under this model file is also deleted. This function is responsible for
freeing the whole memory reserved for ModelFile. After this call, access to 
the model file is no longer possible, and pointer must be set to NULL. 

\version 2.0

\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DAsmModelFileDelete,(A3DAsmModelFile* pModelFile));



#endif	/*	__A3DPDFLITERESTRICTED_H__ */
