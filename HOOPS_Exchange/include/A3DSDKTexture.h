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
\brief      Header for the Texture module, which is part of the Graphics module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCTEXTURE_H__
#define __A3DPRCTEXTURE_H__

/*!
\defgroup a3d_textures Textures
\ingroup a3d_graphics

\note <b>Please refer to classical graphical definitions when needed (OpenGL, DirectX, ...). Notions are quite
similar to the ones used inside common scene graphs</b>. This is true for lights, textures, line styles, patterns, cameras.

*/

#ifndef __A3D_TEXTURETRANSFORMATION__

/*!
\defgroup a3d_texturetransformation Texture Transformation
\ingroup a3dtexture_definition
*/

/*!
\ingroup a3d_texturetransformation
\brief  Texture Transformation Structure
\version 2.0

The \COMPONENT_A3D_LIBRARY supports 2D texture transformations.
It does not currently support 3D texture transformations.

The matrix is always an array of 16 doubles.\n
Rotation around x:  matrix[0], matrix[1], matrix[2]\n
Rotation around y:  matrix[4], matrix[5], matrix[6]\n
Rotation around z:  matrix[8], matrix[9], matrix[10]\n
Translation(x,y,z):  matrix[12], matrix[13], matrix[14]\n
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; should be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bTextureFlipS;		/*!< Inverts the S coordinate parameter. */
	A3DBool m_bTextureFlipT;		/*!< Inverts the T coordinate parameter. */
	A3DDouble m_dMatrix[16];		/*!< Coordinates of the matrix, which are described in the \b Detailed \b Description for this structure. */
	A3DBool m_bIs2D;				/*!< Indicates that matrix_transformation contains only 2D terms; always true in this version. */
} A3DGraphTextureTransformationData;

/*!
\brief Populates the \ref A3DGraphTextureTransformation structure
\ingroup a3d_texturetransformation
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphTextureTransformationGet,(const A3DGraphTextureTransformation* pTextureTransformation,
																 A3DGraphTextureTransformationData* pData));


/*!
\brief Creates an \ref A3DGraphTextureTransformation from an \ref A3DGraphTextureTransformationData structure.
\ingroup a3d_texturetransformation
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphTextureTransformationCreate,(const A3DGraphTextureTransformationData* pData,
																	 A3DGraphTextureTransformation** ppTextureTransformation));

#endif //__A3D_TEXTURETRANSFORMATION__

#ifndef __A3D_TEXTUREDEFINITION__

/*!
\defgroup a3dtexture_definition Texture Definition
\ingroup a3d_textures
\brief Defines a single texture set of parameters, which can be used in a \ref a3dtexture_application

The Texture definitions are stored in the global data.
\sa a3d_global_data_module.
*/

/*!
\defgroup a3d_texturemappingoperator Texture Mapping Operator
\ingroup a3dtexture_definition
@{
*/
/*!
\ingroup a3d_texturemappingoperator
\brief Reserved for future use
\version 2.0

Defines the operator to use for computing mapping coordinates.
The calculated mapping coordinates must be stored on an \ref A3DTess3D object
*/
typedef enum 
{
	kA3DTextureMappingOperatorUnknown,		/*!< Default value. */
	kA3DTextureMappingOperatorPlanar,		/*!< Unused. Reserved for future use. */
	kA3DTextureMappingOperatorCylindrical,	/*!< Unused. Reserved for future use. */
	kA3DTextureMappingOperatorSpherical,	/*!< Unused. Reserved for future use. */
	kA3DTextureMappingOperatorCubical		/*!< Unused. Reserved for future use. */
} A3DETextureMappingOperator;
/*!
@} <!-- end of module a3d_texturemappingoperator -->
*/

/*!
\defgroup a3d_texturemapping Texture Mapping Type
\ingroup a3dtexture_definition
@{
*/
/*!
\brief Defines how to get mapping coordinates.
\version 2.0

The \ref kA3DTextureMappingTypeStored enumeration 
is used with mapping coordinates stored on \ref A3DTess3D object.
Other values are reserved for future use.
*/
typedef enum 
{
	kA3DTextureMappingTypeUnknown,		/*!< Let the application choose. */
	kA3DTextureMappingTypeStored,			/*!< Mapping coordinates are stored. */
	kA3DTextureMappingTypeParametric,	/*!< Get the UV coordinate on the surface as mapping coordinates (reserved for future use). */
	kA3DTextureMappingTypeOperator		/*!< Use the defined \ref a3d_texturemappingoperator to calculate mapping coordinates (reserved for future use). */
} A3DETextureMappingType;
/*!
@} <!-- end of module a3d_texturemapping -->
*/

/*!
\defgroup a3d_texturefunction Texture Function
\ingroup a3dtexture_definition
@{
*/
/*!
\brief Defines how to paint a texture on the surface being rendered.
\version 2.0
*/
typedef enum 
{
	kA3DTextureFunctionUnknown,	/*!< Let the application choose. */
	kA3DTextureFunctionModulate,	/*!< Default value. Combines lighting with texturing. */
	kA3DTextureFunctionReplace,	/*!< Replace object color by texture color data. */
	kA3DTextureFunctionBlend,		/*!< Unused. Reserved for future use. */
	kA3DTextureFunctionDecal		/*!< Unused. Reserved for future use. */
} A3DETextureFunction;
/*!
@} <!-- end of module a3d_texturefunction -->
*/

/*!
\defgroup a3d_texturemappingattribute Texture Mapping Attribute
\ingroup a3dtexture_definition
\brief Defines texture-mapping methods
\version 2.0

\ref kA3DTextureMappingDiffuse single value is used as default attribute. 
\ref kA3DTextureMappingSphericalReflection and \ref kA3DTextureMappingCubicalReflection indicate that single values 
are used as environment mapping. 
Other values and combined values are reserved for future use.
@{*/
#define kA3DTextureMappingDiffuse						0x0001 /*!< Default value. */
#define kA3DTextureMappingBump							0x0002 /*!< Not yet supported. \todo To be documented. */
#define kA3DTextureMappingOpacity						0x0004 /*!< Not yet supported. \todo To be documented. */
#define kA3DTextureMappingSphericalReflection		0x0008 /*!< \todo To be documented. */
#define kA3DTextureMappingCubicalReflection			0x0010 /*!< \todo To be documented. */
#define kA3DTextureMappingRefraction					0x0020 /*!< Not yet supported. \todo To be documented. */
#define kA3DTextureMappingSpecular						0x0040 /*!< Not yet supported. \todo To be documented. */
#define kA3DTextureMappingAmbient						0x0080 /*!< Not yet supported. \todo To be documented. */
#define kA3DTextureMappingEmission						0x0100 /*!< Not yet supported. \todo To be documented. */
/*!
@} <!-- end of module a3d_texturemappingattribute -->
*/

/*!
\defgroup a3d_textureapplyingmode Texture Applying Mode
\ingroup a3dtexture_definition
\brief Defines special modes for applying textures.
\version 2.0

The values here define special modes for applying a texture. 
@{*/
#define kA3DTextureApplyingModeNone				0x0000 /*!< All states are disabled. */
#define kA3DTextureApplyingModeLighting		0x0001 /*!< Lighting Enabled. */
#define kA3DTextureApplyingModeAlphaTest		0x0002 /*!< Alpha Test Enabled. */
#define kA3DTextureApplyingModeVertexColor	0x0004 /*!< Use Vertex Color (combine a texture with one-color-per-vertex mode). */
/*!
@} <!-- end of module a3d_textureapplyingmode -->
*/

/*!
\defgroup a3d_textureblendparameter Texture Blend Parameter
\ingroup a3dtexture_definition
@{
*/
/*!
\brief Reserved for future use.
\version 2.0

Defines how to apply blending.
*/
typedef enum
{
	kA3DTextureBlendParameterUnknown,				/*!< Default value. */
	kA3DTextureBlendParameterZero,					/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterOne,						/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterSrcColor,				/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterOneMinusSrcColor,	/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterDstColor,				/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterOneMinusDstColor,	/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterSrcAlpha,				/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterOneMinusSrcAlpha,	/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterDstAlpha,				/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterOneMinusDstAlpha,	/*!< Unused. Reserved for future use. */
	kA3DTextureBlendParameterSrcAlphaSaturate		/*!< Unused. Reserved for future use. */
} A3DETextureBlendParameter;
/*!
@} <!-- end of module a3d_textureblendparameter -->
*/

/*!
\defgroup a3d_texture_mapping_attributes_components Texture Mapping Attribute Components
\ingroup a3dtexture_definition
@{
*/
/*!
\brief Defines which component(s) must be used to map a texture
\version 2.0
*/
#define kA3DTextureMappingComponentsRed		0x0001 /*!< \todo To be documented. */
#define kA3DTextureMappingComponentsGreen		0x0002 /*!< \todo To be documented. */
#define kA3DTextureMappingComponentsBlue		0x0004 /*!< \todo To be documented. */
#define kA3DTextureMappingComponentsRgb		0x0007 /*!< \todo To be documented. */
#define kA3DTextureMappingComponentsAlpha		0x0008 /*!< \todo To be documented. */
#define kA3DTextureMappingComponentsRgba		0x000f /*!< \todo To be documented. */
/*!
@} <!-- end of module a3d_texture_mapping_attributes_components -->
*/

/*!
\defgroup a3d_texturealphatest Texture Alpha Test
\ingroup a3dtexture_definition
@{
*/
/*!
\brief Reserved for future use
\version 2.0

Defines how to use Alpha test
*/
typedef enum 
{
	kA3DTextureAlphaTestUnknown,		/*!< Default value. */
	kA3DTextureAlphaTestNever,			/*!< Unused. Reserved for future use. */
	kA3DTextureAlphaTestLess,			/*!< Unused. Reserved for future use. */
	kA3DTextureAlphaTestEqual,			/*!< Unused. Reserved for future use. */
	kA3DTextureAlphaTestLequal,		/*!< Unused. Reserved for future use. */
	kA3DTextureAlphaTestGreater,		/*!< Unused. Reserved for future use. */
	kA3DTextureAlphaTestNotequal,		/*!< Unused. Reserved for future use. */
	kA3DTextureAlphaTestGequal,		/*!< Unused. Reserved for future use. */
	kA3DTextureAlphaTestAlways			/*!< Unused. Reserved for future use. */
} A3DETextureAlphaTest;
/*!
@} <!-- end of module a3d_texturealphatest -->
*/

/*!
\defgroup a3d_texturewrappingmode Texture Wrapping Mode
\ingroup a3dtexture_definition
@{
*/
/*!
\brief Defines repeating and clamping texture modes
\version 2.0
*/
typedef enum 
{
	kA3DTextureWrappingModeUnknown,			/*!< Let the application choose. */
	kA3DTextureWrappingModeRepeat,			/*!< Display repeated texture on the surface. */
	kA3DTextureWrappingModeClampToBorder,	/*!< Clamp texture to border. Display surface color over texture limits. */
	kA3DTextureWrappingModeClamp,				/*!< Unused. Reserved for future use. */
	kA3DTextureWrappingModeClampToEdge,		/*!< Unused. Reserved for future use. */
	kA3DTextureWrappingModeMirroredRepeat	/*!< Unused. Reserved for future use. */
} A3DETextureWrappingMode;
/*!
@} <!-- end of module a3d_texturewrappingmode --> 
*/

/*!
\brief TextureDefinitionData structure
\ingroup a3dtexture_definition
\version 2.0

The picture index refers to a picture in the picture array of the global data.

The \ref m_ucTextureDimension member represents the dimension of the image. 
Possible values are 1, 2 or 3 (1 and 3 are reserved for future use)

The \ref m_uiMappingAttributes member is a bitmask that defines the procedure 
to apply the texture (see \ref a3d_texturemappingattribute).
This information can be completed with additional information 
such as intensity and involved color/alpha components.

The \ref m_pdMappingAttributesIntensity member is an array of values that specify texture intensity values.
Each of these members can be set to 0 or to the number of procedures deduced from the texture mapping attributes.
If 0, intensity is set to 1. Otherwise, values should be in the range [0.0,1.0] 
and correspond to each non-zero bit of texture mapping attributes respectively.
Same for the texture mapping attributes components, for which the default value 
is \ref kA3DTextureMappingComponentsRgba (\ref a3d_texture_mapping_attributes_components).

Multiple procedures for texture application are reserved for future use.
Therefore \ref A3DGraphTextureDefinitionData::m_pdMappingAttributesIntensity and \ref A3DGraphTextureDefinitionData::m_pucMappingAttributesComponents can contain at most one element:

Here is some pseudocode that sets attribute values that are within the current limitation in texture mapping settings:
\code
myGraphTextureDefinition.m_uiMappingAttributes = kA3DTextureMappingDiffuse;

// For each bit of \ref m_uiMappingAttributes with a value of 1, intensity are 1.0 by default
myGraphTextureDefinition.m_uiMappingAttributesIntensitySize = 0;

// For each bit of \ref m_uiMappingAttributes with a value of 1, components are \ref kA3DTextureMappingComponentsRgba by default
myGraphTextureDefinition.m_uiMappingAttributesComponentsSize = 0;
\endcode
Or:\n
\code
myGraphTextureDefinition.m_uiMappingAttributes = kA3DTextureMappingDiffuse;
myGraphTextureDefinition.m_uiMappingAttributesIntensitySize = 1;
myGraphTextureDefinition.m_pdMappingAttributesIntensity[0] = 1.0;
myGraphTextureDefinition.m_uiMappingAttributesComponentsSize = 1;
myGraphTextureDefinition.m_pucMappingAttributesComponents[0] = kA3DTextureMappingComponentsRgba;
\endcode

For information on values for the \ref m_dAlphaTestReference member or the \ref m_dAlphaTestReference member, 
see \ref a3d_texturealphatest. The latter member is a threshold value for the alpha test, 
which is used in conjunction with the \ref m_dAlphaTestReference member. 

\sa \ref A3DGlobal
*/
typedef struct 
{
	A3DUns16 m_usStructSize;							/*!< Reserved; should be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiPictureIndex;							/*!< Picture index in global data \ref A3DGlobal. */
	A3DUns8 m_ucTextureDimension;						/*!< Dimension of the texture. */
	A3DETextureMappingType m_eMappingType;				/*!< Mapping type. */
	A3DETextureMappingOperator m_eMappingOperator;		/*!< Mapping operator. */
	A3DMiscCartesianTransformation* m_pOperatorTransfo;	/*!< Optional mapping transformation. */
	A3DUns32 m_uiMappingAttributes;						/*!< Defines a method to map a texture. See explanations above. \sa a3d_texturemappingattribute */
	A3DUns32 m_uiMappingAttributesIntensitySize;		/*!< Size of next array. */
	A3DDouble* m_pdMappingAttributesIntensity;			/*!< Intensities for attributes. */
	A3DUns32 m_uiMappingAttributesComponentsSize;		/*!< Size of next array. */
	A3DUns8* m_pucMappingAttributesComponents;			/*!< Components for attributes. */
	A3DETextureFunction m_eTextureFunction;				/*!< Defines how to paint a texture on the surface being rendered. \sa a3d_texturefunction */
	A3DDouble m_dRed;									/*!< Reserved for future use. Blend color component in the range [0.0,1.0]. */
	A3DDouble m_dGreen;									/*!< Reserved for future use. Blend color component in the range [0.0,1.0]. */
	A3DDouble m_dBlue;									/*!< Reserved for future use. Blend color component in the range [0.0,1.0]. */
	A3DDouble m_dAlpha;									/*!< Reserved for future use. Blend alpha component in the range [0.0,1.0]. */
	A3DETextureBlendParameter m_eBlend_src_RGB;			/*!< Reserved for future use. \sa a3d_textureblendparameter */
	A3DETextureBlendParameter m_eBlend_dst_RGB;			/*!< Reserved for future use. \sa a3d_textureblendparameter */
	A3DETextureBlendParameter m_eBlend_src_Alpha;		/*!< Reserved for future use. \sa a3d_textureblendparameter */
	A3DETextureBlendParameter m_eBlend_dst_Alpha;		/*!< Reserved for future use. \sa a3d_textureblendparameter */
	A3DUns8 m_ucTextureApplyingMode;					/*!< Defines special applying modes of a texture \ref a3d_textureapplyingmode. */
	A3DETextureAlphaTest m_eTextureAlphaTest;			/*!< Reserved for future use. Defines how to use Alpha test. \sa a3d_texturealphatest */
	A3DDouble m_dAlphaTestReference;					/*!< Threshold value for alpha test; used in conjunction with \ref m_eTextureAlphaTest. */
	A3DETextureWrappingMode m_eTextureWrappingModeS;	/*!< Repeating mode first direction. \sa a3d_texturewrappingmode */
	A3DETextureWrappingMode m_eTextureWrappingModeT;	/*!< Repeating mode second direction. \sa a3d_texturewrappingmode */
	A3DGraphTextureTransformation* m_pTextureTransfo;	/*!< Optional texture transformation. \sa a3d_texturetransformation */
} A3DGraphTextureDefinitionData;

/*!
\brief Populates the \ref A3DGraphTextureDefinitionData structure
\ingroup a3dtexture_definition
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphTextureDefinitionData,(const A3DUns32 uiIndexTextureDefinition,
																		 A3DGraphTextureDefinitionData* pData));

/*!
\brief Creates a Texture Definition from an \ref A3DGraphTextureDefinitionData structure in global data
\ingroup a3dtexture_definition
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphTextureDefinition,(const A3DGraphTextureDefinitionData* pData,
																		A3DUns32* puiIndexTextureDefinition));

#endif /*__A3D_TEXTUREDEFINITION__*/

#ifndef __A3D_TEXTUREAPPLICATION__
/*!
\defgroup a3dtexture_application Texture Application
\ingroup a3d_textures
\brief Defines a complete set of textures to apply

The texture applications are managed as materials in the global data.
\sa a3d_global_data_module, a3dtexture_definition
*/

/*!
\brief TextureApplicationData structure
\ingroup a3dtexture_application
\version 2.0

The UV Coordinates Index defines which UV coordinates to consider in an \ref A3DTess3DData structure.
The material index should correspond to a material stored in global data.
This material defines the basic material parameters of the texture.
The texture definition index must correspond to a texture definition stored in global data.

\sa a3dtexture_definition, a3d_global_data_module

*/
typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; should be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUns32	m_uiMaterialIndex;					/*!< Associated \ref A3DGraphMaterialData in global data (\ref A3DGlobalData) materials. */
	A3DUns32	m_uiTextureDefinitionIndex;			/*!< Texture definition index (\ref a3dtexture_definition). */
	A3DInt32	m_iUVCoordinatesIndex;				/*!< The set of UV coordinates to consider on the \ref A3DTess3DData. */
	A3DUns32 m_uiNextTextureApplicationIndex;		/*!< Index in global data materials of the optional next texture unit. \ref A3D_DEFAULT_MATERIAL_INDEX = no other texture. */
} A3DGraphTextureApplicationData;


/*!
\brief Populates the \ref A3DGraphTextureApplicationData structure
\ingroup a3dtexture_application
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphTextureApplicationData,(const A3DUns32 uiIndexTextureApplication,
																		  A3DGraphTextureApplicationData* pData));

/*!
\brief Creates a Texture Application from an \ref A3DGraphTextureApplicationData structure in global data
\ingroup a3dtexture_application
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphTextureApplication,(const A3DGraphTextureApplicationData* pData,
																		 A3DUns32* puiIndexTextureApplication));

#endif /*__A3D_TEXTUREAPPLICATION__*/


#endif /* __A3DPRCTEXTURE_H__*/
