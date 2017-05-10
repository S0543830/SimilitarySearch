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

/*!
\addtogroup a3d_publish_modelfile_loadexport Model File Load-Export Module
\ingroup a3d_entitiesdata_module
\brief Methods and structures dedicated to 3D data reading and writing capabilities

This module describes the functions and structures that allow you to read and write 3D model files. 
*/


typedef void A3DAsmProductOccurrence; /* Not used in Publish Lite */

#ifndef __A3D_RW_READ__
/*!
\defgroup a3d_read Load Module
\ingroup a3d_publish_modelfile_loadexport
\brief Loads the model file with information from the input CAD file.

Please refer to \REF_SUPPORTED_FORMATS documentation for list of available formats. 
*/

#ifndef WIN32
	#include <stdlib.h>
#endif

/*!
\ingroup a3d_read
\brief ReadingMode of the model file. Sets which kind of content should be read.
\version 3.0
*/
typedef enum
{
	kA3DReadGeomOnly = 0,	/*!< Read only geometry. */
	kA3DReadGeomAndTess,	/*!< Mixed mode: read geometry and tessellation. */
	kA3DReadTessOnly		/*!< Read only tessellation. */
} A3DEReadGeomTessMode;

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
	A3DProEFamTabOrUseTessellation = 1,		/*!< If the accelerator file isn't present then we search for the tessellation representation: if found and we use it*/
	A3DProEFamTabOrUseWireAndGeneric = 2	/*!< If none of the accelerator file or the tessellation representation is present so we use the generic or wire representation: be aware that the representation will not be what the configuration should be! it's like a placebo in order to have something*/
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
	A3DBool m_bComputeValidationProperties;/*!< requires to have m_bReadValidationProperties=true */
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
\ingroup a3d_read
\brief Loads an \ref A3DAsmModelFile from a PRC Buffer.

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



/*!
\ingroup a3d_read
\brief Free PRC read helper.
\param [in,out] pA3DRWParamsPrcReadHelper The helper to free.
\version 8.1
*/
A3D_API(A3DVoid, A3DRWParamsPrcReadHelperFree, (A3DRWParamsPrcReadHelper* pA3DRWParamsPrcReadHelper));



#endif	/*	__A3D_RW_READ__ */


#ifndef __A3D_RW_WRITE__
/*!
\defgroup a3d_write Export Module
\ingroup a3d_publish_modelfile_loadexport
\brief Structures to write the ModelFile defined through this API in a 3D Annot.

Supported formats are PRC and U3D.
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
\brief Free PRC write helper.
\param [in,out] pA3DRWParamsPrcWriteHelper The helper to free.
\version 3.0
*/
A3D_API(A3DVoid, A3DRWParamsPrcWriteHelperFree, (A3DRWParamsPrcWriteHelper* pA3DRWParamsPrcWriteHelper));



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



#endif	/*	__A3D_RW_WRITE__ */

#endif	/*	__A3DPRCREADWRITE_H__ */
