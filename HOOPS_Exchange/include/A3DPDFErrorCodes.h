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
\brief      Header file for the error codes module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.

As a general rule, every negative value for return codes <b>must be handled as an
error</b>, and not simply passed by. When possible, a brief explanation on every 
case has been provided. 

*/

#ifndef __A3DPDFERRORCODES_H__
#define __A3DPDFERRORCODES_H__



/*******************************************************************************
********************************************************************************
* 
*  ERROR CODES
* 
********************************************************************************
*******************************************************************************/

/*!
\brief Error Codes
*/
typedef enum
{
/*******************************************************************************
* 
*  GENERAL ERROR CODES
* 
*******************************************************************************/

	A3D_SUCCESS											=	0,		/*!< Successful return value. */
	A3D_ERROR											=	-1,		/*!< General error. */
	A3D_EXCEPTION										=	-2,		/*!< Caught exception. */
	A3D_ALLOC_FATAL_ERROR								=	-10,	/*!< Allocation has failed. Major error. */
	A3D_NOT_IMPLEMENTED									=	-33,	/*!< Local code, which is not yet implemented. */
	A3D_INVALID_LICENSE									=	-34,	/*!< License option doesn't allowed the requested function. */

/*******************************************************************************
*
*  MACROS ERROR CODES
*
*******************************************************************************/

	A3D_INVALID_DATA_STRUCT_SIZE						=	-100,	/*!< \ref A3D_INITIALIZE_DATA not called or bad alignment in input struct. */
	A3D_INVALID_DATA_STRUCT_NULL						=	-101,	/*!< Input struct function cannot be NULL. */
	A3D_INVALID_ENTITY_NULL								=	-102,	/*!< Input entity function cannot be NULL. */
	A3D_INVALID_ENTITY_TYPE								=	-103,	/*!< Input entity function is of bad type. */
	A3D_INVALID_DATA									=	-104,	/*!< Input contains bad data. */


/*******************************************************************************
* 
*  BASE ERROR CODES
* 
*******************************************************************************/

	A3D_INITIALIZE_ALREADY_CALLED						=	-200,	/*!< \ref A3DDllInitialize already called; bad sequence with the \ref A3DDllTerminate function. */
	A3D_INITIALIZE_NOT_CALLED							=	-201,	/*!< \ref A3DDllInitialize must be called before calling the \ref A3DDllTerminate function. */
	A3D_INITIALIZE_BAD_VALUES							=	-202,	/*!< Initialization led to bad internal values for globals. Fatal error. Reinitialize program. */
	A3D_INITIALIZE_CANNOT_PROCESS						=	-205,	/*!< Cannot initialize library. */

/*******************************************************************************
* 
*  LOADING CAD FILES ERROR CODES
* 
*******************************************************************************/

	A3D_LOAD_INVALID_FILE_NAME							=	-10000,	/*!< Input file does not correspond to a valid file name. */
	A3D_LOAD_MULTI_MODELS_CADFILE						=	-10001,	/*!< Input CAD file correspond to a multi model file. */
	A3D_LOAD_CANNOT_ACCESS_CADFILE						=	-10002,	/*!< Cannot access input CAD file. */
	A3D_LOAD_CANNOT_READ_SETTINGS						=	-10003,	/*!< Cannot access CAD reading settings file. */
	A3D_LOAD_MISSING_COMPONENTS							=	-10004,	/*!< One or several components are missing. */
	A3D_LOAD_INVALID_FILE_FORMAT						=	-10005,	/*!< Input file seems invalid. */
	A3D_LOAD_READER_NOT_IMPLEMENTED						=	-10006,	/*!< The reader is not implemented. */
	A3D_LOAD_CANNOT_LOAD_MODEL							=	-10007,	/*!< An error occurred during parsing. */
	A3D_LOAD_CANNOT_LOAD_MULTIENTRY						=	-10008,	/*!< Cannot load multi-entry file. */
	A3D_LOAD_EMPTY_MULTI_MODEL							=	-10009,	/*!< Empty model. */
	A3D_LOAD_INVALID_READER_FOR_INCREMENTAL_LOAD		=	-10010,	/*!< Invalid reader for incremental load. */
	A3D_LOAD_INVALID_PARAMETERS_FOR_INCREMENTAL_LOAD	=	-10011,	/*!< Invalid parameters for incremental load. */
	
/*******************************************************************************
* 
*  LOADING PRC ERROR CODES
* 
*******************************************************************************/

	A3D_LOADPRC_INITIALIZATION_FAILURE					=	-10300,	/*!< Cannot initialize reading context. */
	A3D_LOADPRC_CANNOT_OPEN_FILE						=	-10301,	/*!< Cannot open file. */
	A3D_LOADPRC_READING_ERROR							=	-10302,	/*!< Internal reading error. */
	A3D_LOADPRC_BUILD_ERROR								=	-10303,	/*!< Internal reading error - Invalid PRC file. */
	A3D_LOADPRC_PDFLINIT_ERROR							=	-10304,	/*!< Error while initializing PDFL. */
	A3D_LOADPRC_INVALID_ANNOT_INDEX						=	-10305,	/*!< Input annotation index is invalid. */
	A3D_LOADPRC_INVALID_ANNOT							=	-10306,	/*!< Input annotation is invalid. */
	A3D_LOADPRC_EMPTY_FILE								=	-10307,	/*!< Input file is empty. */
	A3D_LOADPRC_NO_3D									=	-10308,	/*!< Input file does not contain any 3D Annot. */

/*******************************************************************************
* 
*  WRITING ERROR CODES
* 
*******************************************************************************/

	A3D_WRITE_ERROR										=	-10400,	/*!< Error while writing export file. */
	A3D_WRITE_CANNOT_LOAD_WRITER						=	-10401,	/*!< Cannot load writer. */
	A3D_WRITE_WRITER_NOT_IMPLEMENTED					=	-10402,	/*!< The writer is not implemented. */
	A3D_WRITE_INVALID_FILE_NAME							=	-10403,	/*!< Input file does not correspond to a valid file name. */
	A3D_WRITE_INVALID_INPUT								=	-10404,	/*!< Input file does not correspond to a valid file name. */

/*******************************************************************************
* 
*  CALLBACK FUNCTIONS ERROR CODES
* 
*******************************************************************************/

	A3D_CALLBACK_MEMORY_FUNCTIONS_ALREADY_SET			=	-900000,	/*!< \ref A3DDllSetCallbacksMemory can be called only once per session. */
	A3D_CALLBACK_INVALID_BREAK_VALUE					=	-900001,	/*!< \ref A3DDllSetCallbacksProgress : lBreak must be a valid pointer (not NULL). */
	A3D_CALLBACK_CONTINUE								=	-900002,	/*!< \ref A3DDllSetCallbacksProgress : lBreak must be a valid pointer (not NULL). */

/*******************************************************************************
* 
*  PDF PUBLISH FUNCTIONS ERROR CODES
* 
*******************************************************************************/

	A3DPDF_PDFLIB_ERROR									=	-1000000,	/*!< Unexpected PDFLib Error. */
	A3DPDF_ONLY_ONE_PAGE_AUTHORIZED						=	-1000001,	/*!< \ref A3DPDFDocumentCreateUniquePage can be called only on an empty document. */
	A3DPDF_3D_ANNOT_REQUIRED							=	-1000002,	/*!< Cannot call \ref A3DPDFDocumentSave without a 3D Annot in the document. */
	A3DPDF_ERR_AFTER_SAVE								=	-1000003,	/*!< \ref A3DPDFDocumentSave : document has not been saved properly. */
	A3DPDF_OPT_NOT_PERMITTED							=	-1000004,	/*!< \ref A3DPDFDocumentSave : invalid options. */
	A3DPDF_FILE_ALREADY_OPEN							=	-1000005,	/*!< \ref A3DPDFDocumentSave : file is already opened in another application. */
	A3DPDF_FILE_LOCKED									=	-1000006,	/*!< \ref A3DPDFDocumentSave : file is locked by another application. */
	A3DPDF_BAD_FONT_PARAMETERS							=	-1000007,	/*!< \ref A3DPDFPageInsertText : bad font parameters. */
	A3DPDF_BAD_PARAMETERS								=	-1000008,	/*!< Bad parameters. */
	A3DPDF_CANNOT_ACCESS_FILE							=	-1000009,	/*!< Cannot access file. */
	A3DPDF_UNKNOWN_FIELD								=	-1000010,	/*!< Cannot find the specified field in the document. */
	A3DPDF_DEFAULT_VIEW_ERROR							=	-1000011,	/*!< Cannot find a default view in 3D Annot. */
	A3DPDF_INVALID_DIMENSIONS							=	-1000014,	/*!< Width and height must be >0 and <=682. */
	A3DPDF_MEMORY_ERROR									=	-1000015,	/*!< Not enough memory. */
	A3DPDF_CANNOT_FIND_FONT								=	-1000016,	/*!< Cannot find the specified font. */
	A3DPDF_CANNOT_CREATE_ENCODING						=	-1000017,	/*!< Cannot create the specified encoding. */
	A3DPDF_CANNOT_CREATE_FONT							=	-1000018,	/*!< Cannot create the specified font. */
	A3DPDF_CANNOT_CONVERT_PICTURE						=	-1000019,	/*!< Cannot convert the specified picture. */
	A3DPDF_CANNOT_SNAPSHOT_VIEW_WITHOUT_CAMERA			=	-1000020,	/*!< In a PRC/PDF file, there is a view without a camera; snapshots cannot be created from such views. */
	A3DPDF_CANNOT_LOAD_TABLETOPDF_DLL					=	-1000021,	/*!< tabletopdf.dll or one of its components is missing from your directory. */
	A3DPDF_HTML_TABLE_ERROR								=	-1000022,	/*!< Wrong HTML format for table entry. */
	A3DPDF_HTML_STYLE_ERROR								=	-1000023,	/*!< Wrong HTML format for style entry. */
	A3DPDF_CANNOT_INITIALIZE_RESOURCES					=	-1000024,	/*!< Resource directory could not be initialized. Please check you used \ref A3DPDFInitializePDFLibAndResourceDirectory with a correct path. */
	A3DPDF_INVALID_PAGE_INDEX							=	-1000025,	/*!< Input page index is invalid or not in pages bounds. */
	A3DPDF_CANNOT_GENERATE_IMAGE_FROM_VIEW				=	-1000026,	/*!< Error while generating the images for the buttons in the view carousel. */
	A3DPDF_ANIMATION_NULL_MOTION						=	-1000027,	/*!< At least one motion is null, the animation can't be created. */
	A3DPDF_SLIDETABLE_NBCOLUMNS_ERROR					=	-1000028,	/*!< The number of columns in the table frame is different than the number of columns in text data. */
	A3DPDF_SLIDETABLE_TEXTDATA_ERROR					=	-1000029,	/*!< Error in text data (ppTexts argument). */
	A3DPDF_CANNOT_LOAD_PDFLIB_DLL						=	-1000030,	/*!< pdflib DLL or one of its components is missing. */
	A3DPDF_CANNOT_LOAD_IMAGEMAGICK_DLL					=	-1000031,	/*!< ImageMagick DLL or one of its components is missing. */
	A3DPDF_NO_3D_ON_PAGE								=	-1000032,	/*!< Error retrieving 3D data on page. No annot was found. */
	A3DPDF_3D_NOTFOUND_ON_PAGE							=	-1000033,	/*!< Error retrieving 3D data on page. No 3D annot was found. */
	A3DPDF_CANNOT_READSTREAM							=	-1000035,	/*!< Error reading text stream. */
	A3DPDF_CANNOT_CONVERTSTREAM							=	-1000036,	/*!< Encoding error converting text stream. */
	A3DPDF_SLIDETABLE_SLIDER_ERROR						=	-1000037,	/*!< Error in slider creation */
	A3DPDF_SLIDETABLE_TEXT_FIELD_ERROR					=	-1000038,	/*!< Error in slider creation */
	A3DPDF_SLIDETABLE_NOT_EXIST							=	-1000039,	/*!< The slidetable object could not be found */
	A3DPDF_CAROUSEL_NOT_EXIST							=	-1000040,	/*!< The carousel object could not be found */
} A3DStatus;


#endif	/*	__A3DPDFERRORCODES_H__ */
