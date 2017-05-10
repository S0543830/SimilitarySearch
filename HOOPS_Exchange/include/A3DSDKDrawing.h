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
\brief      Header file for the drawing module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCDRAWING_H__
#define __A3DPRCDRAWING_H__

#ifndef __A3DPRCMISC_H__
#error A3DSDKMisc.h must be included before current file
#endif

/*!
\defgroup a3d_drawing_module Drawing Module
\ingroup a3d_entitiesdata_module
\brief Creates and accesses entities that represent drawing
This module describes the functions and structures that allow you to create and parse Drawings.

Drawing structure entities have names of the form A3DDrawingEntityName, for example \ref A3DDrawingModel.

Drawing structures are divided into 2 parts:
\li structure entities ( \ref A3DDrawingModel, \ref A3DDrawingSheet, \ref A3DDrawingView, \ref A3DDrawingBlock)
\li graphic entities ( \ref A3DDrawingEntity )

The root drawing entity is \ref A3DDrawingModel witch is a set of \ref A3DDrawingSheet.
\image html drawing_diagramme.png
*/

//##############################################################################
#ifndef __A3D_DRAWING_MODEL__
/*!
\defgroup a3d_drawing_model Drawing Model
\ingroup a3d_drawing_module
\version 5.0

Entity type is \ref kA3DTypeDrawingModel.

Drawing model is a set a sheet.
If model contains more that one sheet, a default active sheet is defined.

\image html drawing_model.png 
*/

/*!
\brief Drawing Model structure
\ingroup a3d_drawing_model
\version 5.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32							m_uiDrwSheetsSize;				/*!< Size of next array. */
	A3DDrawingSheet**					m_ppDrwSheets;					/*!< Array of pointers on sheets. */
	A3DUns32							m_uiActiveSheet;				/*!< Index of the active sheet (must be less than \ref m_uiDrwSheetsSize).
																				<br>In the case below, m_uiActiveSheet is set to 1. \image html drawing_model.png */
} A3DDrawingModelData;

/*!
\brief Populates the \ref A3DDrawingModelData structure
\ingroup a3d_drawing_model
\version 5.0

\param [in] pDrawingModel The input drawing model.
\param [out] pData Data of the drawing model.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingModelGet,(	const A3DDrawingModel* pDrawingModel,
														A3DDrawingModelData* pData));


/*!
\brief Creates an \ref A3DDrawingModel from \ref A3DDrawingModelData structure
\ingroup a3d_drawing_model
\version 5.0

\param [in] pData The input drawing model data.
\param [out] ppDrawingModel The drawing model entity.

\return \ref A3D_DRW_CANNOT_CREATE \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingModelCreate,(	const A3DDrawingModelData* pData,
															A3DDrawingModel** ppDrawingModel));

#endif // __A3D_DRAWING_MODEL__



//##############################################################################
#ifndef __A3D_DRAWING_SHEETFORMAT__
/*!
\defgroup a3d_drawing_sheetformat Drawing Sheet Format
\ingroup a3d_drawing_sheet
\version 5.0

Entity type is \ref kA3DTypeDrawingSheetFormat.
*/

/*!
\brief Drawing sheet format structure
\ingroup a3d_drawing_sheetformat
\version 5.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*						m_pcName;						/*!< String. */
	A3DVector2dData						m_sSize;						/*!< Size of the sheet. */
} A3DDrawingSheetFormatData;

/*!
\brief Populates the \ref A3DDrawingSheetFormatData structure
\ingroup a3d_drawing_sheetformat
\version 5.0

\param [in] pDrwSheetFormat The input sheet format.
\param [out] pData Data of the sheet format.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingSheetFormatGet,(	const A3DDrawingSheetFormat* pDrwSheetFormat,
																A3DDrawingSheetFormatData* pData));


/*!
\brief Creates an \ref A3DDrawingSheetFormat from \ref A3DDrawingSheetFormatData structure
\ingroup a3d_drawing_sheetformat
\version 5.0

\param [in] pData The input sheet format data.
\param [out] ppDrwSheetFormat The sheet format entity.

\return \ref A3D_DRW_SHEET_FORMAT_CANNOT_CREATE \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL\n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingSheetFormatCreate,(	const A3DDrawingSheetFormatData* pData,
																	A3DDrawingSheetFormat** ppDrwSheetFormat));

#endif // __A3D_DRAWING_SHEETFORMAT__ 


//##############################################################################
#ifndef __A3D_DRAWING_SHEET__
/*!
\defgroup a3d_drawing_sheet Drawing Sheet
\ingroup a3d_drawing_module
\sa a3d_drawing_model
\version 5.0

Entity type is \ref kA3DTypeDrawingSheet.

A sheet corresponds to a paper page with geometries which are groups into some structures. 
\image html drawing_sheet.png

*/

/*!
\brief Drawing sheet structure
\ingroup a3d_drawing_sheet
\version 5.0

\details
A local coordinate system can be applied on sheet, by setting \ref m_sRefPoint and \ref m_dScale.
\code
	A3DVector2dData SheetLocalToGlobal( A3DVector2dData const & sLocalCoord)
	{
		A3DVector2dData sGlobalCoord;
		sGlobalCoord.x = sLocalCoord.x * m_dScale + m_sRefPoint.x;
		sGlobalCoord.y = sLocalCoord.y * m_dScale + m_sRefPoint.y;
		return sGlobalCoord;
	}
\endcode

*/
typedef struct
{
	A3DUns16							m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDrawingSheetFormat*				m_pFormat;					/*!< Optional sheet format. */
	A3DVector2dData						m_sSize;					/*!< Size of the sheet (not used if \ref m_pFormat is defined). Refers to \ref a3d_drawing_sheetformat for more details. */
	A3DVector2dData						m_sRefPoint;				/*!< Set a new reference point for the sheet. \image html drawing_sheet_refpoint.png */
	A3DDouble							m_dScale;					/*!< Set a scale for the sheet. This scale is apply on all entities contained by the sheet. Asbolute value must be greater than 1e-12. \image html drawing_sheet_scale.png */
	A3DBool								m_bDrawFrame;				/*!< Draw the frame of the sheet. */
	A3DUns16							m_usStyle;					/*!< */
	A3DUns16							m_usBackgroundStyle;		/*!< Defines the color of the sheet. */
	A3DDrawingBlock*					m_pBackgroundBlocks;		/*!< Geometries defined as part of the background of the sheet (like a title block). Refers to \ref a3d_drawing_block for more details. */
	A3DUns32							m_uiDrwBlocksSize;			/*!< Size of next array. */
	A3DDrawingBlock**					m_ppDrwBlocks;				/*!< Array of pointers on blocks. Refers to \ref a3d_drawing_block for more details. */
	A3DUns32							m_uiDrwViewsSize;			/*!< Size of next array. */
	A3DDrawingView**					m_ppDrwViews;				/*!< Array of pointers on views. Refers to \ref a3d_drawing_view for more details. */
} A3DDrawingSheetData;

/*!
\brief Populates the \ref A3DDrawingSheetData structure
\ingroup a3d_drawing_sheet
\version 5.0

\param [in] pDrawingSheet The input sheet.
\param [out] pData Data of the sheet.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingSheetGet,(	const A3DDrawingSheet* pDrawingSheet,
														A3DDrawingSheetData* pData));


/*!
\brief Creates an \ref A3DDrawingSheet from \ref A3DDrawingSheetData structure
\ingroup a3d_drawing_sheet
\version 5.0

\param [in] pData The input sheet data.
\param [out] ppDrawingSheet The sheet entity.

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_DRW_SHEET_CANNOT_CREATE \n
\return \ref A3D_DRW_SHEET_INVALID_SIZE \n
\return \ref A3D_DRW_SHEET_INVALID_SCALE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingSheetCreate,(	const A3DDrawingSheetData* pData,
															A3DDrawingSheet** ppDrawingSheet));

#endif // __A3D_DRAWING_SHEET__




//##############################################################################
#ifndef __A3D_DRAWING_VIEW_TYPE_ENUM__

/*!
\addtogroup a3d_drawing_view
\brief Enumerations for drawing view type for use in the \ref A3DDrawingViewData structure
@{
*/

/*!
\version 5.0

Drawing view type identifiers
*/

typedef enum
{
	kA3DDrawingViewTypeUnknown		=   0,	/*!< Unknown value. */
	kA3DDrawingViewTypeIso			=   1,	/*!< ISO view. */
	kA3DDrawingViewTypeTop			=   2,	/*!< Top view. */
	kA3DDrawingViewTypeBottom		=   3,	/*!< Bottom view. */
	kA3DDrawingViewTypeLeft			=   4,	/*!< Left view. */
	kA3DDrawingViewTypeRight		=   5,	/*!< Right view. */
	kA3DDrawingViewTypeFront		=   6,	/*!< Front view. */
	kA3DDrawingViewTypeBack			=   7,	/*!< Back view. */
	kA3DDrawingViewTypeBackground	=   8,	/*!< Background view. */
	kA3DDrawingViewTypeWorking		=   9,	/*!< Working view. */
	kA3DDrawingViewTypeProjected	=  10,	/*!< Projected view. */
	kA3DDrawingViewTypeAuxiliary	=  11,	/*!< Auxiliary view. */
	kA3DDrawingViewTypeSection		=  12,	/*!< Section view. */
	kA3DDrawingViewTypeDetail		=  13,	/*!< Detail view. */
} A3DEDrawingViewType;

/*!
@} <!-- end of a3d_drawing_viewtype_enumes -->
*/

#endif // __A3D_DRAWING_VIEW_TYPE_ENUM__



//##############################################################################
#ifndef __A3D_DRAWING_CLIPFRAME__
/*!
\defgroup a3d_drawing_clipframe Drawing Clip Frame
\ingroup a3d_drawing_view
\version 5.0

\brief Define a clipping frame for views

Entity type is \ref kA3DTypeDrawingClipFrame.
*/

/*!
\brief A3DEDrawingClipFrameType enum
\ingroup a3d_drawing_clipframe
\version 5.0

\image html drawing_view_clipping_type.png

*/
typedef enum
{
	kA3DDrawingClipFrameTypeNone					=  0,				/*!< Unknown value. */
	kA3DDrawingClipFrameTypeRectangular				=  1,				/*!< The frame is a rectangle. */
	kA3DDrawingClipFrameTypeUserDefine				=  2				/*!< The frame is defined by user. */
} A3DEDrawingClipFrameType;

/*!
\brief A3DDrawingClipFrame structure
\ingroup a3d_drawing_clipframe
\version 5.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns16							m_uiStyle;						/*!< Style of the boundary if \ref m_bDrawBound is set to true. */
	A3DBool								m_bDrawBound;					/*!< Draw the boundary. */
	A3DBool								m_bClipBound;					/*!< Clip view geometry with the boundary. \image html drawing_view_clipping.png */
	A3DEDrawingClipFrameType			m_eType;						/*!< Type of current clipping frame (see \ref A3DEDrawingClipFrameType). \image html drawing_view_clipping_type.png */
	A3DDomainData						m_sRectangularBox;				/*!< BoundingBox of clipping if \ref m_eType is \ref kA3DDrawingClipFrameTypeRectangular. \n Coordinate are in local coordinate space. */
	A3DCrvBase*							m_pCurve;						/*!< Closed curve of clipping if \ref m_eType is \ref kA3DDrawingClipFrameTypeUserDefine. */
} A3DDrawingClipFrameData;

/*!
\brief Populates the \ref A3DDrawingClipFrameData structure
\ingroup a3d_drawing_clipframe
\version 5.0

\param [in] pDrwClipFrame The input clipping frame.
\param [out] pData Data of the clipping frame.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingClipFrameGet,(	const A3DDrawingClipFrame* pDrwClipFrame,
															A3DDrawingClipFrameData* pData));


/*!
\brief Creates an \ref A3DDrawingClipFrame from \ref A3DDrawingClipFrameData structure
\ingroup a3d_drawing_clipframe
\version 5.0

\param [in] pData The input clipping frame data
\param [out] ppDrwClipFrame The clipping frame entity.

\return \ref A3D_INITIALIZE_NOT_CALLED\n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingClipFrameCreate,(	const A3DDrawingClipFrameData* pData,
															A3DDrawingClipFrame** ppDrwClipFrame));

#endif // __A3D_DRAWING_CLIPFRAME__


//##############################################################################
#ifndef __A3D_DRAWING_VIEW__
/*!
\defgroup a3d_drawing_view Drawing View
\ingroup a3d_drawing_module
\sa a3d_drawing_sheet
\version 5.0

Entity type is \ref kA3DTypeDrawingView.

\details
A local coordinate system can be applied on view, by setting \ref A3DDrawingViewData::m_sOriginOnSheet,
\ref A3DDrawingViewData::m_sOffsetLocation, \ref A3DDrawingViewData::m_dScale and \ref A3DDrawingViewData::m_dAngle.\n
To convert local view coordinates into local sheet coordinate space, you can use the pseudo function below.
\code
	Matrix2D ViewToSheetMatrix( A3DDrawingViewData const & sViewData)
	{
		Marix2D sMatrix
		
		sMatrix.SetAngle(  sViewData.m_dAngle );
		sMatrix.Translate( sViewData.m_sOffsetLocation );
		sMatrix.Scale(     sViewData.m_dScale );
		sMatrix.Translate( sViewData.m_sOriginOnSheet );
		
		return sMatrix;
	}
\endcode

*/

/*!
\struct A3DDrawingViewData
\brief DrawingView structure
\ingroup a3d_drawing_view
\version 5.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DEDrawingViewType					m_eType;					/*!< Type of current view. \image html drawing_view.png */
	A3DDrawingClipFrame*				m_pClipFrame;				/*!< Clipping frame of current view. Refer to \ref a3d_drawing_clipframe for more details. */
	A3DVector2dData						m_sOriginOnSheet;			/*!< Origin of view in owner sheet space. Refer to \ref a3d_drawing_view. \image html drawing_sheet_refpoint.png */
	A3DVector2dData						m_sOffsetLocation;			/*!< Sets a new origin for the local space of the view. Refer to \ref a3d_drawing_view. \image html drawing_view_offset.png */
	A3DDouble							m_dScale;					/*!< Set a scale to local coordinate system. Refer to \ref a3d_drawing_view. */
	A3DDouble							m_dAngle;					/*!< Set a angle rotation to local coordinate system. Refer to \ref a3d_drawing_view. */
	A3DUns32							m_uiSrcFilesNamesSize;		/*!< Size of next array. */
	A3DUTF8Char**						m_ppcSrcFilesNames;			/*!< Name of reference files. */
	A3DDrawingBlock*					m_pLocalBlocks;				/*!< Block on view. */
	A3DUns32							m_uiDrwBlocksSize;			/*!< Size of next array. */
	A3DDrawingBlock**					m_ppDrwBlocks;				/*!< Array of pointers on blocks. */
	A3DMkpView*							m_pBaseView;				/*!< For future use. */
	A3DAsmFilter*						m_pFilter;					/*!< For future use. */
} A3DDrawingViewData;

/*!
\brief Populates the \ref A3DDrawingViewData structure
\ingroup a3d_drawing_view
\version 5.0

\param [in] pDrawingView The input view.
\param [out] pData Data of the view.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingViewGet,(	const A3DDrawingView* pDrawingView,
														A3DDrawingViewData* pData));


/*!
\brief Creates an \ref A3DDrawingView from \ref A3DDrawingViewData structure
\ingroup a3d_drawing_view
\version 5.0

\param [in] pData The input view data
\param [out] ppDrawingView The clipping view entity.

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_DRW_VIEW_INVALID_SCALE \n
\return \ref A3D_DRW_VIEW_INVALID_TYPE \n
\return \ref A3D_DRW_VIEW_CANNOT_CREATE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingViewCreate,(	const A3DDrawingViewData* pData,
															A3DDrawingView** ppDrawingView));

#endif // __A3D_DRAWING_VIEW__


/*!
\defgroup a3d_drawing_block Drawing Block
\ingroup a3d_drawing_module
\ingroup a3d_repitem
\sa a3d_drawing_sheet
\sa a3d_drawing_view
\version 5.0

\brief Creates and accesses entities that contain graphics entities.

An \ref A3DDrawingBlock is a specific representation item, which can be use only in drawing context. 
\sa a3d_ricontent

They are used to represent sketches on sheet or view.

They may contain other \ref A3DDrawingBlock, \ref A3DMkpMarkup or \ref A3DDrawingEntity.
\image html drawing_block.png

*/


//##############################################################################
#ifndef __A3D_DRAWING_BLOCKBASIC__
/*!
\defgroup a3d_drawing_blockbasic Drawing Block Basic
\ingroup a3d_drawing_block
\version 5.0

Entity type is \ref kA3DTypeDrawingBlockBasic.

This entity is a physical grouping of other drawing entities.

An \ref A3DDrawingBlockBasic entity can contain multiple child \ref A3DDrawingBlock, \ref A3DMkpMarkup or \ref A3DDrawingEntity.

\warning Circular references are not allowed.

*/

/*!
\brief DrawingBlockBasic structure
\ingroup a3d_drawing_blockbasic
\version 5.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32							m_uiDrwEntitiesSize;		/*!< Size of next array. */
	A3DDrawingEntity**					m_ppDrwEntities;			/*!< Array of gemeometric entities. */
	A3DUns32							m_uiMarkupsSize;			/*!< Size of next array. */
	A3DMkpMarkup**						m_ppMarkups;				/*!< Array of markups. */
	A3DUns32							m_uiDrwBlocksSize;			/*!< Size of next array. */
	A3DDrawingBlock**					m_ppDrwBlocks;				/*!< Array of drawing block. */
} A3DDrawingBlockBasicData;

/*!
\brief Populates the \ref A3DDrawingBlockBasicData structure
\ingroup a3d_drawing_blockbasic
\version 5.0

\param [in] pDrawingBlock The basic block.
\param [out] pData Data of the basic block.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingBlockBasicGet,(const A3DDrawingBlockBasic* pDrawingBlock,
															A3DDrawingBlockBasicData* pData));


/*!
\brief Creates an \ref A3DDrawingBlockBasic from \ref A3DDrawingBlockBasicData structure
\ingroup a3d_drawing_blockbasic
\version 5.0

\param [in] pData The input basic block data
\param [out] ppDrawingBlock The basic block entity

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_DRW_BLOCK_CANNOT_CREATE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingBlockBasicCreate,(const A3DDrawingBlockBasicData* pData,
																A3DDrawingBlockBasic** ppDrawingBlock));

#endif // __A3D_DRAWING_BLOCKBASIC__


//##############################################################################
#ifndef __A3D_DRAWING_OPERATOR_ENUM__

/*!
\addtogroup a3d_drawing_operator
\brief Enumerations for drawing operator type for use in the \ref A3DDrawingBlockOperatorData structure
@{
*/

/*!
\version 5.0

Drawing operator type identifiers
*/

typedef enum
{
	kA3DDrawingOperatorTypeUnknwon				=  0,	/*!< Unknown value. */
	kA3DDrawingOperatorTypeDetail				=  1,	/*!< View of detail. */
	kA3DDrawingOperatorTypeSection				=  2	/*!< View of section. */

} A3DEDrawingOperatorType;

/*!
@} <!-- end of a3d_drawing_operator_enums -->
*/

#endif // __A3D_DRAWING_OPERATOR_ENUM__



//##############################################################################
#ifndef __A3D_DRAWING_BLOCKOPERATOR__
/*!
\defgroup a3d_drawing_operator Drawing Operator
\ingroup a3d_drawing_block
\version 5.0

Entity type is \ref kA3DTypeDrawingBlockOperator.

Block Operator is same as Block Basic, but it provide also a link between graphic entities and a view.
It is useful to define a relationship between a curve section and a view.

Refer to \ref a3d_drawing_blockbasic for other details.

\warning Circular dependencies between \ref A3DDrawingBlockOperator and \ref A3DDrawingView are not allowed.
*/

/*!
\brief DrawingBlockOperator structure
\ingroup a3d_drawing_operator
\version 5.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DEDrawingOperatorType				m_eType;					/*!< Defines the type of operator. */
	A3DDrawingView*						m_pViewResult;				/*!< View linked with current operator. \image html drawing_view.png */
	A3DUns32							m_uiDrwEntitiesSize;		/*!< Size of next array. */
	A3DDrawingEntity**					m_ppDrwEntities;			/*!< Array of drawing entities. Refer to \ref a3d_drawing_blockbasic for details. */
	A3DUns32							m_uiMarkupsSize;			/*!< Size of next array. */
	A3DMkpMarkup**						m_ppMarkups;				/*!< Array of markups. Refer to \ref a3d_drawing_blockbasic for details. */
	A3DUns32							m_uiDrwBlocksSize;			/*!< Size of next array. */
	A3DDrawingBlock**					m_ppDrwBlocks;				/*!< Array of Drawing block. Refer to \ref a3d_drawing_blockbasic for details. */
} A3DDrawingBlockOperatorData;

/*!
\brief Populates the \ref A3DDrawingBlockOperatorData structure
\ingroup a3d_drawing_operator
\version 5.0

\param [in] pDrawingOperator The operator block.
\param [out] pData Data of the operator block.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingBlockOperatorGet,(const A3DDrawingBlockOperator* pDrawingOperator,
																A3DDrawingBlockOperatorData* pData));


/*!
\brief Creates an \ref A3DDrawingBlockOperator from \ref A3DDrawingBlockOperatorData structure
\ingroup a3d_drawing_operator
\version 5.0

\param [in] pData The input operator block data
\param [out] ppDrawingOperator The operator block entity

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_DRW_OPERATOR_CANNOT_CREATE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingBlockOperatorCreate,(const A3DDrawingBlockOperatorData* pData,
																	A3DDrawingBlockOperator** ppDrawingOperator));

#endif // __A3D_DRAWING_BLOCKOPERATOR_


/*!
\brief Push a \ref A3DMiscCascadedAttributes
\ingroup a3d_drawing_block
\version 5.0

In case of reading mode is TessOnly, push the \ref A3DMiscCascadedAttributes of a \ref A3DDrawingEntity

\param [in,out] pAttr The cascaded attributes to update
\param [in] pBlock The block entity
\param [in] uiEntityIndex Index of drawing entity from pBlock
\param [in] pFather The father cascaded attribute

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingBlockPushMiscCascadedAttributes,(A3DMiscCascadedAttributes* pAttr,
																					const A3DDrawingBlock* pBlock,
																					A3DUns32 uiEntityIndex,
																					const A3DMiscCascadedAttributes* pFather) );


//##############################################################################
#ifndef __A3D_DRAWING_ENTITY__
/*!
\defgroup a3d_drawing_entity Drawing Entity
\ingroup a3d_drawing_module
\version 5.0

\brief Creates and accesses geometrical or graphical entities used with \ref A3DDrawingModel

\image html drawing_entity.png

\sa a3d_drawing_block
\sa a3d_basewithgraphics

*/
#endif // __A3D_DRAWING_ENTITY__



//##############################################################################
#ifndef __A3D_DRAWING_CURVE__
/*!
\defgroup a3d_drawing_curve Drawing Curve
\ingroup a3d_drawing_entity
\version 5.0

An A3DDrawingCurve is a drawing item that contains a geometrical curve.

Entity type is \ref kA3DTypeDrawingCurve.
	
\sa a3d_basewithgraphics

*/

/*!
\brief A3DDrawingCurve structure
\ingroup a3d_drawing_curve
\version 5.0

On drawing, only 2 dimension curve are used. If \ref m_pCurve is a 3 dimension curve, \ref m_pPlane must be defined. \n
In this case, resulting curve of the projection on the given plane is used. \n
In case of 2 dimension curve \ref m_pPlane is not used. \n

\warning  \ref m_sTrimInterval must be contained or equal to the curve interval definition.
*/
typedef struct
{
	A3DUns16									m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DCrvBase*								m_pCurve;					/*!< Geometric curve. Refers to \ref a3d_crv for more details. */
	A3DIntervalData						m_sTrimInterval;			/*!< Trim interval for the curve. It must be contained or equal to the curve interval: \image html drawing_trimcurve.png */
	A3DSurfPlane*							m_pPlane;					/*!< Projection plane in case of 3D curve. */
} A3DDrawingCurveData;

/*!
\brief Populates the \ref A3DDrawingCurveData structure
\ingroup a3d_drawing_curve
\version 5.0

\param [in] pDrawingCrv The drawing curve entity.
\param [out] pData Data of the drawing curve.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingCurveGet,(	const A3DDrawingCurve* pDrawingCrv,
													A3DDrawingCurveData* pData));


/*!
\brief Creates an \ref A3DDrawingCurve from \ref A3DDrawingCurveData structure
\ingroup a3d_drawing_curve
\version 5.0

\param [in] pData The input drawing curve data
\param [out] ppDrawingCrv The drawing curve entity

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingCurveCreate,(	const A3DDrawingCurveData* pData,
															A3DDrawingCurve** ppDrawingCrv));

#endif // __A3D_DRAWING_CURVE__




//##############################################################################
#ifndef __A3D_DRAWING_FILLEDAREAMODE_ENUM__
/*!
\addtogroup a3d_drawing_filledarea
@{
*/

/*!
\version 5.0

\brief Enumerations for drawing filled area mode for use in the \ref A3DDrawingFilledAreaData structure

In case of intersecting, or self-intersecting boundaries, \ref A3DEDrawingFilledAreaMode is used to determine the fill area.

For example, in case of two intersecting square boundaries, three different fill areas can be obtained like in the next picture.
\image html drawing_fillmode.png
*/

typedef enum
{
	kA3DDrawingFiledAreaModeOR								= 0,	/*!< Use OR operator. */
	kA3DDrawingFiledAreaModeAND							= 1,	/*!< Use AND operator. */
	kA3DDrawingFiledAreaModeXOR							= 2	/*!< Use XOR operator. */
} A3DEDrawingFilledAreaMode;

/*!
@} <!-- end of a3d_drawing_filledareamode_enums -->
*/

#endif // __A3D_DRAWING_FILLEDAREAMODE_ENUM__



//##############################################################################
#ifndef __A3D_DRAWING_FILLEDAREA__
/*!
\defgroup a3d_drawing_filledarea Drawing Filled Area
\ingroup a3d_drawing_entity
\version 5.0

Entity type is \ref kA3DTypeDrawingFilledArea.

*/

/*!
\brief DrawingFilledArea structure
\ingroup a3d_drawing_filledarea
\version 5.0
*/
typedef struct
{
	A3DUns16									m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DEDrawingFilledAreaMode			m_eMode;						/*!< Fill mode refers to \ref A3DEDrawingFilledAreaMode for more details. */
	A3DUns32									m_uiPatternIndex;			/*!< Pattern index. Refers to \ref a3d_graphics_module for more details. */
	A3DBool									m_bIgnoreViewTransfo;	/*!< Indiquate if drawing of pattern is independant of view transformation. \image html drawing_ignoreviewtransfo.png */
	A3DUns32									m_uiBoundaryCurvesSize;	/*!< Size of next array. */
	A3DCrvBase**							m_ppBoundaryCurves;		/*!< Array of closed curves. Refers to \ref a3d_crv for more details. \n
																					Each curve must be closed. Intersection area is treated with m_eMode parameter. */
} A3DDrawingFilledAreaData;

/*!
\brief Populates the \ref A3DDrawingFilledAreaData structure
\ingroup a3d_drawing_filledarea
\version 5.0

\param [in] pDrwFilledArea The drawing filled area entity.
\param [out] pData Data of the drawing filled area.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingFilledAreaGet,(const A3DDrawingFilledArea* pDrwFilledArea,
															A3DDrawingFilledAreaData* pData));


/*!
\brief Creates an \ref A3DDrawingFilledArea from \ref A3DDrawingFilledAreaData structure
\ingroup a3d_drawing_filledarea
\version 5.0

\param [in] pData The input drawing filled area data
\param [out] ppDrwFilledArea The drawing filled area entity

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingFilledAreaCreate,(const A3DDrawingFilledAreaData* pData,
																A3DDrawingFilledArea** ppDrwFilledArea));

#endif // __A3D_DRAWING_FILLEDAREA__



//##############################################################################
#ifndef __A3D_DRAWING_PICTURE__
/*!
\defgroup a3d_drawing_picture Drawing Picture
\ingroup a3d_drawing_entity
\version 5.0

Entity type is \ref kA3DTypeDrawingPicture.
*/

/*!
\brief DrawingPicture structure
\ingroup a3d_drawing_picture
\version 5.0
*/
typedef struct
{
	A3DUns16									m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32									m_uiPictureIndex;			/*!< Index of picture. Refers to \ref A3DGlobalGetGraphPictureData for more details. */
	A3DVector2dData						m_sPosition;				/*!< Position of the picture (bottom,left) in view or sheet space coordinate. \image html drawing_picture.png */
	A3DVector2dData						m_sSize;						/*!< Size of the picture in view or sheet space coordinate. */
} A3DDrawingPictureData;

/*!
\brief Populates the \ref A3DDrawingPictureData structure
\ingroup a3d_drawing_picture
\version 5.0

\param [in] pDrawingPicture The drawing picture entity.
\param [out] pData Data of the drawing picture.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingPictureGet,(const A3DDrawingPicture* pDrawingPicture,
														A3DDrawingPictureData* pData));

/*!
\brief Creates an \ref A3DDrawingPicture from \ref A3DDrawingPictureData structure
\ingroup a3d_drawing_picture
\version 5.0

\param [in] pData The input drawing picture data
\param [out] ppDrawingPicture The drawing picture entity

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingPictureCreate,(const A3DDrawingPictureData* pData,
															A3DDrawingPicture** ppDrawingPicture));

#endif // __A3D_DRAWING_PICTURE__



//##############################################################################
#ifndef __A3D_DRAWING_VERTICES__
/*!
\defgroup a3d_drawing_vertices Drawing Vertices
\ingroup a3d_drawing_entity
\version 5.0

Entity type is \ref kA3DTypeDrawingVertices.

\sa a3d_basewithgraphics

*/

/*!
\brief DrawingVertices structure
\ingroup a3d_drawing_vertices
\version 5.0
*/
typedef struct
{
	A3DUns16									m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32									m_uiPointsSize;			/*!< Size of next array. */
	A3DVector2dData*						m_pPoints;					/*!< Array of points. */
} A3DDrawingVerticesData;

/*!
\brief Populates the \ref A3DDrawingVerticesData structure
\ingroup a3d_drawing_vertices
\version 5.0

\param [in] pDrawingVertices The drawing vertices entity.
\param [out] pData Data of the drawing vertices.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingVerticesGet,(const A3DDrawingVertices* pDrawingVertices,
													A3DDrawingVerticesData* pData));


/*!
\brief Creates an \ref A3DDrawingVertices from \ref A3DDrawingVerticesData structure
\ingroup a3d_drawing_vertices
\version 5.0

\param [in] pData The input drawing vertices data
\param [out] ppDrawingVertices The drawing vertices entity

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDrawingVerticesCreate,(const A3DDrawingVerticesData* pData,
														A3DDrawingVertices** ppDrawingVertices));

#endif // __A3D_DRAWING_VERTICES__


#endif // __A3DPRCDRAWING_H__
