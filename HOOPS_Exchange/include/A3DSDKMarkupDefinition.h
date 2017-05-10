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
\brief      Header file for the markup with definition module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMARKUPDEFINITION__
#define __A3DPRCMARKUPDEFINITION__

#ifndef __A3DPRCMARKUPLEADERDEFINITION__
#error A3DSDKMarkupLeaderDefinition.h must be included before current file
#endif


/*!\addtogroup a3d_markupdefinition_module
\details

The \ref A3DMkpAnnotationItemData structure references an \ref A3DMkpMarkup. This markup contains tessellation, leaders, and linked item information that is available by using the function \ref A3DMkpMarkupGet.
In addition this markup can contain also definition and specific data. Those data are stored in common structure \ref A3DMarkupDefinitionData and in a specific structure corresponding to the type return by the function \ref A3DEntityGetType.
For the structures corresponding to markups with definition, only access functions are defined. In other words, the customer can only create A3DMkpMarkup. 

\n
The following illustration shows the available methods to retrieve all the data.\n
In yellow, the data stored in the structure; in blue, the access function defined for corresponding structure.
\image html pmi_access.png

Here, it samples of the two ways to obtain markup data. In the first case, the markup contains only a tessellation, a type, and a sub type, in the second case, considering a markup text creation, the markup contains specific data (text, text properties (font...), position definition, display options, with a tessellation, a type, and a sub type.
\image html pmi_access_sample.png

See the following sample code:

\code

	//markup data

	A3DEEntityType eType;
	A3DInt32 iRet=A3DEntityGetType( pMarkup, &eType);
	// if ( iRet!=A3D_SUCCESS ) exit
	if(eType == kA3DTypeMkpMarkup)
	{
		//no definition is set, no information to retrieve
		//terminate...
	}

	//markup definition data

	A3DMarkupDefinitionData sDataDefinition;
	A3D_INITIALIZE_DATA( A3DMarkupDefinitionData, sDataDefinition);
	A3DInt32 iRet=A3DMarkupDefinitionGet((A3DMarkupDefinition*)pMarkup, &sDataDefinition);//sDataDefinition contains basic definition information

	//specific data

	A3DMarkupTextData sTextData;
	A3DMarkupDimensionData sDimensionData;
		switch(eType)
		{
		case kA3DTypeMarkupText:
		A3DMarkupTextData sTextData;
		A3D_INITIALIZE_DATA( A3DMarkupTextData, sTextData);
		A3DInt32 iRet=A3DMarkupTextGet((A3DMarkupText*)pMarkup, &sTextData);
		break;
		case kA3DTypeMarkupDimension:
		A3DMarkupDimensionData sDimensionData;
		A3D_INITIALIZE_DATA( A3DMarkupDimensionData, sDimensionData);
		A3DInt32 iRet=A3DMarkupTextGet((A3DMarkupDimension*)pMarkup, &sDimensionData);
		break;

		case kA3DTypeMarkupGDT:
		A3DMarkupGDTData sGDTData;
		A3D_INITIALIZE_DATA( A3DMarkupGDTData, sGDTData);
		A3DInt32 iRet=A3DMarkupGDTGet((A3DMarkupGDT*)pMarkup, &sGDTData);
		break;

		...same thing for all types

		default:
			break;

	}
\endcode

*/

/*!
\defgroup a3d_markupposition Position definition
\ingroup a3d_markupdefinition_module
\version 4.0
*/

/*!
\defgroup a3d_markupnote Notes
\ingroup a3d_markupdefinition_module
\version 4.0
*/



/*!
\defgroup a3d_markupdimension Dimension
\ingroup a3d_markupdefinition_module
\version 4.0
*/

/*!
\defgroup a3d_markuptolerance Tolerance
\ingroup a3d_markupdefinition_module
\version 4.0
*/

/*!
\defgroup a3d_markupsymbol Symbols
\ingroup a3d_markupdefinition_module
\version 4.0
*/
/*!
\defgroup a3d_markupwelding Welding
\ingroup a3d_markupdefinition_module
\version 4.0
*/



/*!
\enum EA3DMDMarkupDisplayType
\ingroup a3d_markupdefinition_module
\details
* The markup position is defined by an attach point and an attach type.
* 
* The attach type specifies the point of markup frame on which the attach point will be aligned.
* See below.\image html pmi_attach_type.png 
*/
typedef enum {
	KEA3DMDDisplayType_Unknown			= -1, /*!< Unknown. */
	KEA3DMDDisplayType_Unspecified		= 0, /*!< Unspecified. */
	KEA3DMDDisplayType_FlatToScreen		= 1,/*!< Flat to screen. */
	KEA3DMDDisplayType_FlatToSurface	= 2/*!< Flat to surface. */
}EA3DMDMarkupDisplayType;


#ifndef __A3D_MARKUPTEXTPROPERTIESDATA__
/*!
\enum EA3DMDTextPropertiesScore
\ingroup a3d_markupdefinition_module
\brief Enumerator that describes the score type applied on text
*/
typedef enum {
	KEA3DMDTextPropertiesScoreNone	= 0,	/*!< Text is not scored.																	*/
	KEA3DMDTextPropertiesUnderScored	= 1,	/*!< Text is underscored: draw a horizontal line below the text.						*/
	KEA3DMDTextPropertiesScored		= 2,	/*!< Also called strike through, Text is scored: draw a horizontal line through the text. */
	KEA3DMDTextPropertiesOverScored	= 3		/*!< Text is overscored: draw a horizontal line above the text.						*/
}EA3DMDTextPropertiesScore; 

/*!
\enum EA3DMDTextPropertiesFormat
\ingroup a3d_markupdefinition_module
\brief Enumerator that describes the format text
*/
typedef enum {
	KEA3DMDTextPropertiesFormatNormal	= 0, 	/*!< Classical text.							*/
	KEA3DMDTextPropertiesFormatUnderLine	= 1, 	/*!< Text positioning under the classical text.	*/
	KEA3DMDTextPropertiesFormatOverLine	= 2, 	/*!< Text positioning over the classical text.	*/
	KEA3DMDTextPropertiesFormatExposant	= 3, 	/*!< Text positioning as an exposant.			*/
	KEA3DMDTextPropertiesFormatindice	= 4 	/*!< Text positioning as an indice.				*/
}EA3DMDTextPropertiesFormat; 

/*!
\enum EA3DMDTextPropertiesJustification
\ingroup a3d_markupdefinition_module
\brief Enumerator that justifies the text
*/
typedef enum {
	KEA3DMDTextPropertiesJustificationLeft	= 0, /*!< Justifies the text on the left side. */
	KEA3DMDTextPropertiesJustificationCenter	= 1, /*!< Centers the text. */
	KEA3DMDTextPropertiesJustificationRight	= 2  /*!< Justifies the text on the right side. */
}EA3DMDTextPropertiesJustification;

/*!
\struct A3DMDTextPropertiesData
\brief Markup text properties data structure
\ingroup a3d_markupdefinition_module
\version 4.0

\note For Markup rich text, properties are encoded into string attached to. It is the role of
the user to parse through these properties. In case of simple text and others markups, the user needs this function in
order to get properties.
*/

typedef struct
{
	A3DUns16							m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA.					*/
	A3DUTF8Char*						m_pcFont;				/*!< Font of text.																	*/
	A3DDouble							m_dAngle;				/*!< Slant angle (expressed in degrees).											*/
	A3DBool								m_bSlant;				/*!< Is the text slanted?															*/
	A3DUns16							m_ucThickness;			/*!< Thickness of the text.															*/
	A3DUns16							m_ucSize;				/*!< Font size.																		*/
	A3DUns16							m_usLineStyle;			/*!< Index of line symbol style in the table. \sa A3DGlobalLineStyleGe				*/
	A3DDouble							m_dCharHeight;			/*!< Char height (expressed in mm). If this value is not used, it is set to -1.		*/
	A3DDouble							m_dCharSpacing;			/*!< Char spacing (expressed in mm). If this value is not used, it is set to -1.	*/
	A3DDouble							m_dCharWidth;			/*!< Char width (expressed in mm). If this value is not used, it is set to -1.		*/
	A3DUns16							m_iCharFixedRatioMode;	/*!< Char fixed ratio mode. If this value is not used, it is set to -1.				*/
	EA3DMDTextPropertiesScore			m_eGlobalTextScoring;	/*!< Global text scoring.															*/
	EA3DMDTextPropertiesFormat			m_eFormat;				/*!< Text format.																	*/
	EA3DMDTextPropertiesJustification	m_eJustification;		/*!< Text justification.															*/
}A3DMDTextPropertiesData;



/*!
\brief Populates the \ref A3DMDTextPropertiesData structure
\ingroup a3d_markupdefinition_module
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDTextPropertiesGet,(	const A3DMDTextProperties* pTextProperties,
		 A3DMDTextPropertiesData* pData));


#endif	/*	__A3D_MARKUPTEXTPROPERTIESDATA__ */






#ifndef __A3DPRCMARKUPDEFINITIONDATA__

/*!
\struct A3DMarkupDefinitionData
\brief Structure defining common data to all markup with definition
\ingroup a3d_markupdefinition_module
\version 4.0
*/
typedef struct 
{
	A3DUns16						m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */

	A3DMDPosition*					m_pAttach;				/*!< Position of the markup. */
	EA3DMDAnchorPointType			m_eAttachType;			/*!< Attach point type. See \ref EA3DMDAnchorPointType for details. */
	A3DDouble						m_dAttachAngle;			/*!< Z angle. */

	A3DBool							m_bDisplayParallelOnScreen;		/*!< A value of true specifies the markup is displayed parallel to the screen. */
	A3DBool							m_bZoomable;					/*!< A value of true specifies the markup is zoomable. */
	A3DBool							m_bLeaderNotIntersectWithBox;	/*!< A value of true specifies the markup leader(s) can cross the markup box. */

} A3DMarkupDefinitionData;

/*!
\brief Populates the \ref A3DMarkupDefinitionData structure
\ingroup a3d_markupdefinition_module
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupDefinitionGet,(	const A3DMarkupDefinition* pMarkupDefinition,
		 A3DMarkupDefinitionData* pData));





#endif	/*	__A3DPRCMARKUPDEFINITIONDATA__ */

#endif	/*	__A3DPRCMARKUPDEFINITION__ */
