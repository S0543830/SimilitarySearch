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
\brief      Header file for curve entities
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCGEOMETRYCRV_H__
#define __A3DPRCGEOMETRYCRV_H__

#ifndef __A3DPRCMISC_H__
#error A3DSDKMisc.h must be included before current file
#endif

/*!
\defgroup a3d_crv Curves Module
\ingroup a3d_geometry_module
\brief Creates and accesses entities that represent geometric curves

Geometric curves (\ref A3DCrvBase) are a mandatory part of the topology construct in an \ref A3DTopoBody entity. 
Do not confuse an \ref A3DCrvBase entity with an \ref A3DRiCurve entity. 
The latter is a particular  representation item that has
an \ref A3DTopoSingleWireBody as its topology entry point.

All curves are defined as described in these steps: 
<ol>
	<li>Define the canonical form of the whole curve.</li>
	<li>Define the actual parameterization and the portion of curve (trimming information) 
		(\ref A3DParameterizationData). </li>
	<li>Define the orientation and scaling of the curve using a Cartesian transformation. 
		The transformation cannot specify mirror or non-uniform scaling transformations 
		(see \ref A3DMiscCartesianTransformationData). </li>
</ol>

Here are definitions for terms that apply to curves. 
\li \e Curve is a mathematical description for a whole curve.
\li \e Arc is a portion of a curve corresponding to an interval. 
*/

#ifndef __A3D_CRVNURBS__
/*!
\defgroup a3d_crvnurbs NURBS Curve
\ingroup a3d_crv
Entity type is \ref kA3DTypeCrvNurbs.

\note This curve type contains neither \ref A3DParameterizationData nor \ref A3DMiscCartesianTransformationData. 

*/

/*!
\brief enumerate to characterize knot vector
\ingroup a3d_crvnurbs
\version 2.0
*/
typedef enum
{
	kA3DKnotTypeUniformKnots,			/*!< Uniform. */
	kA3DKnotTypeUnspecified,			/*!< No particularity. */
	kA3DKnotTypeQuasiUniformKnots,		/*!< Quasi-uniform. */
	kA3DKnotTypePieceWiseBezierKnots	/*!< Extrema with multiplicities of degree + 1, internal is degree. */
} A3DEKnotType;

/*!
\brief Enumerate to characterize curve form
\ingroup a3d_crvnurbs
\version 2.0
*/
typedef enum
{
	kA3DBSplineCurveFormUnspecified,	/*!< No particularity. */
	kA3DBSplineCurveFormPolyline,		/*!< Polyline. */
	kA3DBSplineCurveFormCircularArc,	/*!< Circle arc. */
	kA3DBSplineCurveFormEllipticArc,	/*!< Elliptic arc. */
	kA3DBSplineCurveFormParabolicArc,	/*!< Parabolic arc. */
	kA3DBSplineCurveFormHyperbolicArc	/*!< Hyperbolic arc. */
} A3DEBSplineCurveForm;

/*!
\brief NURBS curve structure
\ingroup a3d_crvnurbs
\version 2.0
*/
typedef struct
{
	A3DUns16					m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool						m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DBool						m_bRational;		/*!< A value of true indicates the curve is rational. */
	A3DUns32					m_uiDegree;			/*!< Degree. */
	A3DUns32					m_uiCtrlSize;		/*!< Size of next array. */
	A3DVector3dData*			m_pCtrlPts;			/*!< Control points. */
	A3DUns32					m_uiWeightSize;		/*!< Size of next array. */
	A3DDouble*					m_pdWeights;		/*!< Vector of weights. May be null. */
	A3DUns32					m_uiKnotSize;		/*!< Size of next array. */
	A3DDouble*					m_pdKnots;			/*!< Expanded vector of knots. */
	A3DEKnotType				m_eKnotType;		/*!< Knot type. */
	A3DEBSplineCurveForm		m_eCurveForm;		/*!< Curve form. */
} A3DCrvNurbsData;

/*!
\brief Populates the \ref A3DCrvNurbsData structure
\ingroup a3d_crvnurbs
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_CRV_NURBS_CANNOT_ACCESS_CONTROL_POINTS \n
\return \ref A3D_CRV_NURBS_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvNurbsGet,(const A3DCrvNurbs* pCrv,
										 A3DCrvNurbsData* pData));

/*!
\brief Creates an \ref A3DCrvNurbs from \ref A3DCrvNurbsData structure
\ingroup a3d_crvnurbs
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvNurbsCreate,(const A3DCrvNurbsData* pData,
											 A3DCrvNurbs** ppCrv));

/*!
\brief Populates the \ref A3DCrvNurbsData structure from any type of \ref A3DCrvBase
\ingroup a3d_crvnurbs
\version 2.1

This structure must be freed with \ref A3DCrvNurbsGet call.
\warning This function can modify the parameterization for curve. 
You must treat related entities accordingly. 

\note dTolerance must be computed to obtain the final targeted precision.
The inputs are: 
\li the tolerance that you want to achieve (that is: the maximum deviation 
between the original geometry and its approximation), which you should express 
in mm. This is the starting point with a physical significance. 
\li you have to take into account the body scale
\li you have to take into account the part unit 
\li you have to take into account eventual additional scales in the product 
hierarchy to come up to the actual value that you should input for he function. 
Let’s assume that the part is in inches, that there is no scale (all set to 1.) in 
the product hierarchy, and that the body scale is 1000.
As a reminder, here is how to interpret the meaning of the values stored in the 
curve’s data: let’s assume that you have a value of “0.1” stored for the curve 
definition (say a coordinate for a control point or an origin of cylinder axis). 
This value is to be interpreted as multiplied by the body scale (here: 1000.) and 
then expressed in the unit of the part. Thus this “0.1” corresponds physically to 
0.1*1000=100 inches or 2500.4 mm.
Hence, imagine that you want to convert this curve into a NURBS with a tolerance 
of 0.001 mm (which is a classical value), the calculation is following: 
<b>tolerance to put = Wanted tolerance in mm / (body scale * unit in times mm);</b>
In example above, this leads to a final tolerance to put being
<b>1/25.4 e-6 = 0.001 / (1000 * 25.4 mm);</b>
With this value, all the numbers which are manipulated at the “TopoContext” level, 
including for instance coordinates of control points, will be treated consistently 
with their physical significance.

\warning This function can be called with any type of curve.

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvBaseGetAsNurbs,(const A3DCrvBase* pCrv,
														A3DDouble dTolerance,
														A3DBool bUseSameParameterization,
														A3DCrvNurbsData* pData));

#endif	/*	__A3D_CRVNURBS__ */

#ifndef __A3D_CRVLINE__
/*!
\defgroup a3d_crvline Linear Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvLine.

The canonical form is defined with the help of \ref A3DMiscCartesianTransformationData, 
its origin (parameter 0) being the origin of the line and its vector X being the direction of the line.
\ref A3DParameterizationData allows for reparameterization and trim. 

\par Example of a line segment

\image html A3DPRCGeometryCrvLine.jpg
In the above illustration, the line is restricted to <b>[ t0 , t1 ]</b> interval on the X vector of its Cartesian transformation.
\note Scale from \ref A3DMiscCartesianTransformationData must be taken into account in previous evaluation's algorithms.
\note Y vector from \ref A3DMiscCartesianTransformationData has no particular meaning in this case and must be ignored.
*/

/*!
\brief Structure for defining linear curves
\ingroup a3d_crvline
\version 2.0
*/
typedef struct
{
	A3DUns16									m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool										m_bIs2D;		/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData			m_sTrsf;		/*!< Cartesian transformation. */
	A3DParameterizationData						m_sParam;		/*!< Parameterization. */
} A3DCrvLineData;

/*!
\brief Populates the \ref A3DCrvLineData structure
\ingroup a3d_crvline
\version 2.0

\note Y vector from \ref A3DMiscCartesianTransformationData has no particular 
meaning in this case and must be ignored.
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvLineGet,(const A3DCrvLine* pCrv,
										A3DCrvLineData* pData));

/*!
\brief Creates an \ref A3DCrvLine from \ref A3DCrvLineData structure
\ingroup a3d_crvline
\version 2.0

\note The Y vector from \ref A3DMiscCartesianTransformationData has no particular meaning 
in this case, but \b must \b be \b set
so that it is normed and perpendicular to the X vector. This is mandatory. 
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvLineCreate,(const A3DCrvLineData* pData,
											A3DCrvLine** ppCrv));
#endif	/*	__A3D_CRVLINE__ */

#ifndef __A3D_CRVCIRCLE__
/*!
\defgroup a3d_crvcircle Circular Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvCircle.

The canonical form is defined with an \ref A3DMiscCartesianTransformationData, its origin being the center of the circle and its vector X being the axis corresponding to zero parameter.
The implicit parameterization is an angle expressed as radians in the range [0, 2PI].

\ref A3DParameterizationData lets you specify reparameterization and trim. 
 
Here are parameterization examples:
<ul>
	<li>To specify the interval in radians,
		set \c m_dCoeffA to 1.0 and \c m_dCoeffB to 0.0. 
		These parameter values specify an identity conversion.</li>
	<li>To specify the interval in degrees,
		set  \c m_dCoeffA to PI/180 and  \c m_dCoeffB to 0.0.
		\c m_dCoeffA is the ratio of radians to degrees.</li>
</ul>

\par Example of a circular arc

\image html A3DPRCGeometryCrvCircle.jpg
In the above example, the circular arc is in the XY plane (and therefore has an identity transformation),
has radius \b R, and is restricted to the <b>[ t0 , t1 ]</b> interval. 

If \c m_dCoeffA is 1.0 and \c m_dCoeffB is 0.0 and 
if the interval is defined as \c t0=0 and \c t1=PI/2, 
then \c t0 corresponds to the Cartesian coordinates (R,0,0) and \c t1 to (0,R,0).
These values for the \c m_dCoeffA and \c m_dCoeffB co-efficients indicate parameterization is in radians and starts at the X axis.

\note Radius must be greater than \b 0.
\warning Radius as a parameter can be modified by \ref A3DMiscCartesianTransformationData when the transformation defines uniform scaling. 
*/

/*!
\brief Circle arc structure
\ingroup a3d_crvcircle
\version 2.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;			/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;			/*!< Parameterization. */
	A3DDouble							m_dRadius;			/*!< Radius. */
} A3DCrvCircleData;

/*!
\brief Populates the \ref A3DCrvCircleData structure
\ingroup a3d_crvcircle
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvCircleGet,(const A3DCrvCircle* pCrv,
										  A3DCrvCircleData* pData));

/*!
\brief Creates an \ref A3DCrvCircle from \ref A3DCrvCircleData structure
\ingroup a3d_crvcircle
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvCircleCreate,(const A3DCrvCircleData* pData,
											  A3DCrvCircle** ppCrv));

#endif	/*	__A3D_CRVCIRCLE__ */

#ifndef __A3D_CRVELLIPSE__
/*!
\defgroup a3d_crvellipse Elliptic Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvEllipse.

The canonical form is defined with an \ref A3DMiscCartesianTransformationData, its origin being the center of the ellipse and its vector X being the axis corresponding to zero parameter and X radius.
The implicit parameterization is an angle in radian in the range [0, 2PI].

\ref A3DParameterizationData allows for reparameterization and trim. 

\par Example of an elliptic arc

\image html A3DPRCGeometryCrvEllipse.jpg
In this example, the ellipse is in the XY plane (and therefore has an identity transformation), 
with radii \b Rx and \b Ry and is restricted to the <b>[ t0 , t1 ]</b> interval.
Assuming \c m_dCoeffA is 1.0 and \c m_dCoeffB 0.0 (which indicates a parameterization in radians), 
then t0=0 and t1=PI/2, t0 corresponds to the Cartesian coordinates (Rx,0,0) and t1 to (0,Ry,0).
\note The values of the \c m_dXRadius and \c m_dYRadius members must be greater than 0.
*/

/*!
\brief Elliptic curve structure
\ingroup a3d_crvellipse
\version 2.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;			/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;			/*!< Parameterization. */
	A3DDouble							m_dXRadius;			/*!< Radius along X axis. Must be greater than 0. */
	A3DDouble							m_dYRadius;			/*!< Radius along Y axis. Must be greater than 0. */
} A3DCrvEllipseData;

/*!
\brief Populates the \ref A3DCrvEllipseData structure
\ingroup a3d_crvellipse
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n 
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvEllipseGet,(const A3DCrvEllipse* pCrv,
											A3DCrvEllipseData* pData));

/*!
\brief Creates an \ref A3DCrvEllipse from \ref A3DCrvEllipseData structure
\ingroup a3d_crvellipse
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvEllipseCreate,(const A3DCrvEllipseData* pData,
												A3DCrvEllipse** ppCrv));

#endif	/*	__A3D_CRVELLIPSE__ */

#ifndef __A3D_CRVPARABOLA__
/*!
\defgroup a3d_crvparabola Parabolic Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvParabola.

For the canonical definition of this curve and its corresponding parametric equation, 
see the "SerializeParabola" section of the \REF_PRC_SPEC.

The \ref A3DParameterizationData struct specified by the \ref A3DCrvParabolaData::m_sParam member 
specifies reparameterization and trim for the curve.

\attention In version 2.1 and earlier, values for parameterization named in the \ref A3DCrvParabolaData::m_cParamType member 
are inverted compared to the corresponding values in the \REF_PRC_SPEC.

\version 2.3

When \ref A3DCrvParabolaData::m_cParamType is set to 1, X value must be taken as <b>param2/sqrt(16*focus2+param2)</b>, and Y
as corresponding value <b>2 * \ref A3DCrvParabolaData::m_dFocal * sqrt( fabs(X) / \ref A3DCrvParabolaData::m_dFocal )</b>.

\ref A3DParameterizationData allows for reparameterization and trim. 
*/

/*!
\brief Parabola arc structure
\ingroup a3d_crvparabola
\version 2.0

*/
typedef struct
{
	A3DUns16							m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;			/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;			/*!< Parameterization. */
	A3DDouble							m_dFocal;			/*!< Focal distance. */
	A3DInt8								m_cParamType;		/*!< Parameterization type. */
} A3DCrvParabolaData;

/*!
\brief Populates the \ref A3DCrvParabolaData structure
\ingroup a3d_crvparabola
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvParabolaGet,(const A3DCrvParabola* pCrv,
											 A3DCrvParabolaData* pData));

/*!
\brief Creates an \ref A3DCrvParabola from \ref A3DCrvParabolaData structure
\ingroup a3d_crvparabola
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvParabolaCreate,(const A3DCrvParabolaData* pData,
												 A3DCrvParabola** ppCrv));

#endif	/*	__A3D_CRVPARABOLA__ */

#ifndef __A3D_CRVHYPERBOLA__
/*!
\defgroup a3d_crvhyperbola Hyperbolic Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvHyperbola.

For the canonical definition of this curve and its corresponding parametric equation, 
see the "SerializeHyperbola" section of the \REF_PRC_SPEC.

The \ref A3DParameterizationData struct specified by the \ref A3DCrvHyperbolaData::m_sParam member 
specifies reparameterization and trim for the curve.

\attention In version 2.1 and earlier, values for the parameterization type named by the \ref A3DCrvHyperbolaData::m_cParamType member 
are inverted compared to the corresponding values in the \REF_PRC_SPEC.

*/

/*!
\brief Hyperbola arc structure
\ingroup a3d_crvhyperbola
\version 2.0

*/
typedef struct
{
	A3DUns16							m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;			/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;			/*!< Parameterization. */
	A3DDouble							m_dSemiAxis;		/*!< Semi axis along X axis. */
	A3DDouble							m_dSemiImageAxis;	/*!< Semi axis along Y axis. */
	A3DInt8								m_cParamType;		/*!< Parameterization type. */
} A3DCrvHyperbolaData;

/*!
\brief Populates the \ref A3DCrvHyperbolaData structure
\ingroup a3d_crvhyperbola
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvHyperbolaGet,(const A3DCrvHyperbola* pCrv,
											  A3DCrvHyperbolaData* pData));

/*!
\brief Creates an \ref A3DCrvHyperbola from \ref A3DCrvHyperbolaData structure
\ingroup a3d_crvhyperbola
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvHyperbolaCreate,(const A3DCrvHyperbolaData* pData,
												  A3DCrvHyperbola** ppCrv));

#endif	/*	__A3D_CRVHYPERBOLA__ */

#ifndef __A3D_CRVPOLYLINE__
/*!
\defgroup a3d_crvpolyline Polyline Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvPolyLine.

For the canonical definition of this curve, see the "SerializePolyLine" section of the \REF_PRC_SPEC.

\ref A3DParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 
*/

/*!
\brief PolyLine structure
\ingroup a3d_crvpolyline
\version 2.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;		/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;		/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;		/*!< Parameterization. */
	A3DUns32							m_uiSize;		/*!< Size of next array. */
	A3DVector3dData*					m_pPts;			/*!< Array of points. */
} A3DCrvPolyLineData;

/*!
\brief Populates the \ref A3DCrvPolyLineData structure
\ingroup a3d_crvpolyline
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvPolyLineGet,(const A3DCrvPolyLine* pCrv,
											 A3DCrvPolyLineData* pData));

/*!
\brief Creates an \ref A3DCrvPolyLine from \ref A3DCrvPolyLineData structure
\ingroup a3d_crvpolyline
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvPolyLineCreate,(const A3DCrvPolyLineData* pData,
												 A3DCrvPolyLine** ppCrv));

#endif	/*	__A3D_CRVPOLYLINE__ */

#ifndef __A3D_CRVCOMPOSITE__
/*!
\defgroup a3d_crvcomposite Composite Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvComposite.

For the canonical definition of this curve, see the "SerializeComposite" section of the \REF_PRC_SPEC.

\ref A3DParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 
*/

/*!
\brief Composite curve structure
\ingroup a3d_crvcomposite
\version 2.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;			/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;			/*!< Parameterization. */
	A3DUns32							m_uiSize;			/*!< Size of next array. */
	A3DCrvBase**						m_ppCurves;			/*!< Array of pointers on curves. */
	A3DBool*							m_pbSenses;			/*!< Array of senses per curve (same size as previous array). */
	A3DBool								m_bClosed;			/*!< Flag indicating that composite curve is closed. */
} A3DCrvCompositeData;

/*!
\brief Populates the \ref A3DCrvCompositeData structure
\ingroup a3d_crvcomposite
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvCompositeGet,(const A3DCrvComposite* pCrv,
											  A3DCrvCompositeData* pData));

/*!
\brief Creates an \ref A3DCrvPolyLine from \ref A3DCrvCompositeData structure
\ingroup a3d_crvcomposite
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvCompositeCreate,(const A3DCrvCompositeData* pData,
												  A3DCrvComposite** ppCrv));

#endif	/*	__A3D_CRVCOMPOSITE__ */

#ifndef __A3D_CRVEQUATION__
/*!
\defgroup a3d_crvequation Equation Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvEquation.

For the canonical definition of this curve, see the "SerializeEquation" section of the \REF_PRC_SPEC.

\ref A3DParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 

*/

/*!
\brief Equation structure
\ingroup a3d_crvequation
\version 2.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;			/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;			/*!< Parameterization. */
	A3DIntervalData						m_sMaxInterval;		/*!< Maximum interval of definition for the functions defined in the next members. */
	A3DMathFct1D*						m_pFunctionX;		/*!< Function X. */
	A3DMathFct1D*						m_pFunctionY;		/*!< Function Y. */
	A3DMathFct1D*						m_pFunctionZ;		/*!< Function Z. */
} A3DCrvEquationData;

/*!
\brief Populates the \ref A3DCrvEquationData structure
\ingroup a3d_crvequation
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvEquationGet,(const A3DCrvEquation* pCrv,
											 A3DCrvEquationData* pData));

/*!
\brief Creates an \ref A3DCrvEquation from \ref A3DCrvEquationData structure
\ingroup a3d_crvequation
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_CRV_EQUATION_CANNOT_CREATE_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvEquationCreate,(const A3DCrvEquationData* pData,
												 A3DCrvEquation** ppCrv));

#endif	/*	__A3D_CRVEQUATION__ */

#ifndef __A3D_CRVTRANSFORM__
/*!
\defgroup a3d_crvtransform Transform Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvTransform.

For the canonical definition of this curve, 
see the "SerializeTransformationCurve" section of the \REF_PRC_SPEC.

\ref A3DParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 

*/

/*!
\brief Transform curve structure
\ingroup a3d_crvtransform
\version 2.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;			/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;			/*!< Parameterization. */
	A3DMathFct3D*						m_pTransfo;			/*!< Transformation to apply to basis curve. */
	A3DCrvBase*							m_pBasisCrv;		/*!< Basis Curve. */
} A3DCrvTransformData;

/*!
\brief Populates the \ref A3DCrvTransformData structure
\ingroup a3d_crvtransform
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvTransformGet,(const A3DCrvTransform* pCrv,
											  A3DCrvTransformData* pData));

/*!
\brief Creates an \ref A3DCrvTransform from \ref A3DCrvTransformData structure
\ingroup a3d_crvtransform
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_CRV_TRANSFORM_CANNOT_CREATE_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvTransformCreate,(const A3DCrvTransformData* pData,
												  A3DCrvTransform** ppCrv));

#endif	/*	__A3D_CRVTRANSFORM__ */

#ifndef __A3D_CRVONSURF__
/*!
\defgroup a3d_crvonsurf Curve On Surface
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvOnSurf.

For the canonical definition of this curve, 
see the "SerializeTransformationCurve" section of the \REF_PRC_SPEC.

\note \ref A3DParameterizationData must have \ref A3DParameterizationData::m_dCoeffA set to 1, 
\ref A3DParameterizationData::m_dCoeffB set to 0 and 
an \ref A3DIntervalData identical to the one of \ref A3DCrvOnSurfData::m_pUVCurve. 
\note \ref A3DMiscCartesianTransformationData should correspond to identity transformation. 
\note \ref A3DCrvOnSurfData::m_pUVCurve must be a curve of type \ref kA3DTypeCrvLine or \ref kA3DTypeCrvNurbs. 
*/

/*!
\brief Curve on Surface structure

3D Curve defined as a 2D parametric curve lying on a surface
\ingroup a3d_crvonsurf
\version 2.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;			/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;			/*!< Parameterization. */
	A3DCrvBase*							m_pUVCurve;			/*!< Parameter space curve. */
	A3DSurfBase*						m_pSurface;			/*!< Base surface. */
} A3DCrvOnSurfData;

/*!
\brief Populates the \ref A3DCrvOnSurfData structure
\ingroup a3d_crvonsurf
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvOnSurfGet,(const A3DCrvOnSurf* pCrv,
										  A3DCrvOnSurfData* pData));

/*!
\brief Creates an \ref A3DCrvOnSurf from \ref A3DCrvOnSurfData structure
\ingroup a3d_crvonsurf
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_CRV_CRVONSURF_CANNOT_CREATE_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvOnSurfCreate,(const A3DCrvOnSurfData* pData,
											  A3DCrvOnSurf** ppCrv));

#endif	/*	__A3D_CRVONSURF__ */

#ifndef __A3D_CRVOFFSET__
/*!
\defgroup a3d_crvoffset Offset Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvOffset.

For the canonical definition of this curve, see the "SerializeOffset" section of the \REF_PRC_SPEC.

You can use an existing offset curve entity as the base curve used to create a new offset curve.
That is, you can specify  
\image html A3DPRCGeometryCrvOffset.jpg

\note \ref A3DParameterizationData must have \ref A3DParameterizationData::m_dCoeffA set to 1, 
\ref A3DParameterizationData::m_dCoeffB set to 0 and an \ref A3DIntervalData identical 
to the one of \ref A3DCrvOffsetData::m_pBasisCrv. 

\note \ref A3DMiscCartesianTransformationData should correspond to identity transformation. 
*/
/*!
\brief Offset structure
\ingroup a3d_crvoffset
\version 2.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;			/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;			/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;			/*!< Parameterization. */
	A3DCrvBase*							m_pBasisCrv;		/*!< Basis curve. */
	A3DDouble							m_dOffset;			/*!< Offset along vector. */
	A3DVector3dData						m_sVector;			/*!< Offset vector. */
} A3DCrvOffsetData;

/*!
\brief Populates the \ref A3DCrvOffsetData structure
\ingroup a3d_crvoffset
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvOffsetGet,(const A3DCrvOffset* pCrv,
										  A3DCrvOffsetData* pData));

/*!
\brief Creates an \ref A3DCrvOffset from \ref A3DCrvOffsetData structure
\ingroup a3d_crvoffset
\version 2.0

\warning Associated transformation must be Identity
\warning Trimming interval must be defined inside curve definition
\warning Parameterization must have CoeffA = 1. and CoeffB = 0.
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_CRV_OFFSET_CANNOT_CREATE_CANONICAL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DCrvOffsetCreate,(const A3DCrvOffsetData* pData,
											  A3DCrvOffset** ppCrv));

#endif	/*	__A3D_CRVOFFSET__ */

/*************************************************************************
*
*	NOT YET IMPLEMENTED
*
*************************************************************************/

#ifndef __A3D_CRVHELIX__
/*!
\defgroup a3d_crvhelix Helix Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvHelix.

For the canonical definition of this curve, see the "SerializeHelix01" section of the \REF_PRC_SPEC.

\ref A3DParameterizationData allows for reparameterization and trim. 

\ref A3DMiscCartesianTransformationData allows for specific placement. 

\note \ref kA3DConstantPitch and \ref kA3DVariablePitch correspond to type 0 and 1 respectively in \REF_PRC_SPEC.
*/

/*!
\brief Enumerated values that characterize helix curves
\ingroup a3d_crvhelix
\version 2.0
*/
typedef enum
{
	kA3DConstantPitch = 0,		/*!< Constant pitch. */
	kA3DVariablePitch			/*!< Variable pitch. */
} A3DEHelixType;

/*!
\brief Constant pitch structure for helix curves
\ingroup a3d_crvhelix
\version 2.0
*/
typedef struct
{
	A3DUns16			m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool				m_bTrigonometricOrientation;	/*!< Trigonometruc orientation. */
	A3DVector3dData		m_sStartPoint;					/*!< Starting point. */
	A3DVector3dData		m_sOrigin;						/*!< Origin (optional). */
	A3DVector3dData		m_sDirection;					/*!< Direction. */
	A3DDouble			m_dPitch;						/*!< Pitch. */
	A3DDouble			m_dRadiusEvolution;				/*!< Radius evolution. */
} A3DCrvHelixPitchCstData;

/*!
\brief Variable Pitch structure for helical arc structure
\ingroup a3d_crvhelix
\version 2.0
*/
typedef struct
{
	A3DUns16			m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool				m_bTrigonometricOrientation;	/*!< Trigonometric orientation. */
	A3DVector3dData		m_sStartPoint;					/*!< Starting point. */
	A3DVector3dData		m_sUnitZ;						/*!< Unit Z. */
	A3DVector3dData		m_sUnitU;						/*!< Unit U. */
	A3DMathFct1D*		m_psRadiusLaw;					/*!< Radius Law. */
	A3DMathFct1D*		m_psZLaw;						/*!< Z Law. */
	A3DMathFct1D*		m_psThetaLaw;					/*!< Theta Law. */
	A3DDouble			m_dRatioU;						/*!< Ratio U. */
	A3DDouble			m_dRatioV;						/*!< Ratio V. */
	A3DDouble			m_dRatioZ;						/*!< Ratio Z. */
	A3DDouble			m_dTheta0;						/*!< Theta 0. */
} A3DCrvHelixPitchVarData;

/*!
\brief Helical arc structure
\ingroup a3d_crvhelix
\version 2.0
*/
typedef struct
{
	A3DUns16							m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool								m_bIs2D;				/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData	m_sTrsf;				/*!< Cartesian transformation. */
	A3DParameterizationData				m_sParam;				/*!< Parameterization. */
	A3DEHelixType						m_eType;				/*!< Helix type. */
	A3DCrvHelixPitchCstData				m_sCstHelixData;		/*!< Data if type is CstHelix. */
	A3DCrvHelixPitchVarData				m_sVarHelixData;		/*!< Data if type is VarHelix. */
} A3DCrvHelixData;

/*!
\brief Populates the \ref A3DCrvHelixData structure
\ingroup a3d_crvhelix
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
\attention <b>FUNCTION IS NOT IMPLEMENTED YET</b>
*/
A3D_API (A3DStatus, A3DCrvHelixGet,(const A3DCrvHelix* pCrv,
										 A3DCrvHelixData* pData));

/*!
\brief Creates an \ref A3DCrvHelix from \ref A3DCrvHelixData structure
\ingroup a3d_crvhelix
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
\attention <b>FUNCTION IS NOT IMPLEMENTED YET</b>
*/
A3D_API (A3DStatus, A3DCrvHelixCreate,(const A3DCrvHelixData* pData,
													A3DCrvHelix** ppCrv));

#endif	/*	__A3D_CRVHELIX__ */

#ifndef __A3D_CRVINTERSECTION__
/*!
\defgroup a3d_crvintersection Intersection Curve
\ingroup a3d_crv
\version 2.0
Entity type is \ref kA3DTypeCrvIntersection.

\note This type is not yet implemented
*/

/*!
\struct A3DCrossingPointsCrvIntersectionData
\brief Crossing point curve intersection data
\ingroup a3d_crvintersection
\version 2.0
*/
typedef struct
{
	A3DUns16			m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DVector3dData		m_sPosition;		/*!< Crossing point position. */
	A3DVector2dData		m_sUVPosition1;		/*!< Crossing point UV on surface 1. */
	A3DVector2dData		m_sUVPosition2;		/*!< Crossing point UV on surface 2. */
	A3DVector3dData		m_sTangent;			/*!< Crossing point tangent. */
	A3DDouble			m_dParameter;		/*!< Crossing point parameter. */
	A3DDouble			m_dScale;			/*!< Crossing point scale. */
	A3DUTF8Char			m_cFlags;			/*!< Crossing point flags. */
} A3DCrossingPointsCrvIntersectionData;

/*!
\enum A3DEIntersectionLimitType
\brief Intersection limit type
\ingroup a3d_crvintersection
\version 2.0
*/
typedef enum
{
	kA3DIntersectionLimitTypeHelp,			/*!< Arbitary limit on a closed intersection curve. */
	kA3DIntersectionLimitTypeTerminator,	/*!< Limit where one of the two intersection surface normals is degenerate or where they become colinear. */
	kA3DIntersectionLimitTypeLimit,			/*!< Artificial limit to avoid an infinite curve. */
	kA3DIntersectionLimitTypeBoundary		/*!< Limit of the curve if a A3DSurfBlend02 surface (that uses the intersection curve as its center curve) becomes degenerate. */
} A3DEIntersectionLimitType;

/*!
\struct A3DCrvIntersectionData
\brief Intersection structure
\ingroup a3d_crvintersection
\version 2.0
*/
typedef struct
{
	A3DUns16					m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool						m_bIs2D;					/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData m_sTrsf;				/*!< Cartesian transformation. */
	A3DParameterizationData		m_sParam;					/*!< Parameterization. */
	A3DSurfBase*				m_pSurface1;				/*!< Surface 1. */
	A3DSurfBase*				m_pSurface2;				/*!< Surface 2. */
	A3DBool						m_bSensSurface1;			/*!< True if sense is the same as surface 1; false otherwise. */
	A3DBool						m_bSensSurface2;			/*!< True if sense is the same as surface 2; false otherwise. */
	A3DBool						m_bSens;					/*!< True if the sense of the intersection sense is surface 1 cross surface 2; false otherwise. */
	A3DUns32					m_uiCrossingPtsSize;		/*!< Number of crossing points. */
	A3DCrossingPointsCrvIntersectionData*	m_pCrossingPts;	/*!< Array of crossing points. */
	A3DVector3dData				m_sStartLimitPoint;			/*!< Start limit point. */
	A3DEIntersectionLimitType	m_sStartLimitType;			/*!< Start limit type. */
	A3DVector3dData				m_sEndLimitPoint;			/*!< End limit point. */
	A3DEIntersectionLimitType	m_sEndLimitType;			/*!< End limit type. */
	A3DDouble					m_dChordalError;			/*!< Chordal error. */
	A3DDouble					m_dAngularError;			/*!< Angular error. */
	A3DBool						m_bParameterizationDefinitionRespected;/*!< Parameterization definition respected. */
} A3DCrvIntersectionData;

/*!
\brief Populates the \ref A3DCrvIntersectionData structure
\ingroup a3d_crvintersection
\version 2.0

Not yet implemented.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
\attention <b>FUNCTION IS NOT IMPLEMENTED YET</b>
*/
A3D_API (A3DStatus, A3DCrvIntersectionGet,(const A3DCrvIntersection* pCrv,
												  A3DCrvIntersectionData* pData));

/*!
\brief Creates an \ref A3DCrvIntersection from \ref A3DCrvIntersectionData structure
\ingroup a3d_crvintersection
\version 2.0

Not yet implemented.

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
\attention <b>FUNCTION IS NOT IMPLEMENTED YET</b>
*/
A3D_API (A3DStatus, A3DCrvIntersectionCreate,(const A3DCrvIntersectionData* pData,
													  A3DCrvIntersection** ppCrv));

#endif	/*	__A3D_CRVINTERSECTION__ */

#ifndef __A3D_CRVBOUNDARY__
/*!
\defgroup a3d_crvboundary Blend02Boundary Curve
\ingroup a3d_crv
\version 2.0

Entity type is \ref kA3DTypeCrvBlend02Boundary.

\note This type is not yet implemented
*/

/*!
\brief Blend02Boundary structure
\ingroup a3d_crvboundary
\version 2.0

Not yet implemented.
*/
typedef struct
{
	A3DUns16					m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool						m_bIs2D;					/*!< A value of true specifies a 2D curve; and a value of false specifies a 3D curve. */
	A3DMiscCartesianTransformationData m_sTrsf;				/*!< Cartesian transformation. */
	A3DParameterizationData m_sParam;						/*!< Parameterization. */
	A3DSurfBase*				m_pBlend;					/*!< Blend surface must be of type PRC_TYPE_SURF_Blend02. */
	A3DUns32					m_uiBlend;					/*!< Bound. */
	A3DUns32					m_uiCrossingPtsSize;		/*!< Number of crossing points. */
	A3DVector3dData*			m_pCrossingPts;				/*!< Array of Crossing point positions. */
	A3DDouble					m_dChordalError;			/*!< Chordal error. */
	A3DDouble					m_dAngularError;			/*!< Angular error. */
	A3DSurfBase*				m_pBoundingSurface;			/*!< Bounding surface. */
	A3DBool						m_bBoundingSurfaceSens;		/*!< Sense of bounding surface. */
	A3DBool						m_bIntersectionOrder;		/*!< Intersection order. */
	A3DBool						m_bIntersectionCurveSens;	/*!< Sense of intersection curve. */
	A3DDouble					m_dBaseParameter;			/*!< Base parameter. */
	A3DDouble					m_dBaseScale;				/*!< Base scale. */
	A3DVector3dData				m_sStartLimitPoint;			/*!< Start limit point. */
	A3DEIntersectionLimitType	m_sStartLimitType;			/*!< Start limit type. */
	A3DVector3dData				m_sEndLimitPoint;			/*!< End limit point. */
	A3DEIntersectionLimitType	m_sEndLimitType;			/*!< End limit type. */
} A3DCrvBlend02BoundaryData;

/*!
\brief Populates the \ref A3DCrvBlend02BoundaryData structure
\ingroup a3d_crvboundary
\version 2.0

Not yet implemented.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_CRV_CANNOT_ACCESS_CANONICAL \n
\return \ref A3D_SUCCESS \n
\attention <b>FUNCTION IS NOT IMPLEMENTED YET</b>
*/
A3D_API (A3DStatus, A3DCrvBlend02BoundaryGet,(const A3DCrvBlend02Boundary* pCrv,
													  A3DCrvBlend02BoundaryData* pData));

/*!
\brief Creates an \ref A3DCrvBlend02Boundary from \ref A3DCrvBlend02BoundaryData structure
\ingroup a3d_crvboundary
\version 2.0

Not yet implemented.

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
\attention <b>FUNCTION IS NOT IMPLEMENTED YET</b>
*/
A3D_API (A3DStatus, A3DCrvBlend02BoundaryCreate,(const A3DCrvBlend02BoundaryData* pData,
														  A3DCrvBlend02Boundary** ppCrv));

#endif	/*	__A3D_CRVBOUNDARY__ */



#endif	/*	__A3DPRCGEOMETRYCRV_H__ */
