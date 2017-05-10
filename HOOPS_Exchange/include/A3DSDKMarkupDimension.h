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
\brief      Header file for the markup dimension module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMarkupDimension_H__
#define __A3DPRCMarkupDimension_H__

#ifndef __A3DPRCMARKUPDEFINITION__
#error A3DSDKMarkupSemantic.h must be included before current file
#endif



#ifndef __A3DPRCDIMENSIONVALUE_H__

/*!
\defgroup a3d_markupdimension Dimension
\ingroup a3d_markup
\version 4.0
*/


/*!
\defgroup a3d_markupdimensionvalue Dimension value
\ingroup a3d_markupdimension Dimension value format
\struct A3DMDDimensionValueFormatData
\ingroup a3d_markupdimensionvalue
\brief Structure that describes dimension value format
\sa A3DMDDimensionValueFormatGet
	
	\note for member m_iType: 
	\li 1 = length(for length/distance/radius/diameter),
	\li 2 = Angle.

	\note for member m_iUnit:
	\li 1 = mm,
	\li 2 = inch,
	\li 3 = radians,
	\li 4 = degree,
	\li 5 = grade.

	\note for member m_dGlobFact:
	to display a distance in kilometers with units set to mm with Unit=1: GlobFact = 0.000001

	\note for member m_iSepDen:
	\li 1 = Before fractional rest,
	\li 2 = After fractional rest.
  
	\note for member m_iTypFrac:
	\li 1 = Side by side,
	\li 2 = Super-imposed.
  
	\note for member m_dFact_1:
	Separator number as described in the separator character table.
	The term measured value is multiplied by this factor prior to being displayed (the global multiplying factor is also used).
	All 3 values must have increasing and distinct values. 
	Example: to display a value with a term in centimeters and a term in millimeters, 
	with m_iUnit = mm and m_dGlobFact = 1., set m_dFact_1 = 1 and m_dFact_2 = 10
*/
typedef struct
{
	A3DUns16			m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*		m_pcName;			/*!< Name. */
	A3DInt32			m_iType;			/*!< Value type. */
	A3DInt32			m_iUnit;			/*!< Value unit. */
	A3DDouble			m_dGlobFact;		/*!< Global Multiplying Factor. */
	A3DInt32			m_iNulFac_1;		/*!< 1/2 => No display/display of Null Terms. */
	A3DInt32			m_iNulFac_2;		/*!< 1/2 => No display/display of leading zeros in last factor. */
	A3DInt32			m_iExise;			/*!< 1/2 => No display/display of separator for thousands. */
	A3DInt32			m_iSep1000;			/*!< Separator characters for decimal and thousands. */
	A3DDouble			m_dFact_1;			/*!< Term Multiplying Factor on term 1. */
	A3DDouble			m_dFact_2;			/*!< Term Multiplying Factor on term 2. */
	A3DDouble			m_dFact_3;			/*!< Term Multiplying Factor on term 3. */
	A3DDouble			m_dValPos_1;		/*!< Term vertical positioning offset on term 1. */
	A3DDouble			m_dValPos_2;		/*!< Term vertical positioning offset on term 2. */
	A3DDouble			m_dValPos_3;		/*!< Term vertical positioning offset on term 3. */
	A3DUTF8Char*		m_pcSepar_1;		/*!< Term unit suffix, 16 char string on term 1. */
	A3DUTF8Char*		m_pcSepar_2;		/*!< Term unit suffix, 16 char string on term 2. */
	A3DUTF8Char*		m_pcSepar_3;		/*!< Term unit suffix, 16 char string on term 3 */
	A3DDouble			m_dSepScl_1;		/*!< Term unit height ratio on term 1. */
	A3DDouble			m_dSepScl_2;		/*!< Term unit height ratio on term 2. */
	A3DDouble			m_dSepScl_3;		/*!< Term unit height ratio on term 3. */
	A3DDouble			m_dSepPos_1;		/*!< Term unit vertical positioning offset on term 1. */
	A3DDouble			m_dSepPos_2;		/*!< Term unit vertical positioning offset on term 2. */
	A3DDouble			m_dSepPos_3;		/*!< Term unit vertical positioning offset on term 3. */
	A3DDouble			m_dRestY;			/*!< This value is a ratio to the character height. */
	A3DInt32			m_iFinZer;			/*!< 1/2 => No display/display of trailing zeros (number of digits specified in the value precision). */
	A3DInt32			m_iSepNum;			/*!< Fractional Rest. */
	A3DInt32			m_iTypFrac;			/*!< Fraction type. */
	A3DInt32			m_iSepDen;			/*!< Position of last term unit. */
	A3DDouble			m_dOperY;			/*!< Offset between fractional rest numerator and denominator. */
	A3DInt32			m_iNulOther;		/*!< This value is a ratio to the character height. */
	A3DDouble			m_dResScl;			/*!< Unit height / value height. */
	A3DInt32			m_iFact;			/*!< Number of terms in the value [1..3]. */
	A3DDouble			m_dRestX;			/*!< This value is a ratio to the character height. */
} A3DMDDimensionValueFormatData;

/*!
\fn A3DStatus A3DMDDimensionValueFormatGet( const A3DMDDimensionValueFormat* pDimensionValueFormat, A3DMDDimensionValueFormatData* pData)
\brief Populates the \ref A3DMDDimensionValueFormatData structure
\ingroup a3d_markupdimensionvalue
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionValueFormatGet, ( const A3DMDDimensionValueFormat* pDimensionValueFormat,
												A3DMDDimensionValueFormatData* pData));




/*!
	\struct A3DMDDimensionSimpleToleranceFormatData
	\ingroup a3d_markupdimensionvalue
	\brief Structure that describes dimension tolerance format
	\sa A3DMDDimensionSimpleToleranceFormatGet, A3DMDDimensionValueData

	\note for member m_iType:
	\li 1: Numerical side by side,
	\li 2: Numerical super-imposed,
	\li 3: Resolved numerical side by side,
	\li 4: Resolved numerical super-imposed,
	\li 5: Alphanumerical single value,
	\li 6: Alphanumerical side by side,	
	\li 7: Alphanumerical super-imposed.

	\note for member m_dSymbolH: Ratio between separator character and value text font sizes

	\note for member m_iTrailing: Display of tolerance trailing zeros
	\li 0: Display (number of digits specified in the value precision),
	\li 1: No Display,
	\li 2: Same "display" mode as the dimension value

	\note for member m_iFractLine:
	\li 1: No fraction line,
	\li 2: Fraction line.

	\note for member m_iPtOnValue:
	\li 7: Top,
	\li 8: Middle,
	\li 9: Bottom.

	\note for member m_iAnchorPt:
	\li 1: Top,
	\li 2: Middle,
	\li 3: Bottom.

	\note for member m_iMergeSame:
	\li 1: Display common value,
	\li 2: Display separate values.

	\note for member m_iShowNull: for numerical tolerances only and
	\li 1: Display null value with sign,
	\li 2: Display null value without sign,
	\li 3: No display of null value.
*/
typedef struct
{
	A3DUns16			m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*		m_pcName;		/*!< Name of the tolerance format. */
	A3DInt32			m_iType;		/*!< Tolerance format type. */
	A3DInt32			m_iSepar_1;		/*!< Separators for super-imposed tolerances. */
	A3DInt32			m_iSepar_2;		/*!< Separators for super-imposed tolerances. */
	A3DDouble			m_dSymbolH;		/*!< Separator character size. */
	A3DInt32			m_iSepTo_1;		/*!< Separators for side-by-side tolerances. */
	A3DInt32			m_iSepTo_2;		/*!< Separators for side-by-side tolerances. */
	A3DInt32			m_iSepTo_3;		/*!< Separators for side-by-side tolerances. */
	A3DInt32			m_iTrailing;	/*!< Trailing 0 display. */
	A3DInt32			m_iFractLine;	/*!< Fraction line. */
	A3DInt32			m_iPtOnValue;	/*!< Tolerance position anchor point (for offset computing). */
	A3DInt32			m_iAnchorPt;	/*!< Anchor position. */
	A3DDouble			m_dIntX;		/*!< Offset between the 2 tolerance values: X value. */
	A3DDouble			m_dIntY;		/*!< Offset between the 2 tolerance values: Y value. */
	A3DDouble			m_dExtX;		/*!< Offset between dimension value and tolerance: X value. */
	A3DDouble			m_dExtY;		/*!< Offset between dimension value and tolerance: Y value. */
	A3DInt32			m_iMergeSame;	/*!< Display of identical tolerance values (for numerical tolerances only). */
	A3DInt32			m_iShowNull;	/*!< Display of null tolerance values. */
	A3DDouble			m_dScale;		/*!< Scale. */
	
} A3DMDDimensionSimpleToleranceFormatData;


/*!
\fn A3DStatus A3DMDDimensionSimpleToleranceFormatGet( const A3DMDDimensionSimpleToleranceFormat* pDimensionToleranceFormat, A3DMDDimensionSimpleToleranceFormatData* pData)
\brief Populates the \ref A3DMDDimensionSimpleToleranceFormat structure
\ingroup a3d_markupdimensionvalue
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionSimpleToleranceFormatGet,( const A3DMDDimensionSimpleToleranceFormat* pDimensionToleranceFormat,
		 A3DMDDimensionSimpleToleranceFormatData* pData));






/*!
	\struct A3DMDDimensionCombinedToleranceFormatData
	\ingroup a3d_markupdimensionvalue
	\brief Structure that describes Combined tolerance format
	\sa A3DMDDimensionCombinedToleranceFormatGet, A3DMDDimensionToleranceFormatGet

	\note for member m_iType:
	\li 1: Numerical side by side,
	\li 2: Numerical super-imposed,
	\li 3: Resolved numerical side by side,
	\li 4: Resolved numerical super-imposed,
	\li 5: Alphanumerical single value,
	\li 6: Alphanumerical side by side,	
	\li 7: Alphanumerical super-imposed.

	\note for member m_dSymbolH: Ratio between separator character and value text font sizes
*/
typedef struct
{
	A3DUns16								m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*							m_pcName;				/*!< Name of the tolerance format. */
	A3DInt32								m_iType;				/*!< Tolerance format type. */
	A3DMDDimensionSimpleToleranceFormat*	m_pToleranceFormat1;	/*!< First tolerance format. */
	A3DDouble								m_dExtX1;	
	A3DDouble								m_dExtY1;
	A3DInt32								m_iAnchorPt1;
	A3DInt32								m_iPtOnValue1;
	A3DInt32								m_iSepar_1;	
	A3DMDDimensionSimpleToleranceFormat*	m_pToleranceFormat2;	/*!< Second tolerance format. */
	A3DDouble								m_dExtX2;
	A3DDouble								m_dExtY2;
	A3DInt32								m_iAnchorPt2;
	A3DInt32								m_iPtOnValue2;
	A3DInt32								m_iSepar_2;
} A3DMDDimensionCombinedToleranceFormatData;





/*!
\fn A3DStatus A3DMDDimensionCombinedToleranceFormatGet( const A3DMDDimensionCombinedToleranceFormat* pDimensionToleranceFormat, A3DMDDimensionCombinedToleranceFormatData* pData)
\brief Populates the \ref A3DMDDimensionCombinedToleranceFormatData structure
\ingroup a3d_markupdimensionvalue
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionCombinedToleranceFormatGet,( const A3DMDDimensionCombinedToleranceFormat* pDimensionCombinedToleranceFormat,
		 A3DMDDimensionCombinedToleranceFormatData* pData));


/*!
\enum EA3DMDDimensionValueOption
\ingroup a3d_markupdimensionvalue
\brief Enumerator that describes dimension's option
\version 9.0
*/
typedef enum
{
	KEA3DMDDimensionValueOptionNone = 0, /*!< Dimension has no option. */
	KEA3DMDDimensionValueOptionMin = 1,	/*!< Dimension has the min modifier. */
	KEA3DMDDimensionValueOptionMax = 2,	/*!< Dimension has the max modifier. */
	KEA3DMDDimensionValueOptionEnvelopeModifier = 4,	/*!< Dimension has the enveloppe modifier. */
	KEA3DMDDimensionValueOptionIndependencyModifier = 8,	/*!< Dimension has the independency modifier. */
	KEA3DMDDimensionValueOptionStaticalTolerancingModifier = 16,	/*!< Dimension has the statical tolerancing modifier. */
	KEA3DMDDimensionValueOptionPerfectFormAtMMCNotRequired = 32,	/*!< Dimension has the option perfect form at MMC not required. */
} EA3DMDDimensionValueOption;

/*!
	\struct A3DMDDimensionValueData
	\ingroup a3d_markupdimensionvalue
	\brief Structure that describes dimension value
	\sa A3DMDDimensionValueGet, A3DMarkupDimensionData

	\note for member m_iType:
	\li 0: true value is used (Use m_dValue from \ref A3DMarkupDimensionData),
	\li 1: fake value is used, original value is numerical,
	\li 2: fake value is used, original value is alpha numerical.

	\note for member m_bFormat:
	\li TRUE: decimal
	\li FALSE: fractional
*/
typedef struct
{
	A3DUns16							m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DInt32							m_iType;				/*!< Dimension value type. */
	A3DBool								m_bFormat;				/*!< Dimension format. */
	A3DDouble							m_dAccuracy;			/*!< Display accuracy. */
	A3DDouble							m_dToleranceAccuracy;	/*!< Display tolerance accuracy, if NULL, use m_dAccuracy. */
	A3DUTF8Char*						m_pcFakeValue;			/*!< Fake value. */
	A3DDouble							m_dTolNumSup;			/*!< Superior numerical tolerance, related to m_pToleranceFormat. */
	A3DDouble							m_dTolNumInf;			/*!< Inferior numerical tolerance, related to m_pToleranceFormat. */
	A3DUTF8Char*						m_pcTolTxtSup;			/*!< Superior alpha numerical tolerance, related to m_pToleranceFormat. */
	A3DUTF8Char*						m_pcTolTxtInf;			/*!< Inferior alpha numerical tolerance, related to m_pToleranceFormat. */
	A3DUTF8Char*						m_pcBeforeText;			/*!< Text diplayed before value. */
	A3DUTF8Char*						m_pcAfterText;			/*!< Text diplayed after value. */
	A3DUTF8Char*						m_pcAboveText;			/*!< Text diplayed above value. */
	A3DUTF8Char*						m_pcBelowText;			/*!< Text diplayed below value. */
	A3DUns16							m_usLastSeparDefinedNum;/*!< Last separator to use. */
	A3DMDDimensionValueFormat*			m_pDimValueFormat;		/*!< Value format. */
	A3DMDDimensionToleranceFormat*		m_pToleranceFormat;		/*!< Tolerance format. */
	A3DInt32							m_iOption;				/*!<  Option of semantic data. A combination of EA3DMDDimensionValueOption enum values. /version 9.0 */
	A3DDouble							m_dDeltaForMinMax;		/*!<  Value of delta if the option MIN/MAX is activated. /version 9.0 */

} A3DMDDimensionValueData;


/*!
\fn A3DStatus A3DMDDimensionValueGet( const A3DMDDimensionValue* pDimensionValue, A3DMDDimensionValueData* pData)
\brief Populates the \ref A3DMDDimensionValueData structure
\ingroup a3d_markupdimensionvalue
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionValueGet,( const A3DMDDimensionValue* pDimensionValue,
											A3DMDDimensionValueData* pData));



#endif	/*	__A3DPRCDIMENSIONVALUE_H__ */




#ifndef __A3DPRCDIMENSIONLINE_H__

/*!
\defgroup a3d_markupdimensionline Dimension line
\ingroup a3d_markupdimension
\version 4.0
*/

/*!
	\enum EA3DMDDimensionLineGraphicalRepresentation
	\ingroup a3d_markupdimensionline
	\brief Enumerator that describes dimension's line graphical representation
*/
typedef enum 
{
	KEA3DMDDimensionGraphicalRepresentationRegular			= 0,	/*!< Regular dimension line representation: \image html pmi_markup_dimension_GraphRep_Regular.png */
	KEA3DMDDimensionGraphicalRepresentationTwoParts			= 1,	/*!< Two parts dimension line representation: \image html pmi_markup_dimension_GraphRep_Two_Parts.png */
	KEA3DMDDimensionGraphicalRepresentationLeaderOnePart	= 2,	/*!< Leader one part dimension line representation: \image html pmi_markup_dimension_GraphRep_Leader_one_Part.png */
	KEA3DMDDimensionGraphicalRepresentationLeaderTwoParts	= 3		/*!< Leader two parts dimension line representation: \image html pmi_markup_dimension_GraphRep_Leader_two_Parts.png */
} EA3DMDDimensionLineGraphicalRepresentation;

/*!
	\enum EA3DMDDimensionOrientation
	\ingroup a3d_markupdimensionline
	\brief Enumerator that describes dimension's orientation
	\sa A3DMDDimensionSecondPartData, A3DMarkupDimensionData
*/
typedef enum
{ 
	KEA3DMDDimensionOrientationScreenHorizontal		= 0,	/*!< Dimension along horizontal line of the screen. */
	KEA3DMDDimensionOrientationScreenVertical		= 1,	/*!< Dimension along vertical line of the screen. */
	KEA3DMDDimensionOrientationScreenAngle			= 2,	/*!< Uses m_AnnAngle of \ref A3DMarkupDefinitionData. */
	KEA3DMDDimensionOrientationViewHorizontal		= 3,	/*!< Dimension along horizontal line of the view. */
	KEA3DMDDimensionOrientationViewVertical			= 4,	/*!< Dimension along vertical line of the view. */
	KEA3DMDDimensionOrientationViewAngle			= 5,	/*!< Uses m_AnnAngle of \ref A3DMarkupDefinitionData. */
	KEA3DMDDimensionOrientationParallel				= 6,	/*!< Dimension is parallel to the dimension line. */
	KEA3DMDDimensionOrientationPerpendicular		= 7,	/*!< Dimension is perpendicular to the dimension line. */
	KEA3DMDDimensionOrientationAngle				= 8		/*!< Uses m_AnnAngle of \ref A3DMarkupDefinitionData. */
} EA3DMDDimensionOrientation;


/*!
	\struct A3DMDDimensionSecondPartData
	\ingroup a3d_markupdimensionline
	\brief Structure that describes the second part of dimension line if it's used.
	\sa A3DMDDimensionLineData
	\image html pmi_markup_dimension_SecondPart.png
*/
typedef struct 
{
	A3DUns16					m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	EA3DMDDimensionOrientation	m_eOrientation;	/*!< Orientation type. */
	A3DDouble					m_dAngle;		/*!< Orientation angle. */
	A3DDouble					m_dOffSet;		/*!< Orientation angle. */
} A3DMDDimensionSecondPartData;


/*!
\fn A3DStatus A3DMDDimensionSecondPartGet( const A3DMDDimensionSecondPart* pDimensionSecondPart, A3DMDDimensionSecondPartData* pData)
\brief Populates the \ref A3DMDDimensionSecondPartData structure
\ingroup a3d_markupdimensionline
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionSecondPartGet,( const A3DMDDimensionSecondPart* pDimensionSecondPart,
		 A3DMDDimensionSecondPartData* pData));






/*!
	\enum EA3DMDDimensionSymbolSharpe
	\ingroup a3d_markupdimensionline
	\brief Enumerator that describes line symbols 
	\sa A3DMDDimensionLineSymbolData
*/
typedef enum 
{
	KEA3DDimensionSymbolTypeUNKNOW			= -1,
	KEA3DDimensionSymbolTypeNONE			= 0,
	KEA3DDimensionSymbolTypePROJTOLZONE		= 1,
	KEA3DDimensionSymbolTypeMAXMATERIAL		= 2,
	KEA3DDimensionSymbolTypeLEASTMATERIAL	= 3,
	KEA3DDimensionSymbolTypeFREESTATE		= 4,
	KEA3DDimensionSymbolTypeOHM				= 5,
	KEA3DDimensionSymbolTypeCENTERLINE		= 6,
	KEA3DDimensionSymbolTypeDEPTH			= 7,
	KEA3DDimensionSymbolTypeCOUNTERBORE		= 8,
	KEA3DDimensionSymbolTypeCOUNTERSUNK		= 9,
	KEA3DDimensionSymbolTypeCIRCULARRUNOUT	= 10,
	KEA3DDimensionSymbolTypeSURFPROFILE		= 11,
	KEA3DDimensionSymbolTypeLINEPROFILE		= 12,
	KEA3DDimensionSymbolTypeFLATNESS		= 13,
	KEA3DDimensionSymbolTypeSTRAIGHT		= 14,
	KEA3DDimensionSymbolTypeTOTALRUNOUT		= 15,
	KEA3DDimensionSymbolTypeSYMMETRY		= 16,
	KEA3DDimensionSymbolTypePERPENDICULAR	= 17,
	KEA3DDimensionSymbolTypePARALLEL		= 18,
	KEA3DDimensionSymbolTypeCYLINDRIC		= 19,
	KEA3DDimensionSymbolTypeCONCENTRIC		= 20,
	KEA3DDimensionSymbolTypeCIRCULAR		= 21,
	KEA3DDimensionSymbolTypeANGULAR			= 22,
	KEA3DDimensionSymbolTypeMICRO			= 23,
	KEA3DDimensionSymbolTypeDEGREE			= 24,
	KEA3DDimensionSymbolTypePLUSMINUS		= 25,
	KEA3DDimensionSymbolTypePOSITION		= 26,
	KEA3DDimensionSymbolTypeDIAMETER		= 27,
	KEA3DDimensionSymbolTypeENVELOPE		= 28,
	KEA3DDimensionSymbolTypeARROW			= 29,  
	KEA3DDimensionSymbolTypeNOACTUALSIZE	= 30,
	KEA3DDimensionSymbolTypeTANGENTPLANE	= 31,
	KEA3DDimensionSymbolTypeLOWEROREQUAL	= 32,
	KEA3DDimensionSymbolTypeGREATEROREQUAL	= 33,
	KEA3DDimensionSymbolTypeTHREADPREFIX	= 34,
	KEA3DDimensionSymbolTypeSLOPE			= 35,
	KEA3DDimensionSymbolTypeCONICALTAPER	= 36,
	KEA3DDimensionSymbolTypeUPTRIANGLE		= 37,
	KEA3DDimensionSymbolTypeSQUARE			= 38,
	KEA3DDimensionSymbolTypeST				= 39,
	KEA3DDimensionSymbolTypeSDIAMETER		= 40,
	KEA3DDimensionSymbolTypeRADIUS			= 41,
	KEA3DDimensionSymbolTypeSRADIUS			= 42,
	KEA3DDimensionSymbolTypeCRADIUS			= 43,
	KEA3DDimensionSymbolTypeUNEQUALLY		= 44,
	//a symbol can use to precise the dimension value,
	//It can be placed before or after the gloval dimension value,
	//the following value, precise that the symbol is to be placed after the dim value
	KEA3DDimensionSymbolTypeSET_AFTER		= 1000
} EA3DMDDimensionSymbolType;




/*!
	\enum EA3DMDDimensionSymbolSharpe
	\ingroup a3d_markupdimensionline
	\brief Enumerator that describes line symbols 
	\sa A3DMDDimensionLineSymbolData
*/
typedef enum 
{
	KEA3DDimensionSymbolNone				= 0,	/*!< No symbol. */
	KEA3DDimensionSymbolOpenArrow			= 1,	/*!< Open arrow. */
	KEA3DDimensionSymbolClosedArrow			= 2,	/*!< Closed arrow. */
	KEA3DDimensionSymbolFilledArrow			= 3,	/*!< Filled arrow. */
	KEA3DDimensionSymbolSymArrow			= 4,	/*!< Symetric arrow. */
	KEA3DDimensionSymbolSlash				= 5,	/*!< Slash. */
	KEA3DDimensionSymbolCircle				= 6,	/*!< Circle. */
	KEA3DDimensionSymbolFilledCircle		= 7,	/*!< Filled circle. */
	KEA3DDimensionSymbolScoredCircle		= 8,	/*!< Scored circle. */
	KEA3DDimensionSymbolCircledCross		= 9,	/*!< Circled cross. */
	KEA3DDimensionSymbolTriangle			= 10,	/*!< Triangle. */
	KEA3DDimensionSymbolFilledTriangle		= 11,	/*!< Filled Triangle. */
	KEA3DDimensionSymbolCross				= 12,	/*!< Cross. */
	KEA3DDimensionSymbolXCross				= 13,	/*!< X cross. */
	KEA3DDimensionSymbolDoubleArrow			= 14,	/*!< Double arrow. */
	KEA3DDimensionSymbolSquare				= 15,	/*!< Box. \version 7.1 */
	KEA3DDimensionSymbolFilledSquare		= 16,	/*!< Filled box. \version 7.1 */
	KEA3DDimensionSymbolWave				= 17	/*!< Wave. \version 7.1 */
} EA3DMDDimensionSymbolSharpe;


/*!
	\enum EA3DMDDimensionLineExtensionType
	\ingroup a3d_markupdimensionline
	\brief Enumerator that describes the extension type 
	\sa A3DMDDimensionLineGet
*/
typedef enum
{
	KEA3DMDDimensionExtensionFromStandard				= 0,	/*!< Undocumented. */	
	KEA3DMDDimensionExtensionTillCenter					= 1,	/*!< Undocumented. */	
	KEA3DMDDimensionExtensionNotTillCenter				= 2,	/*!< Undocumented. */	
	KEA3DMDDimensionExtensionHideFirstPartOfDimLine		= 4,	/*!< Undocumented. */	
	KEA3DMDDimensionExtensionHideFSecondPartOfDimLine	= 8,	/*!< Undocumented. */	
	KEA3DMDDimensionExtensionHideEntireDimLine			= 16,	/*!< Undocumented. */	
	KEA3DMDDimensionExtensionAddIsoLineUnderTextValue	= 32	/*!< Undocumented. */	
} EA3DMDDimensionLineExtensionType;

/*!
	\struct A3DMDDimensionForeshortenedData
	\ingroup a3d_markupdimensionline
	\brief Structure that describes foreshortened data
	\sa A3DMDDimensionForeshortenedGet, A3DMDDimensionLineData
	\image html pmi_markup_dimension_Foreshortened.png
*/
typedef struct 
{ 
	A3DUns16					m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool						m_bTextPosition;	/*!< Position of the text associated to the dim line:\li TRUE => on the short segment\li FALSE => on the long segment */
	A3DBool						m_bOrientation;		/*!< Orientation of the text associated to the dim line:\li FALSE => parallel\li TRUE => convergent */
	A3DDouble					m_dAngle;			/*!< Angle in radians. */
	A3DFloat					m_fRatio;			/*!< Specify the ratio between the short segment and the long segment. */
	A3DUns16					m_usPointScale;		/*!< Point scale. */
} A3DMDDimensionForeshortenedData;

/*!
\fn A3DStatus A3DMDDimensionForeshortenedGet( const A3DMDDimensionForeshortened* pDimensionForeshortened, A3DMDDimensionForeshortenedData* pData)
\brief Populates the \ref A3DMDDimensionForeshortenedData structure
\ingroup a3d_markupdimensionline
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionForeshortenedGet,( const A3DMDDimensionForeshortened* pDimensionForeshortened,
		 A3DMDDimensionForeshortenedData* pData));




/*!
	\struct A3DMDDimensionLineSymbolData
	\ingroup a3d_markupdimensionline
	\brief Structure that describes dimension line symbols
	\sa A3DMDDimensionLineData
*/
typedef struct 
{
	A3DUns16					m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	EA3DMDDimensionSymbolSharpe		m_eShape;	/*!< Line symbol. */
	A3DUns32					m_iLineColor;	/*!< Color index. \sa A3DGlobalGetGraphRgbColorData */
	A3DFloat					m_fThickness;	/*!< Thickness. */
	A3DFloat					m_fArrowLength; /*!< Arrow length. */
	A3DFloat					m_fArrowAngle;	/*!< Arrow angle, in degree. */
} A3DMDDimensionLineSymbolData;


/*!
\fn A3DStatus A3DMDDimensionLineSymbolGet( const A3DMDDimensionLineSymbol* pDimensionLineSymbol, A3DMDDimensionLineSymbolData* pData)
\brief Populates the \ref A3DMDDimensionLineSymbolData structure
\ingroup a3d_markupdimensionvalue
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionLineSymbolGet,( const A3DMDDimensionLineSymbol* pDimensionLineSymbol,
		 A3DMDDimensionLineSymbolData* pData));





/*!
	\struct A3DMDDimensionLineData
	\ingroup a3d_markupdimensionline
	\brief Structure that describes dimension line
	\sa A3DMDDimensionLineGet, A3DMDDimensionDimensionData
	\image html pmi_markup_dimension_Line.png

	\note For members m_pSymbol1, m_pSymbol2 and m_pLeaderSymbol: pointer can be shared with other markups.

	\note For m_pLeaderSymbol: This data is useful if \ref m_eGraphRepresentation is set to 
	pmi_markup_dimension_GraphRep_Leader_one_Part or pmi_markup_dimension_GraphRep_Leader_two_Parts.

	\note For m_sSecondPart: This structure is valid only if \ref m_eGraphRepresentation is set to 
	pmi_markup_dimension_GraphRep_Leader_one_Part or pmi_markup_dimension_GraphRep_Leader_two_Parts.

	\note for m_usReversal: 
	\li 0: both symbols are set automatically
	\li 1: both symbols are set inside of the extension lines,
	\li 2: both symbols are set outside of the extension lines,
	\li 3: first symbols is set inside, second symbol is set outside,
	\li 4: first symbols is set outside, second symbol is set inside.
	
	\note For m_dLeaderAngle: This value is valid only if \ref m_eGraphRepresentation is set to 
	KEA3DMDDimensionGraphicalRepresentationLeaderOnePart or KEA3DMDDimensionGraphicalRepresentationLeaderTwoParts.
*/
typedef struct
{   
	A3DUns16									m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMDDimensionLineSymbol*					m_pSymbol1;				/*!< First symbol description. */
	A3DMDDimensionLineSymbol*					m_pSymbol2;				/*!< Second symbol description. */
	A3DMDDimensionLineSymbol*					m_pLeaderSymbol;		/*!< Leader symbol description. */
	EA3DMDDimensionLineGraphicalRepresentation	m_eGraphRepresentation; /*!< Graphical representation of the dimension line. */
	A3DMDDimensionSecondPart*					m_pSecondPart;			/*!< Second part description. */
	A3DUns16									m_usStyle;				/*!< Line style Index. */
	A3DFloat									m_fThickness;			/*!< Thickness. */
	A3DUns16									m_usReversal;			/*!< Reversal. */
	A3DMDDimensionForeshortened*				m_psForeshortened;		/*!< Optionnal foreshortened description. */
	A3DDouble									m_dLeaderAngle;			/*!< Leader angle. */
	EA3DMDDimensionLineExtensionType			m_eExtension;			/*!< Extension type. */
	A3DRiCurve*									m_pExplicitCurve;		/*!< Explicit cure, in case of curvilinear dimension. */
} A3DMDDimensionLineData;

/*!
\fn A3DStatus A3DMDDimensionLineGet( const A3DMDDimensionLine* pDimensionLine, A3DMDDimensionLineData* pData)
\brief Populates the \ref A3DMDDimensionLineData structure
\ingroup a3d_markupdimensionline
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionLineGet,( const A3DMDDimensionLine* pDimensionLine,
		 A3DMDDimensionLineData* pData));



#endif	/*	__A3DPRCDIMENSIONLINE_H__ */

#ifndef __A3DPRCDIMENSIONEXTLINE_H__

/*!
\defgroup a3d_markupdimensionextensionline Dimension extension line
\ingroup a3d_markupdimension
\version 4.0
*/

/*!
	\struct A3DMDDimensionFunnelData
	\ingroup a3d_markupdimensionextensionline
	\brief Structure that describes funnels
	\sa A3DMDDimensionFunnelGet, A3DMDDimensionExtentionLineData
	\image html pmi_markup_dimension_Funnel.png

	\note for member m_usIndex: Funnel applies to
	\li 0: first extension line only,
	\li 1: second extension line only,
	\li 2: both extension lines.

	\note for member m_bMode:
	\li FALSE: inside,
	\li TRUE: outside.

*/
typedef struct
{
	A3DUns16		m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns16		m_usIndex;			/*!< Funnel covering. */
	A3DBool			m_bMode;			/*!< Mode. */
	A3DDouble		m_dAngle;			/*!< Angle. */
	A3DDouble		m_dHeight;			/*!< Height. */
	A3DDouble		m_dWidth;			/*!< Width. */
}A3DMDDimensionFunnelData;

/*!
\fn A3DStatus A3DMDDimensionFunnelGet( const A3DMDDimensionFunnel* pDimensionFunnel, A3DMDDimensionFunnelData* pData)
\brief Populates the \ref A3DMDDimensionFunnelData structure
\ingroup a3d_markupdimensionvalue
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionFunnelGet,( const A3DMDDimensionFunnel* pDimensionFunnel,
		 A3DMDDimensionFunnelData* pData));






/*!
	\struct A3DMDDimensionExtremityData
	\ingroup a3d_markupdimensionextensionline
	\brief Structure that describes extremities
	\sa A3DMDDimensionExtentionLineData
	\image html pmi_markup_dimension_Extremity.png
*/
typedef struct
{ 
	A3DUns16	m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool		m_bShow;			/*!< Indicates if the dimension line is visible (TRUE) ar not (FALSE). */
	A3DDouble	m_dBlanking;		/*!< Blanked part of the extension line (expressed in mm). */
	A3DDouble	m_dOverrun;			/*!< Overrunning part of the extension line (expressed in mm). */
} A3DMDDimensionExtremityData;

/*!
\fn A3DStatus A3DMDDimensionExtremityGet( const A3DMDDimensionExtremity* pDimensionExtremity, A3DMDDimensionExtremityData* pData)
\brief Populates the \ref A3DMDDimensionExtremityData structure
\ingroup a3d_markupdimensionextensionline
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionExtremityGet,( const A3DMDDimensionExtremity* pDimensionExtremity,
		 A3DMDDimensionExtremityData* pData));





/*!
	\struct A3DMDDimensionExtentionLineData
	\ingroup a3d_markupdimensionextensionline
	\brief Structure that describes extension lines
	\sa A3DMDDimensionExtentionLineGet, A3DMarkupDimensionData
	\image html pmi_markup_dimension_ExtentionLine.png
*/
typedef struct
{ 
	A3DUns16						m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMDDimensionFunnel*			m_pFunnel;			/*!< Pointer to optional funnel description. This pointer can be shared with other markups. */
	A3DMDDimensionExtremityData		m_sExtremity1;		/*!< Description of first dimension extension line extremities. */
	A3DMDDimensionExtremityData		m_sExtremity2;		/*!< Description of second dimension extension line extremities. */
	A3DDouble						m_dLineSlant;		/*!< Line slant. */
	A3DUns16						m_usStyle;			/*!< Index of line symbol style in the table. \sa A3DGlobalLineStyleGe */
	A3DFloat						m_fThickness;		/*!< Thickness. */
} A3DMDDimensionExtentionLineData;



/*!
\fn A3DStatus A3DMDDimensionExtentionLineGet( const A3DMDDimensionExtentionLine* pDimensionExtentionLine, A3DMDDimensionExtentionLineData* pData)
\brief Populates the \ref A3DMDDimensionExtentionLineData structure
\ingroup a3d_markupdimensionextensionline
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDDimensionExtentionLineGet,( const A3DMDDimensionExtentionLine* pDimensionExtentionLine,
		 A3DMDDimensionExtentionLineData* pData));





#endif	/*	__A3DPRCDIMENSIONEXTLINE_H__ */


/*!
	\enum EA3DMDDimensionType Dimension type
	\ingroup a3d_markupdimension
	\brief Enumerator that describes the dimension's type
	\sa A3DMarkupDimensionData
*/
typedef enum
{
	KEA3DMDDimensionTypeDistance			= 0,	/*!< Undocumented. */	
	KEA3DMDDimensionTypeDistanceOffset		= 1,	/*!< Undocumented. */
	KEA3DMDDimensionTypeLength				= 2,	/*!< Undocumented. */
	KEA3DMDDimensionTypeLengthCurvilinear	= 3,	/*!< Undocumented. */
	KEA3DMDDimensionTypeAngle				= 4,	/*!< Undocumented. */
	KEA3DMDDimensionTypeRadius				= 5,	/*!< Undocumented. */
	KEA3DMDDimensionTypeRadiusTangent		= 6,	/*!< Undocumented. */
	KEA3DMDDimensionTypeRadiusCylinder		= 7,	/*!< Undocumented. */
	KEA3DMDDimensionTypeRadiusEdge			= 8,	/*!< Undocumented. */
	KEA3DMDDimensionTypeDiameter			= 9,	/*!< Undocumented. */
	KEA3DMDDimensionTypeDiameterTangent		= 10,	/*!< Undocumented. */
	KEA3DMDDimensionTypeDiameterCylinder	= 11,	/*!< Undocumented. */
	KEA3DMDDimensionTypeDiameterEdge		= 12,	/*!< Undocumented. */
	KEA3DMDDimensionTypeDiameterCone		= 13,	/*!< Undocumented. */
	KEA3DMDDimensionTypeChamfer				= 14,	/*!< Undocumented. */
	KEA3DMDDimensionTypeSlope				= 15	/*!< Undocumented. */
} EA3DMDDimensionType;

/*!
	\enum EA3DMDDimensionDualDisplay Dimension dual value display
	\ingroup a3d_markupdimension
	\brief Enumerator that describes dual value display
	\sa A3DMarkupDimensionData
*/
typedef enum
{
	KEA3DMDDimensionDualDisplayNone			= 0, /*!< Undocumented. */
	KEA3DMDDimensionDualDisplayBelow		= 1, /*!< Undocumented. */
	KEA3DMDDimensionDualDisplayFractional	= 2, /*!< Undocumented. */
	KEA3DMDDimensionDualDisplaySideBySide	= 3  /*!< Undocumented. */
} EA3DMDDimensionDualDisplay;


/*!
	\enum EA3DMDDimensionFrame Dimension frame
	\ingroup a3d_markupdimension
	\brief Enumerator that describes dimension's frame
	\sa A3DMarkupDimensionData
*/
typedef enum
{
	KEA3DMDDimensionFrameNone			= 0, /*!< No frame. */
	KEA3DMDDimensionFrameCircle			= 1, /*!< Circle frame. */
	KEA3DMDDimensionFrameScoredCircle	= 2, /*!< Scored circle frame. */
	KEA3DMDDimensionFrameDiamondShaped	= 3, /*!< Diamond frame. */
	KEA3DMDDimensionFrameSquare			= 4, /*!< Square frame. */
	KEA3DMDDimensionFrameRectangle		= 5, /*!< Rectangle frame. */
	KEA3DMDDimensionFrameOblong			= 6, /*!< Oblong frame. */
	KEA3DMDDimensionFrameRightFlag		= 7, /*!< Right flag frame. */
	KEA3DMDDimensionFrameRightTriangle	= 8  /*!< Triangle frame. */
} EA3DMDDimensionFrame;

/*!
	\enum EA3DMDDimensionScore Dimension score
	\ingroup a3d_markupdimension
	\brief Enumerator that describes angle sector used
	\sa A3DMarkupDimensionData
	*/
typedef enum
{
	KEA3DMDDimensionScoreNone			= 0,
	KEA3DMDDimensionUnderScored			= 1,
	KEA3DMDDimensionScored				= 2,
	KEA3DMDDimensionOverScored			= 3
}EA3DMDDimensionScore;



/*!
	\struct A3DMarkupDimensionData
	\ingroup a3d_markupdimension
	\brief Structure that describes dimension markups
	\sa A3DMarkupDimensionGet

	\note for member m_pExtentionLine: This pointer can be shared with other markups.

	\note for member m_dOffset: Value defining the distance between the dimension value and the dimension line
	\image html pmi_markup_dimension_dOffset.png


	\note for member m_usPosition: Markup dimension position is:
	\li 0: Auto,
	\li 1: Inside, \image html pmi_markup_dimension_usPosition_inside.png
	\li 2: Outside. \image html pmi_markup_dimension_usPosition_outside.png


	\note for member m_usScore: Scoring applies to
	\li 0: not to score,
	\li 1: only the value,
	\li 2: all dimension texts.

	\note for member m_usScoreGroup: Scoring applies to
	\li 0: the main value,
	\li 1: the dual value,
	\li 2: both values.

	\note for member m_usFrame: Framing applies to
	\li 0: Value,
	\li 1: Value+tolerance,
	\li 2: Value+tolerance+texts.

	\note for member m_usFrameGroup: Framing applies to
	\li 0: the main value,
	\li 1: the dual value,
	\li 2: both values.

	\note for member m_usDisplayModeTextBox: 
	\li 3: Show box,
	\li 4: hide value.

*/
typedef struct 
{ 
	A3DUns16							m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	EA3DMDDimensionType					m_eType;				/*!< Dimension markup type. */

	A3DMDDimensionValue*				m_pMainValue;			/*!< Main value description. */
	A3DMDDimensionValue*				m_pDualValue;			/*!< Description. */
	EA3DMDDimensionDualDisplay			m_eDualDisplay;			/*!< Dual value display's type. */

	A3DDouble							m_dValue;				/*!< Dimension markup value. */
	EA3DMDDimensionSymbolType			m_eSymbol;				/*!< Optional symbol before the value. */
	EA3DMDDimensionSymbolType			m_eAdditionnalSymbol;	/*!< Optional symbol before the value. */
	A3DUTF8Char*						m_pcSuffixe;			/*!< Suffix string. */
	A3DUTF8Char*						m_pcPrefixe;			/*!< Prefix string. */

	A3DMDDimensionExtentionLine*		m_pExtentionLine;		/*!< Dimension extension line definition. */
	A3DMDDimensionLine*					m_pLine;				/*!< Dimension line definition. */
	EA3DMDDimensionOrientation			m_eOrientation;			/*!< Orientation. */
	A3DVector3dData						m_sOffSet;				/*!< Offset. */
	A3DUns16							m_usPosition;			/*!< Position. */

	EA3DMDDimensionScore				m_eScore;				/*!< Scoring. */
	A3DUns16							m_usScore;				/*!< Scoring covering. */
	A3DUns16							m_usScoreGroup;			/*!< Scoring element. */
	EA3DMDDimensionFrame				m_eFrame;				/*!< Frame type. */
	A3DUns16							m_usFrame;				/*!< Frame covering. */
	A3DUns16							m_usFrameGroup;			/*!< Frame element. */

	A3DMDTextProperties*				m_pTextProperties;		/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGet */
} A3DMarkupDimensionData;





/*!
\fn A3DStatus A3DMarkupDimensionGet( const A3DMarkupDimension* pDimension, A3DMarkupDimensionData* pData)
\brief Populates the \ref A3DMarkupDimensionData structure
\ingroup a3d_markupdimension
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupDimensionGet,( const A3DMarkupDimension* pDimension,
		 A3DMarkupDimensionData* pData));



#endif	/*	__A3DPRCMarkupDimension_H__ */
