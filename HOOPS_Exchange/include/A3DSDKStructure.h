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
\brief      Header file for the structure module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCSTRUCTURE_H__
#define __A3DPRCSTRUCTURE_H__

#ifndef __A3DPRCGRAPHICS_H__
#error A3DSDKGraphics.h must be included before current file
#endif

#ifndef __A3DPRCMISC_H__
#include "A3DSDKMisc.h"
#endif



/*!
\defgroup a3d_structure_module Structure Module
\ingroup a3d_entitiesdata_module
\brief Creates and accesses structural PRC entities 

This module describes the functions and structures that allow you to create and parse PRC structure entities. 
PRC structure entities have names of the form <code>A3DAsm<i>Entity_name</i></code>, for example \ref A3DAsmProductOccurrence.

The PRC structure entities can be adapted to support a variety of 3D modelling formats, including specific CAD formats, neutral 3D formats such as IGS, and tessellation formats such as VRML. 
\sa \REF_PRC_SPEC
*/

#ifndef __A3D_ASM_MODELFILE__
/*!
\defgroup a3d_modelfile Model File
\ingroup a3d_structure_module
\brief Reads and writes a physical file containing a PRC model file; and creates and accesses model file entities

The \ref A3DAsmModelFile is the root entity of the PRC data. It is the starting point for parsing a PRC file. 
It is also one of the arguments used to create a 3D annotation within a PDF document. 

Entity type is \ref kA3DTypeAsmModelFile.
\sa \REF_TECH_OVERVIEW
*/

/*!
\brief Modeller type
\ingroup a3d_modelfile
\version 2.1
*/
typedef enum
{
    kA3DModellerUnknown = 0,
    kA3DModellerCatia = 2,
    kA3DModellerCatiaV5 = 3,
    kA3DModellerCadds = 4,
    kA3DModellerUnigraphics = 5,
    kA3DModellerParasolid = 6,
    kA3DModellerEuclid = 7,
    kA3DModellerIges = 9,
    kA3DModellerUnisurf = 10,
    kA3DModellerVda = 11,
    kA3DModellerStl = 12,
    kA3DModellerWrl = 13,
    kA3DModellerDxf = 14,
    kA3DModellerAcis = 15,
    kA3DModellerProE = 16,
    kA3DModellerStep = 18,
    kA3DModellerIdeas = 19,
    kA3DModellerJt = 20,
    kA3DModellerSlw = 22,
    kA3DModellerCgr = 23,
    kA3DModellerPrc = 24,
    kA3DModellerXvl = 25,
    kA3DModellerHpgl = 26,
    kA3DModellerTopSolid = 27,
    kA3DModellerOneSpaceDesigner = 28,
    kA3DModeller3dxml = 29,
    kA3DModellerInventor = 30,
    kA3DModellerPostScript = 31,
    kA3DModellerPDF = 32,
    kA3DModellerU3D = 33,
    kA3DModellerIFC = 34,
    kA3DModellerDWG = 35,
    kA3DModellerDWF = 36,
    kA3DModellerSE = 37,
    kA3DModellerOBJ = 38,
    kA3DModellerKMZ = 39,
    kA3DModellerDAE = 40,
    kA3DModeller3DS = 41,
    kA3DModellerRhino = 43,
	kA3DModellerXML = 44,
    kA3DModellerLast = 45
} A3DEModellerType;


/*!
\brief ModelFile structure

\COMPONENT_A3D_API version 2.1 adds support for the \ref m_bUnitFromCAD field. 
In earlier versions of the SDK, this field was described as \e Reserved.

\ingroup a3d_modelfile

\version 2.0

\warning \ref m_dUnit in multiple of millimeters. You must provide a value for this member to create a model file.

*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DEModellerType m_eModellerType;			/*!< The Modeller used to create the Model. Used only in Get method. */
	A3DBool	m_bUnitFromCAD;						/*!< Indicates whether the following unit is read from the native CAD file. */
	A3DDouble m_dUnit;							/*!< Unit. */
	A3DUns32 m_uiPOccurrencesSize;				/*!< Number of product occurrences in next array. */
	A3DAsmProductOccurrence** m_ppPOccurrences;	/*!< Array of \ref A3DAsmProductOccurrence. */
} A3DAsmModelFileData;

/*!
\brief Populates the \ref A3DAsmModelFileData structure
\ingroup a3d_modelfile

\version 2.0

\param pModelFile A reference to the model file, which is created by invoking \ref A3DAsmModelFileLoadFromFile
\param pData A reference to the A3DAsmModelFileData structure in which the \COMPONENT_A3D_LIBRARY stores the model file data

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n

\par Sample code
\include ModelFile.cpp
*/
A3D_API (A3DStatus, A3DAsmModelFileGet,(
											  const A3DAsmModelFile* pModelFile,
											  A3DAsmModelFileData* pData));

/*!
\brief Creates an \ref A3DAsmModelFile from \ref A3DAsmModelFileData structure
\ingroup a3d_modelfile
\version 2.0
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_MODELFILE_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DAsmModelFileCreate,(
												  const A3DAsmModelFileData* pData,
												  A3DAsmModelFile** ppModelFile));

/*!
\brief Deletes the entire \ref A3DAsmModelFile entity from memory
\ingroup a3d_modelfile
\par

Every entity under this model file is also deleted. This function is responsible for
freeing the whole memory reserved for ModelFile. After this call, access to 
the model file is no longer possible, and pointer must be set to NULL. 

\version 2.0

\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DAsmModelFileDelete,(
												  A3DAsmModelFile* pModelFile));


/*!
\brief Removes all tessellation and geometry of an \ref A3DAsmProductOccurrence entity
This can only be done on parts
\ingroup a3d_modelfile
\version 9.1

\param pModelFile The model file
\param uiPartsSize Size of next array.
\param ppParts Array of parts to unload.

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_PART_EXTERNAL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API(A3DStatus, A3DAsmModelFileUnloadParts, (
	A3DAsmModelFile* pModelFile,
	A3DUns32 uiPartsSize,
	A3DAsmProductOccurrence** ppParts));


#endif	/*	__A3D_ASM_MODELFILE__ */

#ifndef __A3D_ASM_POCCURRENCE__
/*!
\defgroup a3d_productoccurrence Product Occurrence
\ingroup a3d_structure_module
\brief Creates and accesses product occurrence PRC entities

A product occurrence denotes an assembly tree. If the assembly tree contains a single part, the product occurrence
points directly to a part definition. In the case of a more complex assembly tree, 
a product occurrence is a hierarchy of child product occurrences. 
And a product occurrence can reference product occurrences that are designated as ProductPrototypes or
ExternalData. Such ProductOccurrences denote subassembly structures, which in turn can point to PartDefinitions.


Entity type is \ref kA3DTypeAsmProductOccurrence. 

*/

/*!
\brief Load status of the PRC model file
\ingroup a3d_productoccurrence
\version 2.1
*/
typedef enum
{
	kA3DProductLoadStatusUnknown = 0,	/*!< Unknown status. */ 
	kA3DProductLoadStatusError,			/*!< Loading error. For example, there is a missing file. */
	kA3DProductLoadStatusNotLoaded,		/*!< Not loaded. */
	kA3DProductLoadStatusNotLoadable,	/*!< Not loadable. For example, limitations exist that prevent the product from loading. */
	kA3DProductLoadStatusLoaded			/*!< The product was successfully loaded. */
} A3DEProductLoadStatus;

/*!
\defgroup a3d_product_flag Bit field flag definitions for product occurrences
@ingroup a3d_productoccurrence
@{

These flags represent characteristics of product occurrences.

A product occurrence can be:<BR>
\li A container. In this case, it acts as a repository of son occurrences that do not necessarily have 
	relationships between them. This is useful for situations where a single CAD file can correspond to a whole database of parts and assemblies.
\li A configuration. This is a specific arrangement of a product with respect to its whole hierarchy.<BR>
\li A view. A view refers to another product occurrence (its prototype) to denote a particular setting 
	of visibilities and position within the same hierarchy.<BR>
\li Suppressed. /version 9.0<BR>

If none of these flags is specified, a product occurrence is regular. If the product occurrence has no 
father, it is similar to a configuration. 

\attention <b>A product occurrence with no father cannot have a product prototype or external data property.</b>

For containers, configurations, and views, a product occurrence can be the default, which means that it 
is loaded by default in the originating CAD system.

\version 2.1

*/
#define A3D_PRODUCT_FLAG_DEFAULT		0x0001	/*!< The product occurrence is the default container, configuration, or view. */
#define A3D_PRODUCT_FLAG_INTERNAL		0x0002	/*!< The product occurrence is internal. This flag is used only when the product occurrence has no father. */
#define A3D_PRODUCT_FLAG_CONTAINER		0x0004	/*!< The product occurrence is a container. */
#define A3D_PRODUCT_FLAG_CONFIG			0x0008	/*!< The product occurrence is a configuration. */
#define A3D_PRODUCT_FLAG_VIEW			0x0010	/*!< The product occurrence is a view. */
#define A3D_PRODUCT_FLAG_SUPPRESSED		0x0040	/*!< The product occurrence is suppressed. /version 9.0 */
#define A3D_PRODUCT_FLAG_CONFIG_NOT_UPDATED	0x0100	/*!< The config does not include the model data or the model data is not up to date. */

/*!
@}
*/

/*!
\brief A structure to store material, visibility, suppressed, etc... informations, to put on other product occurence.
Used for Assemblies / Views that modify those informations.
It will be applied during shattered post-treatment.
\ingroup a3d_productoccurrence
*/
typedef struct
{
	A3DUns32 m_uiPathInAssemblyTreeSize;				/*!< Size of next array. */
	A3DUTF8Char** m_ppPathInAssemblyTree; 				/*!< path in the assembly tree of Product Occurence to modify */
	A3DGraphMaterialData* m_pMaterial;
	A3DMiscCartesianTransformationData* m_pTransform;	/*!< Pointer to an \ref A3DMiscCartesianTransformation entity. May be NULL. */
	A3DBool m_bIsSuppressed;							/*!< Is it suppressed? */
	A3DUns16 m_usLayer;									/*!< Layer. */
	A3DUns16 m_usBehaviour;								/*!< Behavior. */
	A3DUns8  m_ucType;									/*!< Type. /version 9.0 */

} A3DMaterialAndVisualisationInfos;

/*!
\brief A structure to store a list of MaterialAndVisualisationInfos, applied by a view.
Used for a View that modify those informations.
It will be applied during shattered post-treatment.
\ingroup a3d_productoccurrence
*/
typedef struct
{
	A3DUns32 m_uiViewIndex;													/*!< index of the View in the ProductOccurence view list. */

	A3DUns32 m_uiMaterialAndVisualisationSetupSize;							/*!< Size of next array. */
	A3DMaterialAndVisualisationInfos* m_psMaterialAndVisualisationSetup;	/*!< MaterialAndVisualisation Informations to apply in the assembly tree, modify by the view */

} A3DViewMaterialAndVisualisationInfos;

/*!
\brief A structure specifying product occurrence data
\ingroup a3d_productoccurrence
\par

Global concepts definitions:

\li ModelFile: this is the top level of the assembly tree
\li ProductOccurrences: these are the intermediate nodes of the assembly tree. Each
ProductOccurrence can hold a PartDefinition (see below), several ProductOccurrences as 
sons, a Prototype (see below) or an ExternalData (see below). Each one can carry its 
own unit.
\li Prototype: special case for a ProductOccurrence. A Prototype is a sub-assembly that 
might be modified outside the Modelfile. For instance, a CATProduct or a CATPart being 
referenced by a Catia V5 assembly will be loaded as a Prototype, for the related physical
file might change during design process. The whole internal hierarchy of this "file" can
be explored from the Modelfile, as it was a classical ProductOccurrence, but any modification
inside this sub-assembly will lead to an update of the whole Modelfile, in order to reference
proper entities. 
\li ExternalData: special case for a ProductOccurrence. an ExternalData is a sub-assembly that
cannot be "managed" from the Modelfile. The corresponding Partdefinitions cannot be modified
(color, visibility, position, etc.). For instance, this can be a IGES file being embedded in a 
CATproduct.
\li PartDefinition: this is the terminal level of an assembly. No "organized" hierachy can be
defined below that level. Only groups (refer to \ref A3DRiSet definition) might be referenced
as unorganized groups. A Partdefinition must be referenced in a Modelfile via a ProductOccurrence.
Conversely, any terminal ProductOccurrence of a fully loaded Modelfile must refereence a
PartDefinition.

A product occurrence can have the following data:
\li PartDefinition: Pointer to the corresponding part definition. Can be NULL. See above.\n
\li ProductPrototype: Pointer to the corresponding product occurrence prototype. Can be NULL. See above. \n
\li ExternalData: Pointer to the corresponding external product occurrence. Can be NULL. See above. \n
\li Sons: Array of pointers to the son product occurrences. See above.\n
\li Location: Relative placement of the product occurrence in the father local coordinate system. Can be NULL. \n

When applications interpret an assembly that uses subassemblies, they resolve links in the product 
prototype and external data entities and import the content described by those links. That is, 
those entities are resolved in the same way that software macros are resolved.

In addition to the data described in the \ref A3DAsmProductOccurrenceData structure, 
an \ref A3DAsmProductOccurrence entity can have attributes specified through the \ref A3DRootBase and 
\ref A3DMiscCascadedAttributes entities. 

For version 2.1, new fields were added to the end of this structure. These new fields are identified with the tag "version 2.1."

\version 2.0

\par Sample code

The following pseudocode demonstrates how to get the external data of a product occurrence.

\code
POccurrence* function GetExternalData(POccurrence* pocc)
{
	If pocc->pExternalData is null and pocc->pPrototype is not null
		Return GetExternalData(pocc->pPrototype)
	Else
		Return pocc->pExternalData
}
\endcode

The following pseudocode demonstrates how to get the part definition of a product occurrence.

\code
POccurrence* GetPart(POccurrence* pocc)
{
	If pocc->pPart is not null
		Return pocc->pPart

	POccurrence* po = pocc->pPrototype
	While po is not null
		If po->pPart is not null
			Return po->pPart
		Else
			po = po->pPrototype

	If pocc->uiPOccurrencesSize = 0 and GetExternalData(pocc) is not null
		Return GetExternalData(pocc)->pPart

	Return null
}
\endcode

The following pseudocode demonstrates how to get the location of a product occurrence.

\code
CartesianTransfo* GetLocation(POccurrence* pocc)
{
	If GetExternalData(pocc) is not null
		If GetExternalData(pocc)->pLocation is not null
			Return GetExternalData(pocc)->pLocation
	If pocc->pLocation is null and pocc->pPrototype is not null
		Return GetLocation(pocc->pPrototype)
	Return pocc->pLocation
}
\endcode

\note In case of multi-units assemblies, the unit must be applied to the matrix 
of the transformations. 
*/
typedef struct
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiPOccurrencesSize;						/*!< Number of product occurrences in next array. */
	A3DAsmProductOccurrence** m_ppPOccurrences;			/*!< Array of \ref A3DAsmProductOccurrence references. */
	A3DAsmPartDefinition* m_pPart;						/*!< Pointer to an \ref A3DAsmPartDefinition entity. May be NULL. */
	A3DAsmProductOccurrence* m_pPrototype;				/*!< Pointer to a product prototype. May be NULL. */
	A3DAsmProductOccurrence* m_pExternalData;			/*!< Pointer to a external data product. May be NULL. */
	A3DUns8 m_ucBehaviour;								/*!< For a future use */
	A3DMiscTransformation* m_pLocation;					/*!<
															Pointer to an \ref A3DMiscCartesianTransformation 
															or \ref A3DMiscGeneralTransformation entity. May be NULL. */
	A3DUns32 m_uiEntityReferenceSize;					/*!< Size of next array. */
	A3DMiscEntityReference** m_ppEntityReferences;		/*!< Entity references. */
	A3DUns32 m_uiAnnotationsSize;						/*!< Size of next array. */
	A3DMkpAnnotationEntity** m_ppAnnotations;			/*!< Annotation entities stored under the current product occurrence. */
	A3DUns32 m_uiViewsSize;								/*!< Size of next array. */
	A3DMkpView** m_ppViews;								/*!< Views stored under the current product occurrence. */
	A3DAsmFilter* m_pEntityFilter;						/*!< Array of \c A3DAsmFilter references on entities that are kept by the occurrence. */
	A3DUns32 m_uiDisplayFilterSize;						/*!< Size of next array. */
	A3DAsmFilter** m_ppDisplayFilters;					/*!<
															Array of Filter references that specify the filters 
															to use for display. Several filters can be specified but only one is active. */
	A3DUns32 m_uiSceneDisplayParameterSize;				/*!< Size of next array. */
	A3DGraphSceneDisplayParametersData* m_psSceneDisplayParameters;		/*!< Array of SceneDisplayParameters. Reserved for future use. */
	A3DEProductLoadStatus m_eProductLoadStatus;			/*!<
															Current load status for the ProductOccurrence, 
															where values are defined by the \ref A3DEProductLoadStatus enum. \version 2.1 */
	A3DUns32 m_uiProductFlags;							/*!< Refer to \ref a3d_product_flag for explanations \version 2.1 */
	A3DBool m_bUnitFromCAD;								/*!< Indicates whether \ref m_dUnit (below) was obtained from the native CAD file. \version 2.1 */
	A3DDouble m_dUnit;									/*!< Unit. \version 2.1 */
	A3DDouble m_dDensityVolumeUnit;						/*!< Volume unit used for the physical material density. 1.0 refers to meter cube*/
	A3DDouble m_dDensityMassUnit;						/*!< Mass unit used for the physical material density. 1.0 refers to kilogram*/
	A3DEModellerType m_eModellerType;					/*!< The Modeller used to create the Model. Used only in Get method. */
	A3DBool		m_bInactivateAnnotations;				/*!< If set to true, annotations are defined but inactivated in the product. \version 7.0 */


	A3DUns32 m_uiMaterialAndVisualisationSetupSize;							/*!< Size of next array. */
	A3DMaterialAndVisualisationInfos* m_psMaterialAndVisualisationSetup;	/*!< MaterialAndVisualisation Informations to apply in the assembly tree, modify by assembly. */


} A3DAsmProductOccurrenceData;


/*!
\brief Populates the \ref A3DAsmProductOccurrenceData structure
\ingroup a3d_productoccurrence
\version 2.0

\par Sample code
\include ProductOccurrence.cpp
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DAsmProductOccurrenceGet,(
	const A3DAsmProductOccurrence* pProductOccurrence,
	A3DAsmProductOccurrenceData* pData));

/*!
\brief Creates an \ref A3DAsmProductOccurrence from \ref A3DAsmProductOccurrenceData structure
\ingroup a3d_productoccurrence
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_PART_EXTERNAL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmProductOccurrenceCreate,(
	const A3DAsmProductOccurrenceData* pData,
	A3DAsmProductOccurrence** ppProductOccurrence));

/*!
\brief Sets up an \ref A3DAsmProductOccurrence entity as a prototype 
to another \ref A3DAsmProductOccurrence entity
\ingroup a3d_productoccurrence
\version 2.0

This function sets an \ref A3DAsmProductOccurrence entity as a prototype to another \ref A3DAsmProductOccurrence entity,
and duplicates the \ref A3DAsmProductOccurrenceData structure. 

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_PART_EXTERNAL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmProductOccurrenceSetProductPrototype,(
			A3DAsmProductOccurrence* pProductOccurrence,
			A3DAsmProductOccurrence* pProductPrototype));

/*!
\brief Removes all tessellation and geometry of an \ref A3DAsmProductOccurrence entity
\ingroup a3d_productoccurrence
\warning DEPRECATED: use \ref A3DAsmModelFileUnloadParts
\version 3.1

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_PART_EXTERNAL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmProductOccurrenceUnload,(
			A3DAsmProductOccurrence* pProductOccurrence));

/*!
\brief Returns the full path name of the file associated with the product occurrence. Warning: Using this function on a product occurrence holding a prototype is not recommended, as the result is influenced by how the data is originally stored in the CAD file.
\ingroup a3d_productoccurrence
\version 4.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_PART_EXTERNAL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmProductOccurrenceGetFilePathName,(
			const A3DAsmProductOccurrence* pProductOccurrence, A3DUTF8Char **ppcFileName));

/*!
\brief Returns the original file name stored in the CAD file. Warning: Using this function on a product occurrence holding a prototype is not recommended, as the result is influenced by how the data is originally stored in the CAD file.
\ingroup a3d_productoccurrence
\version 8.2

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_PART_EXTERNAL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmProductOccurrenceGetOriginalFilePathName,(
			const A3DAsmProductOccurrence* pProductOccurrence, A3DUTF8Char **ppcFileName));

/*!
\brief Adds a view in the Array of views
\ingroup a3d_productoccurrence
\version 4.1

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_PART_EXTERNAL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmProductOccurrenceAddView,( A3DAsmProductOccurrence* pProductOccurrence,
															A3DMkpView* pView));

/*!
\brief Allows to modify some data of a product occurrence
\ingroup a3d_productoccurrence
\version 5.1

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmProductOccurrenceEdit,(
			const A3DAsmProductOccurrenceData* pData, A3DAsmProductOccurrence* pProductOccurrence));

#endif	/*	__A3D_ASM_POCCURRENCE__ */
#ifndef __A3D_ASM_PINFORMATION__

/*!
\brief Product Occurence Type in Solidworks
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef enum
{
	A3DEProductOccurenceTypeSLW_ContainerTess = -2,
	A3DEProductOccurenceTypeSLW_Container = -1,
	A3DEProductOccurenceTypeSLW_Part = 0,
	A3DEProductOccurenceTypeSLW_Assembly,
	A3DEProductOccurenceTypeSLW_Drawing,
	A3DEProductOccurenceTypeSLW_Unknown,
	A3DEProductOccurenceTypeSLW_PartTesselated,
	A3DEProductOccurenceTypeSLW_AssemblyTesselated,
	A3DEProductOccurenceTypeSLW_StandalonePart

} A3DEProductOccurenceTypeSLW;


/*!
\brief A structure specifying assembly attachments infos specific to Solidworks format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DInt32 m_iRiIndex;
	A3DInt32 m_iConfigID;
	A3DUTF8Char *m_psReplacedFilePath;

	A3DUns32 m_uiPathsInAssemblyTreeSize;		/*!< Size of next array. */
	A3DUTF8Char **m_ppsPathsInAssemblyTree;		/*!< Array of Paths In Assembly Tree. */

} A3DAsmAttachmentsInfosSLW;

/*!
\brief A structure specifying product occurrence data specific to Solidworks format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;									/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char *m_psNodeSlwID;									/*!< ID comming from Solidworks, to use to resolve the "PathsInAssemblyTree" */
	
	A3DInt32 m_iIndexCfg;										/*!< Cfg Index */
	A3DUTF8Char *m_psCfgName;									/*!< Cfg Name in the file*/	

	A3DEProductOccurenceTypeSLW m_usType;						/*!< Product Occurrence Type */

	A3DUns32 m_uiAttachementsSize;								/*!< Size of next array. */
	A3DAsmAttachmentsInfosSLW *m_psAttachements;				/*!< Storage to put assembly attachments information on product occurrence in assembly tree. */
} A3DAsmProductOccurrenceDataSLW;


/*!
\brief Populates the \ref A3DAsmProductOccurrenceDataSLW structure
\ingroup a3d_productoccurrence
\version 8.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DAsmProductOccurrenceGetSLW, (
	const A3DAsmProductOccurrence* pProductOccurrence,
	A3DAsmProductOccurrenceDataSLW* pData));



typedef enum
{
	A3DEProductOccurenceTypeCat_unknown = -1,
	A3DEProductOccurenceTypeCat_model = 0,
	A3DEProductOccurenceTypeCat_sessionModel,
	A3DEProductOccurenceTypeCat_session,
	A3DEProductOccurenceTypeCat_export

} A3DEProductOccurenceTypeCat;

/*!
\brief A structure specifying product occurrence data specific to Catia format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */

	A3DEProductOccurenceTypeCat m_eCatiaFileType;
	A3DInt32 m_iModelNumber;
	A3DUns32 m_uiIdWorkspace;
	A3DInt32 m_iTypeWorkspace;

	A3DUTF8Char *m_psModelName;
	A3DUTF8Char *m_psUser;
	A3DUTF8Char *m_psDatm;
	A3DUTF8Char *m_psTimem;
	A3DUTF8Char *m_psVersion;
	A3DUTF8Char *m_psRelease;

} A3DAsmProductOccurrenceDataCat;


/*!
\brief Populates the \ref A3DAsmProductOccurrenceDataCat structure
\ingroup a3d_productoccurrence
\version 8.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DAsmProductOccurrenceGetCat, (
	const A3DAsmProductOccurrence* pProductOccurrence,
	A3DAsmProductOccurrenceDataCat* pData));

/*!
\brief A structure specifying product occurrence data specific to CV5 format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */

	A3DUTF8Char *m_psRootFilePath;					/*!< unique ID : to be sure incremental loading is ok, we need the same root
													assembly file with same timestamp. Otherwise : must reload all. */
	A3DInt32 m_iRootModificationTime;
	A3DInt32 m_iRootUpdateIndex;
	A3DInt32 m_iCurrentAsmProductIdentifier;
	A3DInt32 m_iNotUpdatedAsmProductIdentifier;

	A3DInt32 m_aiCLSID[4];

	A3DBool m_bProductInError;
	A3DBool m_bHasCGMInformation;
	A3DBool m_bFromCATPart;
	A3DUTF8Char *m_psVersion;
	A3DUTF8Char *m_psPartNumber;

} A3DAsmProductOccurrenceDataCV5;


/*!
\brief Populates the \ref A3DAsmProductOccurrenceDataCV5 structure
\ingroup a3d_productoccurrence
\version 8.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DAsmProductOccurrenceGetCV5, (
	const A3DAsmProductOccurrence* pProductOccurrence,
	A3DAsmProductOccurrenceDataCV5* pData));



/*!
\brief A structure specifying Promoted Bodies Ids for Ug Format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DUns32 m_uiBaseTagOcc;	    /*!< Base Tag Occurrence  /version 9.0 */
	A3DUns32 m_uiBaseTag;			/*!< Base Tag */
	A3DUns32 m_uiPromotedBodyID;	/*!< Id of the Promoted body. */

} A3DPromotedBodyUg;


/*!
\brief A structure specifying a List of Elements Ids associated to a refset, for Ug Format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DUTF8Char *m_psRefset;	/*!< the Refset. */
	A3DUns32 m_uiElementsSize;	/*!< Size of next array. */
	A3DUns32 *m_auiElements;	/*!< array of Element IDs. */

} A3DElementsByRefsetUg;

/*!
\brief A structure specifying product occurrence data specific to Ug format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */

	
	A3DUTF8Char *m_psRootFilePath;		/*!< unique ID : to be sure incremental loading is ok, we need the same root
											assembly file with same timestamp. Otherwise : must reload all. */
	
	A3DUTF8Char *m_psFileName;			/*!< for UG, the actual path is deduced from this value (which is in the file)
											and then a wise combination of research paths. */
	A3DUTF8Char *m_psInstanceFileName;
	A3DUTF8Char *m_psRefSet;
	A3DUTF8Char *m_psPartUID;

	A3DUns32 m_uiInstanceTag;

	A3DUns32 m_uiPromotedBodiesSize;				/*!< Size of next array. */
	A3DPromotedBodyUg* m_asPromotedBodies;
	A3DUns32 m_uiChildrenByRefsetsSize;				/*!< Size of next array. */
	A3DElementsByRefsetUg* m_asChildrenByRefsets;
	A3DUns32 m_uiSolidsByRefsetsSize;				/*!< Size of next array. */
	A3DElementsByRefsetUg* m_asSolidsByRefsets;

} A3DAsmProductOccurrenceDataUg;


/*!
\brief Populates the \ref A3DAsmProductOccurrenceDataUg structure
\ingroup a3d_productoccurrence
\version 8.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DAsmProductOccurrenceGetUg, (
	const A3DAsmProductOccurrence* pProductOccurrence,
	A3DAsmProductOccurrenceDataUg* pData));


/*!
\brief A structure specifying product occurrence data specific to CV5 format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */

	A3DDouble m_dAccuracy;

	A3DUTF8Char *m_sPartName;

	A3DInt32 m_iProEMemberType;
	A3DInt32 m_iProEMemberId;
	A3DBool m_bXprOrXas;

	A3DBool m_bHasFamilyTable;
	A3DBool m_bHasBooleanOperation;
	A3DBool m_bHasFlexibleComponent;

	A3DMiscCartesianTransformationData* m_pDefaultExplodePosition; /*!< Default position defined in the default explode for the owner product in his fathers explode state. */

	
	A3DUns32 m_uiExplodedProductsSize;				/*!< Size of next array. */
	A3DAsmProductOccurrence** m_ppExplodedProducts;	/*!< Definition of the redefine position of sub element (target)
													for the Explode state of the product owner level the explosion
													is define by a path to access to the target and an array of transfomation
													to apply to each level A product of this array reprensents an instance repositioning,
													his product sons array represents the path to access to the target element, and he had
													an array of linked items to store all new position for path member. */

} A3DAsmProductOccurrenceDataProe;


/*!
\brief Populates the \ref A3DAsmProductOccurrenceDataProe structure
\ingroup a3d_productoccurrence
\version 8.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DAsmProductOccurrenceGetProe, (
	const A3DAsmProductOccurrence* pProductOccurrence,
	A3DAsmProductOccurrenceDataProe* pData));

/*!
\brief A structure specifying The type of Productoccurence, for Inventor
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef enum
{
	A3DEProductOccurenceTypeInv_none,
	A3DEProductOccurenceTypeInv_iam,
	A3DEProductOccurenceTypeInv_ipt
} A3DEProductOccurenceTypeInv;

/*!
\brief A structure specifying product occurrence data specific to Inventor format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	
	A3DEProductOccurenceTypeInv m_eType;	/*!< Product Occurrence Type (none, iam, ipt). */

	A3DInt32 m_aiCLSID[4];					/*!< Product CLSID. Only on regular products (type: iam, ipt). */
	A3DInt32 m_iNodeID;						/*!< Node ID. */

	A3DUns32 m_uiOccurenceIDsSize;			/*!< Size of next array. */
	A3DInt32* m_aiOccurenceIDs;				/*!< Ids of Products corresponding to occurrences. */
	A3DUns32 m_uiFlexibleOccurenceIDsSize;	/*!< Size of next array. */
	A3DInt32* m_aiFlexibleOccurenceIDs;		/*!< Ids of flexible occurrences */

	A3DBool m_bIsSubstituted;

} A3DAsmProductOccurrenceDataInv;


/*!
\brief Populates the \ref A3DAsmProductOccurrenceDataInv structure
\ingroup a3d_productoccurrence
\version 8.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DAsmProductOccurrenceGetInv, (
	const A3DAsmProductOccurrence* pProductOccurrence,
	A3DAsmProductOccurrenceDataInv* pData));


/*!
\brief A structure specifying product occurrence data specific to JT format
\ingroup a3d_productoccurrence
\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	
	A3DUns16 m_usValidDisplayFields;

} A3DAsmProductOccurrenceDataJT;


/*!
\brief Populates the \ref A3DAsmProductOccurrenceDataJT structure
\ingroup a3d_productoccurrence
\version 8.2

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API(A3DStatus, A3DAsmProductOccurrenceGetJT, (
	const A3DAsmProductOccurrence* pProductOccurrence,
	A3DAsmProductOccurrenceDataJT* pData));


/*!
\brief Combine Part ID and Occurrence identifier
\ingroup a3d_productoccurrence
\version 9.1

\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API(A3DStatus, A3DAsmProductOccurrenceGetIdentifier, (
	const A3DAsmProductOccurrence* pProductOccurrence, A3DUTF8Char** ppcIdentifier));

#endif	/*	__A3D_ASM_PINFORMATION__ */

#ifndef __A3D_ASM_PARTDEF__
/*!
\defgroup a3d_partdefinition Part Definition
\ingroup a3d_productoccurrence
\version 2.0

Entity type is \ref kA3DTypeAsmPartDefinition.
*/

/*!
\brief A structure that specifies the part definition data
\ingroup a3d_partdefinition
\version 2.0
*/
typedef struct
{
	A3DUns16					m_usStructSize;				/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBoundingBoxData			m_sBoundingBox;				/*!< Bounding box. */
	A3DUns32					m_uiRepItemsSize;			/*!< Size of next array. */
	A3DRiRepresentationItem**	m_ppRepItems;				/*!< Representation items stored under current Part definition. */
	A3DUns32					m_uiAnnotationsSize;		/*!< Size of next array. */
	A3DMkpAnnotationEntity**	m_ppAnnotations;			/*!< Annotation entities stored under current Part definition. */
	A3DUns32					m_uiViewsSize;				/*!< Size of next array. */
	A3DMkpView**				m_ppViews;					/*!< Views stored under current Part definition. */
	A3DUns32					m_uiDrawingModelsSize;		/*!< Size of next array. Must be set to zero. */
	A3DDrawingModel**			m_ppDrawingModels;			/*!< For future use. Must be set to zero. */
	A3DBool						m_bInactivateAnnotations;	/*!< If set to true, annotations are defined but inactivated in the product. \version 7.0 */
} A3DAsmPartDefinitionData;

/*!
\brief Populates an \ref A3DAsmPartDefinitionData structure
\ingroup a3d_partdefinition
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DAsmPartDefinitionGet,(
													 const A3DAsmPartDefinition* pPartDefinition,
													 A3DAsmPartDefinitionData* pData));


/*!
\brief Creates an \ref A3DAsmPartDefinition entity from an \ref A3DAsmPartDefinitionData structure
\ingroup a3d_partdefinition
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PARTDEFINITION_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmPartDefinitionCreate,(
	const A3DAsmPartDefinitionData* pData,
	A3DAsmPartDefinition** ppPartDefinition));


/*!
\brief Get the list of reference files present on drawing
\ingroup a3d_partdefinition
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DDrawingGetReferencesList,(	const A3DAsmPartDefinition* pPartDefinition,
																	A3DUns32* puiNumberOfFilePaths,
																	A3DUTF8Char*** pppcSrcFilePaths));


/*!
\brief Adds a view in the Array of views
\ingroup a3d_partdefinition
\version 4.1

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_PART_EXTERNAL \n
\return \ref A3D_PRODUCTOCCURRENCE_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmPartDefinitionAddView,( A3DAsmPartDefinition* pPartDefinition,
		 A3DMkpView* pView));

/*!
\brief Allows to modify some data of a part definition
\ingroup a3d_partdefinition
\version 5.1

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS.\n
*/

A3D_API (A3DStatus, A3DAsmPartDefinitionEdit,(
			const A3DAsmPartDefinitionData* pData,
			A3DAsmPartDefinition* pPartDefinition));


#endif	/*	__A3D_ASM_PARTDEF__ */

#ifndef __A3D_ASM_FILTER__
/*!
\defgroup a3d_filter Filter Module
\ingroup a3d_productoccurrence
\brief Creates and accesses filter entities that control the entities and layers included in the 3D image

Entity type is \ref kA3DTypeAsmFilter.

The filter entity lets you include or exclude product occurrences or representation items based on their layer or entity type. 
Such inclusive or exclusive filtering applies to the primary entity and its descendants. 
For example, you can exclude all wireframe entities.

You can filter entities from these perspectives:
<ul>
	<li>Layer, inclusively. Only the entities belonging to a certain layer are included in the 3D view. 
		Entities in other layers are removed. </li>
	<li>Layer, exclusively. Only the entities not belonging to a certain layer are included in the 3D view. 
		Entities in other layers are removed. </li>
	<li>Entity, inclusively. Only entities of certain types are included in the 3D view. 
		Entities of other types are removed. </li>
	<li>Entity, exclusively. Only entities not of certain types are included in the 3D view. 
		Entities of other types are removed.</li>
</ul>

If the \ref A3DAsmLayerFilterItemData::m_bIsInclusive member is \c TRUE, the layer filter is inclusive; otherwise, it is exclusive. 
Similarly for an entity filter,
if the \ref A3DAsmEntityFilterItemData::m_bIsInclusive member is \c TRUE, the entity filter is inclusive; otherwise, it is exclusive. 
If a layer or entity satisfies an inclusive filter criterion, then it and all of its child entities are included in the 3D view.
If a layer or entity satisfies an exclusive filter criterion, then it and all its child entities are excluded from the 3D view.

For example, if one of the entries in the \ref A3DAsmLayerFilterItemData::m_puiLayerIndexes member 
specifies a layer index of "3" 
and if the \ref A3DAsmLayerFilterItemData::m_bIsInclusive member is \c FALSE, 
then entities with miscellaneous cascaded attributes member \c m_usLayer set to 3 are excluded from the 3D view.

Multiple filters can be specified within a particular \ref a3d_productoccurrence entity. 
The filters specified within one product are propagated to descendent product occurrences.

*/

/*!
\brief A structure that specifies the layers to consider in a layer filter
\ingroup a3d_filter
\version 2.0

This structure is used for layer-filtering where one of the following situations occur, 
depending on the setting of the \ref m_bIsInclusive member:
<ul>
	<li>Only the entities belonging to a certain layer are present. 
		Entities in other layers are removed. </li>
	<li>Only entities not belonging to a certain layer are present. 
		Entities in other layers are retained. </li>
</ul>
*/

typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bIsInclusive;							/*!<
														A value of \c TRUE indicates the entities in the specified layer are retained. 
														A value of \c FALSE indicates the entities in the specified layer are removed. */
	A3DUns32 m_uiSize;								/*!< Size of the next array. */
	A3DUns32* m_puiLayerIndexes;					/*!< Layers considered by the filter. The index references a layer in the global data. */
} A3DAsmLayerFilterItemData;

/*!
\brief A structure that specifies the entities to consider in an entity filter
\ingroup a3d_filter
\version 2.0

The \ref A3DAsmEntityFilterItemData structure is similar to the \ref A3DAsmLayerFilterItemData 
except that filtering is done by entity.
*/

typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bIsInclusive;							/*!<
														A value of \c TRUE indicates the specified entity types are retained. 
														A value of \c FALSE indicates the specified entity types are removed. */
	A3DUns32 m_uiSize;								/*!< Size of next array. */
	A3DMiscEntityReference** m_ppEntities;			/*!< Entities referenced in the current filter. */
} A3DAsmEntityFilterItemData;

/*!
\brief A structure that specifies entity and layer-filtering characteristics
\ingroup a3d_filter
\version 2.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bIsActive;							/*!< If \c TRUE, this filter corresponds to the active layout when loading the file. */
	A3DAsmLayerFilterItemData m_sLayerFilterItem;	/*!< For filtering by layer. */
	A3DAsmEntityFilterItemData m_sEntityFilterItem;	/*!< For filtering by entity item. */
} A3DAsmFilterData;

/*!
\brief Populates the \ref A3DAsmFilterData structure with data from an \ref A3DAsmFilter entity
\ingroup a3d_filter
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DAsmFilterGet,(
										  const A3DAsmFilter* pFilter,
										  A3DAsmFilterData* pData));


/*!
\brief Creates an \ref A3DAsmFilter entity from an \ref A3DAsmFilterData structure
\ingroup a3d_filter
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_PARTDEFINITION_INCONSISTENT_EMPTY \n
\return \ref A3D_SUCCESS.\n
*/
A3D_API (A3DStatus, A3DAsmFilterCreate,(
											  const A3DAsmFilterData* pData,
											  A3DAsmFilter** ppFilter));

#endif	/*	__A3D_ASM_FILTER__ */



#ifndef __A3D_FILE_CONTEXT__
/*!
\defgroup a3d_file_context File Context
\ingroup a3d_structure_module
\brief Creates and accesses file contexts
*/

/*!
\brief A structure that specifies the file contexts
\ingroup a3d_structure_module
\version 8.1
*/

typedef struct
{
	A3DUns16		m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char*	m_pcFileName;						/*!< Name of the concerned file. */
	A3DUns32		m_uiNbContexts;						/*!< Number of contexts for this file. */
	A3DUTF8Char**	m_apcContexts;						/*!< Contexts for this file. */
} A3DFileContextData;

/*!
\brief Populates the \ref A3DFileContextData structure with data from an \ref A3DAsmProductOccurrence entity
\ingroup a3d_structure_module
\version 8.1

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DFileContextDelete,(A3DFileContextData* pData));


#endif	/*	__A3D_FILE_CONTEXT__ */

#endif	/*	__A3DPRCSTRUCTURE_H__ */
