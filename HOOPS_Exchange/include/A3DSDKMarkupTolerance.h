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
\brief      Header file for the tolerance markup module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMARKUPTOLERANCE_H__
#define __A3DPRCMARKUPTOLERANCE_H__

#ifndef __A3DPRCMARKUPDEFINITION__
#error A3DSDKMarkupSemantic.h must be included before current file
#endif




#ifndef __A3D_MARKUPDATUMN__

/*!
\defgroup a3d_markupdatum Datum
\ingroup a3d_markuptolerance
\version 4.0
*/


/*!
\struct A3DMarkupDatumData
\ingroup a3d_markupdatum
\brief Markup datum
\details
This structure stored the definition of markups datum identifier and markups datum target according the several options
\image html pmi_datum.png
*/
typedef struct
{
	A3DUns16						m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*					m_pcUpText;			/*!< Up text. */
	A3DUTF8Char*					m_pcDownText;		/*!< Down text. */
	A3DBool							m_bTarget;			/*!< Option: Is target? */
	A3DBool							m_bDiameter;		/*!< Option: Is diameter? */
	A3DBool							m_bIndividual;		/*!< Option: Is individual? */
	A3DMDTextProperties*			m_pTextProperties;	/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
}A3DMarkupDatumData;


/*!
\fn A3DStatus A3DMarkupDatumGet( const A3DMarkupDatum* pMarkupDatum, A3DMarkupDatumData* pData)
\brief Populates the \ref A3DMarkupDatumData structure
\ingroup a3d_markupdatum
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupDatumGet,( const A3DMarkupDatum* pMarkupDatum,
												A3DMarkupDatumData* pData));



#endif	/*	__A3D_MARKUPDATUMN__ */



#ifndef __A3D_MARKUPGDT__

/*!
\defgroup a3d_markupgdt Geometrical dimensioning tolerance
\ingroup a3d_markuptolerance
\version 4.0
\details
A markup GDT is composed of appended texts and an array of tolerances. In this version, only features control frame tolerance (ref A3DMDFeatureControlFrameData) are yet implemented.
\image html pmi_markup_gdt.png
*/

/*!
\defgroup a3d_markupfcf Feature control frame
\ingroup a3d_markupgdt
\version 4.0
\details
see in the following description of a feature control frame with two rows
\image html pmi_markup_fcf_row.png
*/

/*!
\defgroup a3d_markupfcfrow Drawing row
\ingroup a3d_markupfcf
\version 4.0
\details
\image html pmi_markup_fcf_drawing_row.png
*/

/*!
\defgroup a3d_markupfcf_semanticrow Semantic drawing row value
\ingroup a3d_markupfcfrow
\version 5.2
*/
/*!
\defgroup a3d_markupfcfdftrow Drafting row
\ingroup a3d_markupfcf
\version 4.0
\details
\image html pmi_markup_fcf_drafting_row.png
*/
/*!
\enum EA3DGDTType
\ingroup a3d_markupfcfrow
\brief Enumerations for row type
\version 4.0
\image html pmi_gdt_types.png
*/
typedef enum
{ 
	KEA3DGDTTypeNone					= 0,	/*!< Undocumented. */
	KEA3DGDTTypeStraightness			= 1,	/*!< Straightness. */
	KEA3DGDTTypeFlatness				= 2,	/*!< Flatness. */
	KEA3DGDTTypeCircularity				= 3,	/*!< Circularity. */
	KEA3DGDTTypeCylindricity			= 4,	/*!< Cylindricity. */
	KEA3DGDTTypeLineProfile				= 5,	/*!< Profile of a line. */
	KEA3DGDTTypeSurfaceProfile			= 6,	/*!< Profile of a surface. */
	KEA3DGDTTypeAngularity				= 7,	/*!< Angularity. */
	KEA3DGDTTypePerpendicularity		= 8,	/*!< Perpendicularity. */
	KEA3DGDTTypeParallelism				= 9,	/*!< Parallel. */
	KEA3DGDTTypePosition				= 10,	/*!< Positional. */
	KEA3DGDTTypeConcentricity			= 11,	/*!< Concentricity. */
	KEA3DGDTTypeSymmetry				= 12,	/*!< Symmetric. */
	KEA3DGDTTypeCircularRunout			= 13,	/*!< Circular run out. */
	KEA3DGDTTypeTotalRunout				= 14	/*!< Total run out. */
}EA3DGDTType;
/*!
\struct A3DMDFCFDraftingRowData
\ingroup a3d_markupfcfdftrow
\brief FCF drafting row
\sa A3DMDFCFDraftingRowGet
*/
typedef struct
{
	A3DUns16			m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	EA3DGDTType			m_eType;					/*!< GDT type. */
	A3DUns32			m_uiNumberOfTextsInBoxes;	/*!< Number of texts in boxes. */
	A3DUTF8Char**		m_ppcTextsInBoxes;			/*!< Texts in row boxes, code with RTF format. See \ref a3d_markup_rtf. */
}A3DMDFCFDraftingRowData;


/*!
\fn A3DStatus A3DMDFCFDraftingRowGet( const A3DMDFCFDraftingRow* pFDraftingRow, A3DMDFCFDraftingRowData* pData)
\brief Populates the \ref A3DMDFCFDraftingRowData structure
\ingroup a3d_markupfcfdftrow
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDFCFDraftingRowGet,( const A3DMDFCFDraftingRow* pDraftingRow,
		 A3DMDFCFDraftingRowData* pData));






/*!
\enum A3DMDGDTValueType
\ingroup a3d_markupfcfrow
\brief Enumerations for modifier type
\version 4.0

*/
typedef enum
{
	KEA3DGDTValueNone			= 0, /*!< No modifier defined. */
	KEA3DGDTValueDiameter		= 1, /*!< Diameter value type. */
	KEA3DGDTValueRadius			= 2, /*!< Radial value type. */
	KEA3DGDTValueSpherical		= 3  /*!< Spherical value type. */
} A3DMDGDTValueType;


/*!
\enum EA3DMDGDTModifierType
\ingroup a3d_markupfcfrow
\brief Enumerations for modifier type
\image html pmi_gdt_modifiers.png
\version 4.0

*/
typedef enum
{
	KEA3DGDTModifierNone			= 0, /*!< No modifier defined. */
	KEA3DGDTModifierMax				= 1, /*!< Maximum material condition. */
	KEA3DGDTModifierMin				= 2, /*!< Least material condition. */
	KEA3DGDTModifierProj			= 3, /*!< Projected tolerance zone. */
	KEA3DGDTModifierFree			= 4, /*!< Free State. */
	KEA3DGDTModifierRfs				= 5, /*!< Regardless of feature size. */
	KEA3DGDTModifierTangent			= 6, /*!< Tangent plane. */
	KEA3DGDTModifierST				= 8  /*!< Statistical. */
} EA3DMDGDTModifierType;

/*!
\struct A3DMDFCValueData
\ingroup a3d_markupfcf_semanticrow
\brief Tolerance value. Value can be double or string according to m_bIsValue.
\sa A3DMDFCFToleranceValueData
*/
typedef struct
{
	A3DUns16				m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble					m_dValue;	/*!< Value. */
	A3DUTF8Char*			m_pcValue;		/*!< User value. */
	A3DBool					m_bIsValue;		/*!< If it's true, value is user value. */
}A3DMDFCValueData;


/*!
\fn A3DStatus A3DMDFCValueGet( const A3DMDFCValue* pToleranceValue, A3DMDFCValueData* pData)
\brief Populates the \ref A3DMDFCValueData structure
\ingroup a3d_markupfcf_semanticrow
\version 5.2


\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDFCValueGet,( const A3DMDFCValue* pValue,
		 A3DMDFCValueData* pData));


/*!
\struct A3DMDFCTolerancePerUnitData
\ingroup a3d_markupfcf_semanticrow
\brief Tolerance per unit
\sa AA3DMDFCTolerancePerUnitData
*/
typedef struct
{
	A3DUns16				m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble				m_dUnitLengthOrAreaFirstValue;	/*!< Length 1. */
	A3DDouble*				m_pdUnitAreaSecondLength;		/*!< Length 2: if non null, it defines the second value of the area. */
	A3DMDFCValue*			m_psRefinementZone;				/*!< Refinement zone. */
}A3DMDFCTolerancePerUnitData;


/*!
\fn A3DStatus A3DMDFCTolerancePerUnitGet( const A3DMDFCTolerancePerUnit* pTolerancePerUnit, A3DMDFCTolerancePerUnitData* pData)
\brief Populates the \ref A3DMDFCTolerancePerUnitData structure
\ingroup a3d_markupfcf_semanticrow
\version 5.2


\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDFCTolerancePerUnitGet,( const A3DMDFCTolerancePerUnit* pTolerancePerUnit,
		 A3DMDFCTolerancePerUnitData* pData));



/*!
\struct A3DMDFCProjectedZoneData
\ingroup a3d_markupfcf_semanticrow
\brief Projected tolerance zone 
\sa AA3DMDFCProjectedZoneData
*/
typedef struct
{
	A3DUns16				m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMDFCValueData		m_sLength;			/*!< Length. */
	A3DDouble*				m_pdPosition;		/*!< Position minimum dimension. */
}A3DMDFCProjectedZoneData;


/*!
\fn A3DStatus A3DMDFCProjectedZoneGet( const A3DMDFCProjectedZone* pProjectedZone, A3DMDFCProjectedZoneData* pData)
\brief Populates the \ref A3DMDFCProjectedZoneData structure
\ingroup a3d_markupfcf_semanticrow
\version 5.2


\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDFCProjectedZoneGet,( const A3DMDFCProjectedZone* pProjectedZone,
		 A3DMDFCProjectedZoneData* pData));


/*!
\struct A3DMDFCFToleranceValueData
\ingroup a3d_markupfcf_semanticrow
\brief FCF tolerance value
\sa A3DMDFCFToleranceValueData
*/
typedef struct
{
	A3DUns16						m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMDFCValueData				m_sValue;				/*!< Global value. */
	A3DMDFCTolerancePerUnit*		m_psTolerancePerUnit;	/*!< Tolerance per unit definition. */
	A3DMDFCProjectedZone*			m_psProjectedZone;		/*!< Projected tolerance zone definition. */
	A3DMDFCValue*					m_psProfileTolerance;	/*!< Precision of the profile tolerance. */
	A3DMDFCValue*					m_psMaximumBonus;		/*!< Maximum bonus. */
}A3DMDFCFToleranceValueData;


/*!
\fn A3DStatus A3DMDFCFToleranceValueGet( const A3DMDFCFToleranceValue* pToleranceValue, A3DMDFCFToleranceValueData* pData)
\brief Populates the \ref A3DMDFCFToleranceValueData structure
\ingroup a3d_markupfcfrow
\version 5.2


\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDFCFToleranceValueGet,( const A3DMDFCFToleranceValue* pToleranceValue,
		 A3DMDFCFToleranceValueData* pData));



/*!
\struct A3DMDFCFRowDatumData
\ingroup a3d_markupfcfrow
\brief FCF datum row
\sa A3DMDFCFRowDatumDataData
*/
typedef struct
{
	A3DUns16						m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*					m_pcDatum;			/*!< Datum label. */
	EA3DMDGDTModifierType			m_eModifier;		/*!< Modifier type. */
	A3DMDFCFRowDatum*				m_pNext;			/*!< Next datum, non null in case of composite datum. */
	A3DMiscMarkupLinkedItem* m_pLinkedItem;				/*!< Represents the link with an entity. It must be one of owner (markup GDT or reference frame) of linked item array (see A3DMkpMarkupData). */
}A3DMDFCFRowDatumData;


/*!
\fn A3DStatus A3DMDFCFRowDatumGet( const A3DMDFCFRowDatum* pRowDatum, A3DMDFCFRowDatumData* pData)
\brief Populates the \ref A3DMDFCFRowDatumData structure
\ingroup a3d_markupfcfrow
\version 4.0


\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDFCFRowDatumGet,( const A3DMDFCFRowDatum* pRowDatum,
		 A3DMDFCFRowDatumData* pData));



/*!
\struct A3DMDFCFDrawingRowData
\ingroup a3d_markupfcfrow
\brief FCF drawing row
\sa A3DMDFCFDrawingRowData
\version 4.0
*/
typedef struct
{
	A3DUns16					m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	EA3DGDTType					m_eType;			/*!< GDT type. */
	A3DUTF8Char*				m_pcValue;			/*!< Value. */
	A3DMDFCFToleranceValue*		m_psSemanticValue;	/*!< Semantic value. */
	A3DMDGDTValueType			m_eValueType;		/*!< Value type. */
	EA3DMDGDTModifierType		m_eModifier;		/*!< Modifier type. */
	A3DBool						m_bFreeState;		/*!< Free state. */
	A3DBool						m_bStatistical;		/*!< Statistical. */
	A3DMDFCFRowDatum*			m_psPrimaryRef;		/*!< Primary reference. */
	A3DMDFCFRowDatum*			m_psSecondaryRef;	/*!< Secondary reference. */
	A3DMDFCFRowDatum*			m_psTertiaryRef;	/*!< Tertiary reference. */
}A3DMDFCFDrawingRowData;


/*!
\fn A3DStatus A3DMDFCFDrawingRowGet( const A3DMDFCFDrawingRow* pDrawingRow, A3DMDFCFDrawingRowData* pData)
\brief Populates the \ref A3DMDFCFDrawingRowData structure
\ingroup a3d_markupfcfrow
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDFCFDrawingRowGet,( const A3DMDFCFDrawingRow* pDrawingRow,
		 A3DMDFCFDrawingRowData* pData));





/*!
\brief Populates the \ref A3DMDFCFDrawingRowData structure whatever the row type
\brief Note that if the drawing row is not defined with a tolerance value, the function returns \ref A3D_MARKUP_SEMANTIC_TOL_VALUE_NOT_SET
\sa A3DMDFCFDrawingRowData

\ingroup a3d_markupfcfrow
\version 5.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_MARKUP_SEMANTIC_DEFINITION_NOT_SET \n
\return \ref A3D_MARKUP_SEMANTIC_TOL_VALUE_NOT_SET \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDFCFSemanticRowGet,( const A3DMDFCFRow* pRow,
		 A3DMDFCFDrawingRowData* pData));





/*!
\struct A3DMDFeatureControlFrameData
\ingroup a3d_markupfcf
\brief Feature control frame
*/
typedef struct
{
	A3DUns16			m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32			m_uiNumberOfRows;	/*!< Number of rows. */
	A3DMDFCFRow**		m_ppRows;			/*!< Array of rows. */
}A3DMDFeatureControlFrameData;


/*!
\fn A3DStatus A3DMDFeatureControlFrameGet( const A3DMDFeatureControlFrame* pFCF, A3DMDFeatureControlFrameData* pData)
\brief Populates the \ref A3DMDFeatureControlFrameData structure
\ingroup a3d_markupfcf
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDFeatureControlFrameGet,( const A3DMDFeatureControlFrame* pFCF,
		 A3DMDFeatureControlFrameData* pData));





/*!
\fn A3DStatus A3DMDSemanticFeatureControlFrameGet( const A3DMDFeatureControlFrame* pFCF, A3DMDFeatureControlFrameData* pData)
\brief Retrieves the semantic definition if set and populates the \ref A3DMDFeatureControlFrameData structure
\ingroup a3d_markupfcf
\version 5.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_MARKUP_SEMANTIC_DEFINITION_NOT_SET \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDSemanticFeatureControlFrameGet,( const A3DMDFeatureControlFrame* pFCF,
		 A3DMDFeatureControlFrameData* pData));




/*!
\struct A3DMarkupGDTData
\brief Markup geometrical and dimensioning tolerance
\ingroup a3d_markupgdt
\brief Markup geometrical dimensioning tolerance data structure
*/
typedef struct
{
	A3DUns16						m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*					m_pcAboveText;					/*!< Above text in RTF format. See \ref a3d_markup_rtf. */
	A3DUTF8Char*					m_pcBelowText;					/*!< Below text in RTF format. See \ref a3d_markup_rtf. */
	A3DUTF8Char*					m_pcBeforeText;					/*!< Before text in RTF format. See \ref a3d_markup_rtf. */
	A3DUTF8Char*					m_pcAfterText;					/*!< After text in RTF format. See \ref a3d_markup_rtf. */
	A3DUns32						m_uiNumberOfMarkupTolerances;	/*!< Number of tolerances. */
	A3DMDTolerance**				m_ppsMarkupTolerances;			/*!< Array of tolerances. */
	A3DMDTextProperties*			m_pTextProperties;				/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
}A3DMarkupGDTData;


/*!
\fn A3DStatus A3DMarkupGDTGet( const A3DMarkupGDT* pMarkupGDT, A3DMarkupGDTData* pData)
\brief Populates the \ref A3DMarkupGDTData structure
\ingroup a3d_markupgdt
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupGDTGet,( const A3DMarkupGDT* pMarkupGDT,
		 A3DMarkupGDTData* pData));



#endif	/*	__A3D_MARKUPGDT__ */


#endif	/*	__A3DPRCMARKUPTOLERANCE_H__ */
