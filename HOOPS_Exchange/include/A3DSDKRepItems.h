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
\brief      Header file for representation item entities
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCREPITEMS_H__
#define __A3DPRCREPITEMS_H__

#ifndef __A3DPRCGEOMETRY_H__
#error A3DSDKGeometry.h must be included before current file
#endif

#ifndef __A3DPRCREADWRITE_H__
#error A3DSDKReadWrite.h must be included before current file
#endif

#ifndef __A3D_RI__
/*!
\defgroup a3d_repitem Representation Items Module
\ingroup a3d_entitiesdata_module
Representation item entities define individual objects that are present in a CAD file,
such as a bolt, wheel, or table leg.

Multiple representation items are contained within a part definition,
which scales and positions the representation items within a 3D space. 
The result is a 3D part that can be assembled into higher level product occurrences, 
such as an engine part, car, or table.

An \ref A3DRiRepresentationItem contains a local \ref A3DRiCoordinateSystem.
The \ref A3DRiCoordinateSystem coordinate system is expressed relative to the 
parent product occurrence's coordinate system (\ref A3DAsmProductOccurrence).

All representation item entities inherit the \ref A3DRiRepresentationItem base class.
*/

#endif	/*	__A3D_RI__ */


#ifndef __A3D_RICONTENT__
/*!
\defgroup a3d_ricontent Representation Item Base
\ingroup a3d_repitem
*/

/*!
\brief Representation Item Structure
\ingroup a3d_ricontent
\version 2.0
*/
typedef struct
{
	A3DUns16				m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DTessBase*			m_pTessBase;			/*!< Tessellation base. */
	A3DRiCoordinateSystem*	m_pCoordinateSystem;	/*!< Coordinate system. */
} A3DRiRepresentationItemData;

/*!
\brief Populates the \ref A3DRiRepresentationItemData structure
\ingroup a3d_ricontent
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiRepresentationItemGet,(const A3DRiRepresentationItem* pRi,
																A3DRiRepresentationItemData* pData));

/*!
\brief Sets a previously created \ref A3DRiRepresentationItem with an \ref A3DRiRepresentationItemData structure
\ingroup a3d_ricontent
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SET_INCONSISTENT_EMPTY \n	
\return \ref A3D_SUCCESS \n
\note The \ref A3DRiRepresentationItem entity is an abstract class. You cannot directly create this entity.
Instead, use the appropriate derived function (such as \ref A3DRiSetCreate or \ref A3DRiPointSetCreate)
to create a specific representation item entity.
Then use this function to specify values in that entity base class. 
For example, this function specifies a value for the \ref A3DRiRepresentationItemData::m_pCoordinateSystem member. 
*/
A3D_API (A3DStatus, A3DRiRepresentationItemSet,(A3DRiRepresentationItem* pRi,
																const A3DRiRepresentationItemData* pData));

/*!
\brief Calculates the tessellation of a previously created \ref A3DRiRepresentationItem with an \ref A3DRWParamsTessellationData parameters
\ingroup a3d_ricontent
\version 4.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SET_INCONSISTENT_EMPTY \n	
\return \ref A3D_SUCCESS \n
\note If the \ref A3DRiRepresentationItem entity has already been tessellated, the previous tessellation will be
replaced by the new one. This function works for brep models and curves only.
*/

A3D_API (A3DStatus, A3DRiRepresentationItemGetTessellation,(A3DRiRepresentationItem* pRi,
																				const A3DRWParamsTessellationData* pTessellationParametersData));



/*!
\brief Function to release the tessellation stored on the representation item
\version 5.0
\ingroup a3d_ricontent
\par

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DRiReleaseTesselation,(A3DRiRepresentationItem* pRepresentationItem));

#endif	/*	__A3D_RICONTENT__ */

#ifndef __A3D_RISET__
/*!
\defgroup a3d_riset Set Representation Item
\ingroup a3d_repitem
This entity is a logical grouping of other representation items. 
No matrix for placement is attached to components, 
and an \ref A3DRiSet entity can contain multiple child \ref A3DRiSet sets. 

\warning A representation item cannot belong to more than one set.

\par Sample code
\include Set.cpp
*/

/*!
\brief Set structure
\ingroup a3d_riset
\version 2.0
*/
typedef struct
{
	A3DUns16					m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32					m_uiRepItemsSize;	/*!< Size of next array. */
	A3DRiRepresentationItem**	m_ppRepItems;		/*!< Array of representation items in the set. */
} A3DRiSetData;

/*!
\brief Populates the \ref A3DRiSetData structure
\ingroup a3d_riset
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiSetGet,(const A3DRiSet* pSet,
											A3DRiSetData* pData));

/*!
\brief Creates an \ref A3DRiSet from \ref A3DRiSetData structure
\ingroup a3d_riset
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SET_INCONSISTENT_EMPTY \n	
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiSetCreate,(const A3DRiSetData* pData,
												A3DRiSet** ppSet));
#endif	/*	__A3D_RISET__ */

#ifndef __A3D_RIPOINTSET__
/*!
\defgroup a3d_ripointset PointSet Representation Item
\ingroup a3d_repitem
An \ref A3DRiPointSet is a set of 3D points. 

When the \ref A3DRiPointSetGet function populates an \ref A3DRiPointSetData structure, 
it allocates arrays of coordinates. 
When you no longer need the \ref A3DRiPointSetData structure, invoke the \ref A3DRiPointSetGet function 
with the first argument set to NULL to free its allocated memory.
\par Sample code
\include PointSet.cpp
*/

/*!
\brief PointSet structure
\ingroup a3d_ripointset
\version 2.0
*/
typedef struct
{
	A3DUns16			m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32			m_uiSize;		/*!< Number of points in the set. */
	A3DVector3dData*	m_pPts;			/*!< Array of 3D points. */
} A3DRiPointSetData;

/*!
\brief Populates the \ref A3DRiPointSetData structure
\ingroup a3d_ripointset
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiPointSetGet,(const A3DRiPointSet* pPointSet,
													A3DRiPointSetData* pData));

/*!
\brief Creates an \ref A3DRiPointSet from an \ref A3DRiPointSetData structure
\ingroup a3d_ripointset
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiPointSetCreate,(const A3DRiPointSetData* pData,
														A3DRiPointSet** ppPointSet));

#endif	/*	__A3D_RIPOINTSET */

#ifndef __A3D_RIDIRECTION__
/*!
\defgroup a3d_ridirection Direction Representation Item
\ingroup a3d_repitem
\version 2.0

An \ref A3DRiDirection is defined by a point (optional) and a vector (mandatory).
*/

/*!
\brief Direction structure
\ingroup a3d_ridirection
\version 2.0
*/
typedef struct
{
	A3DUns16		m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool			m_bHasOrigin;		/*!< If this boolean is false, m_sOrigin has no meaning. */
	A3DVector3dData	m_sOrigin;			/*!< Origin (optional). */
	A3DVector3dData	m_sDirection;		/*!< Direction. */
} A3DRiDirectionData;

/*!
\brief Populates the \ref A3DRiDirectionData structure
\ingroup a3d_ridirection
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiDirectionGet,(const A3DRiDirection* pDirection,
													A3DRiDirectionData* pData));

/*!
\brief Creates an \ref A3DRiDirection from an \ref A3DRiDirectionData structure
\ingroup a3d_ridirection
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
\todo Not yet implemented
*/
A3D_API (A3DStatus, A3DRiDirectionCreate,(const A3DRiDirectionData* pData,
														A3DRiDirection** ppDirection));

#endif	/*	__A3D_RIDIRECTION */

#ifndef __A3D_RICSYS__
/*!
\defgroup a3d_ricoordinatesystem Coordinate System Representation Item
\ingroup a3d_repitem
\brief An axis system

An \ref A3DRiCoordinateSystem is an \ref A3DRiRepresentationItem that specifies a coordinate system. 
The \ref A3DRiCoordinateSystemData structure contains an \ref A3DMiscCartesianTransformation 
axis system. This axis system owns the geometric data: there is no particular
geometry attached, and the user is responsible for representation.

\note An \ref A3DRiCoordinateSystem is an \ref A3DRiRepresentationItem and not an \ref A3DMiscCartesianTransformation.
Being a representation item, a coordinate system can own a local coordinate system (on the RI level), which can also
own a local coordinate system, and so on... 
*/

/*!
\brief Coordinate System structure
\ingroup a3d_ricoordinatesystem
\version 2.0
*/
typedef struct
{
	A3DUns16					m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMiscTransformation*		m_pTransformation;		/*!< Cartesian transformation 3D. Cannot be NULL. */
} A3DRiCoordinateSystemData;

/*!
\brief Populates the \ref A3DRiCoordinateSystemData structure
\ingroup a3d_ricoordinatesystem
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE\n
\return \ref A3D_INVALID_DATA_STRUCT_NULL\n
\return \ref A3D_INVALID_ENTITY_NULL\n
\return \ref A3D_INVALID_ENTITY_TYPE\n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DRiCoordinateSystemGet,(const A3DRiCoordinateSystem* pCoordinateSystem,
															A3DRiCoordinateSystemData* pData));

/*!
\brief Creates an \ref A3DRiCoordinateSystem from an \ref A3DRiCoordinateSystemData structure
\ingroup a3d_ricoordinatesystem
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SET_INCONSISTENT_EMPTY \n	
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiCoordinateSystemCreate,(const A3DRiCoordinateSystemData* pData,
																A3DRiCoordinateSystem** ppCoordinateSystem));
#endif	/*	__A3D_RICSYS__ */


#ifndef __A3D_RICURVE__
/*!
\defgroup a3d_ricurve Curve Representation Item
\ingroup a3d_repitem
An \ref A3DRiCurve is a representation item that contains a geometrical curve. 
\sa \ref a3d_crv.
*/

/*!
\brief RiCurve structure
\ingroup a3d_ricurve
\version 2.0
*/
typedef struct
{
	A3DUns16				m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DTopoSingleWireBody*	m_pBody;				/*!< Body. */
} A3DRiCurveData;

/*!
\brief Populates the \ref A3DRiCurveData structure
\ingroup a3d_ricurve
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiCurveGet,(const A3DRiCurve* pRICrv,
												A3DRiCurveData* pData));

/*!
\brief Creates an \ref A3DRiCurve from an \ref A3DRiCurveData structure
\ingroup a3d_ricurve
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiCurveCreate,(const A3DRiCurveData* pData,
													A3DRiCurve** ppRICrv));

/*!
\brief Get the geometrical element used to build the \ref A3DRiCurve
\ingroup a3d_ricurve
\version 6.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/

A3D_API (A3DStatus, A3DRiCurveSupportGet,(const A3DRiCurve* pRiCurve,
		 A3DMiscMarkupLinkedItem*& pLinkedItem));
#endif	/*	__A3D_RICURVE__ */


#ifndef __A3D_RIPLANE__
/*!
\defgroup a3d_riplane Plane Representation Item
\ingroup a3d_repitem
An \ref A3DRiPlane is a representation item that contains a \ref A3DTopoBrepData made of one single planar face.
*/

/*!
\brief RiPlane structure
\ingroup a3d_riplane
\version 2.0
*/
typedef struct
{
	A3DUns16			m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DTopoBrepData*	m_pBrepData;			/*!< Topological entry for plane description. Made of one face, no trimming loops. */
} A3DRiPlaneData;

/*!
\brief Populates the \ref A3DRiPlaneData structure
\ingroup a3d_riplane
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiPlaneGet,(const A3DRiPlane* pRiPlane,
												A3DRiPlaneData* pData));

/*!
\brief Creates an \ref A3DSurfPlane from an \ref A3DRiPlaneData structure
\ingroup a3d_riplane
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiPlaneCreate,(const A3DRiPlaneData* pData,
													A3DRiPlane** ppRIPlane));



/*!
\brief Get the geometrical element used to build the \ref A3DRiPlane
\ingroup a3d_riplane
\version 6.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/

A3D_API (A3DStatus, A3DRiPlaneSupportGet,(const A3DRiPlane* pRiPlane,
		 A3DMiscMarkupLinkedItem*& pLinkedItem));

#endif	/*	__A3D_RIPLANE__ */


#ifndef __A3D_RIBREPMODEL__
/*!
\defgroup a3d_ribrepmodel BrepModel Representation Item
\ingroup a3d_repitem
An \ref A3DRiBrepModel is a representation item that contains a topological Boundary Representation.
*/

/*!
\brief BrepModel structure
\ingroup a3d_ribrepmodel
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bSolid;				/*!< Solid or Shell flag. */
	A3DTopoBrepData* m_pBrepData;	/*!< Topological description of the B-rep. */
} A3DRiBrepModelData;

/*!
\brief Populates the \ref A3DRiBrepModelData structure
\ingroup a3d_ribrepmodel
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiBrepModelGet,(const A3DRiBrepModel* pRIBrepModel,
													A3DRiBrepModelData* pData));

/*!
\brief Creates an \ref A3DRiBrepModel from an \ref A3DRiBrepModelData structure
\ingroup a3d_ribrepmodel
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiBrepModelCreate,(const A3DRiBrepModelData* pData,
														A3DRiBrepModel** ppRIBrepModel));
#endif	/*	__A3D_RIBREPMODEL__ */

#ifndef __A3D_RIPOLYBREPMODEL__
/*!
\defgroup a3d_ripolybrepmodel PolyBrepModel Representation Item
\ingroup a3d_repitem
An \ref A3DRiPolyBrepModel is a representation item that contains only a tessellation of a solid or a surface.
\sa \ref A3DTessBaseGet
*/

/*!
\brief PolyBrepModel structure
\ingroup a3d_ripolybrepmodel
\version 2.0

This structure handles only a flag indicating whether the tessellation is closed (solid). 
Tessellation must be recovered with base class function \ref A3DRiRepresentationItemGet.
\sa \ref a3d_tessellation_module 
*/
typedef struct
{
	A3DUns16	m_usStructSize; 		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool		m_bIsClosed;			/*!< A value of true indicates the tessellation closed; otherwise, it is open. */
} A3DRiPolyBrepModelData;

/*!
\brief Populates the \ref A3DRiPolyBrepModelData structure
\ingroup a3d_ripolybrepmodel
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE\n
\return \ref A3D_INVALID_DATA_STRUCT_NULL\n
\return \ref A3D_INVALID_ENTITY_NULL\n
\return \ref A3D_INVALID_ENTITY_TYPE\n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DRiPolyBrepModelGet,(	const A3DRiPolyBrepModel* pRIPolyBrepModel,
															A3DRiPolyBrepModelData* pData));

/*!
\brief Creates an \ref A3DRiPolyBrepModel from an \ref A3DRiPolyBrepModelData structure
\ingroup a3d_ripolybrepmodel
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiPolyBrepModelCreate,(	const A3DRiPolyBrepModelData* pData,
																A3DRiPolyBrepModel** ppRIPolyBrepModel));

#endif	/*	__A3D_RIPOLYBREPMODEL__ */

#ifndef __A3D_RIPOLYWIRE__
/*!
\defgroup a3d_ripolywire PolyWire Representation Item
\ingroup a3d_repitem
An \ref A3DRiPolyWire is a representation item that contains a polywire. 
See the description for the \ref A3DRiPolyBrepModelData structure
to understand how to access the data (tessellation definition). 

\sa \ref A3DRiPolyWire
*/

/*!
\brief PolyWire structure
\ingroup a3d_ripolywire
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize; /*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
} A3DRiPolyWireData;

/*!
\brief Populates the \ref A3DRiPolyWireData structure
\ingroup a3d_ripolywire
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE\n
\return \ref A3D_INVALID_DATA_STRUCT_NULL\n
\return \ref A3D_INVALID_ENTITY_NULL\n
\return \ref A3D_INVALID_ENTITY_TYPE\n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DRiPolyWireGet,(	const A3DRiPolyWire* pRIPolyWire,
													A3DRiPolyWireData* pData));

/*!
\brief Creates an \ref A3DRiPolyWire from an \ref A3DRiPolyWireData structure
\ingroup a3d_ripolywire
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SET_INCONSISTENT_EMPTY \n	
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRiPolyWireCreate,(	const A3DRiPolyWireData* pData,
														A3DRiPolyWire** ppRIPolyWire));

#endif	/*	__A3D_RIPOLYWIRE__ */

#endif	/*	__A3DPRCREPITEMS_H__ */
