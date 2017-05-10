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
\brief      Header file for the markup text module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMarkupText_H__
#define __A3DPRCMarkupText_H__

#ifndef __A3DPRCMARKUPDEFINITION__
#error A3DSDKMarkupSemantic.h must be included before current file
#endif

/*!
\version 4.0
@{
\enum EA3DMarkupFrameType
\ingroup a3d_markuptext
\brief Markup frame identifiers for markup text, datum, ....
*/

typedef enum
{
	KA3DMarkupFrameNone						= 0, /*!< No Frame. */
	KA3DMarkupFrameRectangle				= 1, /*!< Rectangle Frame. */
	KA3DMarkupFrameSquare					= 2, /*!< Square Frame. */
	KA3DMarkupFrameCircle					= 3, /*!< Circle Frame. */
	KA3DMarkupFrameScoredCircle				= 4, /*!< Scored Circle. */
	KA3DMarkupFrameDiamond					= 5, /*!< Diamond Frame. */
	KA3DMarkupFrameTriangle					= 6, /*!< Triangle Frame. */
	KA3DMarkupFrameRightFlag				= 7, /*!< Right Flag Frame. */
	KA3DMarkupFrameLeftFlag					= 8, /*!< Left Flag Frame. */
	KA3DMarkupFrameBothFlag					= 9, /*!< Both Flag Frame. */
	KA3DMarkupFrameOblong					= 10, /*!< Oblong Frame. */
	KA3DMarkupFrameEllipse					= 11, /*!< Ellipse Frame. */
	KA3DMarkupFrameFixRectangle				= 51, /*!< Fixed Rectangle Frame. */
	KA3DMarkupFrameFixSquare				= 52, /*!< Fixed Square Frame. */
	KA3DMarkupFrameFixCircle				= 53, /*!< Fixed Circle Frame. */
	KA3DMarkupFrameFixScoredCircle			= 54, /*!< Fixed Scored Circle Frame. */
	KA3DMarkupFrameFixDiamond				= 55, /*!< Fixed Diamond Frame. */
	KA3DMarkupFrameFixTriangle				= 56, /*!< Fixed Triangle Frame. */
	KA3DMarkupFrameFixRightFlag				= 57, /*!< Fixed Right Flag Frame. */
	KA3DMarkupFrameFixLeftFlag				= 58, /*!< Fixed Left Flag Frame. */
	KA3DMarkupFrameFixBothFlag				= 59, /*!< Fixed Both Flag Frame. */
	KA3DMarkupFrameFixOblong				= 60, /*!< Fixed Oblong Frame. */
	KA3DMarkupFrameFixEllipse				= 61, /*!< Fixed Ellipse Frame. */
	KA3DMarkupFrameCustom					= 255 /*!< Custom Frame. */
}EA3DMarkupFrameType;

/*!
\enum EA3DLeaderAlignementType
\ingroup a3d_markuptext
\brief Enumerations for Leader alignment type
This enumeration defines the way the leader anchors on markup.
\version 4.0

*/
typedef enum
{
	KA3DLeaderAlignement_Simple				= 0,
	KA3DLeaderAlignement_Bellow				= 1, /*!< For a text note, the leader underline the first text line. */
	KA3DLeaderAlignement_Underline			= 2, /*!< The leader underline all lines. */
	KA3DLeaderAlignement_ExtToMax				= 3, /*!< The leader underline all lines with the maximum line length. */
	KA3DLeaderAlignement_OnBoxPoint			= 4, /*!< The leader anchors to the markup bounding box. */
	KA3DLeaderAlignement_SimpleOnBoxPoint		= 5 /*!< The leader anchors to the markup bounding box, and in the middle of the line. */
} EA3DLeaderAlignementType;


/*!
@} <!-- end of a3d_markuptext_enums -->
*/
#ifndef __A3D_MARKUPTEXTPOSITION__

/*!
\struct A3DMDTextPositionData
\brief Markup text position
\ingroup a3d_markuptext
\version 4.0

*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DVector3dData	m_sPosition;	/*!< Origin for text orientation. */
	A3DVector3dData	m_sBaseVector;	/*!< Horizontal vector for text orientation. */
	A3DVector3dData	m_sUpVector;	/*!< Vertical vector for text orientation. */
} A3DMDTextPositionData;

/*!
\brief Populates the \ref A3DMDTextPositionData structure
\ingroup a3d_markuptext
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDTextPositionGet,(	const A3DMDTextPosition* pTextPosition,
		 A3DMDTextPositionData* pData));

#endif	/*	__A3D_MARKUPTEXTPOSITION__ */



#ifndef __A3D_MARKUPTEXT__

/*!
\defgroup a3d_markuptext Markups based on simple text
\ingroup a3d_markupnote
\version 4.0
*/


/*!
\struct A3DMarkupTextData
\brief Note with simple text (m_ppcLines) and text properties like font, size, thickness...
\ingroup a3d_markuptext
*/
typedef struct
{
	A3DUns16						m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32						m_uiLinesSize;				/*!< Size of next array. */
	A3DUTF8Char**					m_ppLines;					/*!< Note lines. */
	A3DUns32						m_uiFileLinksSize;			/*!< Number of file links. */
	A3DUTF8Char**					m_ppFileLinks;				/*!< Array of file links. */
	A3DDouble						m_dWrappingWidth;			/*!< Wrapping width. */
	EA3DMarkupFrameType				m_eFrameType;				/*!< Frame type. */
	EA3DLeaderAlignementType		m_eLeaderAlignementType;	/*!< Precises the leader/note attach. */
	A3DMDTextProperties*			m_pTextProperties;			/*!< Pointer to the text properties. \sa A3DMDTextPropertiesGetData */
	A3DMDTextPosition*				m_psTextPosition;			/*!< The relative position of the text to the attach of the markup \ref A3DMDTextPropertiesGet. */
} A3DMarkupTextData;

/*!
\fn A3DStatus A3DMarkupTextGet( const A3DMarkupText* pMarkupText, A3DMarkupTextData* pData)
\brief Populates the \ref A3DMarkupTextData structure
\ingroup a3d_markuptext
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupTextGet,( const A3DMarkupText* pMarkupText,
											A3DMarkupTextData* pData));


#endif	/*	__A3D_MARKUPTEXT__ */


#ifndef __A3D_MARKUPCOORDINATE__

/*!
\struct A3DMarkupCoordinateData
\brief Markup text with additional data.
Use \ref A3DMarkupTextGet to access to markup text data.
\ingroup a3d_markuptext


*/
typedef struct
{
	A3DUns16						m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble						m_dLitDimensionedX;		/*!< Coordinate x. */
	A3DDouble						m_dLitDimensionedY;		/*!< Coordinate y. */
	A3DDouble						m_dLitDimensionedZ;		/*!< Coordinate z. */
	A3DBool							m_bType3D;				/*!< Specifies if it's a 2D or a 3D coordinate; if it's the latter, m_dLitDimensionedZis is initialized. */
	A3DMDTextPosition*				m_psTextPosition;		/*!< The relative position of the text to the attach of the markup. \sa A3DMDTextPositionGetData */
} A3DMarkupCoordinateData;

/*!
\brief Populates the \ref A3DMarkupCoordinateData structure
\ingroup a3d_markuptext
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupCoordinateGet,( const A3DMarkupCoordinate* pMarkupCoordinate,
											A3DMarkupCoordinateData* pData));


#endif	/*	__A3D_MARKUPCOORDINATE__ */


#ifndef __A3D_MARKUPRICHTEXT__

/*!
\defgroup a3d_markuprichtext Markup note based on rich text
\ingroup a3d_markupnote
\version 4.0
*/

/*!
\struct A3DMarkupRichTextData
\brief Markup rich text data
\ingroup a3d_markuprichtext
\version 4.0
Entity type is \ref kA3DTypeMarkupRichText.
*/
typedef struct
{
	A3DUns16						m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*					m_pcRichText;			/*!< Text with RTF format. See \ref a3d_markup_rtf. */
	A3DUns32						m_uLength;				/*!< Length of the rich text. */
	A3DUns32						m_uiFileLinksSize;		/*!< Number of file links. */
	A3DUTF8Char**					m_ppFileLinks;			/*!< Array of file links. */
	A3DDouble						m_dWrappingWidth;		/*!< Wrapping width. */
	EA3DMarkupFrameType				m_eFrameType;			/*!< Frame type. */
	EA3DLeaderAlignementType	m_eLeaderAlignementType;	/*!< Precises the leader/note attach. */
	A3DMDTextPosition*				m_psTextPosition;		/*!< The relative position of the text to the attach of the markup. \sa A3DMDTextPositionGetData */
} A3DMarkupRichTextData;

/*!
\brief Populates the \ref A3DMarkupRichTextData structure
\ingroup a3d_markuprichtext
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMarkupRichTextGet,( const A3DMarkupRichText* pMarkupRichText,
											A3DMarkupRichTextData* pData));


#endif	/*	__A3D_MARKUPRICHTEXT__ */



#endif	/*	__A3DPRCMarkupText_H__ */
