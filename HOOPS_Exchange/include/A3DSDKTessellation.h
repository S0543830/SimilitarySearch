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
\brief      Header file for tessellation
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCTESSELLATION_H__
#define __A3DPRCTESSELLATION_H__

#ifndef __A3D_TESS__
/*!
\defgroup a3d_tessellation_module Tessellation Module
\ingroup a3d_entitiesdata_module
\brief Creates and accesses tessellation entities

This module describes how to access and encode tessellation for a variety of entities. 
It also provides information about tessellations, associated textures, and markup representations. 

\par Usage
Tessellation entities can appear in the \c pTessBase member of all types of representation items, 
except \ref A3DRiCoordinateSystem and \ref A3DRiPointSet.

If your application parses PRC content, you must develop dedicated functions to parse the base tessellation data 
and to parse each type of tessellation entity. The following sample code demonstrates the following basic steps:
<ol>
	<li>Use the \ref A3DTessBaseGet function to get the tessellation base data.</li>
	<li>Use the \ref A3DEntityGetType function to determine the specific tessellation type.</li>
	<li>Invoke a custom function to parse the entity contents.</li>
</ol>
\par Sample code
\include TessellationModule.cpp
\sa \ref A3DTess3D
\sa \ref A3DTess3DWire
\sa \ref A3DTessMarkup
*/

/*!
\brief Functions for setting and getting data common to all tessellation entities
\defgroup a3d_tessellation_base Tessellation Base
\ingroup a3d_tessellation_module
\par

Entity type is \ref kA3DTypeTessBase.
@{
*/

/*!
\brief Structure for defining tessellation base data
\version	2.0

*/
typedef struct
{
	A3DUns16		m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool			m_bIsCalculated;	/*!< A value of true indicates that during import tessellation was calculated from exact geometry. */
	A3DUns32		m_uiCoordSize;		/*!< Number of \ref A3DDouble in next array. */
	A3DDouble*		m_pdCoords;			/*!< Array of \ref A3DDouble. See \ref A3DTess3DData, \ref A3DTess3DWireData, or \ref A3DTessMarkupData for explanations. */
} A3DTessBaseData;

/*!
\brief Populates the \ref A3DTessBaseData structure
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTessBaseGet,(const A3DTessBase* pTessBase,
										 A3DTessBaseData* pData));

/*!
\brief Function to set the tessellation base from the \ref A3DTessBaseData structure 
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_TESSBASE_INCONSISTENT \n
\return \ref A3D_TESSBASE_POINTS_INCONSISTENT_DATA \n
\return \ref A3D_TESSBASE_POINTS_BAD_SIZE \n
\return \ref A3D_SUCCESS\n
*/
A3D_API (A3DStatus, A3DTessBaseSet,(A3DTessBase* pTessBase,
										 const A3DTessBaseData* pData));
/*!
@}
*/

#endif	/*	__A3D_TESS__ */

#ifndef __A3D_TESS_TESSFACE__
/*!
\defgroup a3d_tessface TessFace
\ingroup a3d_tess3d
\brief Functions and structures for defining tessellation face data

Entity type is \ref kA3DTypeTessFace.

This entity is used only within the \ref kA3DTypeTess3D entity and is never shared. 
Therefore, no pointer is available for this entity type.
\sa A3DTessFaceData
*/

/*!
\defgroup a3d_tessfacetype Bitmasks for Specifying Tessellation Types
\ingroup a3d_tessface
\brief Bitmasks for specifying the type of tessellation face data 
	for the \ref A3DTessFaceData::m_usUsedEntitiesFlags member
\version 2.0
@{
*/
/*!
\brief Not currently supported

Not currently supported. */
#define kA3DTessFaceDataPolyface 							0x0001
/*!
\brief Simple triangle

Simple triangle that is described with six indexes (normal, point, normal, point, normal, point). */
#define kA3DTessFaceDataTriangle							0x0002
/*!
\brief Triangle fan 

Triangle fan that is described with 2*n indexes (normal, point, ..., normal, point). */
#define kA3DTessFaceDataTriangleFan							0x0004
/*!
\brief Triangle strip

Triangle strip that is described with 2*n indexes (normal, point, ..., normal, point). */
#define kA3DTessFaceDataTriangleStripe						0x0008
/*!
\brief Not currently supported.

Not currently supported. */
#define kA3DTessFaceDataPolyfaceOneNormal					0x0010
/*!
\brief Simple triangle with one normal

Simple triangle with one normal, which is described with 4 indexes (normal, point, point, point). */
#define kA3DTessFaceDataTriangleOneNormal					0x0020
/*!
\brief Triangle fan with one normal 
	and other characteristics depending on \ref kA3DTessFaceDataNormalSingle

Triangle fan with one normal and one of the following characteristics, 
depending on whether the normal behavior for \b OneNormal entities 
as specified in the \ref kA3DTessFaceDataNormalSingle bit: 
\li If the \ref kA3DTessFaceDataNormalSingle bit is set, the face data is described 
	with n+1 indexes (normal, point, point, ..., point). 
\li Otherwise, the face data is described with 2*n indexes (normal, point, ..., normal, point),
	which is the same as the \ref kA3DTessFaceDataTriangleFan tessellation face data type.
*/
#define kA3DTessFaceDataTriangleFanOneNormal				0x0040
/*!
\brief Triangle strip with one normal and with indexes 
	as specified by the \ref kA3DTessFaceDataNormalSingle bit

Triangle strip with one normal and with indexes as specified by the \ref kA3DTessFaceDataNormalSingle bit:
\li If \ref kA3DTessFaceDataNormalSingle is not set, the face is described 
	with 2*n indexes (normal, point, ..., normal, point) if \ref kA3DTessFaceDataNormalSingle is not set.
	This is the same case as \ref kA3DTessFaceDataTriangleStripe.
\li If \ref kA3DTessFaceDataNormalSingle is set, 
	it is described with n+1 indexes (normal, point, point, ..., point). 
*/
#define kA3DTessFaceDataTriangleStripeOneNormal				0x0080
/*!
\brief Not currently supported

Not currently supported. */
#define kA3DTessFaceDataPolyfaceTextured					0x0100
/*!
\brief Simple triangle with texture

Simple triangle with texture, which is the same as the \ref kA3DTessFaceDataTriangle face type
with the addition of indexes for texture coordinates. 
These texture coordinate indexes are added to the \ref A3DTess3DData::m_puiTriangulatedIndexes array 
between the normal and point indexes.
The number of the texture coordinate is given by the corresponding \ref A3DTessFaceData::m_uiTextureCoordIndexesSize.
For example: (normal,{texture...},point,normal,{texture...},point,normal,{texture...},point)
*/
#define kA3DTessFaceDataTriangleTextured					0x0200
/*!
\brief Triangle fan with texture

Triangle fan with texture, which is the same as \ref kA3DTessFaceDataTriangleFan
with the addition of indexes for texture coordinates. 
These texture coordinate indexes are added to the \ref A3DTess3DData::m_puiTriangulatedIndexes array 
between the normal and point indexes.
The number of texture indexes is given by the corresponding \ref A3DTessFaceData::m_uiTextureCoordIndexesSize.
For example: (normal,{texture...},point,normal,{texture...},point,normal,{texture...},point).
*/
#define kA3DTessFaceDataTriangleFanTextured					0x0400
/*!
\brief Triangle strip with texture

Triangle strip with texture, which is the same as \ref kA3DTessFaceDataTriangleStripe
with the addition of indexes for texture coordinates.
These texture coordinate indexes are added to the \ref A3DTess3DData::m_puiTriangulatedIndexes array 
between the normal and point indexes.
The number of texture indexes is given by the corresponding  \ref A3DTessFaceData::m_uiTextureCoordIndexesSize.
For example: (normal,{texture...},point,normal,{texture...},point,...,normal,{texture...},point)
*/
#define kA3DTessFaceDataTriangleStripeTextured				0x0800
/*!
\brief Not currently supported

Not currently supported. */
#define kA3DTessFaceDataPolyfaceOneNormalTextured			0x1000
/*!
\brief Simple triangle with one normal and texture

Simple triangle with one normal and texture, which is the same as \ref kA3DTessFaceDataTriangleOneNormal
with the addition of indexes for texture coordinates.
These texture coordinate indexes are added to the \ref A3DTess3DData::m_puiTriangulatedIndexes array 
between the normal and point indexes.
The number of texture indexes is given by the corresponding  \ref A3DTessFaceData::m_uiTextureCoordIndexesSize.
For example: (normal,{texture...},point,{texture...},point,{texture...},point)
*/
#define kA3DTessFaceDataTriangleOneNormalTextured			0x2000
/*!
\brief Triangle fan with one normal and texture 

Triangle fan with one normal and texture, which is the same as \ref kA3DTessFaceDataTriangleFanOneNormal
with the addition of indexes for texture coordinates.
These texture coordinate indexes are added to the \ref A3DTess3DData::m_puiTriangulatedIndexes array 
between the normal and point indexes.
The number of texture indexes is given by the corresponding  \ref A3DTessFaceData::m_uiTextureCoordIndexesSize.
For example: 
\li (normal, {texture...}, point, ..., normal, {texture...}, point) if \ref kA3DTessFaceDataNormalSingle is not set 
\li (normal, {texture...}, point, ..., {texture...}, point) if \ref kA3DTessFaceDataNormalSingle is set
*/
#define kA3DTessFaceDataTriangleFanOneNormalTextured		0x4000
/*!
\brief Triangle strip with one normal and texture

Triangle strip with one normal and texture, which is the same as \ref kA3DTessFaceDataTriangleStripeOneNormal
with the addition of indexes for texture coordinates.
These texture coordinate indexes are added to the \ref A3DTess3DData::m_puiTriangulatedIndexes array 
between the normal and point indexes.
The number of  texture indexes is given by the corresponding  \ref A3DTessFaceData::m_uiTextureCoordIndexesSize.
For example: 
\li (normal, {texture...}, point, ..., normal, {texture...}, point) if \ref kA3DTessFaceDataNormalSingle is not set 
\li (normal, {texture...}, point, ..., {texture...}, point) if \ref kA3DTessFaceDataNormalSingle is set
*/
#define kA3DTessFaceDataTriangleStripeOneNormalTextured		0x8000	
/*!
@} <!-- end of a3d_tessfacetype -->
*/

/*!
\defgroup a3d_tessfaceflags Bitmasks for Loop Characteristics in Face Loops
\ingroup a3d_tessface
\brief Bitmasks for specifying loop characteristics of face wires in the \ref A3DTessFaceData::m_puiSizesWires array
\version 2.0
@{
*/
#define kA3DTessFaceDataWireIsNotDrawn						0x4000 	/*!< Current wire is not to be drawn. */
#define kA3DTessFaceDataWireIsClosing						0x8000	/*!< Current wire is closing on first point. */
/*!
@} <!-- end of a3d_tessfaceflags -->
*/

/*!
\defgroup a3d_tessfacenormal Bitmasks for Behavior of Normals
\ingroup a3d_tessface
\brief Bitmasks used to set and access the \ref A3DTessFaceData::m_usUsedEntitiesFlags
\version 2.0

If this flag is set, the corresponding OneNormal entity (see \ref a3d_tessfacetype) 
is planar and only one normal is defined for the entity. 
Otherwise, one normal per point is defined. 
@{
*/
#define kA3DTessFaceDataNormalSingle	0x40000000	/*!< Bit indicating normal behavior for \b OneNormal entities. */
#define kA3DTessFaceDataNormalMask		0x3FFFFFFF	/*!< Access to real value of number of entities. */
/*!
@} <!-- end of a3d_tessfacenormal -->
*/

/*!
\struct A3DTessFaceData
\ingroup a3d_tessface
\brief Structure that describes basic entities per face for solid or surface mesh representations
\version 2.0
 
In the context of solid or surface mesh representations, an entity can be a triangle, 
a fan, or a strip, with all declinations described for the the \ref A3DTess3DData structure.

The \ref m_uiStyleIndexesSize member has these values:
\li 0 indicates that there are no graphics (in this case, all graphics are inherited 
	from the owner (parent) of the \ref A3DTess3DData).
\li 1 indicates that one graphic is associated with the face.
\li Greater than 1 indicates that the number of graphics is linked to the number of entities 
	in the \ref m_puiSizesTriangulated member.

\par Wireframe representation

The following \ref A3DTessFaceData members are for wireframe faces:
\li \ref m_uiStartWire : The starting index for the wire in the array of point indexes of the \ref A3DTess3DData.
\li \ref m_puiSizesWires : Array of the number of indexes for each wire edge of the face, 
	where the number of indexes is ANDed with the relevant flags 
	\ref kA3DTessFaceDataWireIsNotDrawn and/or \ref kA3DTessFaceDataWireIsClosing.
	In an \ref A3DTessFaceData structure, the size of a wire edge is limited to 
	16383 (0x3FFF) points. When both flags are set, they have the value 0xC000.

Consider an example of an \ref A3DTessFaceData structure in which both loops describe closed wire edges:
\li First loop consists of two wire edges: 
- First edge has 10 points.
- Second edge has 20 points.
\li Second loop consists of one edge having 12 points.

For this example, the \ref m_puiSizesWires array has these entries:
<b>[0x0010, 0x4020, 0x4012]</b>. 
The second and third array entries are the number of edges ANDed with the \ref kA3DTessFaceDataWireIsNotDrawn (0x4000).
Notice that the indexes for each edge's extremity are always stored. 
Therefore, the tenth point of the first edge is followed by the first point of the second edge. 

\par Solid representation

The following \ref A3DTessFaceData members are for solid representations:
\li \ref m_usUsedEntitiesFlags (see \ref a3d_tessfacetype): This flag specifies how to interpret the array \ref m_puiSizesTriangulated.\n
\li \ref m_uiStartTriangulated : Starting index for the triangulated data in the array of point indexes of the \ref A3DTess3DData.\n
\li \ref m_puiSizesTriangulated : Array of the number of indexes for each triangulated entity of the face. \n

The triangulated data sizes are stored following the order of values in \ref a3d_tessfacetype. 
Thus, the triangles are stored before the triangle fans and before the triangles textured. 
\li For triangle types, the \ref m_puiSizesTriangulated member specifies the number of triangles. 
\li For triangle fan and strips types, the \ref m_puiSizesTriangulated member specifies the number of fans or stripes 
	followed by the product of the number of fans or strips n times the number of points for each of them.

Consider an example of an \ref A3DTessFaceData structure that describes five triangles, 
two fans of 5 and 7 points respectively, and one strip of 11 indexes.
For this example, set \ref m_usUsedEntitiesFlags to \ref kA3DTessFaceDataTriangle & \ref kA3DTessFaceDataTriangleFan & \ref kA3DTessFaceDataTriangleStripe \n
\ref m_puiSizesTriangulated is [5,2,5,7,1,11]. 

In case of the tessellation type \b kA3DTessFaceData*OneNormal, 
the number of points can bear the flag \ref kA3DTessFaceDataNormalSingle,
modifying the way of reading normals information. In such a case, you must use \ref kA3DTessFaceDataNormalSingle to characterize
status and \ref kA3DTessFaceDataNormalMask to access to real value.

The following \ref A3DTessFaceData members also apply to solid representations:
\li \ref m_pucRGBAVertices : Colors stored directly on vertices. Either there is no color on vertices or every 
vertex must bear a color. Therefore, \ref m_uiRGBAVerticesSize is either 0 or equal to the number of point indexes 
as calculated from \ref m_uiSizesTriangulatedSize. (In the previous example, this is 38 = 5*3 + 5 + 7 + 11).
\li \ref m_bIsRGBA : If true, the color scheme is RGBa; otherwise, it is RGB. 
\li \ref m_usBehaviour : This member denotes the graphics behavior for this \ref A3DTessFaceData towards owning entity in the tree, 
as described in \ref a3d_graphicsbits.
For face behavior, \ref kA3DGraphicsShow and \ref kA3DGraphicsRemoved are not currently supported.
\li \ref m_uiTextureCoordIndexesSize : Number of texture coordinate indexes (see \ref a3d_tessfacetype).
*/
typedef struct
{
	A3DUns16	m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32	m_uiStyleIndexesSize;			/*!< Size of next array. */
	A3DUns32*	m_puiStyleIndexes;				/*!< Array of display styles. See explanations above. */
	A3DUns32	m_uiStartWire;					/*!< See explanations above. */
	A3DUns32	m_uiSizesWiresSize;				/*!< Size of next array. */
	A3DUns32*	m_puiSizesWires;				/*!< See explanations above. */
	A3DUns16	m_usUsedEntitiesFlags;			/*!< Bit field containing list of used entities in current face tessellation. See explanations above. \sa a3d_tessfacetype*/
	A3DUns32	m_uiStartTriangulated;			/*!< See explanations above. */
	A3DUns32	m_uiSizesTriangulatedSize;		/*!< Size of next array. */
	A3DUns32*	m_puiSizesTriangulated;			/*!< See explanations above. */
	A3DBool		m_bIsRGBA;						/*!<
													A value of true specifies that the array is made of RGBA. 
													A value of false indicates that it is made of RGB. */
	A3DUns32	m_uiRGBAVerticesSize;			/*!< Size of next array. */
	A3DUns8*	m_pucRGBAVertices;				/*!< See explanations above. */
	A3DUns16	m_usBehaviour;					/*!< See explanations above. */
	A3DUns32	m_uiTextureCoordIndexesSize;	/*!< See explanations above. */
} A3DTessFaceData;

#endif	/*	__A3D_TESS_TESSFACE__ */

#ifndef __A3D_TESS_3DTESS__
/*!
\defgroup a3d_tess3d Tess3D
\ingroup a3d_tessellation_module
\brief Tessellation for solids and surfaces

Entity type is \ref kA3DTypeTess3D.

An \ref A3DTess3D is a tessellation dedicated to solids and surfaces. This structure is a derivation of \ref A3DTessBase
and can be obtained by using the \ref A3DTessBaseGet function on any \ref A3DRiRepresentationItem.
This structure may contain collections of points that define mesh vertices, normals (per vertex, per entity), and UV coordinates if 
textures are stored.
*/

/*!
\brief Structure used to create or parse an \ref A3DTess3D entity
\ingroup a3d_tess3d
\version 2.0

\note The \ref A3DTess3D entity includes data stored in the \ref A3DTessBase entity.

Structure containing all global information for solid representation.

The \ref m_bHasFaces member indicates whether the \ref A3DTess3D entity is built with a concept of geometrical faces.

Point coordinates \ref A3DTessBaseData::m_pdCoords are taken 3 by 3 to build up 3D vectors.

Normal coordinates \ref m_pdNormals are taken 3 by 3 to build up 3D vectors.

Wire indexes in the \ref m_puiWireIndexes array are the point indexes describing the face's wire 
contours in the array of points of \ref A3DTessBaseData::m_pdCoords.

Triangulated indexes \ref m_puiTriangulatedIndexes are the point, normal, and texture indexes describing the 
face triangulated representation (triangles, triangle fans, triangle strips) in the array 
of points, normals, and textures coordinates. The indexes are multiples of 3 for points and normals, and should be multiples of 
1 to 4 for textures coordinates.

The contents of the \ref A3DTessFaceData structure specifies how to interpret the data in this array, 
as described in \ref a3d_tessface.

The contents of the \ref A3DTessFaceData structure also  specifies 
how the texture coordinates \ref m_pdTextureCoords are interpreted according to the 
final graphics of each \ref A3DTessFaceData. This graphics is given either on the \ref A3DTessFaceData structure 
or by the representation item owning the \ref A3DTess3DData. Then, this graphics  corresponds 
to a texture with an appropriate number of coordinates.

An \ref A3DTessFaceData structure corresponds to a geometrical face if there is an indication that the tessellation has face data 
(as denoted by \ref m_bHasFaces). Otherwise, it is simply a large container of any tessellated data.


\warning \ref A3DTessBaseData::m_uiCoordSize represents the size of the array referenced by \ref A3DTessBaseData::m_pdCoords. 
It is not the number of 3D points. 
*/
typedef struct
{
	A3DUns16			m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32			m_bHasFaces;					/*!< A value of true indicates the geometrical face notion. */
	A3DUns32			m_uiNormalSize;					/*!< Number of \ref A3DDouble in next array. */
	A3DDouble*			m_pdNormals;					/*!< Array of \ref A3DDouble, \b x \b y \b z for each normal. */
	A3DUns32			m_uiWireIndexSize;				/*!< Size of next array. */
	A3DUns32*			m_puiWireIndexes;				/*!< Array of indexes of points in A3DTessBaseData::m_pdCoords. */
	A3DUns32			m_uiTriangulatedIndexSize;		/*!< Size of next array. */
	A3DUns32*			m_puiTriangulatedIndexes;		/*!< Array of indexes of points in A3DTessBaseData::m_pdCoords. */
	A3DUns32			m_uiFaceTessSize;				/*!< Number of \ref A3DTessFaceData in next array. */
	A3DTessFaceData*	m_psFaceTessData;				/*!< Array of face tessellation definition. */
	A3DUns32			m_uiTextureCoordSize;			/*!< Number of \ref A3DDouble in next array. */
	A3DDouble*			m_pdTextureCoords;				/*!< Array of \ref A3DDouble, as texture coordinates. */
	A3DBool				m_bMustRecalculateNormals;		/*!< Normals must be recalculated. */
	A3DUns8				m_ucNormalsRecalculationFlags;	/*!< Unused parameter. */
	A3DDouble			m_dCreaseAngle;					/*!< Unused parameter; definition similar to VRML. */
} A3DTess3DData;

/*!
\brief Populates the \ref A3DTess3DData structure
\ingroup a3d_tess3d
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTess3DGet,(const A3DTess3D* pTess,
									  A3DTess3DData* pData));

/*!
\brief Creates an \ref A3DTess3D from an \ref A3DTess3DData structure
\ingroup a3d_tess3d
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_TESS3D_NORMALS_INCONSISTENT_DATA \n
\return \ref A3D_TESS3D_NORMALS_BAD_SIZE \n
\return \ref A3D_TESS3D_FACE_INCONSISTENT_DATA \n
\return \ref A3D_TESSFACE_TRIANGULATED_INCONSISTENT_DATA \n
\return \ref A3D_TESSFACE_TRIANGULATED_INCONSISTENT_EMPTY \n
\return \ref A3D_TESSFACE_USEDENTITIES_BAD_TYPE \n
\return \ref A3D_TESSFACE_STARTTRIANGULATED_INCONSISTENT_DATA \n
\return \ref A3D_TESSFACE_STARTWIRE_INCONSISTENT_DATA \n
\return \ref A3D_TESSFACE_STYLEINDEXESSIZE_INCONSISTENT_DATA \n
\return \ref A3D_TESSFACE_RGBAVERTICESSIZE_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTess3DCreate,(const A3DTess3DData* pData,
										  A3DTess3D** ppTess));

#endif	/*	__A3D_TESS_3DTESS__ */

#ifndef __A3D_TESS_3DWIRE__
/*!
\defgroup a3d_tess3dwire Tess3DWire
\ingroup a3d_tessellation_module
\brief Tessellation for 3D wireframes

Entity type is \ref kA3DTypeTess3DWire.

An \ref A3DTess3DWire is a tessellation dedicated to curves. This structure is a derivation of \ref A3DTessBase
and can be obtained by using the \ref A3DTessBaseGet function on any \ref A3DRiRepresentationItem entity.
*/

/*!
\defgroup a3d_tess3dwireflags Flags for Specifying Wire Characteristics
\ingroup a3d_tess3dwire
\brief Bitmasks used in the \ref A3DTess3DWireData structure to describe wire characteristics
\version 2.0

These bitmasks must be applied on the first unsigned int containing the number of related indexes in the array
used to described current wire. 
@{
*/
#define  kA3DTess3DWireDataIsClosing		0x10000000	/*!< The current wire is closed. */
#define  kA3DTess3DWireDataIsContinuous		0x20000000	/*!< Indicates that the last point of preceding wire should be linked with the first point of the current one. */

/*!
@}
*/

/*!
\struct A3DTess3DWireData
\brief 3D wire data structure
\ingroup a3d_tess3dwire
\version 2.0

\note The \ref A3DTess3DWire entity includes data stored in the \ref A3DTessBaseData structure.

The \ref A3DTessBaseData::m_pdCoords member represents point coordinates, 
which are interpreted in groups of three (X, Y, Z) to represent 3D vectors.

The \ref m_uiSizesWiresSize member represents the number of wire indexes in the whole \ref A3DTess3DWireData.  
The \ref m_puiSizesWires member references an array of wire indexes in the array of points \ref A3DTessBaseData::m_pdCoords.

If \ref m_uiSizesWiresSize is zero, the tessellation is given as a single wire edge with the array 
of points contained as described in \ref A3DTessBaseData::m_pdCoords.
Conversely, if \ref m_uiSizesWiresSize is non-zero, the array referenced by \ref m_puiSizesWires describes 
single edges as follows: 

<center>[number of indexes in the wire edge, indexes of the wire edge,.....]</center>

Continuing with the non-zero case, the number of indexes can include the flags described in \ref a3d_tess3dwireflags.

Consider the following example of two wires of three points, then 4 others: 
\li \ref m_uiSizesWiresSize = 9 = (3+1+4+1)\n
\li \ref m_puiSizesWires = [3,index point 1, index point 2, index point 3, 4, index point 1, index point 2, index point 3, index point 4]\n
\li \ref m_pucRGBAVertices specifies the number of colors for each vertex. 
A value of 0 specifies that no colors are associated with any vertex.
A non-zero value specifies the number of colors associated with very vertex. 
Therefore, \ref m_uiRGBAVerticesSize is either 0 or equal 
to the number of colors per vertex times the number of point indexes as calculated from \ref m_puiSizesWires.\n

If the last point of the first wire is linked to the first point of the second wire, the stored values are as follows:\n
\ref m_puiSizesWires = [3, index point 1, index point 2, index point 3, 4 | 
\ref kA3DTess3DWireDataIsContinuous, index point 1, index point 2, index point 3, index point 4]

If the second wire is closed, the stored values are as follows:\n
\ref m_puiSizesWires = [3, index point 1, index point 2, index point 3, 4 | 
\ref kA3DTess3DWireDataIsClosing, index point 1, index point 2, index point 3, index point 4]

\warning Implicit points coming from \ref a3d_tess3dwireflags must also bear a color.

The following \ref A3DTess3DWireData members also apply to wire representations:
\li \ref m_bIsRGBA : A value of true indicates the color is RGBA; a value of false indicates RGB. 
\li \ref m_bIsSegmentColor : A value of true indicates the color is for the whole segment; in this case, there is n-1 colors 
for n vertices; otherwise, color is per vertex. 

\warning \ref A3DTessBaseData::m_uiCoordSize represents size of array \ref A3DTessBaseData::m_pdCoords and not a number of 3D points. 
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiSizesWiresSize;	/*!< Size of next array. */
	A3DUns32* m_puiSizesWires;		/*!< See explanations in \b Detailed \b Description. */
	A3DBool m_bIsRGBA;				/*!< See explanations in \b Detailed \b Description. */
	A3DBool m_bIsSegmentColor;		/*!< See explanations in \b Detailed \b Description. */
	A3DUns32 m_uiRGBAVerticesSize;	/*!< Size of next array. */
	A3DUns8* m_pucRGBAVertices;		/*!< See explanations above. */
} A3DTess3DWireData;

/*!
\brief Populates the \ref A3DTess3DWireData structure
\ingroup a3d_tess3dwire
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTess3DWireGet,(const A3DTess3DWire* pTess,
											A3DTess3DWireData* pData));
/*!
\brief Creates the \ref A3DTess3DWire from \ref A3DTess3DWireData structure
\ingroup a3d_tess3dwire
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_TESSWIRE_RGBAVERTICESSIZE_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTess3DWireCreate,(const A3DTess3DWireData* pData,
												A3DTess3DWire** ppTess));



#endif	/*	__A3D_TESS_3DWIRE__ */

#ifndef __A3D_TESS_MARKUP__
/*!
\defgroup a3d_tessmarkup Tessellation for Markups
\ingroup a3d_tessellation_module
\brief Tessellation for markups

Entity type is \ref kA3DTypeTessMarkup.

The tessellation uses two arrays: one for the codes and another for the coordinates.
The codes array describes the type of contents in tessellation (the entities).
The coordinates array contains point coordinates and other floating point values used by the entities.
The coordinates array is specified in the \ref A3DTessBaseData structure.

Each entity occupies at least two codes. The first code contains the entity type and the number of specific codes.
The second code contains the number of doubles (coordinates) for the entity. 
The doubles (coordinates) are in the coordinates array of the \ref A3DTessBaseData structure.

\par Explanation of the first code:

Use one of the following masks to identify the entity type with the first code:
\li \ref kA3DMarkupIsMatrix denotes a matrix.
\li \ref kA3DMarkupIsExtraData indicates other entities (extra data).
\li \ref kA3DMarkupExtraDataType is the type of extra data.

If none of these masks are set, the entity is a polyline.

\ref kA3DMarkupIsMatrix must not be set if \ref kA3DMarkupIsExtraData is set and \ref kA3DMarkupExtraDataType represents
the type of entity only if \ref kA3DMarkupIsExtraData is set.<br>
The \ref kA3DMarkupIntegerMask mask represents the number of codes that refers to the entity (inner codes).<br>
\ref kA3DMarkupIsMatrix and \ref kA3DMarkupIsExtraData are booleans; whereas, \ref kA3DMarkupExtraDataType is
an integer.<br>
The other bits should be set to zero.

See \ref a3d_tessmarkupflags and \ref a3d_tessmarkupextradata for more details.

\par Explanation of the second code:

The second code is the number of doubles needed by the entity. 
Each time the first double of block refers to updated position within 
BaseData Coord array: starting from 0 if reading a matrix first and next double value to read will be at Coord[16].

The following table describes the inner codes and doubles that can be defined for each entity.
It also describes the extra data type number.


\verbatim
Entity              Extra data type   Number of inner codes     Number of doubles
---------------------------------------------------------------------------------------------
Polyline            none              0                         number of points * 3
Matrix mode[1]      none              0 or number in block      0 or number in block
Pattern                0              3 + number of loops       number of points in loops * 3
Picture                1              1                         0
Triangles              2              0                         number of triangles * 9
Quads                  3              0                         number of quads * 12
Face view mode[1]      6              0 or number in block      0 or number in block
Frame draw mode[1]     7              0 or number in block      0 or number in block
Fixed size mode[1]     8              0 or number in block      0 or number in block
Symbol                 9              1                         3
Cylinder              10              0                         3
Color                 11              1                         0
Line stipple[2]       12              0 or 1                    0
Font                  13              2                         0
Text                  14              1                         2
Points                15              0                         number of points * 3
Polygon               16              0                         number of points * 3
Line width[2]         17              0                         0 or 1
\endverbatim
See \ref A3D_ENCODE_EXTRA_DATA macro to encode extra data.

\par About Blocks

Blocks are defined by face view, frame draw, fixed size, and matrix modes (indicated by [1]).
Each block is surrounded by the corresponding entity. At the start of a block, the entity modifies
the state (style, current transformation matrix, ...). Then this state is restored at the end of the block.
For example, a matrix mode starts by defining a matrix (which will multiply the current transformation matrix),
draws some entities, and ends with another matrix mode entity for indicating the end of the mode.

[1]
The face view, frame draw, fixed size, and matrix modes start with the corresponding entity
and end with the same entity; therefore, they define blocks.
The starting entity has a non-zero number of inner codes. It represents the number of codes until the end of the block,
excluding the 2 mandatory codes for each entity. The same rule applies to the doubles.
The ending entity has 0 inner codes and 0 doubles.
The use of this number is to easily skip a block when reading tessellation.
To treat the content of a block, the numbers to use are as follows:

\verbatim
Mode                      Number of inner codes          Number of doubles
--------------------------------------------------------------------------------
Face view (starting)      0                              3
Face view (ending)        0                              0
Frame draw (starting)     0                              3
Frame draw (ending)       0                              0
Fixed size (starting)     0                              3
Fixed size (ending)       0                              0
Matrix (starting)         0                              16
Matrix (ending)           0                              0
\endverbatim

For example: matrix mode
\verbatim
        --+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
Codes     |  |M1|16|C |C |C |C |C |C |C |C |C |C |C |M2|0 |
        --+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
\endverbatim

M1 code is \ref kA3DMarkupIsMatrix (0 additional code), which is the same as M2.
This example shows the codes for defining a matrix mode. The M1 code defines the beginning 
of the matrix mode, and the M2 code defines the closing of that mode. The number of doubles for the M1 code is 16.
After that, some entities are drawn (the Cs) and the M2 code defines the end of the matrix mode. 
The M2 code has 0 codes and 0 doubles because it is only reverting back to the initial matrix.

[2]
The line stipple and line width modes operate identically to [1], but the numbers
correspond to the entity only and not to the block. This is because the treatment
of those can be more easily omitted than for the previous ones.
For line stipple mode, the number of inner codes denotes the start (1) or the end (0) of the block.
For line width mode, the number of doubles denotes the start (1) or the end (0) of the block.

\par Explanation of each entity:

The array for each entity is organized as described here:
\li First column shows the mandatory codes and the inner codes
\li Second column shows the doubles 

\b Polyline

\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0                                 X
number of points * 3              Y
                                  Z
\endverbatim
There is a (x,y,z) triplet for each point of the polyline.

\b Triangles

A list of triangles.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0                                 X
number of triangles * 9           Y
                                  Z
\endverbatim
There is a (x,y,z) triplet for each point of the triangle list.

\b Quads

A list of quads.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0                                 X
number of quads * 12              Y
                                  Z
\endverbatim
There is a (x,y,z) triplet for each point of the quad list.

\b Polygon

\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0                                 X
number of points * 3              Y
                                  Z
\endverbatim
There is a (x,y,z) triplet for each point of the polygon.

\b Points

A list of points.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0                                 X
number of points * 3              Y
                                  Z
\endverbatim
There is a (x,y,z) triplet for each point.

<b>Face view mode</b>

In this mode, all the drawing entities are parallel to the screen (billboard).
The point given in the doubles corresponds to the origin of the new coordinate system in
which we draw parallel to the screen.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0 or number in block              X
0 or number in block              Y
                                  Z
\endverbatim

<b>Frame draw mode</b>

In this mode, all the drawing entities are given in 2D space.
The point given in the doubles corresponds to a 3D point projected onto the screen giving
origin of 2D coordinate system in which we draw in 2D (viewport).
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0 or number in block              X
0 or number in block              Y
                                  Z
\endverbatim

<b>Fixed size mode</b>

In this mode, all the drawing entities are drawn at a fixed size, independant of the zoom setting.
The point given in the doubles corresponds to the origin of the new coordinate system in which
we draw at fixed size.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0 or number in block              X
0 or number in block              Y
                                  Z
\endverbatim

<b>Matrix mode</b>

In this mode, all the drawing entities are transformed by the current transformation matrix
multiplied by the matrix given in the doubles.
At the end of the mode, the previously active transformation matrix is restored.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0 or number in block              a(1,1)
0 or number in block              a(2,1)
                                  a(3,1)
                                  a(4,1)
                                  a(1,2)
                                  a(2,2)
                                  ...
                                  a(3,4)
                                  a(4,4)
\endverbatim

\b Symbol

The point given in the doubles corresponds to the position of the symbol in 3D.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
1                                 X
3                                 Y
id of pattern                     Z
\endverbatim
The pattern is an \ref A3DGraphVPicturePatternData type.
The pattern identifier is obtained by invoking the \ref A3DGlobalInsertGraphVPicturePattern function.

\b Color

This entity defines a color that will be effective until a new one is defined.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
1                                  
0                                 
id of color
\endverbatim
Color identifier is obtained by invoking the \ref A3DGlobalInsertGraphRgbColor function.

<b>Line stipple mode</b>

This entity defines the style that will be effective inside the block.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0 or 1
0
id of style
\endverbatim
The first code is 1 for beginning the block and 0 for ending the block.
The style identifier is obtained by invoking the \ref A3DGlobalInsertGraphStyle function.

\b Font

This entity defines the font used for the Text entity (described next).
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
2
0
family index
style index/size index/attributes
\endverbatim
The indexes and the attributes are taken from the \ref A3DFontKeyData structure.
To create the \ref A3DFontKeyData structure, invoke the \ref A3DGlobalFontKeyCreate function.

The font style, size indexes, and attributes are encoded into a single code 
by using the bitmasks in \ref a3d_tessmarkupfontkeydef. See \ref a3d_fonts.

\b Text

This entity defines a text string to be rendered with the current font (defined by \ref A3DFontData entity). 
\sa \ref a3d_fonts

\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
1                                 W
2                                 H
index of text
\endverbatim
The index of text refers to the zero-based text index in \ref A3DTessMarkupData::m_ppcTexts.<br>
The \b W and \b H correspond to the width and height (respectively) of text in real display coordinates.

<b>Line width mode</b>

This entity defines the line width that will be effective inside the block.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0                                 W
0 or 1
\endverbatim
The number of doubles is 1 for beginning the block and 0 for ending the block.
The \b W double is the line width to use in the block.
There is no \b W double when ending the block.

\b Cylinder

\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
0                                 Base radius
3                                 Top radius
                                  Height
\endverbatim
The cylinder is positioned by a matrix mode, oriented with Z axis, base at Z = 0 and top at Z = Height.

\b Picture

This entity defines a picture positioned at the current position.
\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
1
0
id of picture
\endverbatim
Picture identifier is obtained by invoking the \ref A3DGlobalInsertGraphPicture function.

\b Pattern

\verbatim
Codes                             Doubles
--------------------------------------------------------------------------------
3 + number of loops               X
number of points in loops * 3     Y
id of pattern                     Z
filled mode
behavior
number of points for loop 1
...
number of points for loop n
\endverbatim
The filled mode is one of these values: \c 0=OR, \c 1=AND, or \c 2=XOR.
The behavior is a bit field, with the 0x1 bit specifying whether to ignore the view transformation. 
If true, the pattern is not transformed by the current view transformation. 
The other bits should be set to zero.
There is a (x,y,z) triplet for each point of loops, sequentially.

Pattern identifier is created by invoking one of the following functions:
\li \ref A3DGlobalInsertGraphDottingPattern
\li \ref A3DGlobalInsertGraphHatchingPattern
\li \ref A3DGlobalInsertGraphSolidPattern
\li \ref A3DGlobalInsertGraphVPicturePattern
*/

/*!
\defgroup a3d_tessmarkupflags Bitmasks for A3DTessMarkupData tessellation
\ingroup a3d_tessmarkup
\version 2.0

\par Sample Use
\include TessMarkupFlags.cpp

To encode color type entities \b and the following masks that apply to your color type:

00000100-00000000-00000000-00000000	kA3DMarkupIsExtraData<br>
00000001-01100000-00000000-00000000	kA3DMarkupColorMask<br>
00000000-00000000-00000000-00000001	Number of additional codes = 1<br>

Here is an example of a code corresponding to a color:

00000101-01100000-00000000-00000001	(In decimal form, this value is 90177537.)

And with no associated doubles, the three codes for a color type are:<br>
uiCode[n] = 90177537;<br>
uiCode[n+1] = 0; no doubles<br>
uiCode[n+2] = id_of_color;<br>

For encoding/decoding extra data types, use macros defined in \ref a3d_tessmarkupextradata.

\sa a3d_tessmarkup
@{
*/
#define kA3DMarkupIsMatrix			0x08000000		/*!< Bit to denote whether the current entity is a matrix. */
#define kA3DMarkupIsExtraData		0x04000000		/*!< Bit to denote whether the current entity is extra data (neither matrix nor polyline). */
#define kA3DMarkupIntegerMask		0xFFFFF			/*!< Integer mask to retrieve sizes. */
#define kA3DMarkupExtraDataType		0x3E00000		/*!< Mask to get the integer type of the entity. */
/*!
@} <!-- end of module a3d_tessmarkupflags -->
*/

/*!
\defgroup a3d_tessmarkupextradata Extra data types for A3DTessMarkupData tessellation
\ingroup a3d_tessmarkup
\version 2.0
@{
*/
#define kA3DMarkupPatternMask		0x000000		/*!< Mask to encode pattern type entity. */
#define kA3DMarkupPictureMask		0x200000		/*!< Mask to encode picture type entity. */
#define kA3DMarkupTrianglesMask		0x400000		/*!< Mask to encode triangles type entity. */
#define kA3DMarkupQuadsMask			0x600000		/*!< Mask to encode quads type entity. */
#define kA3DMarkupFaceViewMask		0xC00000		/*!< Mask to encode face view mode. */
#define kA3DMarkupFrameDrawMask		0xE00000		/*!< Mask to encode frame draw mode. */
#define kA3DMarkupFixedSizeMask		0x1000000		/*!< Mask to encode fixed size mode. */
#define kA3DMarkupSymbolMask		0x1200000		/*!< Mask to encode symbol type entity. */
#define kA3DMarkupCylinderMask		0x1400000		/*!< Mask to encode cylinder type entity. */
#define kA3DMarkupColorMask			0x1600000		/*!< Mask to encode color type entity. */
#define kA3DMarkupLineStippleMask	0x1800000		/*!< Mask to encode line stipple type entity. */
#define kA3DMarkupFontMask			0x1A00000		/*!< Mask to encode font type entity. */
#define kA3DMarkupTextMask			0x1C00000		/*!< Mask to encode text type entity. */
#define kA3DMarkupPointsMask		0x1E00000		/*!< Mask to encode point type entities. */
#define kA3DMarkupPolygonMask		0x2000000		/*!< Mask to encode polygonal type entity. */
#define kA3DMarkupLineWidthMask		0x2200000		/*!< Mask to encode line width type entity. */

/*! Macro to encode an extra data type for storing in a markup's tessellation.

The \c ExtraDataType parameter must be set with one of the above markup encoding definitions. 
The \c InnerCodes parameter is the number of inner codes associated with the extra data.
*/
#define A3D_ENCODE_EXTRA_DATA(ExtraDataType, InnerCodes) ((kA3DMarkupIsExtraData | ExtraDataType) + InnerCodes)
/*! Macro to decode the extra data type from a markup's tessellation code. */
#define A3D_DECODE_EXTRA_DATA(TessCode) ((TessCode & kA3DMarkupExtraDataType) >> 21)
/*!
@} <!-- end of module a3d_tessmarkupflags -->
*/

/*!
\defgroup a3d_tessmarkupdef Bitmasks for markup options
\ingroup a3d_tessmarkup
\sa a3d_tessmarkup
\version 2.0
@{
*/
#define kA3DMarkupIsHidden				0x01 /*!< The tessellation is hidden. */
#define kA3DMarkupHasFrame				0x02 /*!< The tessellation has a frame. */
#define kA3DMarkupIsNotModifiable		0x04 /*!< The tessellation is given and must not be modified. */
#define kA3DMarkupIsZoomable			0x08 /*!< The tessellation is zoomable. */
#define kA3DMarkupIsOnTop				0x10 /*!< The tessellation is on top of geometry. */
#define kA3DMarkupIsNotRotatable		0x20 /*!< The tessellation is not rotatable. /version 9.0 */
/*!
@} <!-- end of a3d_tessmarkupdef -->
*/

/*!
\defgroup a3d_tessmarkupfontkeydef Masks for encoding font keys
\ingroup a3d_tessmarkup
\par Sample Use of the masks for Encoding Font Keys
\include TessMarkupFontKey.cpp

\sa a3d_tessmarkup
@{
*/
#define kA3DFontKeyAttrib		0x00000FFF /*!< Mask to encode the font attributes of the \ref A3DFontKeyData structure into the \ref A3DTessMarkupData structure. */
#define kA3DFontKeySize			0x00FFF000 /*!< Mask to encode the font size index of the \ref A3DFontKeyData structure into the \ref A3DTessMarkupData structure. */
#define kA3DFontKeyStyle		0xFF000000 /*!< Mask to encode the font style index of the \ref A3DFontKeyData structure into the \ref A3DTessMarkupData structure. */
/*!
@} <!-- end of a3d_tessmarkupfontkeydef -->
*/

/*!
\brief TessMarkupData structure
\ingroup a3d_tessmarkup
\version 2.0

The \ref A3DTessMarkup entity contains data stored in the \ref A3DTessBaseData structure.
For this structure, the \ref A3DTessBaseData::m_bIsCalculated is not applicable and must be set to false.

For information about the values for the \ref m_cBehaviour member, see \ref a3d_tessmarkupdef.

Text referenced by the \ref m_ppcTexts member must be UTF-8 encoded.
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiCodesSize;		/*!< Size of next array. */
	A3DUns32* m_puiCodes;		/*!< Array of codes. See explanations in \ref a3d_tessmarkup. */
	A3DUns32 m_uiTextsSize;		/*!< Size of next array. */
	A3DUTF8Char** m_ppcTexts;	/*!< Texts used in tessellation. See explanations in \ref a3d_tessmarkup. */
	A3DUTF8Char* m_pcLabel;		/*!< Markup label. */
	A3DInt8 m_cBehaviour;		/*!< Flags for tessellation. See \ref a3d_tessmarkupdef. */
} A3DTessMarkupData;

/*!
\brief Populates the \ref A3DTessMarkupData structure
\ingroup a3d_tessmarkup
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTessMarkupGet,(const A3DTessMarkup* pTess,
											A3DTessMarkupData* pData));

/*!
\brief Creates an \ref A3DTessMarkup entity from an \ref A3DTessMarkupData structure
\ingroup a3d_tessmarkup
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_TESSMARKUP_HAS_INVALID_FONTKEY \n
\return \ref A3D_TESSMARKUP_HAS_INVALID_TEXT_INDEX \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DTessMarkupCreate,(const A3DTessMarkupData* pData,
												A3DTessMarkup** ppTess));

/*!< \ingroup a3d_tessmarkup */

#endif	/*	__A3D_TESS_MARKUP__ */

#endif	/*	__A3DPRCTESSELLATION_H__ */
