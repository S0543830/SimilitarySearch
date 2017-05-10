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
\brief      Header of <b>A3DSDK</b>. Tool section.
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCTOOLS_H__
#define __A3DPRCTOOLS_H__

/*!
\defgroup a3d_tools_module Tools Module
\ingroup a3d_base_module
*/


/*!
\defgroup a3d_copy_and_adapt_brep_model Copy and adapt B-rep model
\ingroup a3d_tools_module
*/

/*!
\ingroup a3d_copy_and_adapt_brep_model
\brief Copy and convert to NURBS parameter
*/
typedef struct
{
	A3DUns16				m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool					m_bUseSameParam;				/*!< If true, surfaces will keep their parametrization when converted to NURBS. */
	A3DDouble				m_dTol;							/*!< Tolerance value of resulting B-rep. The value is relative to the scale of the model. */
	A3DBool					m_bDeleteCrossingUV;			/*!< If true, UV curves that cross seams of periodic surfaces are replaced by 3D curves */
	A3DBool					m_bSplitFaces;					/*!< If true, periodic surfaces are split on parametric seams */
	A3DBool					m_bSplitClosedSurfaces;			/*!< If true, closed surfaces are split into faces at the parametric seam and mid-parameter */
	A3DBool					m_bForceComputeUV;				/*!< If true, UV curves are computed from the B-rep data */
	A3DBool					m_bAllowUVCrossingSeams;		/*!< If true and m_bForceComputeUV is true, computed UV curves can cross seams. \version 9.0 */
	A3DBool					m_bForceCompute3D;				/*!< If true, 3D curves are computed from the B-rep data */
	A3DUns32				m_uiAcceptableSurfacesSize;		/*!< Length of m_puiAcceptableSurfaces array */
	A3DUns32*				m_puiAcceptableSurfaces;		/*!< A list of acceptable surface types that your modeler can handle. Acceptable surface types are listed in A3DSDKTypes.h and begin with 'kA3DTypeSurf' */
	A3DUns32				m_uiAcceptableCurvesSize;		/*!< Length of m_puiAcceptableCurves array */
	A3DUns32*				m_puiAcceptableCurves;			/*!< A list of acceptable curve types that your modeler can handle. Acceptable curve types are listed in A3DSDKTypes.h and begin with 'kA3DTypeCrv' */
	A3DBool					m_bContinueOnError;				/*!< Continue processing even if an error occurs. Use /ref A3DCopyAndAdaptBrepModelAdvanced to get the error status. */
} A3DCopyAndAdaptBrepModelData;


/*!
\ingroup a3d_copy_and_adapt_brep_model
\brief Copy and adapt B-rep parameters

<p>The B-rep used by HOOPS Exchange may not be completely compatible with modeling systems that do not support the full range of B-rep as employed by PRC. This function attempts to convert PRC B-rep into a format that is compatible with your system.</p>

<p>In order to use this function, you create a A3DCopyAndAdaptBrepModelData structure and configure it to create a new B-rep model using entities you are able to support. The function can transform predetermined surface types and curves to NURBS. It also can process parametric curves and 3D curves, as well as split periodic parameteric surfaces.</p>

<p>Finally, it creates a new B-rep model. After using it, the new model should be deleted.</p>
	
	A3DCopyAndAdaptBrepModel will perform the following steps:</p>

	\li For each face, the bearing surface and the 3D curves are converted
	\li Surfaces are reduced in size
	\li Cross-period UV curves are deleted if necessary
	\li Faces are split at periodic seams and/or mid-parameter for closed surfaces
	\li Final UV curves are computed
	\li A second surface shrink is performed with new UV parameters
	\li Final 3D curves are computed
	
\note When the function A3DCopyAndAdaptBrepModel returns an error, you may try to
	set the parameters m_bSplitFaces and/or m_bForceComputeUV to 'false' and retry the 
	conversion.
	
\param [in] p A pointer to the source B-rep entity
\param [in] psSetting The structure that defines which types of B-rep you would like to convert to
\param [out] pp A pointer to the result B-rep entity or entities
*/

A3D_API (A3DStatus, A3DCopyAndAdaptBrepModel, (	const A3DEntity* p,
																const A3DCopyAndAdaptBrepModelData *psSetting,
																A3DEntity** const pp) );


/*!
\ingroup a3d_copy_and_adapt_brep_model
\brief Copy and adapt B-rep parameters

<p>Same as \ref A3DCopyAndAdaptBrepModelData , but return status of each face in error if \ref A3DCopyAndAdaptBrepModelData.m_bContinueOnError is set to true
<p> puiNbErrors return the number of face in error
<p> paiErrors corresponds to a set of index and error code
<code>
paiErrors[0] = type the topological element
paiErrors[1] = error status
paiErrors[2] = number of index to find element (connex = 1, shell = 2, face = 3, loop = 4, coedge /edge = 5)
paiErrors[3] = first index
...
paiErrors[3+paiErrors[2]] = last index
</code>

\param [in] p A pointer to the source B-rep entity
\param [in] psSetting The structure that defines which types of B-rep you would like to convert to
\param [out] pp A pointer to the result B-rep entity or entities
\param [out] puiNbErrors Number of elements in error
\param [out] paiErrors Index and error code of each element
*/
A3D_API (A3DStatus, A3DCopyAndAdaptBrepModelAdvanced, (const A3DEntity* p,
																		const A3DCopyAndAdaptBrepModelData *psSetting,
																		A3DEntity** const pp,
																		A3DUns32 *puiNbErrors,
																		A3DInt32 **paiErrors) );


/*!
\defgroup a3d_adapt_and_replace_all_brep_in_modelfile Adapt and replace all B-rep in model file
\ingroup a3d_tools_module
*/


/*!
\ingroup a3d_adapt_and_replace_all_brep_in_modelfile
\brief Entity Convert to NURBS facility

	This function allows to adapt all Brep in a Model File to the customers' need.
	It allows to transform predetermined type of surface and curves as NURBS.
	It allows to compute parametric curves or/and 3D curves, split periodicals surfaces...
	Finally, It creates	a new BrepModel. After using it, it should be delete using FreeBrepModel.
	
	The list of steps is following; these steps are performed according to
	A3DCopyAndAdaptBrepModelData:
	\li For each face, the bearing surface is converted and then the 3D curves that are present,
	\li Surfaces are shrinked,
	\li Cross-period UV curves are deleted if needed,
	\li Faces are split at periodic seams and/or mid-parameter for closed surfaces,
	\li Final UV curves are computed,
	\li A second surface shrink is performed with new UVs,
	\li Final 3D curves are computed.

\version 5.2
\note When the function A3AdaptAndReplaceAllBrepInModelFile returns an error, you may try to
	set the parameters m_bSplitFaces and/or m_bForceComputeUV to false and retry the 
	conversion.
*/

A3D_API (A3DStatus, A3DAdaptAndReplaceAllBrepInModelFile, (		A3DAsmModelFile* p,
																const A3DCopyAndAdaptBrepModelData *psSetting
																) );



/*!
\defgroup a3d_entity_delete Delete Entities
\ingroup a3d_tools_module
*/

/*!
\ingroup a3d_entity_delete
\brief Entity deletion facility.

This function is reserved for future use. It is excluded from this current version of the API.

\warning This function must be called very carefully, only on locally created data. When
used in another case, it may corrupt global structure and drastically disturb the library behavior.

\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DEntityDelete,(A3DEntity* pEntity));



/*!
\defgroup a3d_entity_pdfid Entity PDF IDs 
\ingroup a3d_tools_module
*/
/*!
\ingroup a3d_entity_pdfid
\brief Gets the PDF node unique IDs for the entities.

Given a pointer to the PRC entity, this function gets the unique name that will be used in the PDF scene graph. 
This function must be used AFTER the PRC file has been created from the model file.

\param [in] pEntity The pointer to the PRC entity
\param [in] pEntityFather The pointer to the product occurrence owner to the PRC entity. NULL if pEntity is a product occurrence.
\param [in] pA3DRWParamsPrcWriteHelper The pointer to the helper object generally built by the function A3DAsmModelFileExportToPrcFile.
\param [out] pcUTF8Name The identifier as a string.

\version 4.1

\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DEntityGetPDFNodeIdFromWrite,(const A3DEntity* pEntity,
	const A3DEntity* pEntityFather,
	const A3DRWParamsPrcWriteHelper* pA3DRWParamsPrcWriteHelper,
	A3DUTF8Char** pcUTF8Name));



/*!
\defgroup a3d_tools_topoitemowners_module Topological item owners
\ingroup a3d_tools_module
\version 5.0
*/

/*!
\brief Structure is a linked list for storing topology items owners
\ingroup a3d_tools_topoitemowners_module
\version 5.0

This structure gives you an access to topology item owners.
*/
typedef struct
{
	const A3DTopoItem*		m_pTopoItem;					/*!< Topology item owner. */
	void*					m_pNext;						/*!< If the topology item is shared by several owners, this pointer gives access to the next owner item. */
} A3DTopoItemOwner;


/*!
\ingroup a3d_tools_topoitemowners_module
\brief Structure for storing topology items owners
\version 5.0
Methods and structures dedicated to managing the link between topology items and their owner(s).
*/
typedef void* A3DTopoItemOwnersManager;

/*!
\brief Creates manager of topology items fron an \ref A3DRiRepresentationItem
\ingroup a3d_tools_topoitemowners_module
\version 5.0
\par
This function creates a map, on request, between topological items and linked lists of owners.
When the map is built, the function \ref A3DTopoItemOwnersGet lets you retrieve owners of specific topological item.
For example, if you need the faces owner of edges, first you build your map, then you retrieve the owner list for each edge.
The following code shows how to use it.

\code
	// map creation
	A3DTopoItemOwnersManager* pTopologyOwnersManager = NULL;
	if(A3DTopoItemOwnersManagerGet(pBrepOwner, pTopologyOwnersManager) != A3D_SUCCESS)
		return A3D_ERROR;
	if(pTopologyOwnersManager == NULL)
		return A3D_ERROR;
	
	// edge owners = CoEdge
	A3DTopoItemOwner* pOwningCoEdge = NULL;
	A3DTopoItemOwnersGet(pTopologyOwnersManager, pEdge, pOwningCoEdge);
	while( pOwningCoEdge!=NULL)
	{
		// coedge owners = Loop
		A3DTopoItemOwner* pOwningLoop = NULL;
		A3DTopoItemOwnersGet(pTopologyOwnersManager, pOwningCoEdge->m_pTopoItem, pOwningLoop);
		while( pOwningLoop!=NULL)
		{
			// Loop owners = face
			A3DTopoItemOwner* pOwingFace = NULL;
			A3DTopoItemOwnersGet(pTopologyOwnersManager, pOwningLoop->m_pTopoItem, pOwingFace);
			while( pOwingFace!=NULL)
			{
				if(A3DEntityGetType(pOwingFace->m_pTopoItem, &entityType) != A3D_SUCCESS)
					return A3D_ERROR;
				if(entityType != kA3DTypeTopoFace)
					return A3D_ERROR;
				
				pOwingFace = pOwingFace->m_pNext;
			}
			pOwningLoop = pOwningLoop->m_pNext;
		}
		pOwningCoEdge = pOwningCoEdge->m_pNext;
	}

\endcode

Note that, if A3DTopoItemOwnersManagerGet is called several times with the same representation item, the map is not recomputed; and if the 
representation item is null, the map is released.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DTopoItemOwnersManagerGet,( const A3DRiRepresentationItem* pBrepOwner, A3DTopoItemOwnersManager*& pTopoItemOwnersManager));


/*!
\ingroup a3d_tools_topoitemowners_module
\brief Gets owners of topology item
\version 5.0

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DTopoItemOwnersGet,( A3DTopoItemOwnersManager* pTopoItemOwnersManager, const A3DTopoItem* pTopoItem, A3DTopoItemOwner*& pTopoItemOwner));




/*!
\defgroup a3d_physical_properties Physical properties
\ingroup a3d_tools_module
\version 5.2
*/

/*!
\ingroup a3d_physical_properties
\brief Physical property settings
\version 5.2
*/
typedef struct
{
	A3DUns16				m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DVector3dData			m_sGravityCenter;					/*!< Gravity center. */
	A3DDouble				m_dSurface;							/*!< B-rep model surface area of resulting B-rep. */
	A3DBool					m_bVolumeComputed;					/*!< False, typically in case the B-rep is not a solid. */
	A3DDouble				m_dVolume;							/*!< B-rep model volume of resulting B-rep. */
} A3DPhysicalPropertiesData;


/*!
\ingroup a3d_physical_properties
\brief Function to compute the physical properties (the gravity center, surface area and volume) of a BrepModel.
An optional scale, psScale, can be used. It can be either uniform or not. Physical properties will be computed after having scaled the 
geometrical data in the A3DRiBrepModel.
\param [in] p The input B-rep model.
\param [in] psScale The optional scale.
\param [out] psPhysicalPropertiesData The wanted physical properties.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n

\version 5.2
*/
A3D_API (A3DStatus, A3DComputePhysicalProperties,(	const A3DRiBrepModel* p,
																	const A3DVector3dData* psScale,
																	A3DPhysicalPropertiesData* psPhysicalPropertiesData));

/*!
\ingroup a3d_physical_properties
\brief Function to compute the surface of the current A3DTopoFace. The current TopoContext is needed in order to get the correct current scale.


\param [in] pFace The input A3DTopoFace.
\param [in] pBrepDataTopoContext The corresponding A3DTopoContext of the current A3DTopoBrepData who is owing the A3DTopoFace.
\param [out] pArea The surface of the A3DTopoFace in the current unit.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n

\version 7.0
*/
A3D_API (A3DStatus, A3DComputeFaceArea, ( const A3DTopoFace* pFace, const A3DTopoContext* pBrepDataTopoContext, A3DDouble* pArea));
/*!
\ingroup a3d_physical_properties
\brief Function to compute the physical properties (the gravity center, surface area and volume) of a PolyBrepModel.
An optional scale, psScale, can be used. It can be either uniform or not. Physical properties will be computed after having scaled the 
geometrical data in the A3DRiPolyBrepModel.
\param [in] p The input poly B-rep model.
\param [in] psScale The optional scale.
\param [out] psPhysicalPropertiesData The wanted physical properties.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n

\version 6.1
*/
A3D_API (A3DStatus, A3DComputePolyBrepPhysicalProperties,(	const A3DRiPolyBrepModel* p,
															const A3DVector3dData* psScale,
															A3DPhysicalPropertiesData* psPhysicalPropertiesData));


/*!
\ingroup a3d_physical_properties
\brief Function to compute the physical properties (the gravity center, surface area and volume) of a modelfile, typically an assembly.
Data is returned in the modelfile unit;
\param [in] p The input modelfile.
\param [out] psPhysicalProperties The physical properties.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n

\version 5.2
*/
A3D_API (A3DStatus, A3DComputeModelFilePhysicalProperties,(	const A3DAsmModelFile* p,
															A3DPhysicalPropertiesData* psPhysicalProperties));


/*!
\defgroup a3d_simplify_modelfile_curve_and_surface_as_analytic Simplify modelfile curves and surfaces as analytic
\ingroup a3d_tools_module
*/

/*!
\ingroup a3d_simplify_modelfile_curve_and_surface_as_analytic
\brief Function to traverse the entire modelfile and simplify all curves and surfaces to analytics if possible, according to a certain tolerance.
\warning DEPRECATED: use \ref A3DSimplifyModelFileWithAnalytics
\param [in, out] p The input modelfile.
\param [in] dTol The tolerance.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n

\version 5.2
*/
A3D_API (A3DStatus, A3DSimplifyModelFileCurveAndSurfaceAsAnalytic,(	A3DAsmModelFile* p,
																	double dTol));


/*!
\defgroup a3d_simplify_modelfile_curve_and_surface_as_analytic Simplify modelfile curves and surfaces as analytic
\ingroup a3d_tools_module
*/

/*!
\ingroup a3d_simplify_modelfile_curve_and_surface_as_analytic
\brief Function to traverse the entire modelfile and simplify all curves and surfaces to analytics if possible, according to a certain tolerance.
Recognize surface type are:\n
\ref a3d_srfcone
\ref a3d_srfcylinder
\ref a3d_srfplane
\ref a3d_srfsphere
\ref a3d_srftorus
Recognize curve type are:\n
\ref a3d_crvline
\ref a3d_crvcircle
If uNbRecognizedType and pOptRecognizedType are defined, \ref A3DSimplifyModelFileWithAnalytics recognizes only given types.

\param [in, out] p The input modelfile.
\param [in] dTol The tolerance.
\param [in] uNbRecognizedType Size of array pOptRecognizedType.
\param [in] pOptRecognizedType Optional type of surface we want to recognize.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n

\version 7.0
*/
A3D_API (A3DStatus, A3DSimplifyModelFileWithAnalytics,(	A3DAsmModelFile* p,
																			A3DDouble dTol,
																			A3DUns32 uNbRecognizedType,
																			A3DEEntityType const *pOptRecognizedType));

#endif	/*	__A3DPRCTOOLS_H__ */
