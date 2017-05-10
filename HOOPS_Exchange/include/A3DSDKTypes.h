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
\brief      Header file for type definitions
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCTYPES_H__
#define __A3DPRCTYPES_H__


/*!
\defgroup a3d_types_def Type Definitions

This section describes the types defined by the \COMPONENT_A3D_API. 
These type definitions concern fundamental types such as int, float, and strings and 
types specific to the \COMPONENT_A3D_API entities such as geometries, parts, and representation items. 
@{
*/
/*!
@} <!-- end of a3d_types_def -->
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

/* These are compiler-specific */
#ifndef _MSC_VER
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
#	include <string.h>
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
\defgroup a3d_entitytypes_def Entity Type Definitions
\ingroup a3d_types_def
This section describes the entity types used for the PRC entities defined in the \REF_PRC_SPEC.
Every type corresponds to a unique entry in the \ref A3DEEntityType enumerator.
The types are grouped into the following modules in this reference (the \COMPONENT_A3D_API_REF). 
\li Root types
\li Structure
\li Geometry
\li Topology
\li Tessellation
\li Markup
\li Texture
\li Graphics
\li Miscellaneous data

\sa a3d_types_enum
*/

/*!
\defgroup a3d_types_enum Entity Constants
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
#define kA3DTypeRoot						0									/*!< This type does not correspond to any entity. */
#define kA3DTypeCrv							( kA3DTypeRoot +  10 )				/*!< Types for PRC geometrical curves. \sa a3d_crv */
#define kA3DTypeSurf						( kA3DTypeRoot +  75 )				/*!< Types for PRC geometrical surfaces. \sa a3d_srf */
#define kA3DTypeTopo						( kA3DTypeRoot + 140 )				/*!< Types for PRC topology. \sa a3d_topology_module */
#define kA3DTypeTess						( kA3DTypeRoot + 170 )				/*!< Types for PRC tessellation. \sa a3d_tessellation_module */
#define kA3DTypeMisc						( kA3DTypeRoot + 200 )				/*!< Types for PRC miscellaneous data. */
#define kA3DTypeRi							( kA3DTypeRoot + 230 )				/*!< Types for PRC representation items. \sa a3d_geometry_module */
#define kA3DTypeAsm							( kA3DTypeRoot + 300 )				/*!< Types for PRC assembly. \sa a3d_structure_module */
#define kA3DTypeMkp							( kA3DTypeRoot + 500 )				/*!< Types for PRC markup. */
#define kA3DTypeGraph						( kA3DTypeRoot + 700 )				/*!< Types for PRC graphics. */
#define kA3DTypeMath						( kA3DTypeRoot + 900 )				/*!< Types for PRC mathematical operators. */
#define kA3DTypeDrawing						( kA3DTypeRoot + 1300 )				/*!< Types for PRC drawing. \sa a3d_drawing_module */
#define kA3DTypeAdditionalPrcData			( kA3DTypeRoot + 10000 )			/*!< Types for PRC user data. */
#define kA3DTypeNonePRCData					( kA3DTypeAdditionalPrcData + 1000 )/*!< Types for PRC user data. */
#define kA3DTypeMD							( kA3DTypeAdditionalPrcData + 100 )	/*!< Types for PRC markup with definition. */

/*!
\brief Enumerations for Entity Types
This enumeration defines a unique type for each PRC entity defined in the \REF_PRC_SPEC.
\version 2.0

*/
typedef enum 
{
	kA3DTypeUnknown								= -1,

	kA3DTypeRootBase							= kA3DTypeRoot + 1,		/*!< Abstract root type for any PRC entity. */
	kA3DTypeRootBaseWithGraphics				= kA3DTypeRoot + 2,		/*!< Abstract root type for any PRC entity that can bear graphics. */

	kA3DTypeTopoContext							= kA3DTypeTopo + 1,		/*!< Self-containing set of topological entities. */
	kA3DTypeTopoItem							= kA3DTypeTopo + 2,		/*!< Abstract root type for any topological entity (body or single item). */
	kA3DTypeTopoMultipleVertex					= kA3DTypeTopo + 3,		/*!< Vertex whose position is the average of all edges' extremity positions to whom it belongs. \sa a3d_multiple_vertex */
	kA3DTypeTopoUniqueVertex					= kA3DTypeTopo + 4,		/*!< Vertex with one set of coordinates (absolute position). \sa a3d_unique_vertex */
	kA3DTypeTopoWireEdge						= kA3DTypeTopo + 5,		/*!< Edge belonging to a wire body. */
	kA3DTypeTopoEdge							= kA3DTypeTopo + 6,		/*!< Edge belonging to a BrepData body. \sa a3d_edge */
	kA3DTypeTopoCoEdge							= kA3DTypeTopo + 7,		/*!< Usage of an edge in a loop. \sa a3d_coedge */
	kA3DTypeTopoLoop							= kA3DTypeTopo + 8,		/*!< Array of co-edges that delimit a face. \sa a3d_loop */
	kA3DTypeTopoFace							= kA3DTypeTopo + 9,		/*!< Topological face delimiting a shell. \sa a3d_face */
	kA3DTypeTopoShell							= kA3DTypeTopo + 10,	/*!< Topological shell (open or closed). \sa a3d_shell */
	kA3DTypeTopoConnex							= kA3DTypeTopo + 11,	/*!< Topological region. \sa a3d_connex */
	kA3DTypeTopoBody							= kA3DTypeTopo + 12,	/*!< Abstract root type for any topological body. */
	kA3DTypeTopoSingleWireBody					= kA3DTypeTopo + 13,	/*!< Single wire body. */
	kA3DTypeTopoBrepData						= kA3DTypeTopo + 14,	/*!< Main entry to non-wire topology. \sa a3d_topology_module */
	kA3DTypeTopoWireBody						= kA3DTypeTopo + 17,	/*!< Main entry to wire topology. */

	kA3DTypeTessBase							= kA3DTypeTess + 1,		/*!< Abstract root type for any tessellated entity. */
	kA3DTypeTess3D								= kA3DTypeTess + 2,		/*!< Tessellated faceted data; regular form. \sa a3d_tessellation_module */
	kA3DTypeTessFace							= kA3DTypeTess + 4,		/*!< Tessellated face. \sa a3d_tessface */
	kA3DTypeTess3DWire							= kA3DTypeTess + 5,		/*!< Tessellated wireframe. \sa a3d_tess3dwire */
	kA3DTypeTessMarkup							= kA3DTypeTess + 6,		/*!< Tessellated markup. \sa a3d_tessmarkup */

	kA3DTypeMiscAttribute						= kA3DTypeMisc + 1,		/*!< Entity attribute. \sa a3d_attribute */
	kA3DTypeMiscCartesianTransformation			= kA3DTypeMisc + 2,		/*!< Cartesian transformation. */
	kA3DTypeMiscEntityReference					= kA3DTypeMisc + 3,		/*!< Entity reference. Used to overwrite properties of referenced entities. */
	kA3DTypeMiscMarkupLinkedItem				= kA3DTypeMisc + 4,		/*!< Link between a markup and an entity. */

	kA3DTypeMiscReferenceOnTopology   			= kA3DTypeMisc + 6,		/*!< Reference pointing on a topological entity. */
	kA3DTypeMiscGeneralTransformation			= kA3DTypeMisc + 7,		/*!< General transformation. This type allows for storage of any kind of transformation. */
	kA3DTypeMiscReferenceOnCsysItem   			= kA3DTypeMisc + 8,		/*!< Reference pointing on a coordinate sub-component entity. */
	kA3DTypeMiscPKMapper						= kA3DTypeMisc + 9,		/*!< Mapper between A3DEntities and PK entities. */

	kA3DTypeRiRepresentationItem				= kA3DTypeRi + 1,		/*!< Basic abstract type for representation items. */
	kA3DTypeRiBrepModel							= kA3DTypeRi + 2,		/*!< Basic type for surfaces and solids. */
	kA3DTypeRiCurve								= kA3DTypeRi + 3,		/*!< Basic type for curves. */
	kA3DTypeRiDirection							= kA3DTypeRi + 4,		/*!< Optional point + vector. */
	kA3DTypeRiPlane								= kA3DTypeRi + 5,		/*!< Construction plane (Do not confuse this type with the plane surface geometry type \c kA3DTypeSrfPlane.) */
	kA3DTypeRiPointSet							= kA3DTypeRi + 6,		/*!< Set of points. \sa A3DRiPointSetData */
	kA3DTypeRiPolyBrepModel						= kA3DTypeRi + 7,		/*!< Basic type to polyhedral surfaces and solids. */
	kA3DTypeRiPolyWire							= kA3DTypeRi + 8,		/*!< Polyedric wireframe entity. */
	kA3DTypeRiSet								= kA3DTypeRi + 9,		/*!< Logical grouping of arbitrary number of representation items. \sa a3d_riset */
	kA3DTypeRiCoordinateSystem					= kA3DTypeRi + 10,		/*!< Coordinate system. */
	kA3DTypeRiCoordinateSystemItem				= kA3DTypeRi + 11,		/*!< Coordinate system sub-component. */

	kA3DTypeAsmModelFile						= kA3DTypeAsm + 1,		/*!< Basic entry type for PRC. \sa a3d_modelfile */

	kA3DTypeAsmProductOccurrence				= kA3DTypeAsm + 10,		/*!< Basic construction for assemblies. \sa a3d_productoccurrence */
	kA3DTypeAsmPartDefinition					= kA3DTypeAsm + 11,		/*!< Basic construction for parts. \sa a3d_partdefinition */
	kA3DTypeAsmFilter							= kA3DTypeAsm + 20,		/*!< Entities filtering. */

	kA3DTypeMkpView								= kA3DTypeMkp + 1,		/*!< Grouping of markup by views. \sa a3d_annots_view */
	kA3DTypeMkpMarkup							= kA3DTypeMkp + 2,		/*!< Basic type for simple markups. \sa a3d_markup_module */
	kA3DTypeMkpLeader							= kA3DTypeMkp + 3,		/*!< Basic type for markup leader. \sa a3d_markupleader */
	kA3DTypeMkpAnnotationItem					= kA3DTypeMkp + 4,		/*!< Usage of a markup in a logical group. \sa a3d_annotationitem */
	kA3DTypeMkpAnnotationSet					= kA3DTypeMkp + 5,		/*!< Group of annotations. \sa a3d_annotationset */
	kA3DTypeMkpAnnotationReference				= kA3DTypeMkp + 6,		/*!< Logical group of annotations. \sa a3d_annotationreference */

	kA3DTypeMDPosition3D						= kA3DTypeMD + 1,		/*!< Markup position 2D. \sa a3d_markupposition */
	kA3DTypeMDPosition2D						= kA3DTypeMD + 2,		/*!< Markup position 3D. \sa a3d_markupposition */
	kA3DTypeMDPositionReference					= kA3DTypeMD + 3,		/*!< Markup position reference. \sa a3d_markupposition */
	kA3DTypeMDLeaderSymbol						= kA3DTypeMD + 4,		/*!< Markup leader symbol. \sa a3d_markupleaderdefinition */
	kA3DTypeMDTextProperties					= kA3DTypeMD + 5,		/*!< Markup text properties. \sa a3d_markupdefinition_module */
	kA3DTypeMDTextPosition						= kA3DTypeMD + 6,		/*!< Markup text position. \sa a3d_markuptext */
	kA3DTypeMDLeaderDefinition					= kA3DTypeMD + 7,		/*!< Definition of leader. \sa a3d_markupleaderdefinition */
	kA3DTypeMDMarkupLeaderStub					= kA3DTypeMD + 8,		/*!< Definition of leader stub. \sa a3d_markupleaderdefinition */

	kA3DTypeMarkupText							= kA3DTypeMD + 11,		/*!< Definition of markup text. \sa a3d_markuptext */
	kA3DTypeMarkupRichText						= kA3DTypeMD + 12,		/*!< Definition of markup rich text. \sa a3d_markuprichtext */
	kA3DTypeMarkupCoordinate					= kA3DTypeMD + 13,		/*!< Definition of markup coordinate note. \sa a3d_markupcoordinate */
	kA3DTypeMarkupBalloon						= kA3DTypeMD + 14,		/*!< Definition of markup balloon. \sa a3d_markupballoon */
	kA3DTypeMarkupDatum							= kA3DTypeMD + 15,		/*!< Definition of markup datum. \sa a3d_markupdatum */
	kA3DTypeMarkupGDT							= kA3DTypeMD + 16,		/*!< Definition of markup geometrical and dimensioning tolerance. \sa a3d_markupgdt */
	kA3DTypeMarkupRoughness						= kA3DTypeMD + 17,		/*!< Definition of markup roughness. \sa a3d_markuproughness */
	kA3DTypeMarkupDimension						= kA3DTypeMD + 18,		/*!< Definition of markup dimension. \sa a3d_markupdimension */
	kA3DTypeMarkupLocator						= kA3DTypeMD + 19,		/*!< Definition of markup locator. \sa a3d_markuplocator */
	kA3DTypeMarkupMeasurementPoint				= kA3DTypeMD + 20,		/*!< Definition of markup measurement point. \sa a3d_markupmeasurementpoint */
	kA3DTypeMarkupFastener						= kA3DTypeMD + 21,		/*!< Definition of markup fastener. \sa a3d_markupfastener */
	kA3DTypeMarkupSpotWelding					= kA3DTypeMD + 22,		/*!< Definition of markup spot welding. \sa a3d_markupwelding */
	kA3DTypeMarkupLineWelding					= kA3DTypeMD + 23,		/*!< Definition of markup line welding. \sa a3d_markupwelding */

	kA3DTypeMDDimensionValue					= kA3DTypeMD + 30,		/*!< Dimension value. \sa a3d_markupdimension */
	kA3DTypeMDDimensionToleranceFormat			= kA3DTypeMD + 31,		/*!< Basic abstract type of tolerance format of markup dimension. */
	kA3DTypeMDDimensionSimpleToleranceFormat	= kA3DTypeMD + 32,		/*!< Simple tolerance format of markup dimension. \sa a3d_markupdimensionvalue */
	kA3DTypeMDDimensionCombinedToleranceFormat	= kA3DTypeMD + 33,		/*!< Combined tolerance format of markup dimension. \sa a3d_markupdimensionvalue */
	kA3DTypeMDDimensionValueFormat				= kA3DTypeMD + 34,		/*!< Value format of markup dimension. \sa a3d_markupdimensionvalue */
	kA3DTypeMDDimensionFunnel					= kA3DTypeMD + 35,		/*!< Dimension funnel. \sa a3d_markupdimension */
	kA3DTypeMDDimensionExtentionLine			= kA3DTypeMD + 36,		/*!< Dimension extension line. \sa a3d_markupdimension */
	kA3DTypeMDDimensionLineSymbol				= kA3DTypeMD + 37,		/*!< Dimension line symbol. \sa a3d_markupdimension */
	kA3DTypeMDDimensionLine						= kA3DTypeMD + 38,		/*!< Dimension line. \sa a3d_markupdimension */
	kA3DTypeMDDimensionSecondPart				= kA3DTypeMD + 39,		/*!< Dimension second part. \sa a3d_markupdimension */

	kA3DTypeMDFeatureControlFrame				= kA3DTypeMD + 40,		/*!< Feature control frame. \sa a3d_markupdatum */
	kA3DTypeMDFCFRow							= kA3DTypeMD + 41,		/*!< Basic abstract type of feature control frame row. */
	kA3DTypeMDFCFDrawingRow						= kA3DTypeMD + 42,		/*!< Drawing row of feature control frame. \sa a3d_markupgdt */
	kA3DTypeMDFCFDraftingRow					= kA3DTypeMD + 43,		/*!< Drafting row of feature control frame. \sa a3d_markupgdt */
	kA3DTypeMDFCFRowDatum						= kA3DTypeMD + 44,		/*!< Datum of Drawing row. \sa a3d_markupgdt */


	kA3DTypeGraphStyle							= kA3DTypeGraph + 1,	/*!< This type gathers all the information to configure the display style of every entity: color/material/texture, line pattern, fill pattern... */
	kA3DTypeGraphMaterial						= kA3DTypeGraph + 2,	/*!< Basic material definition with colors and alpha. */
	kA3DTypeGraphPicture						= kA3DTypeGraph + 3,	/*!< Picture. */
	kA3DTypeGraphTextureApplication				= kA3DTypeGraph + 11,	/*!< Defines a set of textures to apply. */
	kA3DTypeGraphTextureDefinition				= kA3DTypeGraph + 12,	/*!< Defines a single texture set of parameters to be used in a texture application. */
	kA3DTypeGraphTextureTransformation			= kA3DTypeGraph + 13,	/*!< Texture transformation. */
	kA3DTypeGraphLinePattern					= kA3DTypeGraph + 21,	/*!< One dimensional display style. \sa A3DGraphLinePatternData */
	kA3DTypeGraphFillPattern					= kA3DTypeGraph + 22,	/*!< Abstract class for two-dimensional display style. One of the four *Pattern types. */
	kA3DTypeGraphDottingPattern					= kA3DTypeGraph + 23,	/*!< Two-dimensional filling with dots. */
	kA3DTypeGraphHatchingPattern				= kA3DTypeGraph + 24,	/*!< Two-dimensional filling with hatches. */
	kA3DTypeGraphSolidPattern					= kA3DTypeGraph + 25,	/*!< Two-dimensional filling with particular style (color, material, texture). */
	kA3DTypeGraphVPicturePattern				= kA3DTypeGraph + 26,	/*!< Two-dimensional filling with vectorized picture. \sa A3DPictureData */
	kA3DTypeGraphAmbientLight					= kA3DTypeGraph + 31,	/*!< Scene ambient illumination. */
	kA3DTypeGraphPointLight						= kA3DTypeGraph + 32,	/*!< Scene point illumination. */
	kA3DTypeGraphDirectionalLight				= kA3DTypeGraph + 33,	/*!< Scene directional illumination. */
	kA3DTypeGraphSpotLight						= kA3DTypeGraph + 34,	/*!< Scene spot illumination. */
	kA3DTypeGraphSceneDisplayParameters			= kA3DTypeGraph + 41,	/*!< Parameters for scene visualization. */
	kA3DTypeGraphCamera							= kA3DTypeGraph + 42,	/*!< Camera. */

	kA3DTypeCrvBase								= kA3DTypeCrv + 1,		/*!< Abstract type for all geometric curves. */
	kA3DTypeCrvBlend02Boundary					= kA3DTypeCrv + 2,		/*!< Blend02Boundary curve. \sa a3d_crvboundary */
	kA3DTypeCrvNurbs							= kA3DTypeCrv + 3,		/*!< NURBS curve. \sa a3d_crvnurbs */
	kA3DTypeCrvCircle							= kA3DTypeCrv + 4,		/*!< Circle. \sa a3d_crvcircle */
	kA3DTypeCrvComposite						= kA3DTypeCrv + 5,		/*!< Array of oriented curves. \sa a3d_crvcomposite */
	kA3DTypeCrvOnSurf							= kA3DTypeCrv + 6,		/*!< Curve defined by a UV curve on a surface. \sa a3d_crvonsurf */
	kA3DTypeCrvEllipse							= kA3DTypeCrv + 7,		/*!< Ellipse. \sa a3d_crvellipse */
	kA3DTypeCrvEquation							= kA3DTypeCrv + 8,		/*!< Curve described by specific equation elements. \sa a3d_crvequation */
	kA3DTypeCrvHelix							= kA3DTypeCrv + 9,		/*!< Helix. \sa a3d_crvhelix */
	kA3DTypeCrvHyperbola						= kA3DTypeCrv + 10,		/*!< Hyperbola. \sa a3d_crvhyperbola */
	kA3DTypeCrvIntersection						= kA3DTypeCrv + 11,		/*!< Intersection between two surfaces. \sa a3d_crvintersection */
	kA3DTypeCrvLine								= kA3DTypeCrv + 12,		/*!< Line curve. \sa a3d_crvline */
	kA3DTypeCrvOffset							= kA3DTypeCrv + 13,		/*!< Offset curve. \sa a3d_crvoffset */
	kA3DTypeCrvParabola							= kA3DTypeCrv + 14,		/*!< Parabola. \sa a3d_crvparabola */
	kA3DTypeCrvPolyLine							= kA3DTypeCrv + 15,		/*!< Polyedric curve. \sa a3d_crvpolyline */
	kA3DTypeCrvTransform						= kA3DTypeCrv + 16,		/*!< Transformed curve. \sa a3d_crvtransform */

	kA3DTypeSurfBase							= kA3DTypeSurf + 1,		/*!< Abstract type for all geometric surfaces. */
	kA3DTypeSurfBlend01							= kA3DTypeSurf + 2,		/*!< Blend type 1. */
	kA3DTypeSurfBlend02							= kA3DTypeSurf + 3,		/*!< Blend type 2. */
	kA3DTypeSurfBlend03							= kA3DTypeSurf + 4,		/*!< Blend type 3. */
	kA3DTypeSurfNurbs							= kA3DTypeSurf + 5,		/*!< NURBS surface. */
	kA3DTypeSurfCone							= kA3DTypeSurf + 6,		/*!< Conical surface. */
	kA3DTypeSurfCylinder						= kA3DTypeSurf + 7,		/*!< Cylindrical surface. */
	kA3DTypeSurfCylindrical						= kA3DTypeSurf + 8,		/*!< Surface that is defined in cylindrical space. */
	kA3DTypeSurfOffset							= kA3DTypeSurf + 9,		/*!< Offset surface. */
	kA3DTypeSurfPipe							= kA3DTypeSurf + 10,	/*!< Pipe. */
	kA3DTypeSurfPlane							= kA3DTypeSurf + 11,	/*!< Plane. */
	kA3DTypeSurfRuled							= kA3DTypeSurf + 12,	/*!< Ruled surface. */
	kA3DTypeSurfSphere							= kA3DTypeSurf + 13,	/*!< Sphere. */
	kA3DTypeSurfRevolution						= kA3DTypeSurf + 14,	/*!< Surface of revolution. */
	kA3DTypeSurfExtrusion						= kA3DTypeSurf + 15,	/*!< Surface of extrusion. */
	kA3DTypeSurfFromCurves						= kA3DTypeSurf + 16,	/*!< Surface build from curves. */
	kA3DTypeSurfTorus							= kA3DTypeSurf + 17,	/*!< Torus. */
	kA3DTypeSurfTransform						= kA3DTypeSurf + 18,	/*!< Transformed surface. */
	kA3DTypeSurfBlend04							= kA3DTypeSurf + 19,	/*!< Defined for future use. */

	kA3DTypeMathFct1D							= kA3DTypeMath + 1,		/*!< Basic type for first-degree equation object. */
	kA3DTypeMathFct1DPolynom					= kA3DTypeMathFct1D + 1,/*!< Polynomial equation. */
	kA3DTypeMathFct1DTrigonometric				= kA3DTypeMathFct1D + 2,/*!< Cosine-based equation. */
	kA3DTypeMathFct1DFraction					= kA3DTypeMathFct1D + 3,/*!< Fraction between two first-degree equation objects. */
	kA3DTypeMathFct1DArctanCos					= kA3DTypeMathFct1D + 4,/*!< Specific equation. */
	kA3DTypeMathFct1DCombination				= kA3DTypeMathFct1D + 5,/*!< Combination of first-degree equation object. */
	kA3DTypeMathFct3D							= kA3DTypeMath + 10,	/*!< Basic type for third-degree equation object. */
	kA3DTypeMathFct3DLinear						= kA3DTypeMathFct3D + 1,/*!< Linear transformation (with a matrix). */
	kA3DTypeMathFct3DNonLinear					= kA3DTypeMathFct3D + 2,/*!< Specific transformation. */

	kA3DTypeDrawingModel						= kA3DTypeDrawing + 1,	/*!< Drawing model. */
	kA3DTypeDrawingSheet						= kA3DTypeDrawing + 2,	/*!< Drawing sheet. */
	kA3DTypeDrawingSheetFormat					= kA3DTypeDrawing + 3,	/*!< Drawing sheet format. */
	kA3DTypeDrawingView							= kA3DTypeDrawing + 4,	/*!< Drawing view. */
	kA3DTypeDrawingClipFrame					= kA3DTypeDrawing + 5,	/*!< Drawing clip frame. */
	kA3DTypeDrawingBlock						= kA3DTypeDrawing + 6,	/*!< Abstract type for drawing block. */
	kA3DTypeDrawingBlockBasic					= kA3DTypeDrawing + 7,	/*!< Drawing block basic. */
	kA3DTypeDrawingBlockOperator				= kA3DTypeDrawing + 8,	/*!< Drawing block operator. */
	kA3DTypeDrawingEntity						= kA3DTypeDrawing + 10,	/*!< Abstract type for drawing graphic entities. */
	kA3DTypeDrawingFilledArea					= kA3DTypeDrawing + 11,	/*!< Drawing filled. */
	kA3DTypeDrawingPicture						= kA3DTypeDrawing + 12,	/*!< Drawing picture. */
	kA3DTypeDrawingVertices						= kA3DTypeDrawing + 13,	/*!< Drawing vertices. */
	kA3DTypeDrawingCurve						= kA3DTypeDrawing + 14	/*!< Drawing curve. */


} A3DEEntityType;
/*!
@} <!-- end of a3d_types_enum -->
*/
/*!
@} <!-- end of a3d_entitytypes_def -->
*/

/*!
\defgroup a3d_root_types Root Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DEntity;					/*!< Root type for any entity. */
typedef void A3DRootBase;				/*!< Root type for any entity with attributes. */
typedef void A3DRootBaseWithGraphics;	/*!< Root type for any entity with attributes and graphics. */
/*!
@} <!-- end of a3d_root_types -->
*/

/*!
\defgroup a3d_structure_types Structure Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DAsmModelFile;			/*!< Model file entity. The top level for accessing entities. \sa a3d_modelfile */
typedef void A3DAsmProductOccurrence;	/*!< Product occurrence. Refer to \ref a3d_structure_module for more details. \sa a3d_productoccurrence */
typedef void A3DAsmPartDefinition;		/*!< Part definition. Refer to \ref a3d_structure_module for more details. \sa a3d_partdefinition */
typedef void A3DAsmFilter;				/*!< Filter. Refer to \ref a3d_filter for more details. */
/*!
@} <!-- end of a3d_structure_types -->
*/
/*!
\defgroup a3d_repitems_types Representation Item Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DRiRepresentationItem;	/*!< Representation item entity. Refer to \ref a3d_structure_module for more details. \sa a3d_repitem */
typedef void A3DRiBrepModel;			/*!< Solid/surface model as representation item. \sa a3d_ribrepmodel, a3d_topology_module */
typedef void A3DRiCurve;				/*!< Curve as representation item. \sa a3d_ricurve */
typedef void A3DRiDirection;			/*!< Direction representation item. \sa a3d_ridirection */
typedef void A3DRiPlane;				/*!< Plane as representation item. \sa a3d_riplane */
typedef void A3DRiPointSet;				/*!< Set of 3D points. \sa a3d_ripointset */
typedef void A3DRiPolyBrepModel;		/*!< Faceted model as representation item. \sa a3d_ripolybrepmodel, a3d_topology_module */
typedef void A3DRiPolyWire;				/*!< Wireframe model as representation item. \sa a3d_ripolywire, a3d_topology_module */
typedef void A3DRiSet;					/*!< Set of representation item entities. \sa a3d_riset */
typedef void A3DRiCoordinateSystem;		/*!< Coordinate system representation item. \sa a3d_ricoordinatesystem */
/*!
@} <!-- end of a3d_repitems_types -->
*/

/*!
\defgroup a3d_geometry_types Geometry Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

In general, each curve and surface has a parametric function that describes its minimal natural definition.

<ul>
	<li>Curves have a parametric function that takes a single argument,
		\c Parameter), which is a real number. The result of the \c PointOnCurve function  
		is a 3D cartesian point represented by three real numbers.

		<CODE> PointOnCurve = F(Parameter) </CODE>

		For example, the following parametric function provides the minimal natural definition of a circle
		on the Z=0 plane, centered in (0,0,0), and having the radius: \c R. 
	
		<CODE> X = Radius * cos(Parameter), Y = R * sin(Parameter), Z = 0  </CODE>
	</li>

	<li>Surfaces have a parametric function that takes two arguments,
		\c Parameter_U and \c Parameter_V, which are real numbers. 
		The result of the function (\c PointOnSurface) is a 3D cartesian point represented by three real numbers.

		<CODE> PointOnSurface = F(Parameter_U, Parameter_V) </CODE>

		For example, the following parametric function provides the minimal natural definition of the Z=0 plane:
		
		<CODE> X = Parameter_U, Y = Parameter_V, Z = 0 </CODE>
	</li>
</ul>

To represent other circles and planes, the following items are sequentially applied to each curve and surface
(except for NURBS curves and NURBS surfaces):
<ol>
	<li>Trim </li>
	<li>Parametric transformation (an affine function) </li>
	<li>Cartesian transformation</li>
</ol>

For example, the following equation shows the application of these modifications:

<CODE>PointOnCurve = CartesianTransformation( F(CoefA * Parameter + CoefB) ) </CODE>

Where the equation components have the following characteristics:
\li \c Parameter value is bounded by two real numbers as follows: <CODE>IntervalMin <= Parameter <= IntervalMax</CODE>.
\li \c CoefA and \c CoefB are real numbers that define the affine function (the parametric transformation).
\li \c CartesianTransformation is a spatial transformation.
@{
*/
/*!
@} <!-- end of a3d_geometry_types -->
*/


/*!
\defgroup a3d_curves_type Curve Type Declarations
\ingroup a3d_geometry_types
\version 2.0

@{
*/
typedef void A3DCrvBase;			/*!< Abstract type for a geometric curve. \sa a3d_crv */
typedef void A3DCrvBlend02Boundary;	/*!< Blend02Boundary curve. \sa a3d_crvboundary */
typedef void A3DCrvNurbs;			/*!< NURBS curve. \sa a3d_crvnurbs */
typedef void A3DCrvCircle;			/*!< Circular curve. \sa a3d_crvcircle */
typedef void A3DCrvComposite;		/*!< Composite curve. \sa a3d_crvcomposite */
typedef void A3DCrvOnSurf;			/*!< On-surface curve. \sa a3d_crvonsurf */
typedef void A3DCrvEllipse;			/*!< Elliptic curve. \sa a3d_crvellipse */
typedef void A3DCrvEquation;		/*!< Equation curve. \sa a3d_crvequation */
typedef void A3DCrvHelix;			/*!< Helical curve. \sa a3d_crvhelix */
typedef void A3DCrvHyperbola;		/*!< Hyperbolic curve. \sa a3d_crvhyperbola */
typedef void A3DCrvIntersection;	/*!< Intersection curve. \sa a3d_crvintersection */
typedef void A3DCrvLine;			/*!< Linear curve. \sa a3d_crvline */
typedef void A3DCrvOffset;			/*!< Offset curve. \sa a3d_crvoffset */
typedef void A3DCrvParabola;		/*!< Parabolic curve. \sa a3d_crvparabola */
typedef void A3DCrvPolyLine;		/*!< Polygonal curve. \sa a3d_crvpolyline */
typedef void A3DCrvTransform;		/*!< Transform curve. \sa a3d_crvtransform */
/*!
@} <!-- end of a3d_curves_type -->
*/

/*!
\defgroup a3d_surfaces_type Surface Type Declarations
\ingroup a3d_geometry_types
\version 2.0

@{
*/
typedef void A3DSurfBase;			/*!< Abstract type for a Surface. \sa a3d_srf */
typedef void A3DSurfBlend01;		/*!< Surface for blend type 1. \sa a3d_srfblend01 */
typedef void A3DSurfBlend02;		/*!< Surface for blend type 2. \sa a3d_srfblend02 */
typedef void A3DSurfBlend03;		/*!< Surface for blend type 3. \sa a3d_srfblend03 */
typedef void A3DSurfNurbs;			/*!< NURBS surface. \sa a3d_srfnurbs */
typedef void A3DSurfCone;			/*!< Conical surface. \sa a3d_srfcone */
typedef void A3DSurfCylinder;		/*!< Cylindrical surface. \sa a3d_srfcylinder */
typedef void A3DSurfCylindrical;	/*!< Cylindrical surface. \sa a3d_srfcylindrical */
typedef void A3DSurfOffset;			/*!< Offset surface. \sa a3d_srfoffset */
typedef void A3DSurfPipe;			/*!< Pipe surface. \sa a3d_srfpipe */
typedef void A3DSurfPlane;			/*!< Planar surface. \sa a3d_srfplane */
typedef void A3DSurfRuled;			/*!< Ruled surface. \sa a3d_srfruled */
typedef void A3DSurfSphere;			/*!< Spherical surface. \sa a3d_srfsphere */
typedef void A3DSurfRevolution;		/*!< Surface of revolution. \sa a3d_srfrevolution */
typedef void A3DSurfExtrusion;		/*!< Surface of extrusion. \sa a3d_srfextrusion */
typedef void A3DSurfFromCurves;		/*!< Surface from curves. \sa a3d_srffromcurves */
typedef void A3DSurfTorus;			/*!< Toric surface. \sa a3d_srftorus */
typedef void A3DSurfTransform;		/*!< Transform surface. \sa a3d_srftransform */
typedef void A3DSurfBlend04;		/*!< Surface for blend type 4. \sa a3d_srfblend04 */
/*!
@} <!-- end of a3d_surfaces_type -->
*/

/*!
\defgroup a3d_math_types Mathematical Operator Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DMathFct1D;				/*!< Basic type for first-degree equation object. \sa a3d_maths */
typedef void A3DMathFct1DPolynom;		/*!< Type for a polynomial object. \sa a3d_maths */
typedef void A3DMathFct1DTrigonometric;	/*!< Type for a cosine-based equation object. \sa a3d_maths */
typedef void A3DMathFct1DFraction;		/*!< Type for an object representing linear combination of other equations. \sa a3d_maths */
typedef void A3DMathFct1DArctanCos;		/*!< Type for an arctangent-based equation object. \sa a3d_maths */
typedef void A3DMathFct1DCombination;	/*!< Type for an object representing weighted combinations of other equations. \sa a3d_maths */
typedef void A3DMathFct3D;				/*!< Basic type for third-degree equation object. \sa a3d_maths */
typedef void A3DMathFct3DLinear;		/*!< Type for an object representing linear equations for 3x1 matrices. \sa a3d_maths */
typedef void A3DMathFct3DNonLinear;		/*!< Type for an object representing trigonometric equations for 3x1 matrices. \sa a3d_maths */
/*!
@} <!-- end of a3d_math_types -->
*/

/*!
\defgroup a3d_topology_types Topology Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DTopoContext;				/*!< Topological context. \sa a3d_context */
typedef void A3DTopoItem;					/*!< Abstract root type for any topological entity (body or single item). */
typedef void A3DTopoVertex;					/*!< Vertex. One of the two following types. */
typedef void A3DTopoMultipleVertex;			/*!< Vertex. \sa a3d_multiple_vertex */
typedef void A3DTopoUniqueVertex;			/*!< Vertex. \sa a3d_unique_vertex */
typedef void A3DTopoWireEdge;				/*!< Wire Edge. \sa a3d_wireedge */
typedef void A3DTopoEdge;					/*!< Edge. \sa a3d_edge */
typedef void A3DTopoCoEdge;					/*!< Co-Edge. \sa a3d_coedge */
typedef void A3DTopoLoop;					/*!< Loop. \sa a3d_loop */
typedef void A3DTopoFace;					/*!< Face. \sa a3d_face */
typedef void A3DTopoShell;					/*!< Shell. \sa a3d_shell */
typedef void A3DTopoConnex;					/*!< Connex. \sa a3d_connex */
typedef void A3DTopoBody;					/*!< Abstract root type for any topological body. */
typedef void A3DTopoSingleWireBody;			/*!< Single wire body. \sa a3d_singlewirebody */
typedef void A3DTopoBrepData;				/*!< Main entry to solid and surface topology (regular form). \sa a3d_brepdata */

/*!
@} <!-- end of a3d_topology_types -->
*/

/*!
\defgroup a3d_tessellation_types Tessellation Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DTessBase;		/*!< Generic type for all kind of tessellations. \sa a3d_tessellation_module */
typedef void A3DTess3D;			/*!< Tessellation type for solids/surfaces. \sa a3d_tess3d */
typedef void A3DTess3DWire;		/*!< Tessellation type for wire bodies. \sa a3d_tess3dwire */
typedef void A3DTessMarkup;		/*!< Tessellation type for markups. \sa a3d_tessmarkup */
/*!
@} <!-- end of a3d_tessellation_types -->
*/

/*!
\defgroup a3d_markup_types Markup Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DMkpView;				/*!< Grouping of markup by views. Refer to \ref a3d_markup_module for more details. \sa a3d_annots_view */
typedef void A3DMkpMarkup;				/*!< Definition of a markup. May contain tessellation. \sa a3d_markup_module */
typedef void A3DMkpLeader;				/*!< Definition of a markup leader. May contain tessellation. \sa a3d_markupleader */
typedef void A3DMkpAnnotationEntity;	/*!< Abstract type for an Annotation entity (three types below). Refer to \ref a3d_markup_module for more details. \sa a3d_annotationentity */
typedef void A3DMkpAnnotationItem;		/*!< Usage of a markup. An annotation item references a single markup.
											A single markup can be referenced by multiple annotations. \sa a3d_annotationitem */
typedef void A3DMkpAnnotationSet;		/*!< Group of annotations. 
											An annotation set is a group of annotation items or other annotation sets. 
											For instance, an \ref A3DMkpView entity contains a set of markups associated with a plane. 
											In another example, a tolerance can be a set containing a datum, a feature control frame, 
											and a dimension. \sa a3d_annotationset */
typedef void A3DMkpAnnotationReference;	/*!< Logical grouping of annotations for reference. An annotation reference is a set of references on other markups. It is mainly used as a combination of datum with modifiers. \sa a3d_annotationreference */
/*!
@} <!-- end of a3d_markup_types -->
*/

/*!
\defgroup a3d_markupdefinitiontype_module Markup Definition Type Declarations
\ingroup a3d_markup_types
\version 4.0

@{
*/
typedef void A3DMarkupDefinition;		/*!< Abstract type for a markup with definition (13 types below). Refer to \ref a3d_markupdefinition_module for more details. */
typedef void A3DMarkupText;				/*!< Definition of a markup simple text. Refer to \ref a3d_markuptext for more details. */
typedef void A3DMarkupCoordinate;		/*!< Definition of a markup note coordinate.Refer to \ref a3d_markuptext for more details. */
typedef void A3DMarkupRichText;			/*!< Definition of a markup rich text. Refer to \ref a3d_markuptext for more details. */
typedef void A3DMarkupDatum;			/*!< Definition of a markup indent/target. Refer to \ref a3d_markuptolerance for more details. */
typedef void A3DMarkupGDT;				/*!< Definition of a markup geometrical and dimensioning tolerance. Refer to \ref a3d_markuptolerance for more details. */
typedef void A3DMarkupDimension;		/*!< Definition of a markup dimension. Refer to \ref a3d_markupdimension for more details. */
typedef void A3DMarkupRoughness;		/*!< Definition of a markup roughness or surface finish. Refer to \ref a3d_markupsymbol for more details. */
typedef void A3DMarkupSpotWelding;		/*!< Definition of a markup spot welding symbol Refer to \ref a3d_markupwelding for more details. */
typedef void A3DMarkupLineWelding;		/*!< Definition of a markup line welding symbol Refer to \ref a3d_markupwelding for more details. */
typedef void A3DMarkupBalloon;			/*!< Definition of a markup balloon. Refer to \ref a3d_markupsymbol for more details. */
typedef void A3DMarkupLocator;			/*!< Definition of a markup locator. Refer to \ref a3d_markupsymbol for more details. */
typedef void A3DMarkupFastener;			/*!< Definition of a markup fastener. Refer to \ref a3d_markupsymbol for more details. */
typedef void A3DMarkupMeasurementPoint;	/*!< Definition of a markup measurement point. Refer to \ref a3d_markupsymbol for more details. */

/*!
@} <!-- end of a3d_markupdefinitiontype_module -->
*/


/*!
\defgroup a3d_markupdefinitiongeneral_module Common Data Type declarations
\ingroup a3d_markupdefinitiontype_module
\version 4.0
@{
*/
typedef void A3DMDLeaderDefinition;				/*!< Definition of a markup leader Refer to \ref a3d_markupleaderdefinition for more details. */
typedef void A3DMDMarkupLeaderStub;				/*!< Definition of a leader stub Refer to \ref a3d_markupleaderdefinition for more details. */
typedef void A3DMDLeaderSymbol;					/*!< Definition of a markup leader symbol. Refer to \ref a3d_markupleaderdefinition for more details. */
typedef void A3DMDPosition;						/*!< Abstract type for a markup position (two types below). Refer to \ref a3d_markupposition  for more details. */
typedef void A3DMDPosition2D;					/*!< Definition of a markup position 2D. Refer to \ref a3d_markupposition for more details. */
typedef void A3DMDPosition3D;					/*!< Definition of a markup position 3D. Refer to \ref a3d_markupposition for more details. */
typedef void A3DMDPositionReference;			/*!< Definition of a markup position reference. Refer to \ref a3d_markupposition for more details. */
typedef void A3DMDTextProperties;				/*!< Definition of a markup text properties. Refer to \ref a3d_markupdefinition_module for more details. */
typedef void A3DMDTextPosition;					/*!< Definition of a position for text of markup text, rich text... Refer to \ref a3d_markuptext for more details. */

/*!
@} <!-- end of a3d_markupdefinitiongeneral_module -->
*/

/*!
\defgroup a3d_markuptolerance_types Type declarations specific to markup GDT
\ingroup a3d_markupdefinitiontype_module
\version 4.0
@{							*/
typedef void A3DMDTolerance;					/*!< Abstract type for tolerance defined in markup GDT (one type below). Refer to \ref a3d_markupgdt for more details. */
typedef void A3DMDFeatureControlFrame;			/*!< Definition of markup GDT tolerance. Refer to \ref a3d_markupgdt for more details. */		
typedef void A3DMDFCFRow;						/*!< Abstract type for feature control frame row (two types below). Refer to \ref a3d_markupfcfrow for more details. */
typedef void A3DMDFCFDrawingRow;				/*!< Definition of control frame row. Refer to \ref a3d_markupfcfrow for more details. */		
typedef void A3DMDFCFDraftingRow;				/*!< Definition of control frame row. Refer to \ref a3d_markupfcfrow for more details. */	
typedef void A3DMDFCFRowDatum;					/*!< Definition of row datum. Refer to \ref a3d_markupfcfrow for more details. */	
typedef void A3DMDFCFToleranceValue;			/*!< Definition of tolerance value. Refer to \ref a3d_markupfcf_semanticrow for more details. */
typedef void A3DMDFCValue;						/*!< Definition of value. Refer to \ref a3d_markupfcf_semanticrow for more details. */
typedef void A3DMDFCTolerancePerUnit;			/*!< Definition of tolerance per unit. Refer to \ref a3d_markupfcf_semanticrow for more details. */
typedef void A3DMDFCProjectedZone;				/*!< Definition of projected tolerance zone. Refer to \ref a3d_markupfcf_semanticrow for more details. */
/*!
@} <!-- end of a3d_markuptolerance_types -->
*/



/*!
\defgroup a3d_markupdimension_types Type declarations specific to markup dimension
\ingroup a3d_markupdefinitiontype_module
\version 4.0
@{
*/

typedef void A3DMDDimensionValue;						/*!< Definition of a dimension value. Refer to \ref a3d_markupdimensionvalue for more details. */
typedef void A3DMDDimensionValueFormat;					/*!< Definition of a format for dimension value. Refer to \ref a3d_markupdimensionvalue for more details. */
typedef void A3DMDDimensionToleranceFormat;				/*!< Abstract type for dimension tolerance format (two types below). Refer to \ref a3d_markupdimensionvalue for more details. */
typedef void A3DMDDimensionSimpleToleranceFormat;		/*!< Definition of a format for dimension tolerance. Refer to \ref a3d_markupdimensionvalue for more details. */
typedef void A3DMDDimensionCombinedToleranceFormat;		/*!< Definition of a format for dimension tolerance. Refer to \ref a3d_markupdimensionvalue for more details. */
typedef void A3DMDDimensionExtentionLine;				/*!< Definition of a extension line. Refer to \ref a3d_markupdimension for more details. */
typedef void A3DMDDimensionExtremity;					/*!< Definition of a extremity of extension line. Refer to \ref a3d_markupdimension for more details. */
typedef void A3DMDDimensionFunnel;						/*!< Definition of a funnel of extension line. Refer to \ref a3d_markupdimension for more details. */
typedef void A3DMDDimensionLine;						/*!< Definition of a dimension line. Refer to \ref a3d_markupdimension for more details. */
typedef void A3DMDDimensionLineSymbol;					/*!< Definition of a symbol for dimension line. Refer to \ref a3d_markupdimension for more details. */
typedef void A3DMDDimensionSecondPart;					/*!< Definition of a second part for dimension line. Refer to \ref a3d_markupdimension for more details. */
typedef void A3DMDDimensionForeshortened;				/*!< Definition of a foreshortened for dimension line. Refer to \ref a3d_markupdimension for more details. */

/*!
@} <!-- end of a3d_markupdimension_types -->
*/


/*!
\defgroup a3d_graphics_types Graphics Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DGraphics;						/*!< Graphics associated to \ref A3DRootBaseWithGraphics. \sa a3d_graphics */
typedef void A3DGraphSceneDisplayParameters;	/*!< Parameters to display a scene; associated to a product occurrence or a view. \sa a3d_productoccurrence */
typedef void A3DGraphCamera;					/*!< Camera. */
typedef void A3DGraphAmbientLight;				/*!< Ambient light. */
typedef void A3DGraphPointLight;				/*!< Point light. */
typedef void A3DGraphSpotLight;					/*!< Spot light. */
typedef void A3DGraphDirectionalLight;			/*!< Directional light. */
/*!
@} <!-- end of a3d_graphics_types -->
*/

/*!
\defgroup a3d_texture_types Texture Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DGraphTextureApplication;		/*!< Defines a set of textures to apply. */
typedef void A3DGraphTextureDefinition;			/*!< Defines a single texture set of parameters to be used in an \ref A3DGraphTextureApplication. */
typedef void A3DGraphTextureTransformation;		/*!< Defines transformation for a texture. */
/*!
@} <!-- end of a3d_texture_types module --> 
*/

/*!
\defgroup a3d_misc_data_types Miscellaneous Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DMiscTransformation;			/*!< Transformation base entity. This entity appears in structure members as a pointer that references 
												either an \ref A3DMiscCartesianTransformation or an \ref A3DMiscGeneralTransformation entity. 
												\sa a3d_misc_trsf */
typedef void A3DMiscAttribute;				/*!< Attributes of an \ref A3DRootBase entity. \sa a3d_attribute */
typedef void A3DMiscCartesianTransformation;/*!< Cartesian transformation where individual types of transformations 
												(scaling, rotation, translation) are selected. \sa a3d_cartesiantransfo3d */
typedef void A3DMiscEntityReference;		/*!< Entity reference. \sa a3d_entity_reference */
typedef void A3DMiscMarkupLinkedItem;		/*!< Link between a markup and an entity. This type allows a logical link 
												between a markup and a pointed entity, which can be geometry or another markup. 
												Conversely to an EntityReference, the pointed entity 
												can be a "remote" entity in another product occurrence, 
												in case where an assembly markup points to a subpart. 
												It can be associated with a leader of the markup. 
												\sa a3d_markuplinkeditem */
typedef void A3DMiscReferenceOnTopology;	/*!< Entity reference on a topological item. \sa a3d_reference_on_topo */
typedef void A3DMiscReferenceOnCsysItem;	/*!< Entity reference on a coordinate system sub-component. \sa a3d_reference_on_topo */
typedef void A3DMiscGeneralTransformation;	/*!< Cartesian transformation that uses a 4x4 matrix. \sa a3d_generaltransfo3d */

typedef void A3DGlobal;						/*!< Global container. Refer to \ref a3d_global_data_module for more details. */

typedef void A3DFaceUVPointInsideManager;	/*!< Manager to classify UV Point in face. */

typedef void A3DProjectPointCloudManager; /*!< Manager to classify 3D points on representation item. */

typedef void A3DRWParamsPrcReadHelper;		/*!< Reserved for future use. */
typedef void A3DRWParamsPrcWriteHelper;		/*!< Reserved for future use. */

/*!
@} <!-- end of a3d_misc_data_types -->
*/

/*!
\defgroup a3d_tools_data_types Tools Type Declarations
\ingroup a3d_entitytypes_def
\version 2.0

@{
*/
typedef void A3DMiscCascadedAttributes; /*!< Inheritable settings for the associated PRC entity 
											such as layer, style, and coordinate system. 
											\sa <a class="el" href="managing_attribute_inheritance.html">Miscellaneous Cascaded Attributes</a> */
typedef void A3DMiscPKMapper; /*!< Topology entities mapper */
/*!

@} <!-- end of a3d_tools_data_types -->
*/


/*!
\defgroup a3d_drawing_type Drawing Type Declarations
\ingroup a3d_entitytypes_def
\version 5.0

@{
*/
typedef void A3DDrawingModel;				/*!< Definition of a drawing model. Refer to \ref a3d_drawing_model for more details. */
typedef void A3DDrawingSheet;				/*!< Definition of a drawing sheet. Refer to \ref a3d_drawing_sheet for more details. */
typedef void A3DDrawingSheetFormat;			/*!< Definition of a drawing sheet format. Refer to \ref a3d_drawing_sheetformat for more details. */
typedef void A3DDrawingClipFrame;			/*!< Definition of a drawing clipping frame. Refer to \ref a3d_drawing_clipframe for more details. */
typedef void A3DDrawingView;				/*!< Definition of a drawing view. Refer to \ref a3d_drawing_view for more details. */
typedef void A3DDrawingBlock;				/*!< Abstract type drawing block. Refer to \ref a3d_drawing_block for more details. */
typedef void A3DDrawingBlockBasic;			/*!< Definition of a drawing basic block. Refer to \ref a3d_drawing_blockbasic for more details. */
typedef void A3DDrawingBlockOperator;		/*!< Definition of a drawing operator block. Refer to \ref a3d_drawing_operator for more details. */
typedef void A3DDrawingEntity;				/*!< Abstract class for drawing entities. Refer to \ref a3d_drawing_entity for more details. */
typedef void A3DDrawingCurve;				/*!< Definition of a drawing curve. Refer to \ref a3d_drawing_curve for more details. */
typedef void A3DDrawingFilledArea;			/*!< Definition of a drawing filled area block. Refer to \ref a3d_drawing_filledarea for more details. */
typedef void A3DDrawingPicture;				/*!< Definition of a drawing picture . Refer to \ref a3d_drawing_picture for more details. */
typedef void A3DDrawingVertices;			/*!< Definition of a drawing vertices. Refer to \ref a3d_drawing_vertices for more details. */

/*!
@} <!-- end of a3d_drawing_type -->
*/

/*!
\defgroup a3d_hlr_type HLR Type Declarations
\ingroup a3d_entitytypes_def
\version 8.2

@{
*/
typedef void A3DHLRRepresentationItem;		/*!<  Definition of a HLR representation item result. Refer to \ref a3d_HLR_Compute for more details. */
/*!
@} <!-- end of a3d_drawing_type -->
*/

#endif	/*	__A3DPRCTYPES_H__ */
