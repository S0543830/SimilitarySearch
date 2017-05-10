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

#ifndef __A3DSDKADVANCEDTOOLS_H__
#define __A3DSDKADVANCEDTOOLS_H__

/*!
\defgroup a3d_evaluate Eval on curves and surfaces
\ingroup a3d_tools_module
*/

/*!
\ingroup a3d_evaluate
\brief Function to get a curve parametric interval

\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvGetInterval, (const A3DCrvBase* pCrv,
													A3DIntervalData* pInterval));

/*!
\ingroup a3d_evaluate
\brief Function to evaluate a point and the derivatives of a curve at a parameter\n
\par Derivatives are stored in the following order:
		  	   \li  With uiNbDerivatives = 0: Point
			   \li  With uiNbDerivatives = 1: Point, First Derivative
			   \li  With uiNbDerivatives = 2: Point, First Derivative, Second Derivative

pPointAndDerivatives size must be equal to (uiNbDerivatives+1):
	 \li size = 1 if uiNbDerivatives=0
	 \li size = 2 if uiNbDerivatives=1;
	 \li size = 3 if uiNbDerivatives=2;

\version 4.0

\warning The number of derivatives must be less than or equal to 2.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DCrvEvaluate,(const A3DCrvBase* pCrv,
												A3DDouble dParameter,
												A3DUns32 uiNbDerivatives,
												A3DVector3dData* pPointAndDerivatives));

/*!
\ingroup a3d_evaluate
\brief Function to evaluate a point and the derivatives of a curve at a parameter, then the normal of this point to each of the given surfaces\n
\par Derivatives are stored in the following order:
				\li  With uiNbDerivatives = 0: Point
				\li  With uiNbDerivatives = 1: Point, First Derivative
				\li  With uiNbDerivatives = 2: Point, First Derivative, Second Derivative

psPointAndDerivatives size must be equal to (uiNbDerivatives+1):
		\li size = 1 if uiNbDerivatives=0
		\li size = 2 if uiNbDerivatives=1;
		\li size = 3 if uiNbDerivatives=2;
psNormal size must be equal to the uiNbSurfaces, the number of given surfaces.
Life time of psPointAndDerivatives and psNormal must be handled by the user.


\version 8.2

\warning The number of derivatives must be less than or equal to 2.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DCrvEvaluatePointAndNormal,(	A3DCrvBase const* psCrv,
													A3DDouble dParameter,
													A3DUns32 uiNbSurfaces,
													A3DSurfBase** ppsSurfaces,
													A3DUns32 uiNbDerivatives,
													A3DVector3dData* psPointAndDerivatives,
													A3DVector3dData* psNormal));

/*!
\ingroup a3d_evaluate
\brief Function to get a surface parametric domain

\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DSrfGetDomain, (const A3DSurfBase* pSrf,
													A3DDomainData* pDomain));

/*!
\ingroup a3d_evaluate
\brief Function to evaluate a point and the derivatives on a surface.
\par
	pPointAndDerivatives size must be equal to (uiNbDerivatives+1)*(uiNbDerivatives+1)
\par
		 Derivatives are stored in the following order:
	 \li if uiNbDerivatives=0,
	 pPointAndDerivatives size must be equal to 1

	 \li if uiNbDerivatives=1,
	 pPointAndDerivatives size must be equal to 4

<pre>
       _ 2D array representation:
                         v derivs
                      |   0   |   1   |
                -----------------------
                   0  | Point |   V   |
      u derivs  -----------------------
                   1  |  U    |       |
</pre>
<pre>
       _ 1D array representation:
              0 |   1   |   2   |    3   |
          --------------------------------
          Point |   V   |   U   |        |
</pre>
	 \li if uiNbDerivatives=2,
	 pPointAndDerivatives size must be equal to 9

<pre>
       _ 2D array representation:
	                            v derivs
                      |   0   |   1   |   2   |
                -------------------------------
                   0  | Point |   V   |   V2  |
                -------------------------------
     u derivs      1  |  U    |   UV  |       |
                -------------------------------
                   2  |  U2   |       |       |
</pre>
<pre>
       _ 1D array representation:
              0 |   1   |   2   |    3   |   4   |   5   |    6   |   7   |   8   |
          -------------------------------------------------------------------------
          Point |   V   |   V2  |    U   |   UV  |       |   U2   |       |       |
</pre>

\version 4.0

\warning The number of derivatives must be less or equal to 2.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n

*/

A3D_API (A3DStatus, A3DSurfEvaluate,(	const A3DSurfBase* pSurf,
													const A3DVector2dData* pUVParameter,
													A3DUns32 uiNbDerivatives,
													A3DVector3dData* pPointAndDerivatives));




/*!
\ingroup a3d_evaluate
\brief Function to determine if a surface is degenerated at a point

\version 9.0

\param [in] pSurf The input surface.
\param [in] pUVParameter The coordinates of the point.
\param [in] dTolerance The tolerance of the test.
\param [out] pbIsDegenerated The returned value.
\param [out] pbUDirection The direction of the degeneracy if a degeneracy is detected (true = U direction, and false = V direction).

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
*/
A3D_API(A3DStatus, A3DSurfIsDegenerated, (	const A3DSurfBase* pSurf,
											const A3DVector2dData* pUVParameter,
											A3DDouble dTolerance,
											A3DBool* pbIsDegenerated,
											A3DBool* pbUDirection));

/*!
\ingroup a3d_evaluate
\brief Function to determine if a surface is G1 discontinuous at a point

\version 9.0

\param [in] pSurf The input surface.
\param [in] pUVParameter The coordinates of the point.
\param [in] dAngleTolerance The derivative angle tolerance.
\param [out] pbUG1Continuous The returned value for u direction.
\param [out] pbVG1Continuous The returned value for v direction.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
*/
A3D_API(A3DStatus, A3DSurfIsG1Continuous, (	const A3DSurfBase* pSurf,
											const A3DVector2dData* pUVParameter,
											A3DDouble dAngleTolerance,
											A3DBool* pbUG1Continuous,
											A3DBool* pbVG1Continuous));

/*!
\version 5.0
\enum A3DEAnalyticType
\ingroup a3d_evaluate
\brief Tells what kind of curve has been created by A3DGetCurveAsAnalytic
*/

typedef enum {
	kA3DAnalyticNone,
	kA3DAnalyticCircle,
	kA3DAnalyticAlreadyCircle,
	kA3DAnalyticLine,
	kA3DAnalyticAlreadyLine,

	kA3DAnalyticCone,
	kA3DAnalyticAlreadyCone,
	kA3DAnalyticCylinder,
	kA3DAnalyticAlreadyCylinder,
	kA3DAnalyticPlane,
	kA3DAnalyticAlreadyPlane,
	kA3DAnalyticSphere,
	kA3DAnalyticAlreadySphere,
	kA3DAnalyticTorus,
	kA3DAnalyticAlreadyTorus
} A3DEAnalyticType;


/*!
\ingroup a3d_evaluate
\brief Function to get curves as analytic (line or circle) according to a certain tolerance.
Use \ref A3DEntityDelete to delete the analytic curve after using it.
\version 5.0
\warning DEPRECATED: use \ref A3DSimplifyCurveWithAnalytics

\return \ref A3D_SUCCESS if an analytic has been created \n
\return \ref A3D_ERROR \n

*/


A3D_API (A3DStatus, A3DGetCurveAsAnalytic,(	const A3DCrvBase* pCurve,
															double dTol,
															A3DCrvBase** pAnalyticCurve,
															A3DEAnalyticType* peAnalyticType));

/*!
\ingroup a3d_evaluate
\brief Function to get curves as analytic (line or circle) according to a certain tolerance.
Use \ref A3DEntityDelete to delete the analytic curve after using it.
Recognized curve type are:\n
\ref a3d_crvline
\ref a3d_crvcircle
If uNbRecognizedType and pOptRecognizedType are defined, \ref A3DSimplifyCurveWithAnalytics recognizes only given types.
\version 7.0

\param [in, out] pCurve The input curve.
\param [in] dTol The tolerance.
\param [in] uNbRecognizedType Size of array pOptRecognizedType.
\param [in] pOptRecognizedType Optional type of curve we want to recognize.
\param [out] pAnalyticCurve The new analytic curve. \warning must be deleted by the user.
\param [out] peAnalyticType The type of analytic curve.

\return \ref A3D_SUCCESS if an analytic has been created \n
\return \ref A3D_ERROR \n

*/
A3D_API (A3DStatus, A3DSimplifyCurveWithAnalytics,(const A3DCrvBase* pCurve,
																	A3DDouble dTol,
																	A3DUns32 uNbRecognizedType,
																	A3DEEntityType const *pOptRecognizedType,
																	A3DCrvBase** pAnalyticCurve,
																	A3DEAnalyticType* peAnalyticType));

/*!
\ingroup a3d_evaluate
\brief Function to get curves as analytic (line or circle) according to a certain tolerance
Try to use UV curves from Edges if exist, otherwise use 3D Curves.
Use \ref A3DEntityDelete to delete the analytic curve after using it.
\version 5.0
\warning DEPRECATED: use \ref A3DSimplifyCurveWithAnalyticsFromCoEdge

\return \ref A3D_SUCCESS if an analytic has been created \n
\return \ref A3D_ERROR \n

*/

A3D_API (A3DStatus, A3DGetCurveAsAnalyticFromCoEdge,(	const A3DTopoCoEdge* pCoEdge,
																		double dTol,
																		A3DCrvBase** pAnalyticCurve,
																		A3DEAnalyticType *peAnalyticType));

/*!
\ingroup a3d_evaluate
\brief Function to get curves as analytic (line or circle) according to a certain tolerance
Try to use 3D curves from Edges if exist, otherwise use UV Curves on CoEdge.
Use \ref A3DEntityDelete to delete the analytic curve after using it.
Recognize curve type are:\n
\ref a3d_crvline
\ref a3d_crvcircle
If uNbRecognizedType and pOptRecognizedType are defined, \ref A3DSimplifyCurveWithAnalytics recognizes only given types.
\version 7.0

\param [in] pCoEdge The input coEdge.
\param [in] dTol The tolerance.
\param [in] uNbRecognizedType Size of array pOptRecognizedType.
\param [in] pOptRecognizedType Optional type of curve we want to recognize.
\param [out] pAnalyticCurve The new analytic curve. \warning must be deleted by the user.
\param [out] peAnalyticType The type of analytic curve.

\return \ref A3D_SUCCESS if an analytic has been created \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DSimplifyCurveWithAnalyticsFromCoEdge,(	const A3DTopoCoEdge* pCoEdge,
																					A3DDouble dTol,
																					A3DUns32 uNbRecognizedType,
																					A3DEEntityType const *pOptRecognizedType,
																					A3DCrvBase** pAnalyticCurve,
																					A3DEAnalyticType *peAnalyticType));

/*!
\ingroup a3d_evaluate
\brief Function to get surface as analytic according to a certain tolerance.
Use \ref A3DEntityDelete to delete the analytic surface after using it.
Recognized surface type are:\n
\ref a3d_srfcone
\ref a3d_srfcylinder
\ref a3d_srfplane
\ref a3d_srfsphere
\ref a3d_srftorus
\version 5.0

\warning DEPRECATED: use \ref A3DSimplifySurfaceWithAnalytics

\param [in] pSrf The input surface
\param [in] dTol Tolerance
\param [out] pAnalyticSurface The new analytic surface. \warning must be deleted by the user
\param [out] peAnalyticType The type of analytic surface

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DGetSurfaceAsAnalytic, (	A3DSurfBase const * pSrf,
																double dTol,
																A3DSurfBase** pAnalyticSurface,
																A3DEAnalyticType *peAnalyticType) );


/*!
\ingroup a3d_evaluate
\brief Function to get surface as analytic according to a certain tolerance.
Use \ref A3DEntityDelete to delete the analytic surface after using it.
Recognized surface type are:\n
\ref a3d_srfcone
\ref a3d_srfcylinder
\ref a3d_srfplane
\ref a3d_srfsphere
\ref a3d_srftorus
If uNbRecognizedType and pOptRecognizedType are defined, \ref A3DSimplifySurfaceWithAnalytics recognizes only given types.
\version 7.0

\param [in] pSrf The input surface.
\param [in] dTol Tolerance.
\param [in] uNbRecognizedType Size of array pOptRecognizedType.
\param [in] pOptRecognizedType Optional type of surface we want to recognize.
\param [out] pAnalyticSurface The new analytic surface. \warning must be deleted by the user.
\param [out] peAnalyticType The type of analytic surface.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DSimplifySurfaceWithAnalytics, (A3DSurfBase const * pSrf,
																		A3DDouble dTol,
																		A3DUns32 uNbRecognizedType,
																		A3DEEntityType const *pOptRecognizedType,
																		A3DSurfBase** pAnalyticSurface,
																		A3DEAnalyticType *peAnalyticType) );

/*!
\ingroup a3d_projection
\brief This function projects a point on a curve
The number of returned solutions is given by puiNbSolutions and for each one,
ppdSolutionParameter and ppdSolutionDistance arrays give the parameter on the curve
and the spatial distance between pPointToProject and the solution (on the curve).
\version 5.0

\param [in] pCrv The input curve.
\param [in] pPointToProject The input point to project on curve.
\param [out] puiNbSolutions The number of returned solutions.
\param [out] ppdSolutionParameter Array of parameters on the curve.
\param [out] ppdSolutionDistance Array of spatial distances between pPointToProject and the solution (on the curve).

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n

*/
A3D_API (A3DStatus, A3DCrvProjectPoint, (const A3DCrvBase* pCrv,
		 const A3DVector3dData *pPointToProject,
		 A3DUns32* puiNbSolutions,
		 A3DDouble** ppdSolutionParameter,
		 A3DDouble** ppdSolutionDistance));


/*!
\ingroup a3d_projection
\brief This function projects a point on a surface
The number of returned solutions is given by puiNbSolutions and for each one,
ppdSolutionParameters and ppdSolutionDistance arrays give the 2D point in surface parametric domain
and the spatial distance between pPointToProject and the solution (on the surface).
\version 5.0

\param [in] pSurf The input surface.
\param [in] pPointToProject The input point to project on surface.
\param [out] puiNbSolutions The number of returned solutions.
\param [out] ppdSolutionParameters Array of 2D points in the surface parametric domain.
\param [out] ppdSolutionDistance Array of spatial distances between pPointToProject and the solution (on the surface).

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n

*/

A3D_API (A3DStatus, A3DSurfProjectPoint,(	const A3DSurfBase* pSurf,
		 const A3DVector3dData *pPointToProject,
		 A3DUns32* puiNbSolutions,
		 A3DVector2dData** ppdSolutionParameters,
		 A3DDouble** ppdSolutionDistance));

/*!
\ingroup a3d_projection
\brief This function projects a point on a curve with a guess parameter pdSolutionParameter
and pdSolutionDistance give the parameter on the curve and the spatial distance
between pPointToProject and the solution (on the curve).
\version 5.0

\param [in] pCrv The input curve.
\param [in] pPointToProject The input point to project on curve.
\param [in] dGuessParameter The input guess parameters.
\param [out] pbFindSolution Result status.
\param [out] pdSolutionParameter parameter solution.
\param [out] pdSolutionDistance spatial distance (optional).

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_CRV_INVALID_PARAMETER \n
\return \ref A3D_ERROR \n

*/
A3D_API (A3DStatus, A3DCrvLocalProjectPoint, (	const A3DCrvBase* pCrv,
																const A3DVector3dData *pPointToProject,
																A3DDouble dGuessParameter,
																A3DBool* pbFindSolution,
																A3DDouble* pdSolutionParameter,
																A3DDouble* pdSolutionDistance));

/*!
\ingroup a3d_projection
\brief This function projects a point on a surface with a guess parameter pSolutionParameter
and pdSolutionDistance give the 2D point in surface parametric domain and the spatial distance
between pPointToProject and the solution (on the surface).

pGuessPoint must be contained by the domain of the surface.

\version 5.0

\param [in] pSurf The input surface.
\param [in] pPointToProject The input point to project on surface.
\param [in] pGuessPoint The input guess parameters.
\param [out] pbFindSolution Result status.
\param [out] pSolutionParameter parameter solution.
\param [out] pdSolutionDistance spatial distance (optional).

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_SRF_INVALID_PARAMETERS \n
\return \ref A3D_ERROR \n

*/
A3D_API (A3DStatus, A3DSurfLocalProjectPoint,(	const A3DSurfBase* pSurf,
																const A3DVector3dData *pPointToProject,
																const A3DVector2dData *pGuessPoint,
																A3DBool* pbFindSolution,
																A3DVector2dData* pSolutionParameter,
																A3DDouble* pdSolutionDistance));

/*!
\ingroup a3d_evaluate
\brief Function to evaluate a normal on a surface

\param [in] pSurf The input surface.
\param [in] pUVParameter The input UV point to evaluate the normal of the surface.
\param [out] pNormal The normal of the surface at the UV parameter.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n

*/
A3D_API (A3DStatus, A3DSurfEvaluateNormal,(	const A3DSurfBase* pSurf,
															const A3DVector2dData* pUVParameter,
															A3DVector3dData* pNormal) );


/*!
\defgroup a3d_Healing Healing
\ingroup a3d_tools_module
\version 6.0

Healing functions for model file or BRepData.
\sa A3DAsmModelFileSew, A3DSewBrep
*/

/*!
\ingroup a3d_Healing
\brief Function to sew multiple B-rep data structures.
\version 5.2

\param [in] p An array of A3DRiBrepModel* to sew.
\param [in] uNbBrepModels The number of A3DRiBrepModel* in p.
\param [in] dTolerance The maximum tolerance for the sewing (in file unit).
\param [out] pBrepModelsOut The output array of sewed A3DRiBrepModel*.
\param [out] uNbBrepOut The number of A3DRiBrepModel* in pBrepModelsOut.

\return \ref A3D_SUCCESS \n
\return \ref A3D_ERROR \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n

*/
A3D_API (A3DStatus, A3DSewBrep,(A3DRiBrepModel*** p,
			A3DUns32 uNbBrepModels,
			double dTolerance,
			A3DRiBrepModel*** pBrepModelsOut,
			A3DUns32 * const uNbBrepOut) );


/*!
\ingroup a3d_Healing
\brief Function to sew one model file.
\version 6.0

\param [in] ppModelFile The model file to sew.
\param [in] dToleranceInMM The maximum tolerance for the sewing (in mm).

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_NULL \n

*/
A3D_API (A3DStatus, A3DAsmModelFileSew, (A3DAsmModelFile** ppModelFile,
			A3DDouble dToleranceInMM) );

/*!
\defgroup a3d_UV_Classification UV Classification
\ingroup a3d_tools_module
\version 5.2

Entity type is \ref kA3DTypeTopoShell
\sa A3DTopoShell, A3DTopoShellData, A3DTopoShellGet, A3DTopoShellCreate
*/

/*!
\brief A3DFaceUVPointInsideManager structure
\ingroup a3d_UV_Classification
\version 5.2

*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiFaceSize;				/*!< Number of faces in the cache manager. */
} A3DFaceUVPointInsideManagerData;


/*!
\brief Creates an \ref A3DFaceUVPointInsideManager from an \ref A3DFaceUVPointInsideManagerData structure
\ingroup a3d_UV_Classification
\version 5.2

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DFaceUVPointInsideManagerCreate,(	A3DFaceUVPointInsideManagerData const * pData,
																			A3DFaceUVPointInsideManager ** pManager) );

/*!
\brief Deletes an \ref A3DFaceUVPointInsideManager
\ingroup a3d_UV_Classification
\version 5.2

\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DFaceUVPointInsideManagerDelete, ( A3DFaceUVPointInsideManager * pManager) );


/*!
\ingroup a3d_UV_Classification
\brief This function projects a UV point on a face, and return if it's inside or not.
puiUVInFace gives the result: 0 if the point is outside the face, and 1 if it's inside.
dTol3D is used to check if a UV point is on edges. If it's set to zero
and the point is not inside the face but potentially on its edges, the tolerance check will not happen.
\version 5.2

\param [in] pManager The face manager.
\param [in] psFace The input face.
\param [in] pUVParameter The input UV Point.
\param [in] dTol3D Tolerance to check if the UV point is on the edge.
\param [out] puiUVInFace Status of the UV point on the face. 0 is outside, 1 is inside.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_ENTITY_TYPE
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_TOPO_GEOMETRY_MISSING - it's missing UV curves \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DFaceUVPointInside, (	A3DFaceUVPointInsideManager *pManager,
															A3DTopoFace const *psFace,
															A3DVector2dData const * pUVParameter,
															A3DDouble dTol3D,
															A3DUns8 * puiUVInFace) );


/*!
\defgroup a3d_ProjectPointCloud Project Point Cloud
\ingroup a3d_tools_module
\version 6.1

ProjectPointCloud functions for model file.
\sa A3DProjectPointCloud
*/

/*!
\brief A3DProjectedPointCloudData structure
\ingroup a3d_ProjectPointCloud
\version 6.1

*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bSuccess;			/*!< Store if the point has been projected successfully or not. */
	A3DDouble m_dDist;			/*!< Distance between the point to project and the projected point. */
	A3DVector3dData m_sPt;		/*!< 3D projected point. */
	A3DInt32 m_iBRepIndice;		/*!< Index of the RIBRepModel where the point has been projected. */
	A3DInt32 m_iFaceIndice;		/*!< Index of the face where the point has been projected. */
	A3DInt32 m_iEdgeIndice;		/*!< Index of the edge where the point has been projected. */
	A3DVector2dData m_sUV;		/*!< 2D projected point. */
	A3DDouble m_dEdgeParameter;	/*!< Parameter on edge curve or on coedge curve if 3D curve is not present. */
	A3DBool m_bIsInFace;		/*!< Tell if a point which is on edge is also inside or outside face. */
}A3DProjectedPointCloudData;


/*!
\ingroup a3d_ProjectPointCloud
\brief Function to project Point Cloud on BrepModel
\version 6.1

\param [in] uRiBrepModelSize Number of BrepModels in pRiBrepModel.
\param [in] pRiBrepModel Array of Brep Models.
\param [in] uPointCloudSize Number of points in pPointCloudToProject.
\param [in] pPointCloudToProject Point cloud to project.  This point cloud must be in the same coordinate system as the BrepData structures stored in BrepModel.
\param [in] bUseExactComputation Flag to use exact topology. When this flag is false, the algorithm drops the
point cloud on the faceted geometry, otherwise, the exact topology is used.
\param [in] uNbThreads Number of threads wanted. 0 means non multi-thread. Please avoid setting a number of threads larger than the number of CPU cores.
\param [out] ppProjectedPointCloud Point cloud projected. ppProjectedPointCloud is automatically allocated by
A3DProjectPointCloud.
It must be freed with the custom free memory callback.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
\return \ref A3D_BREPDATA_INCONSISTENT_DATA if bUseExactComputation is set and if is missing \ref A3DTopoBrepData \n
\return \ref A3D_TOPO_GEOMETRY_MISSING if bUseExactComputation is set and if is missing UV curves \n
*/


A3D_API (A3DStatus, A3DProjectPointCloud,(unsigned int uRiBrepModelSize,
														A3DRiBrepModel** pRiBrepModel,
														A3DUns32 uPointCloudSize,
														A3DVector3dData* pPointCloudToProject,
														A3DBool bUseExactComputation,
														A3DUns32 uNbThreads,
														A3DProjectedPointCloudData** ppProjectedPointCloud ));


class A3DMatrix4x4;

/*!
\brief A3DProjectPointCloudManagerDataFromRI sructure
\ingroup a3d_ProjectPointCloud
\version 8.1

*/
typedef struct
{
	A3DUns16							m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32							m_uRepItemSize;	/*!< m_uRepItemSize number of element in pRepItems. */
	A3DRiRepresentationItem**	m_pRepItems;		/*!< pRepItem Array of representation item. Only \ref A3DRiBrepModel is supported*/
	A3DDouble **					m_pOptPlacements;	/*!< Optional array of representation item placements (16 A3DDouble matrix). */
	A3DBool							m_bUseExactComputation; /*!< Flag to use exact topology. When this flag is false, the algorithm drops the
																		point cloud on the faceted geometry, otherwise, the exact topology is used. */
} A3DProjectPointCloudManagerDataFromRI;


/*!
\ingroup a3d_ProjectPointCloud
\brief Create a Point Cloud Manager from a set of \ref A3DRiRepresentationItem with matrix placement.
\version 8.1

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
\return \ref A3D_BREPDATA_INCONSISTENT_DATA if bUseExactComputation is set and if is missing \ref A3DTopoBrepData \n
\return \ref A3D_TOPO_GEOMETRY_MISSING if bUseExactComputation is set and if is missing UV curves \n
*/
A3D_API (A3DStatus, A3DProjectPointCloudManagerCreateFromRI,(	A3DProjectPointCloudManagerDataFromRI *pData,
																					A3DProjectPointCloudManager ** pManager));

/*!
\ingroup a3d_ProjectPointCloud
\brief Create a Point Cloud Manager from a \ref A3DAsmModelFile
\version 8.1

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
\return \ref A3D_BREPDATA_INCONSISTENT_DATA if bUseExactComputation is set and if is missing \ref A3DTopoBrepData \n
\return \ref A3D_TOPO_GEOMETRY_MISSING if bUseExactComputation is set and if is missing UV curves \n
*/
A3D_API (A3DStatus, A3DProjectPointCloudManagerCreateFromModelFile,(	A3DAsmModelFile *pModelFile,
																							A3DProjectPointCloudManager ** pManager));

/*!
\brief Deletes an \ref A3DProjectPointCloudManager
\ingroup a3d_ProjectPointCloud
\version 8.1

\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DProjectPointCloudManagerDelete,( A3DProjectPointCloudManager * pManager));

/*!
\ingroup a3d_ProjectPointCloud
\brief Function to project Point Cloud on BrepModel with a \ref A3DProjectPointCloudManager
\version 8.1

\param [in] pManager \ref A3DProjectPointCloudManager created by \ref A3DProjectPointCloudManagerCreateFromModelFile function.
\param [in] uPointCloudSize Number of points in pPointCloudToProject.
\param [in] pPointCloudToProject Point cloud to project.  This point cloud must be in the same coordinate system as the BrepData structures stored in BrepModel.
\param [in] bUseExactComputation Flag to use exact topology. When this flag is false, the algorithm drops the
point cloud on the faceted geometry, otherwise, the exact topology is used.
\param [in] uNbThreads Number of threads wanted. 0 means non multi-thread. Please avoid setting a number of threads larger than the number of CPU cores.
\param [in] dInsidePointEdgeTolerance Tolerance used to check if projection point which is inside a face is on edge.
\param [out] ppProjectedPointCloud Point cloud projected. ppProjectedPointCloud is automatically allocated by
A3DProjectPointCloud.
It must be freed with the custom free memory callback.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DProjectPointCloud2,(	A3DProjectPointCloudManager * pManager,
															A3DUns32 uPointCloudSize,
															A3DVector3dData* pPointCloudToProject,
															A3DBool bUseExactComputation,
															A3DUns32 uNbThreads,
															A3DDouble dInsidePointEdgeTolerance,
															A3DProjectedPointCloudData** ppProjectedPointCloud ));

/*!
\defgroup a3d_ComputeSection Compute Section
\ingroup a3d_tools_module
\version 6.1

Compute section functions for model file.
\sa A3DComputePlanarSectionOnRepresentationItem
\sa A3DComputePlanarSectionOnModelFile
*/

/*!
\brief A3DPlanarSectionData structure
\ingroup a3d_ComputeSection
\version 7.0
*/
typedef struct
{
	A3DUns16 			m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DVector3dData	m_sOrigin;			/*!< Section plane origin. */
	A3DVector3dData	m_sDirection;		/*!< Section plane normal direction. */
	A3DBool				m_bColor;			/*!< Color to apply to the to section curves. */
	A3DBool				m_bCreateFaces;		/*<! Create section faces or not. */
} A3DPlanarSectionData;


/*!
\ingroup a3d_ComputeSection
\brief Function to compute plane section on BrepModel
\version 7.0

\param [in] pRiBrepModel B-rep models.
\param [in] psSectionParametersData Parameters of the planar section.

\param [out] ppRISectionResults Array of section curves. ppRISectionResults is automatically allocated by A3DComputePlanarSectionOnRepresentationItem. It has to be freed with a call to A3DComputePlanarSectionOnRepresentationItem(NULL, psSectionParametersData, ppRISectionCurvesis).

\return \ref A3D_SUCCESS \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DComputePlanarSectionOnRepresentationItem,(	A3DRiBrepModel const * pRiBrepModel,
																						A3DPlanarSectionData const * psSectionParametersData,
																						A3DRiSet ** ppRISectionResults));


/*!
\ingroup a3d_ComputeSection
\brief Function to compute plane section on ModelFile
\version 7.0

\param [in] pModelFile Model file.
\param [in] psSectionParametersData Parameters of the planar section.

\param [out] pNumberOfSections Number of A3DRiSets.
\param [out] pppRISectionElements Array of A3DRiSets. ppRISectionElements is automatically allocated by A3DComputePlanarSectionOnModelFile. It has to be freed with a call to A3DComputePlanarSectionOnModelFile(NULL, psSectionParametersData, pNumberOfSections, ppRISectionElements).

\return \ref A3D_SUCCESS \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DComputePlanarSectionOnModelFile,(	A3DAsmModelFile const * pModelFile,
																			A3DPlanarSectionData const * psSectionParametersData,
																			A3DUns32 * pNumberOfSections,
																			A3DRiSet*** pppRISectionElements));


/*!
\ingroup a3d_CurveLength
\brief Function to compute the length of a curve (optionally restricted to an interval)
\version 7.0

\param [in] pCrv The curve: \ref A3DCrvBase.
\param [in] pOptInterval The interval of restriction of the curve (if NULL, the natural interval of the curve will be used).

\param [out] pdLength The length of the curve.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DCurveLength,(	const A3DCrvBase* pCrv,
										A3DIntervalData* pOptInterval,
										A3DDouble* pdLength));

/*!
\defgroup a3d_CompareFaces Compare faces
\ingroup a3d_tools_module
\version 7.0

Function to compare the faces of two groups of A3DRiBrepModel.
\sa A3DCompareFaces
\sa A3DCompareFacesInBrepModels
*/

/*!
\brief A3DCompareInputData structure that contains input data of \ref A3DCompareFaces.
\ingroup a3d_CompareFaces
\version 7.0
*/
typedef struct
{
	A3DUns16 			m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble			m_dTol;			/*!< maximum distance between two matching faces. */

	A3DUns32				m_uiOldRiBrepModelsSize;	/*!< Size of next array. */
	A3DRiBrepModel const **	m_ppOldRiBrepModels;		/*!< Array of RiBrepModel of the old group. */
	A3DMatrix4x4 *			m_pOldRiBrepModelPlacements;/*!< Array of RiBrepModel placements of the old group. */

	A3DUns32				m_uiNewRiBrepModelsSize;	/*!< Size of next array. */
	A3DRiBrepModel const **	m_ppNewRiBrepModels;		/*!< Array of RiBrepModel of the new group. */
	A3DMatrix4x4 *			m_pNewRiBrepModelPlacements;/*!< Array of RiBrepModel placements of the new group. */

} A3DCompareInputData;

/*!
\brief A3DCompareOutputData structure that contains result data of \ref A3DCompareFaces or \ref A3DCompareFacesInBrepModels.
\ingroup a3d_CompareFaces
\version 7.0
*/
typedef struct
{
	A3DUns16 		m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */

	A3DUns32		m_uiOldFaceSize;	/*!< Size of next array. */
	A3DTopoFace	**	m_pOldFace;			/*!< Array of old faces. */
	A3DBool  *		m_pOldFaceMatch;	/*!< Array of old status: true means every point of this face matches a face of the other group. */

	A3DUns32		m_uiNewFaceSize;	/*!< Size of next array. */
	A3DTopoFace **	m_pNewFace;			/*!< Array of new faces. */
	A3DBool  *		m_pNewFaceMatch;	/*!< Array of new status: true means every point of this face matches a face of the other group. */

	A3DRiSet *			m_pResultRiSet; /*!< RiSet containing the resulting data: faces with different colors according to their status */
										/*!< and also faceted data that represents subparts of the original faces to better understand what's different */
										/*!< between the two groups. */

	A3DAsmModelFile *	m_pResultAsmModeFile;	/*!< An A3DAsmModelFile that contains the previous RiSet. The user can directly export it to PRC for example */

} A3DCompareOutputData;



/*!
\ingroup a3d_CompareFaces
\brief Function to compare the faces of two groups of A3DRiBrepModel.
This function will detect if every points in a face of the first group (referenced as group of the old faces) can be projected to
one of the faces of the other group (referenced as group of the new faces) within the given tolerance.
This is useful for exemple to understand what has changed in a part between two versions: a hole has been added, an edge has been blended.

\version 7.0

\param [in] pInput pointer to a \ref A3DCompareInputData that contains input data.

\param [out] pOutput pointer to a \ref A3DCompareOutputData that contains returned data.
It has to be freed by calling again \ref A3DCompareFaces with NULL as input structure pointer.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DCompareFaces,(	A3DCompareInputData * pInput,
										A3DCompareOutputData * pOutput));


/*!
\ingroup a3d_CompareFaces
\brief Function to compare the faces of two \ref A3DAsmModelFile.
This is the same as \ref A3DCompareFaces except that A3DRiBrepModel will be found by traversing the two \ref A3DAsmModelFile.
\version 7.0

\param [in] pOldModelFile a \ref A3DAsmModelFile containing the first group of A3DRiBrepModel.
\param [in] pNewModelFile a \ref A3DAsmModelFile containing the second group of A3DRiBrepModel.
\param [in] dToleranceInMM maximum distance between two matching faces

\param [out] pOutput pointer to a \ref A3DCompareOutputData that contains returned data.
It has to be freed by calling again \ref A3DCompareFacesInBrepModels with NULL as input A3DAsmModelFile pointers.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API (A3DStatus, A3DCompareFacesInBrepModels,(	A3DAsmModelFile * pOldModelFile,
													A3DAsmModelFile * pNewModelFile,
													A3DDouble dToleranceInMM,
													A3DCompareOutputData * pOutput));


/*!
\ingroup a3d_ComputeSection
\version 8.2
*/
typedef struct
{
	A3DUns16 			m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32			m_uiPointSize;			/*!< Size of next array. */
	A3DVector3dData *	m_pPoints;				/*!< Array of points witch define profile (must be in same plane). */
	A3DVector3dData		m_sExtrudeDirection;	/*!< Extrude vector direction. Normal of the plan contains pofile */
	A3DVector3dData		m_sProfileNormal;		/*!< Normal to the profile section at the first point */
} A3DMultiPlanarSectionData;


/*!
\ingroup a3d_ComputeSection
\brief Function to compute the result of a section with serveral plane on a set of \ref A3DRiRepresentationItem
\version 8.2

Call A3DCutWithMultiPlanarSectionOnRepresentationItems( 0, NULL, NULL, NULL, pNumberOfRepItems, pppRIRepresentationItem, pppRIPlanarSections)
to release pppRIRepresentationItem and pppRIPlanarSections data

\param [in] uiNbRepItems Number of \ref A3DRiRepresentationItem.
\param [in] apRepItems set of \ref A3DRiRepresentationItem.
\param [in] pOptPlacements Optional set of representation item placements (16 A3DDouble matrix).
\param [in] psSectionParametersData define the section to use.
\param [out] pNumberOfRepItems Number of \ref A3DRiRepresentationItem in pppRIRepresentationItem and pppRIPlanarSections array.
\param [out] pppRIRepresentationItem  \ref A3DRiRepresentationItem corresponding to the boolean section results. Can be NULL if a \ref A3DRiRepresentationItem if fully cutted by the section.
\param [out] pppRIPlanarSections  \ref A3DRiRepresentationItem corresponding to planar section for each \ref A3DRiRepresentationItem

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA \n
\return \ref A3D_ERROR \n
*/
A3D_API(A3DStatus, A3DCutWithMultiPlanarSectionOnRepresentationItems, (	A3DUns32 uiNbRepItems,
																		A3DRiRepresentationItem const ** apRepItems,
																		A3DDouble ** pOptPlacements,
																		A3DMultiPlanarSectionData const * psSectionParametersData,
																		A3DUns32 * pNumberOfRepItems,
																		A3DRiRepresentationItem*** pppRIRepresentationItem,
																		A3DRiRepresentationItem*** pppRIPlanarSections));


/*!
\ingroup a3d_ComputeSection
\brief Function to compute the result of a section with serveral plane on a \ref A3DAsmModelFile
\version 8.2

Call A3DCutWithMultiPlanarSectionOnModelFile( NULL, pOptMrkRView, psSectionParametersData, NULL, pNumberOfRepItems, pppRIRepresentationItem, pppRIPlanarSections)
to release pppRIRepresentationItem and pppRIPlanarSections data

If pOptMrkRView is a cutting view, psSectionParametersData can be set to NULL.
In this case, cutting planes contains in pOptMrkRView are use.
Planes must to ordained, and set a profile, if not an \ref A3D_TOOLS_INVALID_SECTION_PLANE error is returned.

\param [in] pModelFile Number of BrepModels in pRiBrepModel.
\param [in] pOptMrkRView optional \ref A3DMkpView (filter and/or move entities).
\param [in] psSectionParametersData define the section to use (can be NULL if pOptMrkRView is a cutting view).
\param [out] pNumberOfRepItems Number of \ref A3DRiRepresentationItem in pppRIRepresentationItem and pppRIPlanarSections array.
\param [out] pppRIRepresentationItem  \ref A3DRiRepresentationItem corresponding to the sectionresults. Can be NULL if a \ref A3DRiRepresentationItem if fully cutted by the section.
\param [out] pppRIPlanarSections  \ref A3DRiRepresentationItem corresponding to planar section for each \ref A3DRiRepresentationItem

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA \n
\return \ref A3D_ERROR \n
\return \ref A3D_TOOLS_INVALID_SECTION_PLANE\n
*/
A3D_API(A3DStatus, A3DCutWithMultiPlanarSectionOnModelFile, (	A3DAsmModelFile const * pModelFile,
																A3DMkpView const * pOptMrkRView,
																A3DMultiPlanarSectionData const * psSectionParametersData,
																A3DUns32 * pNumberOfRepItems,
																A3DRiRepresentationItem*** pppRIRepresentationItem,
																A3DRiRepresentationItem*** pppRIPlanarSections));// A3DSectionRepresentationItemData ** ppRiSectionData));

/*!
\defgroup a3d_HLR_Compute Compute HLR
\ingroup a3d_tools_module
\version 8.1

Compute HLR functions for model file.
\sa A3DComputeOthoHLROnRepresentationItem
\sa A3DComputeOrthoHLROnModelFile
*/

/*!
\brief A3DHLRViewPlaneData structure
\ingroup a3d_ComputeHLR
\version 8.1
*/
typedef struct
{
	A3DUns16	m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble	m_adOrigin[3];  	/*!< Origin of the projection plane.*/
	A3DDouble	m_adAxis1[3];		/*!< Horizontal axis and dimension of plane */
	A3DDouble	m_adAxis2[3];		/*!< Vertical axis and dimension of plane */
	A3DBool		m_bUseClipBox;		/*!< Is true, length of horizontal axis, and vertical axis are used to clip generated curve */
} A3DHLRViewPlaneData;


/*!
\defgroup a3d_hlr_curve_type Type of HLR curves result.
\ingroup a3d_HLR_Compute
\version 8.1
@{
*/
#define A3D_HLR_TYPE_UNKNOWN				0 /*!< Unknown type*/
#define A3D_HLR_TYPE_EDGE					1 /*!< curve is a edge in the \ref A3DRiRepresentationItem input */
#define A3D_HLR_TYPE_SILHOUETTE				2 /*!< curve is a silhouette */
#define A3D_HLR_TYPE_SECTION				3 /*!< curve is a section of previous boolean operation*/
#define A3D_HLR_TYPE_SILHOUETTE_SECTION		4 /*!< curve is a silhouette and a section of previous boolean operation*/
/*!
@} <!-- end of a3d_hlr_curve_type -->
*/

/*!
\brief A3DHLRCurveData structure
\ingroup a3d_HLR_Compute
\version 8.2

\ref m_psTopoEdge, \ref m_psTopoFirstFace and \ref m_psTopoSecondFace are part of the \ref A3DRiRepresentationItem of \ref A3DHLRRepresentationItemData.
If \ref m_bFirstFaceIsSection (respectivly \ref m_bSecondFaceIsSection) is set to true, then \ref m_psTopoFirstFace (respectivly \ref m_psTopoSecondFace) is part of
the planar section result of \ref A3DCutWithMultiPlanarSectionOnModelFile or \ref A3DCutWithMultiPlanarSectionOnRepresentationItems functions.

*/
typedef struct
{
	A3DUns16 				m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DCrvPolyLine*			m_pProjectedPolyLine;	/*!< PolyLine curve*/
	A3DTopoEdge *			m_psTopoEdge;			/*!< To retrieve analytics from Edge */
	A3DTopoFace *			m_psTopoFirstFace;		/*!< To retrieve analytics from face */
	A3DTopoFace *			m_psTopoSecondFace;		/*!< To retrieve analytics from face */
	bool 					m_bFirstFaceIsSection;	/*!< For future used */
	bool 					m_bSecondFaceIsSection;	/*!< For future used */
	A3DUns8 				m_cType;				/*!< Type of curve must be /ref A3D_HLR_TYPE_UNKNOWN, /ref A3D_HLR_TYPE_EDGE, /ref A3D_HLR_TYPE_SILHOUETTE,
														 /ref A3D_HLR_TYPE_SECTION  or \ref A3D_HLR_TYPE_SILHOUETTE_SECTION*/
	A3DBool					m_bIsHidden;			/*!< if true, the curve is hidden */
} A3DHLRCurveData;


/*!
\brief A3DHLRCurveData structure
\ingroup a3d_HLR_Compute
\version 8.1
*/
typedef struct
{
	A3DUns16 			m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DRiRepresentationItem const *	m_pRepItem;	/* Current representation item */
	A3DDouble			m_adMatrix[16];			/*!< Global placement of the current representation item (used for \ref A3DHLRCurveData m_psTopoEdge or m_psTopoFirstFace / m_psTopoSecondFace).*/
	A3DUns32 			m_uiNumberHLRCurves;	/*!< number of element in m_pppHLRCurves.*/
	A3DHLRCurveData*	m_pppHLRCurves;			/*!< Array of \ref A3DHLRCurveData, describing result hlr curves.*/
} A3DHLRRepresentationItemData;


/*!
\ingroup a3d_HLR_Compute
\brief Function to compute Hidden Line Removal on a set of \ref A3DRiRepresentationItem.
\version 8.1

Call A3DComputeOrthoHLROnRepresentationItems( 0, NULL, NULL, NULL, pNumberHLRData, pppHLRData) to release *pppHLRData structure ( A3DCrvPolyLine* was not released)

\param [in] uiNbRepItems Number of \ref A3DRiRepresentationItem.
\param [in] apRepItems set of \ref A3DRiRepresentationItem.
\param [in] pOptPlacements Optional set of representation item placements (16 A3DDouble matrix).
\param [in] psHLRViewPlaneData define a plane as a camera with orthogonal projection.
\param [out] pNumberHLRData Number \ref A3DHLRRepresentationItemData.
\param [out] pppHLRData HLR curve result grouped by \ref A3DRiRepresentationItem entity.  pppHLRData is automatically allocated by A3DComputeOrthoHLROnRepresentationItems.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
\return \ref A3D_BREPDATA_INCONSISTENT_DATA if bUseExactComputation is set and if is missing \ref A3DTopoBrepData \n
\return \ref A3D_TOPO_GEOMETRY_MISSING if bUseExactComputation is set and if is missing UV curves \n
*/
A3D_API(A3DStatus, A3DComputeOrthoHLROnRepresentationItems, (	A3DUns32 uiNbRepItems,
																A3DRiRepresentationItem const ** apRepItems,
																A3DDouble ** pOptPlacements,
																A3DHLRViewPlaneData const * psHLRViewPlaneData,
																A3DUns32 * pNumberHLRData,
																A3DHLRRepresentationItemData** pppHLRData));
/*!
\ingroup a3d_HLR_Compute
\brief Function to compute Hidden Line Removal on a \ref A3DAsmModelFile
\warning DEPRECATED: use \ref A3DComputeOrthoHLROnModelFile2
\version 8.1

Call A3DComputeOrthoHLROnModelFile( NULL, pOptMrkRView, NULL, pNumberHLRData, pppHLRData) to release *pppHLRData structure ( A3DCrvPolyLine* was not released)

\param [in] pModelFile Number of BrepModels in pRiBrepModel.
\param [in] pOptMrkRView optional \ref A3DMkpView (cut, filter and/or move entities).
\param [in] psHLRViewPlaneData define a plane as a camera with orthogonal projection.
\param [out] pNumberHLRData Number \ref A3DHLRRepresentationItemData.
\param [out] pppHLRData HLR curve result grouped by \ref A3DRiRepresentationItem entity.  pppHLRData is automatically allocated by A3DComputeOrthoHLROnModelFile.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API(A3DStatus, A3DComputeOrthoHLROnModelFile,(	A3DAsmModelFile const * pModelFile,
													A3DMkpView const * pOptMrkRView,
													A3DHLRViewPlaneData const * psHLRViewPlaneData,
													A3DUns32 * pNumberHLRData,
													A3DHLRRepresentationItemData** pppHLRData));

/*!
\ingroup a3d_HLR_Compute
\brief Function to compute Hidden Line Removal on a \ref A3DAsmModelFile
\version 9.0

Call A3DComputeOrthoHLROnModelFile2( NULL, NULL, NULL, pNumberHLRRepItem, pppHLRRepItem) to release *pppHLRRepItem structure ( internal A3DCrvPolyLine* was not released)

If pOptMrkRView is a cutting view, psSectionParametersData can be set to NULL.
In this case, cutting planes contains in pOptMrkRView are use.
Planes must to ordained, and set a profile, if not an \ref A3D_TOOLS_INVALID_SECTION_PLANE error is returned.

\param [in] pModelFile Number of BrepModels in pRiBrepModel.
\param [in] pOptMrkRView optional \ref A3DMkpView (cut, filter and/or move entities).
\param [in] psHLRViewPlaneData define a plane as a camera with orthogonal projection.
\param [out] pNumberHLRRepItem Number \ref A3DHLRRepresentationItem.
\param [out] pppHLRRepItem HLR curve result grouped by \ref A3DRiRepresentationItem entity.  pppHLRRepItem is automatically allocated by A3DComputeOrthoHLROnModelFile.

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
\return \ref A3D_TOOLS_INVALID_SECTION_PLANE \n
*/
A3D_API(A3DStatus, A3DComputeOrthoHLROnModelFile2, (	A3DAsmModelFile const * pModelFile,
														A3DMkpView const * pOptMrkRView,
														A3DHLRViewPlaneData const * psHLRViewPlaneData,
														A3DUns32 * pNumberHLRRepItem,
														A3DHLRRepresentationItem*** pppHLRRepItem));

/*!
\ingroup a3d_HLR_Compute
\brief Populates the \ref A3DHLRRepresentationItemData structure
\version 9.0

Call A3DHLRRepresentationItemGet( NULL, psRIData) to release *psRIData structure ( A3DCrvPolyLine* was not released)

\param [in] pHLRRepItem The input entity
\param [out] psRIData The structure to populate

\return \ref A3D_SUCCESS \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_ERROR \n
*/
A3D_API(A3DStatus, A3DHLRRepresentationItemGet, (	A3DHLRRepresentationItem const* pHLRRepItem,
													A3DHLRRepresentationItemData * psRIData));


#endif
