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
\brief      Header file for the draw module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCDRAWMODELFILE_H__
#define __A3DPRCDRAWMODELFILE_H__

#ifndef __A3DPRCMARKUP_H__
#error A3DSDKMarkup.h must be included before current file
#endif

#ifndef __A3DPRCTEXTURE_H__
#error A3DSDKTexture.h must be included before current file
#endif

#ifndef __A3DPRCGRAPHICS_H__
#error A3DSDKGraphics.h must be included before current file
#endif

/*!
\defgroup a3d_draw_module Draw Module
\brief Draws model file entities using callback functions you provide

The functions and callback functions in this module allow you to 
draw PRC model files using drawing functions that you provide.
*/

/*!
\defgroup a3d_draw_functions_pointers Callback-Function Type Definitions
\ingroup a3d_draw_module
*/

/*!
\brief Enumeration for characterizing material 
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef enum 
{
	kA3DDrawMaterialAmbient, /*!< Ambient color. RGBA. */
	kA3DDrawMaterialDiffuse, /*!< Diffuse color. RGBA. */
	kA3DDrawMaterialSpecular, /*!< Specular color. RGBA. */
	kA3DDrawMaterialEmission, /*!< Emission color. RGBA. */
	kA3DDrawMaterialShininess /*!< Shininess color. Single value. */
} A3DEDrawMaterialType;

/*!
\brief Enumeration for characterizing begin and end callbacks
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef enum 
{
	kA3DDrawBeginEndProductOccurrence, /*!< Begins or ends drawing a \ref A3DAsmProductOccurrence. */
	kA3DDrawBeginEndRepresentationItem, /*!< Begins or ends drawing a \ref A3DRiRepresentationItem. */
	kA3DDrawBeginEndMarkup /*!< Begins or ends drawing a \ref A3DMkpMarkup. */
} A3DEDrawBeginEndType;

/*!
\brief Pushes the current matrix onto the stack
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawPushMatrix)(void);
/*!
\brief Pops the matrix off the stack
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawPopMatrix)(void);
/*!
\brief Multiplies the matrix on the top of the stack by another matrix
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawMultMatrix)(const A3DDouble adMatrix[16]);
/*!
\brief Begins drawing
\version 2.0

The \c pcName argument can be NULL if there is no name.
The \c uiTriangleCount argument is meaningful only 
when the \c eType argument has a value of \c kA3DDrawBeginEndRepresentationItem; 
otherwise, its value is 0.
\todo Doc
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawBegin)(A3DEDrawBeginEndType eType, const A3DUTF8Char* pcName, A3DUns32 uiTrianglesCount);
/*!
\brief End
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawEnd)(A3DEDrawBeginEndType eType);
/*!
\brief Returns all the points of a representation item tessellation
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawSetTessellationPoints)(const A3DVector3dData* pasPoint, A3DUns32 uiPointsSize);
/*!
\brief Projects the point
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawProject)(const A3DVector3dData* psPoint, A3DVector3dData* psResult);
/*!
\brief Un-projects the point
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawUnProject)(const A3DVector3dData* psPoint, A3DVector3dData* psResult);
/*!
\brief Draws a list of triangles
\ingroup a3d_draw_functions_pointers
\version 2.0

Each point of each triangle has its own normal.

*/
typedef void (*A3DCallbackDrawTriangle)(const A3DVector3dData* pasNormals, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a fan of triangles
\version 2.0

Each point of the fan has its own normal.
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleFan)(const A3DVector3dData* pasNormals, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a triangle strip
\version 2.0

Each point of the strip has its own normal.
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleStripe)(const A3DVector3dData* pasNormals, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a list of triangles where each triangle has only one normal
\version 2.0

Each triangle has only one normal. Therefore, the number of normals is \c uiPointsSize/3.
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleOneNormal)(const A3DVector3dData* pasNormals, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a fan of triangles with one normal
\version 2.0

The fan has only one normal, psNormal.
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawTriangleFanOneNormal)(const A3DVector3dData* psNormal, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a triangle strip with one normal
\version 2.0

The strip has only one normal, which is identified by the \c psNormal argument.
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleStripeOneNormal)(const A3DVector3dData* psNormal, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a list of textured triangles 
\version 2.0

Each point of each triangle has its own normal.
\note Textures are not yet implemented
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleTextured)(const A3DVector3dData* pasNormals, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a fan of textured triangles
\version 2.0

Each point of the fan has its own normal.
\note Textures are not yet implemented
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleFanTextured)(const A3DVector3dData* pasNormals, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a triangle strip
\version 2.0

Each point of the strip has its own normal.
\note Textures are not yet implemented
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleStripeTextured)(const A3DVector3dData* pasNormals, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a list of textured triangles where each triangle has only one normal
\version 2.0

Each triangle has only one normal. Therefore, the number of normals is \c uiPointsSize/3.
\note Textures are not yet implemented
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleOneNormalTextured)(const A3DVector3dData* pasNormals, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a fan of textured triangles, where each triangle has only one normal
\version 2.0

The fan has only one normal, which is \c psNormal.
\note Textures are not yet implemented
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleFanOneNormalTextured)(const A3DVector3dData* psNormal, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Draws a triangle strip with one normal
\version 2.0

The strip has only one normal, which is returned in the \c psNormal argument.
\note Textures are not yet implemented
\ingroup a3d_draw_functions_pointers
*/
typedef void (*A3DCallbackDrawTriangleStripeOneNormalTextured)(const A3DVector3dData* psNormal, const A3DVector3dData* pasPoints, A3DUns32 uiPointsSize);
/*!
\brief Defines the color to be used for all subsequent entities
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 6.1
*/
typedef void (*A3DCallbackDrawColor)(const A3DDouble adPoints[3]);

/*!
\brief Defines the material to be used for all subsequent entities.
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawMaterial)(A3DEDrawMaterialType eType, const A3DDouble* pdValues, A3DUns32 uiValuesSize);
/*!
\brief Store current materials of the environment
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawBeginMaterial)(void);
/*!
\brief Restore materials of the environment previously stored
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawEndMaterial)(void);
/*!
\brief Requests the projection, modelview matrix and the viewport (See classical OGL definition for more informations)
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawGetDrawContext)(A3DDouble adProjection[16], A3DDouble adModelView[16], A3DInt32 aiViewport[4]);
/*!
\brief Draws a list of triangles without normals, for markups
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawMarkupTriangle)(const A3DDouble* pdPoints, A3DUns32 uiPointSize);
/*!
\brief Sets the environment to draw with screen coordinates
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawBeginFrameDraw)(const A3DVector3dData* psPoint3d, A3DBool bIsZoomable, A3DDouble dFixedSize);
/*!
\brief Ends the draw with screen coordinates
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawEndFrameDraw)(void);
/*!
\brief Sets the environment to draw with a fixed size
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawBeginFixedSize)(const A3DVector3dData* psPoint3d);
/*!
\brief Ends the draw with fixed size
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawEndFixedSize)(void);
/*!
\brief Draws a cylinder
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawCylinder)(A3DDouble dBaseRadius, A3DDouble dTopRadius, A3DDouble dHeight);
/*!
\brief Draws a polygon
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawPolygon)(const A3DDouble* pdPoints, A3DUns32 uiPointSize);
/*!
\brief Sets the environment to draw with a line width
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawBeginLineWidth)(A3DDouble dWidth);
/*!
\brief Ends the draw with a line width
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawEndLineWidth)(void);
/*!
\brief Draws a list of points
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawPoint)(const A3DDouble* pdPoints, A3DUns32 uiPointSize);
/*!
\brief Defines a font
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawFont)(const A3DFontKeyData* psFontKeyData);
/*!
\brief Sets the environment to draw with a line stipple
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawBeginLineStipple)(const A3DGraphStyleData* psGraphStyleData);
/*!
\brief Ends the draw with a line stipple
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawEndLineStipple)(void);
/*!
\brief Draws a symbol at the 3D position
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawSymbol)(const A3DGraphVPicturePatternData* psPatternData, const A3DVector3dData* psPosition);
/*!
\brief Draws a polyline
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawPolyLine)(const A3DDouble* pdPoints, A3DUns32 uiPointSize);
/*!
\brief Draws a text at current position
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawText)(const A3DUTF8Char* pcBuffer, A3DDouble dWidth, A3DDouble dHeight);
/*!
\brief Draws a pattern
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawPattern)(A3DUns32 uiLoopsSize, A3DUns32 uiPatternId, A3DUns32 uiFilledMode, A3DUns32 uiBehaviour, const A3DDouble* pdPoints, const A3DUns32* puiLoopsPointSize);
/*!
\brief Draws a picture at current position
\todo Doc
\ingroup a3d_draw_functions_pointers
\version 2.0
*/
typedef void (*A3DCallbackDrawPicture)(const A3DGraphPictureData* psPictureData);

/*!
\brief Structure for specifying callback functions for drawing
\ingroup a3d_draw_module
\version 2.0

Use this structure to define the callback functions \COMPONENT_A3D_LIBRARY will use to draw a model file entity.
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized using the \ref A3D_INITIALIZE_DATA macro. */
	A3DCallbackDrawPushMatrix m_pfuncPushMatrix; /*!< */
	A3DCallbackDrawPushMatrix m_pfuncPopMatrix; /*!< */
	A3DCallbackDrawMultMatrix m_pfuncMultMatrix; /*!< */
	A3DCallbackDrawBegin m_pfuncBegin; /*!< */
	A3DCallbackDrawEnd m_pfuncEnd; /*!< */
	A3DCallbackDrawSetTessellationPoints m_pfuncSetTessellationPoints; /*!< */
	A3DCallbackDrawTriangle m_pfuncTriangle; /*!< */
	A3DCallbackDrawTriangleFan m_pfuncTriangleFan; /*!< */
	A3DCallbackDrawTriangleStripe m_pfuncTriangleStripe; /*!< */
	A3DCallbackDrawTriangleOneNormal m_pfuncTriangleOneNormal; /*!< */
	A3DCallbackDrawTriangleFanOneNormal m_pfuncTriangleFanOneNormal; /*!< */
	A3DCallbackDrawTriangleStripeOneNormal m_pfuncTriangleStripeOneNormal; /*!< */
	A3DCallbackDrawTriangleTextured m_pfuncTriangleTextured; /*!< */
	A3DCallbackDrawTriangleFanTextured m_pfuncTriangleFanTextured; /*!< */
	A3DCallbackDrawTriangleStripeTextured m_pfuncTriangleStripeTextured; /*!< */
	A3DCallbackDrawTriangleOneNormalTextured m_pfuncTriangleOneNormalTextured; /*!< */
	A3DCallbackDrawTriangleFanOneNormalTextured m_pfuncTriangleFanOneNormalTextured; /*!< */
	A3DCallbackDrawTriangleStripeOneNormalTextured m_pfuncTriangleStripeOneNormalTextured; /*!< */
	A3DCallbackDrawMaterial m_pfuncMaterial; /*!< */
	A3DCallbackDrawGetDrawContext m_pfuncGetDrawContext; /*!< */
	A3DCallbackDrawMarkupTriangle m_pfuncMarkupTriangle; /*!< */
	A3DCallbackDrawUnProject m_pfuncUnProject; /*!< */
	A3DCallbackDrawBeginFrameDraw m_pfuncBeginFrameDraw; /*!< */
	A3DCallbackDrawEndFrameDraw m_pfuncEndFrameDraw; /*!< */
	A3DCallbackDrawBeginFixedSize m_pfuncBeginFixedSize; /*!< */
	A3DCallbackDrawEndFixedSize m_pfuncEndFixedSize; /*!< */
	A3DCallbackDrawCylinder m_pfuncCylinder; /*!< */
	A3DCallbackDrawPolygon m_pfuncPolygon; /*!< */
	A3DCallbackDrawBeginLineWidth m_pfuncBeginLineWidth; /*!< */
	A3DCallbackDrawEndLineWidth m_pfuncEndLineWidth; /*!< */
	A3DCallbackDrawPoint m_pfuncPoint; /*!< */
	A3DCallbackDrawFont m_pfuncFont; /*!< */
	A3DCallbackDrawBeginLineStipple m_pfuncBeginLineStipple; /*!< */
	A3DCallbackDrawEndLineStipple m_pfuncEndLineStipple; /*!< */
	A3DCallbackDrawSymbol m_pfuncSymbol; /*!< */
	A3DCallbackDrawPolyLine m_pfuncPolyLine; /*!< */
	A3DCallbackDrawText m_pfuncText; /*!< */
	A3DCallbackDrawPattern m_pfuncPattern; /*!< */
	A3DCallbackDrawPicture m_pfuncPicture; /*!< */
	A3DCallbackDrawBeginMaterial m_pfuncBeginMaterial; /*!< */
	A3DCallbackDrawEndMaterial m_pfuncEndMaterial; /*!< */
	A3DCallbackDrawColor m_pfuncColor; /*!< */
} A3DDrawCallbacksData;

/*!
\brief Initializes the callbacks used for drawing
\ingroup a3d_draw_module
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawInitCallbacks,( A3DDrawCallbacksData* psCallbacks));

/*!
\defgroup a3d_drawflags Flags for Drawing Model File Entities
\version 2.0

These flags apply to the \ref A3DDraw and \ref A3DDrawGetBoundingBox functions.
\ingroup a3d_draw_module
@{
*/
#define kA3DDraw3D		0x1 /*!< Draws only 3D tessellation. */
#define kA3DDrawMarkups	0x2 /*!< Draws only markups. */
/*!
@} <!-- End of a3d_drawflags -->
*/

/*!
\brief Draws the model file entities, using the callbacks defined by \ref A3DDrawInitCallbacks
\ingroup a3d_draw_module
\version 2.0

To set the \c uiDrawFlags argument, use the flags defined in \ref a3d_drawflags.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDraw,(const A3DAsmModelFile* pModelFile, A3DUns32 uiDrawFlags));


/*!
\brief Draws the representation item entities, using the callbacks defined by \ref A3DDrawInitCallbacks
\ingroup a3d_draw_module
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawRepresentationItem,(	const A3DRiRepresentationItem* pRepItem, const A3DMiscCascadedAttributes* pFatherAttr));


/*!
\brief Draws the markup item entities, using the callbacks defined by \ref A3DDrawInitCallbacks
\ingroup a3d_draw_module
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawMarkup, (const A3DMkpMarkup* pMarkup, const A3DMiscCascadedAttributes* pFatherAttr));

/*!
\brief Calculates the bounding box of the model file entity, without using any callback functions
\version 2.0

To set the \c uiDrawFlags argument, use the flags defined in \ref a3d_drawflags.
\ingroup a3d_draw_module
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawGetBoundingBox,(const A3DAsmModelFile* pModelFile, A3DBoundingBoxData* psBoundingBox, A3DUns32 uiDrawFlags));

#endif // #ifndef __A3DPRCDRAWMODELFILE_H__
