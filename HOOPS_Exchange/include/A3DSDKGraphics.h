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
\brief      Header file for the graphics module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCGRAPHICS_H__
#define __A3DPRCGRAPHICS_H__

#ifndef __A3DPRCGEOMETRY_H__
#error A3DSDKGeometry.h must be included before current file
#endif

#ifndef __A3DPRCTESSELLATION_H__
#error A3DSDKTessellation.h must be included before current file
#endif

/*!
\defgroup a3d_graphics_module Graphics Module
\ingroup a3d_entitiesdata_module
\brief Creates and accesses scene display attributes (such as camera and lighting) 
	and common graphic attributes (such as textures, patterns and RGB colors)
	
\note The conventions described here are similar to the common scene graphics conventions described for 
other 3D standards such as OpenGL and DirectX. This is true for lights, textures, linestyles, patterns, cameras.
*/


#ifndef __A3D_GRAPHIC__
/*!
\defgroup a3d_graphics Graphics
\ingroup a3d_graphics_module
Graphics data exists only on entities that have the base type \ref A3DRootBaseWithGraphics. 

Graphics data is stored as a set of arrays in the global object \ref A3DGlobalData.  
Graphics data includes the following attributes:
\li Display style attributes such as transparency and width (see \ref a3d_style)
\li Graphics attributes such as patterns, RGB color, and graphics materials 
	(\ref A3DGraphVPicturePatternData or \ref A3DGraphLinePatternData, 
	\ref A3DGraphRgbColorData, \ref A3DGraphMaterialData or \ref A3DGraphTextureApplicationData)

To process a graphical attribute for an entity, consider whether the attribute is expressed 
as an explicit value or as an index that reference global attributes, as described in the following steps:
<ol>
	<li>Use the \ref a3d_cascadedattributes feature to obtain an \ref A3DGraphStyleData structure for the entity.
		(You can also use the \ref A3DGraphicsGet function to obtain graphic data for the entity; 
		however, it does not resolve inheritance settings.)</li>
	<li>For \ref A3DGraphStyleData members that contain attribute values (instead of indexes), 
		use the values as is.</li>
	<li>For \ref A3DGraphStyleData members that contain indexes (patterns or colors), 
	 	obtain the value from the current default global settings or from the appropriate global array.</li>
</ol>
*/

/*!
\brief Graphics data
\ingroup a3d_graphics
\version 2.0

To get the graphical attributes of an entity that has  the
\ref A3DRootBaseWithGraphics entity as its base, do these tasks: 
<ol>
	<li>Use the \ref m_uiStyleIndex member to retrieve the index of style in the global style array.</li>
	<li>If the index matches the default value, no particular graphical style is applied on entity.
	<li>Otherwise, use the index on \ref A3DGlobalGetGraphStyleData 
		to get the \ref A3DGraphStyleData from the global object. </li>
		<ul>
			<li>Width and transparency are directly on the \ref A3DGraphStyleData object.</li>
			<li>Use the indexes for colors, materials, textures, or patterns 
				and dedicated functions to get these graphics objects from global arrays.</li>
		</ul>
	</li>
</ol>

\warning When initializing the \ref A3DGraphicsData structure with the \ref A3D_INITIALIZE_DATA macro, every 
field is set to NULL; thus, to create a graphic attribute, and <b>if you do not change the behavior, the object will be hidden</b>. 
Please refer to \ref a3d_graphicsbits for more information on possible values. 
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiLayerIndex;	/*!< Layer index. */
	A3DUns32 m_uiStyleIndex;	/*!< Index of the display style in the global style array. \sa A3DGraphStyleData */
	A3DUns16 m_usBehaviour;		/*!< Behavior. \sa a3d_graphicsbits */
} A3DGraphicsData;

/*!
\brief Populates the \ref A3DGraphicsData structure
\ingroup a3d_graphics
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphicsGet,(const A3DGraphics* pGraphics,
												A3DGraphicsData* pData));


/*!
\brief Creates a \ref A3DGraphics from \ref A3DGraphicsData structure
\ingroup a3d_graphics
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphicsCreate,(const A3DGraphicsData* pData, 
													A3DGraphics** ppGraphics));

/*!
\defgroup a3d_graphicsbits Bit Field for Behavior on Graphics
\ingroup a3d_graphics
\version 2.0

This bit field defines the behavior of a given entity, regarding its visibility, color, transparency, layer, line pattern and line width, given
its position in the tree of entities. The inheritance works as follows:<BR>
<BR>
Following the path of a leaf in the tree of entities:<BR>
\li If there are <b>SonHerit</b> flags, it is the lowest node in the tree which has this flag which defines the value, except if it has a <b>FatherHerit</b> flag.
\li If there are <b>FatherHerit</b> flags, it is the highest node in the tree which has this flag which defines the value.
\li If there is no flag, the current value is set, if any.<BR>

To determine the value of a son regarding his father, the following rules can be applied:<BR>
\li If the father has a <b>SonHerit</b> flag and the son has a <b>SonHerit</b> flag too, the value is the one of the son.
\li If the father has a <b>SonHerit </b>flag but not the son, the value is the one of the father.
\li If the father does not have a <b>SonHerit</b> flag, but the son has one, the value is the one of the son.
\li If the father does not have a <b>SonHerit</b> flag neither a <b>FatherHerit</b> flag, and the son does not have a <b>SonHerit</b> flag too, the value is the one of the son.
\li If none of those rules can match, the value is the current one.<BR>

Following are different configurations that can be found:<BR>
<TABLE border=1 border=1 rules="all" cellspacing="0" cellpadding="10" align="left">
<TR>
  <TD>\image html graphicsbits_image001.png</TD>
  <TD>This tree has no flag; each node defines its own color. This is the reference.
Each following diagram is the same than this one, but with different flags on some nodes.  The 'S' means that the node has a
<b>SonHerit</b> flag, the 'F'; that the node has a <b>FatherHerit</b> flag.</TD>
 </TR>
 <TR>
  <TD>\image html graphicsbits_image002.png</TD>
  <TD>The second leaf does not have a <b>SonHerit</b> flag. It takes the pattern of its father.</TD>
 </TR>
 <TR>
  <TD>\image html graphicsbits_image003.png</TD>
  <TD>The second leaf does not have a <b>SonHerit</b> flag, and also its father. So it takes its own value of pattern.</TD>
 </TR>
 <TR>
  <TD>\image html graphicsbits_image004.png</TD>
  <TD>The second node has a <b>FatherHerit</b> flag. Its sons don't have any flag. They take the pattern of their father.</TD>
 </TR>
 <TR>
  <TD>\image html graphicsbits_image005.png</TD>
  <TD>The second node has a <b>FatherHerit</b> flag. The first leaf has a <b>SonHerit</b> flag. It takes its own pattern. 
But the second leaf doesn't have a <b>SonHerit</b> flag, so it takes the pattern of its father.</TD>
 <TR>
  <TD>\image html graphicsbits_image006.png</TD>
  <TD>The root node has a <b>FatherHerit</b> flag. The entire tree takes its pattern.</TD>
 </TR> 
 <TR>
  <TD>\image html graphicsbits_image007.png</TD>
  <TD>The root node has a <b>FatherHerit</b> flag. The second node too, so it takes the pattern of its father. The first
leaf has a <b>SonHerit</b> flag, so it takes its own pattern. But the second
leaf has no flag, so it takes the pattern of its father.</TD>
 </TR>
</TABLE>
<b>NB1:</b> The <b>SonHerit</b> flag overrides the <b>FatherHerit</b> flag.<BR>
<b>NB2:</b> If a <b>SonHeritShow</b> or a <b>FatherHeritShow  </b>flag is set, the <b>Show</b> flag is ignored.<BR>
@{
*/
#define kA3DGraphicsShow					0x0001	/*!< Entity is shown. */ 
#define kA3DGraphicsSonHeritShow			0x0002	/*!< Show inheritance. */ 
#define kA3DGraphicsFatherHeritShow			0x0004	/*!< Show inheritance. */ 
#define kA3DGraphicsSonHeritColor			0x0008	/*!< Color / material inheritance. */ 
#define kA3DGraphicsFatherHeritColor		0x0010 	/*!< Color / material inheritance. */ 
#define kA3DGraphicsSonHeritLayer			0x0020 	/*!< Layer inheritance. */ 
#define kA3DGraphicsFatherHeritLayer		0x0040 	/*!< Layer inheritance. */ 
#define kA3DGraphicsSonHeritTransparency	0x0080 	/*!< Transparency inheritance. */ 
#define kA3DGraphicsFatherHeritTransparency	0x0100 	/*!< Transparency inheritance. */ 
#define kA3DGraphicsSonHeritLinePattern		0x0200 	/*!< Line pattern inheritance. */ 
#define kA3DGraphicsFatherHeritLinePattern	0x0400	/*!< Line pattern inheritance. */ 
#define kA3DGraphicsSonHeritLineWidth		0x0800 	/*!< Line width inheritance. */ 
#define kA3DGraphicsFatherHeritLineWidth	0x1000 	/*!< Line width inheritance. */ 
#define kA3DGraphicsRemoved					0x2000 	/*!< Entity is removed. As a result, the entity no longer appears in the tree. */ 
/*!
@} <!-- End of module a3d_graphicsbits -->
*/
#endif	/*	__A3D_GRAPHIC__ */


#ifndef __A3D_GRAPHIC_STYLE__
/*!
\defgroup a3d_style Display Style
\ingroup a3d_graphics
Entity type is \ref kA3DTypeGraphStyle.
*/

typedef enum
{
	kA3DSolid,							/*!< Solid rendering mode. \todo To be documented. */
	kA3DSolidOutline,					/*!< Solid outline rendering mode. \todo To be documented. */
	kA3DWireframe,						/*!< Wireframe rendering mode. \todo To be documented. */
	kA3DHLR								/*!< HLR rendering mode. \todo To be documented. */
} A3DERenderingMode;

/*!
\brief Style data
\ingroup a3d_style
\version 2.0


Some of the members in this structure have paired interactions 
in which one member influences the behavior of the next member.
See the member descriptions for details. 

Use the \ref A3DGlobalData and dedicated global access functions to get graphic settings in the global arrays.

\sa \ref a3d_global_data_module
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dWidth;					/*!< Line width in mm. */
	A3DBool m_bVPicture;				/*!< A value of true indicates the  \ref m_uiLinePatternIndex member (next) 
											references a vpicture in the global arrays
											(see \ref A3DGraphVPicturePatternData).
											A value of false indicates it references a line pattern 
											(see \ref A3DGraphLinePatternData). */
	A3DUns32 m_uiLinePatternIndex;		/*!< Index in the global array as indicated in the \ref m_bVPicture member (above). */
	A3DBool m_bMaterial;				/*!< A value of true indicates the \ref m_uiRgbColorIndex member (next) 
											references a material in the global arrays 
											(see \ref A3DGraphMaterialData or \ref A3DGraphTextureApplicationData). 
											A value of false indicates it references a color 
											(see \ref A3DGraphRgbColorData). */
	A3DUns32 m_uiRgbColorIndex;			/*!< Index in the global array as indicated in the \ref m_bMaterial member (above). */
	A3DBool m_bIsTransparencyDefined;	/*!< A value of true indicates 
											the \ref m_ucTransparency member (next) is defined. 
											A value of false indicates the transparency is the default value (255). */
	A3DUns8 m_ucTransparency;			/*!< From 0 (transparent) to 255 (opaque). Default value is 255. */
	A3DBool m_bSpecialCulling;			/*!< A value of true indicates special culling defined.
											See descriptions for \ref m_bFrontCulling, \ref m_bBackCulling,
											and m_bBackCulling. */
	A3DBool m_bFrontCulling;				/*!< If \ref m_bSpecialCulling is TRUE and if \ref m_bFrontCulling is TRUE, 
							 				font culling is active. */
	A3DBool m_bBackCulling;				/*!< If \ref m_bSpecialCulling is TRUE and if \ref m_bBackCulling is TRUE, 
											back-culling is active. */
	A3DBool m_bNoLight;					/*!< A value of true indicates material light is sensible. */
	A3DERenderingMode m_eRenderingMode; /*!< Rendering mode, see enum above. */
} A3DGraphStyleData;


/*!
\brief Populates the \ref A3DGraphStyleData structure
\ingroup a3d_style
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphStyleData,(const A3DUns32 uiIndexStyle,
																A3DGraphStyleData* pData));

/*!
\brief Inserts a style from \ref A3DGraphStyleData structure into the global data
\ingroup a3d_style
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphStyle,(const A3DGraphStyleData* pData,
																A3DUns32* puiIndexStyle));
#endif	/*	__A3D_GRAPHIC_STYLE__ */

#ifndef __A3D_GRAPHIC_COLOR__
/*!
\defgroup a3d_rgbcolor RGB Color
\ingroup a3d_graphics
*/

/*!
\brief RGB Color data
\ingroup a3d_rgbcolor
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dRed;	/*!< [0..1] red value. */
	A3DDouble m_dGreen;	/*!< [0..1] green value. */
	A3DDouble m_dBlue;	/*!< [0..1] blue value. */
} A3DGraphRgbColorData;

/*!
\brief Populates the \ref A3DGraphRgbColorData structure
\ingroup a3d_rgbcolor
\version 2.0

Structure of three doubles containing values for Red, Green and Blue intensities of current color. 
These values must be between 0.0 and 1.0.
\note The index must be a multiple of 3.
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphRgbColorData,(const A3DUns32 uiIndexRgbColor,
																	A3DGraphRgbColorData* pData));

/*!
\brief Creates a color from \ref A3DGraphRgbColorData structure in global data
\ingroup a3d_rgbcolor
\version 2.0

This function returns the index (puiIndexRgbColor) of the color in global data.
The index returned is not a new index if the same color is already stored.
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphRgbColor,(const A3DGraphRgbColorData* pData,
																	A3DUns32* puiIndexRgbColor));

#endif	/*	__A3D_GRAPHIC_COLOR__ */


#ifndef __A3D_GRAPHIC_LINEPATTERN__
/*!
\defgroup a3d_linepattern Line Pattern
\ingroup a3d_graphics

Entity type is \ref kA3DTypeGraphLinePattern.
This structure contains an array of doubles defining the basic sequence used to 
describe a line pattern. The dash is defined as number pairs, where 
the first number specifies the length of the line and the second number specifies the length of the space.
The pair is repeated.

If additional number pairs are provided, they are added to the sequence before the pattern is repeated.

Line and space lengths can be defined by using the current units (typically millimeters) or as proportions.

Here are some examples:
\li {10000., 0.} specifies a continuous line ____________________
\li {3., 3.} specifies a dashed line - - - - - - - - - -
\li {1., 4.} specifies a dotted line .  .  .  .  .  .  .
\li {1., 2., 4., 2.} specifies a line with a mixed pattern  _ ____ _ ____ _ ____
*/

/*!
\brief Line Pattern data
\ingroup a3d_linepattern
\version 2.0

Here are characteristics of a line pattern:
\li Array describing a basic sequence is always starting with a black value (pen down).
\li Sequence can start with an offset from 0 ( \ref m_dPhase ).
\li Sequence lengths can be defined in real length or proportions ( \ref m_bRealLength ).
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiNumberOfLengths;	/*!< Size of next array. */
	A3DDouble* m_pdLengths;			/*!< Array of lengths describing basic sequence for pattern. */
	A3DDouble m_dPhase;				/*!< Starting point. Can be non-zero. */
	A3DBool m_bRealLength;			/*!< Either proportion (OpenGL style) or real length (AutoCad DXF format style). */
} A3DGraphLinePatternData;

/*!
\brief Populates the \ref A3DGraphLinePatternData structure
\ingroup a3d_linepattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphLinePatternData,(const A3DUns32 uiIndexLinePattern,
																		A3DGraphLinePatternData* pData));

/*!
\brief Creates a line pattern from \ref A3DGraphLinePatternData structure in global data
\ingroup a3d_linepattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphLinePattern,(const A3DGraphLinePatternData* pData,
																		A3DUns32* puiIndexLinePattern));

#endif	/*	__A3D_GRAPHIC_LINEPATTERN__ */


#ifndef __A3D_GRAPHIC_MATERIAL__
/*!
\defgroup a3d_material Material
\ingroup a3d_graphics
Entity type is \ref kA3DTypeGraphMaterial.
*/

/*!
\brief Material data
\ingroup a3d_material
\version 2.0
\note Use \ref A3DGlobalGetGraphRgbColorData to get ambient, diffuse, emissive and specular colors.

\note The conventions described here are similar to the common scene graphics conventions described for 
other 3D standards such as OpenGL and DirectX. 
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiAmbient;			/*!< Ambient color. */
	A3DUns32 m_uiDiffuse;			/*!< Diffuse color. */
	A3DUns32 m_uiEmissive;			/*!< Emissive color. */
	A3DUns32 m_uiSpecular;			/*!< Specular color. */
	A3DDouble m_dAmbientAlpha;		/*!< Ambient alpha value. Not yet implemented. Use \ref A3DGraphStyleData::m_ucTransparency instead. */
	A3DDouble m_dDiffuseAlpha;		/*!< Diffuse alpha value. Not yet implemented. Use \ref A3DGraphStyleData::m_ucTransparency instead. */
	A3DDouble m_dEmissiveAlpha;		/*!< Emissive alpha value. Not yet implemented. Use \ref A3DGraphStyleData::m_ucTransparency instead. */
	A3DDouble m_dSpecularAlpha;		/*!< Specular alpha value. Not yet implemented. Use \ref A3DGraphStyleData::m_ucTransparency instead. */
	A3DDouble m_dShininess;			/*!< Shininess. Valid values are between 0.0 and 1.0. */
} A3DGraphMaterialData;

/*!
\brief Populates the \ref A3DGraphMaterialData structure
\ingroup a3d_material
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphMaterialData,(const A3DUns32 uiIndexMaterial,
																	A3DGraphMaterialData* pData));

/*!
\brief Creates a material from \ref A3DGraphMaterialData structure in global data
\ingroup a3d_material
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphMaterial,(const A3DGraphMaterialData* pData, 
																	A3DUns32* puiIndexMaterial));

#endif	/*	__A3D_GRAPHIC_MATERIAL__ */

#ifndef __A3D_GRAPHIC_PICTURE__
/*!
\defgroup a3d_picture Picture
\ingroup a3d_graphics
Entity type is \ref kA3DTypeGraphPicture.

The \COMPONENT_A3D_API does not interpret or otherwise process picture data (image data).
Instead, it transmits picture data directly to the \PRODUCT_ACRO3D rendering engine. 

For information about the picture data formats that \PRODUCT_ACRO3D supports, see 
the "Filters" section in the \REF_PDF_REFERENCE.
*/

/*!
\ingroup a3d_picture
\brief Image format
\version 2.0

\note The conventions described here are similar to the common scene graphics conventions described for 
other 3D standards such as OpenGL and DirectX.

*/
typedef enum
{	
	kA3DPicturePng,					/*!< PNG format. \todo To be documented. */
	kA3DPictureJpg,					/*!< JPEG format. \todo To be documented. */
	kA3DPictureBmp,					/*!< BMP format. \todo To be documented. */
	kA3DPictureBitmapRgbByte,		/*!< \todo To be documented. */
	kA3DPictureBitmapRgbaByte,		/*!< \todo To be documented. */
	kA3DPictureBitmapGreyByte,		/*!< \todo To be documented. */
	kA3DPictureBitmapGreyaByte		/*!< \todo To be documented. */
} A3DEPictureDataFormat;

/*!
\brief Picture data
\ingroup a3d_picture
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DEPictureDataFormat m_eFormat;	/*!< Format for image. */
	A3DUns32 m_uiSize;					/*!< Size for next array. */
	A3DUns8* m_pucBinaryData;			/*!< Binary data for image. */
	A3DUns32 m_uiPixelWidth;			/*!< Pixel width. \todo To be documented. */
	A3DUns32 m_uiPixelHeight;			/*!< Pixel height. \todo To be documented. */
} A3DGraphPictureData;

/*!
\brief Populates the \ref A3DGraphPictureData structure
\ingroup a3d_picture
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphPictureData,(	const A3DUns32 uiIndexPicture,
																	A3DGraphPictureData* pData));

/*!
\brief Creates a picture from \ref A3DGraphPictureData structure in global data
\ingroup a3d_picture
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphPicture,(const A3DGraphPictureData* pData,
																	A3DUns32* puiPictureIndex));

/*!
@}
*/

#endif	/*	__A3D_GRAPHIC_PICTURE__ */

#ifndef __A3D_GRAPHIC_DOTTINGPATTERN__
/*!
\defgroup a3d_dottingpattern Dotting Pattern
\ingroup a3d_graphics
Entity type is \ref kA3DTypeGraphDottingPattern. It is one of the four Fill Patterns.
*/

/*!
\ingroup a3d_dottingpattern
\brief Dotting Pattern Structure
\version 2.0

By default, this pattern describes a regular grid of point spaced with the \ref m_dPitch member.
If \ref m_bZigZag is TRUE, then points are offset in X by \ref m_dPitch /2.0 for the odd row.
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dPitch;					/*!< Pitch. \todo To be documented. */
	A3DBool m_bZigZag;					/*!< Zigzag. \todo To be documented. */
	A3DUns32 m_uiColorIndex;			/*!< Color index. \todo To be documented. */
	A3DUns32 m_uiNextPatternIndex;		/*!< Next pattern index. \todo To be documented. */
} A3DGraphDottingPatternData;

/*!
\brief Populates the \ref A3DGraphDottingPatternData structure
\ingroup a3d_dottingpattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphDottingPatternData,(const A3DUns32 uiIndexDottingPattern,
																			A3DGraphDottingPatternData* pData));

/*!
\brief Creates a Dotting Pattern from \ref A3DGraphDottingPatternData structure in global data
\ingroup a3d_dottingpattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphDottingPattern,(	const A3DGraphDottingPatternData* pData,
																			A3DUns32* puiIndexDottingPattern));

#endif	/*	__A3D_GRAPHIC_DOTTINGPATTERN__ */

#ifndef __A3D_GRAPHIC_HATCHINGPATTERN__

/*!
\defgroup a3d_hatchingpattern Hatching Pattern
\ingroup a3d_graphics
Entity type is \ref kA3DTypeGraphHatchingPattern. It is one of the four Fill Patterns.
*/

/*!
\defgroup a3d_hatchingpatternline Hatching Pattern Line
\ingroup a3d_hatchingpattern
*/
/*!
\ingroup a3d_hatchingpatternline
\brief A HatchingPatternLine is a group of infinite lines in XY space that are defined 
by a start line and an offset between sequential lines.
\version 2.0

Start line is defined by a start point and an angle in radians from the X Axis.
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DVector2dData	m_sStart;		/*!< Start. \todo To be documented. */
	A3DVector2dData	m_sOffset;		/*!< Offset. \todo To be documented. */
	A3DDouble m_dAngle;				/*!< Angle. \todo To be documented. */
	A3DUns32 m_uiStyleIndex;		/*!< Style index. \todo To be documented. */
} A3DGraphHatchingPatternLineData;

/*!
\ingroup a3d_hatchingpattern
\brief Hatching Pattern Structure
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiSize;									/*!< Size of next array. */
	A3DGraphHatchingPatternLineData* m_psHatchLines;	/*!< Hatch lines array. \todo To be documented. */
	A3DUns32 m_uiNextPatternIndex;						/*!< Next pattern index. \todo To be documented. */
} A3DGraphHatchingPatternData;

/*!
\brief Populates the \ref A3DGraphHatchingPatternData structure
\ingroup a3d_hatchingpattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphHatchingPatternData,(	const A3DUns32 uiIndexHatchingPattern,
																				A3DGraphHatchingPatternData* pData));

/*!
\brief Creates a Hatching Pattern from \ref A3DGraphHatchingPatternData structure in global data
\ingroup a3d_hatchingpattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphHatchingPattern,(const A3DGraphHatchingPatternData* pData,
																			A3DUns32* puiIndexHatchingPattern));

#endif	/*	__A3D_GRAPHIC_HATCHINGPATTERN__ */

#ifndef __A3D_GRAPHIC_SOLIDPATTERN__
/*!
\defgroup a3d_solidpattern Solid Pattern
\ingroup a3d_graphics
Entity type is \ref kA3DTypeGraphSolidPattern. It is one of the four Fill Patterns.
*/

/*!
\ingroup a3d_solidpattern
\brief Solid Pattern Structure
\version 2.0
*/
typedef struct
{
	A3DUns16	m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool		m_bMaterial;				/*!< Is next index related to \ref A3DGraphMaterialData or \ref A3DGraphRgbColorData in \ref A3DGlobalData? */
	A3DUns32	m_uiRgbColorIndex;			/*!< Index in array as indicated above. */
	A3DUns32	m_uiNextPatternIndex;		/*!< Next pattern index. \todo To be documented. */
} A3DGraphSolidPatternData;

/*!
\brief Populates the \ref A3DGraphSolidPatternData structure
\ingroup a3d_solidpattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphSolidPatternData,(	const A3DUns32 uiIndexSolidPattern,
																			A3DGraphSolidPatternData* pData));

/*!
\brief Creates a Solid Pattern from \ref A3DGraphSolidPatternData structure in global data
\ingroup a3d_solidpattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphSolidPattern,(const A3DGraphSolidPatternData* pData,
																		A3DUns32* puiIndexSolidPattern));

#endif	/*	__A3D_GRAPHIC_SOLIDPATTERN__ */

#ifndef __A3D_GRAPHIC_VPICTUREPATTERN__

/*!
\defgroup a3d_vpicturepattern Vectorized Picture Pattern
\ingroup a3d_graphics
Entity type is \ref kA3DTypeGraphVPicturePattern. It is one of the four Fill Patterns.

This pattern uses a tessellation to define a vectorized picture.
*/

/*!
\ingroup a3d_vpicturepattern
\brief VPicture Pattern Structure
\version 2.0

\warning \ref m_pMarkupTess is a restricted version of \ref kA3DTypeTessMarkup.
The authorized entities are as follows:
- Polyline
- Triangles
- Color
- Line stipple
- Points
- Polygon
- Line width
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiNextPatternIndex;	/*!< Next pattern index. \todo To be documented. */
	A3DTessMarkup* m_pMarkupTess;	/*!< Tessellation used as pattern. */
} A3DGraphVPicturePatternData;

/*!
\brief Populates the \ref A3DGraphVPicturePatternData structure
\ingroup a3d_vpicturepattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalGetGraphVPicturePatternData,(	const A3DUns32 uiIndexVPicturePattern,
																				A3DGraphVPicturePatternData* pData));

/*!
\brief Creates a VPicture Pattern from \ref A3DGraphVPicturePatternData structure in global data
\ingroup a3d_vpicturepattern
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DEFAULT_COLOR \n
\return \ref A3D_INVALID_COLOR_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalInsertGraphVPicturePattern,(const A3DGraphVPicturePatternData* pData,
																			A3DUns32* puiIndexVPicturePattern));

#endif	/*	__A3D_GRAPHIC_VPICTUREPATTERN__ */

#ifndef __A3D_CAMERA__
/*!
\defgroup a3d_camera Camera
\ingroup a3d_graphics_module
Entity type is \ref kA3DTypeGraphCamera.
*/
/*!
\ingroup a3d_camera
\brief Camera Structure
\version 2.0

The \ref m_bOrthographic influences the interpretation of the \ref m_dXFovy and \ref m_dYFovy members, 
as described in the member descriptions.
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bOrthographic;	/*!< A value of true indicates an orthographic projection.
									A value of false indicates a perspective projection. */
	A3DVector3dData m_sLocation;/*!< Position of the camera. */
	A3DVector3dData m_sLookAt;	/*!< Position of the target. */
	A3DVector3dData m_sUp;		/*!< Up vector. It should be defined so that it is perpendicular to the vector created between the camera and target position. 
									A non-perpendicular up vector results in unpredictable behavior. */
	A3DDouble m_dXFovy;			/*!< For an orthographic projection (\ref m_bOrthographic is true), this member specifies the view size in the X direction.
									For a perspective projection, it specifies a field of view angle in radians in the X direction. 
									Usually, X and Y are equal and the aspect ratio is set to 1. */
	A3DDouble m_dYFovy;			/*!< For an orthographic projection (\ref m_bOrthographic is true), this member specifies the view size in the Y direction.
									For a perspective projection, it specifies a field of view angle in radians in the Y direction. 
									Usually, X and Y are equal and the aspect ratio is set to 1. */
	A3DDouble m_dAspectRatio;	/*!< Ratio of X to Y. Usually, X and Y are equal and the aspect ratio is set to 1. */
	A3DDouble m_dZNear;			/*!< Near clipping plane distance from the viewer (positive value). */
	A3DDouble m_dZFar;			/*!< Far clipping plane distance from the viewer (positive value). */
	A3DDouble m_dZoomFactor;	/*!< Zoom factor. Usually, this parameter is not considered and the zoom factor is specified through \ref m_dXFovy and \ref m_dYFovy.
									For an orthographic projection, the view size is directly defined by the X and Y parameters. For example \ref m_dXFovy = \ref m_dYFovy = 100
									means the size of the view is 100.
									For a perspective projection, the zoom factor is deduced from the angle of the field of view and the distance camera-target. */
} A3DGraphCameraData;

/*!
\brief Populates the \ref A3DGraphCameraData structure
\ingroup a3d_camera
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphCameraGet,(const A3DGraphCamera* pCamera,
													A3DGraphCameraData* pData));


/*!
\brief Creates a \ref A3DGraphCamera from \ref A3DGraphCameraData structure
\ingroup a3d_camera
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphCameraCreate,(const A3DGraphCameraData* pData, 
														A3DGraphCamera** ppCamera));

#endif	/*	__A3D_CAMERA__ */

/*!
\defgroup a3d_light Light
\ingroup a3d_graphics_module
\brief Creates and accesses light sources 

This module explains how to create and access the PRC entities that specify light sources.
Light sources provide the lighting for a 3D scene. 
A single scene can specify multiple different light sources.

*/

#ifndef __A3D_AMBIENT_LIGHT__
/*!
\defgroup a3d_light_ambient Ambient Light
\ingroup a3d_light
\brief Creates and accesses ambient light attributes

This module explains how to create and access a PRC entity that specifies an ambient light source.
Ambient light is light that is generally scattered about the scene to the extent that the source
of the light cannot be determined.
 
Entity type is \ref kA3DTypeGraphAmbientLight.

*/

/*!
\ingroup a3d_light_ambient
\brief Light Structure. Ambient light
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiAmbientColorIndex;			/*!< Ambient color index. */
	A3DUns32 m_uiDiffuseColorIndex;			/*!< Diffuse color index. */
	A3DUns32 m_uiSpecularColorIndex;		/*!< Specular color index. */
} A3DGraphAmbientLightData;

/*!
\brief Populates the \ref A3DGraphAmbientLightData structure
\ingroup a3d_light_ambient
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphAmbientLightGet,(const A3DGraphAmbientLight* pLight,
															A3DGraphAmbientLightData* pData));

/*!
\brief Creates a \ref A3DGraphAmbientLight from an \ref A3DGraphAmbientLightData structure
\ingroup a3d_light_ambient
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphAmbientLightCreate,(const A3DGraphAmbientLightData* pData, 
																A3DGraphAmbientLight** ppLight));

#endif	/*	__A3D_AMBIENT_LIGHT__ */

#ifndef __A3D_POINT_LIGHT__
/*!
\defgroup a3d_light_point Point Light
\ingroup a3d_light
\brief Creates and accesses point light attributes

This module explains how to create and access a PRC entity that specifies a point light source.
Point light radiates equally in all directions, similar to a light bulb.
 
Entity type is \ref kA3DTypeGraphPointLight.
*/

/*!
\ingroup a3d_light_point
\brief A structure representing the settings for a point light
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiAmbientColorIndex;			/*!< Ambient color index. */
	A3DUns32 m_uiDiffuseColorIndex;			/*!< Diffuse color index. */
	A3DUns32 m_uiSpecularColorIndex;		/*!< Specular color index. */
	A3DVector3dData m_sLocation;			/*!< Location. */
	A3DDouble m_dConstantAttenuation;		/*!< Constant attenuation. */
	A3DDouble m_dLinearAttenuation;			/*!< Linear attenuation. */
	A3DDouble m_dQuadraticAttenuation;		/*!< Quadratic attenuation. */
} A3DGraphPointLightData;

/*!
\brief Populates the \ref A3DGraphPointLightData structure
\ingroup a3d_light_point
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphPointLightGet,(	const A3DGraphPointLight* pLight,
															A3DGraphPointLightData* pData));

/*!
\brief Creates a \ref A3DGraphPointLight from \ref A3DGraphPointLightData structure
\ingroup a3d_light_point
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphPointLightCreate,(	const A3DGraphPointLightData* pData, 
																A3DGraphPointLight** ppLight));

#endif	/*	__A3D_POINT_LIGHT__ */

#ifndef __A3D_SPOT_LIGHT__
/*!
\defgroup a3d_light_spot Spotlight
\ingroup a3d_light
\brief Creates and accesses spotlight attributes

This module explains how to create and access a PRC entity that specifies a spotlight source.
A spotlight source radiates in a conical direction, similar to a car headlight.

Entity type is \ref kA3DTypeGraphSpotLight.
*/
/*!
\ingroup a3d_light_spot
\brief Spotlight structure

For version 2.1, additional fields for attenuation settings were added to this structure. 
These additional fields are identified with version tags.

\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiAmbientColorIndex;			/*!< Ambient color index. */
	A3DUns32 m_uiDiffuseColorIndex;			/*!< Diffuse color index. */
	A3DUns32 m_uiSpecularColorIndex;		/*!< Specular color index. */
	A3DVector3dData m_sDirection;			/*!< Direction. */
	A3DDouble m_dFallOffAngle;				/*!< Fall-off angle.*/
	A3DDouble m_dFallOffExponent;			/*!< Fall-off exponent. */
	A3DVector3dData m_sLocation;			/*!< Location. \version 2.1 */
	A3DDouble m_dConstantAttenuation;		/*!< Constant attenuation. \version 2.1 */
	A3DDouble m_dLinearAttenuation;			/*!< Linear attenuation. \version 2.1 */
	A3DDouble m_dQuadraticAttenuation;		/*!< Quadratic attenuation. \version 2.1 */
} A3DGraphSpotLightData;

/*!
\brief Populates the \ref A3DGraphSpotLightData structure
\ingroup a3d_light_spot
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphSpotLightGet,(const A3DGraphSpotLight* pLight,
														A3DGraphSpotLightData* pData));

/*!
\brief Creates a \ref A3DGraphSpotLight from \ref A3DGraphSpotLightData structure
\ingroup a3d_light_spot
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphSpotLightCreate,(const A3DGraphSpotLightData* pData, 
															A3DGraphSpotLight** ppLight));

#endif	/*	__A3D_SPOT_LIGHT__ */

#ifndef __A3D_DIRECTIONAL_LIGHT__
/*!
\defgroup a3d_light_directional Directional Light
\ingroup a3d_light
\brief Creates and accesses a directional light attributes

This module explains how to create and access a PRC entity that specifies a directional light source.
A directional light (specular light) emanates from a particular direction and bounces off the surface in a preferred direction. Specular light gives a surface a shiny appearance.

Entity type is \ref kA3DTypeGraphDirectionalLight.
*/
/*!
\ingroup a3d_light_directional
\brief Light Structure. Directional light
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiAmbientColorIndex;		/*!< Ambient color index. */
	A3DUns32 m_uiDiffuseColorIndex;		/*!< Diffuse color index. */
	A3DUns32 m_uiSpecularColorIndex;	/*!< Specular color index. */
	A3DDouble m_dIntensity;				/*!< Density. */
	A3DVector3dData m_sDirection;		/*!< Direction. */
} A3DGraphDirectionalLightData;

/*!
\brief Populates the \ref A3DGraphDirectionalLightData structure
\ingroup a3d_light_directional
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphDirectionalLightGet,(	const A3DGraphDirectionalLight* pLight,
																	A3DGraphDirectionalLightData* pData));

/*!
\brief Creates a \ref A3DGraphDirectionalLight from \ref A3DGraphDirectionalLightData structure
\ingroup a3d_light_directional
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphDirectionalLightCreate,(	const A3DGraphDirectionalLightData* pData, 
																		A3DGraphDirectionalLight** ppLight));

#endif	/*	__A3D_DIRECTIONAL_LIGHT__ */

#ifndef __A3D_SCENEDISPPARAMS__
/*!
\defgroup a3d_scenedisplayparameters SceneDisplayParameters
\ingroup a3d_graphics_module
Entity type is \ref kA3DTypeGraphSceneDisplayParameters.
*/

/*!
\ingroup a3d_scenedisplayparameters
\brief SceneDisplayParameters Structure
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bIsActive;								/*!< \c true if scene is active, otherwise \c false. */
	A3DGraphCamera* m_pCamera;							/*!< Camera. */
	A3DUns32 m_uiLightSize;								/*!< Size of the next array. */
	A3DEntity** m_ppLights;								/*!< Lights array. */
	A3DUns32 m_uiPlaneSize;								/*!< Size of the next array. */
	A3DSurfPlane** m_ppClippingPlanes;					/*!< Clipping planes array. */
	A3DBool m_bHasRotationCenter;						/*!< \c true if the scene has a rotation center, otherwise \c false. */
	A3DVector3dData m_sRotationCenter;					/*!< Rotation center. */
	A3DUns32 m_uiBackgroundStyleIndex;					/*!< Backgrounds style index. */
	A3DUns32 m_uiDefaultStyleIndex;						/*!< Default style index. */
	A3DUns32 m_uiDefaultPerTypeIndexSize;				/*!< Size of the next array. */
	A3DUns32* m_puiDefaultStyleIndexesPerType;			/*!< Default style indexes per type array. */
	A3DEEntityType* m_puiTypesOfDefaultStyleIndexes;	/*!< Types array. */

} A3DGraphSceneDisplayParametersData;

/*!
\brief Populates the \ref A3DGraphSceneDisplayParametersData structure
\ingroup a3d_scenedisplayparameters
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphSceneDisplayParametersGet,(	const A3DGraphSceneDisplayParameters* pSceneDisplayParameters,
																			A3DGraphSceneDisplayParametersData* pData));


/*!
\brief Creates a \ref A3DGraphSceneDisplayParameters from \ref A3DGraphSceneDisplayParametersData structure
\ingroup a3d_scenedisplayparameters
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGraphSceneDisplayParametersCreate,(	const A3DGraphSceneDisplayParametersData* pData, 
																				A3DGraphSceneDisplayParameters** ppSceneDisplayParameters));

#endif	/*	__A3D_SCENEDISPPARAMS__ */

#ifndef __A3D_CASCADEDATTRIBUTES__
/*!
\defgroup a3d_cascadedattributes Miscellaneous Cascaded Attributes
\ingroup a3d_misc_module
\brief Access inheritable PRC attributes such as visibility, color, and coordinate system

These functions provide tools for browsing the model file and for determining 
inheritable attributes such as visibility, color, and coordinate system. 
The functions and structures in this module simplify the determination of inherited attributes. 
<a class="el" href="managing_attribute_inheritance.html">Miscellaneous Cascaded Attributes</a> provides a complete explanation and sample code.

\sa \ref a3d_graphicsbits
\sa <a class="el" href="managing_attribute_inheritance.html">Miscellaneous Cascaded Attributes</a>
*/

/*!
\ingroup a3d_cascadedattributes
\brief Cascaded Attributes Structure
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bShow;							/*!< The object is to be shown. */
	A3DBool m_bRemoved;							/*!< The object or its reference has been removed. */
	A3DUns16 m_usLayer;							/*!< Layer \todo To be documented. */
	A3DGraphStyleData m_sStyle;					/*!< Style to use for the object. */
	A3DRiCoordinateSystem* m_pCoordinateSystem;	/*!< Coordinate system to use for the object. */
} A3DMiscCascadedAttributesData;


/*!
\brief Creates a \ref A3DMiscCascadedAttributes
\ingroup a3d_cascadedattributes
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscCascadedAttributesCreate,(A3DMiscCascadedAttributes** ppAttr));

/*!
\brief Delete a \ref A3DMiscCascadedAttributes
\ingroup a3d_cascadedattributes
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscCascadedAttributesDelete,(A3DMiscCascadedAttributes* pAttr));

/*!
\brief Populate the \ref A3DMiscCascadedAttributesData structure
\ingroup a3d_cascadedattributes
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscCascadedAttributesGet,(	const A3DMiscCascadedAttributes* pAttr,
																	A3DMiscCascadedAttributesData* psData));

/*!
\brief Push a \ref A3DMiscCascadedAttributes
\ingroup a3d_cascadedattributes
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscCascadedAttributesPush,(A3DMiscCascadedAttributes* pAttr,
																	const A3DRootBaseWithGraphics* pBase,
																	const A3DMiscCascadedAttributes* pFather));

/*!
\brief Push a \ref A3DMiscCascadedAttributesData for a \ref A3DTessFaceData
\ingroup a3d_cascadedattributes
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscCascadedAttributesPushTessFace,(	A3DMiscCascadedAttributes* pAttr,
																				const A3DRiRepresentationItem* pRepItem,
																				const A3DTessBase* pTessBase,
																				const A3DTessFaceData* psTessFaceData,
																				A3DUns32 uiFaceIndex,
																				const A3DMiscCascadedAttributes* pFather));

A3D_API (A3DStatus, A3DMiscCascadedAttributesEntityReferencePush,(A3DMiscCascadedAttributes* pAttr,
																						const A3DAsmProductOccurrence* pOccurrence,
																						A3DPtr* ppPtr));

A3D_API (A3DStatus, A3DMiscPointerFromIndexGet,(const A3DUns32 uiIndex,
																const A3DEEntityType eType,
																A3DEntity** ppEntity));

A3D_API (A3DStatus, A3DMiscRootBaseInsertAttribute, (const A3DRootBase* pRootBase, const A3DMiscAttribute* pAttribute));

#endif	/*	__A3D_CASCADEDATTRIBUTES__ */

#endif	/*	__A3DPRCGRAPHICS_H__ */
