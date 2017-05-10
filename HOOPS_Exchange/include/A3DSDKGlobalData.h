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
\brief      Header file for global data
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCGLOBALDATA_H__
#define __A3DPRCGLOBALDATA_H__

/*!
\defgroup a3d_global_data_module Global Data Module
\ingroup a3d_entitiesdata_module
\brief Accesses global definitions used by all PRC entities

This module defines the data for commonly used attributes, such as colors, textures, materials, and patterns.
Global data is stored in the session's global memory, separate from the \ref A3DAsmModelFile.
Global data can be accessed independently from \ref A3DAsmModelFile. 
Therefore, you can access colors, textures, materials, and patterns that may or may not be used 
by the entities that are used in an \ref A3DAsmModelFile. 
All these global arrays are filled when reading the PRC physical file and optimized to save place. 
For instance, if two entities uses the same color definition (same triplet RGB), only one color will be stored in the array. 
*/

#ifndef __GLOBALDATA__

/*!
\brief Gets the global object \ref A3DGlobal 
\ingroup a3d_global_data_module
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetPointer,(A3DGlobal** ppGlobal));

/*!
\brief Global data structure
\ingroup a3d_global_data_module
\version 2.0

This structure holds the sizes of stored graphical parameters for the current \ref A3DAsmModelFile entity. 
Graphical parameters are stored as arrays of following data:
\li RGB colors: the size is \ref m_uiColorsSize; to access the content data, 
use \ref A3DGlobalGetGraphRgbColorData; to create, use \ref A3DGlobalInsertGraphRgbColor; 
\li Pictures: the size is \ref m_uiPicturesSize; to access the content data, 
use \ref A3DGlobalGetGraphPictureData; to create, use  \ref A3DGlobalInsertGraphPicture
\li Texture Definitions: the size is \ref m_uiTextureDefinitionsSize; To access the content data, 
use \ref A3DGlobalGetGraphTextureDefinitionData; to create, use  \ref A3DGlobalInsertGraphTextureDefinition
\li Materials: material is a generic type for two kind of data: \ref A3DGraphMaterialData 
and \ref A3DGraphTextureApplicationData. The size of the array is \ref m_uiMaterialsSize. 
To get the type of the data, use \ref A3DGlobalIsMaterialTexture. To access the content data, 
use \ref A3DGlobalGetGraphMaterialData or \ref A3DGlobalGetGraphTextureApplicationData; to create, use \ref A3DGlobalInsertGraphMaterial or \ref A3DGlobalInsertGraphTextureApplication
\li Line Patterns: the size is \ref m_uiLinePatternsSize; To access the content data, 
use \ref A3DGlobalGetGraphLinePatternData; to create, use \ref A3DGlobalInsertGraphLinePattern
\li Display Styles: The size is \ref m_uiStylesSize; To access the content data, 
use \ref A3DGlobalGetGraphStyleData; to create, use \ref A3DGlobalInsertGraphStyle
\li Fill Patterns: This is a generic type for several kind of data. 
The size of the array is \ref m_uiFillPatternsSize. \n  
To determine the type of the data, use the \ref A3DGlobalGetFillPatternType function. \n
To access the content data, use the dedicated function for the pattern. The form for such functions is <code>A3DGlobalGetGraph<i>XXX</i>PatternData</code>,
where <code><i>XXX</i></code> is replaced with type of pattern. \n
To set the content data, use the dedicated function for the pattern. The form for such functions is <code>A3DGlobalInsertGraph<i>XXX</i>Pattern</code>. 

\sa a3d_graphics
\warning The access functions <code>A3DGlobalGetGraph<i>XXX</i>Data</code> and <code>A3DGlobalInsertGraph<i>XXX</i></code> are used with indexes instead of pointers.
\note Call the <code>A3DGlobalGet<i>XXX</i>Data</code> function with default index to free the data structure.
*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiColorsSize;					/*!< Number of RGB colors. */
	A3DUns32 m_uiPicturesSize;				/*!< Number of Pictures. */
	A3DUns32 m_uiTextureDefinitionsSize;	/*!< Number of Texture definitions. */
	A3DUns32 m_uiMaterialsSize;				/*!< Number of Materials. */
	A3DUns32 m_uiLinePatternsSize;			/*!< Number of LinePatterns. */
	A3DUns32 m_uiStylesSize;					/*!< Number of Styles. */
	A3DUns32 m_uiFillPatternsSize;			/*!< Number of FillPatterns. */
} A3DGlobalData;

/*!
\brief Populates the \ref A3DGlobalData structure
\ingroup a3d_global_data_module
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGet,(	const A3DGlobal* pGlobal,
												A3DGlobalData* pData));


/*!
\brief Determines whether the data at the index uiIndexMaterial in the global array of materials 
is an \ref A3DGraphTextureApplication or an \ref A3DGraphMaterialData
\ingroup a3d_global_data_module
\version 2.0

\sa a3dtexture_application
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalIsMaterialTexture,(const A3DUns32 uiIndexMaterial,
																A3DBool* pbIsTexture));


/*!
\ingroup a3d_global_data_module
\version 2.0
\brief Gives the FillPattern type of the uiIndexPattern index in the global array of fill patterns. 

A FillPattern type can be one of the following types:
\li \ref kA3DTypeGraphDottingPattern
\li \ref kA3DTypeGraphHatchingPattern
\li \ref kA3DTypeGraphSolidPattern
\li \ref kA3DTypeGraphVPicturePattern

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetFillPatternType,(const A3DUns32 uiIndexPattern,
																A3DEEntityType* pePatternType));

#endif	/*	__GLOBALDATA__ */



#endif	/*	__A3DPRCGLOBALDATA_H__ */
