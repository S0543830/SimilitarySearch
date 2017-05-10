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
\brief      Header file for surface entities
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCGEOMETRYSRF_H__
#define __A3DPRCGEOMETRYSRF_H__

#ifndef __A3DPRCGEOMETRYCRV_H__
#error A3DSDKGeometryCrv.h must be included before current file
#endif

/*!
\defgroup a3d_srf Surfaces Module
\ingroup a3d_geometry_module
\brief Creates and accesses entities that represent geometric surfaces

Geometric surfaces (\ref A3DSurfBase) are a mandatory part of the topology construct 
that is represented by an \ref A3DTopoBrepData entity. 

All surfaces are defined as follows: 
<ol>
	<li>Define the canonical form of the whole surface.</li>
	<li>Define the actual parameterization and the portion of surface (trimming information) 
		(\ref A3DUVParameterizationData). </li>
	<li>Define the orientation and scaling of the curve using a Cartesian transformation. 
		The transformation cannot specify mirror or non-uniform scaling transformations 
		(see \ref A3DMiscCartesianTransformationData). </li>
</ol>

*/

#ifndef __A3D_SRFNURBS__
/*!
\defgroup a3d_srfnurbs NURBS Surface (the base surface entity)
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfNurbs.

\note This surface type contains neither \ref A3DUVParameterizationData nor \ref A3DMiscCartesianTransformationData. 
*/

/*!
\brief Enumeration for characterizing a surface's form
\ingroup a3d_srfnurbs
\version 2.0
*/
typedef enum
{
	kA3DBSplineSurfaceFormPlane,					/*!< Planar surface. */
	kA3DBSplineSurfaceFormCylindrical,			/*!< Cylindrical surface. */
	kA3DBSplineSurfaceFormConical,				/*!< Conical surface. */
	kA3DBSplineSurfaceFormSpherical,				/*!< Spherical surface. */
	kA3DBSplineSurfaceFormRevolution,			/*!< Surface of revolution. */
	kA3DBSplineSurfaceFormRuled,					/*!< Ruled surface. */
	kA3DBSplineSurfaceFormGeneralizedCone,		/*!< Cone. */
	kA3DBSplineSurfaceFormQuadric,				/*!< Quadric surface. */
	kA3DBSplineSurfaceFormLinearExtrusion,		/*!< Surface of extrusion. */
	kA3DBSplineSurfaceFormUnspecified,			/*!< Unspecified. */
	kA3DBSplineSurfaceFormPolynomial				/*!< Polynomial surface. */
} A3DEBSplineSurfaceForm;

/*!
\brief Nurbs surface structure
\ingroup a3d_srfnurbs
\version 2.0

\note Size of \ref m_pCtrlPts is \ref m_uiUCtrlSize * \ref m_uiVCtrlSize, 
and control points are stored in a sequential form. (Pu0v0, Pu0v1, ..., Pu0vx, Pu1v0, Pu1v1, ..., Pu1vx, ..., Puxv0, ..., Puxvx).
\note Size of \ref m_pdWeights is \ref m_uiUCtrlSize * \ref m_uiVCtrlSize.
*/
typedef struct
{
	A3DUns16									m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DEKnotType								m_eKnotType;		/*!< Knot type. */
	A3DEBSplineSurfaceForm					m_eSurfaceForm;	/*!< Surface form. */
	A3DUns32										m_uiUDegree;		/*!< Degree in U direction. */
	A3DUns32										m_uiVDegree;		/*!< Degree in V direction. */
	A3DUns32										m_uiUKnotSize;		/*!< Knots number in U direction. */
	A3DUns32										m_uiVKnotSize;		/*!< Knots number in V direction. */
	A3DUns32										m_uiUCtrlSize;		/*!< Control points number in U direction. */
	A3DUns32										m_uiVCtrlSize;		/*!< Control points number in V direction. */
	A3DDouble*									m_pdUKnots;			/*!< Knots in U direction. */
	A3DDouble*									m_pdVKnots;			/*!< Knots in V direction. */
	A3DDouble*									m_pdWeights;		/*!< Weights if surface is rational. */
	A3DVector3dData*							m_pCtrlPts;			/*!< Control points. */
} A3DSurfNurbsData;

/*!
\brief Populates the \ref A3DSurfNurbsData structure
\ingroup a3d_srfnurbs
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfNurbsGet,(	const A3DSurfNurbs* pSrf,
													A3DSurfNurbsData* pData));

/*!
\brief Creates an \ref A3DSurfNurbs from an \ref A3DSurfNurbsData structure
\ingroup a3d_srfnurbs
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfNurbsCreate,(	const A3DSurfNurbsData* pData,
														A3DSurfNurbs** ppSrf));

/*!
\brief Populates the \ref A3DSurfNurbsData structure from any type of \ref A3DSurfBase
\ingroup a3d_srfnurbs
\version 2.0

This structure must be freed with \ref A3DSurfNurbsGet call.
\warning This function can modify the parameterization for surface. You must
treat related entities accordingly. 

\warning See note on Tolerance explanation at \ref A3DCrvBaseGetAsNurbs definition.

\warning This function can be called with any type of curve.

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SRF_NURBS_TOO_TINY_TOLERANCE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfBaseGetAsNurbs,(const A3DSurfBase* pSrf,
												  A3DDouble dTolerance, 
												  A3DBool bUseSameParameterization,
												  A3DSurfNurbsData* pData));
#endif	/*	__A3D_SRFNURBS__ */

#ifndef __A3D_SRFSPHERE__
/*!
\defgroup a3d_srfsphere Spherical Surface
\ingroup a3d_srf
\version 2.0

Entity type is \ref kA3DTypeSurfSphere.

For the canonical definition and corresponding parametric equation,
see the "SerializeSphere" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

*/

/*!
\brief Structure for representing a spherical surface
\ingroup a3d_srfsphere
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DDouble m_dRadius;	/*!< Radius. Must be greater than 0. */
} A3DSurfSphereData;

/*!
\brief Populates the \ref A3DSurfSphereData structure
\ingroup a3d_srfsphere
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfSphereGet,(	const A3DSurfSphere* pSrf, 
													A3DSurfSphereData* pData));

/*!
\brief Creates an \ref A3DSurfSphere from an \ref A3DSurfSphereData structure
\version 2.0
\ingroup a3d_srfsphere
\warning Associated transformation must be Identity
\warning Trimming interval must be defined inside curve definition
\warning Parameterization must have CoeffA = 1. and CoeffB = 0.
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfSphereCreate,(	const A3DSurfSphereData* pData,
														A3DSurfSphere** ppSrf));

#endif	/*	__A3D_SRFSPHERE__ */

#ifndef __A3D_SRFCYLINDER__
/*!
\defgroup a3d_srfcylinder Cylindrical Surface
\ingroup a3d_srf
\version 2.0

Entity type is \ref kA3DTypeSurfCylinder.

For the canonical definition and corresponding parametric equation,
see the "SerializeCylinder" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

*/

/*!
\brief Structure for representing a cylindrical surface
\ingroup a3d_srfcylinder
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DDouble m_dRadius;	/*!< Radius. Must be greater than 0. */
} A3DSurfCylinderData;

/*!
\brief Populates the \ref A3DSurfCylinderData structure
\ingroup a3d_srfcylinder
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfCylinderGet,(	const A3DSurfCylinder* pSrf, 
														A3DSurfCylinderData* pData));

/*!
\brief Creates an \ref A3DSurfCylinder from an \ref A3DSurfCylinderData structure
\ingroup a3d_srfcylinder
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfCylinderCreate,(	const A3DSurfCylinderData* pData, 
															A3DSurfCylinder** ppSrf));

#endif	/*	__A3D_SRFCYLINDER__ */

#ifndef __A3D_SRFTORUS__
/*!
\defgroup a3d_srftorus Toric Surface
\ingroup a3d_srf
\version 2.0

Entity type is \ref kA3DTypeSurfTorus.

For the canonical definition and corresponding parametric equation,
see the "SerializeTorus" section of the \REF_PRC_SPEC

\ref A3DUVParameterizationData allows for reparameterization and trim. 

*/

/*!
\brief Structure for defining toric surfaces
\ingroup a3d_srftorus
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DDouble m_dMajorRadius;	/*!< Major radius. Must be greater than 0. */
	A3DDouble m_dMinorRadius;	/*!< Minor radius. Must be greater than 0. */
} A3DSurfTorusData;

/*!
\brief Populates the \ref A3DSurfTorusData structure
\ingroup a3d_srftorus
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfTorusGet,(	const A3DSurfTorus* pSrf, 
													A3DSurfTorusData* pData));

/*!
\brief Creates an \ref A3DSurfTorus from an \ref A3DSurfTorusData structure
\ingroup a3d_srftorus
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfTorusCreate,(	const A3DSurfTorusData* pData, 
														A3DSurfTorus** ppSrf));


#endif	/*	__A3D_SRFTORUS */

#ifndef __A3D_SRFREVOLUTION__
/*!
\defgroup a3d_srfrevolution Revolution Surface
\ingroup a3d_srf
\version 2.0

Entity type is \ref kA3DTypeSurfRevolution.

For the canonical definition and corresponding parametric equation,
see the "SerializeRevolution" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

*/

/*!
\brief Revolution structure
\ingroup a3d_srfrevolution
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DCrvBase* m_pCurve; /*!< Curve to be rotated around axis */
	A3DVector3dData	m_sOrigin; /*!< Origin for axis */
	A3DVector3dData	m_sDirection; /*!< Direction vector for axis */
} A3DSurfRevolutionData;


/*!
\brief Populates the \ref A3DSurfRevolutionData structure
\ingroup a3d_srfrevolution
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfRevolutionGet,(const A3DSurfRevolution* pSrf, A3DSurfRevolutionData* pData));

/*!
\brief Creates an \ref A3DSurfRevolution from an \ref A3DSurfRevolutionData structure
\ingroup a3d_srfrevolution
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfRevolutionCreate,(const A3DSurfRevolutionData* pData, A3DSurfRevolution** ppSrf));


#endif	/*	__A3D_SRFREVOLUTION__ */

#ifndef __A3D_SRFEXTRUSION__
/*!
\defgroup a3d_srfextrusion Extrusion Surface
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfExtrusion.

For the canonical definition and corresponding parametric equation,
see the "SerializeExtrusion" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

*/

/*!
\brief Extrusion structure
\ingroup a3d_srfextrusion
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DCrvBase* m_pCurve; /*!< Curve to be extruded. */
	A3DVector3dData	m_sDirection; /*!< Direction vector for extrusion. */
} A3DSurfExtrusionData;


/*!
\brief Populates the \ref A3DSurfExtrusionData structure
\ingroup a3d_srfextrusion
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfExtrusionGet,(const A3DSurfExtrusion* pSrf, A3DSurfExtrusionData* pData));

/*!
\brief Creates an \ref A3DSurfExtrusion from an \ref A3DSurfExtrusionData structure
\ingroup a3d_srfextrusion
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfExtrusionCreate,(const A3DSurfExtrusionData* pData, A3DSurfExtrusion** ppSrf));


#endif	/*	__A3D_SRFEXTRUSION__ */

#ifndef __A3D_SRFOFFSET__
/*!
\defgroup a3d_srfoffset Offset Surface
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfOffset.

For the canonical definition and corresponding parametric equation,
see the "SerializeOffset" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 

*/

/*!
\brief Offset structure
\ingroup a3d_srfoffset
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DSurfBase* m_pBasisSurf;	/*!< Basis surface. Cannot be NULL. */
	A3DDouble m_dOffset;	/*!< Offset from basis surface. Can be negative. */
} A3DSurfOffsetData;


/*!
\brief Populates the \ref A3DSurfOffsetData structure
\ingroup a3d_srfoffset
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfOffsetGet,(	const A3DSurfOffset* pSrf,
													A3DSurfOffsetData* pData));

/*!
\brief Creates an \ref A3DSurfOffset from an \ref A3DSurfOffsetData structure
\ingroup a3d_srfoffset
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfOffsetCreate,(const A3DSurfOffsetData* pData, 
														A3DSurfOffset** ppSrf));


#endif	/*	__A3D_SRFOFFSET__ */

#ifndef __A3D_SRFPLANE__
/*!
\defgroup a3d_srfplane Plane Surface
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfPlane.

Canonical definition corresponds to coordinate system defined by \ref A3DMiscCartesianTransformationData.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

*/

/*!
\brief Surface Plane structure
\version 2.0
\ingroup a3d_srfplane
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;				/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;							/*!< UV Parameterization. */
} A3DSurfPlaneData;

/*!
\brief Populates the \ref A3DSurfPlaneData structure from any type of \ref A3DSurfPlane
\version 2.0
\ingroup a3d_srfplane
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfPlaneGet,(	const A3DSurfPlane* pSrf, 
													A3DSurfPlaneData* pData));

/*!
\brief Creates the \ref A3DSurfPlane from \ref A3DSurfPlaneData structure
\ingroup a3d_srfplane
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
\return \ref A3D_SRF_PLANE_CANNOT_CREATE_CANONICAL \n
*/
A3D_API (A3DStatus, A3DSurfPlaneCreate,(	const A3DSurfPlaneData* pData, 
														A3DSurfPlane** ppSrf));

#endif	/*	__A3D_SRFPLANE__ */

#ifndef __A3D_SRFBLEND01__
/*!
\defgroup a3d_srfblend01 Blend Surface Type 1
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfBlend01.

For the canonical definition and corresponding parametric equation,
see the "SerializeBlend01" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 

*/

/*!
\brief Blend01 structure
\ingroup a3d_srfblend01
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;				/*!< UV Parameterization. */
	A3DCrvBase* m_pPntCurve;							/*!< Basis curve of iso-0 points. */
	A3DCrvBase* m_pCtrCurve;							/*!< Basis curve of centers. */
	A3DCrvBase* m_pTanCurve;							/*!< Basis curve of tangents. */
} A3DSurfBlend01Data;

/*!
\brief Populates the \ref A3DSurfBlend01Data structure
\ingroup a3d_srfblend01
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfBlend01Get,(const A3DSurfBlend01* pSrf, A3DSurfBlend01Data* pData));

/*!
\brief Creates an \ref A3DSurfBlend01 from an \ref A3DSurfBlend01Data structure
\ingroup a3d_srfblend01
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfBlend01Create,(const A3DSurfBlend01Data* pData, A3DSurfBlend01** ppSrf));


#endif	/*	__A3D_SRFBLEND01__ */

#ifndef __A3D_SRFBLEND02__
/*!
\defgroup a3d_srfblend02 Blend Surface Type 2
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfBlend02.

For the canonical definition and corresponding parametric equation,
see the "SerializeBlend02" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 
*/

/*!
\brief Blend02 structure
\ingroup a3d_srfblend02
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;				/*!< UV Parameterization. */
	A3DSurfBase*	m_pSurface0;						/*!< Bound Surface 0. */
	A3DCrvBase*		m_pCurve0;							/*!< Bound curve 0. */
	A3DSurfBase*	m_pSurface1;						/*!< Bound surface 1. */
	A3DCrvBase*		m_pCurve1;							/*!< Bound curve 1. */
	A3DCrvBase*		m_pCenterCurve;					/*!< Center curve. */
	A3DBool			m_bCenterCurveSens;				/*!< Center curve sense. */									
	A3DBool			m_bBound0Sens;						/*!< Bound surface 0 sense. */
	A3DBool			m_bBound1Sens;						/*!< Bound surface 1 sense. */
	A3DDouble		m_dRadius0;							/*!< Radius 0. */
	A3DDouble		m_dRadius1;							/*!< Radius 1. */
	A3DUns8			m_cParameterizationType;		/*!< Parameterization type. */
	A3DSurfBase* m_pCliffSurface0;					/*!< Cliff supporting surface 0. */
	A3DSurfBase* m_pCliffSurface1;					/*!< Cliff supporting surface 1. */
} A3DSurfBlend02Data;

/*!
\brief Populates the \ref A3DSurfBlend02Data structure
\ingroup a3d_srfblend02
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfBlend02Get,(const A3DSurfBlend02* pSrf, A3DSurfBlend02Data* pData));

/*!
\brief Creates an \ref A3DSurfBlend02 from an \ref A3DSurfBlend02Data structure
\ingroup a3d_srfblend02
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfBlend02Create,(const A3DSurfBlend02Data* pData, A3DSurfBlend02** ppSrf));


#endif	/*	__A3D_SRFBLEND02__ */

#ifndef __A3D_SRFBLEND03__
/*!
\defgroup a3d_srfblend03 Blend Surface Type 3
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfBlend03.

For the canonical definition and corresponding parametric equation,
see the "SerializeBlend03" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 
*/

/*!
\brief Blend03 structure
\ingroup a3d_srfblend03
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DBool Struct_not_implemented_____A3DSurfBlend03Data;
	A3DMiscCartesianTransformationData	m_sTrsf;						/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;									/*!< UV Parameterization. */
	
	A3DUns32							m_uiNbOfElement;						/*!< Number of elements. */
	A3DDouble*						m_pdParameters;						/*!< Array of parameters (size = m_uiNbOfElement). */
	A3DInt32*							m_piMultiplicities;					/*!< Array of multiplicities (size = m_uiNbOfElement). */
	A3DVector3dData*				m_pPositions;							/*!< Array of positions (size = 3*m_uiNbOfElement). */
	A3DDouble*						m_pdRail2AnglesV;						/*!< Array of (size = m_uiNbOfElement). */
	A3DVector3dData*				m_pTangent;								/*!< (size = 3*m_uiNbOfElement). */
	A3DDouble*						m_pdRail2DerivativesV;				/*!< (size = m_uiNbOfElement). */
	A3DVector3dData*				m_pSecondDerivatives;				/*!< (size = 3*m_uiNbOfElement). */
	A3DDouble*						m_pdRail2SecondDerivatives;		/*!< (size = m_uiNbOfElement). */
	A3DDouble						m_dRail2ParameterV;					/*!< */
	A3DDouble						m_dTrimVMin;							/*!< */
	A3DDouble						m_dTrimVMax;							/*!< */
	A3DInt32							m_piReserveInt[6];					/*!< Reserved for future use. */
	A3DInt8							m_cReservedChar0;						/*!< Reserved for future use. */
	A3DInt8							m_cReservedChar1;						/*!< Reserved for future use. */
	A3DInt8							m_cReservedChar2;						/*!< Reserved for future use. */
	A3DUns32							m_uiReservedDoublesSize;				/*!< Size of next array. */
	A3DDouble*						m_pdReservedDoubles;					/*!< Reserved for future use. */
} A3DSurfBlend03Data;


/*!
\brief Populates the \ref A3DSurfBlend03Data structure
\ingroup a3d_srfblend03
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
\attention <b>FUNCTION IS NOT IMPLEMENTED YET</b>
*/
A3D_API (A3DStatus, A3DSurfBlend03Get,(const A3DSurfBlend03* pSrf, A3DSurfBlend03Data* pData));

/*!
\brief Creates an \ref A3DSurfBlend03 from an \ref A3DSurfBlend03Data structure
\ingroup a3d_srfblend03
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
\attention <b>FUNCTION IS NOT IMPLEMENTED YET</b>
*/
A3D_API (A3DStatus, A3DSurfBlend03Create,(const A3DSurfBlend03Data* pData, A3DSurfBlend03** ppSrf));


#endif	/*	__A3D_SRFBLEND03__ */

#ifndef __A3D_SRFCONE__
/*!
\defgroup a3d_srfcone Conic Surface
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfCone.

For the canonical definition and corresponding parametric equation,
see the "SerializeCone" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 
*/

/*!
\brief Structure for describing conical surfaces
\ingroup a3d_srfcone
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DDouble m_dRadius;	/*!< Bottom Radius. */
	A3DDouble m_dSemiAngle; /*!< Semi Angle; canonical definition. */
	A3DBool m_bInsideOut; /*!< Unused flag; should be set to false. */
} A3DSurfConeData;

/*!
\brief Populates the \ref A3DSurfConeData structure
\ingroup a3d_srfcone
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfConeGet,(const A3DSurfCone* pSrf, 
												A3DSurfConeData* pData));

/*!
\brief Creates an \ref A3DSurfCone from an \ref A3DSurfConeData structure
\ingroup a3d_srfcone
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfConeCreate,(const A3DSurfConeData* pData, 
													A3DSurfCone** ppSrf));


#endif	/*	__A3D_SRFCONE__ */

#ifndef __A3D_SRFCYLINDRICAL__
/*!
\defgroup a3d_srfcylindrical Cylindrical-Space Surface
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfCylindrical.

For the canonical definition and corresponding parametric equation,
see the "SerializeCylindrical" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement.
*/

/*!
\brief Structure for defining a cylindrical-space surface
\ingroup a3d_srfcylindrical
\version 2.0

A cylindrical-space surface is a surface defined in cylindrical space with these parameters:
\li X stands for R
\li Y stands for Theta
\li Z remains Z
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DSurfBase* m_pBasisSurf;	/*!< Basis surface. Cannot be NULL. */
} A3DSurfCylindricalData;


/*!
\brief Populates the \ref A3DSurfCylindricalData structure
\ingroup a3d_srfcylindrical
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfCylindricalGet,(const A3DSurfCylindrical* pSrf, A3DSurfCylindricalData* pData));

/*!
\brief Creates an \ref A3DSurfCylindrical from an \ref A3DSurfCylindricalData structure
\ingroup a3d_srfcylindrical
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfCylindricalCreate,(const A3DSurfCylindricalData* pData, A3DSurfCylindrical** ppSrf));


#endif	/*	__A3D_SRFCYLINDRICAL__ */

#ifndef __A3D_SRFRULED__
/*!
\defgroup a3d_srfruled Ruled Surface
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfRuled.

For the canonical definition and corresponding parametric equation,
see the "SerializeRuled" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement.

*/

/*!
\brief Ruled surface structure
\ingroup a3d_srfruled
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DCrvBase* m_pFirstCurve;		/*!< Basis first curve. */
	A3DCrvBase* m_pSecondCurve;	/*!< Basis second curve. */
} A3DSurfRuledData;


/*!
\brief Populates the \ref A3DSurfRuledData structure
\ingroup a3d_srfruled
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfRuledGet,(const A3DSurfRuled* pSrf, A3DSurfRuledData* pData));

/*!
\brief Creates an \ref A3DSurfRuled from an \ref A3DSurfRuledData structure
\ingroup a3d_srfruled
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfRuledCreate,(const A3DSurfRuledData* pData, A3DSurfRuled** ppSrf));


#endif	/*	__A3D_SRFRULED__ */

#ifndef __A3D_SRFPIPE__
/*!
\defgroup a3d_srfpipe Pipe Surface
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfPipe.

For the canonical definition and corresponding parametric equation,
see the "SerializePipe" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement.

\note This type is not yet implemented
*/

/*!
\brief Pipe structure
\ingroup a3d_srfpipe
\version 2.0
\note \ref m_pSpine describes curve of centers of circles
\note \ref m_pOrigine describes evolution of 0 parameter along the circle when parsing through spine 
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData	m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;	/*!< UV Parameterization. */
	A3DDouble m_dRadius;		/*!< Radius. Must be greater than 0. */
	A3DCrvBase* m_pSpine;	/*!< Basis spine. Cannot be NULL. */
	A3DCrvBase* m_pOrigine;	/*!< Basis origine. Cannot be NULL. */
} A3DSurfPipeData;


/*!
\brief Populates the \ref A3DSurfPipeData structure
\ingroup a3d_srfpipe
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfPipeGet,(const A3DSurfPipe* pSrf, A3DSurfPipeData* pData));

/*!
\brief Creates an \ref A3DSurfPipe from an \ref A3DSurfPipeData structure
\ingroup a3d_srfpipe
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfPipeCreate,(const A3DSurfPipeData* pData, A3DSurfPipe** ppSrf));


#endif	/*	__A3D_SRFPIPE__ */

#ifndef __A3D_SRFTRANFORM__
/*!
\defgroup a3d_srftransform Transform Surface
\ingroup a3d_srf
\version 2.0

Entity type is \ref kA3DTypeSurfTransform.

For the canonical definition and corresponding parametric equation,
see the "SerializeTransformationSurface" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement.

*/

/*!
\brief Transform surface structure
\ingroup a3d_srftransform
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;								/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DMiscCartesianTransformationData m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;				/*!< Parameterization. */
	A3DMathFct3D* m_pTransfo;							/*!< Transformation to apply to basis curve. */
	A3DSurfBase* m_pBasisSurf;							/*!< Basis Surface. */
} A3DSurfTransformData;


/*!
\brief Populates the \ref A3DSurfTransformData structure
\ingroup a3d_srftransform
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SRF_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfTransformGet,(const A3DSurfTransform* pSrf, A3DSurfTransformData* pData));

/*!
\brief Creates an \ref A3DSurfTransform from an \ref A3DSurfTransformData structure
\ingroup a3d_srftransform
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SRF_CANNOT_CREATE_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfTransformCreate,(const A3DSurfTransformData* pData, A3DSurfTransform** ppSrf));


#endif	/*	__A3D_SRFTRANFORM__ */

#ifndef __A3D_SRFFROMCURVES__
/*!
\defgroup a3d_srffromcurves From Curves Surface
\ingroup a3d_srf
Entity type is \ref kA3DTypeSurfFromCurves.

For the canonical definition and corresponding parametric equation,
see the "SerializeFromCurves" section of the \REF_PRC_SPEC.

\ref A3DUVParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement.
*/

/*!
\brief Surface from curves structure
\ingroup a3d_srffromcurves
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DMiscCartesianTransformationData m_sTrsf;	/*!< Cartesian transformation. */
	A3DUVParameterizationData m_sParam;				/*!< Parameterization. */
	A3DVector3dData	m_sOrigin; /*!< Origine for the surface. */
	A3DCrvBase* m_pFirstCurve;		/*!< Basis first curve. */
	A3DCrvBase* m_pSecondCurve;	/*!< Basis second curve. */
} A3DSurfFromCurvesData;


/*!
\brief Populates the \ref A3DSurfFromCurvesData structure
\ingroup a3d_srffromcurves
\version 2.0
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfFromCurvesGet,(const A3DSurfFromCurves* pSrf, A3DSurfFromCurvesData* pData));

/*!
\brief Creates an \ref A3DSurfFromCurves from an \ref A3DSurfFromCurvesData structure
\ingroup a3d_srffromcurves
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSurfFromCurvesCreate,(const A3DSurfFromCurvesData* pData, A3DSurfFromCurves** ppSrf));

#endif	/*	__A3D_SRFFROMCURVES__ */






#endif	/*	__A3DPRCGEOMETRYSRF_H__ */
