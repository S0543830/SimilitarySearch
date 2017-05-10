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
\brief      Header file for the markup module.
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMARKUP_H__
#define __A3DPRCMARKUP_H__

#ifndef __A3DPRCTESSELLATION_H__
#error A3DSDKTessellation.h must be included before current file
#endif

/*!
\defgroup a3d_markup_module Markup Module
\ingroup a3d_entitiesdata_module
Entity type is \ref kA3DTypeMkpMarkup.

There may be a tessellation in the markup and in each leader.
The following sample code shows how to retrieve the tessellation.
\par Sample code
\include Markup.cpp
\sa a3d_tessmarkup
*/

/*!
\defgroup a3d_markupdefinition_module Markup definition
\ingroup a3d_markup_module
\version 4.0
*/
#ifndef __A3D_MARKUPLEADER__
/*!
\defgroup a3d_markupleader Markup Leader
\ingroup a3d_markup_module
Entity type is \ref kA3DTypeMkpLeader.

There may a tessellation in the leader.
Use the sample code in \ref a3d_markup_module to retrieve the tessellation.
\sa a3d_tessmarkup
*/

/*!
\brief Markup Leader structure
\ingroup a3d_markupleader
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMiscMarkupLinkedItem* m_pLinkedItem;		/*!< Represents the link with an entity. It must be one of the markup array of leaders (see A3DMkpMarkupData). It is not mandatory. */
	A3DTessMarkup* m_pTessellation;				/*!< Tessellation of leader. May be NULL. */
} A3DMkpLeaderData;

/*!
\brief Populates the \ref A3DMkpLeaderData structure
\ingroup a3d_markupleader
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpLeaderGet,(	const A3DMkpLeader* pLeader,
													A3DMkpLeaderData* pData));

/*!
\brief Creates an \ref A3DMkpLeader from an \ref A3DMkpLeaderData structure
\ingroup a3d_markupleader
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpLeaderCreate,(const A3DMkpLeaderData* pData,
													A3DMkpLeader** ppLeader));

#endif	/*	__A3D_MARKUPLEADER__ */


/*!
\defgroup a3d_annotationentity Annotations Entity
\ingroup a3d_markup_module
An annotation entity can be one of the following types:
\li \ref A3DMkpAnnotationItem
\li \ref A3DMkpAnnotationSet
\li \ref A3DMkpAnnotationReference
*/

#ifndef __A3D_ANNOTATIONITEM__
/*!
\defgroup a3d_annotationitem Annotation Item
\brief Usage of a markup
\ingroup a3d_annotationentity

Entity type is \ref kA3DTypeMkpAnnotationItem.

An annotation item denotes the usage of a single markup.
It enables the sharing of markups. For instance, a markup of type "datum" can be re-used in several annotation sets
to denote different tolerances.
*/

/*!
\brief Annotation Item structure
\ingroup a3d_annotationitem
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMkpMarkup* m_pMarkup;		/*!< The markup held by the annotation item. */
} A3DMkpAnnotationItemData;

/*!
\brief Populates the \ref A3DMkpAnnotationItemData structure
\ingroup a3d_annotationitem
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpAnnotationItemGet,(const A3DMkpAnnotationItem* pAnnotation,
															A3DMkpAnnotationItemData* pData));

/*!
\brief Creates an \ref A3DMkpAnnotationItem from an \ref A3DMkpAnnotationItemData structure
\ingroup a3d_annotationitem
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpAnnotationItemCreate,(const A3DMkpAnnotationItemData* pData,
																A3DMkpAnnotationItem** ppAnnotation));

#endif	/*	__A3D_ANNOTATIONITEM__ */

#ifndef __A3D_ANNOTATIONSET__
/*!
\defgroup a3d_annotationset Annotation Set
\brief Group of annotation entities
\ingroup a3d_annotationentity
Entity type is \ref kA3DTypeMkpAnnotationSet.

An annotation set is a group of annotation items or subsets.
For example, a tolerance defined by a datum and a feature control frame are described by an annotation set 
with two annotation items, where the items point respectively 
to a markup of type "datum" and a markup of type "feature control frame".

*/

/*!
\brief Annotation Set structure
\ingroup a3d_annotationset
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiAnnotationsSize;				/*!< Size of next array. */
	A3DMkpAnnotationEntity** m_ppAnnotations;	/*!< Annotation entities stored under current annotation. */
} A3DMkpAnnotationSetData;

/*!
\brief Populates the \ref A3DMkpAnnotationSetData structure
\ingroup a3d_annotationset
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpAnnotationSetGet,(	const A3DMkpAnnotationSet* pAnnotation,
															A3DMkpAnnotationSetData* pData));

/*!
\brief Creates an \ref A3DMkpAnnotationSet from an \ref A3DMkpAnnotationSetData structure
\ingroup a3d_annotationset
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_ANNOTATIONSET_WITH_NULL_ELEMENT \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpAnnotationSetCreate,(	const A3DMkpAnnotationSetData* pData,
																A3DMkpAnnotationSet** ppAnnotation));

#endif	/*	__A3D_ANNOTATIONSET__ */

#ifndef __A3D_ANNOTATIONREFERENCE__
/*!
\defgroup a3d_annotationreference Annotation Reference
\brief Logical grouping of other annotations
\ingroup a3d_annotationentity
Entity type is \ref kA3DTypeMkpAnnotationReference.

An annotation reference stores explicit combinations of markup data with modifiers that can then be used
to define other annotations (feature control frame).

*/

/*!
\brief Annotation Reference structure
\ingroup a3d_annotationreference
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiLinkedItemsSize;				/*!< Number of \ref A3DMiscMarkupLinkedItem in next array. */
	A3DMiscMarkupLinkedItem** m_ppLinkedItems;	/*!< Array of \ref A3DMiscMarkupLinkedItem. */
} A3DMkpAnnotationReferenceData;

/*!
\brief Populates the \ref A3DMkpAnnotationReferenceData structure
\ingroup a3d_annotationreference
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpAnnotationReferenceGet,(	const A3DMkpAnnotationReference* pAnnotation,
																	A3DMkpAnnotationReferenceData* pData));

/*!
\brief Creates an \ref A3DMkpAnnotationReference from an \ref A3DMkpAnnotationReferenceData structure
\ingroup a3d_annotationreference
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpAnnotationReferenceCreate,(	const A3DMkpAnnotationReferenceData* pData,
																		A3DMkpAnnotationReference** ppAnnotation));

#endif	/*	__A3D_ANNOTATIONREFERENCE__ */

#ifndef __A3D_VIEW__
/*!
\defgroup a3d_annots_view View
\ingroup a3d_markup_module
Entity type is \ref kA3DTypeMkpView.

A view is either a grouping of markups or a particular representation of the 3D scene, depending on the 
value of the \ref A3DMkpViewData::m_bIsAnnotationView member. 
If \ref A3DMkpViewData::m_bIsAnnotationView is \c TRUE, 
the view contains only an array of annotation entities.
If it is \c FALSE, it can also redefine other view properties such scene display parameters, 
entity visibilities, and positions on representation items and markups

*/

/*!
\brief View structure
\ingroup a3d_annots_view
\version 2.0

The type of children must be \ref kA3DTypeMkpAnnotationSet and must point to existing annotation entities.
*/
typedef struct
{
	A3DUns16 m_usStructSize;									/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiAnnotationsSize;								/*!< Size of next array. */
	A3DMkpAnnotationEntity** m_ppAnnotations;					/*!< View children. */
	A3DSurfPlane* m_pPlane;										/*!< View plane. */
	A3DGraphSceneDisplayParameters* m_pSceneDisplayParameters;	/*!< Scene display parameters. Reserved for future use. */
	A3DBool m_bIsAnnotationView;								/*!< This view is used only to group markups. */
	A3DBool m_bIsDefaultView;									/*!< If true, the parameters of this view are used when loading the 3D scene. */
	A3DUns32 m_uiLinkedItemsSize;								/*!< Size of next array. */
	A3DMiscMarkupLinkedItem** m_ppLinkedItems;					/*!< Array of pointers to \ref A3DMiscMarkupLinkedItem entities, 
																	each of which redefine special display parameters for the view. */
	A3DUns32 m_uiDisplayFilterSize;								/*!< Size of next array. */
	A3DAsmFilter** m_ppDisplayFilters;							/*!< Filters for display settings. Several filters are possible, but only one filter is active at a time. */
} A3DMkpViewData;

/*!
\brief Populates the \ref A3DMkpViewData structure
\ingroup a3d_annots_view
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpViewGet,(	const A3DMkpView* pView,
												A3DMkpViewData* pData));

/*!
\brief Creates an \ref A3DMkpView from an \ref A3DMkpViewData structure
\ingroup a3d_annots_view
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpViewCreate,(	const A3DMkpViewData* pData,
													A3DMkpView** ppView));


/*!
\brief A3DMkpViewFlagsGet returns flags that tell what is handled by the view. In view, several components are defined or not; such as camera, annotations, cross-section and explosion.
The view flags let you know what components are set. Only component set can impact the current view.
For instance, dealing with cross-section , the behaviors are as follow:

<table border="1">
<tr><th colspan = "2">VIEW TO ACTIVATE</th><th rowspan="2" >Cross-section set in current state</th><th rowspan="2">Cross-section in Resulting view</th></tr>
<tr><th>Flag set</th><th>Cross-section set in view</th></tr>
<tr><td rowspan="4">YES</td><td>NO</td><td>NO</td><td>NO</td></tr>
<tr><td>NO</td><td>YES</td><td>NO</td></tr>
<tr><td>YES</td><td>NO</td><td>YES (view cross-section)</td></tr>
<tr><td>YES</td><td>YES</td><td>YES (view cross-section)</td></tr>
<tr><td rowspan="4">NO</td><td>NO</td><td>NO</td><td>NO</td></tr>
<tr><td>NO</td><td>YES</td><td>YES (current cross-section)</td></tr>
<tr><td>YES</td><td>NO</td><td>NO</td></tr>
<tr><td>YES</td><td>YES</td><td>YES (current cross-section)</td></tr>
</table>

It's the same method for all components, to change the camera, you need a view with a camera set, if it's not the case the current camera have to be kept...

\ingroup a3d_annots_view
\version 7.1
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpViewFlagsGet, ( const A3DMkpView* pView,
	bool& bIsCameraSet, bool& bIsPMIFilteringSet, bool& bIsGeomFilteringSet, bool& bIsCrosssectionSet, bool& bIsExplosionSet, bool& bIsCombineState));

#endif	/*	__A3D_VIEW__ */

#ifndef __A3D_MARKUPLINKEDITEM__
/*!
\defgroup a3d_markuplinkeditem Markup Linked Item
\ingroup a3d_markup_module
Entity type is \ref kA3DTypeMiscMarkupLinkedItem.

The linked item contains data that can be accessed using the \ref A3DMiscEntityReferenceGet function.
\sa a3d_entity_reference
*/

/*!
\brief Markup Linked Item structure
\ingroup a3d_markuplinkeditem
\version 2.0

The \ref m_bMarkupShowControl and \ref m_bMarkupDeleteControl members apply only to linked items in markups 
(\ref A3DMkpMarkupData).
Similarly, the \ref m_bLeaderShowControl and \ref m_bLeaderDeleteControl members apply only to linked items in leaders 
(\ref A3DMkpLeaderData).
*/
typedef struct
{
	A3DUns16 m_usStructSize;								/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bMarkupShowControl;							/*!< Show/hide markup follows pointed entity. */
	A3DBool m_bMarkupDeleteControl;							/*!< Delete markup follows pointed entity. */
	A3DBool m_bLeaderShowControl;							/*!< Show leader follows pointed entity. */
	A3DBool m_bLeaderDeleteControl;							/*!< Delete leader follows pointed entity. */
	A3DAsmProductOccurrence* m_pTargetProductOccurrence;	/*!< If non-null, this member references a remote product occurrence that contains the reference. */
	A3DEntity* m_pReference;								/*!< Pointer on the referenced entity. \version 2.2 */
} A3DMiscMarkupLinkedItemData;

/*!
\brief Populates the \ref A3DMiscMarkupLinkedItemData structure
\ingroup a3d_markuplinkeditem
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscMarkupLinkedItemGet,(const A3DMiscMarkupLinkedItem* pLinkedItem,
																A3DMiscMarkupLinkedItemData* pData));

/*!
\brief Creates an \ref A3DMiscMarkupLinkedItem from an \ref A3DMiscMarkupLinkedItemData structure
\ingroup a3d_markuplinkeditem
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscMarkupLinkedItemCreate,(const A3DMiscMarkupLinkedItemData* pData,
																	A3DMiscMarkupLinkedItem** ppLinkedItem));

#endif	/*	__A3D_MARKUPLINKEDITEM__ */

#ifndef __A3D_MARKUP__ 

/*!
\defgroup a3d_markup_enums Markup Types and Subtypes
\ingroup a3d_markup_module
\brief Enumerations for markup types and subtypes for use in the \ref A3DMkpMarkupData structure
@{
*/

/*!
\version 2.0

Markup type identifiers
*/
typedef enum
{
	kA3DMarkupTypeUnknown = 0,		/*!< Unknown value. */ 
	kA3DMarkupTypeText,				/*!< Plain text. */
	kA3DMarkupTypeDimension,		/*!< Dimension. */
	kA3DMarkupTypeArrow,			/*!< Arrow. */
	kA3DMarkupTypeBalloon,			/*!< Balloon. */
	kA3DMarkupTypeCircleCenter,		/*!< Center of circle. */
	kA3DMarkupTypeCoordinate,		/*!< Coordinate. */
	kA3DMarkupTypeDatum,			/*!< Datum. */
	kA3DMarkupTypeFastener,			/*!< Fastener. */
	kA3DMarkupTypeGdt,				/*!< GD&T. */
	kA3DMarkupTypeLocator,			/*!< Locator. */
	kA3DMarkupTypeMeasurementPoint,	/*!< Point. */
	kA3DMarkupTypeRoughness,		/*!< Roughness. */
	kA3DMarkupTypeWelding,			/*!< Welding. */
	kA3DMarkupTypeTable,			/*!< Table. */
	kA3DMarkupTypeOther				/*!< Other. */
} A3DEMarkupType;

/*!
\brief Markup subtype identifiers
\version 2.0
*/
typedef enum
{
	kA3DMarkupSubTypeUnknown						=  0,	/*!< Unknown value. */ 
	kA3DMarkupSubTypeEnumMax,								/*!< Unknown max value. \version 2.2 */ 

	kA3DMarkupSubTypeDatumIdent						=  1,	/*!< Datum subtype. */ 
	kA3DMarkupSubTypeDatumTarget,							/*!< Datum subtype. */ 
	kA3DMarkupSubTypeDatumEnumMax,							/*!< Datum max value. \version 2.2 */ 

	kA3DMarkupSubTypeDimensionDistance				=  1,	/*!< Dimension distance subtype. */ 
	kA3DMarkupSubTypeDimensionDistanceOffset,				/*!< Dimension distance subtype. */ 
	kA3DMarkupSubTypeDimensionDistanceCumulate,				/*!< Dimension distance subtype. */ 
	kA3DMarkupSubTypeDimensionChamfer,						/*!< Dimension chamfer subtype. */ 
	kA3DMarkupSubTypeDimensionSlope,						/*!< Dimension slope subtype. */ 
	kA3DMarkupSubTypeDimensionOrdinate,						/*!< Dimension ordinate subtype. */ 
	kA3DMarkupSubTypeDimensionRadius,						/*!< Dimension radius subtype. */ 
	kA3DMarkupSubTypeDimensionRadiusTangent,				/*!< Dimension radius subtype. */ 
	kA3DMarkupSubTypeDimensionRadiusCylinder,				/*!< Dimension radius subtype. */ 
	kA3DMarkupSubTypeDimensionRadiusEdge,					/*!< Dimension radius subtype. */ 
	kA3DMarkupSubTypeDimensionDiameter,						/*!< Dimension diameter subtype. */ 
	kA3DMarkupSubTypeDimensionDiameterTangent,				/*!< Dimension diameter subtype. */ 
	kA3DMarkupSubTypeDimensionDiameterCylinder,				/*!< Dimension diameter subtype. */ 
	kA3DMarkupSubTypeDimensionDiameterEdge,					/*!< Dimension diameter subtype. */ 
	kA3DMarkupSubTypeDimensionDiameterCone,					/*!< Dimension diameter subtype. */ 
	kA3DMarkupSubTypeDimensionLength,						/*!< Dimension length subtype. */ 
	kA3DMarkupSubTypeDimensionLengthCurvilinear,			/*!< Dimension length subtype. */ 
	kA3DMarkupSubTypeDimensionLengthCircular,				/*!< Dimension length subtype. */ 
	kA3DMarkupSubTypeDimensionAngle,						/*!< Dimension angle subtype. */ 
	kA3DMarkupSubTypeDimensionEnumMax,						/*!< Dimension max value. \version 2.2 */ 

	kA3DMarkupSubTypeGdtFcf							=  1,	/*!< GD&T Feature control frame subtype. */ 
	kA3DMarkupSubTypeGdtEnumMax,							/*!< GD&T max value. \version 2.2 */ 

	kA3DMarkupSubTypeWeldingLine					=  1,	/*!< Line welding subtype. */ 
	kA3DMarkupSubTypeWeldingSpot,							/*!< Spot welding subtype. */ 
	kA3DMarkupSubTypeWeldingEnumMax,						/*!< Welding max value. \version 2.2 */ 

	kA3DMarkupSubTypeOtherSymbolUser				=  1,	/*!< User symbol, other subtype. */ 
	kA3DMarkupSubTypeOtherSymbolUtility,					/*!< Utility symbol, other subtype. */ 
	kA3DMarkupSubTypeOtherSymbolCustom,						/*!< Custom symbol, other subtype. */ 
	kA3DMarkupSubTypeOtherGeometricReference,				/*!< Geometric reference, other subtype. */ 
	kA3DMarkupSubTypeOtherRegion,							/*!< Region symbol, other subtype. \version 7.2 */ 
	kA3DMarkupSubTypeOtherEnumMax							/*!< Other max value. \version 2.2 */ 
} A3DEMarkupSubType;

/*!
\ingroup a3d_markup_rtf
\brief Symbol identifiers used in RTF strings
\version 4.2
*/

typedef enum
{
	KEA3DSymbol_UNKNOWN=0,                 /*!< Not a symbol. */ 
	KEA3DSymbol_Angularity,                /*!< Angularity. */ 
	KEA3DSymbol_MoreOrLess,				   /*!< MoreOrLess. */ 
	KEA3DSymbol_Micron,					   /*!< Micron. */ 
	KEA3DSymbol_Circularity,			   /*!< Circularity. */ 
	KEA3DSymbol_Concentricity,			   /*!< Concentricity. */ 
	KEA3DSymbol_Cylindricity,			   /*!< Cylindricity. */ 
	KEA3DSymbol_Parallelism,			   /*!< Parallelism. */ 
	KEA3DSymbol_Perpendicularity,		   /*!< Perpendicularity. */ 
	KEA3DSymbol_Symmetry,				   /*!< Symmetry. */ 
	KEA3DSymbol_TotalRunout,			   /*!< TotalRunout. */ 
	KEA3DSymbol_Straightness,			   /*!< Straightness. */ 
	KEA3DSymbol_Flatness,				   /*!< Flatness. */ 
	KEA3DSymbol_LineProfile,			   /*!< LineProfile. */ 
	KEA3DSymbol_SurfaceProfile,			   /*!< SurfaceProfile. */ 
	KEA3DSymbol_Runout,					   /*!< Runout. */ 
	KEA3DSymbol_Countersink,			   /*!< Countersink. */ 
	KEA3DSymbol_Counterbore,			   /*!< Counterbore. */ 
	KEA3DSymbol_Depth,					   /*!< Depth. */ 
	KEA3DSymbol_Centerline,				   /*!< Centerline. */ 
	KEA3DSymbol_Ohm,					   /*!< Ohm. */ 
	KEA3DSymbol_Omega,					   /*!< Omega. */ 
	KEA3DSymbol_SmallerOrEqual,			   /*!< SmallerOrEqual. */ 
	KEA3DSymbol_GreaterOrEqual,			   /*!< GreaterOrEqual. */ 
	KEA3DSymbol_Slope,					   /*!< Slope. */ 
	KEA3DSymbol_ConicalTaper,			   /*!< ConicalTaper. */ 
	KEA3DSymbol_Diameter,				   /*!< Diameter. */ 
	KEA3DSymbol_FreeState,				   /*!< FreeState. */ 
	KEA3DSymbol_LeastMaterial,			   /*!< LeastMaterial. */ 
	KEA3DSymbol_MaximumMaterial,		   /*!< MaximumMaterial. */ 
	KEA3DSymbol_ProjectedTolerance,		   /*!< ProjectedTolerance. */ 
	KEA3DSymbol_TangentPlane,			   /*!< TangentPlane. */ 
	KEA3DSymbol_Statistical,			   /*!< Statistical. */ 
	KEA3DSymbol_Position,				   /*!< Position. */ 
	KEA3DSymbol_Square,					   /*!< Square. */ 
	KEA3DSymbol_Triangle,				   /*!< Triangle. */ 
	KEA3DSymbol_between,				   /*!< between. */ 
	KEA3DSymbol_RegardlessOfFeatureSize,   /*!< RegardlessOfFeatureSize. */ 
	KEA3DSymbol_Degre,					   /*!< Degre. */ 
	KEA3DSymbol_Encompassing,			   /*!< Encompassing. */ 
	KEA3DSymbol_CircledU,				   /*!< CircledU. */ 
	KEA3DSymbol_CircledR,				   /*!< CircledR. */ 
	KEA3DSymbol_RightwardArrow,			   /*!< RightwardArrow. */ 
	KEA3DSymbol_SubsetOf,				   /*!< SubsetOf. */ 
	KEA3DSymbol_1STANG,					   /*!< 1STANG. */ 
	KEA3DSymbol_3RDANG,					   /*!< 3RDANG. */ 
	KEA3DSymbol_BREAK15,				   /*!< BREAK15. */ 
	KEA3DSymbol_BREAK30,				   /*!< BREAK30. */ 
	KEA3DSymbol_DATUM1,					   /*!< DATUM1. */ 
	KEA3DSymbol_DATUM2,					   /*!< DATUM2. */ 
	KEA3DSymbol_MINUS,					   /*!< MINUS. */ 
	KEA3DSymbol_PLINE,					   /*!< PLINE. */ 
	KEA3DSymbol_PLUS,					   /*!< PLUS. */ 
	KEA3DSymbol_STRETCH,				   /*!< STRETCH. */ 
	KEA3DSymbol_STS,					   /*!< STS. */ 
	KEA3DSymbol_STS_,					   /*!< STS_. */ 
	KEA3DSymbol_STS_ANG,				   /*!< STS_ANG. */ 
	KEA3DSymbol_STS_ANG_,				   /*!< STS_ANG_. */ 
	KEA3DSymbol_STS_BAS,				   /*!< STS_BAS. */ 
	KEA3DSymbol_STS_BAS_,				   /*!< STS_BAS_. */ 
	KEA3DSymbol_STS_CIR,				   /*!< STS_CIR. */ 
	KEA3DSymbol_STS_CIR_,				   /*!< STS_CIR_. */ 
	KEA3DSymbol_STS_MAT,				   /*!< STS_MAT. */ 
	KEA3DSymbol_STS_MAT_,				   /*!< STS_MAT_. */ 
	KEA3DSymbol_STS_MLT,				   /*!< STS_MLT. */ 
	KEA3DSymbol_STS_MLT_,				   /*!< STS_MLT_. */ 
	KEA3DSymbol_STS_NOM,				   /*!< STS_NOM. */ 
	KEA3DSymbol_STS_NOM_,				   /*!< STS_NOM_. */ 
	KEA3DSymbol_STS_PAR,				   /*!< STS_PAR. */ 
	KEA3DSymbol_STS_PAR_,				   /*!< STS_PAR_. */ 
	KEA3DSymbol_STS_PER,				   /*!< STS_PER. */ 
	KEA3DSymbol_STS_PER_,				   /*!< STS_PER_. */ 
	KEA3DSymbol_STS_PRT,				   /*!< STS_PRT. */ 
	KEA3DSymbol_STS_PRT_,				   /*!< STS_PRT_. */ 
	KEA3DSymbol_STS_RAD,				   /*!< STS_RAD. */ 
	KEA3DSymbol_STS_RAD_				   /*!< STS_RAD_. */ 
} A3DEMarkupSymbol;

/*!
@} <!-- end of a3d_markup_enums -->
*/

/*!
\brief Markup structure
\ingroup a3d_markup_module
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DEMarkupType m_eType;						/*!< Markup type. */
	A3DEMarkupSubType m_eSubType;				/*!< Markup subtype. */
	A3DUns32 m_uiLeadersSize;					/*!< Number of \ref A3DMkpLeader in next array. */
	A3DMkpLeader** m_ppLeaders;					/*!< Array of \ref A3DMkpLeader. */
	A3DUns32 m_uiLinkedItemsSize;				/*!< Number of \ref A3DMiscMarkupLinkedItem in next array. */
	A3DMiscMarkupLinkedItem** m_ppLinkedItems;	/*!< Array of \ref A3DMiscMarkupLinkedItem. */
	A3DTessMarkup* m_pTessellation;				/*!< Tessellation of markup. May be NULL. Does not contain the leaders' tessellation. */
} A3DMkpMarkupData;

/*!
\brief Populates the \ref A3DMkpMarkupData structure
\ingroup a3d_markup_module
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpMarkupGet,(	const A3DMkpMarkup* pMarkup,
													A3DMkpMarkupData* pData));
/*!
\brief Creates the \ref A3DMkpMarkup from \ref A3DMkpMarkupData structure
\ingroup a3d_markup_module
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpMarkupCreate,(	const A3DMkpMarkupData* pData,
														A3DMkpMarkup** ppMarkup));

/*!
\brief Get links corresponding to the \ref A3DMkpMarkup references
\ingroup a3d_markup_module
\version 6.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpLinkForMarkupReferenceGet,(const A3DMkpMarkup* pMarkup,
											A3DUns32& uiLinkedItemsSize,				
											A3DMiscMarkupLinkedItem**& ppLinkedItems));
/*!
\brief Get links corresponding to the \ref A3DMkpMarkup additional references
such as element defining the toleranced line for line profile.
\ingroup a3d_markup_module
\version 9.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DMkpLinkForAdditionalMarkupReferenceGet, (const A3DMkpMarkup* pMarkup,
											A3DUns32& uiLinkedItemsSize,				
											A3DMiscMarkupLinkedItem**& ppLinkedItems));
/*!
\defgroup a3d_markup_rtf RTF parsing
\ingroup a3d_markup_module
Set of functions used to parse RTF strings. \n
RTF strings can be present in \ref A3DMDFCFDraftingRowData, \ref A3DMarkupGDTData, \ref A3DMarkupRichTextData

\par Sample code
\include MarkupRTF.cpp
*/

/*!
\brief Structure used to parse RTF strings
\ingroup a3d_markup_rtf
\version 4.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_usGetFieldIndex;         /*!< Reserved; used internally to parse RTF string. */
	A3DUTF8Char* m_pcText;				/*!< Text extracted from the RTF. Only one caracter if the text is a symbol. */
	A3DUTF8Char* m_pcFamilyName;	    /*!< Font family name extracted from the RTF. */
	A3DEMarkupSymbol m_eSymbol;         /*!< Set if m_pcText is a symbol. \ref A3DEMarkupSymbol */ 
	A3DInt32 m_aRGB[3];					/*!< Text color extracted from the RTF. */
	A3DFloat m_fHeight;		            /*!< Text size as millimeter. */
	A3DInt8 m_cAttributes;			    /*!< Text attributes. See \ref a3d_fontattribdef. */
} A3DRTFFieldData;

/*!
\ingroup a3d_markup_rtf
\brief Initialize RTF data for parsing 
\version 4.2

\return \ref A3D_ERROR \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpRTFInit,(	const A3DUTF8Char* pRTF,
									A3DVoid*& pRTFData));


/*!
\ingroup a3d_markup_rtf
\brief Get each independent field of a RTF data
\version 4.2

\return \ref A3D_ERROR \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMkpRTFGetField,(
		 A3DVoid* pRTFData,
		 A3DRTFFieldData *pRTFField));


/*!
\ingroup a3d_markup_rtf
\brief delete RTF data created by \ref A3DMkpRTFInit
\version 4.2

\return \ref A3D_ERROR \n
\return \ref A3D_SUCCESS \n
*/

A3D_API (A3DStatus, A3DMkpRTFDelete,(A3DVoid* pRTFData));

#endif	/*	__A3D_MARKUP__ */

#ifndef __A3D_FONTS__

/*!
\defgroup a3d_fonts Fonts
\ingroup a3d_markup_module
When creating a markup tessellation that uses specific fonts, 
store fonts with font keys (\ref A3DFontKeyData)
 by invoking the \ref A3DGlobalFontKeyCreate function.  

When parsing a markup tessellation that uses specific fonts, 
use the \ref A3DGlobalFontKeyGet function
to obtain fonts information from font keys (\ref A3DFontKeyData).

\sa a3d_tessmarkup
*/

/*!
\defgroup a3d_fontattribdef Flags for Font and Font-Key Attributes
\ingroup a3d_fonts
\version 2.0

These masks are used to define the attributes for \ref A3DFontData and \ref A3DFontKeyData
\note The bit 0x01 is unused.
@{
*/
#define kA3DFontBold			0x02	/*!< Bold. */
#define kA3DFontItalic			0x04	/*!< Italic. */
#define kA3DFontUnderlined		0x08	/*!< Underlined. */
#define kA3DFontStrikedOut		0x10	/*!< Striked-out. */
#define kA3DFontOverlined		0x20	/*!< Overlined. */
#define kA3DFontStreched		0x40	/*!<
											Streched. In case the font used is not the original font, 
											it indicates that the text needs to be stretched to fit its bounding box. */
#define kA3DFontWired			0x80	/*!< Wired. Indicates that the original font is a wirefame font. */
#define kA3DFontFixedWidth		0x100	/*!< Fixed width. Indicates that the original font is not proportional (each glyph has the same width). */
/*!
@} <!-- end of module a3d_fontattribdef -->
*/

/*!
\brief Font key CharSet
\ingroup a3d_fonts
\version 2.0
*/
typedef enum
{
	kA3DCharsetUnknown = -1,		/*!< */
	kA3DCharsetRoman = 0,			/*!< */
	kA3DCharsetJapanese,			/*!< */
	kA3DCharsetTraditionalChinese,	/*!< */
	kA3DCharsetKorean,				/*!< */
	kA3DCharsetArabic,				/*!< */
	kA3DCharsetHebrew,				/*!< */
	kA3DCharsetGreek,				/*!< */
	kA3DCharsetCyrillic,			/*!< */
	kA3DCharsetRightLeft,			/*!< */
	kA3DCharsetDevanagari,			/*!< */
	kA3DCharsetGurmukhi,			/*!< */
	kA3DCharsetGujarati,			/*!< */
	kA3DCharsetOriya,				/*!< */
	kA3DCharsetBengali,				/*!< */
	kA3DCharsetTamil,				/*!< */
	kA3DCharsetTelugu,				/*!< */
	kA3DCharsetKannada,				/*!< */
	kA3DCharsetMalayalam,			/*!< */
	kA3DCharsetSinhalese,			/*!< */
	kA3DCharsetBurmese,				/*!< */
	kA3DCharsetKhmer,				/*!< */
	kA3DCharsetThai,				/*!< */
	kA3DCharsetLaotian,				/*!< */
	kA3DCharsetGeorgian,			/*!< */
	kA3DCharsetArmenian,			/*!< */
	kA3DCharsetSimplifiedChinese,	/*!< */
	kA3DCharsetTibetan,				/*!< */
	kA3DCharsetMongolian,			/*!< */
	kA3DCharsetGeez,				/*!< */
	kA3DCharsetEastEuropeanRoman,	/*!< */
	kA3DCharsetVietnamese,			/*!< */
	kA3DCharsetExtendedArabic		/*!< */
} A3DECharSet;

/*!
\brief Font key structure
\ingroup a3d_fonts
\version 2.0

This structure stores the information of a font key.
Font keys are used by markup tessellation.

\sa a3d_tessmarkupfontkeydef
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DInt32 m_iFontFamilyIndex;	/*!< Font family index. */
	A3DInt32 m_iFontStyleIndex;		/*!< Font style index. */
	A3DInt32 m_iFontSizeIndex;		/*!< Font size index. */
	A3DInt8 m_cAttributes;			/*!< Font attributes. See \ref a3d_fontattribdef. */
} A3DFontKeyData;

/*!
\brief Font structure
\ingroup a3d_fonts
\version 2.0

This structure stores the information of a font.
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcFamilyName;	/*!< Font family name. */
	A3DUTF8Char* m_pcFontFilePath;	/*!< Font file path. */
	A3DECharSet m_eCharset;			/*!< Font character set. */
	A3DUns32 m_uiSize;				/*!< Font size. */
	A3DInt8 m_cAttributes;			/*!< Font attributes. See \ref a3d_fontattribdef. */
} A3DFontData;

/*!
\brief Retrieves font information (\ref A3DFontData) from the \ref A3DFontKeyData structure.
This function is useful when reading markup tessellation.
\ingroup a3d_fonts
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_MARKUP_CANNOT_ACCESS_FONT \n
\return \ref A3D_MARKUP_INVALID_FONTKEY \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalFontKeyGet,(	const A3DFontKeyData* pFontKeyData,
														A3DFontData* pFontData));

/*!
\brief Gets text bounding box according to the font
\ingroup a3d_fonts
\version 5.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_MARKUP_CANNOT_ACCESS_FONT \n
\return \ref A3D_MARKUP_INVALID_FONTKEY \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalFontTextBoxGet, (	const A3DFontKeyData* psFontKeyData,
												 A3DUTF8Char* pcText,
												 A3DDouble &dLength,
												 A3DDouble &dHeight));

/*!
\brief Gets text bounding box and scale according to the font
\ingroup a3d_fonts
\version 7.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_MARKUP_CANNOT_ACCESS_FONT \n
\return \ref A3D_MARKUP_INVALID_FONTKEY \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalFontTextBoxAndScaleGet, (	const A3DFontKeyData* psFontKeyData,
														A3DUTF8Char* pcText,
														A3DDouble &dLength,
														A3DDouble &dHeight,
														A3DDouble &dScale));
/*!
\brief Creates the \ref A3DFontKeyData structure from the \ref A3DFontData structure
\ingroup a3d_fonts
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_MARKUP_CANNOT_CREATE_FONTKEY \n
\return \ref A3D_MARKUP_INVALID_FONTKEY \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalFontKeyCreate,(	const A3DFontData* pFontData,
															A3DFontKeyData* pFontKeyData));

/*!
\brief Gets text tessellation as wireframe
\ingroup a3d_fonts
\version 6.1

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_MARKUP_CANNOT_ACCESS_FONT \n
\return \ref A3D_MARKUP_INVALID_FONTKEY \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DGlobalFontTextTessellationGet, (	const A3DFontKeyData* psFontKeyData,
														 const A3DUTF8Char* pcOneChar,
														 A3DRiSet** ppset,
														 A3DDouble &dCharWidth));

#endif	/*	__A3D_FONTS__ */

#endif	/*	__A3DPRCMARKUP_H__ */
