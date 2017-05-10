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
\brief      Header file for topology entities
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCTOPOLOGY_H__
#define __A3DPRCTOPOLOGY_H__

/*!
\defgroup a3d_topology_module Topology Module
\ingroup a3d_entitiesdata_module

This module defines the following types of topological entities:
\li Body: An exact 3D geometric representation of a solid, surfacic, or wireframe model. 
	A topology body entity is contained in a representation item entity.
\li Connex: For solids, a connex represents a continuous piece of material.
\li Shell: A hollow sphere is represented by two shells (one inner and one outer).
\li Face: Every shell is represented by a collection of faces sewn together. 
	Each face holds an associated geometric surface. 
\li Loop: A face may be trimmed by several loops (one outer loop and multiple inner loops). 
	Currently, \COMPONENT_A3D_API does not allow a face to have multiple outer loops.
	Instead, you can make several faces, each containing a single outer loop. 
\li Co-edge: A loop is a collection of oriented and ordered co-edges, containing space parametric curves 
	(if any), and neighboring information. The current version of \COMPONENT_A3D_API handles 
	only manifold solids which are solids that have single neighbors per co-edge.  
\li Edge: Each co-edge holds an edge, which in turn holds 3D information (if any), 
	such as 3D curves and vertices.

\note An \ref A3DTopoContext defines a global tolerance for every topological entity in this context.
	This global tolerance can then be superseded by less strict local tolerances for particular entities such as edges.

\section a3d_topotolerance Tolerance
In general, if the local tolerance is lower than the tolerance specified in the associated \ref A3DTopoContext entity, 
you must use the tolerance from the \ref A3DTopoContext entity.

\sa a3d_singlewirebody, a3d_brepdata, a3d_connex, a3d_shell, a3d_face, a3d_loop, a3d_coedge, a3d_edge,a3d_wireedge
*/

#ifndef __A3D_TOPOBODY__
/*!
\defgroup a3d_topobody Topology Body (the topology base entity)
\ingroup a3d_topology_module
\brief Sets and gets attributes that apply to all \ref A3DTopoBody entities

Entity type is \ref kA3DTypeTopoBody
\sa A3DTopoBody, A3DTopoBodyData, A3DTopoBodyGet, A3DTopoBodySet
*/

/*!
\brief Structure and bitmasks for establishing the bounding box orientation and context 
	of any type of \ref A3DTopoBody entity
\defgroup a3d_topobodydata Topology Body Data
\ingroup a3d_topobody
\version 2.0
\sa A3DTopoBodyData, A3DTopoBodyGet, A3DTopoBodySet

@{
*/

#define kA3DBodyBoundingBoxEvaluation	0x0001 /*!< The bounding box has been roughly evaluated from geometrical entities included in the body. */
#define kA3DBodyBoundingBoxPrecise		0x0002 /*!< The bounding box has been deduced from a complete tessellation of the body. */
#define kA3DBodyBoundingBoxCadData		0x0003 /*!< The bounding box has been read from the originating CAD file. */

/*!
\brief TopoBody structure
\version 2.0

The \ref m_ucBehaviour member is an array of bits that uses values 
from the topology body bitmask definitions (\ref a3d_topobodydata). 
The bitmasks are relevant only when the \ref A3DTopoBodyData structure is set for 
an \ref A3DTopoBody of type \ref kA3DTypeTopoBrepData (\ref A3DTopoBrepData); 
otherwise, the \ref m_ucBehaviour member must be set to 0.

\sa A3DTopoBodyData, A3DTopoBodyGet, A3DTopoBodySet
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns8 m_ucBehaviour;			/*!< Array of bits. */
	A3DTopoContext* m_pContext;		/*!< Pointer to an A3DTopoContext entity. */
} A3DTopoBodyData;
/*!
@} <!-- end of module a3d_topobodydata -->
*/

/*!
\brief Populates the \ref A3DTopoBodyData structure
\version 2.0

\ingroup a3d_topobody
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoBodyGet,(const A3DTopoBody* pBody,
										 A3DTopoBodyData* pData));

/*!
\brief Sets a previously created \ref A3DTopoBody with an \ref A3DTopoBodyData structure
\version 2.0

\ingroup a3d_topobody
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SET_INCONSISTENT_EMPTY \n	
\return \ref A3D_SUCCESS \n
\note Because an \ref A3DTopoBody entity is an abstract class, you cannot create directly such entity. 
Instead, use the appropriate derived function (such as \ref A3DTopoSingleWireBodyCreate or \ref A3DTopoBrepDataCreate)
to create a specific topology entity.
Then use this function to specify values in the entity base class.
For example, this function specifies a value for the \ref A3DTopoBodyData::m_pContext. 
*/
A3D_API (A3DStatus, A3DTopoBodySet,(A3DTopoBody* pBody,
										 const A3DTopoBodyData* pData));

#endif	/*	__A3D_TOPOBODY__ */

#ifndef __A3D_TOPOCONTEXT__
/*!
\defgroup a3d_topocontextdata Topology Context Data
\ingroup a3d_topocontext
\brief Structure and bitmasks for specifying the topology context 
	and common attributes such as granularity, tolerance, and thickness
\version 2.0

Entity type is \ref kA3DTypeTopoContext
\sa A3DTopoContext, A3DTopoContextData, A3DTopoContextGet, A3DTopoContextCreate
@{
*/
#define kA3DContextOuterLoopFirst	0x0001 /*!< Outer loops are always first loops. */
#define kA3DContextNoClamp				0x0002 /*!< UV Curves are clamped on surface. */
#define kA3DContextNoSplit				0x0004 /*!< Faces are split. */

/*!
\brief Structure for parsing or creating an \ref A3DTopoContext entity
\version 2.0

The \ref m_ucBehaviour member is a array of bits that uses values 
from the topology context bitmask definitions (\ref a3d_topocontextdata). 

\note \ref m_dScale is a conversion factor from the unit of the part (which is not 
mandatory millimeters) to the "unit" of the modeling kernel. In fact, there is NO 
notion of physical unit at the level of the "TopoContext". The numbers that are 
stored there do not have a physical significance by themselves. To interpret them, 
you should take into account the unit of the part and the "TopoContext" context 
scale. See the ISO doc chapter 2.6 and 2.7 for further explanation. Then, there 
can be further scale on the product hierarchy that should be taken into account 
when converting entities while respecting a given accuracy towards original 
geometry.

\sa A3DTopoContextData, A3DTopoContextGet, A3DTopoContextCreate

*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns8 m_ucBehaviour;					/*!< Array of bits. */
	A3DDouble m_dGranularity;				/*!< Minimal size of an edge. This value is non-dimensional. */
	A3DDouble m_dTolerance;					/*!< Global base tolerance used in the context for topological elements. This value is non-dimensional. */
	A3DBool m_bHaveSmallestFaceThickness;	/*!< True if next member is valid. */
	A3DDouble m_dSmallestThickness;			/*!< Smallest thickness for a face. Used in internal loop treatment. Default should be 100 * \ref m_dGranularity. */
	A3DBool m_bHaveScale;					/*!< True if next member is valid. */
	A3DDouble m_dScale;						/*!< Optional scale to interpret the data of the context. */
} A3DTopoContextData;

/*!
@} <!-- end of a3d_topocontextdata module -->
*/


/*!
\defgroup a3d_topocontext Topology Context
\ingroup a3d_topology_module
\brief Creates and accesses \ref A3DTopoContext entities, which specify topology context 
	and common attributes such as granularity, tolerance, and thickness.

Entity type is \ref kA3DTypeTopoContext

\sa A3DTopoContext, A3DTopoContextData, A3DTopoContextGet, A3DTopoContextCreate
@{
*/

/*!
\brief Populates the \ref A3DTopoContextData structure
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoContextGet,(const A3DTopoContext* pContext,
											 A3DTopoContextData* pData));

/*!
\brief Creates an \ref A3DTopoContext from an \ref A3DTopoContextData structure
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoContextCreate,(const A3DTopoContextData* pData,
												 A3DTopoContext** ppContext));

/*!
@} <!-- end of module a3d_topocontext -->
*/
#endif	/*	__A3D_TOPOCONTEXT__ */


#ifndef __A3D_TOPOSINGLEWIREBODY__
/*!
\defgroup a3d_singlewirebody SingleWireBody
\ingroup a3d_topology_module
\version 2.0

Entity type is \ref kA3DTypeTopoSingleWireBody
\sa A3DTopoSingleWireBody, A3DTopoSingleWireBodyData, A3DTopoSingleWireBodyGet, A3DTopoSingleWireBodyCreate
*/

/*!
\brief SingleWireBody structure
\ingroup a3d_singlewirebody
\sa A3DTopoSingleWireBodyData, A3DTopoSingleWireBodyGet, A3DTopoSingleWireBodyCreate
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DTopoWireEdge* m_pWireEdge;	/*!< Pointer to the A3DTopoWireEdge structure associated with this A3DTopoSingleWireBodyData */
} A3DTopoSingleWireBodyData;

/*!
\brief Populates the \ref A3DTopoSingleWireBodyData structure
\version 2.0
\ingroup a3d_singlewirebody
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoSingleWireBodyGet,(const A3DTopoSingleWireBody* pSingleWireBody,
													  A3DTopoSingleWireBodyData* pData));

/*!
\brief Creates an \ref A3DTopoSingleWireBody from an \ref A3DTopoSingleWireBodyData structure
\version 2.0
\ingroup a3d_singlewirebody
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoSingleWireBodyCreate,(const A3DTopoSingleWireBodyData* pData,
														  A3DTopoSingleWireBody** ppSingleWireBody));
#endif	/*	__A3D_TOPOSINGLEWIREBODY__ */


#ifndef __A3D_TOPOBREPDATA__
/*!
\defgroup a3d_brepdata BrepData
\ingroup a3d_topology_module

Entity type is \ref kA3DTypeTopoBrepData.

\section a3d_topoorientations Orientations
Here are some important points about \ref A3DTopoBrepData entity orientation:
\li Edges are implicitly oriented from the Start vertex toward the End vertex. 
\li 3D curves referenced by edges are oriented from the Start vertex toward the End vertex.
\li Co-edge has two flags that describe orientation:
	- Orientation with loop, which relates to the corresponding edge.
	- Orientation UV with loop, which relates to the space parametric curve attached to the co-edge, if defined. 
\li Loop is oriented regarding Ampere rule (in surface parametric space). 
\li Surface is oriented with the shell so that normals point from the material to the void.

Generally, a face containing a hole is defined with two loops having the same orientation. 
The outside loop is defined by the \c m_uiOuterLoopIndex member of an \ref A3DTopoFaceData structure, 
regardless of orientation. 
To get the real face normal vector, you must consider the surface normal vector 
and the \c m_pucOrientationWithShell member of the 
\ref A3DTopoShellData structure.

sa A3DTopoBrepData, A3DTopoBrepDataData, A3DTopoBrepDataGet, A3DTopoBrepDataCreate
*/

/*!
\brief BrepData structure
\ingroup a3d_brepdata
\version 2.0

The \c m_sBoundingBox member is valid only if the behaviour stored 
in the \c m_ucBehaviour member of the \ref A3DTopoBodyData is not null.
\sa A3DTopoBrepDataData, A3DTopoBrepDataGet, A3DTopoBrepDataCreate
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiConnexSize;			/*!< Number of \ref A3DTopoConnex in next array. */
	A3DTopoConnex** m_ppConnexes;		/*!< Array of \ref A3DTopoConnex. */
	A3DBoundingBoxData m_sBoundingBox;	/*!< Bounding box. */
} A3DTopoBrepDataData;

/*!
\brief Populates the \ref A3DTopoBrepDataData structure
\ingroup a3d_brepdata
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoBrepDataGet,(const A3DTopoBrepData* pBrep,
											  A3DTopoBrepDataData* pData));

/*!
\brief Creates an \ref A3DTopoBrepData from an \ref A3DTopoBrepDataData structure
\ingroup a3d_brepdata
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DTopoBrepDataCreate, (const A3DTopoBrepDataData* pData,
												  A3DTopoBrepData** ppBrep));

/*!
\brief Return all \ref A3DTopoFace from an \ref A3DTopoBrepData
\ingroup a3d_brepdata
\version 8.2

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DTopoBrepDataGetFaces, (A3DTopoBrepData const* psBrepData,
											 A3DUns32* psNbFaces,
											 A3DTopoFace*** papsFaces));

/*!
\brief Return all \ref A3DTopoEdge from an \ref A3DTopoBrepData
\ingroup a3d_brepdata
\version 8.2

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DTopoBrepDataGetEdges, (A3DTopoBrepData const* psBrepData,
											 A3DUns32* piNbEdges,
											 A3DTopoEdge*** papsEdges));

#endif	/*	__A3D_TOPOBREPDATA__ */


#ifndef __A3D_TOPOCONNEX__
/*!
\defgroup a3d_connex Connex
\ingroup a3d_topology_module
\version 2.0

Entity type is \ref kA3DTypeTopoConnex
\sa A3DTopoConnex, A3DTopoConnexData, A3DTopoConnexGet, A3DTopoConnexCreate
*/

/*!
\brief Connex structure
\ingroup a3d_connex
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiShellSize;		/*!< Number of \ref A3DTopoShell in next array. */
	A3DTopoShell** m_ppShells;	/*!< Array of \ref A3DTopoShell. */
} A3DTopoConnexData;

/*!
\brief Populates the \ref A3DTopoConnexData structure
\ingroup a3d_connex
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoConnexGet,(const A3DTopoConnex* pConnex,
											A3DTopoConnexData* pData));

/*!
\brief Creates an \ref A3DTopoConnex from an \ref A3DTopoConnexData structure
\ingroup a3d_connex
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoConnexCreate,(const A3DTopoConnexData* pData,
												A3DTopoConnex** ppConnex));
#endif	/*	__A3D_TOPOCONNEX__ */

#ifndef __A3D_TOPOSHELL__
/*!
\defgroup a3d_shell Shell
\ingroup a3d_topology_module
\version 2.0

Entity type is \ref kA3DTypeTopoShell
\sa A3DTopoShell, A3DTopoShellData, A3DTopoShellGet, A3DTopoShellCreate
*/

/*!
\brief Shell structure
\ingroup a3d_shell
\version 2.0

The \ref m_pucOrientationWithShell member is a bit array 
that denotes the orientation of the surface normal regarding the shell normal.
If the shell is closed and otherwise arbitrary, the shell normal points outside the material.
\note Possible values for the \ref m_pucOrientationWithShell[i] are as follows:
\li 0: Opposite orientations
\li 1: Same orientation for face and shell
\li 2: Unknown orientation
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bClosed;					/*!< Is the Shell closed? */
	A3DUns32 m_uiFaceSize;				/*!< Number of \ref A3DTopoFace in next array. */
	A3DTopoFace** m_ppFaces;			/*!< Array of \ref A3DTopoFace. */
	A3DUns8* m_pucOrientationWithShell;	/*!< For each face, orientation within the shell. */
} A3DTopoShellData;

/*!
\brief Populates the \ref A3DTopoShellData structure
\ingroup a3d_shell
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoShellGet,(const A3DTopoShell* pShell,
										  A3DTopoShellData* pData));

/*!
\brief Creates an \ref A3DTopoShell from an \ref A3DTopoShellData structure
\ingroup a3d_shell
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SHELL_INCONSISTENT_DATA \n
\return \ref A3D_SHELL_BAD_ORIENTATION_DATA \n
\return \ref A3D_SHELL_CANNOT_CREATE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoShellCreate,(const A3DTopoShellData* pData,
											  A3DTopoShell** ppShell));
#endif	/*	__A3D_TOPOSHELL__ */

#ifndef __A3D_TOPOFACE__
/*!
\defgroup a3d_face Face
\ingroup a3d_topology_module
\version 2.0

Entity type is \ref kA3DTypeTopoFace
\sa A3DTopoFace, A3DTopoFaceData, A3DTopoFaceGet, A3DTopoFaceCreate
*/

/*!
\ingroup a3d_face
\brief Face structure
\version 2.0

For the \ref m_sSurfaceDomain member, the face domain for the usage of the surface; must be included in surface's domain.
If not defined (that is, invalid domain with Min > Max), the face domain is the surface domain.

The number of loops: \ref m_uiLoopSize can be null, in this case the surface is bounded by its domain or by the face domain: \ref m_sSurfaceDomain if \ref m_bHasTrimDomain is true.

When parsing an \ref A3DTopoFaceData structure, use a tolerance that is the greater of these values:
\li \ref A3DTopoContextData::m_dTolerance member for the entity
\li \ref A3DTopoFaceData::m_dTolerance member for the entity 
\sa \ref a3d_topotolerance
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DSurfBase* m_pSurface;			/*!< Basis surface. Cannot be null. */
	A3DBool m_bHasTrimDomain;			/*!< Has the surface a trim domain? */
	A3DDomainData m_sSurfaceDomain;		/*!< Trimming domain for surface. */
	A3DUns32 m_uiLoopSize;				/*!< Number of \ref A3DTopoLoop in next array. */
	A3DTopoLoop** m_ppLoops;			/*!< Array of \ref A3DTopoLoop. None can be null. */
	A3DUns32 m_uiOuterLoopIndex;		/*!< Outer loop index. \ref A3D_LOOP_UNKNOW_OUTER_INDEX if unknown. */
	A3DDouble m_dTolerance;				/*!< Face tolerance. */
} A3DTopoFaceData;

/*!
\brief Populates the \ref A3DTopoFaceData structure
\ingroup a3d_face
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoFaceGet,(const A3DTopoFace* pFace,
										 A3DTopoFaceData* pData));

/*!
\brief Creates an \ref A3DTopoFace from an \ref A3DTopoFaceData structure
\ingroup a3d_face
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoFaceCreate,(const A3DTopoFaceData* pData,
											 A3DTopoFace** ppFace));

/*!
\brief Return the owning \ref A3DTopoShell  of the \ref A3DTopoFace inside the given \ref A3DTopoBrepData
\ingroup a3d_brepdata
\version 8.2

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DTopoFaceGetShell, (A3DTopoBrepData const* psBrepData,
										 A3DTopoFace const* psFace,
										 A3DTopoShell const** ppsShell));
#endif	/*	__A3D_TOPOFACE__ */

#ifndef __A3D_TOPOLOOP__
/*!
\defgroup a3d_loop Loop
\ingroup a3d_topology_module
Entity type is \ref kA3DTypeTopoLoop
\sa A3DTopoLoop, A3DTopoLoopData, A3DTopoLoopGet, A3DTopoLoopCreate
*/

/*!
\brief Loop structure
\ingroup a3d_loop
\version 2.0

The \ref m_ucOrientationWithSurface member denotes the orientation 
of the loop <b>"material left"</b> towards the surface normal.
The following values are defined for the \ref m_ucOrientationWithSurface member: 
\li 0: Opposite orientations between the loop and the surface
\li 1: Same orientation for the loop and the surface
\li 2: Unknown orientation
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns8 m_ucOrientationWithSurface;	/*!< Orientation within the surface. */
	A3DUns32 m_uiCoEdgeSize;			/*!< Number of \ref A3DTopoCoEdge in next array. */
	A3DTopoCoEdge** m_ppCoEdges;		/*!< Array of \ref A3DTopoCoEdge. None can be null. */
} A3DTopoLoopData;

/*!
\brief Populates the \ref A3DTopoLoopData structure
\ingroup a3d_loop
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoLoopGet,(const A3DTopoLoop* pLoop,
										 A3DTopoLoopData* pData));

/*!
\brief Creates an \ref A3DTopoLoop from an \ref A3DTopoLoopData structure
\ingroup a3d_loop
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoLoopCreate,(const A3DTopoLoopData* pData,
											 A3DTopoLoop** ppLoop));

/*!
\brief Return the owning \ref A3DTopoFace  of the \ref A3DTopoLoop inside the given \ref A3DTopoBrepData
\ingroup a3d_brepdata
\version 8.2

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DTopoLoopGetFace, (A3DTopoBrepData const* psBrepData,
										A3DTopoLoop const* psLoop,
										A3DTopoFace const** ppsFace));
#endif	/*	__A3D_TOPOLOOP__ */

#ifndef __A3D_TOPOCOEDGE__
/*!
\defgroup a3d_coedge CoEdge
\ingroup a3d_topology_module
\version 2.0

Entity type is \ref kA3DTypeTopoCoEdge
\sa A3DTopoCoEdge, A3DTopoCoEdgeData, A3DTopoCoEdgeGet, A3DTopoCoEdgeCreate
*/

/*!
\brief Co-edge structure
\ingroup a3d_coedge
\version 2.0

The following values are defined for the \ref m_ucOrientationWithLoop (orientation between edge and loop)
and \ref m_ucOrientationUVWithLoop (orientation between uv_curve and loop) members:

\li 0: Opposite orientation
\li 1: Same orientation
\li 2: Unknown orientation
\note The \ref m_pUVCurve member must either reference a curve of type \ref kA3DTypeCrvNurbs, 
	or it must be NULL. 
\note Neighbors are connected one to one in a cyclic linked list. 
	No pointer can be repeated in that list.
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns8 m_ucOrientationWithLoop;	/*!< Orientation of the edge with the loop. */
	A3DUns8 m_ucOrientationUVWithLoop;	/*!< Orientation of the uv_curve with the loop. */
	A3DTopoEdge* m_pEdge;				/*!< Pointer to \ref A3DTopoEdge. */
	A3DCrvBase* m_pUVCurve;				/*!< Pointer to parametric space curve. */
	A3DTopoCoEdge* m_pNeighbor;			/*!< Pointer to list of neighbors. */
} A3DTopoCoEdgeData;

/*!
\brief Populates the \ref A3DTopoCoEdgeData structure
\ingroup a3d_coedge
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoCoEdgeGet,(const A3DTopoCoEdge* pCoEdge,
											A3DTopoCoEdgeData* pData));

/*!
\brief Creates an \ref A3DTopoCoEdge from an \ref A3DTopoCoEdgeData structure
\ingroup a3d_coedge
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoCoEdgeCreate,(const A3DTopoCoEdgeData* pData,
												A3DTopoCoEdge** ppCoEdge));


/*!
\brief Sets the \ref A3DTopoCoEdge neighbor on an \ref A3DTopoCoEdge
\ingroup a3d_coedge
\version 2.0

\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoCoEdgeSetNeighbour,(A3DTopoCoEdge* pCoEdge,
														A3DTopoCoEdge* pNeighbour));

A3D_API(A3DStatus, A3DTopoCoedgeGetLoop, (A3DTopoCoEdge const* psCoEdge,
										  A3DTopoLoop** ppsLoop));
		

#endif	/*	__A3D_TOPOCOEDGE__ */

#ifndef __A3D_TOPOEDGE__
/*!
\defgroup a3d_edge Edge
\ingroup a3d_topology_module
Entity type is \ref kA3DTypeTopoEdge

\sa A3DTopoEdge, A3DTopoEdgeData, A3DTopoEdgeGet, A3DTopoEdgeCreate
*/

/*!
\ingroup a3d_edge
\brief Edge structure
\version 2.0

When parsing this structure, use a tolerance that is the greatest of these values:
\li \ref A3DTopoContextData::m_dTolerance member for the entity
\li \ref A3DTopoEdgeData::m_dTolerance member for the entity
\sa \ref a3d_topotolerance

\note See note about orientation in \ref a3d_topology_module.
\warning If the \ref m_p3dCurve member is null, 
	either the edge is degenerated or all co-edges have UV curves.
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DTopoVertex* m_pStartVertex;		/*!< Start vertex; can be either an \ref A3DTopoMultipleVertex or an \ref A3DTopoUniqueVertex. */
	A3DTopoVertex* m_pEndVertex;		/*!< End vertex; can be either an \ref A3DTopoMultipleVertex or an \ref A3DTopoUniqueVertex. */
	A3DCrvBase* m_p3dCurve;				/*!< Pointer to 3D space curve. */
	A3DBool m_bHasTrimDomain;			/*!< A value of true indicates the edge has a trim domain. */
	A3DIntervalData	m_sInterval;		/*!< Trimming domain for 3D curve. */
	A3DDouble m_dTolerance;				/*!< Edge tolerance. */
} A3DTopoEdgeData;

/*!
\brief Populates the \ref A3DTopoEdgeData structure
\ingroup a3d_edge
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoEdgeGet,(const A3DTopoEdge* pEdge,
										 A3DTopoEdgeData* pData));

/*!
\brief Creates an \ref A3DTopoEdge from an \ref A3DTopoEdgeData structure
\ingroup a3d_edge
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoEdgeCreate,(const A3DTopoEdgeData* pData,
											 A3DTopoEdge** ppEdge));

/*!
\brief Return all \ref A3DTopoCoEdge from an \ref A3DTopoEdge within the given A3DTopoBrepData
\ingroup a3d_edge
\version 8.2

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DTopoEdgeGetCoEdges, (const A3DTopoBrepData* psBrepData,
										   const A3DTopoEdge* psEdge,
												 A3DUns32* piNbCoedges,
												 A3DTopoCoEdge*** papsCoEdges));

/*!
\brief Return all \ref A3DSurfBase from an \ref A3DTopoEdge within the given A3DTopoBrepData
\ingroup a3d_edge
\version 8.2

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DTopoEdgeGetSurfaces, (const A3DTopoBrepData* psBrepData,
											const A3DTopoEdge* psEdge,
												  A3DUns32* piNbSurfaces,
												  A3DSurfBase*** papsSurfaces));

/*!
\brief Return a \ref A3DCrvBase (3D curve or computed A3DCrvOnSurf) from an \ref A3DTopoEdge within the given A3DTopoBrepData
\ingroup a3d_edge
\version 8.2

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DTopoEdgeGetOrCompute3DCurve, (A3DTopoBrepData const* psBrepData,
													A3DTopoEdge const* psEdge,
													A3DCrvBase const** pps3DCurve));

#endif	/*	__A3D_TOPOEDGE__ */

#ifndef __A3D_TOPOWIREEDGE__
/*!
\defgroup a3d_wireedge WireEdge
\ingroup a3d_topology_module
Entity type is \ref kA3DTypeTopoWireEdge

\sa A3DTopoWireEdge, A3DTopoWireEdgeData, A3DTopoWireEdgeGet, A3DTopoWireEdgeCreate
*/

/*!
\brief WireEdge structure
\ingroup a3d_wireedge
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DCrvBase* m_p3dCurve;				/*!< Pointer to 3D space curve. */
	A3DBool m_bHasTrimDomain;			/*!< A value of true indicates the edge has a trim domain. */
	A3DIntervalData	m_sInterval;		/*!< Trimming domain for 3D curve. */
} A3DTopoWireEdgeData;

/*!
\brief Populates the \ref A3DTopoWireEdgeData structure
\ingroup a3d_wireedge
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoWireEdgeGet,(const A3DTopoWireEdge* pWireEdge,
											  A3DTopoWireEdgeData* pData));

/*!
\brief Creates an \ref A3DTopoWireEdge from an \ref A3DTopoWireEdgeData structure
\ingroup a3d_wireedge
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoWireEdgeCreate,(const A3DTopoWireEdgeData* pData,
												  A3DTopoWireEdge** ppWireEdge));
#endif	/*	__A3D_TOPOWIREEDGE__ */

#ifndef __A3D_TOPOVERTEX__
/*!
\defgroup a3d_vertex Vertex
\ingroup a3d_topology_module
This entity defines vertices that are tied to edges. 
A vertex can be defined by a single position (\ref A3DTopoUniqueVertex) or by multiple
positions (\ref A3DTopoMultipleVertex). 
*/

/*!
\defgroup a3d_unique_vertex Vertex defined with a single position
\ingroup a3d_vertex
\version 2.0

Entity type is \ref kA3DTypeTopoUniqueVertex.

This entity describes a tolerant vertex, which is a 3D point combined with a real tolerance. 
This can be visualized as a sphere centered on the vertex
with the sphere's radius set to the tolerance  
in which the real vertex of the edge is defined. Please refer to any documentation upon 
tolerances in 3D tolerant-modelling. 
\image html A3DPRCTopologyUniqueVertex.jpg
\sa A3DTopoUniqueVertex, A3DTopoUniqueVertexData, A3DTopoUniqueVertexGet, A3DTopoUniqueVertexCreate
*/

/*!
\brief Structure for a vertex defined with a single position
\ingroup a3d_unique_vertex
\version 2.0

\note See note in \ref a3d_topology_module.
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dTolerance;		/*!< Associated tolerance. See related note. */
	A3DVector3dData m_sPoint;	/*!< 3D point. */
} A3DTopoUniqueVertexData;

/*!
\brief Populates the \ref A3DTopoUniqueVertexData structure
\ingroup a3d_unique_vertex
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoUniqueVertexGet,(const A3DTopoUniqueVertex* pUniqueVertex,
													A3DTopoUniqueVertexData* pData));

/*!
\brief Creates an \ref A3DTopoUniqueVertexData from an \ref A3DTopoUniqueVertexData structure
\ingroup a3d_unique_vertex
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoUniqueVertexCreate,(const A3DTopoUniqueVertexData* pData,
														A3DTopoUniqueVertex** ppUniqueVertex));


/*!
\defgroup a3d_multiple_vertex Vertex defined with multiple positions
\ingroup a3d_vertex
Entity type is \ref kA3DTypeTopoMultipleVertex.

A multiple vertex is defined as the average position of several 3D points, 
which are typically the endpoints of edge curves that end at this vertex.

\image html A3DPRCTopologyMultipleVertex.jpg
\warning In general, no constraint is given to the 3D points stored in the array referenced by the \ref A3DTopoMultipleVertexData::m_pPts member. 
In particular, the same point (same coordinates) may appear multiple times 
in that array. 
This is a common behavior, and all these points must be taken into account to evaluate the tolerance.
*/

/*!
\brief Structure for a vertex defined with multiple positions
\ingroup a3d_multiple_vertex
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiSize;			/*!< Size of next array. */
	A3DVector3dData* m_pPts;	/*!< Collection of 3D points. */
} A3DTopoMultipleVertexData;

/*!
\brief Populates the \ref A3DTopoMultipleVertexData structure
\ingroup a3d_multiple_vertex
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoMultipleVertexGet,(const A3DTopoMultipleVertex* pMultipleVertex,
													  A3DTopoMultipleVertexData* pData));

/*!
\brief Creates an \ref A3DTopoMultipleVertex from an \ref A3DTopoMultipleVertexData structure
\ingroup a3d_multiple_vertex
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTopoMultipleVertexCreate,(const A3DTopoMultipleVertexData* pData,
														  A3DTopoMultipleVertex** ppMultipleVertex));

#endif	/*	__A3D_TOPOVERTEX__ */

#endif	/*	__A3DPRCTOPOLOGY_H__ */
