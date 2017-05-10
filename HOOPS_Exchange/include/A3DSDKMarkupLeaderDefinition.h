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
\brief      Header file for the leader definition module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMARKUPLEADERDEFINITION__
#define __A3DPRCMARKUPLEADERDEFINITION__

/*!
\defgroup a3d_markupleaderdefinition Leader definition
\ingroup a3d_markupleader
\version 4.0
*/


/*!
\enum EA3DMDAnchorPointType
\brief Markup anchor point type
\ingroup a3d_markupposition
*/
typedef enum {

	KEA3DMDAnchorIgnored			=  -1,

	KEA3DMDAnchorTop_left		=  0,	/*!< Top left point. */
	KEA3DMDAnchorTop_center		=  1,	/*!< Top center point. */
	KEA3DMDAnchorTop_right		=  2,	/*!< Top right point. */

	KEA3DMDAnchorMiddle_left		= 10,	/*!< Middle left point.	*/
	KEA3DMDAnchorMiddle_center	= 11,	/*!< Middle center point. */
	KEA3DMDAnchorMiddle_right	= 12,	/*!< Middle right point. */
	KEA3DMDAnchorMiddle_auto		= 13,	/*!< Closest point to the middle of the frame. */

	KEA3DMDAnchorBottom_left		= 20,	/*!< Bottom left point.	*/
	KEA3DMDAnchorBottom_center	= 21,	/*!< Bottom center point. */
	KEA3DMDAnchorBottom_right	= 22,	/*!< Bottom right point. */
	KEA3DMDAnchorBottom_auto		= 23, /*!< Closest point to the bottom of the frame. */

	KEA3DMDAnchorAutomatic		= 24  /*!< Closest point to the frame. */

}EA3DMDAnchorPointType;


#ifndef __A3D_MARKUPPOSITIONDATA__
/*!\addtogroup a3d_markupposition
\details
Positionning information are stored in one of this three structure:
\li \ref A3DMDPosition3DData, defined by a 3D vector
\li \ref A3DMDPosition2DData, defined by a 2D vector and a plane
\li \ref A3DMDPositionReferenceData, according to another position
*/
/*!
\struct A3DMDPosition3DData
\brief Definition of a position with a 3D vector
\ingroup a3d_markupposition
\version 4.0
*/
typedef struct
{
	A3DUns16		m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DVector3dData	m_sPosition;	/*!< 3D point defining the position. */
}A3DMDPosition3DData;


/*!
\brief Populates the \ref A3DMDPosition3DData structure
\ingroup a3d_markupposition
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDPosition3DGet,( const A3DMDPosition3D* pPosition3D,
		 A3DMDPosition3DData* pData));
/*!
\struct A3DMDPosition2DData
\brief Definition of a position with a 2D vector, a plane and an offset
\ingroup a3d_markupposition
\version 4.0
*/
typedef struct
{
	A3DUns16			m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DVector2dData		m_sPosition;	/*!< 2D point defining the position. */
	A3DDouble			m_dOffset;		/*!< Offset from plane along normal vector. */
	A3DSurfPlane*		m_pPlane;		/*!< Plane definition. */
}A3DMDPosition2DData;


/*!
\brief Populates the \ref A3DMDPosition2DData structure
\ingroup a3d_markupposition
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDPosition2DGet,( const A3DMDPosition2D* pPosition2D,
		 A3DMDPosition2DData* pData));

/*!
\struct A3DMDPositionReferenceData
\brief Definition of a position according to another position
\ingroup a3d_markupposition
\version 4.0
*/
typedef struct
{
	A3DUns16			m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA.	*/
	A3DMiscMarkupLinkedItem*	m_psLinkedItem;	/*!< Position reference. */
	EA3DMDAnchorPointType		m_eAttachType;	/*!< Indicates which point of reference markup frame corresponds to the calculate attach. */
	A3DVector2dData m_sOffsetToReference;		/*!< 2D point defining the offset. */

}A3DMDPositionReferenceData;


/*!
\brief Populates the \ref A3DMDPositionReferenceData structure
\ingroup a3d_markupposition
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDPositionReferenceGet,(	const A3DMDPositionReference* pPositionReference,
		 A3DMDPositionReferenceData* pData));

#endif	/*	__A3D_MARKUPPOSITIONDATA__ */




#ifndef __A3D_MARKUPLEADERDATA__


/*!
\enum A3DMDLeaderSymbolType
\ingroup a3d_markupleaderdefinition
\brief Enumerate that describes leader end symbols.
*/
typedef enum  {
	KA3DMDLeaderSymbolNotUsed					= 0, /*!< Undocumented. */
	KA3DMDLeaderSymbolCross						= 1, /*!< Cross. */
	KA3DMDLeaderSymbolPlus						= 2, /*!< Plus sign. */
	KA3DMDLeaderSymbolConcentric					= 3, /*!< Concentric sign. */
	KA3DMDLeaderSymbolCoincident					= 4, /*!< Undocumented. */
	KA3DMDLeaderSymbolFullCircle					= 5, /*!< Undocumented. */
	KA3DMDLeaderSymbolFullSquare					= 6, /*!< Undocumented. */
	KA3DMDLeaderSymbolStar						= 7, /*!< Undocumented. */
	KA3DMDLeaderSymbolDot						= 8, /*!< Undocumented. */
	KA3DMDLeaderSymbolSmallDot					= 9, /*!< Undocumented. */
	KA3DMDLeaderSymbolMisc1						= 10, /*!< Undocumented. */
	KA3DMDLeaderSymbolMisc2						= 11, /*!< Undocumented. */
	KA3DMDLeaderSymbolFullCircle2				= 12, /*!< Undocumented. */
	KA3DMDLeaderSymbolFullSquare2				= 13, /*!< Undocumented. */
	KA3DMDLeaderSymbolOpenArrow					= 14, /*!< Open arrow. */
	KA3DMDLeaderSymbolUnfilledArrow				= 15, /*!< Transparent arrow. */
	KA3DMDLeaderSymbolBlankedArrow				= 16, /*!< Blanked arrow. */
	KA3DMDLeaderSymbolFilledArrow				= 17, /*!< Filled arrow. */
	KA3DMDLeaderSymbolUnfilledCircle				= 18, /*!< Transparent circle. */
	KA3DMDLeaderSymbolBlankedCircle				= 19, /*!< Opaque circle. */
	KA3DMDLeaderSymbolFilledCircle				= 20, /*!< Filled circle. */
	KA3DMDLeaderSymbolCrossedCircle				= 21, /*!< Crossed circle. */
	KA3DMDLeaderSymbolBlankedSquare				= 22, /*!< Opaque square. */
	KA3DMDLeaderSymbolFilledSquare				= 23, /*!< Filled square. */
	KA3DMDLeaderSymbolBlankedTriangle			= 24, /*!< Opaque triangle. */
	KA3DMDLeaderSymbolFilledTriangle				= 25, /*!< Filled triangle. */
	KA3DMDLeaderSymbolManipulatorSquare			= 26, /*!< Undocumented. */
	KA3DMDLeaderSymbolMamipulatorDiamond			= 27, /*!< Undocumented. */
	KA3DMDLeaderSymbolManipulatorCircle			= 28, /*!< Undocumented. */
	KA3DMDLeaderSymbolManipulatorTriangle		= 29, /*!< Undocumented. */
	KA3DMDLeaderSymbolDoubleOpenArrow			= 30, /*!< Double open arrow. */
	KA3DMDLeaderSymbolWave						= 31 /*!< Wave sign. */
} A3DMDLeaderSymbolType;


/*!
\struct A3DMDLeaderSymbolData
\brief Markup leader symbol data structure
\ingroup a3d_markupleaderdefinition
\version 4.0
*/
typedef struct
{
	A3DUns16					m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMDLeaderSymbolType		m_eHeadSymbol;				/*!< Terminating symbol. */
	A3DDouble					m_dLength;					/*!< Arrow length or circle diameter,... defined in model unit. */
	A3DDouble					m_dAdditionalParameter;		/*!< Angle for symbol arrow, thickness for symbol segment (defined in degree). */
}A3DMDLeaderSymbolData;


/*!
\brief Populates the \ref A3DMDLeaderSymbolData structure
\ingroup a3d_markupleaderdefinition
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDLeaderSymbolGet,(	const A3DMDLeaderSymbol* pLeaderSymbol,
		 A3DMDLeaderSymbolData* pData));



/*!
\struct A3DMDMarkupLeaderStubData
\brief Markup Leader stub data structure
\ingroup a3d_markupleaderdefinition
\version 4.0
\details
The stub is a line which links the leader(s) to the markup box. It is vertical or horizontal line according to the attach point type, and its length depends on the attach point type. 
Therefore, in the structure of markup leader stub, there are two arrays to be considered in parallel: 
the first defines the length of the stub, and the second the anchor point type corresponding to the length.
\image html pmi_leader_stub.png


*/
typedef struct 
{
	A3DUns16				m_usStructSize;						/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */

	A3DUns32				m_uiValuesAndAnchorTypesSize;		/*!< Size of array of values and anchor types. */
	A3DDouble*				m_pdValues;
	A3DUns32*				m_piAnchorTypes;
} A3DMDMarkupLeaderStubData;


/*!
\brief Populates the \ref A3DMDMarkupLeaderStubData structure
\ingroup a3d_markupleaderdefinition
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDMarkupLeaderStubGet,(	const A3DMDMarkupLeaderStub* pLeaderStub,
		 A3DMDMarkupLeaderStubData* pData));

/*!
\struct A3DMDLeaderDefinitionData
\brief Leader data structure
\ingroup a3d_markupleaderdefinition
\version 4.0
*/
typedef struct 
{
	A3DUns16					m_usStructSize;						/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */

	A3DUns32					m_uiNumberOfPathLeaderPositions;	/*!< Number of path leader positions. */
	A3DMDPosition**				m_ppsPathLeaderPositions;
	/*!< Array of path leader positions 
	* This set of markup positions indicates the points: starting with the point on geometry 
	* and finishing with the nearest attach point. See below \image html pmi_leader_path_points.png 
	\par Dimension cases
	* Dimension markups use same leaders as others, but the path positions have to be interpreted array according to the dimension type. 
	* Therefore, for each type, the markup contains specific leader: \image html pmi_leader_path_points_dimension.png
	*/

	A3DUns32					m_uiNbGapsElements;					/*!< Number of gap in following list. */
	A3DDouble*					m_pdGapList;						
	/*!< Array defining leader line interruptions between the entity pointed and the started point.
	* For each interruption two values are stored to indicate the start and end points,
	* and values are ration leader length/ distance to the end.
	*/

	A3DMDLeaderSymbol*			m_pHeadSymbol;						/*!< Leader symbol, ref to \ref A3DMDLeaderSymbolData. May be NULL. */
	A3DMDLeaderSymbolType		m_eTailSymbol;						/*!< Terminating symbol. */

	A3DMDLeaderDefinition*		m_pNextLeader;						/*!<
																	Next leader, may be NULL.
																	*The attach point type defined on the next leader denotes if there is an additional line between both leaders.
																	*If the attach type is zero, we have to create a segment between the first point of the next leader and the last of the preceding leader. In the first case, 
																	*the markup (usally a datum markup) has only one point to define the leader; this type of next leader is used to have additional points.
																	*Otherwise, the next leader appears as an extension line.
																	\image html pmi_markup_leader_next_classical_case.png

																	* The next leader can also be used when a markup is attached to radial dimension markup leader.
																	*The next points define a circle arc: the first point is the arc center, the second is the start point of the arc; 
																	*the end point is the last point of the previous (owning) leader. 
																	*The start point can be offset by the second value of overrun and the end point by the second value of blanking.
																	\image html pmi_markup_leader_next_dimension_case.png
																	*/
	A3DUns32					m_uAnchorFrame;						/*!<
																	Defines to which box the leader will be attached. 
																	* In most cases, the index is equal to zero when there is only one box. 
																	* It can be different for the feature frame control: see next figure to understand the numbering process. \image html pmi_leader_anchor_type.png
																	*/
	A3DUns32					m_uAnchorPoint;						/*!< Defines the anchor point type, the.point of the box where the leader starts; this information is the same as for the markup attach type*/
	A3DMDMarkupLeaderStub*		m_pStub;							/*!< Leader stub, ref to \ref A3DMDMarkupLeaderStubData. May be NULL. */

} A3DMDLeaderDefinitionData;



/*!
\brief Populates the \ref A3DMDLeaderDefinitionData structure
\ingroup a3d_markupleaderdefinition
\version 4.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMDLeaderDefinitionGet,(	const A3DMDLeaderDefinition* pLeader,
		 A3DMDLeaderDefinitionData* pData));

#endif	/*	__A3D_MARKUPLEADERDATA__ */
#endif	/*	__A3DPRCMARKUPLEADERDEFINITION__ */

