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
\brief      Header file for the read-write module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCREADWRITE_H__
#define __A3DPRCREADWRITE_H__

#ifndef __A3DPRCSTRUCTURE_H__
#error A3DSDKStructure.h must be included before current file
#endif

/*!
\defgroup a3d_readwrite_module Read-Write Module
\ingroup a3d_entitiesdata_module
\brief Methods and structures dedicated to reading and writing capabilities

This module describes the functions and structures that allow you to read and write 3D model files. 
*/

#ifndef __A3D_RW_READ__
/*!
\defgroup a3d_read Read functions
\ingroup a3d_readwrite_module
\brief Loads the model file with information from the input CAD file.

Please refer to \REF_SUPPORTED_FORMATS documentation for list of available formats. 
*/

#ifndef WIN32
	#include <stdlib.h>
#endif

/*!
\ingroup a3d_read
\brief ReadingMode of the model file. Set which kind of content should be read.
\version 3.0
*/
typedef enum
{
	kA3DReadGeomOnly = 0,	/*!< Read only geometry. */
	kA3DReadGeomAndTess,	/*!< Mixed mode: read geometry and tessellation. */
	kA3DReadTessOnly		/*!< Read only tessellation. */
} A3DEReadGeomTessMode;

/*!
\ingroup a3d_write
\brief WritingMode of the model file. Set which kind of content should be written.
\version 6.0
*/
typedef enum
{
	kA3DWriteGeomOnly = 0,	/*!< Write only geometry. */
	kA3DWriteGeomAndTess,	/*!< Mixed mode: write geometry and tessellation. */
	kA3DWriteTessOnly		/*!< Write only tessellation. */
} A3DEWriteGeomTessMode;

/*!
\ingroup a3d_read
\brief Unit used in the model file.
\version 3.0
*/
typedef enum
{
	kA3DUnitPoint = 0,		/*!< Point. */
	kA3DUnitInch,			/*!< Inch. */
	kA3DUnitMillimeter,		/*!< Millimeter. */
	kA3DUnitCentimeter,		/*!< Centimeter. */
	kA3DUnitPicas,			/*!< Picas. */
	kA3DUnitFoot,			/*!< Foot. */
	kA3DUnitYard,			/*!< Yard. */
	kA3DUnitMeter,			/*!< Meter. */
	kA3DUnitKilometer,		/*!< Kilometer. */
	kA3DUnitMile,			/*!< Mile. */
	kA3DUnitUnknown			/*!< Unknown. */
} A3DEUnits;

/*!
\ingroup a3d_read
\brief Reading options to filter the types of information that are read when CAD files are loaded.

These options are common to a lot of CAD formats, but not all options are valid with all CAD formats.
Filtering options (reading of wireframe, surfaces, solid entities, PMI...) behave like this:
if the value is \c FALSE, the corresponding entities are ignored during reading.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bReadSolids;			/*!< Filtering option to read solid parts. */
	A3DBool m_bReadSurfaces;		/*!< Filtering option to read surfaces of parts as entities. */
	A3DBool m_bReadWireframes;		/*!< Filtering option to read all wireframe entities in the CAD file. */
	A3DBool m_bReadPmis;			/*!< Filtering option to read PMI markups and notes. */
	A3DBool m_bReadAttributes;		/*!<
										Filtering option to read non-geometric information linked to entities and files.
										Note: Attributes linked to solids and entities, such as Material and Density, 
											are always read, even if m_bReadAttributes is \c FALSE. */
	A3DBool m_bReadHiddenObjects;	/*!< Filtering option to read any objects that are present but currently hidden in the CAD file. */
	A3DBool m_bReadConstructionAndReferences;	/*!< Filtering option to read construction entities, such as planes and axes. */
	A3DBool m_bReadActiveFilter;	/*!< Filtering option to read only data stored in the active filter or on layers corresponding to the active filter. */
	A3DBool m_bReadDrawings;		/*!<
										Sets whether data is read to create a 3D model or a 2D drawing. Valid only with IGES files.
										\li IGES: a value of \c TRUE is to read the 3D model and 2D Drawings; a value of \c FALSE is to read only the 3D model. */
	A3DEReadGeomTessMode m_eReadGeomTessMode;	/*!< Enum to set the content to read (Geometry and/or Tessellation). */
	A3DEUnits m_eDefaultUnit;		/*!<
										DefaultUnit option restricted to those formats where unit never exists or is unreliable (U3D, CGR, STL, VRML)
										\li If it is different than \ref kA3DUnitUnknown, the default unit used is the one defined with this enum
										\li If it is set to \ref kA3DUnitUnknown, the default unit is considered unknown and the value is 1.0. */
	A3DBool m_bReadFeature;			/*!< For future use. */
	A3DInt32 m_iNbMultiProcess;		/*!< Use multi-process mode. /version 8.0. */
	A3DUns32 m_uiSearchTextureDirectoriesSize;			/*!< Size of next array. /version 8.0. */
	A3DUTF8Char ** m_ppcSearchTextureDirectories;		/*!<
															Array of additional directories that the load function
															will search in addition to the texture file. /version 8.0. */
} A3DRWParamsGeneralData;


/*!
\ingroup a3d_read
\brief Structure to specify the PMI reading parameters.

Only used if A3DRWParamsGeneralData::m_bReadPmis is set to \c TRUE.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bAlwaysSubstituteFont;	/*!< A value of \c TRUE is to substitute the fonts in the CAD file with the font that is specified in \ref m_pcSubstitutionFont. */
	A3DUTF8Char* m_pcSubstitutionFont;	/*!< The font used to replace any fonts that are not installed on the computer. If \ref m_bAlwaysSubstituteFont is \c TRUE, this font replaces all the fonts in the file. */
	int m_iNumberOfDigitsAfterDot;		/*!< Number of decimal places to use for numeric values if no decimal information is specified in the CAD file. */
	A3DEUnits m_eDefaultUnit;			/*!<
											Units of measure to use if no unit information is specified in the CAD file.
											Note that only a short set of CAD formats do not specify the unit information and will use this member,
											other formats should specify \ref kA3DUnitUnknown. */
	A3DUns32 m_uiProprietaryFontDirectoriesSize;	/*!< Size of next array. */
	A3DUTF8Char** m_ppcProprietaryFontDirectories;	/*!<
														Usually, fonts are retrieved from the system directory.
														These paths enable to specify the locations of additional fonts. */
	A3DGraphRgbColorData m_sDefaultColor;			/*!< Color to use when PMI has no color. /version 6.1 */
	A3DBool m_bAlwaysUseDefaultColor;				/*!< A value of \c TRUE is to substitute the color of PMI in the CAD file with the default color that is specified in \ref m_sDefaultColor. /version 9.0 */
} A3DRWParamsPmiData;


/*!
\ingroup a3d_read
\brief Structure to specify the level of detail of the tessellation.

See \ref A3DRWParamsTessellationData parameters.
When a level is given, the Chord Height Ratio (\ref A3DRWParamsTessellationData::m_dChordHeightRatio) and 
Wireframe Chord Angle (\ref A3DRWParamsTessellationData::m_dAngleToleranceDeg) change to preset values for the selected level. 
\version 3.0
*/
typedef enum 
{
	kA3DTessLODExtraLow,				/*!< Extra Low level: when selected, these members are automatically defined with the following values:
											\li \ref A3DRWParamsTessellationData::m_dChordHeightRatio = 50,
											\li \ref A3DRWParamsTessellationData::m_dAngleToleranceDeg = 40. */
	kA3DTessLODLow,						/*!< Low level: when selected, these members are automatically defined with the following values:
											\li \ref A3DRWParamsTessellationData::m_dChordHeightRatio = 600,
											\li \ref A3DRWParamsTessellationData::m_dAngleToleranceDeg = 40. */
	kA3DTessLODMedium,					/*!< Medium level: when selected, these members are automatically defined with the following values:
											\li \ref A3DRWParamsTessellationData::m_dChordHeightRatio = 2000,
											\li \ref A3DRWParamsTessellationData::m_dAngleToleranceDeg = 40. */
	kA3DTessLODHigh,					/*!< High level: when selected, these members are automatically defined with the following values:
											\li \ref A3DRWParamsTessellationData::m_dChordHeightRatio = 5000,
											\li \ref A3DRWParamsTessellationData::m_dAngleToleranceDeg = 30. */
	kA3DTessLODExtraHigh,				/*!< Extra High level: when selected, these members are automatically defined with the following values:
											\li \ref A3DRWParamsTessellationData::m_dChordHeightRatio = 10000,
											\li \ref A3DRWParamsTessellationData::m_dAngleToleranceDeg = 20. */
	kA3DTessLODUserDefined,				/*!< User Defined level: when selected, these members should be defined:
											\li \ref A3DRWParamsTessellationData::m_dChordHeightRatio if \ref A3DRWParamsTessellationData::m_bUseHeightInsteadOfRatio is set to false,
											\li \ref A3DRWParamsTessellationData::m_dMaxChordHeight if \ref A3DRWParamsTessellationData::m_bUseHeightInsteadOfRatio is set to true,
											\li \ref A3DRWParamsTessellationData::m_dAngleToleranceDeg.
											Be very careful when using A3DRWParamsTessellationData::m_dMaxChordHeight because a too small value would generate a huge tessellation. */
	kA3DTessLODControlledPrecision		/*!< This is a deprecated feature. Controlled Precision level: when selected, these members should be defined:
											\li \ref A3DRWParamsTessellationData::m_dAngleToleranceDeg,
											\li \ref A3DRWParamsTessellationData::m_dMaxChordHeight,
											\li \ref A3DRWParamsTessellationData::m_dMinimalTriangleAngleDeg. */
} A3DETessellationLevelOfDetail;

/*!
\ingroup a3d_read
\brief Structure to set the tessellation parameters.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DETessellationLevelOfDetail m_eTessellationLevelOfDetail;		/*!< Enum to specify predefined values for some following members. */
	A3DDouble m_dChordHeightRatio;			/*!<
												Specifies the percentage of bounding box used to compute chord height. 
												Set a value from 50 through 10,000. */
	A3DDouble m_dAngleToleranceDeg;			/*!<
												Specifies the maximum angle between two contiguous segments of wire edges for every face. 
												The value must be from 10 through 40. */
	A3DDouble m_dMinimalTriangleAngleDeg;	/*!<
												Specifies the angle between two contiguous segments of wire edges for every face. 
												Allowable values range from 10 through 30. */
	A3DDouble m_dMaxChordHeight;			/*!<
												Specifies the maximum distance between surface and tessellation. Be careful, a too small value can generate a huge tessellation. */ 
	A3DBool m_bAccurateTessellation;		/*!< Accurate tessellation. Uses standard parameters. 'false' indicates the tessellation is set for visualization. Setting this value to 'true' will generate tessellation more suited for analysis. Can be used with all TessellationLevelOfDetails. */ 
	A3DBool m_bDoNotComputeNormalsInAccurateTessellation;  /*!< Do not compute surface normals in accurate tessellation. */ 
	A3DBool m_bKeepUVPoints;				/*!< Keep parametric points as texture points. */
	A3DBool m_bUseHeightInsteadOfRatio;		/*!< Use \ref m_dMaxChordHeight instead of \ref m_dChordHeightRatio if \ref m_eTessellationLevelOfDetail = \ref kA3DTessLODUserDefined. */
	A3DDouble m_dMaximalTriangleEdgeLength;	/*!< Maximal length of the edges of triangles. Disabled if value is 0. Be careful, a too small value can generate a huge tessellation. */
} A3DRWParamsTessellationData;

/*!
\ingroup a3d_read
\brief Structure to define additional directories that the load function will search in addition to the root directory.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcPhysicalPath;		/*!< Path of the additional directory. */
	A3DUTF8Char* m_pcLogicalName;		/*!< Only used with CATIA V4 files (see \ref A3DRWParamsCatiaV4Data). */
	A3DBool m_bRecursive;				/*!< A value of \c TRUE specifies that the load function uses recursive searching for the additional directory. */
} A3DRWParamsSearchDirData;

/*!
\ingroup a3d_read
\brief Structure to define parameters to manage CAD assemblies reading.

This is valid only for CAD formats handling assemblies.
These options identify the locations that the load function searches to load subassemblies and parts for the assembly document.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bUseRootDirectory;		/*!<
											With a value of \c TRUE, the load function searches subparts in the same directory as the head of the assembly.
											If not found, they are searched for in the additional search directories (\ref m_ppcSearchDirectories). */
	A3DBool m_bRootDirRecursive;		/*!<
											Only used if \ref m_bUseRootDirectory is \c TRUE.
											With a value of \c TRUE, the load function searches for all subparts of an assembly in the root directory of the assembly file.
											Then, it searches the subdirectories for any files that it did not find in the root directory. */
	A3DUns32 m_uiSearchDirectoriesSize;	/*!< Size of next array. */
	A3DRWParamsSearchDirData** m_ppcSearchDirectories;		/*!< Array of additional directories that the load function will search in addition to the root. */
	A3DUns32 m_uiPathDefinitionsSize;	/*!< Size of next array. */
	A3DUTF8Char** m_ppcPathDefinitions; /*!<
											Array to specify the location of text files that define additional paths. 
											A text file contains all paths and recursive options. It follows this format: <tt> "path name", [recursive = ] 1/0</tt> \n
											Examples:
											\code
											"c:\data\project\",recursive=1
											"f:\parts",recursive=0
											"d:\special ",1
											"x:\standard-data\production",0 
											\endcode */ 
} A3DRWParamsAssemblyData;

/*!
\ingroup a3d_read
\brief Structure to define which configurations or sub-models should be loaded when the CAD file has multiple entries.

Some CAD formats may create CAD files with multiple entries. For these files, the A3DRWParamsMultiEntriesData structure
must be used to specify to the load function which entry should be loaded. 
The entry can be specified by its name, or it can be the default entry if the CAD file contains one.
<br>
The A3DRWParamsMultiEntriesData structure is implemented for following CAD formats:
<ul>
<li> CATIA V4: Multiple entries are for sub-models. CATIA V4 files never contain default entries. </li>
	<ul>
	<li> \ref m_bLoadDefault is not implemented.</li>
	<li> \ref m_ppcEntries should contain a single name, the name of the root product occurrence to load. </li>
	<li> The load function loads the selected entry, other entries are not loaded, in any way.	</li>
	<li> Entries names can be retrieved from a first call to the load function, and a parsing of the returned model file and the
	product occurrences structure. Here, note that only the root product occurrences should be parsed.</li>
	</ul>
<li> SolidWorks: Multiple entries are for configurations. SolidWorks files always contain a default entry.</li>
	<ul>
	<li> \ref m_bLoadDefault is implemented. </li>
	<li> \ref m_ppcEntries should contain a single name, the name of the configuration to load. </li>
	<li> The load function loads the selected entry, other entries are loaded in a 'structure only' mode 
	(only the Product Occurrences structure is loaded, not the geometric content; all these Product Occurrences
	have a status which is not Loaded).</li>
	<li> Entries names can be retrieved from a first call to the load function, and a parsing of the returned model file and the
	product occurrences structure. Here, note that only the product occurrences of type 'Configuration', sons of the root
	'Container' product	should be parsed (see \ref A3DAsmProductOccurrenceData::m_uiProductFlags and \ref a3d_product_flag).	</li>
	</ul>
</ul>


The load function behaves as follows:
\li If no MultiEntries parameter is specified and the file contains multiple entries, the load function loads the product 
structure only, and returns an error \ref A3D_LOAD_MULTI_MODELS_CADFILE. The user can use the returned model file to get
the Entry names which will be useful to a second call of the load function with the selected entry.
\li If no MultiEntries parameter is specified and the file contains only one entry, the load function automatically loads the model.
\li If the file contains a default entry and \ref m_bLoadDefault is \c TRUE, the load function automatically loads the default entry. 
\li if \ref m_ppcEntries defines an entry as described above and the file contains multiple entries, the selected entry is loaded.


\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bLoadDefault;			/*!< A value of \c TRUE is to load the default entry on a multi-entry file. Nothing changes for non multi-entry files. */
	A3DUns32 m_uiEntriesSize;		/*!< Size of next array. */
	A3DUTF8Char** m_ppcEntries;		/*!< Strings defining the entry to load in case of a multi-entry file. See description paragraph above. */
} A3DRWParamsMultiEntriesData;



/*!
\ingroup a3d_read
\brief Reading parameters specific to CATIA V4 CAD files.

These parameters are related to CATIA V4 logical names handling (DDName). They should be used in conjunction with the Assembly options 
specified in A3DRWParamsAssemblyData and A3DRWParamsSearchDirData.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcRootDirLogicalName;		/*!<
													Only used if \ref A3DRWParamsAssemblyData::m_bUseRootDirectory is \c TRUE. 
													If so, the load function first searches subparts in the same directory as the head of the assembly.
													This member enables to define the LogicalName used to perform this root search. */
	A3DBool m_bAllowSearchInOtherLogicalNames;	/*!<
													A value of \c TRUE specifies that the search can be also performed in other directories.
													A value of \c FALSE specifies that the search should be done only in the real logical name of the file. */ 
} A3DRWParamsCatiaV4Data;

/*!
\ingroup a3d_read
\brief Reading parameters specific to CATIA V5 CAD files.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bCacheActivation;		/*!< A value of \c TRUE activates the representation mode which may be used with large CATIA V5 assemblies. */
	A3DUTF8Char* m_pcCachePath;		/*!< Specifies the folder that the load function uses as the cache folder. */
} A3DRWParamsCatiaV5Data;

/*!
\ingroup a3d_read
\brief Reading parameters specific to Unigraphics CAD files.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bApplyToAllLevels;				/*!< With a value of \c TRUE, the reference sets will apply to all the components including subassemblies. */
	A3DUns32 m_uiPreferredReferenceSetsSize;	/*!< Size of next array. */
	A3DUTF8Char** m_ppcPreferredReferenceSets;	/*!< Determines how references sets are determined and in what priority. */
	A3DBool m_bFitAllToUpdateViewCameras;		/*!< With a value of \c TRUE, the camera views will be computed after a fit all. */
} A3DRWParamsUnigraphicsData;

/*!
\ingroup a3d_read
\brief Used to control the default PMI color:
If you load a Wildfire file and set kA3DFileVersionSessionColor to:
- kA3DFileVersionSessionColor, the PMI with no color will be displayed in yellow;
- kA3DLastCreoVersionSessionColor, the PMI with no color will be displayed in blue as in Creo 2 (for HOOPS Exchange 6.0);
- kA3DHExchangeSessionColor, the PMI with no color will be displayed with the color you chose.
\version 6.1
*/
typedef enum
{
	kA3DLastCreoVersionSessionColor = 0,	/*!< Sets the default session color corresponding to the last version of Creo that HOOPS Exchange supports. */
	kA3DHExchangeSessionColor,				/*!< Uses HOOPS Exchange default color. */
	kA3DFileVersionSessionColor				/*!< Lets the user define the color by using graphics parameters options ( \ref A3DRWParamsPmiData::m_sDefaultColor). */
} A3DProESessionColorType;

/*!
\ingroup a3d_read
\brief Used to control the construction entities reading, entity such as sketch, curves...
\version 8.2
*/
typedef enum
{
	A3DProEReadConstructEntities_AsDatum = 0,	/*!<  Read wire according to the datum reading option*/
	A3DProEReadConstructEntities_Yes,				/*!< read wire*/
	A3DProEReadConstructEntities_No				/*!< Do not read wire*/
} A3DProEReadConstructEntities;

/*!
\ingroup a3d_read
\brief Used to select how to read family tables
\version 9.0
*/
typedef enum
{
	A3DProEFamTabAcceleratorFileOnly = 0,	/*!< Only use accelerator file that is to say even there's tessellation or generic non will be used*/
	A3DProEFamTabOrUseTessellation = 1,	 	/*!< If the accelerator file isn't present then we search for the tessellation representation: if found and we use it*/
	A3DProEFamTabOrUseWireAndGeneric = 2 	/*!< If none of the accelerator file or the tessellation representation is present so we use the generic or wire representation: be aware that the representation will not be what the configuration should be! it's like a placebo in order to have something*/
} A3DProEFamilyTables;



/*!
\ingroup a3d_read
\brief Reading parameters specific to Pro/ENGINEER CAD files.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcCodePageName;				/*!<
													Code page to use for text conversion to Unicode. 
													The values for CodePageName are those usable in the iconv GNU Package
													Example: EUC-JP for Japanese files. */
	A3DBool m_bDisplayTolerance;				/*!< With a value of \c TRUE, read and display the tolerances for dimensions. */
	A3DBool m_bDisplaySubpartAnnotations;		/*!< With a value of \c TRUE, access to the PMIs in subparts in an assembly. */
	A3DProESessionColorType m_eSessionColorType;/*!< Defines the default PMI color type. */
	A3DProEFamilyTables m_eFamilyTables;		/*!< How to read family tables. 0: XPR/XAS only, 1: XPR/XAS, if not: Tessellation, 2: XPR/XAS, if not: Tessellation, if not: Wire+Generic. /version 9.0 */
	A3DBool m_bBoolOpUseGenericIfNoTess;		/*!< With a value of \c TRUE, display the generic form of the element if boolean operation and no tessellation to represent it. /version 9.0 */
	A3DBool m_bFlexCompUseGenericIfNoTess;		/*!< With a value of \c TRUE, display the generic form of the element if flexible component and no tessellation to represent it. /version 9.0 */
	A3DBool m_bHideSkeletons;					/*!< With a value of \c TRUE, hides all skeleton type elements from the file. */
	A3DBool m_bReadExplodeStateAsView;			/*!< With a value of \c TRUE, create a view for each explode state. */
	A3DBool m_bDisplayVisibleDatum;				/*!< Manage the visibility of datum entities /version 9.1 */
	A3DProEReadConstructEntities m_eReadConstructEntities;		/*!< Control the sketch reading */
	A3DBool m_bComputeHomeView;					/*!< With a value of \c TRUE, There will be an additionnal view that reflect the current states (orientation, explode, ...). */
	A3DBool m_bHandlePMIScreenLocation;			/*!<  With a value of \c TRUE, treat scrren location in markup reading. /version 9.1 */
} A3DRWParamsProEData;

/*!
\ingroup a3d_read
\brief Used to select which name to use from NEXT_ASSEMBLY_USAGE_OCCURRENCE as occurrence name.
\version 4.2
*/
typedef enum
{
	kA3DStepNameFromNAUO_ID = 0,				/*!< First Field of NEXT_ASSEMBLY_USAGE_OCCURRENCE. */
	kA3DStepNameFromNAUO_NAME,					/*!< Second Field of NEXT_ASSEMBLY_USAGE_OCCURRENCE. */
	kA3DStepNameFromNAUO_DESCRIPTION			/*!< Third Field of NEXT_ASSEMBLY_USAGE_OCCURRENCE. */
} A3DEStepNameFromNAUO;


/*!
\ingroup a3d_read
\brief Reading parameters specific to STEP files.
\version 4.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bPreferProductName;				/*!<
													With a value of \c TRUE, the name of the occurrence is the one defined by PRODUCT. 
													Otherwise it is the one defined by NEXT_ASSEMBLY_USAGE_OCCURRENCE. */
	A3DBool m_bPreferFirstColor;				/*!< In case a geometry has several colors (with STYLED_ITEM), prefer the first one. */
	A3DEStepNameFromNAUO m_eNameFromNAUO;		/*!< In case \ref m_bPreferProductName = \c FALSE, indicate which name to use from NEXT_ASSEMBLY_USAGE_OCCURRENCE. */ 
	A3DUTF8Char* m_pcCodePageName;				/*!<
													Code page to use for text conversion to Unicode. 
								   					The values for CodePageName are those usable in the iconv GNU Package
								   					Example: EUC-JP for Japanese files. /version 7.1 */
	A3DBool m_bSplitSHELL_BASED_SURFACE_MODEL;	/*!< If \c TRUE, split SHELL_BASED_SURFACE_MODEL with several OPEN_SHELLs into several bodies. /version 7.2 */
	A3DBool m_bHealOrientations;				/*!< If \c TRUE, activate orientation healing on the modelfile. Reading time will be longer. /version 7.2 */
	A3DBool m_bReadValidationProperties; /*!< requires to have m_bReadAttributes=true */
} A3DRWParamsStepData;

/*!
\ingroup a3d_read
\brief Reading parameters specific to IGES files.
\version 5.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bSewBrepModels;					/*!< DEPRECATED. Please use \ref A3DAsmModelFileSew instead. */
} A3DRWParamsIGESData;

/*!
\ingroup a3d_read
\brief Reading parameters specific to IFC files.
\version 5.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcCodePageName;				/*!<
													Code page to use for text conversion to Unicode. 
													The values for CodePageName are those usable in the iconv Gnu Package
													Example: EUC-JP for Japanese files. */
	A3DUTF8Char* m_pcXMLFilePathForAttributes;	/*!< If set and m_bReadAttributes==true , attributes will be saved to this external XML file. /version 7.1 */
	A3DBool m_bIFCOWNERHISTORYOptimized;		/*!<
													If true, IFCOWNERHISTORY will be set only when necessary in order to avoid repetition.
													Otherwise, IFCOWNERHISTORY will be set on all items (default behavior until version 7.1). /version 7.1 */
	A3DBool m_bFACETED_BREPAsOneFace;			/*!< If true, FACETEDBREP faces are gathered in one face. /version 8.0. */
	A3DBool m_bAttributesOnlyGlobalId;          /*!< If true, writes only GlobalId as attribute. /version 8.0. */
} A3DRWParamsIFCData;


/*!
\ingroup a3d_read
\brief JT LOD to retrieve from file.
\version 8.0
*/
typedef enum
{
	JTTessLODLow = 0,		/*!< Will load the lowest level of tessellation available in the JT file. */ 
	JTTessLODMedium,		/*!< Will load an in-between level of tessellation available in the JT file. */ 
	JTTessLODHigh,			/*!< Will load the highest level of tessellation available in the JT file. */ 
} A3DEJTReadTessellationLevelOfDetail;

/*!
\ingroup read
\brief A structure that specifies parameters used to read the model file to JT format.
\version 8.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;									/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DEJTReadTessellationLevelOfDetail m_eReadTessellationLevelOfDetail;	/*!<  LOD to retrieve: low, medium or high. */
} A3DRWParamsJTData;


/*!
\ingroup read
\brief A structure that specifies parameters used to read the model file to Parasolid format.
\version 8.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;									/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bKeepParsedEntities;	/*!< Keep parsed data to avoid passing by PRC data when rewriting to parasolid */
} A3DRWParamsParasolidData;

/*!
\ingroup read
\brief A structure that specifies parameters used to read the model file to Solidworks format.
\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;									/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bLoadAllConfigsData;								/*!< Ask to load data, tree, attributes, representation, PMI, for all configs */
} A3DRWParamsSolidworksData;

/*!
\ingroup read
\brief A structure that specifies parameters used to read the model file to Inventor format.
\version 9.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;									/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bUseTessForFile;									/*!< Use the embedded tessellation instead of generating one. /version 9.0 */
} A3DRWParamsInventorData;


/*!
\ingroup a3d_read
\brief Structure to specify reading parameters specific to some CAD formats.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DRWParamsCatiaV4Data m_sCatiaV4;			/*!< Reading parameters specific to CATIA V4. */
	A3DRWParamsCatiaV5Data m_sCatiaV5;			/*!< Reading parameters specific to CATIA V5. */
	A3DRWParamsUnigraphicsData m_sUnigraphics;	/*!< Reading parameters specific to UG. */
	A3DRWParamsProEData m_sProE;				/*!< Reading parameters specific to ProE. */
	A3DRWParamsStepData m_sStep;				/*!< Reading parameters specific to STEP. */
	A3DRWParamsIGESData m_sIGES;				/*!< Reading parameters specific to IGES. */
	A3DRWParamsIFCData m_sIFC;					/*!< Reading parameters specific to IFC. /version 5.2. */
	A3DRWParamsJTData m_sJT;					/*!< Reading parameters specific to JT.  /version 8.0. */ 
	A3DRWParamsParasolidData m_sParasolid;		/*!< Reading parameters specific to Parasolid.  /version 8.1. */ 
	A3DRWParamsSolidworksData m_sSolidworks;	/*!< Reading parameters specific to Solidworks.  /version 8.2. */
	A3DRWParamsInventorData m_sInventor;		/*!< Reading parameters specific to Inventor.  /version 9.0. */
} A3DRWParamsSpecificLoadData;

/*!
\ingroup a3d_read
\brief Structure to specify reading parameters to load some specific parts of an assembly.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bLoadStructureOnly;						/*!< With a value of \c TRUE, read and return only the tree of the assembly in a model file. */
	A3DBool m_bLoadNoDependencies;						/*!< With a value of \c TRUE, read and return only the first level of the tree of the assembly in a model file. */
	A3DAsmProductOccurrence *m_pRootProductOccurrence;	/*!< Root of the product occurrence to read. */
	A3DUns32 m_uiProductOccurrencesSize;				/*!< Size of next array. */
	A3DAsmProductOccurrence **m_ppProductOccurrences;	/*!< Array of product occurrences to read. They must be sons of m_pRootProductOccurrence. */
} A3DRWParamsIncrementalLoadData;

/*!
\ingroup a3d_read
\brief Structure to define the reading parameters used by the load function \ref A3DAsmModelFileLoadFromFile.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DRWParamsGeneralData m_sGeneral;					/*!< Specifies the general reading parameters. */
	A3DRWParamsPmiData m_sPmi;							/*!< Specifies the PMI reading parameters. */
	A3DRWParamsTessellationData m_sTessellation;		/*!< Specifies the tessellation reading parameters. */
	A3DRWParamsAssemblyData m_sAssembly;				/*!< Specifies the reading parameters used to load Assembly files. */
	A3DRWParamsMultiEntriesData m_sMultiEntries;		/*!< Specifies the parameters used to read multiple-models. */
	A3DRWParamsSpecificLoadData m_sSpecifics;			/*!< Specifies the reading parameters for some specific CAD formats. */
	A3DRWParamsIncrementalLoadData m_sIncremental;		/*!< Specifies the reading parameters used to load specific parts of an assembly. */
} A3DRWParamsLoadData;



/*!
\ingroup a3d_read
\brief Loads an \ref A3DAsmModelFile from a physical file.

This function loads an \ref A3DAsmModelFile from a file. The file could be in any supported CAD format.

\param [in] pcFileName References the path to the file containing the 3D CAD model.
\param [in] pLoadParametersData References the parameters for reading.
\param [out] ppModelFile References a pointer into which should be stored the location 
of the model file. Set this pointer to null before calling the function.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_LOAD_CANNOT_ACCESS_CADFILE \n
\return \ref A3D_LOAD_READER_NOT_IMPLEMENTED \n
\return \ref A3D_LOAD_CANNOT_LOAD_MODEL \n
\return \ref A3D_LOAD_CANNOT_LOAD_MULTIENTRY \n
\return \ref A3D_LOAD_EMPTY_MULTI_MODEL \n
\return \ref A3D_LOAD_MISSING_COMPONENTS \n
\return \ref A3D_LOAD_MULTI_MODELS_CADFILE if the file contains multiple entries (see A3DRWParamsMultiEntriesData). \n
\return \ref A3D_LOAD_INVALID_FILE_FORMAT \n
\return \ref A3D_SUCCESS \n

\version 3.0
*/
A3D_API (A3DStatus, A3DAsmModelFileLoadFromFile,(
	const A3DUTF8Char* pcFileName,
	const A3DRWParamsLoadData* pLoadParametersData,
	A3DAsmModelFile** ppModelFile));


/*!
\brief Sets the license for the current instance.
\ingroup a3d_license_module
\param [in] pcKey The license to be set.
*/
A3D_API (A3DVoid, A3DLicPutPRCLicense,(const A3DUTF8Char* pcKey));


/*!
\ingroup a3d_read
\brief Returns the format of a physical file.

\param [in] pcFileName References the path to the CAD file
\param [out] peModellerType References the format of the input CAD file

\return \ref A3D_INVALID_LICENSE \n
\return \ref A3D_LOAD_CANNOT_ACCESS_CADFILE \n
\return \ref A3D_LOAD_CANNOT_LOAD_MODEL \n
\return \ref A3D_LOAD_CANNOT_LOAD_MULTIENTRY \n
\return \ref A3D_LOAD_EMPTY_MULTI_MODEL \n
\return \ref A3D_LOAD_INVALID_FILE_FORMAT \n
\return \ref A3D_LOAD_MISSING_COMPONENTS \n
\return \ref A3D_LOAD_MULTI_MODELS_CADFILE \n
\return \ref A3D_LOAD_READER_NOT_IMPLEMENTED \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_WRITER_NOT_IMPLEMENTED \n
\return \ref A3D_SUCCESS \n

\version 3.0
*/
A3D_API (A3DStatus, A3DGetFileFormat, (
	const A3DUTF8Char* pcFileName,
	A3DEModellerType *peModellerType));


/*!
\ingroup a3d_read
\brief Checks the format of a physical file.

\param [in] pcFileName References the path to the CAD file
\param [in] rCadTypeWanted References the format that the input CAD file is going to be checked against

\return \ref A3D_INVALID_LICENSE \n
\return \ref A3D_LOAD_CANNOT_ACCESS_CADFILE \n
\return \ref A3D_LOAD_CANNOT_LOAD_MODEL \n
\return \ref A3D_LOAD_CANNOT_LOAD_MULTIENTRY \n
\return \ref A3D_LOAD_EMPTY_MULTI_MODEL \n
\return \ref A3D_LOAD_INVALID_FILE_FORMAT \n
\return \ref A3D_LOAD_MISSING_COMPONENTS \n
\return \ref A3D_LOAD_MULTI_MODELS_CADFILE \n
\return \ref A3D_LOAD_READER_NOT_IMPLEMENTED \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_WRITER_NOT_IMPLEMENTED \n
\return \ref A3D_SUCCESS \n

\version 6.0
*/
A3D_API (A3DStatus, A3DCheckFileFormat, (
		 const A3DUTF8Char* pcFileName,
		 const int& rCadTypeWanted));

/*!
\ingroup a3d_read
\brief Thumbnail data

\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns8 *m_pcBuffer;						/*!< Thumbnail buffer. */
	A3DEPictureDataFormat m_eFormat;			/*!< References the format of the thumbnail */
	A3DInt32 m_iLength;							/*!< Length of the thumbnail buffer. */
}A3DThumbnailData;

/*!
\ingroup a3d_read
\brief Extract thumbnail stored in a CAD file.

\param [in] pcFileName References the path to the CAD file
\param [out] pThumbnailData References the thumbnail data

\return \ref A3D_INVALID_LICENSE \n
\return \ref A3D_LOAD_CANNOT_ACCESS_CADFILE \n
\return \ref A3D_LOAD_CANNOT_LOAD_MODEL \n
\return \ref A3D_LOAD_CANNOT_LOAD_MULTIENTRY \n
\return \ref A3D_LOAD_EMPTY_MULTI_MODEL \n
\return \ref A3D_LOAD_INVALID_FILE_FORMAT \n
\return \ref A3D_LOAD_MISSING_COMPONENTS \n
\return \ref A3D_LOAD_MULTI_MODELS_CADFILE \n
\return \ref A3D_LOAD_READER_NOT_IMPLEMENTED \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_WRITER_NOT_IMPLEMENTED \n
\return \ref A3D_SUCCESS \n

\version 8.2
*/
A3D_API(A3DStatus, A3DExtractFileThumbnail, (
	const A3DUTF8Char* pcFileName,
	A3DThumbnailData *pThumbnailData));

/*!
\ingroup a3d_read
\brief File 

\version 8.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DEModellerType m_eModellerType;			/*!< Modeller type. */
	A3DUTF8Char *m_pcModelName;					/*!< Model name. */
	A3DUTF8Char *m_pcSoftwareVersion;			/*!< Software release */
	A3DUTF8Char *m_pcAuthor;					/*!< Author */
	A3DUTF8Char *m_pcOrganization;				/*!< Organization */
	A3DInt32	m_iTimeStamp;					/*!< TimeStamp. */
}A3DFileInformationData;

/*!
\ingroup a3d_read
\brief Get file information a CAD file.

\param [in] pcFileName References the path to the CAD file
\param [out] pFileInformationData References the information of the input CAD file

\return \ref A3D_INVALID_LICENSE \n
\return \ref A3D_LOAD_CANNOT_ACCESS_CADFILE \n
\return \ref A3D_LOAD_CANNOT_LOAD_MODEL \n
\return \ref A3D_LOAD_CANNOT_LOAD_MULTIENTRY \n
\return \ref A3D_LOAD_EMPTY_MULTI_MODEL \n
\return \ref A3D_LOAD_INVALID_FILE_FORMAT \n
\return \ref A3D_LOAD_MISSING_COMPONENTS \n
\return \ref A3D_LOAD_MULTI_MODELS_CADFILE \n
\return \ref A3D_LOAD_READER_NOT_IMPLEMENTED \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_WRITER_NOT_IMPLEMENTED \n
\return \ref A3D_SUCCESS \n

\version 8.2
*/
A3D_API(A3DStatus, A3DGetFileInformation, (
	const A3DUTF8Char* pcFileName,
	A3DFileInformationData *pFileInformationData));


/*!
\ingroup a3d_read
\brief Binary stream for a 3D model stored in a PDF file. The data format is PRC or U3D.

\version 6.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char *m_pcStream;					/*!< 3D stream. */
	A3DBool m_bIsPrc;							/*!< True if stream is PRC data, false if it is U3D data. */
	A3DInt32 m_iLength;							/*!< Length of the stream. */
}A3DStream3DPDFData;

/*!
\ingroup a3d_read
\brief Function to retrieve all 3D streams embedded in a PDF document.

The stream is the raw binary data stored as a char* stream. A PRC stream can be interpreted with the function A3DAsmModelFileLoadFromPrcStream. 
A U3D stream needs to be written as a physical file before being read with classical A3DAsmModelFileLoadFromFile function.
\param [in] pcFileName References the path to the PDF file
\param [out] ppStreamData Array of stream data
\param [out] piNumStreams Number of streams

If pcFileName is NULL, *ppStreamData will be freed if *piNumStreams is non-null. A3DGet3DPDFStreams(NULL, ppStreamData, piNumStreams) to 
release *ppStreamData.

\return \ref A3D_LOAD_CANNOT_ACCESS_CADFILE \n
\return \ref A3D_SUCCESS \n

\version 6.0
*/
A3D_API (A3DStatus, A3DGet3DPDFStreams, (
		 const A3DUTF8Char* pcFileName, 
		 A3DStream3DPDFData** ppStreamData, 
		 A3DInt32* piNumStreams));

#endif	/*	__A3D_RW_READ__ */


#ifndef __A3D_RW_WRITE__
/*!
\defgroup a3d_write Write functions
\ingroup a3d_readwrite_module
\brief Writing modelfiles defined through this API.

Available formats are: PRC, ACIS, IGES, JT, STEP, Parasolid, STL and VRML.
*/

/*!
\ingroup a3d_write
\brief Level of compression used to write the model file to PRC format.

This sets the amount, in millimeters, of lossy compression that is applied to geometry. 
For best results when exporting geometry, use kA3DCompressionLow.
\version 3.0
*/
typedef enum
{
	kA3DCompressionLow = 0,	/*!< Compression with tolerance set to 0.001 mm (low compression, high accuracy). */
	kA3DCompressionMedium,	/*!< Compression with tolerance set to 0.01 mm (medium compression, medium accuracy). */
	kA3DCompressionHigh		/*!< Compression with tolerance set to 0.1 mm (high compression, low accuracy). */
} A3DECompressBrepType;

/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to write the model file to PRC format.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bCompressBrep;					/*!< Is the B-rep data to be compressed? */
	A3DBool m_bCompressTessellation;			/*!< A value of \c TRUE applies lossy compression to polygons. */
	A3DECompressBrepType m_eCompressBrepType;	/*!< Level of B-rep compression. */
	A3DBool m_bRemoveBRep;						/*!< Removes B-rep data from the model. /version 6.1 */
	A3DBool m_bRemoveAttributes;                /*!< Removes attributes from the model. /version 6.1 */
} A3DRWParamsExportPrcData;

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in a PRC format.

This function writes the \ref A3DAsmModelFile entity to a physical file. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pcCADFileName References the path of the file into which the function stores the model file.
\param [in,out] ppPrcWriteHelper Reserved for future use; must be set to NULL.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 3.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToPrcFile, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportPrcData* pParamsExportData,
	const A3DUTF8Char* pcCADFileName,
	A3DRWParamsPrcWriteHelper** ppPrcWriteHelper));


/*!
\ingroup a3d_write
\brief Extract file paths from a model file.

This function reads the \ref A3DAsmModelFile extracts the file path of all the sub-assemblies, part and missing files
of the \ref A3DAsmModelFile.\n
Sub-assemblies are files referencing other files (part files or other sub-assemblies files).\n
Part files are final files with no reference to an other depending file.\n
If a file has reference on both types of file, the file will be considered as a sub-assembly file and will not be
referenced in the part file path array.\n
Missing files path are sub-files that cannot be loaded for some reasons: bad paths, file not found...

If pA3DAsmModelFile is NULL, the two A3DUTF8Char arrays will be freed if the corresponding unsigned int parameters are
non-null: A3DAsmGetFilesPathFromModelFile(NULL, [...]) to delete the two arrays.

\param [in] pA3DAsmModelFile The input model file. Can be "tree only" A3DAsmModelFile.
\param [out] uNbPartFiles The number of parts detected. (must not be NULL)
\param [out] ppPartFilesPaths The file names of detected parts. (must not be NULL)
\param [out] uNbAssemblyFiles The number of sub-assemblies detected. (can be NULL)
\param [out] ppAssemblyFilesPaths The file names of detected sub-assemblies. (can be NULL)
\param [out] uNbMissingFiles The number of missing files. (can be NULL)
\param [out] ppMissingFilesPaths The file names of detected missing files. (can be NULL)

\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_SUCCESS \n

\version 5.0
*/
A3D_API ( A3DStatus, A3DAsmGetFilesPathFromModelFile, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	A3DUns32* uNbPartFiles,
	A3DUTF8Char*** ppPartFilesPaths,
	A3DUns32* uNbAssemblyFiles,
	A3DUTF8Char*** ppAssemblyFilesPaths,
	A3DUns32* uNbMissingFiles,
	A3DUTF8Char*** ppMissingFilesPaths));



/*!
\ingroup a3d_write
\brief Extract all the files contexts (RefSet, Configs...) from a model file.

\param [in] pA3DAsmModelFile The input model file. Can be "tree only" A3DAsmModelFile.
\param [out] uNbFilesContexts The number of files contexts detected. (must not be NULL)
\param [out] ppFilesContexts The file contexts. (must not be NULL)

\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_SUCCESS \n

\version 8.1
*/
A3D_API ( A3DStatus, A3DAsmGetFilesContextsFromModelFile, (
		 const A3DAsmModelFile* pA3DAsmModelFile,
		 A3DUns32* uNbFilesContexts,
		 A3DFileContextData*** ppFilesContexts));




/*!
\ingroup a3d_write
\brief Creates a model file from multiple PRC files + an PRC assembly file + a map for file names.
This function replugs all the parts And Product from a list from a PRC file loaded with an "assembly NO Dependency" mode.

\param [in] pcRootPrcFilePath The file name of the top assembly file. Conceived for model file loaded as assembly tree only and saved as a PRC file.
\param [in] uNbFile The number of file names to plug.
\param [in] ppPRCFilePath The native part file paths. Length must equal uNbPart.
\param [in] ppCADFilePath The equivalent PRC file paths for parts. Length must equal uNbPart.
\param [in] pParamsLoadData The read parameters use the model file. Configurations must be set (default or numEntries = 1).
\param [out] pA3DAsmModelFile The final reassembled model file.

\return \ref A3D_SUCCESS \n

\version 7.1
*/
A3D_API ( A3DStatus, A3DAsmModelFileLoadFromPRCFiles, (	const A3DUTF8Char* pcRootPrcFilePath,
														const A3DUns32 uNbFile,
														const A3DUTF8Char** ppPRCFilePath,
														const A3DUTF8Char** ppCADFilePath,
														const A3DRWParamsLoadData* pParamsLoadData,
														A3DAsmModelFile** pA3DAsmModelFile));


/*!
\ingroup a3d_write
\brief Creates a model file from multiple PRC files + an PRC assembly file + a map for file names.

This function replugs all the parts from a list from a PRC file loaded with an "assembly tree only" mode.

\param [in] pcFileName The file name of the top assembly file. Conceived for model file loaded as assembly tree only and saved as a PRC file.
\param [in] uNbPart The number of file names to plug.
\param [in] ppCADFilePath The native part file paths. Length must equal uNbPart.
\param [in] ppPRCFilePath The equivalent PRC file paths for parts. Length must equal uNbPart.
\param [in] pParamsLoadData The read/write parameters use the model file. Configurations must be set (default or numEntries = 1).
\param [out] pA3DAsmModelFile The final reassembled model file.

\return \ref A3D_SUCCESS \n

\version 5.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileLoadFromMultiplePrcFile, (
	const A3DUTF8Char* pcFileName,
	const A3DUns32 uNbPart,
	const A3DUTF8Char** ppCADFilePath,
	const A3DUTF8Char** ppPRCFilePath,
	const A3DRWParamsLoadData* pParamsLoadData,
	A3DAsmModelFile** pA3DAsmModelFile));



/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in a PRC format.

This function writes the \ref A3DAsmModelFile entity to a physical file. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [out] pcStream Buffer containing the PRC content.
\param [out] uLength Length of the pcStreambuffer.
\param [in,out] ppPrcWriteHelper Reserved for future use; must be set to NULL.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 4.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToPrcStream, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportPrcData* pParamsExportData,
	A3DUTF8Char*& pcStream,
	unsigned int& uLength,
	A3DRWParamsPrcWriteHelper** ppPrcWriteHelper));





/*!
\ingroup a3d_read
\brief Loads an \ref A3DAsmModelFile from a PRC Buffer

This function loads an \ref A3DAsmModelFile from a PRC Buffer.

\param [in] pcBufferStream Buffer containing the PRC stream.
\param [in] uBufferLength Length of pcBufferStream.
\param [in,out] ppPrcReadHelper Reserved for future use.
\param [out] ppModelFile References a pointer into which should be stored the location 
of the model file. Set this pointer to null before calling the function.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_LOAD_CANNOT_ACCESS_CADFILE \n
\return \ref A3D_LOAD_READER_NOT_IMPLEMENTED \n
\return \ref A3D_LOAD_CANNOT_LOAD_MODEL \n
\return \ref A3D_LOAD_CANNOT_LOAD_MULTIENTRY \n
\return \ref A3D_LOAD_EMPTY_MULTI_MODEL \n
\return \ref A3D_LOAD_MISSING_COMPONENTS \n
\return \ref A3D_LOAD_MULTI_MODELS_CADFILE if the file contains multiple entries (see A3DRWParamsMultiEntriesData). \n
\return \ref A3D_LOAD_INVALID_FILE_FORMAT \n
\return \ref A3D_SUCCESS \n

\version 5.2
*/


A3D_API (A3DStatus, A3DAsmModelFileLoadFromPrcStream,(
	const A3DUTF8Char* pcBufferStream,
	unsigned int uBufferLength,
	A3DRWParamsPrcReadHelper** ppPrcReadHelper,
	A3DAsmModelFile** ppModelFile));



/*!
\ingroup a3d_read
\brief Free PRC read helper.
\param [in,out] pA3DRWParamsPrcReadHelper The helper to free.
\version 8.1
*/
A3D_API(A3DVoid, A3DRWParamsPrcReadHelperFree, (A3DRWParamsPrcReadHelper* pA3DRWParamsPrcReadHelper));



/*!
\ingroup a3d_write
\brief Free PRC write helper.
\param [in,out] pA3DRWParamsPrcWriteHelper The helper to free.
\version 3.0
*/
A3D_API (A3DVoid, A3DRWParamsPrcWriteHelperFree,(A3DRWParamsPrcWriteHelper* pA3DRWParamsPrcWriteHelper));



/*!
\ingroup a3d_write
\brief STEP formats supported for export.
\version 3.0
*/
typedef enum
{
	kA3DStepAP203 = 0,	/*!< AP 203 Ed 2 since /version 9.1 */
	kA3DStepAP214,		/*!< AP 214. */
	kA3DStepAP242		/*!< AP 242. /version 9.1 */
} A3DEStepFormat;

/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to write the model file to a STEP format.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DEStepFormat m_eStepFormat;		/*!< Determines the STEP format. */
	A3DBool m_bSaveFacetedToWireframe;	/*!<
											Determines if entities are faceted or exported as wireframes. 
											\li A value of \c TRUE save polyedrics as wireframe.
											\li A value of \c FALSE save polyedrics as faces. */
	A3DBool m_bSaveAnalyticsToNurbs;	/*!<
											Determines the format for saving analytic surfaces, such as cylinders, cones, planes, and so forth. 
											\li A value of \c TRUE converts all analytics to NURBS surfaces. 
											\li A value of \c FALSE keeps analytics as analytics. */
	A3DBool m_bUseShortNames;			/*!< A value of \c TRUE shortens entity names to reduce the file size. */
	const A3DUTF8Char* m_pcApplication;	/*!< Application name (will be reported in the output file). */
	const A3DUTF8Char* m_pcVersion;		/*!< Application version (will be reported in the output file). */
	A3DBool m_bWritePMI;				/*!< Export or not PMI. Only available for AP242 /version 9.1 */
	A3DBool m_bWriteAttributes;			/*!< Export or not Attributes. Only available for AP242 /version 9.1 */
	A3DBool m_bWriteUVCurves;			/*!< Export PCURVE + 3D Curve on Brep /version 9.1 */
	const A3DUTF8Char* m_pcConfig;		/*!< Export only the configuration with this name /version 9.1 */
} A3DRWParamsExportStepData;

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in STEP format.

This function writes the \ref A3DAsmModelFile entity to a physical file.

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pcCADFileName References the path of the file into which the function stores the model file.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 3.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToStepFile, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportStepData* pParamsExportData,
	const A3DUTF8Char* pcCADFileName));


/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to write the model file to IGES format.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bSaveAnalyticsToNurbs;	/*!<
											Determines the format for saving analytic surfaces, such as cylinders, cones, planes, and so forth. 
											\li A value of \c TRUE converts all analytics to NURBS surfaces. 
											\li A value of \c FALSE keeps analytics as analytics. */
	A3DBool m_bSaveFacetedToWireframe;	/*!<
											Determines if entities are faceted or exported as wireframes. 
											\li A value of \c TRUE save polyedrics as wireframe.
											\li A value of \c FALSE save polyedrics as faces. */
	A3DBool m_bSaveSolidsAsFaces;		/*!<
											Specifies how solids are written.
											\li With a value of \c TRUE, solids are written as independent faces.
											\li With a value of \c FALSE, solid topology is kept. */
	A3DBool m_bWriteHiddenObjects;		/*!< A value of \c TRUE includes any hidden entities in the exported file. */
	A3DBool m_bWriteTessellation;		/*!< If \c TRUE tessellations will be converted to bodies. if \c FALSE tessellations will be ignored. */
	const A3DUTF8Char* m_pcApplication; /*!< Application name (will be reported in the output file). */
	const A3DUTF8Char* m_pcVersion;		/*!< Application version (will be reported in the output file). */
} A3DRWParamsExportIgesData;

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in IGES format.

This function writes the \ref A3DAsmModelFile entity to a physical file. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pcCADFileName References the path of the file into which the function stores the model file.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 3.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToIgesFile, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportIgesData* pParamsExportData,
	const A3DUTF8Char* pcCADFileName));


/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to write the model file to Parasolid format.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bSaveSolidsAsFaces;		/*!<
											Specifies how solids are written.
											\li With a value of \c TRUE, solids are written as independent faces.
											\li With a value of \c FALSE, solid topology is kept. */
	A3DBool m_bWriteTessellation;		/*!< If \c TRUE tessellations will be converted to bodies. If \c FALSE tessellations will be ignored. */
	A3DBool m_bWriteBlankedEntities;	/*!< Write blanked entities (hidden entities become visible). */
	const A3DUTF8Char* m_pcApplication;	/*!< Application name (will be reported in the output file). */
	const A3DUTF8Char* m_pcVersion;		/*!< Application version (will be reported in the output file). */
	A3DBool m_bBStrictAssemblyStructure;	/*!< Internal use only. */
	A3DBool m_bExplodeMultiBodies;		/*!< Explode multi-connexes B-reps into multiple bodies. /version 9.0 */
} A3DRWParamsExportParasolidData;

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in Parasolid format.

This function writes the \ref A3DAsmModelFile entity to a physical file. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pcCADFileName References the path of the file into which the function stores the model file.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 3.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToParasolidFile, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportParasolidData* pParamsExportData,
	const A3DUTF8Char* pcCADFileName));


/*!
\ingroup a3d_write
\brief A structure that contains chained buffers.
It is used to by:
\ref A3DAsmModelFileExportToParasolidBuffer \n
\ref A3DRepresentationItemExportToParasolidBuffer \n
\ref A3DAsmModelFileExportToAcisBuffer \n
\ref A3DRepresentationItemExportToAcisBuffer \n
\ref A3DChainedBufferFree \n
This structure can be used directly when loading a file from a buffer in Parasolid.

\version 4.0
*/
typedef struct A3DChainedBuffer
{
	A3DChainedBuffer*	m_pNext;
	size_t				m_sSize;
	const char*			m_pBuffer;
} A3DChainedBuffer;

/*!
\ingroup a3d_write
\brief This function is used to free memory allocated by following functions:
\ref A3DAsmModelFileExportToParasolidBuffer \n
\ref A3DRepresentationItemExportToParasolidBuffer \n
\ref A3DAsmModelFileExportToAcisBuffer \n
\ref A3DRepresentationItemExportToAcisBuffer \n
\ref A3DChainedBufferFree \n

\version 4.0
*/
A3D_API ( A3DStatus, A3DChainedBufferFree, (A3DChainedBuffer* pBuffer));


/*!
\ingroup a3d_write
\brief Writes a model file to a buffer in Parasolid format.

This function writes the \ref A3DAsmModelFile entity to a buffer. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [out] pBuffer References the chained buffer to be filled.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 4.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToParasolidBuffer, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportParasolidData* pParamsExportData,
	A3DChainedBuffer** pBuffer));


/*!
\ingroup a3d_write
\brief Writes a representation item to a file in Parasolid format.

This function writes the \ref A3DAsmModelFile entity to a file. 

\param [in] pRepItem References the \ref A3DRiRepresentationItem to be written out.
\param [in,out] pcTempFileName References the output file to be written.
\param [in] dUnit References the wanted unit for the RI.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 4.0
*/
A3D_API ( A3DStatus, A3DRepresentationItemExportToParasolidFile, (
	const A3DRiRepresentationItem* pRepItem,
	const A3DUTF8Char* pcTempFileName,
	A3DDouble dUnit));


/*!
\ingroup a3d_write
\brief Writes a representation item to a buffer in Parasolid format.

This function writes the \ref A3DRiRepresentationItem entity to a buffer. 

\param [in] pRepItem References the \ref A3DRiRepresentationItem to be written out.
\param [in] pBuffer References the chained buffer to be filled.
\param [in] dUnit References the wanted unit for the RI.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 4.0
*/
A3D_API (A3DStatus, A3DRepresentationItemExportToParasolidBuffer, (const A3DRiRepresentationItem* pRepItem,
																						 A3DChainedBuffer** pBuffer,
																						 double dUnit));




/*!
\ingroup a3d_write
\brief Control mode of the healing in TranslateToPkParts functions. Used in \ref A3DRWParamsTranslateToPkPartsData.
\version 8.1
*/
typedef enum
{
	kA3DE_HEALING_NO,						/*!< Disable healing. */
	kA3DE_HEALING_YES,						/*!< Enable healing. */
	kA3DE_HEALING_ONLY_IF_NOT_PARASOLID,	/*!< Enable healing only for data coming from neither Parasolid nor from any format that embeds Parasolid data (NX, SolidWorks, Solid Edge and JT) but only if the \ref A3DRWParamsParasolidData::m_bKeepParsedEntities reading option is enabled. */
} A3DETranslateToPkPartsHealing;

/*!
\ingroup a3d_write
\brief Control mode of the accurate edge computation in TranslateToPkParts functions. Used in \ref A3DRWParamsTranslateToPkPartsData.
\version 8.1
*/
typedef enum
{
	kA3DE_ACCURATE_NO,						/*!< Disable accurate edge computation. */
	kA3DE_ACCURATE_YES,						/*!< Enable accurate edge computation. */
	kA3DE_ACCURATE_ONLY_IF_NOT_PARASOLID	/*!< Enable accurate edge computation only for data coming from neither Parasolid nor from any format that embeds Parasolid data (NX, SolidWorks, Solid Edge and JT) but only if the \ref A3DRWParamsParasolidData::m_bKeepParsedEntities reading option is enabled. */
} A3DETranslateToPkPartsAccurate;

/*!
\ingroup a3d_write
\brief Control mode of the healing in TranslateToPkParts functions. Used in \ref A3DRWParamsTranslateToPkPartsData.
\version 8.1
*/
typedef enum
{
	kA3DE_SIMPLIFY_NO,						/*!< Disable healing. */
	kA3DE_SIMPLIFY_YES,						/*!< Enable healing. */
	kA3DE_SIMPLIFY_ONLY_IF_NOT_PARASOLID,	/*!< Enable healing only for data coming from neither Parasolid nor from any format that embeds Parasolid data (NX, SolidWorks, Solid Edge and JT) but only if the \ref A3DRWParamsParasolidData::m_bKeepParsedEntities reading option is enabled. */
} A3DETranslateToPkPartsSimplifyGeometry;

/*!
\ingroup a3d_write
\brief Control mode of the accurate edge computation in TranslateToPkParts functions. Used in \ref A3DRWParamsTranslateToPkPartsData.
\version 8.1
*/
typedef enum
{
	kA3DE_MERGE_NO,							/*!< Disable accurate edge computation. */
	kA3DE_MERGE_YES,						/*!< Enable accurate edge computation. */
	kA3DE_MERGE_ONLY_IF_NOT_PARASOLID,		/*!< Enable accurate edge computation only for data coming from neither Parasolid nor from any format that embeds Parasolid data (NX, SolidWorks, Solid Edge and JT) but only if the \ref A3DRWParamsParasolidData::m_bKeepParsedEntities reading option is enabled. */
} A3DETranslateToPkPartsMergeEntities;

/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to translate the model file or a representation item into an open Parasolid session.
\version 8.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;										/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DETranslateToPkPartsHealing m_eHealing;						/*!< Enum to control healing */
	A3DETranslateToPkPartsAccurate m_eComputeAccurateEdges;			/*!< Enum to control accurate edge computation. */
	A3DBool m_bDisjoinIfFaceFaceError;								/*!< If \c TRUE bodies with face_face error will be disjoined. */
	A3DBool m_bSew;													/*!< Sew the geometry. */
	A3DDouble m_dSewingTolerance;									/*!< Enables the sewing tolerance in meters. */
	A3DETranslateToPkPartsSimplifyGeometry m_eSimplifyGeometry;		/*!< Simplify geometry and topology. */
	A3DETranslateToPkPartsMergeEntities m_eMergeEntities;			/*!< Merge: remove redundant entities (edges/surfaces). */
	const A3DUTF8Char* m_pcPSBodyShopPath;							/*!< Path to PSBodyshop DLL. Necessary for simplify and merge options. */
	A3DMiscPKMapper** m_pMapper;									/*!< Mapper. /version 9.0 */
	A3DBool m_bUseColour2Attribute;									/*!< Use SDL/TYSA_COLOUR_2 Parasolid attribute. /version 9.1 */
	A3DBool m_bUseUTF8ForNameAttribute;								/*!< Use SDL/TYSA_UNAME Parasolid attribute. /version 9.1 */
	A3DBool m_bUseLayerAttribute;									/*!< Use SDL/TYSA_LAYER Parasolid attribute. /version 9.1 */
} A3DRWParamsTranslateToPkPartsData;

/*!
\ingroup a3d_write
\brief Writes a model file to parts in the current Parasolid session.

This function writes the \ref A3DAsmModelFile entity to parts in the current Parasolid session. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pParamsTranslateToPkPartsData References the parameters to export in the Parasolid session. \version 8.1
\param [out] pNbPkParts References the number of resulting parts.
\param [out] pPkParts References the array of resulting parts.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 8.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileTranslateToPkParts, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportParasolidData* pParamsExportData,
	const A3DRWParamsTranslateToPkPartsData* pParamsTranslateToPkPartsData,
	int* pNbPkParts,
	int** pPkParts));

/*!
\ingroup a3d_write
\brief Writes a representation item to parts in the current Parasolid session.

This function writes the \ref A3DRiRepresentationItem entity to parts in the current Parasolid session. 

\param [in] pRepItem References the \ref A3DRiRepresentationItem to be written out.
\param [in] pParamsTranslateToPkPartsData References the parameters to export in the Parasolid session. \version 8.1
\param [in] dUnit References the wanted unit for the RI.
\param [out] pNbPkParts References the number of resulting parts.
\param [out] pPkParts References the array of resulting parts.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 8.0
*/
A3D_API (A3DStatus, A3DRepresentationItemTranslateToPkParts, (
	const A3DRiRepresentationItem* pRepItem,
	const A3DRWParamsTranslateToPkPartsData* pParamsTranslateToPkPartsData,
	double dUnit,
	int* pNbPkParts,
	int** pPkParts));

/*!
\ingroup a3d_write
\brief Heal parts in the current Parasolid session.


\param [in] pNbPkParts References the number of resulting parts.
\param [in,out] pPkParts References the array of resulting parts.
\param [in] pParamsTranslateToPkPartsData References the parameters to export in the Parasolid session. \version 8.1

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_SUCCESS \n

\version 9.1
*/
A3D_API(A3DStatus, A3DHealPkParts, (
	int* pNbPkParts,
	int** pPkParts,
	const A3DRWParamsTranslateToPkPartsData* pParamsTranslateToPkPartsData));

/*!
\ingroup a3d_write
\brief Get Parasolid entities from HOOPS Exchange entity

\param [in] pMapper The mapper
\param [in] pA3DEntity The HOOPS Exchange entity
\param [out] piNbPKEntities Number of Parasolid entities in the following array
\param [out] ppPKEntities Array of Parasolid entities

\return \ref A3D_SUCCESS \n

\version 9.0
*/
A3D_API (A3DStatus, A3DMiscPKMapperGetPKEntitiesFromA3DEntity, (
	const A3DMiscPKMapper * pMapper,
	const A3DEntity* pA3DEntity,
	int* piNbPKEntities,
	int** ppPKEntities));

/*!
\ingroup a3d_write
\brief Get HOOPS Exchange entities from Parasolid entity

\param [in] pMapper The mapper
\param [in] pPKEntity The Parasolid entity
\param [out] piNbA3DEntities Number of HOOPS Exchange entities in the following array
\param [out] ppA3DEntities Array of HOOPS Exchange entities

\return \ref A3D_SUCCESS \n

\version 9.0
*/
A3D_API(A3DStatus, A3DMiscPKMapperGetA3DEntitiesFromPKEntity, (
	const A3DMiscPKMapper * pMapper,
	int pPKEntity,
	int* piNbA3DEntities,
	A3DEntity*** ppA3DEntities));

/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to write the model file to STL format.
\version 3.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bBinaryFile;					/*!< With a value of \c TRUE, compresses the STL file to reduce file size. */
	A3DETessellationLevelOfDetail m_eTessellationLevelOfDetail;	/*!< Enum to specify predefined values for some following members. */
	A3DDouble m_dChordHeightRatio;			/*!<
												Specifies the percentage of bounding box used to compute chord height. 
												Set a value from 50 through 10,000. */
	A3DDouble m_dAngleToleranceDeg;			/*!<
												Specifies the maximum angle between two contiguous segments of wire edges for every face. 
												The value must be from 10 through 40. */
	A3DDouble m_dMinimalTriangleAngleDeg;	/*!<
												Specifies the angle between two contiguous segments of wire edges for every face. 
												Allowable values range from 10 through 30. */
	A3DDouble m_dMaxChordHeight;			/*!< Specifies the maximum distance between surface and tessellation. Be careful, a too small value can generate a huge tessellation. */
	A3DBool m_bAccurateTessellation;		/*!< With a value of \c TRUE, tessellates the STL file with equilateral triangles. */
	A3DBool m_bKeepCurrentTessellation;		/*!< With a value of \c TRUE, keeps the current tessellation. */
	A3DBool m_bUseHeightInsteadOfRatio;		/*!< Use \ref m_dMaxChordHeight instead of \ref m_dChordHeightRatio if \ref m_eTessellationLevelOfDetail = \ref kA3DTessLODUserDefined. */
	A3DDouble m_dMaximalTriangleEdgeLength;	/*!< Maximal length of the edges of triangles. Disabled if value is 0. Be careful, a too small value can generate a huge tessellation. */
} A3DRWParamsExportStlData;

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in STL format.

This function writes the \ref A3DAsmModelFile entity to a physical file. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pcCADFileName References the path of the file into which the function stores the model file.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 3.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToStlFile, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportStlData* pParamsExportData,
	const A3DUTF8Char* pcCADFileName));

/*!
\ingroup a3d_write
\brief U3D formats supported for export.
\version 4.0
*/

typedef enum
{
	kA3DECMA1,		/*!< ECMA-363, version 1 writing. (Acrobat Reader 7.0 compatible). */ 
	kA3DECMA3		/*!< ECMA-363, version 3 writing. */
} A3DEU3DVersion;


/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to write the model file to U3D format.
\version 4.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DEU3DVersion m_eU3DVersion;			/*!< Output type. */
	A3DBool m_bMeshQuality;					/*!< Are tessellations to be compressed? */
	A3DUns8 m_ucMeshQualityValue;			/*!< Level of compression [0, 100]. */
} A3DRWParamsExportU3DData;

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in Universal 3D format.

This function writes the \ref A3DAsmModelFile entity to a physical file. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pcCADFileName References the path of the file into which the function stores the model file.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 4.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToU3DFile, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportU3DData* pParamsExportData,
	const A3DUTF8Char* pcCADFileName));

/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to write the model file to JT format.
\version 6.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DEWriteGeomTessMode m_eWriteGeomTessMode;	/*!< Enum to set the content to write (Geometry and/or Tessellation). */
	A3DBool m_bWriteHiddenObjects;				/*!< Export or not hidden objects. */
	A3DBool m_bWritePMI;						/*!< Export or not PMI. */
} A3DRWParamsExportJTData;

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in JT format.

This function writes the \ref A3DAsmModelFile entity to a physical file. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pcCADFileName References the path of the file into which the function stores the model file.

\return \ref A3D_SUCCESS \n

\version 6.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToJTFile, (
		 const A3DAsmModelFile* pA3DAsmModelFile,
		 const A3DRWParamsExportJTData* pParamsExportData,
		 const A3DUTF8Char* pcCADFileName));


/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to write the model file to ACIS format.
\version 4.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bSaveAsMillimeter;				/*!< Save data in millimeter instead of current model unit. */
	A3DBool m_bSaveAsBinary;					/*!< Save in binary file (.sab). */
} A3DRWParamsExportAcisData;

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in ACIS format.

This function writes the \ref A3DAsmModelFile entity to a physical file. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pcCADFileName References the path of the file into which the function stores the model file.

\return \ref A3D_INVALID_LICENSE \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 5.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToAcisFile, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportAcisData* pParamsExportData,
	const A3DUTF8Char* pcCADFileName));

/*!
\ingroup a3d_write
\brief Writes a model file to a buffer in binary ACIS format.

This function writes the \ref A3DAsmModelFile entity to a buffer. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pBuffer Buffer.

\return \ref A3D_INVALID_LICENSE \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 5.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToAcisBuffer, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportAcisData* pParamsExportData,
	A3DChainedBuffer** pBuffer));

/*!
\ingroup a3d_write
\brief Writes a representation item to a buffer in binary ACIS format.

This function writes the \ref A3DRiRepresentationItem entity to a buffer.

\param [in] pRepItem References the \ref A3DRiRepresentationItem to be written out.
\param [in] pBuffer Buffer.
\param [in] dScale Scale applied to the representation item.

\return \ref A3D_INVALID_LICENSE \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 7.2
*/
A3D_API (A3DStatus, A3DRepresentationItemExportToAcisBuffer, (
	const A3DRiRepresentationItem* pRepItem,
	A3DChainedBuffer** pBuffer,
	double dScale));

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in VRML format.

This function writes the \ref A3DAsmModelFile entity to a physical file. 

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pcCADFileName References the path of the file into which the function stores the model file.

\return \ref A3D_INVALID_LICENSE \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n

\version 6.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToVrmlFile, (
		 const A3DAsmModelFile* pA3DAsmModelFile,
		 const A3DUTF8Char* pcCADFileName));



/*!
\ingroup a3d_write
\brief A structure that specifies parameters used to write the model file to XML format
\version 7.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	bool m_bExportMetadata;						/*!< Set to true to export metadata to XML. */
	bool m_bExportTransformations;				/*!< Set to true to export transformations to XML. */
	bool m_bExportColorMaterial;				/*!< Set to true to export material and color tables to XML. */
	bool m_bExportProductInformationByFormat;	/*!< Set to true to export Product information specific to format to XML. */
} A3DRWParamsExportXMLData;

/*!
\ingroup a3d_write
\brief Writes a model file to a physical file in XML format

This function writes the \ref A3DAsmModelFile entity to a physical file,
and fills two arrays of size uMapSize (puMapXmlId and ppMapProductOccurrences)
that will act as a map of the product occurrences and their respective IDs in the XML file.

\param [in] pA3DAsmModelFile References the \ref A3DAsmModelFile to be written out.
\param [in] pParamsExportData References the parameters for export.
\param [in] pcXMLFileName References the path of the file into which the function stores the model file.
\param [out] uMapSize Size of the two following arrays. If set to NULL, the map construction is bypassed.
\param [out] puMapXmlIds Array of the product occurrence IDs in the XML file. If set to NULL, the map construction is bypassed. It has to be freed with the custom free memory callback.
\param [out] ppMapProductOccurrences Array of the product occurrences in the XML file. If set to NULL, the map construction is bypassed. It has to be freed with the custom free memory callback.

\return \ref A3D_INVALID_LICENSE \n
\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_WRITE_INVALID_FILE_NAME \n
\return \ref A3D_WRITE_ERROR \n
\return \ref A3D_WRITE_CANNOT_LOAD_WRITER \n
\return \ref A3D_SUCCESS \n
\version 7.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileExportToXMLFile, (
	const A3DAsmModelFile* pA3DAsmModelFile,
	const A3DRWParamsExportXMLData* pParamsExportData,
	const A3DUTF8Char* pcXMLFileName, 
	unsigned int* uMapSize,
	unsigned int** puMapXmlIds,
	A3DEntity*** ppMapProductOccurrences));



/*!
\ingroup a3d_read
\brief Loads an \ref A3DAsmModelFile from a XML file and a set of native cad files.

This function loads an \ref A3DAsmModelFile from a XML file and a set of native cad files.

\param [in] pcFileName References the path to the file containing the XML description of the assembly.
\param [in] pLoadParametersData References the parameters for reading the native parts.
\param [out] ppModelFile References a pointer into which should be stored the location 
of the model file. Set this pointer to null before calling the function.

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_LOAD_CANNOT_ACCESS_CADFILE \n
\return \ref A3D_LOAD_READER_NOT_IMPLEMENTED \n
\return \ref A3D_LOAD_CANNOT_LOAD_MODEL \n
\return \ref A3D_LOAD_CANNOT_LOAD_MULTIENTRY \n
\return \ref A3D_LOAD_EMPTY_MULTI_MODEL \n
\return \ref A3D_LOAD_MISSING_COMPONENTS \n
\return \ref A3D_LOAD_MULTI_MODELS_CADFILE if the file contains multiple entries (see A3DRWParamsMultiEntriesData). \n
\return \ref A3D_LOAD_INVALID_FILE_FORMAT \n
\return \ref A3D_SUCCESS \n

\version 7.0
*/
A3D_API ( A3DStatus, A3DAsmModelFileLoadFromXMLFile, (
	const A3DUTF8Char* pcFileName,
	const A3DRWParamsLoadData* pLoadParametersData,
	A3DAsmModelFile** ppModelFile));


#endif	/*	__A3D_RW_WRITE__ */
#endif	/*	__A3DPRCREADWRITE_H__ */
