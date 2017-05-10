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
\brief      Header file for the markups symbol module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMARKUPSYMBOL_H__
#define __A3DPRCMARKUPSYMBOL_H__

#ifndef __A3DPRCMARKUPDEFINITION__
#error A3DSDKMarkupSemantic.h must be included before current file
#endif





#ifndef __A3D_MARKUPROUGHNESS__
/*!
\defgroup a3d_markuproughness Roughness
\ingroup a3d_markupsymbol
\version 4.0
*/

/*!
\enum EA3DMDRoughnessType
\ingroup a3d_markuproughness
\brief Enumerator that describes the roughness type
*/
typedef enum 
{
	KA3DRoughnessTypeBasic					= 1,	/*!< Basic surface texture. */
	KA3DRoughnessTypeMachining_Required		= 2,	/*!< Material removal by machining is required. */
	KA3DRoughnessTypeMachining_Prohibited	= 3		/*!< Material removal by machining is prohibited. */
} EA3DMDRoughnessType; 

/*!
\enum EA3DMDRoughnessContactArea
\ingroup a3d_markuproughness
\brief Enumerator that describes rough contact area type
*/
typedef enum 
{
	KA3DRoughnessContactSurfTexture					= 1,	/*!< Surface texture.							*/
	KA3DRoughnessContactSurfTextAndAllSrfAround		= 2,	/*!< Surface texture and all surfaces around.	*/
	KA3DRoughnessContactBasic						= 3,	 /*!< Basic contact.							*/
	KA3DRoughnessContactSrfAround					= 4		/*!< All surfaces around.						*/
} EA3DMDRoughnessContactArea; 

/*!
\enum EA3DMDRoughnessMode
\ingroup a3d_markuproughness
\brief Enumerator that describes the direction of lay
*/
typedef enum 
{ 
	KA3DRoughnessMode_None	= 0, /*!< No specified lay. */
	KA3DRoughnessModeM		= 1, /*!< Lay multi directional. */
	KA3DRoughnessModeC		= 2, /*!< Lay approximately circular. */
	KA3DRoughnessModeR		= 3, /*!< Lay approximately radial. */
	KA3DRoughnessModeP		= 4, /*!< Lay particulate, non-directional, or protuberant. */
	KA3DRoughnessModeX		= 5, /*!< Lay angular in both directions. */
	KA3DRoughnessModePARA	= 6, /*!< Lay approximately parallel to the line representing the surface. */
	KA3DRoughnessModePERP	= 7 /*!< Lay approximately perpendicular to the line representing the surface. */
} EA3DMDRoughnessMode;  





/*!
\struct A3DMarkupRoughnessData
\ingroup a3d_markuproughness
\brief Markup roughness
*/
/*!defined in file A3DSDKMarkupSymbol.h
\n Values of \ref m_eRoughType, \ref m_eRoughMode, and \ref m_eRoughContactArea define the Roughness symbol form.
\n The differents fields positions are placed all around the roughness symbol as we can see below.
\image html pmi_roughness_symbol.png
*/
typedef struct
{
	A3DUns16				m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*			m_pcField1;					/*!< Field 1. */
	A3DUTF8Char*			m_pcField2;					/*!< Field 2. */
	A3DUTF8Char*			m_pcField3;					/*!< Field 3. */
	A3DUTF8Char*			m_pcField4;					/*!< Field 4. */
	A3DUTF8Char*			m_pcField5;					/*!< Field 5. */
	A3DUTF8Char*			m_pcField6;					/*!< Field 6. */
	A3DUTF8Char*			m_pcField7;					/*!< Field 7. */
	A3DUTF8Char*			m_pcField8;					/*!< Field 8. */
	A3DUTF8Char*			m_pcRoughMode;				/*!< Describes the roughness mode as string. */

	EA3DMDRoughnessType m_eRoughType;					/*!< Describes the roughness type. */
	EA3DMDRoughnessMode m_eRoughMode;					/*!< Describes the roughness mode. */
	EA3DMDRoughnessContactArea m_eRoughContactArea;		/*!< Describes the roughness contact area. */

	A3DMDTextProperties* m_pTextProperties;				/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
}A3DMarkupRoughnessData;


/*!
\fn A3DStatus A3DMarkupRoughnessGet( const A3DMarkupRoughness* pMarkupRoughness, A3DMarkupRoughnessData* pData)
\brief Populates the \ref A3DMarkupRoughnessData structure
\ingroup a3d_markuproughness
\version 4.0

\param [in] pMarkupRoughness Input \ref A3DMarkupRoughness data structure.
\param [out] pData Output \ref A3DMarkupRoughnessData to be populated.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupRoughnessGet,( const A3DMarkupRoughness* pMarkupRoughness,
		 A3DMarkupRoughnessData* pData));



#endif	/*	__A3D_MARKUPROUGHNESS__ */




#ifndef __A3D_MARKUPBALLOON__

/*!
\defgroup a3d_markupballoon Balloon
\ingroup a3d_markupsymbol
\version 4.0
*/
/*!
\enum EA3DMDBalloonShape
\ingroup a3d_markupballoon
\brief Enumerator that describes balloon shape
*/
typedef enum 
{
	KA3DMDBalloonCircle				= 0, /*!< Circle Balloon. */
	KEA3DMDBalloonSquare			= 1, /*!< Square Balloon. */
	KEA3DMDBalloonDividedSquare		= 2, /*!< Divided Square Balloon. */
	KEA3DMDBalloonQuadrantCircle	= 3, /*!< Quadrant Circle Balloon. */
	KEA3DMDBalloonDividedCircle		= 4, /*!< Divided Circle Balloon. */
	KEA3DMDBalloonRoundedBox		= 5, /*!< Rounded Box Balloon. */
	KEA3DMDBalloonTriangle			= 6, /*!< Triangle Balloon. */
	KEA3DMDBalloonTriangleUp		= 7, /*!< Triangle Up Balloon. */
	KEA3DMDBalloonTriangleDown		= 8, /*!< Triangle Down Balloon. */
	KEA3DMDBalloonHexagon			= 9, /*!< Hexagon Balloon. */
	KEA3DMDBalloonDividedHexagon	= 10 /*!< Divided Hexagon Balloon. */
} EA3DMDBalloonShape; 


/*!
\struct A3DMarkupBalloonData
\brief Markup balloon
\ingroup a3d_markupballoon
\version 4.0

*/
typedef struct
{
	A3DUns16				m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */

	A3DUTF8Char*			m_pcUpText;			/*!< Up text. */
	A3DUTF8Char*			m_pcDownText;		/*!< Down text. */
	EA3DMDBalloonShape		m_eBalloonShape;	/*!< Balloon type. */
	A3DDouble				m_dBallownSize;		/*!< Balloon size. */
	A3DMDTextPosition*		m_psTextPosition;	/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
	A3DUns32				m_uiFileLinksSize;	/*!< Number of file links. */
	A3DUTF8Char**			m_ppFileLinks;		/*!< Array of file links. */
	A3DMDTextProperties*	m_pTextProperties;	/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
} A3DMarkupBalloonData;

/*!
\brief Populates the \ref A3DMarkupBalloonData structure
\ingroup a3d_markupballoon
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupBalloonGet,( const A3DMarkupBalloon* pBalloon,
													A3DMarkupBalloonData* pData));

#endif	/*	__A3D_MARKUPBALLOON__ */




#ifndef __A3D_MARKUPFASTENER__
/*!
\defgroup a3d_markupfastener Fastener
\ingroup a3d_markupsymbol
\version 4.0
*/


/*!
\struct A3DMarkupFastenerData
\brief Markup fastener
\ingroup a3d_markupfastener
\version 4.0

*/
typedef struct
{
	A3DUns16					m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */

	A3DDouble					m_dDiameter1;						/*!< Diameter 1. */
	A3DDouble					m_dDepth1;							/*!< Depth 1. */
	A3DDouble					m_dDiameter2;						/*!< Diameter 2. */
	A3DDouble					m_dDepth2;							/*!< Depth 2. */
	A3DDouble					m_dDiameter3;						/*!< Diameter 3. */
	A3DDouble					m_dDepth3;							/*!< Depth 3. */
	A3DDouble					m_dDiameter4;						/*!< Diameter 4. */
	A3DDouble					m_dDepth4;							/*!< Depth 4. */

	A3DUTF8Char*				m_sType;							/*!< Type. */
	A3DUTF8Char*				m_sTypeId;							/*!< Type ID. */
	A3DUTF8Char*				m_sSubtypeId;						/*!< Sub type ID. */
	A3DUns32					m_uiNoteTextsSize;					/*!< Number of note texts. */
	A3DUTF8Char**				m_ppNoteTextsNotes;					/*!< Array of note texts. */
	A3DUns16					m_iDecimalPlaces;					/*!< Display accuracy. */
	A3DVector3dData				m_sAxisVector;						/*!< Axis vector. */
	A3DVector3dData				m_sIndexVector;						/*!< Index vector. */
	A3DVector3dData				m_sOptionalVector;					/*!< Type. */
	A3DUns32					m_uiCoordinateEntitiesNotesSize;	/*!< Number of note texts. */
	A3DUTF8Char**				m_ppCoordinateEntitiesNotes;		/*!< Array of note texts. */
	A3DUTF8Char*				m_sStandard;						/*!< Standard. */
	A3DMDTextProperties*		m_pTextProperties;					/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
} A3DMarkupFastenerData;

/*!
\brief Populates the \ref A3DMarkupFastenerData structure
\ingroup a3d_markupfastener
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupFastenerGet,( const A3DMarkupFastener* pFastener,
		 A3DMarkupFastenerData* pData));

#endif	/*	__A3D_MARKUPFASTENER__ */




#ifndef __A3D_MARKUPLOCATOR__
/*!
\defgroup a3d_markuplocator Locator
\ingroup a3d_markupsymbol
\version 4.0
*/


/*!
\enum EA3DLocatorSymbol
\ingroup a3d_markuplocator
\brief Enumerations for symbol type
\version 4.0
*/
typedef enum
{
	KEA3DSymbolUnknown	= -1,	/*!< Undocumented. */
	KEA3DEdge			= 0,	/*!< Undocumented. */
	KEA3DHole			= 1,	/*!< Undocumented. */
	KEA3DSurface		= 2,	/*!< Undocumented. */
	KEA3DRectangle		= 3,	/*!< Undocumented. */
	KEA3DSlot			= 4,	/*!< Undocumented. */
	KEA3DFreeform		= 5		/*!< Undocumented. */
}EA3DLocatorSymbol;


/*!
\enum EA3DLocatorType
\ingroup a3d_markuplocator
\brief Enumerations for type
\version 4.0
*/
typedef enum
{
	KEA3DLocatorUnknown			=-1,	/*!< Undocumented. */
	KEA3DMain						= 0,	/*!< Undocumented. */
	KEA3DSecondary					= 1,	/*!< Undocumented. */
	KEA3DMainPermTransf			= 2,	/*!< Undocumented. */
	KEA3DSecondaryPermTransf		= 3,	/*!< Undocumented. */
	KEA3DSecondaryCoordination		= 4,	/*!< Undocumented. */
	KEA3DCoordination				= 5,	/*!< Undocumented. */
	KEA3DAccessClearance			= 6,	/*!< Undocumented. */
	KEA3DDetached					= 7,	/*!< Undocumented. */
	KEA3DBlank						= 8,	/*!< Undocumented. */
	KEA3DCorrectable				= 9,	/*!< Undocumented. */
	KEA3DAuxiliaryRest				= 10,	/*!< Undocumented. */
	KEA3DJclamps					= 11	/*!< Undocumented. */
}EA3DLocatorType;

/*!
\enum EA3DLocatorSubType
\ingroup a3d_markuplocator
\brief Enumerations for type
\version 4.0
*/
typedef enum
{
	KEA3DSubtypeUnknown		= -1,	/*!< Undocumented. */
	KEA3DDiesMolds				= 0,	/*!< Undocumented. */
	KEA3DFixing				= 1,	/*!< Undocumented. */
	KEA3DTemporaryTransferred	= 2,	/*!< Undocumented. */
	KEA3DMechanicallyFastened	= 3,	/*!< Undocumented. */
	KEA3DManufacturingAssembly	= 4		/*!< Undocumented. */
}EA3DLocatorSubType;
/*!
\enum EA3DLocatorCoordinatePlane
\ingroup a3d_markuplocator
\brief Enumerations for type
\version 4.0
*/
typedef enum
{
	KEA3DCoordPlaneUnknown	= -1,	/*!< Undocumented. */
	KEA3DCoordPlaneX					= 0,	/*!< Undocumented. */
	KEA3DCoordPlaneY					= 1,	/*!< Undocumented. */
	KEA3DCoordPlaneZ					= 2,	/*!< Undocumented. */
	KEA3DCoordPlaneXY				= 3,	/*!< Undocumented. */
	KEA3DCoordPlaneXZ				= 4,	/*!< Undocumented. */
	KEA3DCoordPlaneYZ				= 5,	/*!< Undocumented. */
	KEA3DCoordPlaneXYZ				= 6		/*!< Undocumented. */
}EA3DLocatorCoordinatePlane;

/*!
\enum EA3DLocatorChangeLevel
\ingroup a3d_markuplocator
\brief Enumerations for type
\version 4.0
*/
typedef enum 
{
	KEA3DLevelUnknown	= -1,	/*!< Undocumented. */
	KEA3DHard			= 0,	/*!< Undocumented. */
	KEA3DMedium		= 1,	/*!< Undocumented. */
	KEA3DSoft			= 2		/*!< Undocumented. */
} EA3DLocatorChangeLevel;



/*!
\enum EA3DLocatorSubscript
\ingroup a3d_markuplocator
\brief Enumerations for type
\version 4.0
*/
typedef enum 
{
	KEA3DLocatorSubscriptO	= 1<<0,	/*!< Undocumented. */
	KEA3DLocatorSubscriptS	= 1<<1,	/*!< Surface main. */
	KEA3DLocatorSubscriptK	= 1<<2,	/*!< Undocumented. */
	KEA3DLocatorSubscriptC	= 1<<3,	/*!< Undocumented. */
	KEA3DLocatorSubscriptF	= 1<<4	/*!< Undocumented. */
}EA3DLocatorSubscript;


/*!
\struct A3DMarkupLocatorData
\brief Markup locator
\ingroup a3d_markuplocator
\version 4.0

*/
typedef struct
{
	A3DUns16					m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */

	EA3DLocatorSymbol			m_eSymbol;						/*!< Symbol type. */
	EA3DLocatorType				m_eType;						/*!< Type. */
	EA3DLocatorSubType			m_eSubType;						/*!< Sub type. */
	EA3DLocatorCoordinatePlane	m_eCoordinatePlane;				/*!< Coordinate plane type. */
	EA3DLocatorChangeLevel		m_eChangeLevel;					/*!< Change level. */
	A3DUns32					m_iDecimalPlaces;				/*!< Display accuracy. */
	A3DUTF8Char*				m_sNoteFont;					/*!< Corresponding font for following note. */
	A3DUTF8Char*				m_sNote;						/*!< Note fonts. */
	A3DUTF8Char*				m_sPartNumberFont;				/*!< Corresponding font for following text. */
	A3DUTF8Char*				m_sPartNumber;					/*!< Part number. */
	A3DUns32					m_uiCoordinateEntitiesNotesSize;/*!< Number of coordinate entities notes. */
	A3DUTF8Char**				m_sCoordinateEntitiesNotesFont;	/*!< Array of note fonts. */
	A3DUTF8Char**				m_sCoordinateEntitiesNotes;		/*!< Array of coordinate entities notes. */
	A3DVector3dData				m_sHotSpot;						/*!< Hot spot. */
	A3DVector3dData				m_sPunchDirection;				/*!< Punch direction. */
	A3DVector3dData				m_sPinDirection;				/*!< Pin direction. */
	A3DVector3dData				m_sNormalDirection;				/*!< Normal direction. */
	A3DUns32					m_iUnit;						/*!< 1 = mm, 2 = inch, 3 = radian, 4 = degree, 5 = grade, -1 no unit defined, use meter. */
	A3DDouble					m_dAccuracy;					/*!< Accuracy. */
	A3DUns16					m_ucSubscripts;					/*!< A combination of EA3DLocatorSubscript enum values. */
	A3DMDTextProperties*		m_pTextProperties;				/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */

} A3DMarkupLocatorData;

/*!
\brief Populates the \ref A3DMarkupLocatorData structure
\ingroup a3d_markuplocator
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupLocatorGet,( const A3DMarkupLocator* pLocator,
		 A3DMarkupLocatorData* pData));



#endif	/*	__A3D_MARKUPLOCATOR__ */




#ifndef __A3D_MARKUPMEASUREMENTPOINT__
/*!
\defgroup a3d_markupmeasurementpoint Measurement point
\ingroup a3d_markupsymbol
\version 4.0
*/


/*!
\struct A3DMarkupMeasurementPointData
\brief Markup measurement point
\ingroup a3d_markupmeasurementpoint
\version 4.0

*/
typedef struct
{
	A3DUns16					m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*				m_sLevel;
	A3DVector3dData				m_sLocation;
	A3DVector3dData				m_sMeasurementVector;
	A3DVector3dData				m_sCoordinationVector;
	A3DVector3dData				m_sNormalVector;
	A3DUns32					m_uiCoordinateEntitiesNotesSize;/*!< Number of coordinate entities notes. */
	A3DUTF8Char**				m_sCoordinateEntitiesNotesFont;	/*!< Array of note fonts. */
	A3DUTF8Char**				m_sCoordinateEntitiesNotes;		/*!< Array of coordinate entities notes. */
	EA3DMDMarkupDisplayType		m_eDisplayType;
	A3DMDTextProperties*		m_pTextProperties;				/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
} A3DMarkupMeasurementPointData;

/*!
\brief Populates the \ref A3DMarkupMeasurementPointData structure
\ingroup a3d_markupmeasurementpoint
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupMeasurementPointGet,( const A3DMarkupMeasurementPoint* pMeasurementPoint,
		 A3DMarkupMeasurementPointData* pData));




#endif	/*	__A3D_MARKUPMEASUREMENTPOINT__ */


#endif	/*	__A3DPRCMARKUPSYMBOL_H__ */
