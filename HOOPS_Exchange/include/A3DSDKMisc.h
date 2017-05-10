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
\brief      Header file for tools used with structure and geometry
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMISC_H__
#define __A3DPRCMISC_H__

#ifndef __A3DPRCGEOMETRY_H__
#error A3DSDKGeometry.h must be included before current file
#endif

/*!
\defgroup a3d_misc_module Miscellaneous Module
\ingroup a3d_entitiesdata_module
\brief Tools and common structures 

This module describes tools and common structures.
*/

#ifndef __A3D_TRSF__
/*!
\defgroup a3d_misc_trsf Transformations Module
\ingroup a3d_misc_module
\brief Creates and accesses transformation entities 
	that can be applied to PRC entities containing geometry

This module describes the transformation entities that can be applied 
to PRC entities containing geometry. 

The abstract base entity for this module (\ref A3DMiscTransformation)  
appears in structure members as a pointer that references 
either an \ref A3DMiscCartesianTransformation or an \ref A3DMiscGeneralTransformation entity. 
There are no functions to separately create or access an \ref A3DMiscTransformation entity.

To determine the type of transformation entity referenced by an \ref A3DMiscTransformation pointer,
use the \ref A3DEntityGetType function.
*/

/*!
\defgroup a3d_generaltransfo3d General 3D Transformation (using 4x4 transformation matrices)
\ingroup a3d_misc_trsf
\brief Functions and structures for defining 4x4 transformation matrices that translate, scale, and rotate

Entity type is \ref kA3DTypeMiscGeneralTransformation.

An \ref A3DMiscGeneralTransformation entity describes a 3D general transformation 
that translates, scales and rotates the associated geometric entity.

@{
*/

/*!
\brief Structure that specifies a 4x4 matrix for use in the \ref A3DMiscGeneralTransformation entity
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_adCoeff[16];		/*!< Matrix[4][4]. */
} A3DMiscGeneralTransformationData;

/*!
\brief Populates the \ref A3DMiscGeneralTransformationData structure
\ingroup a3d_generaltransfo3d
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE\n
\return \ref A3D_INVALID_DATA_STRUCT_NULL\n
\return \ref A3D_INVALID_ENTITY_NULL\n
\return \ref A3D_INVALID_ENTITY_TYPE\n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DMiscGeneralTransformationGet,(	const A3DMiscGeneralTransformation* pGeneralTransformation3d,
																		A3DMiscGeneralTransformationData* pData));

/*!
\brief Creates an \ref A3DMiscGeneralTransformation from an \ref A3DMiscGeneralTransformationData structure. 
\ingroup a3d_generaltransfo3d
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n

*/

A3D_API (A3DStatus, A3DMiscGeneralTransformationCreate,(	const A3DMiscGeneralTransformationData* pData,
																			A3DMiscGeneralTransformation** ppGeneralTransformation3d));
/*!
@} <!-- end of module a3d_generaltransfo3d -->
*/

/*!
\defgroup a3d_cartesiantransfo3d Cartesian Transformation 
\ingroup a3d_misc_trsf
\brief Functions and structures for defining combinations of transformations (without the use of a matrix)

Entity type is \ref kA3DTypeMiscCartesianTransformation.

This entity describes combinations of transformations such as 
relocation to a new 3D Cartesian coordinate system, scaling, and rotation.
The \ref A3DMiscCartesianTransformationData structure provides parameters for the transformation.
The behaviour mask specified by the \ref A3DMiscCartesianTransformationData::m_ucBehaviour member  
specifies the transformations that apply. 
Those transformations must be consistent with the actual data provided in other fields as described here:

\li If the \c m_sOrigin member is null vector, translation is disabled.
\li If the \c m_sXVector member is (1,0,0) and \c m_sYVector member is (0,1,0), rotation is disabled.
\li If the \c m_sScale member is (1,1,1), scaling is disabled.
\li If the \c m_sXVector and \c m_sYVector members are not perpendicular or if they are not unit vectors, 
	the data is invalid.

\par Sample code
\include CartesianTransformation3d.cpp

\version 2.3
\warning
Some particular formats do not support Cartesian transformations directly, but define general 
ones instead. When possible, the associated readers try to make cartesian tranformations out 
of them, setting this Behaviour flag. In all cases, except for Mirror, direct use of 
transformation members is valid, where behavior is just informational.
*/

/*!
\brief Structure for defining an \ref A3DMiscCartesianTransformation entity
\ingroup a3d_cartesiantransfo3d
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DVector3dData	m_sOrigin;		/*!< 3D point - Center of axis system. */
	A3DVector3dData	m_sXVector;		/*!< 3D point - X axis of axis system. */
	A3DVector3dData	m_sYVector;		/*!< 3D point - Y axis of axis system. */
	A3DVector3dData	m_sScale;		/*!< 3D point - Scale of axis system. */
	A3DUns8			m_ucBehaviour;	/*!< Behavior of \ref A3DMiscCartesianTransformationData. \sa a3d_transformationbit */
} A3DMiscCartesianTransformationData;

/*!
\brief Populates the \ref A3DMiscCartesianTransformationData structure
\ingroup a3d_cartesiantransfo3d
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE\n
\return \ref A3D_INVALID_DATA_STRUCT_NULL\n
\return \ref A3D_INVALID_ENTITY_NULL\n
\return \ref A3D_INVALID_ENTITY_TYPE\n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DMiscCartesianTransformationGet,(	const A3DMiscCartesianTransformation* pCartesianTransformation3d,
																			A3DMiscCartesianTransformationData* pData));

/*!
\brief Creates an \ref A3DMiscCartesianTransformation from an \ref A3DMiscCartesianTransformationData structure. 
\ingroup a3d_cartesiantransfo3d

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_POINTSET_BADSIZE \n	
\return \ref A3D_TRANSFORMATION3D_INCONSISTENT \n	
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscCartesianTransformationCreate,(	const A3DMiscCartesianTransformationData* pData,
																				A3DMiscCartesianTransformation** ppCartesianTransformation3d));
/*!
\defgroup a3d_transformationbit Cartesian Transformation Types
\ingroup a3d_cartesiantransfo3d
\brief Bitmasks that can be ANDed together to specify the transformation behavior 
\version 2.0

The bitmasks specify the transformations specified by an \ref A3DMiscCartesianTransformation.
To specify multiple transformation behaviors, AND together the bitmasks for each transformation type.
\note Specifying the \ref kA3DTransformationIdentity flag precludes any other types of transformations.
That is, if you create a transformation value that ANDs \ref kA3DTransformationIdentity and \ref kA3DTransformationRotate,
only the identity transformation is applied.

@{
*/
#define kA3DTransformationIdentity			0x00 /*!< Identity transformation. */
#define kA3DTransformationTranslate			0x01 /*!< Translate transformation */
#define kA3DTransformationRotate			0x02 /*!< Rotate transformation. */
#define kA3DTransformationMirror			0x04 /*!< Mirror transformation. */
#define kA3DTransformationScale				0x08 /*!< Scale transformation. */
#define kA3DTransformationNonUniformScale	0x10 /*!< Non-uniform scale transformation. */
/*!
@} <!-- end of module a3d_transformationbit -->
*/

#endif	/*	__A3D_TRSF__ */

#ifndef __A3D_ASM_ENTITY_REFERENCE__
/*!
\defgroup a3d_entity_reference Entity Reference
\ingroup a3d_misc_module
\brief Creates and accesses references to other PRC entities
\version 2.0

Entity type is \ref kA3DTypeMiscEntityReference.

An \ref A3DMiscEntityReference references an entity containing 
structure data, representation items, topology data, markup data or scene display data. 
All of these entities can be referenced from other entities. 
For example, the \ref A3DAsmProductOccurrence entity (\ref a3d_productoccurrence) can include an \ref A3DMiscEntityReference entity
that references another product occurrence. 
In another example, an \ref A3DAsmFilter entity (\ref a3d_filter) can include an entity filter 
for which multiple \ref A3DMiscEntityReference entities
specify the entities to be inclusively or exclusively filtered. 

The \ref A3DMiscEntityReference can supply modifiers that affect the referenced entity nominal definition.
All entity references can include a coordinate system, which is applied to the referenced item.
Topology entity references can also include global index items, such as color and texture.

To create references for non-topological entities listed in \ref a3d_eligibleforreference, perform these steps:
<ol>
	<li>Create an \ref A3DMiscEntityReferenceData structure that references the non-topological entity.</li>
	<li>Set the coordinate system transformation in the \ref A3DMiscEntityReferenceData structure as needed. </li>
	<li>Create an \ref A3DMiscEntityReference that references the \ref A3DMiscEntityReferenceData structure.</li>
</ol>

To create references for topological entities listed in \ref a3d_eligiblefortopologicalreference, perform these steps:
<ol>
	<li>Create an \ref A3DMiscReferenceOnTopologyData structure that references the topological entity.</li>
	<li>Set global index items in the \ref A3DMiscReferenceOnTopologyData structure as needed. </li>
	<li>Create an \ref A3DMiscReferenceOnTopology entity, providing the \ref A3DMiscReferenceOnTopologyData structure.</li>
	<li>Create an \ref A3DMiscEntityReferenceData structure that references the \ref A3DMiscReferenceOnTopology entity.</li>
	<li>Set the coordinate system transformation in the \ref A3DMiscEntityReferenceData structure as needed. </li>
	<li>Create an \ref A3DMiscEntityReference that references the \ref A3DMiscEntityReferenceData structure.</li>
</ol>

See the referenceable types in the modules \ref a3d_eligibleforreference
and \ref a3d_eligiblefortopologicalreference.

*/

/*!
\ingroup a3d_entity_reference
\brief Structure that identifies the referenced entity and that provides a new coordinate system
\version 2.0

If the type of the referenced entity is topology, 
\ref m_pEntity is an \ref A3DMiscReferenceOnTopology object of type \ref kA3DTypeMiscReferenceOnTopology, 
which contains the reference to the topological body. 
In addition to containing a reference to the topology entity,
the \ref A3DMiscReferenceOnTopology entity defines the topology item type
and includes indexes to items in the global settings, such as color and layer.

If the type of the referenced entity is \e not topology, 
the \ref m_pEntity member can directly reference an object that has one of the types 
defined in  \ref a3d_eligibleforreference. (\ref m_pEntity can also be NULL.)<BR>
To get the type of the entity referenced by the \ref m_pEntity member, use the \ref A3DEntityGetType function.<BR>

*/
typedef struct  
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DEntity* m_pEntity;						/*!< Referenced entity. It can be NULL. */
	A3DRiCoordinateSystem* m_pCoordinateSystem;	/*!< Optional location. */
} A3DMiscEntityReferenceData;

/*!
\brief Populates the \ref A3DMiscEntityReferenceData structure
\ingroup a3d_entity_reference
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscEntityReferenceGet,(	const A3DMiscEntityReference* pEntityReference,
																A3DMiscEntityReferenceData* pData));

/*!
\brief Creates an \ref A3DMiscEntityReference from an \ref A3DMiscEntityReferenceData structure
\ingroup a3d_entity_reference
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_ENTITYREFERENCE_INCONSISTENT_REFERENCE \n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DMiscEntityReferenceCreate,(	const A3DMiscEntityReferenceData* pData,
																	A3DMiscEntityReference** ppEntityReference));

/*!
\brief Function to set the entity reference from \ref A3DMiscEntityReferenceData structure in a previously created object
\ingroup a3d_entity_reference
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_ENTITYREFERENCE_INCONSISTENT_REFERENCE \n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DMiscEntityReferenceSet,(	A3DMiscEntityReference* pEntityReference,
																const A3DMiscEntityReferenceData* pData));

#endif /* __A3D_ASM_ENTITY_REFERENCE__ */

#ifndef __A3D_ASM_REFERENCE_ON_TOPOLOGY__
/*!
\defgroup a3d_reference_on_topo Reference on Topology
\ingroup a3d_entity_reference
\brief Creates and accesses entities that reference topology entities 
	and that specify globally-defined attributes
\version 2.0

Entity type is \ref kA3DTypeMiscReferenceOnTopology.


Reference topology entity are retrieved by indexes on father elements.

For a \ref A3DTopoConnex, it needs:
\li the \ref A3DTopoConnex index on the current \ref A3DTopoBrepData.

For a \ref A3DTopoShell, it needs:
\li the \ref A3DTopoShell index on the current \ref A3DTopoBrepData. It is a global index to the "BrepData. In the case of several \ref A3DTopoConnex, it must take into account the number of shells present in the preceding \ref A3DTopoConnex.
\code
	A3DUns32 uiShellIndex = 0;
	for all pConnex on A3DTopoBrepData
	{
		for all pShell on pConnex
		{
			if pShell is wanted
				return uiShellIndex;
			uiShellIndex++;
		}
	}
\endcode

For a \ref A3DTopoFace, it needs:
\li the \ref A3DTopoFace index on the current \ref A3DTopoBrepData. It is a global index to the "BrepData. In the case of several \ref A3DTopoConnex, it must take into account the number of faces present in the preceding \ref A3DTopoConnex.
\code
	A3DUns32 uiFaceIndex = 0;
	for all pConnex on A3DTopoBrepData
	{
		for all pShell on pConnex
		{
			for all pFace on pShell
			{
				if pFace is wanted
					return uiFaceIndex;
				uiFaceIndex++;
			}
		}
	}
\endcode

For a \ref A3DTopoEdge or \ref A3DTopoCoEdge, it needs:
\li the \ref A3DTopoFace index on the current \ref A3DTopoBrepData (see index need for \ref A3DTopoFace reference)..
\li the \ref A3DTopoLoop index on the current \ref A3DTopoFace.
\li the \ref A3DTopoCoEdge index on the current \ref A3DTopoLoop.

For a \ref A3DTopoVertex, it needs:
\li the \ref A3DTopoFace index on the current \ref A3DTopoBrepData (see index need for \ref A3DTopoFace reference).
\li the \ref A3DTopoLoop index on the current \ref A3DTopoFace.
\li the \ref A3DTopoEdge index on the current \ref A3DTopoLoop.
\li the \ref A3DTopoVertex index on the current \ref A3DTopoEdge. Is set to 0 for the start vertex, and 1 for the end vertex.

*/

/*!
\ingroup a3d_reference_on_topo
\brief Structure that identifies the referenced topology entity and that specifies globally-defined attributes
\version 2.0

\ref m_puiAdditionalIndexes contains index on different topology elements (see \ref a3d_reference_on_topo for explanation)

For reference on \ref A3DTopoEdge or A3DTopoCoEdge, \ref m_uiSize must be set to 3 and
\li \ref m_puiAdditionalIndexes[0] is the \ref A3DTopoFace index in the \ref A3DTopoBrepData
\li \ref m_puiAdditionalIndexes[1] is the \ref A3DTopoLoop index in the \ref A3DTopoFace
\li \ref m_puiAdditionalIndexes[2] is the \ref A3DTopoEdge index in the \ref A3DTopoLoop


For reference on \ref A3DTopoVertex, \ref m_uiSize must be set to 4 and
\li \ref m_puiAdditionalIndexes[0] is the \ref A3DTopoFace index in the \ref A3DTopoBrepData
\li \ref m_puiAdditionalIndexes[1] is the \ref A3DTopoLoop index in the \ref A3DTopoFace
\li \ref m_puiAdditionalIndexes[2] is the \ref A3DTopoEdge index in the \ref A3DTopoLoop
\li \ref m_puiAdditionalIndexes[3] is the \ref A3DTopoVertex index in the \ref A3DTopoEdge.

*/
typedef struct  
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DEEntityType m_eTopoItemType;		/*!< Restricted to the type listed in in \ref a3d_eligiblefortopologicalreference. */
	A3DTopoBrepData* m_pBrepData;		/*!< Body. Can be NULL. */
	A3DUns32 m_uiSize;					/*!< Size of next array. */
	A3DUns32* m_puiAdditionalIndexes;	/*!< Indices to retrieve the topological entity. */
} A3DMiscReferenceOnTopologyData;

/*!
\brief Populates the \ref A3DMiscReferenceOnTopologyData structure
\ingroup a3d_reference_on_topo
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscReferenceOnTopologyGet,(const A3DMiscReferenceOnTopology* pReferenceOnTopoItem,
																	A3DMiscReferenceOnTopologyData* pData));

/*!
\brief Creates an \ref A3DMiscReferenceOnTopology from an \ref A3DMiscReferenceOnTopologyData structure
\ingroup a3d_reference_on_topo
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_ENTITYREFERENCE_INCONSISTENT_REFERENCE \n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DMiscReferenceOnTopologyCreate,(const A3DMiscReferenceOnTopologyData* pData,
																		A3DMiscReferenceOnTopology** ppReferenceOnTopoItem));

#endif /* __A3D_ASM_REFERENCE_ON_TOPOLOGY__ */

/*!
\defgroup a3d_eligibleforreference Referenceable Non-Topological Entities
\ingroup a3d_entity_reference
\brief Listing of the non-topological entities that can be referenced from the \ref A3DMiscEntityReference

\li \ref kA3DTypeMiscEntityReference
\li \ref kA3DTypeMiscMarkupLinkedItem

\li \ref kA3DTypeRiBrepModel
\li \ref kA3DTypeRiCurve
\li \ref kA3DTypeRiDirection
\li \ref kA3DTypeRiPlane
\li \ref kA3DTypeRiPointSet
\li \ref kA3DTypeRiPolyBrepModel
\li \ref kA3DTypeRiPolyWire
\li \ref kA3DTypeRiSet
\li \ref kA3DTypeRiCoordinateSystem

\li \ref kA3DTypeAsmProductOccurrence
\li \ref kA3DTypeAsmPartDefinition
\li \ref kA3DTypeAsmFilter

\li \ref kA3DTypeMkpView
\li \ref kA3DTypeMkpMarkup
\li \ref kA3DTypeMkpLeader
\li \ref kA3DTypeMkpAnnotationItem
\li \ref kA3DTypeMkpAnnotationSet
\li \ref kA3DTypeMkpAnnotationReference

\li \ref kA3DTypeGraphStyle
\li \ref kA3DTypeGraphMaterial
\li \ref kA3DTypeGraphTextureApplication
\li \ref kA3DTypeGraphTextureDefinition
\li \ref kA3DTypeGraphTextureTransformation
\li \ref kA3DTypeGraphLinePattern
\li \ref kA3DTypeGraphDottingPattern
\li \ref kA3DTypeGraphHatchingPattern
\li \ref kA3DTypeGraphSolidPattern
\li \ref kA3DTypeGraphVPicturePattern
\li \ref kA3DTypeGraphCamera
\li \ref kA3DTypeGraphAmbientLight
\li \ref kA3DTypeGraphPointLight
\li \ref kA3DTypeGraphDirectionalLight
\li \ref kA3DTypeGraphSpotLight
\li \ref kA3DTypeGraphCamera
*/

/*!
\defgroup a3d_eligiblefortopologicalreference Referenceable Topological Entities
\ingroup a3d_entity_reference
\brief Listing of the topological entities that can be referenced from the \ref A3DMiscReferenceOnTopology entity

\li \ref kA3DTypeTopoMultipleVertex
\li \ref kA3DTypeTopoUniqueVertex
\li \ref kA3DTypeTopoWireEdge
\li \ref kA3DTypeTopoEdge
\li \ref kA3DTypeTopoLoop
\li \ref kA3DTypeTopoFace
\li \ref kA3DTypeTopoShell
\li \ref kA3DTypeTopoConnex

Currently, not all topological entities are supported. 
	See \ref a3d_reference_on_topo for limitations.
*/

#ifndef __A3D_ASM_REFERENCE_ON_CYS_ITEM__
/*!
\defgroup a3d_reference_on_csys_sub_cmpnt Reference on coordinate system subcomponent
\ingroup a3d_entity_reference
\version 6.0
\brief Creates and accesses entities that reference coordinate system subcomponent

Entity type is \ref kA3DTypeMiscReferenceOnCsysItem.

Reference on coordinate system subcomponent are retrieved by the index.
m_uiIndex = 1 plane (x,y)
m_uiIndex = 2 plane (y,z)
m_uiIndex = 3 plane (x,z)
m_uiIndex = 4 axis x
m_uiIndex = 5 axis y
m_uiIndex = 6 axis z

*/

/*!
\struct A3DMiscReferenceOnCsysItemData
\brief Reference on coordinate system item
\ingroup a3d_reference_on_csys_sub_cmpnt
\version 6.0
*/
typedef struct  
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DRiCoordinateSystem* m_pCoordinateSystem;		/*!< Coordinate system */
	A3DUns16 m_uiIndex;								/*!< Index defining sub-component. */
} A3DMiscReferenceOnCsysItemData;


/*!
\brief Populates the \ref A3DMiscReferenceOnCsysItemData structure
\ingroup a3d_reference_on_csys_sub_cmpnt
\version 6.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscReferenceOnCsysItemGet,(const A3DMiscReferenceOnCsysItem* pReferenceOnCSYSItem,
		 A3DMiscReferenceOnCsysItemData* pData));

/*!
\brief Creates an \ref A3DMiscReferenceOnCsysItem from an \ref A3DMiscReferenceOnCsysItemData structure
\ingroup a3d_reference_on_csys_sub_cmpnt
\version 6.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_ENTITYREFERENCE_INCONSISTENT_REFERENCE \n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DMiscReferenceOnCsysItemCreate,(const A3DMiscReferenceOnCsysItemData* pData,
		 A3DMiscReferenceOnCsysItem** ppReferenceOnCSYSItem));

#endif //__A3D_ASM_REFERENCE_ON_TOPOLOGY__
#ifndef __A3D_UTF8UNICODE__

/*!
\defgroup a3d_UTF8_utilities UTF-8 Conversion Utilities
\ingroup a3d_misc_module
\brief Functions for converting between UTF-8 and UTF-16 strings on Windows.
@{
*/

/*!
\brief Converts UTF-8 encoded characters to UTF-16 strings on Windows.
\version 2.0

This function returns a UTF-16 string on Windows.

You must cast the string to a wide char pointer (\c wchar_t*) depending on the target computer's characteristics.

\warning On Linux, this API simply copies the input \c A3DUTF8Char* string into the output \c A3DUTF8Char* string.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
*/
A3D_API (A3DStatus, A3DMiscUTF8ToUnicode,(const A3DUTF8Char* pcInputBuffer,
														A3DUTF8Char acOutputBuffer[]));

/*!
\brief Converts UTF-16 strings to an array UTF-8 encoded characters on Windows.
\version 2.0

This function returns an array of UTF-8 encoded characters. 

The input buffer is cast and interpreted as a Unicode string (\c wchar_t*). 

\warning On Linux, this API simply copies the input \c A3DUTF8Char* string into the output \c A3DUTF8Char* string.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
*/
A3D_API (A3DStatus, A3DMiscUnicodeToUTF8,(const A3DUTF8Char* pcInputBuffer,
														A3DUTF8Char acOutputBuffer[]));

/*!
\brief Converts a UTF-8 string to a UTF-16 string on Windows.
\version 7.0

This function returns a UTF-16 string. 

\warning On Linux, this API simply returns A3D_ERROR.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
*/
A3D_API (A3DStatus, A3DMiscUTF8ToUTF16,(const A3DUTF8Char* pcInputBuffer,
														A3DUniChar acOutputBuffer[]));

/*!
\brief Converts a UTF-16 string to a UTF-8 string on Windows.
\version 7.0

This function returns a UTF-8 string.

\warning On Linux, this API simply returns A3D_ERROR.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
*/
A3D_API (A3DStatus, A3DMiscUTF16ToUTF8,(const A3DUniChar* pcInputBuffer,
														A3DUTF8Char acOutputBuffer[]));
/*!
@} <!-- end of a3d_UTF8_utilities -->
*/

#endif /* __A3D_UTF8UNICODE__ */
 /*!
 \defgroup a3d_error_debug_utilities Debug Utilities
\ingroup a3d_misc_module
\brief Functions to aid debugging.
@{
 */

/*!
\brief Returns the text description of an error code.

This text is stored in a global array used also by A3DMiscGetEntityTypeMsg. 
This function returns a pointer to the global array and therefore it must not be desallocated.
Each time the function is called, the global array is updated.
For version 2.1, this method declaration was changed to 
use the same convention applied to all other \COMPONENT_A3D_API declarations.
More specifically, the declaration was changed 
to <code>A3D_API (A3DUTF8Char*, A3DMiscGetErrorMsg,(A3DInt32));</code>. 
You will not be able to see this change because this reference 
simplifies all declarations to the more readable format shown in the declaration frame.
\version 2.0
*/

A3D_API (A3DUTF8Char*, A3DMiscGetErrorMsg,(A3DStatus));

/*!
\brief Returns the name of the entity type.

This text is stored in a global array used also by A3DMiscGetErrorMsg. 
This function returns a pointer to the global array and therefore it must not be desallocated.
Each time the function is called, the global array is updated.
For version 2.1, this method declaration was changed to 
use the same convention applied to all other \COMPONENT_A3D_API declarations.
For more information, see the description for \ref A3DMiscGetErrorMsg.

\version 2.0
*/
A3D_API (A3DUTF8Char*, A3DMiscGetEntityTypeMsg,(A3DEEntityType eType));
/*!
@} <!-- end of a3d_error_msg_utilities module -->
*/

/*!
\struct A3DMiscPhysicMaterialData
\brief Physical properties. contains a union of the differents . 
\ingroup a3d_misc_module
\version 9.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dDensity;		/*!< Density in kg/m3. Equal to -1.0 if not set */
} A3DMiscPhysicMaterialData;


/*!
\struct A3DMiscMaterialFiberData
\brief Fiber physical properties.
\ingroup a3d_misc_module
\version 9.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dYoungModulus_X;				/*! Longitudinal Young Modulus */  
	A3DDouble m_dYoungModulus_Y;                /*! Transverse Young Modulus */    
	A3DDouble m_dPoissonRatio_XY;               /*! Poisson Ratio in XY plane */    
	A3DDouble m_dShearModulus_XY;               /*! Shear Modulus in XY plane */   
	A3DDouble m_dShearModulus_YZ;               /*! Shear Modulus in XZ plane */   
	A3DDouble m_dThermalExpansion_X;            /*! Longitudinal Thermal Expansion */      
	A3DDouble m_dThermalExpansion_Y;            /*! Transverse Thermal Expansion */        
	A3DDouble m_dTensileStressLimit_X;          /*! Transverse Tensile Stress Limit */            
	A3DDouble m_dCompressiveStressLimit_X;      /*! Transverse Compressive Stress Limit */        
	A3DDouble m_dTensileStressLimit_Y;          /*! Transverse Tensile Strain Limit */
	A3DDouble m_dCompressiveStressLimit_Y;      /*! Transverse Compressive Strain Limit */
	A3DDouble m_dShearStressLimit_XY;           /*! Shear Stress Limit in XY plane */
	A3DDouble m_dShearStressLimit_YZ;           /*! Shear Stress Limit in XZ plane */

} A3DMiscMaterialFiberData;

/*!
\struct A3DMiscMaterialHoneyCombData
\brief HoneyComb physical properties.
\ingroup a3d_misc_module
\version 9.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dYoungModulus;					/*! Normal Young Modulus */
	A3DDouble m_dShearModulus_XZ;				/*! Shear Modulus in XY plane */      
	A3DDouble m_dShearModulus_YZ;				/*! Shear Modulus in XZ plane */      
	A3DDouble m_dShearStressLimit_XZ;			/*! Shear Stress Limit in XY plane*/  
	A3DDouble m_dShearStressLimit_YZ;			/*! Shear Stress Limit in XZ plane*/  
	A3DDouble m_dThermalExpansion;				/*! Normal Thermal Expansion */

} A3DMiscMaterialHoneyCombData;

/*!
\struct A3DMiscMaterialIsotropicData
\brief Isotropic physical properties.
\ingroup a3d_misc_module
\version 9.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dYoungModulus;                  /*! Young Modulus */
	A3DDouble m_dPoissonRatio;                  /*! Poisson Ratio */
	A3DDouble m_dShearModulus;                  /*! Shear Modulus */
	A3DDouble m_dThermalExpansion;              /*! Thermal Expansion */

} A3DMiscMaterialIsotropicData;

/*!
\struct A3DMiscMaterialOrthotropic2DData
\brief Orthotropic2D physical properties.
\ingroup a3d_misc_module
\version 9.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dYoungModulus_X;                /*! Longitudinal Young Modulus */
	A3DDouble m_dYoungModulus_Y;                /*! Transverse Young Modulus */
	A3DDouble m_dPoissonRatio_XY;               /*! Poisson Ratio in XY plane*/
	A3DDouble m_dShearModulus_XY;               /*! Shear Modulus in XY plane */
	A3DDouble m_dShearModulus_XZ;               /*! Shear Modulus in XZ plane */
	A3DDouble m_dShearModulus_YZ;               /*! Shear Modulus in YZ plane */
	A3DDouble m_dTensileStressLimit_X;          /*! Longitudinal Tensile Stress Limit */
	A3DDouble m_dCompressiveStressLimit_X;      /*! Longitudinal Compressive Stress Limit */
	A3DDouble m_dTensileStressLimit_Y;          /*! Transverse Tensile Stress Limit */
	A3DDouble m_dCompressiveStressLimit_Y;      /*! Transverse Compressive Stress Limit */
	A3DDouble m_dThermalExpansion_X;            /*! Longitudinal Thermal Expansion */
	A3DDouble m_dThermalExpansion_Y;            /*! Transverse Thermal Expansion */
	A3DDouble m_dTensileStrainLimit_X;          /*! Longitudinal Tensile Strain Limit */
	A3DDouble m_dCompressiveStrainLimit_X;      /*! Longitudinal Compressive Strain Limit */
	A3DDouble m_dTensileStrainLimit_Y;          /*! Transverse Tensile Strain Limit */
	A3DDouble m_dCompressiveStrainLimit_Y;      /*! Transverse Compressive Strain Limit */
	A3DDouble m_dShearStressLimit_XY;           /*! Shear Stress Limit in XY plane*/

} A3DMiscMaterialOrthotropic2DData;

/*!
\struct A3DMiscMaterialOrthotropic3DData
\brief Orthotropic3D physical properties.
\ingroup a3d_misc_module
\version 9.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dYoungModulus_X;				/*! Longitudinal Young Modulus */      
	A3DDouble m_dYoungModulus_Y;				/*! Transverse Young Modulus */        
	A3DDouble m_dYoungModulus_Z;				/*! Normal Young Modulus */
	A3DDouble m_dPoissonRatio_XY;				/*! Poisson Ratio in XY plane */
	A3DDouble m_dPoissonRatio_XZ;				/*! Poisson Ratio in XZ plane */
	A3DDouble m_dPoissonRatio_YZ;				/*! Poisson Ratio in YZ plane */
	A3DDouble m_dShearModulus_XY;				/*! Shear Modulus in XY plane */
	A3DDouble m_dShearModulus_XZ;				/*! Shear Modulus in XZ plane */
	A3DDouble m_dShearModulus_YZ;				/*! Shear Modulus in YZ plane */
	A3DDouble m_dThermalExpansion_X;			/*! Longitudinal Thermal Expansion */
	A3DDouble m_dThermalExpansion_Y;			/*! Transverse Thermal Expansion */
	A3DDouble m_dThermalExpansion_Z;			/*! Normal Thermal Expansion */
	A3DDouble m_dTensileStressLimit_X;			/*! Transverse Tensile Stress Limit */                    
	A3DDouble m_dCompressiveStressLimit_X;		/*! Transverse Compressive Stress Limit */                
	A3DDouble m_dTensileStressLimit_Y;			/*! Transverse Tensile Strain Limit */                    
	A3DDouble m_dCompressiveStressLimit_Y;		/*! Transverse Compressive Strain Limit */                
	A3DDouble m_dShearStressLimit_XY;			/*! Longitudinal Shear Stress Limit */
	A3DDouble m_dShearStressLimit_XZ;			/*! Transverse Shear Stress Limit */
	A3DDouble m_dShearStressLimit_YZ;			/*! Normal Shear Stress Limit */

} A3DMiscMaterialOrthotropic3DData;

/*!
\struct A3DMiscMaterialAnisotropicData
\brief Anisotropic physical properties.
\ingroup a3d_misc_module
\version 9.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dShearModulus_XX;				/*! Longitudinal Shear Modulus */
	A3DDouble m_dShearModulus_XY;				/*! Shear Modulus in XY plane */
	A3DDouble m_dShearModulus_XZ;				/*! Shear Modulus in XZ plane */
	A3DDouble m_dShearModulus_YY;				/*! Transverse Shear Modulus */
	A3DDouble m_dShearModulus_YZ;				/*! Shear Modulus in YZ plane */
	A3DDouble m_dShearModulus_ZZ;				/*! Normal Shear Modulus */
	A3DDouble m_dThermalExpansion_X;			/*! Longitudinal Thermal Expansion */
	A3DDouble m_dThermalExpansion_Y;			/*! Transverse Thermal Expansion */
	A3DDouble m_dThermalExpansion_Z;			/*! Normal Thermal Expansion */
	A3DDouble m_dTensileStressLimit;			/*! Tensile Stress Limit */
	A3DDouble m_dCompressiveStressLimit;		/*! Compressive Stress Limit */
	A3DDouble m_dShearStressLimit;				/*! Shear Stress Limit */

} A3DMiscMaterialAnisotropicData;

/*!
\enum A3DMaterialPhysicType
\brief Material physical type properties
\ingroup a3d_misc_module
\version 9.0
*/
enum A3DMaterialPhysicType
{
	A3DPhysicType_None,				/*!< If no material type set */
	A3DPhysicType_Fiber,            /*!< Fiber Type */
	A3DPhysicType_HoneyComb,        /*!< Honey Comb Type */
	A3DPhysicType_Isotropic,        /*!< Isotropic Type */
	A3DPhysicType_Orthotropic2D,    /*!< Orthotropic Type */
	A3DPhysicType_Orthotropic3D,    /*!< Orthotropic 3D Type */
	A3DPhysicType_Anisotropic,      /*!< Anisotropic Type */
};

/*!
\struct A3DMiscMaterialPropertiesData
\brief Material properties, like density
\ingroup a3d_misc_module
\version 8.2
*/
typedef struct
{
	A3DUns16		m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble		m_dDensity;			/*!< Density in kg/m3. Equal to -1.0 if not set */

	A3DUTF8Char*	m_pcMaterialName;	/*!< Name of the material. \version 9.0 */
	A3DMaterialPhysicType m_ePhysicType; /*!< Physical Type: use for extract properties from the union of physical properties.	\version 9.0 */
	union
	{
		A3DMiscMaterialFiberData		    m_sFiber;			/*!< Fiber Material properties			\version 9.0 */
		A3DMiscMaterialHoneyCombData		m_sHoneyComb;       /*!< Honey Comb Material properties		\version 9.0 */
		A3DMiscMaterialIsotropicData		m_sIsotropic;       /*!< Isotropic Material properties		\version 9.0 */
		A3DMiscMaterialOrthotropic2DData	m_sOrthotropic2D;	/*!< Orthotropic Material properties	\version 9.0 */
		A3DMiscMaterialOrthotropic3DData	m_sOrthotropic3D;	/*!< Orthotropic 3D Material properties \version 9.0 */
		A3DMiscMaterialAnisotropicData		m_sAnisotropic;     /*!< Anisotropic Material properties	\version 9.0 */
	};

} A3DMiscMaterialPropertiesData;

/*!
\brief Get density in kg/m3. Equal to -1.0 if not set
\ Can call it on product occurences, part, and representation item
\ingroup a3d_misc_module
\version 8.2
*/
A3D_API(A3DStatus, A3DMiscGetMaterialProperties, (const A3DEntity* pEntity, A3DMiscMaterialPropertiesData *pMaterialPropertiesData));



/*!
\brief Get the Axis Aligned Bounding Box (AABB) of the A3DEntity
\ Can call it on product occurences, part, and representation item
\ If there is no Bounding Box set, will set 0,0,0 triplets to min and max coordinates.
\ingroup a3d_misc_module
\version 8.2
*/
A3D_API(A3DStatus, A3DMiscGetBoundingBox, (const A3DEntity* pEntity, A3DBoundingBoxData *pAABB));



#endif	/*	__A3DPRCMISC_H__ */
