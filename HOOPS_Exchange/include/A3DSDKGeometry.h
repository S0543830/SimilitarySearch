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
\brief      Header file for attributes that apply to all geometric entities
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCGEOMETRY_H__
#define __A3DPRCGEOMETRY_H__

/*!
\defgroup a3d_geometry_module Geometry Module
\ingroup a3d_entitiesdata_module
\brief Creates and access entities that represent curves and surfaces

This module describes the functions and structures for parsing and creating geometric entities, essentially curves and surfaces. 
It also includes means addressing issues specific to geometric entities, such as interval definition, axis definition, 
and parameterization.

Generally, most curve and surface data structures contain canonical, parameterization, and transformation settings:

<ul>
<li>A canonical form is the simplest parametric equations to define a curve or surface. 
	The term \e canonical means commonly known standards for parametrically representing geometric information, 
	in conjunction with an underyling mathematical equation in the form <b>P(t)</b> for a curve or <b>P(u,v)</b> for a surface. 
	For instance, a line is defined with an origin <b>O</b> and a direction <b>v</b>, 
	corresponding to the equation <b>P(t) = O + t.v</b> 

	Each curve and surface has an implicit parameterization 
	that corresponds to the object's canonical form. 
	This implicit parameterization includes units and range. 
	For example, the implicit parameterization of a circle has radians as its units and has the range [0,2PI].

	\ref a3d_geometry_types introduces canonical forms for curves and surfaces. 
	The \REF_PRC_SPEC provides a full description of all canonical forms and their associated equations. </li>

<li>Parameterization settings for a curve or surface translates from the implicit parameterization of the canonical form
	to the actual parameterization of the geometric entity. 
	
	The parameterization settings include reparameterization coefficients and a range.
	The reparameterization coefficients converts from the units and range of the canonical form 
	to the units and range of the final representation (the \e actual \e parameterization). 
	The range specifies the portion of the canonical form to use, expressed in the units of the actual parameterization.
	The reparameterization coefficients specify the offset and scaling between the units of the canonical form 
	and the units of the actual parameterization.
	\ref a3d_parameterization describes 
	range definitions and parameterization settings. </li>

<li>A transformation setting denotes the actual placement of the geometric entity in 3D space.
	\ref a3d_misc_trsf describes transformation settings.</li>
</ul>

*/

/*!
\defgroup a3d_geomtools_module Common Structures for Geometric Entities
\ingroup a3d_geometry_module
\brief Structures that apply to all geometric entities (vectors, range definitions, and parameterization)
*/

#ifndef __A3D_VECTORS__
/*!
\defgroup a3d_vectors Vectors
\ingroup a3d_geomtools_module
\brief Structures for defining 2D and 3D vectors

2D and 3D vectors are used in several kind of structures, such as \ref a3d_extent structures.
*/

/*!
\brief Structure for a 2D Vector
\ingroup a3d_vectors
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dX;		/*!< x coordinate. */
	A3DDouble m_dY;		/*!< y coordinate. */
} A3DVector2dData;

/*!
\brief Structure for a 3D vector
\ingroup a3d_vectors
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dX;		/*!< x coordinate. */
	A3DDouble m_dY;		/*!< y coordinate. */
	A3DDouble m_dZ;		/*!< z coordinate. */
} A3DVector3dData;
#endif	/*	__A3D_VECTORS__ */

#ifndef __A3D_EXTENTS__
/*!
\defgroup a3d_extent Range Definitions
\ingroup a3d_geomtools_module
\brief Structures for defining range definitions for curves, surfaces, and 3D objects 

This module provides structures that define range definitions for geometric entities:
\li \ref A3DIntervalData structure defines curve (1-dimensional) ranges.
\li \ref A3DDomainData structure defines surface (2-dimensional) ranges.
\li \ref A3DBoundingBoxData structure defines 3D ranges.

Range definitions specify the parts of geometric entities actually used in topological entities.
These ranges are relative to a parameterization setting, which is specified 
in a curve's parameterization data (\ref A3DParameterizationData) or in a surface's parameterization data (\ref A3DUVParameterizationData).
\note Generaly, parameters of ranges must be ordered, for any kind of range. 
*/

/*!
\brief Structure for specifying a linear domain
\ingroup a3d_extent
\version 2.0

This structure defines the linear domain, such as the trimming domain for a curve.
*/
typedef struct
{
	A3DUns16		m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble		m_dMin;				/*!< Minimal value. */
	A3DDouble		m_dMax;				/*!< Maximal value. */
} A3DIntervalData;

/*!
\brief Structure for specifying a planar domain
\ingroup a3d_extent
\version 2.0

This structure defines a planar domain, such as a trimming domain for a surface.
*/
typedef struct
{
	A3DUns16			m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DVector2dData	m_sMin;			/*!< Minimal value. */
	A3DVector2dData	m_sMax;			/*!< Maximal value. */
} A3DDomainData;

/*!
\brief Structure for specifying a 3D domain (a bounding box)
\ingroup a3d_extent
\version 2.0

This structure defines a bounding box (a 3D domain).
*/
typedef struct
{
	A3DUns16			m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DVector3dData	m_sMin;				/*!< Minimal value. */
	A3DVector3dData	m_sMax;				/*!< Maximal value. */
} A3DBoundingBoxData;
#endif	/*	__A3D_EXTENTS__ */

#ifndef __A3D_PARAMETERIZATION__

/*!
\defgroup a3d_parameterization Parameterization for Curve and Surface Geometries
\ingroup a3d_geomtools_module
\brief Structures for parameterizing curves and structures

The data structures in this module are used to parametrically represent curves and surfaces. 

The parameterization data for a curve or surface is used to interpret 
all parametric data that the curve or surface references, 
including the trimming interval (for a curve) and the trimming domain (for a surface).
@{
*/

/*!
\brief Structure for parameterizing curves
\version 2.0

This structure is used in curve definitions (see \ref a3d_crv).
Its members specify a trimming interval (1-dimensional range)  
and parameterization settings.
Each curve has an implicit parameterization that corresponds to its canonical form.
The units of the actual parameterization and the units of the implicit parameterization may differ.

The \ref A3DParameterizationData structure provides two coefficients (affine function) 
that convert from the actual parameterization units to the implicit parameterization units.  
\li \c m_dCoeffA, which specifies the ratio between 
	the actual parameter's units and the implicit parameter's units 
\li \c m_dCoeffB, which specifies an offset between the two unit systems

Here are guidelines for setting these coefficients:
\li <i>Actual parameterization units match implicit parameterization units.</i> 
	If the units of the actual parameterization match the units of the implicit parameterization, then
	the \ref m_dCoeffA member must be set to 1 and the \ref m_dCoeffB member must be set to 0. 
\li <i>Actual parameterization units do not match the implicit parameterization units.</i>
	If the units of the actual parameterization do not match the units of the implicit parameterization, then
	the \ref m_dCoeffA member must be set to the ratio of the implicit parameterization's units
	and the actual parameterization's units, and the  \ref m_dCoeffB member must be set 
	to the offset between the units.

\note The trimming interval is always expressed in actual parameterization units.

\warning The initialization macro \ref A3D_INITIALIZE_DATA sets \ref m_dCoeffA and \ref m_dCoeffB to 0. 
	Leaving \ref m_dCoeffA set to 0 (unchanged) will result in an error.
	If no reparameterization is desired (the interval uses the same units as the implicit parameterization), 
	you must set \ref m_dCoeffA to <b>1.0</b>. 
*/
typedef struct
{
	A3DUns16			m_usStructSize;/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DIntervalData	m_sInterval;	/*!< Curve (1-dimensional) range. */
	A3DDouble			m_dCoeffA;		/*!< Coefficient for reparameterization. */
	A3DDouble			m_dCoeffB;		/*!< Coefficient for reparameterization. */
} A3DParameterizationData;

/*!
\brief Structure for parameterizing surfaces
\version 2.0

This structure is used in surface definitions (see \ref a3d_srf).
Its members specify a trimming domain (2-dimensional range)  
and parameterization settings.

It describes a surface reparameterization regarding the implicit parameterization that corresponds to its canonical form.
Here are some important points:
\li <i>Default settings.</i> If reparameterization is unnecessary (the implicit parameterization is used), 
	the \ref m_dUCoeffA and \ref m_dVCoeffA members must be set to 1, 
	the \ref m_dUCoeffB and \ref m_dVCoeffB members must be set to 0,
	and the \ref m_bSwapUV should be set to false. 
\li <i>UV domain.</i> The \ref m_sUVDomain member defines the 2-dimensional range  
	for a surface. Its coordinates are in the \b final parameterization space. 
	Parts of the object that are outside the bounding box are excluded from the view.
	The domain's units are specific for the surface type.
	For example, the units for a cylinder are degrees and linear units (typically millimeters).

Here is the evaluation formula for a given parameterization setting: 
\verbatim
if (swap_uv)
{
	implicit_param.u = parameterization_on_u_coeff_a * param.u + parameterization_on_u_coeff_b
	implicit_param.v = parameterization_on_v_coeff_a * param.v + parameterization_on_v_coeff_b
}
else
{
	implicit_param.u = parameterization_on_v_coeff_a * param.v + parameterization_on_v_coeff_b
	implicit_param.v = parameterization_on_u_coeff_a * param.u + parameterization_on_u_coeff_b
}
\endverbatim

To ensure that 
<code>implicit_param.u(min) < implicit_param.v(min)</code> and 
<code>implicit_param.u(max) < implicit_param.v(max)</code>,
you must specify parameterization values.
 
This example shows the settings to reparameterize a cylinder of 25mm height,
having an implicit parameterization of 2 PI radian in u and height in v,
to a domain of (0,0) and (1,1):
\li \ref m_dUCoeffA = 2 PI
\li \ref m_dUCoeffB = 0.
\li \ref m_dVCoeffA = 25
\li \ref m_dVCoeffB = 0.
\li \ref m_bSwapUV = false

And this example shows the member settings to retain the implicit parameterization (reparameterization is unnecessary):
\li \ref m_dUCoeffA = 1.
\li \ref m_dUCoeffB = 0.
\li \ref m_dVCoeffA = 1.
\li \ref m_dVCoeffB = 0.
\li \ref m_bSwapUV = false

*/
typedef struct
{
	A3DUns16			m_usStructSize;/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDomainData	m_sUVDomain;	/*!< Definition domain. */
	A3DBool				m_bSwapUV;		/*!< Need to swap U and V coordinates. */
	A3DDouble			m_dUCoeffA;		/*!< Coefficient for reparameterization along u vector. */
	A3DDouble			m_dVCoeffA;		/*!< Coefficient for reparameterization along v vector. */
	A3DDouble			m_dUCoeffB;		/*!< Coefficient for reparameterization along u vector. */
	A3DDouble			m_dVCoeffB;		/*!< Coefficient for reparameterization along v vector. */
} A3DUVParameterizationData;

/*!
@} <!-- end of a3d_parameterization module -->
*/
#endif	/*	__A3D_PARAMETERIZATION__ */


#endif	/*	__A3DPRCGEOMETRY_H__ */
