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
\brief      Root entities section
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCROOTENTITIES_H__
#define __A3DPRCROOTENTITIES_H__



/*!
\defgroup a3d_entitiesdata_module Entity Access and Creation
\brief Collection of modules that create and access PRC entities

This module contains the functions and structures for parsing and creating PRC entities. 
It includes modules for specific 3D entities (\ref a3d_structure_module, \ref a3d_topology_module, and \ref a3d_graphics_module)
and for helper PRC entities. Modules that describe such helper PRC entities include 
\ref a3d_rootentities_module (provides names and modeller data for PRC entities) 
and \ref a3d_global_data_module (describes an indexed repository of color and layer settings).

*/

/*!
@} <!-- end of module a3d_entitiesdata_module --> 
*/

/*!
\defgroup a3d_rootentities_module Root Entities Module
\ingroup a3d_entitiesdata_module
\brief Creates and accesses root entities that can be associated with any PRC entity or with any graphics PRC entity

This module defines the root entity attributes that apply to all PRC entities
or to all PRC entities in the \ref a3d_graphics_module.

All PRC entities declared by \COMPONENT_A3D_API are of type \ref A3DEntity. 
All \ref A3DEntity entities inherit the \ref A3DRootBase entity, 
which can include text names that provide modeller data and other data about the 
more specific form of the PRC entities. 

PRC entities in the \ref a3d_graphics_types also inhert the \ref A3DRootBaseWithGraphics entity.
The \ref A3DRootBaseWithGraphics entity has attributes that reference 
graphics data stored in \ref A3DGlobal PRC entities and that specify
inheritance behaviour. 
*/

/*!
@} <!-- a3d_rootentities_module -->
*/

#ifndef __A3D_BASE__
/*!
\defgroup a3d_base Entity Base
\ingroup a3d_rootentities_module
\brief Creates and accesses a hierarchy of descriptive names and modeller data that can be applied to any PRC entity

Entity type is \ref kA3DTypeRootBase

This module lets you create a hierarchy of descriptive names and modeller data (called <i>root-level attributes</i>) 
that can be applied to any PRC entity. These attributes are packaged as an \ref A3DRootBase entity that is referenced 
from the PRC entity they describe. 

The following sample code shows how to create root-level attributes for any PRC entity. 
In this case, the attributes include modeller data. 
For restrictions on specifying modeller data, see \ref A3DMiscAttributeData.

\include MiscAttributeCreation.cpp

The following illustration shows the result of the sample code. 

The sample code creates an \ref A3DRootBase entity that houses three \ref A3DMiscAttribute entities, 
each of which reference an \ref A3DMiscSingleAttributeData structure. 
Each \ref A3DMiscSingleAttributeData structure provides modeller data of type \ref kA3DModellerAttributeTypeString.

\image html PRC_RootAttributes.png

\sa a3d_root_types


*/

/*!
\brief A structure representing a hierarchy of descriptive names and modeler data that applies to any PRC entity
\ingroup a3d_base
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiSize;					/*!< Size of next array. */
	A3DMiscAttribute** m_ppAttributes;	/*!< Array of pointers to \ref A3DMiscAttribute structures. \sa a3d_attribute */
	A3DUTF8Char* m_pcName;				/*!< String containing entity name. */
	A3DUns32 m_uiPersistentId;			/*!< Persistent ID. \version 2.2 */
	A3DUTF8Char* m_pcPersistentId;		/*!< Persistent ID other version, as CLSID, Name... */
	A3DUns32 m_uiNonPersistentId;		/*!< Non persistent ID. \version 2.2 */
} A3DRootBaseData;

/*!
\brief Populates an \ref A3DRootBaseData structure with the data from a PRC entity
\ingroup a3d_base
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRootBaseGet,(const A3DRootBase* pRootBase,
												A3DRootBaseData* pData));

/*!
\brief Adds an \ref A3DRootBaseData structure to an existing PRC entity 
\ingroup a3d_base
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
\note \ref A3DRootBase is an abstract class and cannot be directly created; 
however, any entity created with a function of the form <code>A3D<i>Entity_name</i>Create</code> results 
in the creation of a PRC entity of type \c A3DRootBase and of type <code>A3D<i>Entity_name</i></code>.
*/
A3D_API (A3DStatus, A3DRootBaseSet,(A3DRootBase* pRootBase,
												const A3DRootBaseData* pData));

#endif	/*	__A3D_BASE__ */


#ifndef __A3D_BASEWITHGRAPHICS__
/*!
\defgroup a3d_basewithgraphics Entity Base with Graphics
\ingroup a3d_rootentities_module
\brief Creates and accesses global graphic characteristics that apply to any PRC entity in the \ref a3d_graphics_module
\version 2.0

Entity type is \ref kA3DTypeRootBaseWithGraphics.

Any PRC entity that bears graphics can have an \ref A3DRootBaseWithGraphics entity. 

The \ref A3DRootBaseWithGraphics entity references graphic attributes
such as line patterns, RGB colors, and textures.
Those graphic attributes are used in the more specific PRC entity.

\sa a3d_graphics

*/

/*!
\brief A structure specifying root graphics data
\ingroup a3d_basewithgraphics
\version 2.0

*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DGraphics* m_pGraphics;	/*!< Associated graphics. \sa a3d_graphics */
} A3DRootBaseWithGraphicsData;

/*!
\brief Populates the \ref A3DRootBaseWithGraphicsData structure
\ingroup a3d_basewithgraphics
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DRootBaseWithGraphicsGet,(const A3DRootBaseWithGraphics* pRoot, 
																A3DRootBaseWithGraphicsData* pData));

/*!
\brief Adds an \ref A3DRootBaseWithGraphicsData structure to an existing \ref A3DRootBaseWithGraphics entity
\ingroup a3d_basewithgraphics
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
\note The \ref A3DRootBaseWithGraphics entity type is an abstract class and cannot be directly created; 
however, any graphic entity created with a function of the form <code>A3D<i>Graphics_entity_name</i>Create</code> results 
in the creation of a PRC entity of type \c A3DRootBaseWithGraphics and of type <code>A3D<i>Entity_name</i></code>.
That is, a function of the form <code>A3D<i>Graphics_entity_name</i>Create</code>  
adds specific data to the base class, for example \ref A3DRootBaseWithGraphicsData::m_pGraphics. 
*/
A3D_API (A3DStatus, A3DRootBaseWithGraphicsSet,(A3DRootBaseWithGraphics* pRoot,
																const A3DRootBaseWithGraphicsData* pData));

#endif	/*	__A3D_BASEWITHGRAPHICS__ */



#ifndef __A3D_ATTRIBUTE__
/*!
\defgroup a3d_attribute Miscellaneous Attribute Entity
\ingroup a3d_base
\brief Creates and accesses descriptive names and modeller data associated with PRC entities
\version 2.0

Entity type is \ref kA3DTypeMiscAttribute.

This structure defines the miscellaneous attributes owned by an \ref A3DRootBase entity.

*/

/*!
\brief An enumeration that identifies the type of modeller data represented in an \ref A3DMiscSingleAttributeData structure
\ingroup a3d_attribute
*/
typedef enum
{
	kA3DModellerAttributeTypeNull  = 0,			/*!< Null type; invalid. */
	kA3DModellerAttributeTypeInt = 1,			/*!< Integer (32-bit). */
	kA3DModellerAttributeTypeReal = 2,			/*!< Floating point. */
	kA3DModellerAttributeTypeTime = 3,			/*!< Integer (32-bit), interpreted like \c time_t. */
	kA3DModellerAttributeTypeString = 4		/*!< UTF-8 character string. */
} A3DEModellerAttributeType;

/*!
\brief A structure that specifies modeler data attribute
\ingroup a3d_attribute
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bTitleIsInt;				/*!< A value of TRUE indicates the \ref m_pcTitle member represents an integer. */
	A3DUTF8Char* m_pcTitle;				/*!< Title as string. */
	A3DEModellerAttributeType m_eType;	/*!< Attribute type. */
	A3DUTF8Char* m_pcData;				/*!< Data chunk to be interpreted according to previous type. */
} A3DMiscSingleAttributeData;

/*!
\brief A structure that specifies descriptive names and modeller data
\ingroup a3d_attribute
\version 2.0

The \ref A3DMiscAttributeData structure specifies a descriptive name as a single character string or integer. It can also reference an \ref A3DMiscSingleAttributeData structure, which specifies modeller data. 

If \ref m_bTitleIsInt is true, \ref m_pcTitle contains an unsigned integer (A3DUns32).

\warning When an \ref A3DMiscAttributeData structure references an \ref A3DMiscSingleAttributeData structure, its members must be set as follows: 
<ul>
	<li>Reference a single \ref A3DMiscSingleAttributeData structure. </li>
	<li>Have a \c m_pcTitle value identical to the corresponding member 
		in the \ref A3DMiscSingleAttributeData it references.</li>
</ul>

\warning Although this structure contains an \c m_uiSize member, the \c m_pSingleAttributesData member references the structure itself, not an array of pointers to structures. 

<! I removed this pseudocode from another sample because the code was misleading. -->
Pseudocode to implement Attributes:
\code
A3DVoid stSetAttributes(A3DEntity* p)
{
	A3DMiscAttribute* pAttr[3];

	A3DMiscSingleAttributeData Single;
	A3D_INITIALIZE_DATA(A3DMiscSingleAttributeData, Single);

	Single.m_eType = kA3DModellerAttributeTypeString;
	Single.m_pcTitle = (char*) "Title";
	Single.m_pcData = (char*) "Simple B-rep building demonstration";

	A3DMiscAttributeData sAttribs;
	A3D_INITIALIZE_DATA(A3DMiscAttributeData, sAttribs);

	sAttribs.m_pcTitle = Single.m_pcTitle;
	sAttribs.m_pSingleAttributesData = &Single;
	sAttribs.m_uiSize = 1;
	A3DMiscAttributeCreate(&sAttribs, &pAttr[0]);

	Single.m_pcTitle = (char*) "Author";
	Single.m_pcData = (char*) "HOOPS Exchange";
	sAttribs.m_pcTitle = Single.m_pcTitle;
	A3DMiscAttributeCreate(&sAttribs, &pAttr[1]);

	Single.m_pcTitle = (char*) "Company";
	Single.m_pcData = (char*) "Tech Soft 3D";
	sAttribs.m_pcTitle = Single.m_pcTitle;
	A3DMiscAttributeCreate(&sAttribs, &pAttr[2]);

	A3DRootBaseData sRootData;
	A3D_INITIALIZE_DATA(A3DRootBaseData, sRootData);

	sRootData.m_pcName = (char*) "Trimmed surface";
	sRootData.m_ppAttributes = pAttr;
	sRootData.m_uiSize = 3;
	A3DRootBaseSet(p, &sRootData);

	for(A3DUns32 i = 0; i < sRootData.m_uiSize; ++i)
	{
		A3DEntityDelete(sRootData.m_ppAttributes[i]);
	}
}
\endcode
*/
typedef struct
{
	A3DUns16 m_usStructSize;								/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bTitleIsInt;									/*!< A value of TRUE indicates the m_pcTitle member represents an integer. */
	A3DUTF8Char* m_pcTitle;									/*!< Title as string. */
	A3DUns32 m_uiSize;										/*!< Size of next array. */
	A3DMiscSingleAttributeData* m_pSingleAttributesData;	/*!< Pointer to a single attribute structure. */
} A3DMiscAttributeData;

/*!
\brief Populates the \ref A3DMiscAttributeData structure
\ingroup a3d_attribute
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscAttributeGet,(	const A3DMiscAttribute* pAttribute,
														A3DMiscAttributeData* pData));


/*!
\brief Creates an \ref A3DMiscAttribute from \ref A3DMiscAttributeData structure
\ingroup a3d_attribute
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMiscAttributeCreate,(	const A3DMiscAttributeData* pData, 
															A3DMiscAttribute** ppAttribute));

#endif	/*	__A3D_ATTRIBUTE__ */


#endif	/*	__A3DPRCROOTENTITIES_H__ */
