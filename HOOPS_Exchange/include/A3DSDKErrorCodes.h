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

#ifndef __A3DPRCERRORCODES_H__
#define __A3DPRCERRORCODES_H__


/*******************************************************************************
* 
*  ATTRIBUTES/GLOBAL DATA ERROR CODES
* 
*******************************************************************************/

#define A3D_DEFAULT_LAYER							((A3DUns16)-1)		/*!< Default layer. */
#define A3D_DEFAULT_TRANSPARENCY					((A3DUns8)-1)		/*!< Default transparency. */
#define A3D_DEFAULT_LINE_WIDTH						((A3DDouble)0.1)	/*!< Default line width. */

#define A3D_DEFAULT_COLOR_INDEX						((A3DUns32)-1)		/*!< Default color index. */
#define A3D_DEFAULT_PATTERN_INDEX					((A3DUns32)-1)		/*!< Default pattern index. */
#define A3D_DEFAULT_STYLE_INDEX						((A3DUns16)-1)		/*!< Default style index. */

#define A3D_DEFAULT_LINEPATTERN_INDEX				((A3DUns32)-1)		/*!< Default line pattern index. */
#define A3D_DEFAULT_MATERIAL_INDEX					((A3DUns32)-1)		/*!< Default material index. */
#define A3D_DEFAULT_PICTURE_INDEX					((A3DUns32)-1)		/*!< Default picture index. */
#define A3D_DEFAULT_TEXTURE_DEFINITION_INDEX		((A3DUns32)-1)		/*!< Default texture definition index. */
#define A3D_DEFAULT_TEXTURE_APPLICATION_INDEX		((A3DUns32)-1)		/*!< Default texture application index. */


/*******************************************************************************
* 
*  TOPOLOGY ERROR CODES
* 
*******************************************************************************/
#define	A3D_LOOP_UNKNOW_OUTER_INDEX					((A3DUns32)-1)		/*!< Outer loop is unknown. */


/*******************************************************************************
********************************************************************************
* 
*  ERROR CODES
* 
********************************************************************************
*******************************************************************************/

/*!
\brief Error Codes
*/
typedef enum
{
/*******************************************************************************
* 
*  GENERAL ERROR CODES
* 
*******************************************************************************/

	A3D_SUCCESS											=	0,		/*!< Successful return value. */
	A3D_ERROR											=	-1,		/*!< General error. */
	A3D_EXCEPTION										=	-2,		/*!< Caught exception. */
	A3D_ALLOC_FATAL_ERROR								=	-10,	/*!< Allocation has failed. Major error. */
	A3D_NOT_IMPLEMENTED									=	-33,	/*!< Local code, which is not yet implemented. */
	A3D_INVALID_LICENSE									=	-34,	/*!< License option doesn't allowed the requested function. */
	A3D_INCREMENTAL_MODE_AND_MULTI_PROCESS_NOT_COMPATIBLE	=	-11, /*!< The incremental Mode can not be used with the MultiProcess option set to true */

/*******************************************************************************
*
*  MACROS ERROR CODES
*
*******************************************************************************/

	A3D_INVALID_DATA_STRUCT_SIZE						=	-100,	/*!< \ref A3D_INITIALIZE_DATA not called or bad alignment in input struct. */
	A3D_INVALID_DATA_STRUCT_NULL						=	-101,	/*!< Input struct function cannot be NULL. */
	A3D_INVALID_ENTITY_NULL								=	-102,	/*!< Input entity function cannot be NULL. */
	A3D_INVALID_ENTITY_TYPE								=	-103,	/*!< Input entity function is of bad type. */
	A3D_INVALID_DATA									=	-104,	/*!< Input contains bad data. */


/*******************************************************************************
* 
*  BASE ERROR CODES
* 
*******************************************************************************/

	A3D_INITIALIZE_ALREADY_CALLED						=	-200,	/*!< \ref A3DDllInitialize already called; bad sequence with the \ref A3DDllTerminate function. */
	A3D_INITIALIZE_NOT_CALLED							=	-201,	/*!< \ref A3DDllInitialize must be called before calling the \ref A3DDllTerminate function. */
	A3D_INITIALIZE_BAD_VALUES							=	-202,	/*!< Initialization led to bad internal values for globals. Fatal error. Reinitialize program. */
	A3D_INITIALIZE_CANNOT_PROCESS						=	-205,	/*!< Cannot initialize library. */

/*******************************************************************************
* 
*  TESSELLATION ERROR CODES
* 
*******************************************************************************/

	A3D_TESSELLATION_FILIFORM_TRIS						=	-401, /*!< Tessellation contains filiform triangles. */
	A3D_TESSELLATION_FREE_EDGES							=	-402, /*!< Tessellation contains free edges. */
	A3D_TESSELLATION_FILIFORM_TRIS_FREE_EDGES			=	-403, /*!< Tessellation contains filiform triangles and free edges. */

/*******************************************************************************
* 
*  GEOMETRY ERROR CODES
* 
*******************************************************************************/

	A3D_CRV_CANNOT_REPARAMETERIZE						=	-990,	/*!< Input parameterization data cannot be used to reparameterize the curve. */
	A3D_CRV_INVALID_PARAMETER							=	-991,	/*!< Input parameterization data is invalid. */

	A3D_CRV_CANNOT_ACCESS_CANONICAL						=	-1000,	/*!< Cannot access the canonical form for an \ref A3DCrvBase. */
	A3D_CRV_LINE_CANNOT_CREATE_CANONICAL				=	-1001,	/*!< Cannot create canonical form for an \ref A3DCrvLine. */

	A3D_CRV_CIRCLE_CANNOT_CREATE_CANONICAL				=	-1011,	/*!< Cannot create canonical form for an \ref A3DCrvCircle. */

	A3D_CRV_ELLIPSE_CANNOT_CREATE_CANONICAL				=	-1021,	/*!< Cannot create canonical form for an \ref A3DCrvEllipse. */
	A3D_CRV_HYPERBOLA_CANNOT_CREATE_CANONICAL			=	-1022,	/*!< Cannot create canonical form for an \ref A3DCrvHyperbola. */
	A3D_CRV_PARABOLA_CANNOT_CREATE_CANONICAL			=	-1023,	/*!< Cannot create canonical form for an \ref A3DCrvParabola. */

	A3D_CRV_OFFSET_CANNOT_CREATE_CANONICAL				=	-1041,	/*!< Cannot create canonical form for an \ref A3DCrvOffset. */

	A3D_CRV_EQUATION_CANNOT_CREATE_CANONICAL			=	-1051,	/*!< Cannot create canonical form for an \ref A3DCrvEquation. */
	A3D_CRV_TRANSFORM_CANNOT_CREATE_CANONICAL			=	-1052,	/*!< Cannot create canonical form for an \ref A3DCrvTransform. */
	A3D_CRV_CRVONSURF_CANNOT_CREATE_CANONICAL			=	-1053,	/*!< Cannot create canonical form for an \ref A3DCrvOnSurf. */
	A3D_CRV_HELIX_CANNOT_CREATE_CANONICAL				=	-1054,	/*!< Cannot create canonical form for an \ref A3DCrvHelix. */
	A3D_CRV_POLYLINE_CANNOT_CREATE_CANONICAL			=	-1061,	/*!< Cannot create canonical form for an \ref A3DCrvPolyLine. */
	A3D_CRV_INTERSECTION_CANNOT_CREATE_CANONICAL		=	-1063,	/*!< Cannot create canonical form for an \ref A3DCrvIntersection. */

	A3D_CRV_NURBS_CANNOT_ACCESS_INTERNAL				=	-1070,	/*!< Cannot access the internal form for curve. */
	A3D_CRV_NURBS_CANNOT_ACCESS_CONTROL_POINTS			=	-1072,	/*!< Cannot access the control points for an \ref A3DCrvNurbs. */
	A3D_CRV_NURBS_INCONSISTENT_DATA						=	-1073,	/*!< NURBS curve data is inconsistent (control points number + degree + 1 != knots number). */
	A3D_CRV_NURBS_CANNOT_ACCESS_APPROX					=	-1074,	/*!< Cannot access the NURBS approximation for curve. */
	A3D_CRV_NURBS_TOO_TINY_TOLERANCE					=	-1075,	/*!< Tolerance cannot be less then or equal to zero. */

	A3D_CRV_COMPOSITE_CANNOT_CREATE_CANONICAL			=	-1081,	/*!< Cannot create the canonical form for an \ref A3DCrvComposite. */

	A3D_SRF_CANNOT_ACCESS_CANONICAL						=	-1500,	/*!< Cannot access the canonical form for an \ref A3DSurfBase entity. */
	A3D_SRF_CANNOT_CREATE_CANONICAL						=	-1501,	/*!< Cannot create the canonical form for an \ref A3DSurfBase entity. */
	A3D_SRF_NURBS_CANNOT_ACCESS_APPROX					=	-1502,	/*!< Cannot access the NURBS approximation for a surface. */
	A3D_SRF_NURBS_CANNOT_KEEP_PARAMETERIZATION			=	+1503,	/*!< Cannot keep the parameterization during the NURBS approximation for a surface 
																							This is a warning. You must still free the structure. */
	A3D_SRF_NURBS_TOO_TINY_TOLERANCE					=	-1504,	/*!< Tolerance for the NURBS approximation is too tight. Try with looser tolerance. */

	A3D_SRF_PLANE_CANNOT_CREATE_CANONICAL				=	-1521,	/*!< Cannot create the canonical form for an \ref A3DSurfPlane entity. */
	A3D_SRF_INVALID_PARAMETERS							=	-1522,	/*!< Input parameterization data is invalid. */

/*******************************************************************************
* 
*  ATTRIBUTES/GLOBAL DATA ERROR CODES
* 
*******************************************************************************/
	A3D_EMPTY_STRING									=	-2000,	/*!< Name is an empty string. */
	A3D_DEFAULT_COLOR									=	-2001,	/*!< Input index corresponds to the default color. */
	A3D_DEFAULT_LINEPATTERN								=	-2002,	/*!< Input index corresponds to the default line pattern. */
	A3D_DEFAULT_STYLE									=	-2003,	/*!< Input index corresponds to the default style. */
	A3D_DEFAULT_MATERIAL								=	-2004,	/*!< Input index corresponds to the default material. */
	A3D_DEFAULT_PICTURE									=	-2005,	/*!< Input index corresponds to the default picture. */
	A3D_DEFAULT_PATTERN									=	-2006,	/*!< Input index corresponds to the default pattern. */

	A3D_BASE_BAD_ENTITY_TYPE							=	-2050,	/*!< Cannot access base data for an \ref A3DEntity entity, probably because the type is incorrect. */
	A3D_BASEWITHGRAPHICS_BAD_ENTITY_TYPE				=	-2051,	/*!< Cannot access base with graphics data for an \ref A3DEntity entity, probably because the type is incorrect. */
	A3D_BASEWITHGRAPHICS_INCONSISTENT_EMPTY				=	-2052,	/*!< Input data corresponds to an empty \ref A3DGraphics. */

	A3D_INVALID_COLOR_INDEX								=	-2101,	/*!< Index does not correspond to a valid color. */
	A3D_INVALID_LINEPATTERN_INDEX						=	-2102,	/*!< Index does not correspond to a valid line pattern. */
	A3D_INVALID_STYLE_INDEX								=	-2103,	/*!< Index does not correspond to a valid style. */
	A3D_INVALID_MATERIAL_INDEX							=	-2104,	/*!< Index does not correspond to a valid material. */
	A3D_INVALID_PICTURE_INDEX							=	-2105,	/*!< Index does not correspond to a valid picture. */
	A3D_INVALID_PATTERN_INDEX							=	-2106,	/*!< Index does not correspond to a valid pattern. */
	A3D_INVALID_TEXTURE_DEFINITION_INDEX				=	-2107,	/*!< Index does not correspond to a texture definition. */
	A3D_INVALID_TEXTURE_APPLICATION_INDEX				=	-2108,	/*!< Index does not correspond to a texture application. */
	
	A3D_INVALID_PICTURE_FORMAT							=	-2200,	/*!<  Input picture format is invalid. */

/*******************************************************************************
* 
*  REPRESENTATION ITEMS ERROR CODES
* 
*******************************************************************************/

	A3D_RI_CANNOT_ACCESS_TESS							=	-2500,	/*!< Cannot access the \ref A3DTessBase for the current \ref A3DRiRepresentationItem. */
	A3D_RI_CANNOT_ATTACH_BREPDATA						=	-2501,	/*!< Cannot attach the current \ref A3DTopoBrepData to an \ref A3DRiRepresentationItem. */
	A3D_RI_CANNOT_ATTACH_TESS							=	-2502,	/*!< Cannot attach the current \ref A3DTessBase to an \ref A3DRiRepresentationItem. */

	A3D_RI_CRV_INCONSISTENT_DATA						=	-2510,	/*!< Input data corresponds to an empty \ref A3DRiCurve. */
	A3D_RI_PLANE_INCONSISTENT_DATA						=	-2511,	/*!< Input data corresponds to an empty \ref A3DRiPlane. */
	A3D_RI_BREPMODEL_INCONSISTENT_DATA					=	-2512,	/*!< Input data corresponds to an empty \ref A3DRiBrepModel. */

	A3D_SET_INCONSISTENT_EMPTY							=	-2520,	/*!< Input data corresponds to an empty \ref A3DRiSet. */

	A3D_CSYS_INCONSISTENT_EMPTY							=	-2530,	/*!< Input data corresponds to an empty \ref A3DRiCoordinateSystem. */

	A3D_POINTSET_BADSIZE								=	-2540,	/*!< Input data defines an \ref A3DRiPointSet with an incorrect size. */

/*******************************************************************************
* 
*  STRUCTURE ERROR CODES
* 
*******************************************************************************/

	A3D_MODELFILE_INCONSISTENT_EMPTY					=	-3000,	/*!< Input data corresponds to an empty \ref A3DAsmModelFile. Forbidden. */
	A3D_MODELFILE_INCONSISTENT_UNIT						=	-3001,	/*!< Input data corresponds to an invalid unit for an \ref A3DAsmModelFile. Unit must be greater than 0. */

	A3D_PRODUCTOCCURRENCE_INCONSISTENT_EMPTY			=	-3010,	/*!< Input data corresponds to an empty \ref A3DAsmProductOccurrence. Forbidden. */
	A3D_PRODUCTOCCURRENCE_INCONSISTENT_PART_EXTERNAL	=	-3011,	/*!< Input data cannot contain both an external part and a part. */

	A3D_PARTDEFINITION_INCONSISTENT_EMPTY				=	-3020,	/*!< Input data corresponds to an empty \ref A3DAsmPartDefinition. Forbidden. */

	A3D_ENTITYREFERENCE_INCONSISTENT_REFERENCE			=	-3030,	/*!< Input data corresponds to an empty \ref A3DEntity. Forbidden. */
	A3D_ENTITYREFERENCE_INCONSISTENT					=	-3031,	/*!< Input data corresponds to bad \ref A3DMiscEntityReference. */


/*******************************************************************************
* 
*  UTILS DATA ERROR CODES
* 
*******************************************************************************/

	A3D_INTERVAL_INCONSISTENT_DATA						=	-3500,	/*!< Interval is inconsistent for current operation. */

	A3D_TRANSFORMATION3D_NON_ORTHO_NOR_UNIT				=	-3520,	/*!< Input data defines an inconsistent \ref A3DMiscCartesianTransformation. */
	A3D_TRANSFORMATION3D_INCONSISTENT					=	-3521,	/*!< Inconsistent \ref A3DMiscCartesianTransformation. */

/*******************************************************************************
* 
*  TOPOLOGY ERROR CODES
* 
*******************************************************************************/

	A3D_BREPDATA_INCONSISTENT_DATA						=	-4000,	/*!< Input data corresponds to an empty \ref A3DTopoBrepData. */
	A3D_BREPDATA_CANNOT_CREATE							=	-4001,	/*!< Cannot create \ref A3DTopoBrepData with the input data. */
	A3D_BREPDATA_CANNOT_GETBOUNDINGBOX					=	-4002,	/*!< Cannot get bounding box. */
	A3D_BREPDATA_CANNOT_SETBOUNDINGBOX					=	-4003,	/*!< Cannot set bounding box. */
	A3D_TOPOCONTEXT_INVALID								=	-4004,	/*!< Cannot determine the associated \ref A3DTopoContext. */
	
	A3D_CONNEX_INCONSISTENT_DATA						=	-4010,	/*!< Input data corresponds to an empty \ref A3DTopoConnex. */
	
	A3D_SHELL_INCONSISTENT_DATA							=	-4020,	/*!< Input data corresponds to an empty \ref A3DTopoShell. */
	A3D_SHELL_BAD_ORIENTATION_DATA						=	-4021,	/*!< Input data for orientation is incorrect. */
	A3D_SHELL_CANNOT_CREATE								=	-4022,	/*!< Cannot create \ref A3DTopoShell with the input data. */
	
	A3D_FACE_INCONSISTENT_DATA							=	-4030,	/*!< Input data corresponds to an empty \ref A3DTopoFace. */
	A3D_FACE_CANNOT_LIFT_CRV_INTERNAL1					=	-4031,	/*!< Cannot access the internal data of an \ref A3DTopoFace. Internal information: Sector 1. */
	A3D_FACE_CANNOT_LIFT_CRV_INTERNAL2					=	-4032,	/*!< Cannot access the internal data of an \ref A3DTopoFace. Internal information: Sector 2. */
	A3D_FACE_CANNOT_LIFT_CRV_INTERNAL3					=	-4033,	/*!< Cannot access the internal data of an \ref A3DTopoFace. Internal information: Sector 3. */
	A3D_FACE_INCONSISTENT_DOMAIN						=	-4034,	/*!< Inconsistent domain for underlying surface of \ref A3DTopoFace. */
	
//#define	A3D_LOOP_UNKNOW_OUTER_INDEX								((A3DUns32)-1) /*!< Outer loop is unknown. */
	A3D_LOOP_INCONSISTENT_DATA							=	-4400,	/*!< Input data corresponds to an empty \ref A3DTopoLoop. */
	A3D_LOOP_BAD_ORIENTATION_DATA						=	-4401,	/*!< Input data for orientation is incorrect. */
	A3D_LOOP_CANNOT_COMPUTE_ORIENTATION					=	-4402,	/*!< Cannot determine the loop orientation with the input data. */
	A3D_LOOP_CANNOT_FIND_OUTER_LOOP						=	-4403,	/*!< Cannot determine the outer loop index with the input data. */
	
	A3D_COEDGE_INCONSISTENT_DATA						=	-4500,	/*!< Input data corresponds to an empty \ref A3DTopoCoEdge. */
	A3D_COEDGE_BAD_ORIENTATION_DATA						=	-4501,	/*!< Input data for orientation is incorrect. */
	
	A3D_EDGE_BAD_INTERVAL								=	-4600,	/*!< Curve interval is not contained by the interval specified by the input data. */
	A3D_EDGE_INCONSISTENT_DATA							=	-4601,	/*!< Input data corresponds to an empty \ref A3DTopoWireEdge. */
	A3D_EDGE_BAD_3DCURVE								=	-4602,	/*!< Pointer to 3D space curve does not correspond to a curve. */
	
	A3D_SINGLEWIREBODY_INCONSISTENT_DATA				=	-4700,	/*!< Input data corresponds to an empty \ref A3DTopoSingleWireBody. */
	A3D_SINGLEWIREBODY_CANNOT_CREATE					=	-4701,	/*!< Cannot create an \ref A3DTopoSingleWireBody with the input data. */
	
	A3D_TOPO_VERTICES_MISSING							=	-4800,	/* */
	A3D_TOPO_GEOMETRY_MISSING							=	-4801,	/*!< Missing geometry. */
	A3D_TOPO_CONSISTENCY								=	-4802,
	A3D_TOPO_NON_CONNEX_SHELL							=	-4803,
	A3D_TOPO_WRONG_TOLERANCES							=	-4804,
	A3D_TOPO_OPEN_SOLID									=	-4805,	/*!< Invalid Solid. Contains edges without neighbors. */
	
	A3D_TOPO_MULTIPLEVERTEX_INCONSISTENT_DATA			=	-4900,	/* */

/*******************************************************************************
* 
*  TESSELLATION ERROR CODES
* 
*******************************************************************************/

	A3D_TESS3D_NORMALS_INCONSISTENT_DATA				=	-7010,	/*!< Input data corresponds to a null \ref A3DTess3DData::m_pdNormals. */
	A3D_TESS3D_NORMALS_BAD_SIZE							=	-7011,	/*!< Input data corresponds to an invalid size \ref A3DTess3DData::m_uiNormalSize. */
	A3D_TESS3D_FACE_INCONSISTENT_DATA					=	-7020,	/*!< Input data corresponds to null \ref A3DTess3DData::m_psFaceTessData. */

	A3D_TESSFACE_TRIANGULATED_INCONSISTENT_DATA			=	-7030,	/*!< Input data corresponds to null \ref A3DTessFaceData::m_uiStyleIndexesSize. */
	A3D_TESSFACE_TRIANGULATED_INCONSISTENT_EMPTY		=	-7031,	/*!< Input data corresponds to an empty \ref A3DTessFaceData::m_uiSizesTriangulatedSize. */
	A3D_TESSFACE_USEDENTITIES_BAD_TYPE					=	-7032,	/*!< Input data corresponds to an invalid type \ref A3DTessFaceData::m_usUsedEntitiesFlags. */
	A3D_TESSFACE_STARTTRIANGULATED_INCONSISTENT_DATA	=	-7033,	/*!< Input data corresponds to an invalid \ref A3DTessFaceData::m_uiStartTriangulated. */
	A3D_TESSFACE_STARTWIRE_INCONSISTENT_DATA			=	-7034,	/*!< Input data corresponds to an invalid \ref A3DTessFaceData::m_uiStartWire. */
	A3D_TESSFACE_STYLEINDEXESSIZE_INCONSISTENT_DATA		=	-7035,	/*!< Input data corresponds to an invalid \ref A3DTessFaceData::m_uiStyleIndexesSize. */
	A3D_TESSFACE_RGBAVERTICESSIZE_INCONSISTENT_DATA		=	-7036,	/*!< Input data corresponds to an invalid \ref A3DTessFaceData::m_uiRGBAVerticesSize. */

	A3D_TESSWIRE_RGBAVERTICESSIZE_INCONSISTENT_DATA		=	-7052,	/*!< Input data corresponds to an invalid \ref A3DTess3DWireData::m_uiRGBAVerticesSize. */

	A3D_TESSMARKUP_HAS_INVALID_FONTKEY					=	-7060,	/*!< Input data contains an invalid font key. Call \ref A3DGlobalFontKeyCreate. */
	A3D_TESSMARKUP_HAS_INVALID_TEXT_INDEX				=	-7061,	/*!< Input data contains an invalid text index. */

	A3D_TESSBASE_POINTS_INCONSISTENT_DATA				=	-7070,	/*!< Input data corresponds to null \ref A3DTessBaseData::m_pdCoords. */
	A3D_TESSBASE_POINTS_BAD_SIZE						=	-7071,	/*!< Input data corresponds to an invalid size \ref A3DTessBaseData::m_uiCoordSize. */
	A3D_TESSBASE_INCONSISTENT							=	-7072,	/*!< Input data corresponds to bad \ref A3DTessBase. */

	A3D_TESSBASE_BAD_TYPE								=	-7100,	/*!< Input data is not a valid value. */
	A3D_TESSBASE_BAD_INIT								=	-7101,	/*!< Tessellation facilities is not initialized. */
	A3D_TESSBASE_BAD_ONENORMAL							=	-7102,	/*!< Tessellation facilities is consistent. */
	A3D_TESSBASE_BAD_INDEX								=	-7103,	/*!< Input index is out of bounds. */
	A3D_TESSBASE_BAD_VERTEX								=	-7104,	/*!< Input indices are invalid for vertex. */

/*******************************************************************************
* 
*  TOOLS ERROR CODES
* 
*******************************************************************************/

	A3D_TOOLS_NURBSCONVERT_GENERAL_FAILURE				=	-8000,	/*!< General failure on NURBS conversion operation. */
	A3D_TOOLS_NURBSCONVERT_SURFACE_FAILURE				=	-8001,	/*!< Operation failed while converting a surface to NURBS. */
	A3D_TOOLS_NURBSCONVERT_UV_FAILURE					=	-8002,	/*!< Operation failed while converting a space parametric curve. */
	A3D_TOOLS_NURBSCONVERT_3D_FAILURE					=	-8003,	/*!< Operation failed while converting a 3D space curve. */
	A3D_TOOLS_SPLIT_FAILURE								=	-8005,	/*!< Operation failed while splitting a surface at seam. */
	A3D_TOOLS_COMPUTE_UV_FAILURE						=	-8006,	/*!< Operation failed while computing a space parametric curve. */
	A3D_TOOLS_COMPUTE_3D_FAILURE						=	-8007,	/*!< Operation failed while computing a 3D space curve. */
	A3D_TOOLS_UNITIZE									=	-8008,	/*!< Not Used. */
	A3D_TOOLS_CLAMP_UV									=	-8009,	/*!< Not Used. */
	A3D_TOOLS_DUPLICATE									=	-8010,	/*!< Not Used. */
	A3D_TOOLS_INVALID_SECTION_PLANE						=	-8011,	/*!< Cutting planes in \ref A3DMkpView cannot be used.*/

/*******************************************************************************
* 
*  MARKUPS ERROR CODES
* 
*******************************************************************************/

	A3D_ANNOTATIONSET_INCONSISTENT_EMPTY				=	-9000,	/*!< Input data corresponds to an empty \ref A3DMkpAnnotationSet. */
	A3D_ANNOTATIONSET_WITH_NULL_ELEMENT					=	-9001,	/*!< Input data corresponds an array that contains null elements */
	A3D_ANNOTATIONITEM_INCONSISTENT_EMPTY				=	-9005,	/*!< Input data corresponds to an empty \ref A3DMkpAnnotationItem. */
	A3D_MARKUP_CANNOT_ATTACH_TESS						=	-9020,	/*!< Cannot attach current \ref A3DTessBase to \ref A3DMkpMarkup. */
	A3D_MARKUP_CANNOT_ACCESS_TESS						=	-9021,	/*!< Cannot access the \ref A3DTessBase for the current \ref A3DRiRepresentationItem. */
	A3D_MARKUP_CANNOT_ACCESS_FONT						=	-9040,	/*!< The font information cannot be retrieved. */
	A3D_MARKUP_CANNOT_CREATE_FONTKEY					=	-9041,	/*!< The font key cannot be created. */
	A3D_MARKUP_INVALID_FONTKEY							=	-9042,	/*!< The font key given or retrieved is invalid. */
	A3D_MARKUP_SEMANTIC_DEFINITION_NOT_SET				=	-9043,	/*!< No semantic information to retrieve. */
	A3D_MARKUP_SEMANTIC_TOL_VALUE_NOT_SET				=	-9044,	/*!< No tolerance value set in drawing row. */

/*******************************************************************************
* 
*  LOADING CAD FILES ERROR CODES
* 
*******************************************************************************/

	A3D_LOAD_INVALID_FILE_NAME							=	-10000,	/*!< Input file does not correspond to a valid file name. */
	A3D_LOAD_MULTI_MODELS_CADFILE						=	-10001,	/*!< Input CAD file correspond to a multi model file. */
	A3D_LOAD_CANNOT_ACCESS_CADFILE						=	-10002,	/*!< Cannot access input CAD file. */
	A3D_LOAD_CANNOT_READ_SETTINGS						=	-10003,	/*!< Cannot access CAD reading settings file. */
	A3D_LOAD_MISSING_COMPONENTS							=	-10004,	/*!< One or several components are missing. */
	A3D_LOAD_INVALID_FILE_FORMAT						=	-10005,	/*!< Input file seems invalid. */
	A3D_LOAD_READER_NOT_IMPLEMENTED						=	-10006,	/*!< The reader is not implemented. */
	A3D_LOAD_CANNOT_LOAD_MODEL							=	-10007,	/*!< An error occurred during parsing. */
	A3D_LOAD_CANNOT_LOAD_MULTIENTRY						=	-10008,	/*!< Cannot load multi-entry file. */
	A3D_LOAD_EMPTY_MULTI_MODEL							=	-10009,	/*!< Empty model. */
	A3D_LOAD_INVALID_READER_FOR_INCREMENTAL_LOAD		=	-10010,	/*!< Invalid reader for incremental load. */
	A3D_LOAD_INVALID_PARAMETERS_FOR_INCREMENTAL_LOAD	=	-10011,	/*!< Invalid parameters for incremental load. */
	A3D_LOAD_CANNOT_USE_MULTIPROCESS					=	-10012, /*!< Error while launching multiprocess. */
	
/*******************************************************************************
* 
*  LOADING PRC ERROR CODES
* 
*******************************************************************************/

	A3D_LOADPRC_INITIALIZATION_FAILURE					=	-10300,	/*!< Cannot initialize reading context. */
	A3D_LOADPRC_CANNOT_OPEN_FILE						=	-10301,	/*!< Cannot open file. */
	A3D_LOADPRC_READING_ERROR							=	-10302,	/*!< Internal reading error. */
	A3D_LOADPRC_BUILD_ERROR								=	-10303,	/*!< Internal reading error - Invalid PRC file. */
	A3D_LOADPRC_PDFLINIT_ERROR							=	-10304,	/*!< Error while initializing PDFL. */
	A3D_LOADPRC_INVALID_ANNOT_INDEX						=	-10305,	/*!< Input annotation index is invalid. */
	A3D_LOADPRC_INVALID_ANNOT							=	-10306,	/*!< Input annotation is invalid. */
	A3D_LOADPRC_EMPTY_FILE								=	-10307,	/*!< Input file is empty. */
	A3D_LOADPRC_NO_3D									=	-10308,	/*!< Input file does not contain any 3D Annot. */

/*******************************************************************************
* 
*  WRITING ERROR CODES
* 
*******************************************************************************/

	A3D_WRITE_ERROR										=	-10400,	/*!< Error while writing export file. */
	A3D_WRITE_CANNOT_LOAD_WRITER						=	-10401,	/*!< Cannot load writer. */
	A3D_WRITE_WRITER_NOT_IMPLEMENTED					=	-10402,	/*!< The writer is not implemented. */
	A3D_WRITE_INVALID_FILE_NAME							=	-10403,	/*!< Input file does not correspond to a valid file name. */
	A3D_WRITE_INVALID_INPUT								=	-10404,	/*!< Input file does not correspond to a valid file name. */
	A3D_WRITE_KEEPPARSEDENTITIES_DISABLED				=	-10405,	/*!< KeepParsedEntities should be enabled when translating to Parasolid pkParts */

/*******************************************************************************
*
*	DRAWING ERROR CODES
*
*******************************************************************************/
	A3D_DRW_CANNOT_CREATE								=	-11000,	/*!< Cannot create drawing. */
	A3D_DRW_SHEET_CANNOT_CREATE							=	-11001,	/*!< Cannot create drawing sheet. */
	A3D_DRW_SHEET_FORMAT_CANNOT_CREATE					=	-11002,	/*!< Cannot create drawing sheet format. */
	A3D_DRW_SHEET_INVALID_SIZE							=	-11003,	/*!< Invalid sheet size. */
	A3D_DRW_SHEET_INVALID_SCALE							=	-11004,	/*!< Scale of \ref A3DDrawingSheet must be greater than 1e-12. */
	A3D_DRW_VIEW_CANNOT_CREATE							=	-11005,	/*!< Cannot create drawing view. */
	A3D_DRW_VIEW_INVALID_SCALE							=	-11006,	/*!< Scale of \ref A3DDrawingView must be greater than 1e-12. */
	A3D_DRW_VIEW_INVALID_TYPE							=	-11007,	/*!< Invalid view type. */
	A3D_DRW_BLOCK_CANNOT_CREATE							=	-11008,	/*!< Cannot create drawing block. */
	A3D_DRW_OPERATOR_CANNOT_CREATE						=	-11009,	/*!< Cannot create drawing operator. */
	A3D_DRW_OPERATOR_INVALID_TYPE						=	-11010,	/*!< Invalid drawing operator type. */
	A3D_DRW_CURVE_CANNOT_CREATE							=	-11011,	/*!< Cannot craete drawing curve. */
	A3D_DRW_CURVE_INVALID_DIMENSION						=	-11012,	/*!< Invalid drawing curve dimension. */
	A3D_DRW_CURVE_BAD_INTERVAL							=	-11013,	/*!< Bad drawing curve interval. */
	A3D_DRW_FILLEDAREA_CANNOT_CREATE					=	-11014,	/*!< Cannot create drawing filled area. */
	A3D_DRW_FILLEDAREA_INVALID_MODE						=	-11015,	/*!< Invalid value. Refers to \ref A3DEDrawingFilledAreaMode. */
	A3D_DRW_FILLEDAREA_INVALID_SCALE					=	-11016,	/*!< Scale of \ref A3DDrawingFilledArea must be greater than 1e-12. */
	A3D_DRW_FILLEDAREA_CLOSED_BOUNDARY					=	-11017,	/*!< Boundary of \ref A3DDrawingFilledArea must be closed. */
	A3D_DRW_PICTURE_CANNOT_CREATE						=	-11018,	/*!< Cannot create drawing picture. */
	A3D_DRW_VERTICES_CANNOT_CREATE						=	-11019,	/*!< Cannot create drawing vertices. */

/*******************************************************************************
*
*	MATH FUNCTIONS
*
*******************************************************************************/

	A3D_MATH_INCONSISTENT_DATA							=	-40000,	/*!< Invalid input data. */
	A3D_MATH_FRACTION_INCONSISTENT_NUMERATOR			=	-40001,	/*!< Invalid function for numerator. */
	A3D_MATH_FRACTION_INCONSISTENT_DENOMINATOR			=	-40002,	/*!< Invalid function for denominator. */

/*******************************************************************************
* 
*  CALLBACK FUNCTIONS ERROR CODES
* 
*******************************************************************************/

	A3D_CALLBACK_MEMORY_FUNCTIONS_ALREADY_SET			=	-900000,	/*!< \ref A3DDllSetCallbacksMemory can be called only once per session. */
	A3D_CALLBACK_INVALID_BREAK_VALUE					=	-900001,	/*!< \ref A3DDllSetCallbacksProgress : lBreak must be a valid pointer (not NULL). */
	A3D_CALLBACK_CONTINUE								=	-900002,	/*!< \ref A3DDllSetCallbacksProgress : lBreak must be a valid pointer (not NULL). */

/*******************************************************************************
* 
*  PDF PUBLISH FUNCTIONS ERROR CODES
* 
*******************************************************************************/

	A3DPDF_PDFLIB_ERROR									=	-1000000,	/*!< Unexpected PDFLib Error. */
	A3DPDF_ONLY_ONE_PAGE_AUTHORIZED						=	-1000001,	/*!< \ref A3DPDFDocumentCreateUniquePage can be called only on an empty document. */
	A3DPDF_3D_ANNOT_REQUIRED							=	-1000002,	/*!< Cannot call \ref A3DPDFDocumentSave without a 3D Annot in the document. */
	A3DPDF_ERR_AFTER_SAVE								=	-1000003,	/*!< \ref A3DPDFDocumentSave : document has not been saved properly. */
	A3DPDF_OPT_NOT_PERMITTED							=	-1000004,	/*!< \ref A3DPDFDocumentSave : invalid options. */
	A3DPDF_FILE_ALREADY_OPEN							=	-1000005,	/*!< \ref A3DPDFDocumentSave : file is already opened in another application. */
	A3DPDF_FILE_LOCKED									=	-1000006,	/*!< \ref A3DPDFDocumentSave : file is locked by another application. */
	A3DPDF_BAD_FONT_PARAMETERS							=	-1000007,	/*!< \ref A3DPDFPageInsertText : bad font parameters. */
	A3DPDF_BAD_PARAMETERS								=	-1000008,	/*!< Bad parameters. */
	A3DPDF_CANNOT_ACCESS_FILE							=	-1000009,	/*!< Cannot access file. */
	A3DPDF_UNKNOWN_FIELD								=	-1000010,	/*!< Cannot find the specified field in the document. */
	A3DPDF_DEFAULT_VIEW_ERROR							=	-1000011,	/*!< Cannot find a default view in 3D Annot. */
	A3DPDF_INVALID_DIMENSIONS							=	-1000014,	/*!< Width and height must be >0 and <=682. */
	A3DPDF_MEMORY_ERROR									=	-1000015,	/*!< Not enough memory. */
	A3DPDF_CANNOT_FIND_FONT								=	-1000016,	/*!< Cannot find the specified font. */
	A3DPDF_CANNOT_CREATE_ENCODING						=	-1000017,	/*!< Cannot create the specified encoding. */
	A3DPDF_CANNOT_CREATE_FONT							=	-1000018,	/*!< Cannot create the specified font. */
	A3DPDF_CANNOT_CONVERT_PICTURE						=	-1000019,	/*!< Cannot convert the specified picture. */
	A3DPDF_CANNOT_SNAPSHOT_VIEW_WITHOUT_CAMERA			=	-1000020,	/*!< In a PRC/PDF file, there is a view without a camera; snapshots cannot be created from such views. */
	A3DPDF_CANNOT_LOAD_TABLETOPDF_DLL					=	-1000021,	/*!< tabletopdf.dll or one of its components is missing from your directory. */
	A3DPDF_HTML_TABLE_ERROR								=	-1000022,	/*!< Wrong HTML format for table entry. */
	A3DPDF_HTML_STYLE_ERROR								=	-1000023,	/*!< Wrong HTML format for style entry. */
	A3DPDF_CANNOT_INITIALIZE_RESOURCES					=	-1000024,	/*!< Resource directory could not be initialized. Please check you used \ref A3DPDFInitializePDFLibAndResourceDirectory with a correct path. */
	A3DPDF_INVALID_PAGE_INDEX							=	-1000025,	/*!< Input page index is invalid or not in pages bounds. */
	A3DPDF_CANNOT_GENERATE_IMAGE_FROM_VIEW				=	-1000026,	/*!< Error while generating the images for the buttons in the view carousel. */
	A3DPDF_ANIMATION_NULL_MOTION						=	-1000027,	/*!< At least one motion is null, the animation can't be created. */
	A3DPDF_SLIDETABLE_NBCOLUMNS_ERROR					=	-1000028,	/*!< The number of columns in the table frame is different than the number of columns in text data. */
	A3DPDF_SLIDETABLE_TEXTDATA_ERROR					=	-1000029,	/*!< Error in text data (ppTexts argument). */
	A3DPDF_CANNOT_LOAD_PDFLIB_DLL						=	-1000030,	/*!< pdflib DLL or one of its components is missing. */
	A3DPDF_CANNOT_LOAD_IMAGEMAGICK_DLL					=	-1000031,	/*!< ImageMagick DLL or one of its components is missing. */
	A3DPDF_NO_3D_ON_PAGE								=	-1000032,	/*!< Error retrieving 3D data on page. No annot was found. */
	A3DPDF_3D_NOTFOUND_ON_PAGE							=	-1000033,	/*!< Error retrieving 3D data on page. No 3D annot was found. */
	A3DPDF_CANNOT_READSTREAM							=	-1000035,	/*!< Error reading text stream. */
	A3DPDF_CANNOT_CONVERTSTREAM							=	-1000036,	/*!< Encoding error converting text stream. */
	A3DPDF_SLIDETABLE_SLIDER_ERROR						=	-1000037,	/*!< Error in slider creation */
	A3DPDF_SLIDETABLE_TEXT_FIELD_ERROR					=	-1000038,	/*!< Error in slider creation */
	A3DPDF_SLIDETABLE_NOT_EXIST							=	-1000039,	/*!< The slidetable object could not be found */
	A3DPDF_CAROUSEL_NOT_EXIST							=	-1000040,	/*!< The carousel object could not be found */
	/*******************************************************************************
	* 
	*  PARASOLID ERROR CODES
	* 
	*******************************************************************************/
	A3D_PARASOLID_ERROR_970								=	-2000970, /*!< Error in Parasolid export. */
	A3D_PARASOLID_ERROR_555								=	-2000555, /*!< Error in Parasolid export. */

	/*******************************************************************************
	*
	*  TRANSLATE_TO_PK-PARTS ERROR CODES
	*
	*******************************************************************************/
	A3D_HEPB_MISSING									= -3000001, /*!< Error in HEPB loading. */
	A3D_BODYSHOP_MISSING								= -3000002 /**/

} A3DStatus;


#endif	/*	__A3DPRCERRORCODES_H__ */
