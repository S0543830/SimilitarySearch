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
\brief      Header file for the markup welding module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMarkupWelding_H__
#define __A3DPRCMarkupWelding_H__

#ifndef __A3DPRCMARKUPDEFINITION__
#error A3DSDKMarkupSemantic.h must be included before current file
#endif


/*!
\enum EA3DMDLineWeldingType
\ingroup a3d_markupwelding
\brief Enumerator that describes the direction of lay
*/
typedef enum
{
	KEA3DMDWeldTypeUnknown						= -1, /*!< Unknown. */
	KEA3DMDWeldTypeNone							= 0, /*!< None. */
	KEA3DMDWeldTypeEdgeFlange					= 1, /*!< Undocumented. */
	KEA3DMDWeldTypeSquare						= 2, /*!< Square butt weld: \image html KEA3DMDWeldTypeSquare.png */
	KEA3DMDWeldTypeSingleV						= 3, /*!< Single V butt weld: \image html KEA3DMDWeldTypeSingleV.png*/
	KEA3DMDWeldTypeSingleBevel					= 4, /*!< Single bevel butt weld: \image html KEA3DMDWeldTypeSingleBevel.png */
	KEA3DMDWeldTypeBroadRootFaceSingleV			= 5, /*!< Undocumented. */
	KEA3DMDWeldTypeBroadRootFaceSingleBevel		= 6, /*!< Undocumented. */
	KEA3DMDWeldTypeSingleU						= 7, /*!< Single U butt weld: \image html KEA3DMDWeldTypeSingleU.png */
	KEA3DMDWeldTypeSingleJ						= 8, /*!< Single J butt weld: \image html KEA3DMDWeldTypeSingleJ.png */
	KEA3DMDWeldTypeBacking						= 9, /*!< Back weld: \image html KEA3DMDWeldTypeBacking.png */
	KEA3DMDWeldTypeFillet						= 10, /*!< Fillet weld: \image html KEA3DMDWeldTypeFillet.png */
	KEA3DMDWeldTypePlug							= 11, /*!< Plug weld: \image html KEA3DMDWeldTypePlug.png */
	KEA3DMDWeldTypeSeam							= 12, /*!< Undocumented. */
	KEA3DMDWeldTypeSteepFlankedSingleV		= 13, /*!< Steep-flanked single-V butt weld: \image html KEA3DMDWeldTypeSteepFlankedSingleV.png */
	KEA3DMDWeldTypeSteepFlankedSingleBevel	= 14, /*!< Steep-flanked single-bevel butt weld: \image html KEA3DMDWeldTypeSteepFlankedSingleBevel.png */
	KEA3DMDWeldTypeEdge							= 15, /*!< Undocumented. */
	KEA3DMDWeldTypeSurface						= 16, /*!< Surfacing weld: \image html KEA3DMDWeldTypeSurface.png */
	KEA3DMDWeldTypeSurfaceJoint				= 17, /*!< Undocumented. */
	KEA3DMDWeldTypeInclinedJoint				= 18, /*!< Undocumented. */
	KEA3DMDWeldTypeFoldJoint					= 19, /*!< Undocumented. */
	KEA3DMDWeldTypeSpot							= 20, /*!< Spot weld: \image html KEA3DMDWeldTypeSpot.png */
	KEA3DMDWeldTypePermanentBackStrip		= 21, /*!< Permanent backing strip used: \image html KEA3DMDWeldTypePermanentBackStrip.png */
	KEA3DMDWeldTypeRemovableBackStrip		= 22, /*!< Removable backing strip used: \image html KEA3DMDWeldTypeRemovableBackStrip.png */
	KEA3DMDWeldTypeUnspecifiedEdgeType		= 23, /*!< Undocumented. */
	KEA3DMDWeldTypeFlare_V_Butt				= 24, /*!< Flare V butt weld: \image html KEA3DMDWeldTypeFlare_V_Butt.png */
	KEA3DMDWeldTypeFlare_Bevel_Butt			= 25, /*!< Flare Bevel butt weld: \image html KEA3DMDWeldTypeFlare_Bevel_Butt.png */
	KEA3DMDWeldTypeSingleEdgeFlange			= 26	/*!< Undocumented. */
} EA3DMDLineWeldingType;

/*!
\enum EA3DMDLineWeldingSupplSymbolType
\ingroup a3d_markupwelding
\brief Line Welding supplementary symbol description
*/
typedef enum
{
	KEA3DMDWeldAddSymbolUnknown				= -1, /*!< Unknown. */
	KEA3DMDWeldAddSymbolNone					= 0, /*!< None. */
	KEA3DMDWeldAddSymbolFlush					= 1, /*!< \image html KE_LineWeldSuppl_Flush.png */
	KEA3DMDWeldAddSymbolConvex					= 2, /*!< Weld with convex face: \image html KEA3DMDWeldAddSymbolConvex.png */
	KEA3DMDWeldAddSymbolConcave				= 3, /*!< Weld with concave face: \image html KEA3DMDWeldAddSymbolConcave.png */
	KEA3DMDWeldAddSymbolToesBlended			= 4, /*!< Fillet weld with smooth blended face: \image html KEA3DMDWeldAddSymbolToesBlended.png */
	KEA3DMDWeldAddSymbolFlushFinished		= 5, /*!< Flush finished weld: \image html KEA3DMDWeldAddSymbolFlushFinished.png */
	KEA3DMDWeldAddSymbolBackingPermanent	= 6, /*!< Undocumented. */
	KEA3DMDWeldAddSymbolBackingpRemovable	= 7 /*!< Undocumented. */
} EA3DMDLineWeldingSupplSymbolType;

/*!
\enum EA3DMDLineWeldingFinishSymbol
\ingroup a3d_markupwelding
\brief Line Welding finish symbol description
*/
typedef enum
{
	KEA3DMDWeldFinishSymbolNone			= 0, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolC				= 1, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolF				= 2, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolG				= 3, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolH				= 4, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolM				= 5, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolR				= 6, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolU				= 7, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolChipping	= 8, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolGrinding	= 9, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolHammering	= 10, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolMachining	= 11, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolRolling		= 12, /*!< Undocumented. */
	KEA3DMDWeldFinishSymbolPeening		= 13 /*!< Undocumented. */
} EA3DMDLineWeldingFinishSymbol;


/*!
\enum EA3DMDLineWeldingOption
\ingroup a3d_markupwelding
\brief Line Welding symbol options description
*/
typedef enum
{
	KEA3DMDLineWeldOptionUnknown			= -1, /*!< Unknown. */
	KEA3DMDLineWeldOptionNone				= 0, /*!< None. */
	KEA3DMDLineWeldOptionAllAround		= 0x00100, /*!< Weld applies all around. */
	KEA3DMDLineWeldOptionFieldWeld		= 0x00200, /*!< Unfinished flag. */
	KEA3DMDLineWeldOptionReferenceSign	= 0x00400, /*!< Reference frame. */
	KEA3DMDLineWeldOptionTail				= 0x00800, /*!< Process symbol. */
	KEA3DMDLineWeldOptionIdentifLine		= 0x01000, /*!< Additionnal dotted line. */
	KEA3DMDLineWeldOptionIdentifLineUp	= 0x02000, /*!< Additionnal dotted line up. */
	KEA3DMDLineWeldOptionTextSideDown	= 0x04000 /*!< Up/down reversing for approx texts and others. */
} EA3DMDLineWeldingOption;

/*!
\enum EA3DMDSpotWeldType
\ingroup a3d_markupwelding
\brief Spot welding symbol type description
*/
typedef enum
{
	KEA3DMDSpotWeldTypeUnknown		= -1, /*!< Unknown. */
	KEA3DMDSpotWeldTypeNone			= 0, /*!< None. */
	KEA3DMDSpotWeldTypeResistance	= 1, /*!< Undocumented. */
	KEA3DMDSpotWeldTypeProjection	= 2 /*!< Undocumented. */
} EA3DMDSpotWeldType;

/*!
\enum EA3DMDSpotWeldThickness
\ingroup a3d_markupwelding
\brief Spot welding thickness description
*/
typedef enum
{
	KEA3DMDSpotWeldThickUnknown	= -1, /*!< Unknown. */
	KEA3DMDSpotWeldThick_None		= 0, /*!< None. */
	KEA3DMDSpotWeldTwoThick		= 1, /*!< Undocumented. */
	KEA3DMDSpotWeldThreeThick		= 2, /*!< Undocumented. */
	KEA3DMDSpotWeldE_FourThick	= 3 /*!< Undocumented. */
} EA3DMDSpotWeldThickness;

/*!
\struct A3DMarkupSpotWeldingData
\brief Markup spot welding symbol
\ingroup a3d_markupwelding
\version 4.0
*/
typedef struct 
{
	A3DUns16							m_usStructSize;						/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	EA3DMDSpotWeldType					m_eType;							/*!< Undocumented. */
	EA3DMDSpotWeldThickness				m_eThickness;						/*!< Undocumented. */
	A3DBool								m_bIsCritical;						/*!< Undocumented. */
	A3DDouble							m_dDiameter;						/*!< Undocumented. */
	A3DUTF8Char*						m_pcJointId;						/*!< Undocumented. */
	A3DUTF8Char*						m_pcGroupId;						/*!< Undocumented. */
	A3DUTF8Char*						m_pcProcess;						/*!< Undocumented. */
	A3DUns32							m_uiCoordinateEntitiesNotesSize;	/*!< Number of note texts. */
	A3DUTF8Char**						m_ppCoordinateEntitiesNotes;		/*!< Array of note texts. */
	A3DVector3dData						m_sApproachVector;					/*!< Undocumented. */
	A3DVector3dData						m_sClampingVector;					/*!< Undocumented. */
	A3DVector3dData						m_sNormalVector;					/*!< Undocumented. */
	A3DMDTextProperties*				m_pTextProperties;					/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
} A3DMarkupSpotWeldingData;


/*!
\brief Populates the \ref A3DMarkupSpotWeldingData structure
\ingroup  a3d_markupwelding
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupSpotWeldingGet,(	const A3DMarkupSpotWelding* pSpotWelding,
		 A3DMarkupSpotWeldingData* pData));

/*!
\struct A3DMarkupLineWeldingData
\brief Markup line welding symbol
\ingroup  a3d_markupwelding
\version 4.0
\details 
\image html pmi_welding_symbol.png
*/
typedef struct 
{
	A3DUns16								m_usStructSize;						/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	EA3DMDLineWeldingType					m_eArrowSideType;					/*!< Undocumented. */
	EA3DMDLineWeldingSupplSymbolType		m_eArrowSideSupplType;				/*!< Undocumented. */
	A3DUTF8Char*							m_pcArrowSideValue;					/*!< Undocumented. */
	A3DUTF8Char*							m_pcArrowSideLongitudinalValue;		/*!< Undocumented. */
	A3DUTF8Char*							m_pcArrowSideStaggeredValue;		/*!< Undocumented. */
	EA3DMDLineWeldingFinishSymbol			m_eArrowSideFinishSymbol;			/*!< Undocumented. */
	A3DUTF8Char*							m_pcArrowSideAngle;					/*!< Groove Angle or Countersink Angle, degree symbol to add. */
	A3DUTF8Char*							m_pcArrowSideNumRootDepth;			/*!< Undocumented. */
	A3DUTF8Char*							m_pcArrowSideSize;					/*!< Undocumented. */
	A3DUTF8Char*							m_pcArrowSidePitch;					/*!< Undocumented. */
	EA3DMDLineWeldingType					m_eOtherSideType;					/*!< Undocumented. */
	EA3DMDLineWeldingSupplSymbolType		m_eOtherSideSupplType;				/*!< Undocumented. */
	A3DUTF8Char*							m_pcOtherSideValue;					/*!< Undocumented. */
	A3DUTF8Char*							m_pcOtherSideLongitudinalValue;		/*!< Undocumented. */
	A3DUTF8Char*							m_pcOtherSideStaggeredValue;		/*!< Undocumented. */
	EA3DMDLineWeldingFinishSymbol			m_eOtherSideFinishSymbol;			/*!< Undocumented. */
	A3DUTF8Char*							m_pcOtherSideAngle;					/*!< Undocumented. */
	A3DUTF8Char*							m_pcOtherSideNumRootDepth;			/*!< Undocumented. */
	A3DUTF8Char*							m_pcOtherSideSize;					/*!< Undocumented. */
	A3DUTF8Char*							m_pcOtherSidePitch;					/*!< Undocumented. */
	A3DUTF8Char*							m_pcStandard;						/*!< Undocumented. */
	A3DUns32								m_uiNumberOfProcesses;				/*!< Undocumented. */
	A3DUns32								m_uiNumberOfCoordinate;				/*!< Undocumented. */
	A3DUTF8Char**							m_ppcProcess;						/*!< Undocumented. */
	A3DUns32								m_uiCoordinateEntitiesNotesSize;	/*!< Number of note texts. */
	A3DUTF8Char**							m_ppCoordinateEntitiesNotes;		/*!< Array of note texts. */
	A3DUns32								m_uiProcessNotesSize;				/*!< Number of process texts. */
	A3DUTF8Char**							m_ppProcessNotes;					/*!< Array of process texts. */
	A3DMDTextProperties* m_pTextProperties;										/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
} A3DMarkupLineWeldingData;

/*!
\brief Populates the \ref A3DMarkupLineWeldingData structure
\ingroup  a3d_markupwelding
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupLineWeldingGet,(	const A3DMarkupLineWelding* pLineWelding,
		 A3DMarkupLineWeldingData* pData));

#endif	/*	__A3DPRCMarkupWelding_H__ */
