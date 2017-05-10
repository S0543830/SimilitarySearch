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
\brief      Header file for the Publish module
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPDFPUBLISHSDK_H__
#define __A3DPDFPUBLISHSDK_H__



/*!
\addtogroup a3d_publishpdf_module PDF Module
\brief Publish 3D content in a PDF file

This module describes the functions and structures that allow you to publish 3D model files. 
*/


/*!
\defgroup a3d_publish_types_def PDF Entities Type Definitions
\ingroup a3d_types_def
\version 4.1

@{
*/
typedef void A3DPDFDocument;		/*!< PDF document entity. */
typedef void A3DPDFPage;			/*!< PDF page entity. */
typedef void A3DPDF3DAnnot;			/*!< PDF 3D Annotation entity. */
typedef void A3DPDF3DStream;		/*!< PDF 3D Stream entity. */
typedef void A3DPDF3DArtwork;		/*!< PDF 3D Artwork entity. */
typedef void A3DPDFText;			/*!< PDF text entity. */
typedef void A3DPDFImage;			/*!< PDF image entity. */
typedef void A3DPDFLink;			/*!< PDF link entity. */
typedef void A3DPDFView;			/*!< PDF 3D View entity. */
typedef void A3DPDFTable;			/*!< PDF table entity. */
typedef void A3DPDFField;			/*!< PDF field entity. */
typedef void A3DPDFAnimKeyFrame;	/*!< PDF key frame entity. */
typedef void A3DPDFAnimMotion;		/*!< PDF animation motion entity. */
typedef void A3DPDFAnimation;		/*!< PDF animation entity. */
typedef void A3DPDFTargetEntity;	/*!< PDF animation target entity. */
typedef void A3DPDFButton;			/*!< PDF button entity. */
typedef void A3DPDFTextField;		/*!< PDF Text Field. */
typedef void A3DPDFCheckBox;		/*!< PDF check box field. */
typedef void A3DPDFRadioButton;		/*!< PDF radio button field. */
typedef void A3DPDFListBox;			/*!< PDF listbox field. */
typedef void A3DPDFDropDownList;	/*!< PDF drop down list field. */
typedef void A3DPDFDigitalSignature;/*!< PDF digital signature field. */
typedef void A3DPDFGraphicLine;		/*!< PDF graphic line. */
/*!
@} <!-- end of a3d_publish_types_def -->
*/


/*!
\ingroup a3d_publishpdf_module
\brief A3DPDFRgbColorData structure

A color is defined in RGB color space. Red, Green, and Blue values vary from 0.0 to 1.0.
A value of (0.0, 0.0, 0.0) is for black. (1.0, 1.0, 1.0) is for white. 
\version 4.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dRed;			/*!< [0..1] Red value. */
	A3DDouble m_dGreen;			/*!< [0..1] Green value. */
	A3DDouble m_dBlue;			/*!< [0..1] Blue value. */
} A3DPDFRgbColorData;



/*!
\addtogroup a3d_pdflib_functions \PDF_LIBRARY Start/Terminate Functions
\ingroup a3d_base_module
\brief Starts, configures, and terminates a session with the \PDF_LIBRARY.

The functions in this section start and terminate a session with the \PDF_LIBRARY. 
WARNING: the initialization and termination functions must be called only once during the life of the application. 
Attempting to initialize the \PDF_LIBRARY more than once in the application may cause errors or unpredictable behavior, 
and is not supported. You are free to create multiple documents and/or multiple files within the run, but the initialization 
and termination of the \PDF_LIBRARY is limited to one iteration of each.
*/

/*!
\ingroup a3d_pdflib_functions
\brief This method was deprecated in HOOPS Publish 5.1. Use \ref A3DPDFInitializePDFLibAndResourceDirectory instead.

This function initializes the Adobe PDF Library which is internally used by HOOPS Publish.
It should be called before calling any function working on the PDF document, and only once during the life of the application. 
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFInitializePDFLib, ());

/*!
\ingroup a3d_pdflib_functions
\brief Function to initialize the PDF Library and set the resource directory

This function initializes the Adobe PDF Library which is internally used by HOOPS Publish, and indicates where
the resource directory is located. The resource directory is used by the Adobe PDF Library to manipulate text data.
Customers should consider as a general rule that a complete resource directory (subfolders included) should always 
exist in the distribution and should always be specified to the \ref A3DPDFInitializePDFLibAndResourceDirectory function. 
Not providing a valid resource directory can lead to unexpected behavior and crashes. As an example, the Table 
functionality fails if the resource directory doesn't exist or is not specified.
A minimal exception to this rule might be when the PDF document generated doesn't contain any text strings, whatever the source
(added with HOOPS Publish functions or even already defined in a provided PDF template). 

The resource directory is provided with the HOOPS Publish package in the \\bin\\resource folder. Please also consider all subfolders as 
part of the resources.

This function should be called before calling any function working on the PDF document, and only once during the life of the application. 

\param [in] pcResourceDirectory The path of an existing directory with full resource definition as provided in the HOOPS Publish package.
NULL is valid but should be used very cautiously as not using resources can lead to unexpected behavior and crashes (see function description).
\return \ref A3D_SUCCESS \n
\version 5.0
*/
A3D_API (A3DStatus, A3DPDFInitializePDFLibAndResourceDirectory, (const A3DUTF8Char* pcResourceDirectory));

/*!
\ingroup a3d_pdflib_functions
\brief Function to terminate the PDF Library.
Terminates the PDF library. This function should only be called at the end of your application. Do not call this function and then continue to use either HOOPS Exchange or HOOPS Publish. Doing so will result in undefined behavior. It is important to call this function only once during the life of the application.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFTerminatePDFLib, ());

/*!
\defgroup a3d_publish_document_module Document Module
\ingroup a3d_publishpdf_module
\brief Document functions

This module describes the functions and structures that allow you to define a PDF Document.
*/


/*!
\defgroup a3d_publish_page_module Page Module
\ingroup a3d_publishpdf_module
\brief Page functions

This module describes the functions and structures that allow you to define a PDF Page in the document.
*/

/*!
\ingroup a3d_publish_page_module
\brief Page size of the PDF document
\version 4.1
*/
typedef enum
{
	kA3DPDFPage11x17=0,		/*!< Standard 11*17 format. size in points: 792 * 1224. */ 
	kA3DPDFPageA3,			/*!< Standard A3 format. size in points: 842 * 1190. */ 
	kA3DPDFPageA4,			/*!< Standard A4 format. size in points: 595 * 842. */
	kA3DPDFPageA5,			/*!< Standard A5 format. size in points: 420 * 595. */
	kA3DPDFPageB4JIS,		/*!< Standard B4 JIS format. size in points: 728 * 1031. */ 
	kA3DPDFPageB5JIS,		/*!< Standard B5 JIS format. size in points: 515 * 728. */ 
	kA3DPDFPageExecutive,	/*!< Standard Executive format. size in points: 522 * 756. */ 
	kA3DPDFPageLegal,		/*!< Standard Legal format. size in points: 612 * 1008. */ 
	kA3DPDFPageLetter,		/*!< Standard Letter format. size in points: 612 * 792. */ 
	kA3DPDFPageTabloid,		/*!< Standard Tabloid format. size in points: 792 * 1224. */ 
	kA3DPDFPageB4ISO,		/*!< Standard B4 ISO format. size in points: 709 * 1001. */ 
	kA3DPDFPageB5ISO,		/*!< Standard B5 ISO format. size in points: 499 * 709. */ 
	kA3DPDFPageCustom		/*!< The page format must be defined using SetPageSize.  */ 
} A3DPDFEPageSize;

/*!
\ingroup a3d_publish_page_module
\brief Page orientation of the PDF document
\version 4.1
*/
typedef enum
{
	kA3DPDFPagePortrait = 0,	/*!< Standard portrait orientation. */ 
	kA3DPDFPageLandscape		/*!< Standard landscape orientation. */
} A3DPDFEPageOrientation;


/*!
\ingroup a3d_publish_page_module
\brief A3DPDFPageData structure
\version 4.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DPDFEPageSize m_ePageSize;				/*!< Size of the page. */
	A3DPDFEPageOrientation m_ePageOrientation;	/*!< Orientation of the page (landscape/portrait). */
} A3DPDFPageData;



/*!
\ingroup a3d_publish_page_module
\brief A3DPDFPageData2 structure
\version 7.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DPDFEPageSize m_ePageSize;				/*!< Size of the page. */
	A3DPDFEPageOrientation m_ePageOrientation;	/*!< Orientation of the page (landscape/portrait). */
	int m_iPageWidth ;							/*!< Defines the page Width when the page m_ePageOrientation == kA3DPDFPageCustom */
	int m_iPageHeigth;							/*!< Defines the page Height when Size m_ePageOrientation == kA3DPDFPageCustom */
} A3DPDFPageData2;


/*!
\ingroup a3d_publish_page_module
\brief A3DPDFRectData structure: structure to define a rectangle placement in the PDF page
\version 4.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DInt32 m_iLeft;			/*!< The x coordinate of the bottom left corner of the rectangle. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DInt32 m_iBottom;			/*!< The y coordinate of the bottom left corner of the rectangle. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DInt32 m_iRight;			/*!< The x coordinate of the top right corner of the rectangle. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DInt32 m_iTop;			/*!< The y coordinate of the top right corner of the rectangle. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
} A3DPDFRectData;


/*!
\ingroup a3d_publish_page_module
\brief A3DPDFRectDData structure: structure to define a rectangle placement in the PDF page, in double precision.
\version 9.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dLeft;			/*!< The x coordinate of the bottom left corner of the rectangle. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dBottom;		/*!< The y coordinate of the bottom left corner of the rectangle. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dRight;			/*!< The x coordinate of the top right corner of the rectangle. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dTop;			/*!< The y coordinate of the top right corner of the rectangle. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
} A3DPDFRectDData;


/*!
\ingroup a3d_publish_document_module
\brief Function to create an empty PDF document

This function creates a document with no page. Subsequently, some pages must be added with the append 
functions \ref A3DPDFDocumentAppendNewPage or \ref A3DPDFDocumentAppendPageFromPDFFile.

\param [out] ppDoc The document created.

\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFDocumentCreateEmpty, (A3DPDFDocument** ppDoc));

/*!
\ingroup a3d_publish_document_module
\brief Function to create a document from a PDF file

This function creates a document from a PDF input file. Starting with HOOPS Publish 6.0 the input PDF can contain several pages.
Pages can be added to the document with append functions \ref A3DPDFDocumentAppendNewPage or \ref A3DPDFDocumentAppendPageFromPDFFileEx.

\param [in] pcFileName The input file name.
\param [out] ppDoc The document created.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFDocumentCreateFromPDFFile, (const A3DUTF8Char* pcFileName, A3DPDFDocument** ppDoc));

/*!
\ingroup a3d_publish_document_module
\brief This method was deprecated in HOOPS Publish 1.10. Use \ref A3DPDFDocumentAppendNewPage instead.

This function adds a unique page to an empty PDF document. 
This function can only be used on a file opened with \ref A3DPDFDocumentCreateEmpty. It can't be used on a file which already contains a page.
\param [in,out] pDoc The current document on which the new page will be added.
\param [in] pPageData The page data parameters.
\param [out] ppPage The newly-created page.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFDocumentCreateUniquePage, (A3DPDFDocument* pDoc, const A3DPDFPageData* pPageData, A3DPDFPage** ppPage));


/*!
\ingroup a3d_publish_document_module
\brief This function adds a unique page to an empty PDF document. 
This function can only be used on a file opened with \ref A3DPDFDocumentCreateEmpty. It can't be used on a file which already contains a page.
\param [in,out] pDoc The current document on which the new page will be added.
\param [in] pPageData The page data parameters.
\param [out] ppPage The newly-created page.
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFDocumentCreateUniquePage2, (A3DPDFDocument* pDoc, const A3DPDFPageData2* pPageData, A3DPDFPage** ppPage));


/*!
\ingroup a3d_publish_document_module
\brief Function to get the unique page of the document
\brief This method was deprecated in HOOPS Publish 6.0. Use \ref A3DPDFDocumentGetPage instead.

This function only works on a document which contains a single page. It is designed to be called after \ref A3DPDFDocumentCreateFromPDFFile to get the Page object. 

\param [in] pDoc The Document object to work with.
\param [out] ppPage The Page object.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFDocumentGetUniquePage, (const A3DPDFDocument* pDoc, A3DPDFPage** ppPage));

/*!
\ingroup a3d_publish_document_module
\brief Function to get the number of pages in the document

\param [in] pDoc The Document object to work with.
\param [out] piNbPages The number of pages. Remember to subtract 1 from this value if you are going to pass it to a 
method that takes a zero-based page number.
\return \ref A3D_SUCCESS \n
\version 6.0
*/
A3D_API (A3DStatus, A3DPDFDocumentGetNumberPages, (const A3DPDFDocument* pDoc, A3DInt32* piNbPages));

/*!
\ingroup a3d_publish_document_module
\brief Function to get a page in the document

\param [in] pDoc The Document object to work with.
\param [in] iNumPage The index of the page. The first page is 0.
\param [out] ppPage The Page object.
\return \ref A3D_SUCCESS \n
\version 6.0
*/
A3D_API (A3DStatus, A3DPDFDocumentGetPage, (const A3DPDFDocument* pDoc, const A3DInt32 iNumPage, A3DPDFPage** ppPage));

/*!
\ingroup a3d_publish_document_module
\brief Function to remove pages in the document

\param [in,out] pDoc The Document object to work with.
\param [in] iFirstPage The index of the first page to remove. The first page is 0.
\param [in] iLastPage The index of the last page to remove.
\return \ref A3D_SUCCESS \n
\version 6.0
*/
A3D_API (A3DStatus, A3DPDFDocumentRemovePages, (const A3DPDFDocument* pDoc, const A3DInt32 iFirstPage, const A3DInt32 iLastPage));




/*!
\ingroup a3d_publish_document_module
\brief Appends a new empty page to a document

The page is added at the end of the document. It is a new page created with the options set in the pPageData argument.
\param [in,out] pDoc The Document object to work with.
\param [in] pPageData The page parameters.
\param [out] ppPage The Page object for the new page.
\return \ref A3D_SUCCESS \n
\version 4.2
*/
A3D_API (A3DStatus, A3DPDFDocumentAppendNewPage, (A3DPDFDocument* pDoc, const A3DPDFPageData* pPageData, A3DPDFPage** ppPage));


/*!
\ingroup a3d_publish_document_module
\brief Appends a new empty page to a document

The page is added at the end of the document. It is a new page created with the options set in the pPageData argument.
\param [in,out] pDoc The Document object to work with.
\param [in] pPageData The page parameters.
\param [out] ppPage The Page object for the new page.
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFDocumentAppendNewPage2, (A3DPDFDocument* pDoc, const A3DPDFPageData2* pPageData, A3DPDFPage** ppPage));

/*!
\ingroup a3d_publish_document_module
\brief Superseded by \ref A3DPDFDocumentAppendPageFromPDFFileEx in A3DLIBS 4.3 and later.

Appends new pages from a PDF template to a document. Starting with HOOPS Publish 6.0 the input PDF can contain several pages.
The pages are added at the end of the document. All pages are copied from the PDF template file specified with the pcFileName argument.
If the imported pages contain form fields with names that already exist on other pages of the document, the function will fail. 
In this situation, use \ref A3DPDFDocumentAppendPageFromPDFFileEx to rename all form fields of the imported pages.
\param [in,out] pDoc The Document object to work with.
\param [in] pcFileName The input file name of the PDF template.
\param [out] ppPage The Page object for the last page inserted.
\return \ref A3D_SUCCESS \n
\version 4.2
*/
A3D_API (A3DStatus, A3DPDFDocumentAppendPageFromPDFFile, (A3DPDFDocument* pDoc, const A3DUTF8Char* pcFileName, A3DPDFPage** ppPage));



/*!
\ingroup a3d_publish_document_module

Appends new pages from a PDF template to a document, with the possibility to rename all form fields to avoid PDF conflicts.
This method supersedes \ref A3DPDFDocumentAppendPageFromPDFFile() in A3DLIBS 4.3 and later.
Starting from HOOPS Publish 6.0 the input PDF can contain several pages.
The pages are added at the end of the document. All pages are copied from the PDF template file specified with the pcFileName argument.
If the imported pages contain form fields with names that already exist on other pages of the document, the function will fail. 
In this situation, set the bRenameFields parameter to true to rename all form fields of the imported pages.
Warning: all references to the renamed form fields have to be modified to reflect the new names. This has to be done for example for JavaScript code
that could work with these fields.
\param [in,out] pDoc The Document object to work with.
\param [in] pcFileName The input file name of the PDF template.
\param [in] bRenameFields If true, the form fields of the template pages are renamed, appending the position of the pages in the
final document to every fields. Note that the index of the first page is 1.
For example, a field 'MyTitle' will be renamed 'MyTitle_1" if the page is inserted as the first page of the document.
If false, the form fields are not renamed and the function will fail if some fields already exist on the document with the same name.
\param [out] ppPage The Page object for the last page inserted.
\return \ref A3D_SUCCESS \n
\version 4.3
*/
A3D_API (A3DStatus, A3DPDFDocumentAppendPageFromPDFFileEx, (A3DPDFDocument* pDoc, const A3DUTF8Char* pcFileName, const A3DBool bRenameFields, A3DPDFPage** ppPage));


/*!
\ingroup a3d_publish_document_module
\brief A3DPDFDocumentInformationData structure
\version 4.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcTitle;		/*!< Title of the document. */ 
	A3DUTF8Char* m_pcAuthor;	/*!< Author of the document. */
	A3DUTF8Char* m_pcSubject;	/*!< Subject of the document. */
	A3DUTF8Char* m_pcCreator;	/*!< The product which created the document (customer application). */ 
} A3DPDFDocumentInformationData;

/*!
\ingroup a3d_publish_document_module
\brief Function to set information on the document. These information are visible in the Adobe Reader on the File Properties menu.
\param [in,out] pDoc The Document object to work with.
\param [in] pInformationData The information parameters.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFDocumentSetInformation, (A3DPDFDocument* pDoc, const A3DPDFDocumentInformationData* pInformationData));

/*!
\ingroup a3d_publish_document_module
\brief Function to add user and owner passwords on a document. 

These passwords are natively supported by Adobe Reader. If a user password is specified, Adobe Reader will ask for a password when opening the document.
The owner password  is the password used to set document restrictions on the document. It does not restrict the opening of a PDF file, only what can be done once opened.
Document restrictions can include printing, changing the document, document assembly, content copying, content copying for accessibility, page extraction, commenting, 
filling of form fields, signing, and creation of template pages.

\param [in,out] pDoc The Document object to work with.
\param [in] pcUserPassword The password to protect the document at opening. Also protects against document modification and printing.
If an empty string is specified, no user password is required by Adobe Reader or Acrobat.
\param [in] pcOwnerPassword Lets you require a password when changing the security features of the PDF, not when opening it.
If an empty string is specified, no password will be required in Acrobat to change security settings.

\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFDocumentSetPassword, (A3DPDFDocument* pDoc, const A3DUTF8Char* pcUserPassword, const A3DUTF8Char* pcOwnerPassword));

/*!
\defgroup a3d_publish_documentpermissionbits Bit Field to indicate the document permissions. 
\ingroup a3d_publish_document_module
\version 7.2
@{
*/
#define kA3DPDFDocumentPermOpen		0x01 /*!< The user can open and decrypt the document. */ 
#define kA3DPDFDocumentPermSecure	0x02 /*!< The user can change the document's security settings. */ 
#define kA3DPDFDocumentPermPrint		0x04 /*!< The user can print the document. 
	Page Setup access is unaffected by this permission, since that affects Acrobat's preferences - not 
	the document's. In the Document Security dialog, this corresponds to the Printing entry. */
#define kA3DPDFDocumentPermEdit		0x08 /*!< The user can edit the document more than adding 
	or modifying text notes (see also kA3DPDFDocumentPermEditNotes). In the Document Security dialog,
	this corresponds to the Changing the Document entry. */
#define kA3DPDFDocumentPermCopy		0x10 /*!< The user can copy information from the document 
	to the clipboard. In the document restrictions, this corresponds to the Content Copying or Extraction 
	entry. */
#define kA3DPDFDocumentPermEditNotes	0x20 /*!< The user can add, modify, and delete text notes 
	(see also kA3DPDFDocumentPermEdit). In the document restrictions, this corresponds to the Authoring
	Comments and Form Fields entry. */
#define kA3DPDFDocumentPermSaveAs	0x40 /*!< The user can perform a Save As.... If both 
	kA3DPDFDocumentPermEdit and kA3DPDFDocumentPermEditNotes are disallowed, Save will be disabled but
	Save As... will be enabled. The Save As... menu item is not necessarily disabled even if the user 
	is not permitted to perform	a Save As... */
#define kA3DPDFDocumentPermFillandSign	0x100 /*!< Overrides other kA3DPDFDocumentPerm bits. It allows 
	the user to fill in	or sign existing form or signature fields. */
#define kA3DPDFDocumentPermAccessible	0x200 /*!< Overrides kA3DPDFDocumentPermCopy to enable the 
	Accessibility API. If a document is saved in Rev2 format (Acrobat 4.0 compatible), only the 
	kA3DPDFDocumentPermCopy bit is checked to determine the Accessibility API state. */
#define kA3DPDFDocumentPermDocAssembly	0x400 /*!< Overrides various kA3DPDFDocumentPermEdit bits and
	allows the following operations: page insert/delete/rotate and create bookmark and thumbnail. */
#define kA3DPDFDocumentPermHighPrint		0x800 /*!< This bit is a supplement to kA3DPDFDocumentPermPrint. 
	If it is clear (disabled) only low quality printing (Print As Image) is allowed. On UNIX platforms where
	Print As Image doesn't exist, printing is disabled. */
#define kA3DPDFDocumentPermOwner		0x8000 /*!< The user is permitted to perform all operations,
	regardless of the permissions specified by the document. Unless this permission is set, the document's 
	permissions will be reset to those in the document after a full save. */
#define kA3DPDFDocumentPermFormSubmit       0x10000 /*!< This should be set if the user can submit forms 
	outside of the browser. This bit is a supplement to kA3DPDFDocumentPermFillandSign. */
#define kA3DPDFDocumentPermFormSpawnTempl   0x20000 /*!< This should be set if the user can spawn
	template pages. This bit will allow page template spawning even if kA3DPDFDocumentPermEdit 
	and kA3DPDFDocumentPermEditNotes are clear. */
#define kA3DPDFDocumentPermAll		0xFFFFFFFF /*!< All permissions. */
#define kA3DPDFDocumentPermSettable	(kA3DPDFDocumentPermPrint + kA3DPDFDocumentPermEdit + kA3DPDFDocumentPermCopy + kA3DPDFDocumentPermEditNotes) 
/*!< The OR of all operations that can be set by the user in the
	security restrictions (kA3DPDFDocumentPermPrint + kA3DPDFDocumentPermEdit + kA3DPDFDocumentPermCopy + kA3DPDFDocumentPermEditNotes). */
#define kA3DPDFDocumentPermUser		(kA3DPDFDocumentPermAll - kA3DPDFDocumentPermOpen - kA3DPDFDocumentPermSecure) /*!< All permissions. */
/*!
@} <!-- end of a3d_publish_documentpermissionbits -->
*/

/*!
\ingroup a3d_publish_document_module
\brief Function to set permissions on a document. 

\param [in,out] pDoc The Document object to work with.
\param [in] iPermissions The permissions, composed of bit fields detailed in \ref a3d_publish_documentpermissionbits.

\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFDocumentSetDocumentPermissions, (A3DPDFDocument* pDoc, int iPermissions));

/*!
\ingroup a3d_publish_document_module
\brief Function to store an image in the PDF file in a way it can be used as an icon for PDF fields.

\par Stored in that way, the image can be dynamically retrieved by the Acrobat JavaScript document function 'getIcon'.
For example, if the function is called with A3DPDFDocumentAddImageAsIcon(pimage,"myicon"), then the following
JavaScript code might be used on the document to dynamically set the icon on a button:<br>
<code>
var but = this.getField("buttonfieldtopopulate");<br>
var icon = this.getIcon("myicon");<br>
but.buttonSetIcon(icon);
</code>

\param [in,out] pDoc The Document object to work with.
\param [in] pcIconName The icon name that will be used to identify the image.
\param [in] pImage The image.
\return \ref A3D_SUCCESS \n
\version 6.1
*/
A3D_API (A3DStatus, A3DPDFDocumentAddImageAsIcon, (A3DPDFDocument* pDoc, const A3DPDFImage* pImage, const A3DUTF8Char* pcIconName));

/*!
\ingroup a3d_publish_document_module
\brief Function to attach a file to the document. 
Attachments are visible on the Adobe Reader with the specific navigation pane. In Adobe Reader X version, the Attachments pane can be activated with the menu View / Show/Hide / Navigation Panes / Attachments.
 
\param [in,out] pDoc The Document object to work with.
\param [in] pcFileName The name of the file to attach.
\param [in] pcDescription The description of the attached file.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFDocumentAddFileAttachment, (A3DPDFDocument* pDoc, const A3DUTF8Char* pcFileName, const A3DUTF8Char* pcDescription));

/*!
\ingroup a3d_publish_document_module
\brief Adds a JavaScript to a document. This JavaScript is launched when the file is opened
\param [in,out] pDoc The Document object to work with.
\param [in] pcScriptName The name of the script. It is not used by Acrobat but needs to be unique.
\param [in] pcJavascriptString The string which contains the JavaScript.
\return \ref A3D_SUCCESS \n
\version 4.3
*/
A3D_API (A3DStatus, A3DPDFDocumentAddJavascriptFromString, (A3DPDFDocument* pDoc, const A3DUTF8Char* pcScriptName, const A3DUTF8Char* pcJavascriptString));


/*!
\ingroup a3d_publish_document_module
\brief Function to save the PDF document.

\param [in] pDoc The Document object to save.
\param [in] pcFileName The file name where to save the document. The path (absolute or relative) must be provided (use ".\\" for the current directory).
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFDocumentSave, (A3DPDFDocument* pDoc, const A3DUTF8Char* pcFileName));


/*!
\defgroup a3d_publish_saveflagsbits Bit Field to indicate the savong options.
\ingroup a3d_publish_document_module
\version 9.2
@{
*/
#define kA3DPDFSaveFull				0x00 /*!< Basic level (equivalent to a call to \ref A3DPDFDocumentSave). */ 
#define kA3DPDFSaveOptimized		0x01 /*!< Adds misc optimizations for saving. */ 
#define kA3DPDFSaveOptimizeFonts	0x02 /*!< Adds optimization on fonts definition. This can involve substantial memory and CPU overhead. */ 

/*!
\ingroup a3d_publish_document_module
\brief Function to save the PDF document, using some flags for optimizing the size of the resulting PDF.

\param [in] pDoc The Document object to save, using some flags for optimizing the resulting PDF.
\param [in] iSaveFlags The saving flags, composed of bit fields detailed in \ref a3d_publish_saveflagsbits.
\param [in] pcFileName The file name where to save the document. The path (absolute or relative) must be provided (use ".\\" for the current directory).
\return \ref A3D_SUCCESS \n
\version 9.2
*/
A3D_API(A3DStatus, A3DPDFDocumentSaveEx, (A3DPDFDocument* pDoc, const int iSaveFlags, const A3DUTF8Char* pcFileName));

/*!
\ingroup a3d_publish_document_module
\brief Function to close the document and free all memory.

\param [in,out] pDoc The Document object to work with.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFDocumentClose, (A3DPDFDocument* pDoc));



/*!
\defgroup a3d_publish_text_module Text Module
\ingroup a3d_publishpdf_module
\brief Adds text lines in the page

This module describes the functions and structures that allow you to add Text lines in the page.
*/

/*!
\ingroup a3d_publish_text_module
\brief Different predefined fonts.

These fonts are automatically supported by default by Adobe Reader. Nothing specific is required to display these fonts.
\version 4.1
*/
typedef enum
{
	kA3DPDFFontTimesRoman=0, 			/*!< Adobe standard Times font, with a normal face. */
	kA3DPDFFontTimesItalic,				/*!< Adobe standard Times font, with a italic face. */
	kA3DPDFFontTimesBold,				/*!< Adobe standard Times font, with a bold face. */
	kA3DPDFFontTimesBoldItalic,			/*!< Adobe standard Times font, with a bold-italic face. */
	kA3DPDFFontHelvetica,				/*!< Adobe standard Helvetica font, with a normal face. */
	kA3DPDFFontHelveticaOblique,		/*!< Adobe standard Helvetica font, with a italic face. */
	kA3DPDFFontHelveticaBold,			/*!< Adobe standard Helvetica font, with a bold face. */
	kA3DPDFFontHelveticaBoldOblique,	/*!< Adobe standard Helvetica font, with a bold-italic face. */
	kA3DPDFFontCourier,					/*!< Adobe standard Courier font, with a normal face. */
	kA3DPDFFontCourierOblique,			/*!< Adobe standard Courier font, with a italic face. */
	kA3DPDFFontCourierBold,				/*!< Adobe standard Courier font, with a bold face. */
	kA3DPDFFontCourierBoldOblique		/*!< Adobe standard Courier font, with a bold-italic face. */
} A3DPDFEFontName;


/*!
\ingroup a3d_publish_text_module
\brief A3DPDFTextData structure.

Structure to specify a text line: content and formatting options (color, font used and font size)
\version 4.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcTextString;	/*!< Content of the text string. It should be a single line text string (no carriage return supported). */
	A3DPDFEFontName m_eFontName;	/*!< Font name of the text. */
	A3DInt32 m_iFontSize; 			/*!< Size of the font. */
	A3DPDFRgbColorData m_sColor;	/*!< Color of the text. */
} A3DPDFTextData;


/*!
\ingroup a3d_publish_text_module
\brief Languages supported for text strings.
\version 5.0
*/
typedef enum
{
	kA3DPDFASCII,				/*!< ASCII. */
	kA3DPDFEastEuropeanRoman,	/*!< East European Roman. */		
	kA3DPDFCyrillic,			/*!< Cyrillic. */
	kA3DPDFGreek,				/*!< Greek. */
	kA3DPDFTurkish,				/*!< Turkish. */
	kA3DPDFHebrew,				/*!< Hebrew. */
	kA3DPDFArabic,				/*!< Arabic. */
	kA3DPDFBaltic,				/*!< Baltic. */
	kA3DPDFChineseTraditional,	/*!< Traditional Chinese. */
	kA3DPDFChineseSimplified,	/*!< Simplified Chinese. */
	kA3DPDFJapanese,			/*!< Japanese. */
	kA3DPDFKorean				/*!< Korean. */
}  A3DPDFELanguage;

/*!
\ingroup a3d_publish_text_module
\brief A3DPDFTextDataEx structure.

Structure to specify a text line with extended fonts and languages. The font needs to be available in C:\\Windows\\Fonts directory on the machine 
where HOOPS Publish is run.
Depending on the characters used in the string, the font must be chosen, as well as the according language.

\version 5.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcTextString;		/*!< Content of the text string. It should be a single line text string (no carriage return supported). */
	A3DUTF8Char* m_pcFontName;			/*!< Font name of the text. */
	A3DUTF8Char* m_pcEncodingName;		/*!< Set null to keep default treatment. Supported encoding are "WinAnsiEncoding", 
										"StandardEncoding", "MacRomanEncoding", "MacExpertEncoding", or "PDFDocEncoding"
										(see PDF specifications for more details). 
										If NULL, the encoding is tentatively retrieved from m_eLanguage. The result is uncertain. */
	A3DPDFELanguage m_eLanguage;		/*!< Language used for the text string. */
	A3DInt32 m_iFontSize;				/*!< Size of the font. */
	A3DPDFRgbColorData m_sColor;		/*!< Color of the text. */
	A3DBool m_bEmbedFontInPDF;			/*!< If true, the font will be embedded in the PDF document, no need to have the font on the computer for
												the one who will open the document. */
} A3DPDFTextDataEx;

/*!
\ingroup a3d_publish_text_module
\brief Function to create a text object

The text object is primarily created with this function, and it should be positioned on the page with the function \ref A3DPDFPageInsertText.

\param [in,out] pDoc The Document object to work with.
\param [in] pTextData The text parameters.
\param [out] ppText The Text object created.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFTextCreate, (A3DPDFDocument* pDoc, const A3DPDFTextData* pTextData, A3DPDFText** ppText));


/*!
\ingroup a3d_publish_text_module
\brief Function to create a text object with extended fonts and languages.

The text object is primarily created with this function, and it should be positioned on the page with the function \ref A3DPDFPageInsertText.
If the font can't be found in the directory C:\\Windows\\Fonts, then the function returns an A3DPDF_CANNOT_FIND_FONT (-1000016) error.
WARNING: the initialization function \ref A3DPDFInitializePDFLibAndResourceDirectory must be called before using this function.

\param [in] pDoc The Document object to work with.
\param [in] pTextDataEx The text parameters.
\param [out] ppText The Text object created.
\return \ref A3D_SUCCESS \n
\version 5.0
*/
A3D_API (A3DStatus, A3DPDFTextCreateEx, (A3DPDFDocument* pDoc, const A3DPDFTextDataEx* pTextDataEx, A3DPDFText** ppText));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a text in a page

\param [in,out] pPage The Page object to work with.
\param [in] pText The Text object to insert on the page.
\param [in] iPosLeft The x coordinate of the insertion point of the text. The insertion point is the bottom left corner of the text. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\param [in] iPosBottom The y coordinate of the insertion point of the text. The insertion point is the bottom left corner of the text. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageInsertText, (A3DPDFPage* pPage, A3DPDFText* pText, const A3DInt32 iPosLeft, const A3DInt32 iPosBottom));

/*!
\ingroup a3d_publish_page_module
\brief Function to insert a text in a table

\param [in,out] pPage The Page object to work with.
\param [in] pTable The Table object to insert in the table.
\param [in] pText The Text object to insert in the table.
\param [in] iRowIndex The index of the row of the table's cell to insert the button (start from 1)
\param [in] iColumnIndex The index of the column of the table's cell to insert the button (start from 1)
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFPageInsertTextInTable, (A3DPDFPage* pPage, A3DPDFTable* pTable, A3DPDFText* pText, A3DInt32 iRowIndex, A3DInt32 iColumnIndex));



/*!
\defgroup a3d_publish_image_module Image Module
\ingroup a3d_publishpdf_module
\brief Add Images in the page

This module describes the functions and structures that allow you to add images in the page.
*/

/*!
\ingroup a3d_publish_image_module
\brief Different image formats 
\version 4.1
*/
typedef enum
{
	kA3DPDFImageFormatUnknown,			/*!< Undefined format. */
	kA3DPDFImageFormatBmp,				/*!< BMP format. */
	kA3DPDFImageFormatPng,				/*!< PNG format. */
	kA3DPDFImageFormatJpg,				/*!< JPEG format. */
	kA3DPDFImageFormatBitmapRgbByte,	/*!< Bitmap RGB format. */
	kA3DPDFImageFormatBitmapRgbaByte,	/*!< Bitmap RGBA format. */
	kA3DPDFImageFormatBitmapGreyByte,	/*!< Bitmap grey format. */
	kA3DPDFImageFormatBitmapGreyaByte,	/*!< Bitmap greya format. */
	kA3DPDFImageFormatEmf,				/*!< EMF format. */
	kA3DPDFImageFormatUrl,				/*!< URL format. */	 // m_acBinaryData contains the url (UTF-8)
	kA3DPDFImageFormatGif,				/*!< GIF format. */
	kA3DPDFImageFormatTif,				/*!< TIFF format. */
	kA3DPDFImageFormatPcx,				/*!< PCX format. */
	kA3DPDFImageFormatTga,				/*!< TGA format. */
	kA3DPDFImageFormatPpm,				/*!< PPM format. */
	kA3DPDFImageFormatIlbm,				/*!< ILBM format. */
	kA3DPDFImageFormatCel,				/*!< Cel format. */
	kA3DPDFImageFormatRgb,				/*!< RGB format. */
	kA3DPDFImageFormatPsd,				/*!< PSD format. */
	kA3DPDFImageFormatSoftimagepic		/*!< Softimagepic format. */
} A3DPDFEImageFormat;

/*!
\ingroup a3d_publish_image_module
\brief A3DPDFImageData structure
\version 4.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcFileName;		/*!< File name of the image file. */
	A3DInt32 m_iWidth;				/*!< Width in pixels. */
	A3DInt32 m_iHeight;				/*!< Height in pixels. */
	A3DPDFEImageFormat m_eFormat;	/*!< Format of the image. */
} A3DPDFImageData;

/*!
\ingroup a3d_publish_image_module
\brief Function to create a picture image object

The image object is primarily created with this function, and it should be positioned on the page with the function \ref A3DPDFPageInsertImage.

\param [in,out] pDoc The Document object to work with.
\param [in] pImageData The image parameters.
\param [out] ppImage The Image object created.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFImageCreate, (A3DPDFDocument* pDoc, const A3DPDFImageData* pImageData, A3DPDFImage** ppImage));

/*!
\ingroup a3d_publish_page_module
\brief Function to insert an image in a page

\param [in,out] pPage The Page object to work with.
\param [in] pImage The Image object to insert on the page.
\param [in] iPosLeft The x coordinate of the insertion point of the image. The insertion point is the bottom left corner of the image. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\param [in] iPosBottom The y coordinate of the insertion point of the image. The insertion point is the bottom left corner of the image. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageInsertImage, (A3DPDFPage* pPage, A3DPDFImage* pImage, const A3DInt32 iPosLeft, const A3DInt32 iPosBottom));



/*!
\defgroup a3d_publish_link_module Link Module
\ingroup a3d_publishpdf_module
\brief Adds Links in the page

This module describes the functions and structures that allow you to add links in the page.
A link is a 'hot zone' on which is assigned an action. When the user clicks on the zone, the action is executed.
The link can be invisible, or drawn as a rectangle with a border. The border width and color can be specified.
*/

/*!
\ingroup a3d_publish_link_module
\brief Highlighting mode (the visual effect that shall be used when the mouse button is pressed or held down inside its active area)
\version 5.2
*/
typedef enum
{
	kA3DPDFLinkHighlightNone=0,		/*!< No highlighting. */
	kA3DPDFLinkHighlightInvert,		/*!< Invert the contents of the link rectangle. */
	kA3DPDFLinkHighlightOutline,	/*!< Invert the link border. */
	kA3DPDFLinkHighlightPush		/*!< Display the link as if it were being pushed below the surface of the page. */
} A3DPDFELinkHighlightMode;

/*!
\ingroup a3d_publish_link_module
\brief A3DPDFLinkData structure
\version 5.2
*/
typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DInt32 m_iBorderWidth;						/*!< Border width in points. 0 for an invisible border. */
	A3DPDFRgbColorData m_sColor;					/*!< Border color. */
	A3DPDFELinkHighlightMode m_eHighlightingMode;	/*!< Highlighting mode (the visual effect that shall be used when the mouse button is pressed or held down inside its active area). */
	A3DUTF8Char* m_pcJavascriptString;				/*!< JavaScript action to be executed when the link is clicked. */
} A3DPDFLinkData;

/*!
\ingroup a3d_publish_link_module
\brief Function to create a link object

The link object is primarily created with this function, and it should be positioned on the page with the function \ref A3DPDFPageInsertLink.

\param [in,out] pDoc The Document object to work with.
\param [in] pLinkData The link parameters.
\param [out] ppLink The Link object created.
\return \ref A3D_SUCCESS \n
\version 5.2
*/
A3D_API (A3DStatus, A3DPDFLinkCreate, (A3DPDFDocument* pDoc, const A3DPDFLinkData* pLinkData, A3DPDFLink** ppLink));

/*!
\ingroup a3d_publish_page_module
\brief Function to insert a link in a page

\param [in] pPage The Page object to work with.
\param [in] pLink The Link object to insert on the page.
\param [in] pRectData The rectangle to specify the position on the page.
\return \ref A3D_SUCCESS \n
\version 5.2
*/
A3D_API (A3DStatus, A3DPDFPageInsertLink, (A3DPDFPage* pPage, A3DPDFLink* pLink, const A3DPDFRectData* pRectData));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a link in a table

\param [in,out] pPage The Page object to work with.
\param [in] pTable The Table object to insert in the table.
\param [in] pLink The Link object to insert in the table.
\param [in] iRowIndex The index of the row of the table's cell to insert the link (start from 1)
\param [in] iColumnIndex The index of the column of the table's cell to insert the link (start from 1)
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFPageInsertLinkInTable, (A3DPDFPage* pPage, A3DPDFTable* pTable, A3DPDFLink* pLink, A3DInt32 iRowIndex, A3DInt32 iColumnIndex));

/*!
\defgroup a3d_publish_table_module Table Module
\ingroup a3d_publishpdf_module
\brief Module to create tables on a PDF page

This module describes the functions and structures that allow you to define tables on a PDF page.
The table implementation uses an add-on to HOOPS Publish (TableToPDF) which is provided for free by Tech Soft 3D.
The add-on is using components that are licensed under GNU LGPL terms. 
<b>Consequently, the usage of tables using HOOPS Publish add-on requires our customer's application to comply
with LGPL requirements.</b>
TableToPDF can be downloaded at http://developer.techsoft3d.com/add-ons/tabletopdf/
The deployment process is simple and just requires to copy the provided DLLs in HOOPS Publish binaries folder.

With HOOPS Publish, tables are defined in a HTML format using the function \ref A3DPDFTableCreate. Two parameters
define the table: the table content definition, as well as a style definition. Then, the table is positioned on 
the PDF page using the function \ref A3DPDFPageInsertTable. 

The HTML and style definition is out of the scope of this guide. HOOPS Publish and TableToPDF support the
latest HTML5 and CSS3 specifications which are widely documented on the Internet. A lot of guides and samples
can be consulted.

As an example, the following simple table
\image html sampletable.png

is defined with HOOPS Publish by specifying the members of \ref A3DPDFTableData :

The member \ref A3DPDFTableData::m_pcHtmlTable member takes the following value:
\include extable.html

The member \ref A3DPDFTableData::m_pcHtmlStyle member takes the following value:
\include exstyle.html
	
*/



/*!
\ingroup a3d_publish_table_module
\brief Structure to define a table
\version 5.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcHtmlTable;					/*!< String for definition of the table in a HTML format. See example in \ref a3d_publish_table_module. */
	A3DUTF8Char* m_pcHtmlStyle;					/*!< String for definition of the table style in a CSS format. See example in \ref a3d_publish_table_module. */
} A3DPDFTableData;


/*!
\ingroup a3d_publish_table_module
\brief Function to create a table on a PDF page

The table object is primarily created with this function, and it should be positioned on the page with the function \ref A3DPDFPageInsertTable.
WARNING: the initialization function \ref A3DPDFInitializePDFLibAndResourceDirectory must be called before using this function.
Also, the binaries of the free add-on TableToPDF must have been copied in the same directory as HOOPS Publish binaries.

\param [in,out] pDoc The Document object to work with.
\param [in] pTableData The table parameters.
\param [out] ppTable The Table object created.
\return \ref A3D_SUCCESS \n
\version 5.1
*/
A3D_API (A3DStatus, A3DPDFTableCreate, (A3DPDFDocument* pDoc, const A3DPDFTableData* pTableData, A3DPDFTable **ppTable));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a table in a page

Warning: The positioning is not defined as in the other insertion functions (for texts or images). Here, the position is specified from
the top of the page.

\param [in,out] pPage The Page object to work with.
\param [in] pTable The Table object to insert on the page.
\param [in] iPosLeft The x coordinate of the insertion point of the table. The insertion point is the top left corner of the table. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\param [in] iPosTop The y coordinate of the insertion point of the table. The insertion point is the top left corner of the table. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\return \ref A3D_SUCCESS \n
\version 5.1
*/
A3D_API (A3DStatus, A3DPDFPageInsertTable, (A3DPDFPage* pPage, A3DPDFTable* pTable, const A3DInt32 iPosLeft, const A3DInt32 iPosTop));


/*!
\defgroup a3d_publish_3Dannot_module 3D Annot Module
\ingroup a3d_publishpdf_module
\brief 3D Annot functions

This module describes the functions and structures that allow you to define 3D data in the page.
*/


/*!
\ingroup a3d_publish_3Dannot_module
\brief The circumstances under which the 3D Annot shall be activated
\version 4.1
*/
typedef enum
{
	kA3DPDFActivExplicitActivation=0, 	/*!< The 3D Annot shall remain inactive until explicitly activated by a script or user action. */
	kA3DPDFActivPageOpened,				/*!< The 3D Annot shall be activated as soon as the page containing the 3D Annot is opened. */
	kA3DPDFActivPageVisible				/*!< The 3D Annot shall be activated as soon as any part of the page containing the 3D Annot becomes visible. */
} A3DPDFEActivateWhen;

/*!
\ingroup a3d_publish_3Dannot_module
\brief The circumstances under which the 3D Annot shall be deactivated
\version 4.1
*/
typedef enum
{
	kA3DPDFActivExplicitDesactivation=0,	/*!< The 3D Annot shall remain active until explicitly deactivated by a script or user action. */
	kA3DPDFActivPageClosed,					/*!< The 3D Annot shall be deactivated as soon as the page is closed. */
	kA3DPDFActivPageNotVisible				/*!< The 3D Annot shall be deactivated as soon as the page containing the 3D Annot becomes invisible. */
} A3DPDFEDesactivateWhen;


/*!
\ingroup a3d_publish_3Dannot_module
\brief Animation Style
\version 4.1
*/
typedef enum
{
	kA3DPDFAnimStyleNoAnimation=0,	/*!< Animations shall not be driven directly by the conforming reader. This value shall be used by documents that are intended to drive animations through an alternate means, such as JavaScript. */
	kA3DPDFAnimStyleLoop,			/*!< This animation style results in a repetitive playthrough of the animation. */
	kA3DPDFAnimStyleBounce			/*!< This animation style results in a back-and-forth playing of the animation. */
} A3DPDFEAnimationStyle;

/*!
\ingroup a3d_publish_3Dannot_module
\brief Lighting
\version 4.1
*/
typedef enum
{
	kA3DPDFLightArtworkCurrent=0,	/*!< The light is defined from the 3D data (in the 3D Artwork). */
	kA3DPDFLightNone,				/*!< No light. */
	kA3DPDFLightWhite,				/*!< White light. */
	kA3DPDFLightDay,				/*!< Day light. */
	kA3DPDFLightBright,				/*!< Bright light. */
	kA3DPDFLightPrimaryColor,		/*!< Primary color light. */
	kA3DPDFLightNight,				/*!< Night light. */
	kA3DPDFLightBlue,				/*!< Blue light. */
	kA3DPDFLightRed,				/*!< Red light. */
	kA3DPDFLightCube,				/*!< Cube light. */
	kA3DPDFLightCADOptimized,		/*!< CAD Optimized light. */
	kA3DPDFLightHeadlamp			/*!< Headlamp light. */
} A3DPDFELighting;

/*!
\ingroup a3d_publish_3Dannot_module
\brief Rendering Style
\version 4.1
*/
typedef enum
{
	kA3DPDFRenderingTransparentBoundingBox=0,		/*!< Displays bounding boxes faces of each node, aligned with the axes of the local coordinate space for that node, with an added level of transparency. */
	kA3DPDFRenderingSolid,							/*!< Displays textured and lit geometric shapes. */
	kA3DPDFRenderingTransparent,					/*!< Displays textured and lit geometric shapes (triangles) with an added level of transparency. */
	kA3DPDFRenderingSolidWireframe,					/*!< Displays textured and lit geometric shapes (triangles) with an added level of transparency, with single color opaque edges on top of it. */
	kA3DPDFRenderingIllustration,					/*!< Displays silhouette edges with surfaces, removes obscured lines. */
	kA3DPDFRenderingSolidOutline,					/*!< Displays silhouette edges with lit and textured surfaces, removes obscured lines. */
	kA3DPDFRenderingShadedIllustration,				/*!< Displays silhouette edges with lit and textured surfaces and an additional emissive term to remove poorly lit areas of the artwork. */
	kA3DPDFRenderingBoundingBox,					/*!< Displays the bounding box edges of each node, aligned with the axes of the local coordinate space for that node. */
	kA3DPDFRenderingTransparentBoundingBoxOutline,	/*!< Displays bounding boxes edges and faces of each node, aligned with the axes of the local coordinate space for that node, with an added level of transparency. */
	kA3DPDFRenderingWireframe,						/*!< Displays only edges in a single color. */
	kA3DPDFRenderingShadedWireframe,				/*!< Displays only edges, though interpolates their color between their two vertices and applies lighting. */
	kA3DPDFRenderingTransparentWireframe,			/*!< Displays textured and lit geometric shapes (triangles) with an added level of transparency, with single color opaque edges on top of it. */
	kA3DPDFRenderingHiddenWireframe,				/*!< Displays edges in a single color, though removes back-facing and obscured edges. */
	kA3DPDFRenderingVertices,						/*!< Displays only vertices in a single color. */
	kA3DPDFRenderingShadedVertices					/*!< Displays only vertices, though uses their vertex color and applies lighting. */
} A3DPDFERenderingStyle;



/*!
\defgroup a3d_publish_3Dartwork_module 3D Artwork Module
\ingroup a3d_publish_3Dannot_module
\brief 3D Artwork functions

This module describes the functions and structures that allow you to define 3D data in the page.
*/
/*!
\ingroup a3d_publish_3Dartwork_module
\brief A3DPDF3DArtworkData structure
\version 4.1
*/
typedef struct 
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DPDF3DStream *m_pStream;					/*!< Specifies the 3D stream object created from the 3D data. */
	A3DUTF8Char* m_pcJavaScriptFileName;		/*!< A JavaScript file to store on the 3D Annot. */
	
	A3DBool m_bActivatePMICrossHighlight;		/*!<
													If true, some JavaScript code is generated so that when the user clicks on a markup, the associated surface is highlighted.
													Only works with Acrobat 11 and later. */
	A3DBool m_bAddPMISemanticInformation;		/*!< If true, the information on semantic PMI is added as nodes attributes on the model tree. */
	A3DBool m_bKeepNativeDefaultView;			/*!<
													If true, if there's a default view in the PRC modelfile: the default view in the resulting PDF will be that one, no matter 
													if other default views are defined at PDF level.
													In other situations (no default view in the PRC modelfile; or the boolean is false): a default view is defined at the PDF level.
													A default view at the PDF level means a view programmatically created using \ref A3DPDFViewCreate, or a default view 
													automatically created by HOOPS Publish if no default view is already defined. 
													<br>This boolean is not used if the 3D stream is created with \ref A3DPDF3DStreamCreateFromFile. */
	A3DBool m_bUseRuntimeDisplaySettings;		/*!<
													This boolean controls which display settings (rendering style, background color and lighting) are applied to the 3D annotation
													when a view is activated. 
													<ul>
													<li>If the boolean is true, all the views have initially the <b>default display settings</b>, then if the end-user manually changes
													the settings, this change affects all the views except the 'home' view (the view associated to the 'home' icon in Adobe Reader)
													for which it resets to the <b>default display settings</b>.
													The <b>default display settings</b> are the ones assigned to the default view: A3DPDF3DAnnotData values if the default view is a
													native or the automatic view, and A3DPDFViewData if the default view is a Publish view.
													</li>
													<li>If the boolean is false, activating a view resets the display settings as predefined programmatically on the view, whatever 
													the user might manually change. The settings have A3DPDF3DAnnotData values and are all the same for native views or the automatic
													view; and they have A3DPDFViewData values for Publish views, which can be potentially different for each view.
													</li>
													</ul>
													Warning: all the display behaviors might be affected by a bug in Adobe Reader when the toolbar is not displayed. For a full control
													of display settings, it might be better to always display the toolbar. If not, unexpected rendering might be observed. */
	A3DPDFEAnimationStyle m_eAnimationStyle;	/*!< The animation style. */
	A3DInt32 m_iNumberOfAnimations;				/*!< Number of animations. \version 6.0 */
	A3DPDFAnimation** m_ppAnimations;			/*!< Animations. \version 6.0 */
	A3DBool m_bChangePMIColor;					/*!< If this value is true, the color of the markup in the artwork will be set to m_adRGB. If this value is false, the markup keeps the color it has in the CAD file, or the default color if it does not have a defined color. \version 8.0 */
	A3DPDFRgbColorData m_sPMIColor;				/*!< Color of the markup in the artwork if m_bChangePMIColor is set to true. \version 8.0 */
} A3DPDF3DArtworkData;

/*!
\ingroup a3d_publish_view_module
\brief Structure to define settings for the cross sections display
\version 8.1
*/
typedef struct 
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DBool m_bIsCuttingPlaneVisible;				/*!< Visibility of the cutting plane. */
	A3DDouble m_dOpacity;							/*!< Opacity of the cutting plane, between 0 and 1. */
	A3DPDFRgbColorData m_sCuttingPlaneColor;		/*!< Color of the cutting plane. */
	A3DBool m_bIsIntersectionVisible;				/*!< Visibility of the intersection of the cutting plane with any 3D geometry. */
	A3DPDFRgbColorData m_sIntersectionColor;		/*!< Color of the intersection of the cutting plane, if visible. */
	A3DBool m_bAddSectionCaps;						/*!< If true, show the capping faces. */
} A3DPDFSectionDisplayData;


/*!
\ingroup a3d_publish_3Dartwork_module
\brief A3DPDF3DArtworkData2 structure
\version 8.1
*/
typedef struct 
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DPDF3DStream *m_pStream;						/*!< Specifies the 3D stream object created from the 3D data. */
	A3DUTF8Char* m_pcJavaScriptFileName;			/*!< A JavaScript file to store on the 3D Annot. */
	
	A3DBool m_bActivatePMICrossHighlight;			/*!<
														If true, some JavaScript code is generated so that when the user clicks on a markup, the associated surface is highlighted. 
														Only works with Acrobat 11 and later. */
	A3DBool m_bAddPMISemanticInformation;			/*!< If true, the information on semantic PMI is added as nodes attributes on the model tree. */
	A3DBool m_bKeepNativeDefaultView;				/*!<
														If true, if there's a default view in the PRC modelfile: the default view in the resulting PDF will be that one, no matter 
														if other default views are defined at PDF level.
														In other situations (no default view in the PRC modelfile; or the boolean is false): a default view is defined at the PDF level.
														A default view at the PDF level means a view programmatically created using \ref A3DPDFViewCreate, or a default view 
														automatically created by HOOPS Publish if no default view is already defined. 
														<br>This boolean is not used if the 3D stream is created with \ref A3DPDF3DStreamCreateFromFile. */
	A3DBool m_bUseRuntimeDisplaySettings;			/*!<
														This boolean controls which display settings (rendering style, background color and lighting) are applied to the 3D annotation
														when a view is activated. 
														<ul>
														<li>If the boolean is true, all the views have initially the <b>default display settings</b>, then if the end-user manually changes
														the settings, this change affects all the views except the 'home' view (the view associated to the 'home' icon in Adobe Reader)
														for which it resets to the <b>default display settings</b>.
														The <b>default display settings</b> are the ones assigned to the default view: A3DPDF3DAnnotData values if the default view is a
														native or the automatic view, and A3DPDFViewData if the default view is a Publish view.
														</li>
														<li>If the boolean is false, activating a view resets the display settings as predefined programmatically on the view, whatever 
														the user might manually change. The settings have A3DPDF3DAnnotData values and are all the same for native views or the automatic
														view; and they have A3DPDFViewData values for Publish views, which can be potentially different for each view.
														</li>
														</ul>
														Warning: all the display behaviors might be affected by a bug in Adobe Reader when the toolbar is not displayed. For a full control
														of display settings, it might be better to always display the toolbar. If not, unexpected rendering might be observed. */
	A3DPDFEAnimationStyle m_eAnimationStyle;		/*!< The animation style. */
	A3DInt32 m_iNumberOfAnimations;					/*!< Number of animations. \version 6.0 */
	A3DPDFAnimation** m_ppAnimations;				/*!< Animations. \version 6.0 */
	A3DBool m_bChangePMIColor;						/*!< If the boolean is true, the color of the markups in the artwork will be set to m_adRGB; otherwise, it will remain like it already was. \version 8.0 */
	A3DPDFRgbColorData m_sPMIColor;					/*!< Color of the markups in the artwork if m_bChangePMIColor is set to true. \version 8.0 */
	A3DPDFSectionDisplayData m_sDisplaySectionData;	/*!< Settings for the cross sections display. \version 8.1 */
	A3DBool m_bAddAdditionalGeometry;				/*!< If true, the curves related to edges highlighted by a markup will be computed (only if m_bActivatePMICrossHighlight is set to true. \version 9.1 */
} A3DPDF3DArtworkData2;


/*!
\ingroup a3d_publish_3Dartwork_module
\brief Function to create the 3D Artwork of the 3D Annot.

The 3D Artwork object is primarily created with this function, and it should be stored on the 3D Annot through the structure \ref A3DPDF3DAnnotData.

\param [in,out] pDoc The Document object to work with.
\param [in] p3DArtworkData The 3D Artwork parameters.
\param [out] pp3DArtwork The 3D Artwork object created.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDF3DArtworkCreate, (A3DPDFDocument* pDoc, const A3DPDF3DArtworkData* p3DArtworkData, A3DPDF3DArtwork** pp3DArtwork));

/*!
\ingroup a3d_publish_3Dartwork_module
\brief Function to create the 3D Artwork of the 3D Annot.

The 3D Artwork object is primarily created with this function, and it should be stored on the 3D Annot through the structure \ref A3DPDF3DAnnotData.

\param [in,out] pDoc The Document object to work with.
\param [in] p3DArtworkData The 3D Artwork parameters.
\param [out] pp3DArtwork The 3D Artwork object created.
\return \ref A3D_SUCCESS \n
\version 8.1
*/
A3D_API (A3DStatus, A3DPDF3DArtworkCreate2, (A3DPDFDocument* pDoc, const A3DPDF3DArtworkData2* p3DArtworkData, A3DPDF3DArtwork** pp3DArtwork));

/*!
\ingroup a3d_publish_3Dannot_module
\brief A3DPDF3DAnnotData structure: options for the 3D Annot behavior in the PDF
\version 4.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;					/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DPDFEActivateWhen m_eActivateWhen;		/*!< Option to specify when the 3D Annot should be activated. */
	A3DPDFEDesactivateWhen m_eDesactivateWhen;	/*!< Option to specify when the 3D Annot should be deactivated. */
	A3DBool m_bShowToolbar;						/*!< Option to show or not show the 3D toolbar when the 3D Annot is activated. */
	A3DBool m_bOpenModelTree;					/*!< Option to show or not show the 3D model tree when the 3D Annot is activated. */
	A3DBool m_bDisableInteractivity;			/*!< Option to enable or disable the interactivity on the 3D scene. If disabled, only JavaScript actions can control the 3D Annot. */
	A3DInt32 m_iAppearanceBorderWidth;			/*!< Border width in points. */
	A3DBool m_bTransparentBackground;			/*!<
													If true, the background of the 3D window is transparent. 
													Warning, a transparent background leads to Adobe bugs in Adobe Reader or Acrobat:
													the 3D Annot can't be printed, and the form fields are blinking when a field is triggered. */
	A3DPDFRgbColorData m_sBackgroundColor;		/*!<
													Display setting - background color of the 3D scene. Incompatible with \ref m_bTransparentBackground. 
													See \ref A3DPDF3DArtworkData::m_bUseRuntimeDisplaySettings to understand how this setting is applied. */
	A3DPDFELighting m_eLighting;				/*!< Display setting - lighting of the 3D scene. See \ref A3DPDF3DArtworkData::m_bUseRuntimeDisplaySettings to understand how this setting is applied. */
	A3DPDFERenderingStyle m_eRenderingStyle;	/*!< Display setting - rendering style of the 3D scene. See \ref A3DPDF3DArtworkData::m_bUseRuntimeDisplaySettings to understand how this setting is applied. */
	A3DPDF3DArtwork *m_p3DArtwork;				/*!< Specifies the 3D Artwork object which contains the 3D definition. */
	A3DPDFImage* m_pPosterImage;				/*!<
													Specifies a poster image to be displayed when the 3D Annot is not activated. 
													If null, a poster is automatically created from the default view. To disable this automatic generation of poster, 
													we advise to specify a blank image file. */
	A3DUTF8Char* m_pcName;						/*!< Name of the 3D Annot. */
} A3DPDF3DAnnotData;


/*!
\ingroup a3d_publish_3Dannot_module
\brief Function to create a 3D Annotation object

The 3D Annotation object is primarily created with this function, and it should be inserted on the page with the functions \ref A3DPDFPageInsert3DAnnot or \ref A3DPDFPageFieldSet3DAnnot.

\param [in,out] pDoc The Document object to work with.
\param [in] p3DAnnotData The 3D Annot parameters.
\param [out] pp3DAnnot The 3D Annot object created.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDF3DAnnotCreate, (A3DPDFDocument* pDoc, const A3DPDF3DAnnotData* p3DAnnotData, A3DPDF3DAnnot** pp3DAnnot));

/*!
\ingroup a3d_publish_page_module
\brief Function to insert a 3D Annot in a page

Insert a 3D Annot object on the page. 
Note: starting with HOOPS Publish 1.10, several 3D Annots can be stored on a page.

\param [in,out] pPage The Page object to work with.
\param [in] p3DAnnot The 3D Annot to insert on the page.
\param [in] pRectData The rectangle to specify the position on the page.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageInsert3DAnnot, (A3DPDFPage* pPage, const A3DPDF3DAnnot* p3DAnnot, const A3DPDFRectData* pRectData));

/*!
\ingroup a3d_publish_page_module
\brief Function to replace the form field specified with a 3D Annot object

Note: starting with HOOPS Publish 1.10, several 3D Annots can be stored on a page.

\param [in,out] pPage The Page object to work with.
\param [in] pcFieldName The name of the form field. Only Acroform fields are supported.
\param [in] p3DAnnot The 3D Annot to set.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageFieldSet3DAnnot, (A3DPDFPage* pPage, const A3DUTF8Char* pcFieldName, const A3DPDF3DAnnot* p3DAnnot));

/*!
\ingroup a3d_publish_page_module
\brief Function to set the text of a text form field

\param [in,out] pPage The Page object to work with.
\param [in] pcFieldName The name of the form field. Only Acroform fields are supported.
\param [in] pcValue The value to set to the text field. Text fields set as multiline can contain carriage return characters, they must be '\\r'.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageFieldTextSetValue, (A3DPDFPage* pPage, const A3DUTF8Char* pcFieldName, const A3DUTF8Char* pcValue));

/*!
\ingroup a3d_publish_page_module
\brief Function to set the label of a button form field

\param [in,out] pPage The Page object to work with.
\param [in] pcFieldName The name of the button form field. Only Acroform fields are supported.
\param [in] pcValue The label to set to the field.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageFieldButtonSetLabel, (A3DPDFPage* pPage, const A3DUTF8Char* pcFieldName, const A3DUTF8Char* pcValue));

/*!
\ingroup a3d_publish_page_module
\brief Function to set the icon of a button form field

The image is defined from a \ref A3DPDFImage object. It is always scaled non-proportionally, which means always adapted and stretched
to the size of the field. That way, the members m_iWidth and m_iHeight of \ref A3DPDFImageData are not used by this function.

\param [in,out] pPage The Page object to work with.
\param [in] pcFieldName The name of the form field. Only Acroform fields are supported.
\param [in] pImage The image to store on the button field.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageFieldButtonSetIcon, (A3DPDFPage* pPage, const A3DUTF8Char* pcFieldName, const A3DPDFImage* pImage));

/*!
\ingroup a3d_publish_page_module
\brief Function to add an item to a form field of type list

\param [in,out] pPage The Page object to work with.
\param [in] pcFieldName The name of the form field. Only Acroform fields are supported.
\param [in] pcItemValue The item string which will be visible to the user in the list field.
\param [in] pcItemExportValue The export value for the item. This value acts as a 'symbolic value' for the item.
\return \ref A3D_SUCCESS \n
\version 4.3
*/
A3D_API (A3DStatus, A3DPDFPageFieldListAddItem, (A3DPDFPage* pPage, const A3DUTF8Char* pcFieldName, const A3DUTF8Char* pcItemValue, const A3DUTF8Char* pcItemExportValue));


/*!
\ingroup a3d_publish_page_module
\brief Function to set the visibility of a form field

\param [in,out] pPage The Page object to work with.
\param [in] pcFieldName The name of the form field. Only Acroform fields are supported.
\param [in] bIsVisible Specifies if the field should be visible or not.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageFieldSetVisibility, (A3DPDFPage* pPage, const A3DUTF8Char* pcFieldName, const A3DBool bIsVisible));


/*!
\ingroup a3d_publish_page_module
\brief This method was deprecated in HOOPS Publish 1.1. Use \ref A3DPDFPageFieldSetActionJavascriptFromString instead

Function to attach JavaScript to a form field. The JavaScript is defined in a file.
\param [in,out] pPage The Page object to work with.
\param [in] pcFieldName The name of the form field. Only Acroform fields are supported.
\param [in] pcFileName The path of a file containing a JavaScript.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageFieldSetActionJavascriptFromFile, (A3DPDFPage* pPage, const A3DUTF8Char* pcFieldName, const A3DUTF8Char* pcFileName));

/*!
\ingroup a3d_publish_page_module
\brief Function to attach JavaScript to a form field. The JavaScript is defined as a string.

The goal of this function is to define a JavaScript action to be launched on an event. The action event is different depending on the type of the field.
For fields of type:
<ul>
<li> dropdown list: the action is the selection of a list item.</li>
<li> listbox list: the action is the selection of a list item.</li>
<li> button: the action is the button pushed.</li>
</ul>
\param [in,out] pPage The Page object to work with.
\param [in] pcFieldName The name of the form field. Only Acroform fields are supported.
\param [in] pcJavascriptString The string which contains the JavaScript.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFPageFieldSetActionJavascriptFromString, (A3DPDFPage* pPage, const A3DUTF8Char* pcFieldName, const A3DUTF8Char* pcJavascriptString));



/*!
\ingroup a3d_publish_page_module
\brief Set of events that can trigger the execution of an action.

The kA3DPDFEventPageOpened and kA3DPDFEventPageClosed event on an annotation object have a similar function in the page object. 
However, associating these triggers with annotations allows annotation objects to be self-contained.
The kA3DPDFEventPageVisible and kA3DPDFEventPageInvisible types allow a distinction between pages that are open 
and pages that are visible. At any one time, while more than one page may be visible, depending on the page layout.
\version 9.0
*/
typedef enum
{
	kA3DPDFEventPageOpened = 0,		/*!< An action that shall be performed when the page, or the page containing the annotation, is opened. */
	kA3DPDFEventPageClosed = 1,		/*!< An action that shall be performed when the page, or the page containing the annotation, is closed. */
	kA3DPDFEventPageVisible = 2,	/*!< An action that shall be performed when the page containing the annotation becomes visible. */
	kA3DPDFEventPageInvisible = 3,	/*!< An action that shall be performed when the page containing the annotation is no longer visible in the conforming reader’s user interface. */
	kA3DPDFEventFieldEnter = 4,		/*!< An action that shall be performed when the cursor enters the annotation’s active area. */
	kA3DPDFEventFieldExit = 5,		/*!< An action that shall be performed when the cursor exits the annotation’s active area. */
	kA3DPDFEventFieldMouseDown = 6,	/*!< An action that shall be performed when the mouse button is pressed inside the annotation’s active area. */
	kA3DPDFEventFieldMouseUp = 7,	/*!< An action that shall be performed when the mouse button is released inside the annotation’s active area. */
	kA3DPDFEventFieldFocusIn = 8,	/*!< An action that shall be performed when the annotation receives the input focus. */
	kA3DPDFEventFieldFocusOut = 9,	/*!< An action that shall be performed when the annotation loses the input focus. */
	kA3DPDFEventDocWillClose = 10,	/*!< An action that shall be performed before closing a document. */
	kA3DPDFEventDocWillSave = 11,	/*!< An action that shall be performed before saving a document. */
	kA3DPDFEventDocDidSave = 12,	/*!< An action that shall be performed after saving a document. */
	kA3DPDFEventDocWillPrint = 13,	/*!< An action that shall be performed before printing a document. */
	kA3DPDFEventDocDidPrint = 14,	/*!< An action that shall be performed after printing a document. */
	kA3DPDFEventFieldKeyStroke = 15
} A3DPDFEEventActionType;

/*!
\ingroup a3d_publish_page_module
\brief Function to define a javaScript action to an event triggered on the document. The JavaScript is defined as a string.

The goal of this function is to define a JavaScript action to be launched on an event triggered on the document level.
\param [in] pDoc The Document object to work with.
\param [in] eEventActionType The action type. 
Only \ref kA3DPDFEventDocWillClose,  \ref kA3DPDFEventDocWillSave \ref kA3DPDFEventDocDidSave \ref kA3DPDFEventDocWillPrint and \ref kA3DPDFEventDocDidPrint are relevant at document level.
\param [in] pcJavascriptString The string which contains the JavaScript.
\return \ref A3D_SUCCESS \n
\version 9.0
*/
A3D_API(A3DStatus, A3DPDFDocumentSetActionJavascript, (A3DPDFDocument* pDoc, const A3DPDFEEventActionType eEventActionType, const A3DUTF8Char* pcJavascriptString));

/*!
\ingroup a3d_publish_page_module
\brief Function to attach JavaScript to a form field. The JavaScript is defined as a string.

The goal of this function is to define a JavaScript action to be launched on an event. The action event is different depending on the type of the field.
For fields of type:
<ul>
<li> dropdown list: the action is the selection of a list item.</li>
<li> listbox list: the action is the selection of a list item.</li>
<li> button: the action is the button pushed.</li>
</ul>
\param [in,out] pPage The Page object to work with.
\param [in] pcFieldName The name of the form field. Only Acroform fields are supported.
\param [in] eEventActionType The action type. Only \ref kA3DPDFEventPageOpened and \ref kA3DPDFEventPageClosed are relevant at page level.
\param [in] pcJavascriptString The string which contains the JavaScript.
\return \ref A3D_SUCCESS \n
\version 9.0
*/
A3D_API(A3DStatus, A3DPDFPageFieldSetActionJavascript, (A3DPDFPage* pPage, const A3DUTF8Char* pcFieldName, const A3DPDFEEventActionType eEventActionType, const A3DUTF8Char* pcJavascriptString));

/*!
\ingroup a3d_publish_page_module
\brief Function to define a javaScript action to an event triggered on the page. The JavaScript is defined as a string.

The goal of this function is to define a JavaScript action to be launched on an event triggered on the page level. 
\param [in] pPage The Page object to work with.
\param [in] eEventActionType The action type. Only \ref kA3DPDFEventPageOpened and \ref kA3DPDFEventPageClosed are relevant at page level.
\param [in] pcJavascriptString The string which contains the JavaScript.
\return \ref A3D_SUCCESS \n
\version 9.0
*/
A3D_API(A3DStatus, A3DPDFPageSetActionJavascript, (A3DPDFPage* pPage, const A3DPDFEEventActionType eEventActionType, const A3DUTF8Char* pcJavascriptString));

/*!
\ingroup a3d_publish_page_module
\brief Function to define a javaScript action to an event triggered on an annotation. The JavaScript is defined as a string.

The goal of this function is to define a JavaScript action to be launched on an event triggered on an annotation.
\param [in] pPage The Page object to work with.
\param [in] p3DAnnot The 3D annot object to work with.
\param [in] eEventActionType The action type.
\param [in] pcJavascriptString The string which contains the JavaScript.
\return \ref A3D_SUCCESS \n
\version 9.0
*/
A3D_API(A3DStatus, A3DPDF3DAnnotSetActionJavascript, (A3DPDFPage* pPage, A3DPDF3DAnnot* p3DAnnot, const A3DPDFEEventActionType eEventActionType, const A3DUTF8Char* pcJavascriptString));


/*!
\ingroup a3d_publish_page_module
\brief Field type
\version 6.0
*/
typedef enum
{
	kA3DPDFText=0,			/*!< Field of type 'Text field'. */
	kA3DPDFButton=1,		/*!< Field of type 'Button'. */
	kA3DPDFDropDown,		/*!< Field of type 'Drop-down list' (also named 'Combo box'). */
	kA3DPDFListBox,			/*!< Field of type 'List Box'. */
	kA3DPDFCheckBox,		/*!< Field of type 'Check Box'. */
	kA3DPDFRadioButton,		/*!< Field of type 'Radio Button'. */
	kA3DPDFDigitalSignature,/*!< Field of type 'Digital Signature'. */
	kA3DPDFBarCode			/*!< Field of type 'Barcode'. Not used by Publish. */
} A3DPDFEFieldType;

#define MAX_FIELD_NAME 100

/*!
\ingroup a3d_publish_page_module
\brief A3DPDF3DFieldData structure
\version 6.0
*/
typedef struct
{
	A3DUns16 m_usStructSize;				/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char m_acName[MAX_FIELD_NAME];	/*!< Name of the field. This name can be used in Field functions (prefixed with 'A3DPDFPageField'). */
	A3DPDFRectData m_sRect;					/*!< The rectangle that specifies the position on the page. */
	A3DPDFEFieldType m_eType;				/*!< Type of the field. */
} A3DPDFFieldData;

/*!
\ingroup a3d_publish_page_module
\brief Function to retrieve the fields of a PDF page. The fields supported are only form fields created with Acrobat. 
LiveCycle Designer fields (XFA) are not supported.

\param [in] pPage The Page object to work with.
\param [out] piNbFields The number of fields.
\param [out] pppFields The array of pointer on fields objects created.
\return \ref A3D_SUCCESS \n
\version 6.0
*/
A3D_API (A3DStatus, A3DPDFPageGetFields, (A3DPDFPage* pPage, A3DInt32* piNbFields, A3DPDFField*** pppFields));


/*!
\ingroup a3d_publish_page_module
\brief Function to retrieve useful information regarding a field of a document

\param [in] pField The Field object to work with.
\param [in,out] pFieldData Data structure completed by the function. Contains the attributes of the field.
\version 6.0
*/
A3D_API (A3DStatus, A3DPDFFieldGetInformation, (A3DPDFField* pField, A3DPDFFieldData *pFieldData));



/*!
\defgroup a3d_publish_3Dstream_module 3D Stream Module
\ingroup a3d_publish_3Dannot_module
\brief Adds a 3D Stream in a 3D annot

This module describes the functions and structures that allow you to add a 3D source in a 3D Annot.
*/


/*!
\ingroup a3d_publish_3Dstream_module
\brief Function to create a PRC Stream from a Model File

The 3D Stream object is primarily created with this function, and it should be stored on the 3D Artwork through the structure \ref A3DPDF3DArtworkData.
This function saves the modelfile in a PRC format, and creates a 3D Stream object from this data.

\param [in] pDoc The Document object to work with.
\param [in] pModelFile The Document object to work with.
\param [in] pParamsExportData The PRC export parameters.
\param [out] pp3DStream The 3DStream object created.
\param [in,out] ppPrcWriteHelper Used to get PRC data such as unique identifiers of PRC nodes.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDF3DStreamCreateFromModelFileAsPRC, (A3DPDFDocument* pDoc,
															 A3DAsmModelFile* pModelFile, 
															 const A3DRWParamsExportPrcData* pParamsExportData, 
															 A3DPDF3DStream** pp3DStream,
															 A3DRWParamsPrcWriteHelper** ppPrcWriteHelper));

/*!
\ingroup a3d_publish_3Dstream_module
\brief Function to create a U3D Stream from Model File

The 3D Stream object is primarily created with this function, and it should be stored on the 3D Artwork through the structure \ref A3DPDF3DArtworkData.
This function saves the modelfile in a U3D format, and creates a 3D Stream object from this data.

\param [in] pDoc The Document object to work with.
\param [in] pModelFile The Document object to work with.
\param [in] pParamsExportData The U3D export parameters.
\param [out] pp3DStream The 3DStream object created.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDF3DStreamCreateFromModelFileAsU3D, (A3DPDFDocument* pDoc,
															 A3DAsmModelFile* pModelFile, 
															 const A3DRWParamsExportU3DData* pParamsExportData, 
															 A3DPDF3DStream** pp3DStream));
/*!
\ingroup a3d_publish_3Dstream_module
\brief Function to create a Stream from a file

\param [in] pDoc The Document object to work with.
\param [in] pcFilePath The path of a PRC or U3D file.
\param [in] bIsPRC Specifies the format of the data (true is for PRC, false if for U3D).
\param [out] pp3DStream The 3DStream object created.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDF3DStreamCreateFromFile, (A3DPDFDocument* pDoc,
												   A3DUTF8Char* pcFilePath,
												   const bool bIsPRC,
												   A3DPDF3DStream** pp3DStream));


/*!
\ingroup a3d_publishpdf_module
\brief A3DPDFSnapshotOptionsData structure: options for the snapshot (poster) generation
\version 4.1
*/
typedef struct 
{
	A3DUns16 m_usStructSize;/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DInt32 m_iWidth;		/*!< Width in pixels. */
	A3DInt32 m_iHeight;		/*!< Height in pixels. */
	A3DPDFView* m_pView;	/*!< The view to be activated before the snapshot is generated. */
} A3DPDFSnapshotOptionsData;

/*!
\ingroup a3d_publishpdf_module
\brief Function to create the poster of the 3D Annotation

\param [in] pModelFile The modelfile where is defined the 3D data.
\param [in] pSnapshotOptionsData The snapshot parameters.
\param [in] pcOutputFilename Path to the file name to generate.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFMakeSnapshotFromModelFile, (A3DAsmModelFile* pModelFile, 
													  const A3DPDFSnapshotOptionsData* pSnapshotOptionsData, 
													  const A3DUTF8Char* pcOutputFilename));


/*!
\defgroup a3d_publish_view_module View Module
\ingroup a3d_publishpdf_module
\brief View functions

This module describes the functions and structures that allow you to define 3D views on a 3D Annot.
*/


/*!
\ingroup ingroup a3d_publish_view_module
\brief Projection mode: type of projection
\version 6.0
*/
typedef enum
{
	kA3DPDFOrthographicMode=0,		/*!< Orthographic projection. */
	kA3DPDFPerspectiveMode=1,		/*!< Perspective projection. */
} A3DPDFEProjectionMode;

/*!
\ingroup a3d_publish_view_module
\brief Structure to define a Camera View
\version 4.1
*/
typedef struct 
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcInternalName;					/*!< Internal name of the view. */
	A3DUTF8Char* m_pcExternalName;					/*!< External name of the view. This name is used in JavaScript functions. */
	A3DVector3dData m_sPosition;					/*!< Camera position. */
	A3DVector3dData m_sTarget;						/*!< Target position where the camera is looking at. */
	A3DVector3dData m_sUpVector;					/*!<
														Camera up vector. It should be defined so that it is perpendicular to the vector created between the camera and target position. 
														A non-perpendicular up vector results in a view which is tilting when it is activated in the Adobe PDF Reader. */
	A3DDouble m_dZoomFactor;						/*!<
														This parameter is only applicable for orthographic cameras. 
														It specifies the part of the scene that can be visualized and inversely acts as a zoom factor with the following 
														relationship: [zoomfactor=1/2*view_size], with view_size as the smallest size of the viewable part in the X or Y direction. */
	A3DBool m_bIsDefault;							/*!<
														Specifies that this view should be the default view (the view used when the 3D is activated). 
														Only one view should be defined by default. */
	A3DPDFRgbColorData m_sViewBackgroundColor;		/*!< Display setting - background color for the view. */
	A3DPDFELighting m_eViewLighting;				/*!< Display setting - lighting for the view. */
	A3DPDFERenderingStyle m_eViewRenderingStyle;	/*!< Display setting - rendering style for the view. */
	A3DPDFEProjectionMode m_eProjectionMode;		/*!< Camera projection mode: orthographic or perspective. */	
	A3DDouble m_dFieldOfView;						/*!< This parameter is only applicable for perspective cameras. It specifies the field of view as an angle in degrees. */
} A3DPDFViewData;






/*!
\ingroup a3d_publish_view_module
\brief Function to create a camera view

The View object is primarily created with this function, and it should be stored in the 3D Artwork with the function \ref A3DPDF3DArtworkAddView.

\param [in,out] pDoc The Document object to work with.
\param [in] pViewData The view parameters.
\param [out] ppView The View object created.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFViewCreate, (A3DPDFDocument* pDoc, const A3DPDFViewData* pViewData, A3DPDFView** ppView));

/*!
\ingroup a3d_publish_3Dartwork_module
\brief Adds a view on the 3D Annot

The view is a PDF object and can be activated with PDF actions.
\param [in,out] p3DArtwork The 3D Artwork object to work with.
\param [in] pView The View to be stored on the 3D Annot.

\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDF3DArtworkAddView, (A3DPDF3DArtwork* p3DArtwork, const A3DPDFView* pView));

/*!
\ingroup a3d_publish_3Dartwork_module
\brief Returns the views objects stored in the artwork.

The function returns an array of pointer on views objects. The views returned can be issued from native CAD file, or could have been created with \ref A3DPDF3DArtworkAddView function.
Alternatively if no default view is defined, HOOPS Publish automatically creates one. This automatic view is returned at the end of the array.
\param [in] p3DArtwork The 3D Artwork object to work with.
\param [out] puiNbViews The size of the following array of views.
\param [out] pppViews The array of pointer on views objects created.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDF3DArtworkGetViews, (A3DPDF3DArtwork* p3DArtwork, A3DUns32* puiNbViews,  A3DPDFView*** pppViews));


/*!
\ingroup a3d_publish_view_module
\brief Returns the identifier of the view

The identifier may be used by JavaScript or PDF actions to activate a view. It can also be used to generate poster.
The function returns a string.

\param [in] pView The View object to work with. This object can be retrieved using the function \ref A3DPDF3DArtworkGetViews
\param [out] ppcViewId The identifier as a string.
\return \ref A3D_SUCCESS \n
\version 4.1
*/
A3D_API (A3DStatus, A3DPDFViewGetExternalName, (A3DPDFView* pView, A3DUTF8Char** ppcViewId));

/*!
\ingroup a3d_publish_3Dartwork_module
\brief Get the bounding sphere of the default view of the 3D Artwork

\param [in] p3DArtwork The 3D Artwork object to work with
\param [out] pdRadius The radius of the bounding sphere.
\param [out] pCenter The center of the bounding sphere.

\return \ref A3D_SUCCESS \n
\version 5.1
*/
A3D_API (A3DStatus, A3DPDF3DArtworkGetBoundingSphere, (A3DPDF3DArtwork* p3DArtwork, A3DDouble* pdRadius, A3DVector3dData* pCenter)); 


/*!
\defgroup a3d_publish_animation_module Animation Module
\ingroup a3d_publishpdf_module
\brief Animation functions

This module describes the functions and structures that allow you to define 3D animations on a 3D Annot.
*/

/*!
\ingroup a3d_publish_animation_module
\brief Structure to define a transformation
\version 6.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_adMatrix[16];						/*!< Entity position, absolute coordinates. */
} A3DPDFAnimTransformationData;

/*!
\ingroup a3d_publish_animation_module
\brief Structure grouping the appearance characteristics
\version 6.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DPDFRgbColorData m_sColor;					/*!< Color of the entity. */
	A3DDouble m_dOpacity;							/*!< From 0.0 (transparent) to 1.0 (opaque) */
	A3DPDFERenderingStyle m_eRenderingStyle;		/*!< Rendering style. */
} A3DPDFAnimAppearanceData;

/*!
\ingroup a3d_publish_animation_module
\brief Structure grouping the camera characteristics
\version 6.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DVector3dData m_sPosition;					/*!< Camera position. */
	A3DVector3dData m_sTarget;						/*!< Target position where the camera is looking at. */
	A3DVector3dData m_sUpVector;					/*!<
														Camera up vector. It should be defined so that it is perpendicular to the vector created between the camera and target position. 
														A non-perpendicular up vector results in a view which is tilting when it is activated in the Adobe PDF Reader. */
	A3DDouble m_dZoomFactor;						/*!<
														This parameter is only applicable for orthographic cameras. 
														It specifies the part of the scene that can be visualized and inversely acts as a zoom factor with the following 
														relationship: [zoomfactor=1/2*view_size], with view_size as the smallest size of the viewable part in the X or Y direction. */
	A3DPDFEProjectionMode m_eMode;					/*!< Camera projection mode: orthographic or perspective. Assuming that it won't change during the animation. */
	A3DDouble m_dFieldOfView;						/*!< This parameter is only applicable for perspective cameras. It specifies the field of view as an angle in degrees. */
} A3DPDFAnimCameraData;

/*!
\defgroup a3d_publish_animation_interpolbits Bit Field to indicate which data must be interpolated. 
\ingroup a3d_publish_animation_module
\version 6.1

@{
*/
#define kA3DPDFInterpolateTransformationMatrix		0x00000001	/*!< Transformation matrix is interpolated. */ 
#define kA3DPDFInterpolateAppearanceColor			0x00000002	/*!< Color is interpolated. */ 
#define kA3DPDFInterpolateAppearanceTransparency	0x00000004	/*!< Transparency is interpolated. */ 
#define kA3DPDFInterpolateCamera					0x00000008	/*!< Camera is interpolated. */ 
/*!
@} <!-- end of a3d_publish_animation_interpolbits -->
*/

/*!
\ingroup a3d_publish_animation_module
\brief Structure to define a keyframe
\version 6.1
*/
typedef struct 
{
	A3DUns16 m_usStructSize;								/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dTime;										/*!< Time of the keyframe. Added to the time offset of the motion. */
	A3DPDFAnimTransformationData *m_psTransformationData;	/*!< Data concerning the transformation. */
	A3DPDFAnimAppearanceData *m_psAppearanceData;			/*!< Data concerning the appearance. */
	A3DPDFAnimCameraData *m_psCameraData;					/*!< Data concerning the camera. */
	A3DInt32 m_iInterpolationMask;							/*!< Bits which indicates which data must be interpolated.  \sa a3d_publish_animation_interpolbits */
} A3DPDFAnimKeyFrameData;

/*!
\ingroup a3d_publish_animation_module
\brief Function to create a keyframe

\param [in] pKeyFrameData The keyframe parameters.
\param [out] ppKeyFrame The keyframe object created.
\return \ref A3D_SUCCESS \n
\version 6.1
*/
A3D_API (A3DStatus, A3DPDFAnimKeyFrameCreate, (const A3DPDFAnimKeyFrameData* pKeyFrameData, A3DPDFAnimKeyFrame** ppKeyFrame));


/*!
\ingroup a3d_publish_animation_module
\brief Structure to define an animation motion
\version 6.1
\deprecated
*/
typedef struct 
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DInt32 m_iNumTargets;							/*!< Number of targets. */
	A3DMiscMarkupLinkedItem** m_ppTargets;			/*!< Targets of the motion: product occurence, part, markup. */
	A3DInt32 m_iNumKeyFrames;						/*!< Number of keyframes. */
	A3DPDFAnimKeyFrame **m_ppKeyFrames;				/*!< Array of keyframes. */
	A3DDouble m_dTimeOffset;						/*!< Time to start the first keyframe. */
	A3DBool m_bRepeat;								/*!< If true, the motion is repeated infinitely. */
} A3DPDFAnimMotionData;

/*!
\ingroup a3d_publish_animation_module
\brief Structure to define a target entity
\version 7.1
*/
typedef struct 
{
	A3DUns16 m_usStructSize;									/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DEntity *m_pTargetEntity;									/*!< Entity: product occurrence, part, markup. */
	A3DAsmProductOccurrence *m_pFatherProductOccurrence;		/*!< Father Product Occurrence of the target entity, NULL if the target is a product occurrence. */
} A3DPDFTargetEntityData;

/*!
\ingroup a3d_publish_animation_module
\brief Structure to define a target entity of a motion
\version 7.1
*/
A3D_API (A3DStatus, A3DPDFTargetEntityCreate, (const A3DPDFTargetEntityData* pTargetData, A3DPDFTargetEntity** ppTargetEntity));

/*!
\ingroup a3d_publish_animation_module
\brief Structure to define an animation motion. Replaces A3DPDFAnimMotionData.
\version 7.1
*/
typedef struct 
{
	A3DUns16 m_usStructSize;						/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DInt32 m_iNumTargets;							/*!< Number of targets. */
	A3DPDFTargetEntity** m_ppTargets;				/*!< Targets of the motion: product occurrence, part, markup. */
	A3DInt32 m_iNumKeyFrames;						/*!< Number of keyframes. */
	A3DPDFAnimKeyFrame **m_ppKeyFrames;				/*!< Array of keyframes. */
	A3DDouble m_dTimeOffset;						/*!< Time to start the first keyframe. */
	A3DBool m_bRepeat;								/*!< If true, the motion is repeated infinitely. */
} A3DPDFAnimMotionData2;

/*!
\ingroup a3d_publish_animation_module
\brief Function to create an animation motion

\param [in] pMotionData The motion parameters.
\param [out] ppAnimationMotion The motion object created.
\return \ref A3D_SUCCESS \n
\version 6.1
\deprecated Please use A3DPDFAnimMotionCreate2 instead.
*/
A3D_API (A3DStatus, A3DPDFAnimMotionCreate, (const A3DPDFAnimMotionData* pMotionData, A3DPDFAnimMotion** ppAnimationMotion));

/*!
\ingroup a3d_publish_animation_module
\brief Function to create an animation motion. Replaces A3DPDFAnimMotionCreate.

\param [in] pMotionData The motion parameters.
\param [out] ppAnimationMotion The motion object created.
\return \ref A3D_SUCCESS \n
\version 7.1
*/
A3D_API (A3DStatus, A3DPDFAnimMotionCreate2, (const A3DPDFAnimMotionData2* pMotionData, A3DPDFAnimMotion** ppAnimationMotion));

/*!
\ingroup a3d_publish_animation_module
\brief Structure to define an animation 
\version 6.1
*/
typedef struct 
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcName;								/*!< Name of the animation. */
	A3DInt32 m_iNumAnimationMotions;					/*!< Number of motions. */
	A3DPDFAnimMotion **m_ppAnimationMotions;			/*!< Array of motions. */
	A3DInt32 m_iFramesPerSecond;						/*!< Number of frames per second. */
} A3DPDFAnimationData;

/*!
\ingroup a3d_publish_animation_module
\brief Function to create an animation

\param [in] pAnimationData The animation parameters.
\param [out] ppAnimation The animation object created.
\return \ref A3D_SUCCESS \n
\return \ref A3DPDF_ANIMATION_NULL_MOTION if one or several motions are null.\n
\version 6.1
*/
A3D_API (A3DStatus, A3DPDFAnimationCreate, (const A3DPDFAnimationData* pAnimationData, A3DPDFAnimation** ppAnimation));


/*!
\ingroup a3d_publish_animation_module
\brief Debug function to edit the JavaScript stream corresponding to the animation data in a file. If bUseAnimationFile is set to false,
the 'standard' JavaScript of the animation will be created from the animation data. If true, the output file will be used instead of the animation data.
To use the new content, the code execution should be stopped after the call to this function, then the code modified, then the execution restarted.
This function must be called before A3DPDF3DAnnotCreate.
\param [in,out] p3DArtwork The artwork which contains the animation.
\param [in] pcJavascriptFile The path of the file in which the JavaScript will be outputted. The content of the file can be modified by the user.
\param [in] bUseAnimationFile If true, the modified content will be used to generate the final PDF file. 
\return \ref A3D_SUCCESS \n
\version 6.1
*/
A3D_API (A3DStatus, A3DPDF3DArtworkEditAnimationJavascript, (A3DPDF3DArtwork* p3DArtwork, A3DUTF8Char* pcJavascriptFile, A3DBool bUseAnimationFile));



/*!
\ingroup a3d_publish_animation_module
\brief Utility function to retrieve the targets from their names.
\param [in] pModelFile The model file which contains the targets.
\param [in] iNamesSize The number of names in the next array.
\param [in] ppNames The array of names.
\param [in] piIndexes If the targeted entity had sons, index of the son in the model file tree. Must be -1 if no sons are wanted.
\param [out] ppTargetEntities The targeted entities retrieved. If several entities in the model file tree have the same name, 
	all these entities are in the array.
\param [out] ppiDataSizes For each name, the number of found entities.
\return \ref A3D_ERROR if wrong parameters are given \n
\return \ref A3D_SUCCESS\n
\version 7.1
*/
A3D_API (A3DStatus, A3DPDFGetEntitiesFromName, (A3DAsmModelFile* pModelFile, 
												A3DInt32 iNamesSize,
												A3DUTF8Char** ppNames,
												A3DInt32* piIndexes,
												A3DPDFTargetEntity**** ppTargetEntities,
												A3DInt32** ppiDataSizes));


/*!
\ingroup a3d_publish_document_module
\brief Function to create a 'standard' view carousel and position it in the PDF document.
The PDF document must contain the buttons for the views and the buttons to go to the next and the previous view.
\param [in,out] pDoc The document which will contain the carousel.
\param [in] pPage The page where the carousel will be put.
\param [in] pAnnot The annotation which contains the views of the carousel. 
\param [in] pModelFile The model file corresponding with the annotation. 
\param [in] iNbButtons The number of buttons in the ppButtonsNames array.
\param [in] ppButtonsNames The names of the view buttons in the pdf file. The size of this array should be iNbButtonsRows*iNbButtonsCols.
\param [in] pPreviousButtonName The name of the button to press to scroll the carousel to previous views.
\param [in] pNextButtonName The name of the button to press to scroll the carousel to next views.
\param [in] iNbViews If equal to 0, all the views of the model file will be used, in the order they are found in the model file.
	If superior than 0, the number of the views of the next parameter.
\param [in] ppViews If NULL, all the views of the model file will be used.
	If not NULL, ppViews must contain the views that will be used for the carousel.
\param [in] ppImages If NULL, the images are automatically created from the views.
	If not NULL, ppImages must contain the images that will be used for the views. In that case, the size of the array 
	should be the same as the size of ppViews parameter.
\param [in] iScrollStep This is the number of buttons icons scrolled. 
	If = iNbButtons, the carousel scrolls the icons by page (all the icons are replaced in the carousel). 
	If = the number of rows, the icons are scrolled by rows. 
	If = the number of columns, the icons are scrolled by columns. 
	If = 1, the carousel scrolls the icons one by one (all the icons are shifted of 1 increment in the carousel).
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFDefineViewCarousel, (A3DPDFDocument* pDoc, 
											   A3DPDFPage* pPage, 
											   A3DPDF3DAnnot* pAnnot,
											   A3DAsmModelFile* pModelFile, 
											   A3DInt32 iNbButtons,
											   A3DUTF8Char** ppButtonsNames,
											   A3DUTF8Char* pPreviousButtonName,
											   A3DUTF8Char* pNextButtonName,
											   A3DInt32 iNbViews,
											   A3DPDFView** ppViews,
   											   A3DPDFImage** ppImages,
											   A3DInt32 iScrollStep));



/*!
\ingroup a3d_publish_page_module
\brief Button flags
\version 7.2
*/
typedef enum
{
	kA3DPDFVisible,			/*!< The button is visible and printable. */ 
	kA3DPDFHidden,			/*!< The button is hidden and not printable. */ 
	kA3DPDFVisibleNoPrint,	/*!< The button is visible but not printable. */
	kA3DPDFHiddenPrintable,	/*!< The button is hidden but printable. */
} A3DPDFEFormField;

/*!
\ingroup a3d_publish_page_module
\brief Orientation of the text
\version 7.2
*/
typedef enum
{
	kA3DPDFNormal,			/*!< The text has a standard orientation. */ 
	kA3DPDF90,				/*!< The button is turned 90&deg; from counter clockwise. */ 
	kA3DPDF180,				/*!< The button is turned 180&deg; from counter clockwise. */ 
	kA3DPDF270,				/*!< The button is turned 270&deg; from counter clockwise. */ 
} A3DPDFETextOrientation;

/*!
\ingroup a3d_publish_page_module
\brief Thickness of the border of the button
\version 7.2
*/
typedef enum
{
	kA3DPDFThin,			/*!< The border of the button is thin. */ 
	kA3DPDFMedium,			/*!< The border of the button is medium size. */ 
	kA3DPDFThick,			/*!< The border of the button is thin. */ 
} A3DPDFEThicknessBorder;

/*!
\ingroup a3d_publish_page_module
\brief Line style of the border of the button
\version 7.2
*/
typedef enum
{
	kA3DPDFSolid,
	kA3DPDFDashed,
	kA3DPDFBeveled,
	kA3DPDFInset,
	kA3DPDFUnderlined,
} A3DPDFELineStyleBorder;

/*!
\ingroup a3d_publish_page_module
\brief Position of the label of the button relative to its icon
\version 7.2
*/
typedef enum
{
	kA3DPDFLabelOnly,
	kA3DPDFIconOnly,
	kA3DPDFIconTopLabelBottom,
	kA3DPDFLabelTopIconBottom,
	kA3DPDFIconLeftLabelRight,
	kA3DPDFLabelLeftIconRight,
	kA3DPDFLabelOverIcon,
} A3DPDFELayoutTextIcon;

/*!
\ingroup a3d_publish_document_module
\brief Structure to define a button field
\version 7.2
*/
typedef struct 
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcName;								/*!< Name of the field (it serves as the field identifier, it should be unique in the document). */
	A3DUTF8Char* m_pcTooltip;							/*!<
															Displayed text that the hesitant user may find helpful in filling in the form field. 
															Tooltips appear when the pointer hovers briefly over the form field. */
	A3DPDFEFormField m_eFormField;						/*!< Specifies whether the form field can be seen, either on screen or in print. */
	A3DPDFETextOrientation m_eTextOrientation;			/*!< Orientation of the text inside the field. */
	A3DBool m_bIsReadOnly;								/*!< Defines if the field is editable. */
	A3DBool m_bIsRequired;								/*!< Defines if the field is required. */
	A3DBool m_bIsLocked;								/*!< If locked, prevents any further changes to any form field properties (in Acrobat 'Properties' dialog box). */	
	A3DBool m_bHasBorder;								/*!< If true, there is a border around the field. */
	A3DPDFRgbColorData m_sBorderColor;					/*!< Color of the border of the field (if any). */
	A3DPDFEThicknessBorder m_eThicknessBorder;			/*!< Thickness of the border. */
	A3DPDFELineStyleBorder m_eLineStyleBorder;			/*!< Line style of the border. */
	A3DBool m_bHasFillColor;							/*!< If true, the following field (m_sFillColor) is used. */
	A3DPDFRgbColorData m_sFillColor;					/*!< Color which the inside of the field will be filled with (if m_bHasFillColor is true). */
	A3DPDFRgbColorData m_sTextColor;					/*!< Color of the text. */
	A3DUTF8Char* m_pcFontName;							/*!<
															Font name of the text. 
		It should be the name of the font as appearing in Acrobat font list, but without spaces, and with style separated with a comma. 
		For example, 'Calibri Bold Italic' should be specified as "Calibri,BoldItalic" ; 
		or 'Century Gothic' should be specified as "CenturyGothic".
		Also, specific values exist for Adobe default fonts:
		eTimesRoman is "TiRo" ; eTimesItalic is  "TiIt" ; eTimesBold is "TiBo" ; eTimesBoldItalic is "TiBI" ;
		eHelvetica is "Helv" ; eHelveticaOblique is "HeOb" ; eHelveticaBold is "HeBo" ; eHelveticaBoldOblique is "HeBO" ;
		eCourier is "Cour" ; eCourierOblique is "CoOb" ; eCourierBold is "CoBo" ; eCourierBoldOblique is "CoBO". */
	A3DInt32 m_iFontSize; 								/*!< Size of the font. */
	A3DPDFELayoutTextIcon m_eLayoutTextIcon;			/*!< Position of the label of the button relative to its icon. */
	A3DPDFELinkHighlightMode m_eHighlightingMode;		/*!< Highlighting mode (the visual effect that shall be used when the mouse button is pressed or held down inside its active area). */
	A3DUTF8Char* m_pcLabel;								/*!< Label of the button. */
	A3DPDFImage* m_pImage;								/*!< The image to store on the button as icon. */
} A3DPDFButtonData;


/*!
\ingroup a3d_publish_page_module
\brief Function to create a button

The button is primarily created with this function, and it should be positioned on the page with the function \ref A3DPDFPageInsertButton.

\param [in,out] pDoc The Document object to work with.
\param [in] pButtonData The button parameters. The name is mandatory.
\param [out] ppButton The button created.
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFButtonCreate, (A3DPDFDocument* pDoc, const A3DPDFButtonData* pButtonData, A3DPDFButton** ppButton));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a button in a page

\param [in,out] pPage The Page object to work with.
\param [in] pButton The button object to insert on the page.
\param [in] pRectData The rectangle to specify the position on the page.
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFPageInsertButton, (A3DPDFPage* pPage, A3DPDFButton* pButton, const A3DPDFRectData* pRectData));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a button in a table

\param [in,out] pPage The Page object to work with.
\param [in] pTable The Table object to insert in the table.
\param [in] pButton The Button object to insert in the table.
\param [in] iRowIndex The index of the row of the table's cell to insert the button (starts from 1).
\param [in] iColumnIndex The index of the column of the table's cell to insert the button (starts from 1).
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFPageInsertButtonInTable, (A3DPDFPage* pPage, A3DPDFTable* pTable, A3DPDFButton* pButton, A3DInt32 iRowIndex, A3DInt32 iColumnIndex));



/*!
\ingroup a3d_publish_document_module
\brief Function to create a slide table. This is a table with a fixed size, and two buttons to scroll the rows of the table.
The frame of the table is specified through html definition and printed as-is on the page. Then the text data is populated
dynamically from an array of texts specified.
The table MUST be of simple shape, with the same number of rows for each columns. Optionally, a header can figure in the
table data at first row. 
The text data defines the text content, as well as text format attributes (font, font size, and text color). All rows must 
have the same text attributes, so that only the first row of text data is used internally to get the text format.
\param [in,out] pDoc The document which will contain the slide table.
\param [in,out] pPage The page where the slide table will be put.
\param [in] iPosLeft The x coordinate of the insertion point of the table. The insertion point is the top left corner of the table. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\param [in] iPosTop The y coordinate of the insertion point of the table. The insertion point is the top left corner of the table. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\param [in] pcHtmlFrameTable String for definition of the frame table in a HTML format. See example definition in \ref a3d_publish_table_module.
\param [in] pcHtmlFrameStyle String for definition of the frame table style in a CSS format. See example definition in \ref a3d_publish_table_module.
\param [in] pPreviousButtonName The name of the button to press to go to the previous page.
\param [in] pNextButtonName The name of the button to press to go to the next page.
\param [in] iNbTextRows the number of rows in the matrix of text data specified in ppTextData.
\param [in] iNbTextCols the number of columns in the matrix of text data specified in ppTextData. It should be the same number as of the number of columns specified in the table frame.
\param [in] ppTexts must contain the text data that will be used to dynamically populate the table. 
	It is a matrix of iNbTextRows*iNbTextCols elements of type (A3DPDFTextField*). These elements should be created with A3DPDFTextFieldCreate.
	The first row might contain the header for the table. In that case, specify bHasHeader to TRUE, then the first row will 
	not be scrolled and the formatting specific to this row will be applied.
	The following members of A3DPDFTextFieldData structure are used: 
	<ul>
	<li>the text content is specified in member m_pcDefaultValue</li>
	<li>the font name is specified in member m_pcFontName</li>
	<li>the font size is specified in member m_iFontSize</li>
	<li>the text color is specified in member m_sTextColor</li>
	<li>the background color is specified in member m_sFillColor if member m_bHasFillColor is TRUE</li>
	<li>the text alignment is specified in member m_eTextAlignment</li>	
	<li>the text orientation is specified in member m_eTextOrientation</li>	
	<li>the readonly attribute is specified in member m_bReadOnly</li>	
	<li>the multiline attribute is specified in member m_bMultiLine</li>	
	<li>the donotscroll attribute is specified in member m_bDoNotScroll</li>	
	<li>the formfield attribute is specified in member m_eFormField</li>	
	</ul>
	Only first row is used to get attributes.
\param [in] bHasHeader If true, the table header is described at first row of ppTexts. This row will remain visible and won't 
	be scrolled when pushing the prev/next buttons.
	If false, the table is considered without header, then the whole rows will be scrolled when pushing the prev/next buttons.
\return \ref A3D_SUCCESS \n
\return \ref A3DPDF_SLIDETABLE_NBCOLUMNS_ERROR if iNbTextCols differs from the number of columns in table frame.\n
\return \ref A3DPDF_SLIDETABLE_TEXTDATA_ERROR if ppTexts has wrong data (typically null pointer).\n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFDefineSlideTable, (A3DPDFDocument* pDoc, A3DPDFPage* pPage, 
											   const A3DInt32 iPosLeft, const A3DInt32 iPosTop,
											   const A3DUTF8Char* pcHtmlFrameTable, const A3DUTF8Char* pcHtmlFrameStyle,
											   const A3DUTF8Char* pPreviousButtonName,
											   const A3DUTF8Char* pNextButtonName,
											   const A3DInt32 iNbTextRows,
											   const A3DInt32 iNbTextCols,
											   const A3DPDFTextField* const * const* ppTexts,
											   const A3DBool bHasHeader));


/*!
\ingroup a3d_publish_document_module
\brief Function to create a slide table. This is a table with a fixed size, and a scroll bar to scroll the rows of the table.
This function differs from \ref A3DPDFDefineSlideTable in that it uses a scroll bar to scroll the rows instead of previous and next buttons.
The frame of the table is specified through html definition and printed as-is on the page. Then the text data is populated
dynamically from an array of texts specified.
The table MUST be of simple shape, with the same number of rows for each columns. Optionally, a header can figure in the
table data at first row. 
The text data defines the text content, as well as text format attributes (font, font size, and text color). All rows must
have the same text attributes, so that only the first row of text data is used internally to get the text format.
\param [in,out] pDoc The document which will contain the slide table.
\param [in,out] pPage The page where the slide table will be put.
\param [in] iPosLeft The x coordinate of the insertion point of the table. The insertion point is the top left corner of the table. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\param [in] iPosTop The y coordinate of the insertion point of the table. The insertion point is the top left corner of the table. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
\param [in] pcHtmlFrameTable String for definition of the frame table in a HTML format. See example definition in \ref a3d_publish_table_module.
\param [in] pcHtmlFrameStyle String for definition of the frame table style in a CSS format. See example definition in \ref a3d_publish_table_module.
\param [in] iSliderWidth The width of the scroll bar (in points). Important: The scrollbar is positioned on the right of the table, outside of the frame.
\param [in] iNbTextRows the number of rows in the matrix of text data specified in ppTextData.
\param [in] iNbTextCols the number of columns in the matrix of text data specified in ppTextData. It should be the same number as of the number of columns specified in the table frame.
\param [in] ppTexts must contain the text data that will be used to dynamically populate the table.
It is a matrix of iNbTextRows*iNbTextCols elements of type (A3DPDFTextField*). These elements should be created with A3DPDFTextFieldCreate.
The first row might contain the header for the table. In that case, specify bHasHeader to TRUE, then the first row will
not be scrolled and the formatting specific to this row will be applied.
The following members of A3DPDFTextFieldData structure are used:
<ul>
<li>the text content is specified in member m_pcDefaultValue</li>
<li>the font name is specified in member m_pcFontName</li>
<li>the font size is specified in member m_iFontSize</li>
<li>the text color is specified in member m_sTextColor</li>
<li>the background color is specified in member m_sFillColor if member m_bHasFillColor is TRUE</li>
<li>the text alignment is specified in member m_eTextAlignment</li>
<li>the text orientation is specified in member m_eTextOrientation</li>
<li>the readonly attribute is specified in member m_bReadOnly</li>
<li>the multiline attribute is specified in member m_bMultiLine</li>
<li>the donotscroll attribute is specified in member m_bDoNotScroll</li>
<li>the formfield attribute is specified in member m_eFormField</li>
</ul>
Only first row is used to get attributes.
\param [in] bHasHeader If true, the table header is described at first row of ppTexts. This row will remain visible and won't
be scrolled when using the scroll bar.
If false, the table is considered without header, then the whole rows will be scrolled when using the scroll bar.
\param [out] ppcSTName The identifier of the slide table as a string. It can be useful to add Javascript instructions to work on this specific slide table.
\return \ref A3D_SUCCESS \n
\return \ref A3DPDF_SLIDETABLE_NBCOLUMNS_ERROR if iNbTextCols differs from the number of columns in table frame.\n
\return \ref A3DPDF_SLIDETABLE_TEXTDATA_ERROR if ppTexts has wrong data (typically null pointer).\n
\version 8.1
*/
A3D_API (A3DStatus, A3DPDFDefineSlideTable2, (A3DPDFDocument* pDoc, A3DPDFPage* pPage,
												const A3DInt32 iPosLeft, const A3DInt32 iPosTop,
												const A3DUTF8Char* pcHtmlFrameTable, const A3DUTF8Char* pcHtmlFrameStyle,
												const A3DInt32 iSliderWidth,
												const A3DInt32 iNbTextRows,
												const A3DInt32 iNbTextCols,
												const A3DPDFTextField* const * const* ppTexts,
												const A3DBool bHasHeader,
												A3DUTF8Char** ppcSTName));

/*!
\ingroup a3d_publish_document_module
\brief Structure that defines a set of 3D nodes. Usually used to be referred in a slide table row.
Each element can contain several instances. We can get the uuids for each instance.
\version 9.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DInt32 m_iNbNodes;		/*!< Size of the following array. */
	A3DUTF8Char** m_ppUUIDsForNodes;/*!< The unique IDs of instances for the nodes. */
} A3DPDF3DNodesReferencesData;


/*!
\ingroup a3d_publish_document_module
\brief Function to link 3D nodes to a slide table.
Each row of the slide table are linked to a set of 3D nodes. Thus, when the user clicks on a row, the 3D nodes are 
automatically highlighted; and vice versa: when a 3D node is clicked in the 3D, the row is automatically selected.
\param [in,out] pDoc The document which contains the slide table
\param [in,out] pPage The page where the slide table is
\param [in] pcSTName The identifier of the slide table as a string
\param [in] p3DAnnot The 3D annotation
\param [in] sHighlightRowColor The color for the highlighted row
\param [in] iNbRows The size of the following array
\param [in] p3DNodesReferences The set of nodes for each row
\return \ref A3D_SUCCESS \n
\version 9.1
*/
A3D_API(A3DStatus, A3DPDFSlideTableLinkTo3DNodes, (A3DPDFDocument* pDoc, A3DPDFPage* pPage,
	const A3DUTF8Char* pcSTName,
	const A3DPDF3DAnnot* p3DAnnot,
	const A3DPDFRgbColorData sHighlightRowColor,
	const A3DInt32 iNbRows,
	const A3DPDF3DNodesReferencesData * const p3DNodesReferences
));


/*!
\ingroup a3d_publish_page_module
\brief Alignment of the text
\version 7.2
*/
typedef enum
{
	kA3DPDFLeft,		/*!< The text is left justified. */ 
	kA3DPDFCentered,	/*!< The button is centered. */ 
	kA3DPDFRight,		/*!< The button is right justified. */ 
} A3DPDFETextAlignment;

/*!
\ingroup a3d_publish_document_module
\brief Structure to define a text field
\version 7.2
*/
typedef struct 
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcName;								/*!< Name of the field (it serves as the field identifier, it should be unique in the document). */
	A3DUTF8Char* m_pcTooltip;							/*!<
															Displayed text that the hesitant user may find helpful in filling in the form field. 
															Tooltips appear when the pointer hovers briefly over the form field. */
	A3DPDFEFormField m_eFormField;						/*!< Specifies whether the form field can be seen, either on screen or in print. */
	A3DPDFETextOrientation m_eTextOrientation;			/*!< Orientation of the text inside the field. */
	A3DBool m_bIsReadOnly;								/*!< Defines if the field is editable. */
	A3DBool m_bIsRequired;								/*!< Defines if the field is required. */
	A3DBool m_bIsLocked;								/*!< If locked, prevents any further changes to any form field properties (in Acrobat 'Properties' dialog box). */	
	A3DBool m_bHasBorder;								/*!< If true, there is a border around the field. */
	A3DPDFRgbColorData m_sBorderColor;					/*!< Color of the border of the field (if any). */
	A3DPDFEThicknessBorder m_eThicknessBorder;			/*!< Thickness of the border. */
	A3DPDFELineStyleBorder m_eLineStyleBorder;			/*!< Line style of the border. */
	A3DBool m_bHasFillColor;							/*!< If true, the following field (m_sFillColor) is used. */
	A3DPDFRgbColorData m_sFillColor;					/*!< Color which the inside of the field will be filled with (if m_bHasFillColor is true). */
	A3DPDFRgbColorData m_sTextColor;					/*!< Color of the text. */
	A3DUTF8Char* m_pcFontName;							/*!<
															Font name of the text. 
		It should be the name of the font as appearing in Acrobat font list, but without spaces, and with style separated with a comma. 
		For example, 'Calibri Bold Italic' should be specified as "Calibri,BoldItalic" ; 
		or 'Century Gothic' should be specified as "CenturyGothic".
		Also, specific values exist for Adobe default fonts:
		eTimesRoman is "TiRo" ; eTimesItalic is  "TiIt" ; eTimesBold is "TiBo" ; eTimesBoldItalic is "TiBI" ;
		eHelvetica is "Helv" ; eHelveticaOblique is "HeOb" ; eHelveticaBold is "HeBo" ; eHelveticaBoldOblique is "HeBO" ;
		eCourier is "Cour" ; eCourierOblique is "CoOb" ; eCourierBold is "CoBo" ; eCourierBoldOblique is "CoBO". */
	A3DInt32 m_iFontSize; 								/*!< Size of the font. */
	A3DPDFETextAlignment m_eTextAlignment;				/*!< Alignment of the text inside the text field. */
	A3DUTF8Char* m_pcDefaultValue;						/*!< Default text field content. */
	A3DBool m_bCheckSpelling;							/*!< Defines if the text entered in the field must be spell-checked. */							
	A3DBool m_bIsMultiLine;								/*!< Defines if the text field is multi line. */
	A3DBool m_bDoNotScroll;								/*!< Defines if the text field is scrollable or not. */							
	A3DBool m_bAllowRichText;							/*!< If set, the value of this field shall be a rich text string. */							
	A3DUTF8Char* m_pcRichTextValue;						/*!< If m_bAllowRichText is true, field content in RTF. */
} A3DPDFTextFieldData;
  


/*!
\ingroup a3d_publish_page_module
\brief Function to create a text field

The text field is primarily created with this function, and it should be positioned on the page with the function \ref A3DPDFPageInsertTextField.

\param [in,out] pDoc The Document object to work with.
\param [in] pTextFieldData The text field parameters.
\param [out] ppTextField The text field created.
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFTextFieldCreate, (A3DPDFDocument* pDoc, const A3DPDFTextFieldData* pTextFieldData, A3DPDFTextField** ppTextField));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a text field in a page. 

The text field must have a name before inserting it.

\param [in,out] pPage The Page object to work with.
\param [in] pTextField The Text field object to insert on the page.
\param [in] pRectData The rectangle to specify the position on the page.
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFPageInsertTextField, (A3DPDFPage* pPage, A3DPDFTextField* pTextField, const A3DPDFRectData* pRectData));

/*!
\ingroup a3d_publish_page_module
\brief Function to insert a text field in a table

\param [in,out] pPage The Page object to work with.
\param [in] pTable The Table object to insert in the table.
\param [in] pTextField The Text field object to insert in the table.
\param [in] iRowIndex The index of the row of the table's cell to insert the button (start from 1)
\param [in] iColumnIndex The index of the column of the table's cell to insert the button (start from 1)
\return \ref A3D_SUCCESS \n
\version 7.2
*/
A3D_API (A3DStatus, A3DPDFPageInsertTextFieldInTable, (A3DPDFPage* pPage, A3DPDFTable* pTable, A3DPDFTextField* pTextField, A3DInt32 iRowIndex, A3DInt32 iColumnIndex));


/*!
\ingroup a3d_publish_document_module
\brief Structure to define a check box field
\version 8.0
*/
typedef struct 
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcName;								/*!< Name of the field (it serves as the field identifier, it should be unique in the document). */
	A3DUTF8Char* m_pcTooltip;							/*!<
															Displayed text that the hesitant user may find helpful in filling in the form field. 
															Tooltips appear when the pointer hovers briefly over the form field. */
	A3DPDFEFormField m_eFormField;						/*!< Specifies whether the form field can be seen, either on screen or in print. */
	A3DPDFETextOrientation m_eTextOrientation;			/*!< Orientation of the text inside the field. */
	A3DBool m_bIsReadOnly;								/*!< Defines if the field is editable. */
	A3DBool m_bIsRequired;								/*!< Defines if the field is required. */
	A3DBool m_bIsLocked;								/*!< If locked, prevents any further changes to any form field properties (in Acrobat 'Properties' dialog box). */	
	A3DBool m_bHasBorder;								/*!< If true, there is a border around the field. */
	A3DPDFRgbColorData m_sBorderColor;					/*!< Color of the border of the field (if any). */
	A3DPDFEThicknessBorder m_eThicknessBorder;			/*!< Thickness of the border. */
	A3DPDFELineStyleBorder m_eLineStyleBorder;			/*!< Line style of the border. */
	A3DBool m_bHasFillColor;							/*!< If true, the following field (m_sFillColor) is used. */
	A3DPDFRgbColorData m_sFillColor;					/*!< Color which the inside of the field will be filled with (if m_bHasFillColor is true). */
	A3DPDFRgbColorData m_sTextColor;					/*!< Color of the text. */
	A3DUTF8Char* m_pcFontName;							/*!<
															Font name of the text. 
		It should be the name of the font as appearing in Acrobat font list, but without spaces, and with style separated with a comma. 
		For example, 'Calibri Bold Italic' should be specified as "Calibri,BoldItalic" ; 
		or 'Century Gothic' should be specified as "CenturyGothic".
		Also, specific values exist for Adobe default fonts:
		eTimesRoman is "TiRo" ; eTimesItalic is  "TiIt" ; eTimesBold is "TiBo" ; eTimesBoldItalic is "TiBI" ;
		eHelvetica is "Helv" ; eHelveticaOblique is "HeOb" ; eHelveticaBold is "HeBo" ; eHelveticaBoldOblique is "HeBO" ;
		eCourier is "Cour" ; eCourierOblique is "CoOb" ; eCourierBold is "CoBo" ; eCourierBoldOblique is "CoBO". */
	A3DInt32 m_iFontSize; 								/*!< Size of the font. */
	A3DUTF8Char* m_pcExportValue;						/*!< Value used when field data is exported by Acrobat functions. */
	A3DBool m_bIsCheckedByDefault;						/*!< If true, this check box is selected when the PDF document is opened. */
} A3DPDFCheckBoxData;


/*!
\ingroup a3d_publish_page_module
\brief Function to create a CheckBox

The CheckBox is primarily created with this function, and it should be positionned on the page with the function \ref A3DPDFPageInsertCheckBox.

\param [in,out] pDoc The Document object to work with.
\param [in] pCheckBoxData The CheckBox parameters. The name is mandatory.
\param [out] ppCheckBox The CheckBox created.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFCheckBoxCreate, (A3DPDFDocument* pDoc, const A3DPDFCheckBoxData* pCheckBoxData, A3DPDFCheckBox** ppCheckBox));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a CheckBox in a page

\param [in,out] pPage The Page object to work with.
\param [in] pCheckBox The CheckBox object to insert on the page.
\param [in] pRectData The rectangle to specify the position on the page.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFPageInsertCheckBox, (A3DPDFPage* pPage, A3DPDFCheckBox* pCheckBox, const A3DPDFRectData* pRectData));


/*!
\ingroup a3d_publish_document_module
\brief Structure to define a radio button field
\version 8.0
*/
typedef struct 
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcName;								/*!< Name of the field (it serves as the field identifier, it should be unique in the document). */
	A3DUTF8Char* m_pcTooltip;							/*!<
															Displayed text that the hesitant user may find helpful in filling in the form field. 
															Tooltips appear when the pointer hovers briefly over the form field. */
	A3DPDFEFormField m_eFormField;						/*!< Specifies whether the form field can be seen, either on screen or in print. */
	A3DPDFETextOrientation m_eTextOrientation;			/*!< Orientation of the text inside the field. */
	A3DBool m_bIsReadOnly;								/*!< Defines if the field is editable. */
	A3DBool m_bIsRequired;								/*!< Defines if the field is required. */
	A3DBool m_bIsLocked;								/*!< If locked, prevents any further changes to any form field properties (in Acrobat 'Properties' dialog box). */	
	A3DBool m_bHasBorder;								/*!< If true, there is a border around the field. */
	A3DPDFRgbColorData m_sBorderColor;					/*!< Color of the border of the field (if any). */
	A3DPDFEThicknessBorder m_eThicknessBorder;			/*!< Thickness of the border. */
	A3DPDFELineStyleBorder m_eLineStyleBorder;			/*!< Line style of the border. */
	A3DBool m_bHasFillColor;							/*!< If true, the following field (m_sFillColor) is used. */
	A3DPDFRgbColorData m_sFillColor;					/*!< Color which the inside of the field will be filled with (if m_bHasFillColor is true). */
	A3DPDFRgbColorData m_sTextColor;					/*!< Color of the text. */
	A3DUTF8Char* m_pcFontName;							/*!<
															Font name of the text. 
		It should be the name of the font as appearing in Acrobat font list, but without spaces, and with style separated with a comma. 
		For example, 'Calibri Bold Italic' should be specified as "Calibri,BoldItalic" ; 
		or 'Century Gothic' should be specified as "CenturyGothic".
		Also, specific values exist for Adobe default fonts:
		eTimesRoman is "TiRo" ; eTimesItalic is  "TiIt" ; eTimesBold is "TiBo" ; eTimesBoldItalic is "TiBI" ;
		eHelvetica is "Helv" ; eHelveticaOblique is "HeOb" ; eHelveticaBold is "HeBo" ; eHelveticaBoldOblique is "HeBO" ;
		eCourier is "Cour" ; eCourierOblique is "CoOb" ; eCourierBold is "CoBo" ; eCourierBoldOblique is "CoBO". */
	A3DInt32 m_iFontSize; 								/*!< Size of the font. */
	A3DUTF8Char* m_pcExportValue;						/*!< Value used when field data is exported by Acrobat functions. */
	A3DBool m_bIsCheckedByDefault;						/*!< If true, this radio button is selected when the PDF document is opened. */
	A3DBool m_bRadiosInUnison;							/*!< If true, radio buttons with the same name and choice are selected in unison. */
} A3DPDFRadioButtonData;


/*!
\ingroup a3d_publish_page_module
\brief Function to create a RadioButton

The RadioButton is primarily created with this function, and it should be positionned on the page with the function \ref A3DPDFPageInsertRadioButton.

\param [in,out] pDoc The Document object to work with.
\param [in] pRadioButtonData The RadioButton parameters. The name is mandatory.
\param [out] ppRadioButton The RadioButton created.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFRadioButtonCreate, (A3DPDFDocument* pDoc, const A3DPDFRadioButtonData* pRadioButtonData, A3DPDFRadioButton** ppRadioButton));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a RadioButton in a page

\param [in,out] pPage The Page object to work with.
\param [in] pRadioButton The RadioButton object to insert on the page.
\param [in] pRectData The rectangle to specify the position on the page.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFPageInsertRadioButton, (A3DPDFPage* pPage, A3DPDFRadioButton* pRadioButton, const A3DPDFRectData* pRectData));


/*!
\ingroup a3d_publish_document_module
\brief Structure to define a list box field
\version 8.0
*/
typedef struct 
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcName;								/*!< Name of the field (it serves as the field identifier, it should be unique in the document). */
	A3DUTF8Char* m_pcTooltip;							/*!<
															Displayed text that the hesitant user may find helpful in filling in the form field. 
															Tooltips appear when the pointer hovers briefly over the form field. */
	A3DPDFEFormField m_eFormField;						/*!< Specifies whether the form field can be seen, either on screen or in print. */
	A3DPDFETextOrientation m_eTextOrientation;			/*!< Orientation of the text inside the field. */
	A3DBool m_bIsReadOnly;								/*!< Defines if the field is editable. */
	A3DBool m_bIsRequired;								/*!< Defines if the field is required. */
	A3DBool m_bIsLocked;								/*!< If locked, prevents any further changes to any form field properties (in Acrobat 'Properties' dialog box). */	
	A3DBool m_bHasBorder;								/*!< If true, there is a border around the field. */
	A3DPDFRgbColorData m_sBorderColor;					/*!< Color of the border of the field (if any). */
	A3DPDFEThicknessBorder m_eThicknessBorder;			/*!< Thickness of the border. */
	A3DPDFELineStyleBorder m_eLineStyleBorder;			/*!< Line style of the border. */
	A3DBool m_bHasFillColor;							/*!< If true, the following field (m_sFillColor) is used. */
	A3DPDFRgbColorData m_sFillColor;					/*!< Color which the inside of the field will be filled with (if m_bHasFillColor is true). */
	A3DPDFRgbColorData m_sTextColor;					/*!< Color of the text. */
	A3DUTF8Char* m_pcFontName;							/*!<
															Font name of the text. 
		It should be the name of the font as appearing in Acrobat font list, but without spaces, and with style separated with a comma. 
		For example, 'Calibri Bold Italic' should be specified as "Calibri,BoldItalic" ; 
		or 'Century Gothic' should be specified as "CenturyGothic".
		Also, specific values exist for Adobe default fonts:
		eTimesRoman is "TiRo" ; eTimesItalic is  "TiIt" ; eTimesBold is "TiBo" ; eTimesBoldItalic is "TiBI" ;
		eHelvetica is "Helv" ; eHelveticaOblique is "HeOb" ; eHelveticaBold is "HeBo" ; eHelveticaBoldOblique is "HeBO" ;
		eCourier is "Cour" ; eCourierOblique is "CoOb" ; eCourierBold is "CoBo" ; eCourierBoldOblique is "CoBO". */
	A3DInt32 m_iFontSize; 								/*!< Size of the font. */
	A3DBool m_bMultipleSelection;						/*!< If true, several items can be selected. */							
} A3DPDFListBoxData;


/*!
\ingroup a3d_publish_page_module
\brief Function to create a ListBox

The ListBox is primarily created with this function, and it should be positionned on the page with the function \ref A3DPDFPageInsertListBox.
List items can be added using the function \ref A3DPDFPageFieldListAddItem, after the call to \ref A3DPDFPageInsertListBox.

\param [in,out] pDoc The Document object to work with.
\param [in] pListBoxData The ListBox parameters. The name is mandatory.
\param [out] ppListBox The ListBox created.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFListBoxCreate, (A3DPDFDocument* pDoc, const A3DPDFListBoxData* pListBoxData, A3DPDFListBox** ppListBox));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a ListBox in a page

\param [in,out] pPage The Page object to work with.
\param [in] pListBox The ListBox object to insert on the page.
\param [in] pRectData The rectangle to specify the position on the page.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFPageInsertListBox, (A3DPDFPage* pPage, A3DPDFListBox* pListBox, const A3DPDFRectData* pRectData));


/*!
\ingroup a3d_publish_document_module
\brief Structure to define a drop down list field (combo box)
\version 8.0
*/
typedef struct 
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcName;								/*!< Name of the field (it serves as the field identifier, it should be unique in the document). */
	A3DUTF8Char* m_pcTooltip;							/*!<
															Displayed text that the hesitant user may find helpful in filling in the form field. 
															Tooltips appear when the pointer hovers briefly over the form field. */
	A3DPDFEFormField m_eFormField;						/*!< Specifies whether the form field can be seen, either on screen or in print. */
	A3DPDFETextOrientation m_eTextOrientation;			/*!< Orientation of the text inside the field. */
	A3DBool m_bIsReadOnly;								/*!< Defines if the field is editable. */
	A3DBool m_bIsRequired;								/*!< Defines if the field is required. */
	A3DBool m_bIsLocked;								/*!< If locked, prevents any further changes to any form field properties (in Acrobat 'Properties' dialog box). */	
	A3DBool m_bHasBorder;								/*!< If true, there is a border around the field. */
	A3DPDFRgbColorData m_sBorderColor;					/*!< Color of the border of the field (if any). */
	A3DPDFEThicknessBorder m_eThicknessBorder;			/*!< Thickness of the border. */
	A3DPDFELineStyleBorder m_eLineStyleBorder;			/*!< Line style of the border. */
	A3DBool m_bHasFillColor;							/*!< If true, the following field (m_sFillColor) is used. */
	A3DPDFRgbColorData m_sFillColor;					/*!< Color which the inside of the field will be filled with (if m_bHasFillColor is true). */
	A3DPDFRgbColorData m_sTextColor;					/*!< Color of the text. */
	A3DUTF8Char* m_pcFontName;							/*!< Font name of the text. 
		It should be the name of the font as appearing in Acrobat font list, but without spaces, and with style separated with a comma. 
		For example, 'Calibri Bold Italic' should be specified as "Calibri,BoldItalic" ; 
		or 'Century Gothic' should be specified as "CenturyGothic".
		Also, specific values exist for Adobe default fonts:
		eTimesRoman is "TiRo" ; eTimesItalic is  "TiIt" ; eTimesBold is "TiBo" ; eTimesBoldItalic is "TiBI" ;
		eHelvetica is "Helv" ; eHelveticaOblique is "HeOb" ; eHelveticaBold is "HeBo" ; eHelveticaBoldOblique is "HeBO" ;
		eCourier is "Cour" ; eCourierOblique is "CoOb" ; eCourierBold is "CoBo" ; eCourierBoldOblique is "CoBO". */
	A3DInt32 m_iFontSize; 								/*!< Size of the font. */
	A3DBool m_bAllowUserToEnterCustomText;				/*!< If true, the user can enter custom text. */
	A3DBool m_bCheckSpelling;							/*!< If true, checks the spelling. */
	A3DBool m_bCommitImmediate;							/*!< If true, commits the selected value immediately. */
} A3DPDFDropDownListData;


/*!
\ingroup a3d_publish_page_module
\brief Function to create a DropDownList (combo box)

The DropDownList is primarily created with this function, and it should be positionned on the page with the function \ref A3DPDFPageInsertDropDownList.
List items can be added using the function \ref A3DPDFPageFieldListAddItem, after the call to \ref A3DPDFPageInsertDropDownList.

\param [in,out] pDoc The Document object to work with.
\param [in] pDropDownListData The DropDownList parameters. The name is mandatory.
\param [out] ppDropDownList The DropDownList created.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFDropDownListCreate, (A3DPDFDocument* pDoc, const A3DPDFDropDownListData* pDropDownListData, A3DPDFDropDownList** ppDropDownList));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a DropDownList (combo box) in a page

\param [in,out] pPage The Page object to work with.
\param [in] pDropDownList The DropDownList object to insert on the page.
\param [in] pRectData The rectangle to specify the position on the page.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFPageInsertDropDownList, (A3DPDFPage* pPage, A3DPDFDropDownList* pDropDownList, const A3DPDFRectData* pRectData));


/*!
\ingroup a3d_publish_document_module
\brief Structure to define a digital signature field
\version 8.0
*/
typedef struct 
{
	A3DUns16 m_usStructSize;							/*!< Reserved; must be initialized by \ref A3D_INITIALIZE_DATA. */
	A3DUTF8Char* m_pcName;								/*!< Name of the field (it serves as the field identifier, it should be unique in the document). */
	A3DUTF8Char* m_pcTooltip;							/*!<
															Displayed text that the hesitant user may find helpful in filling in the form field. 
															Tooltips appear when the pointer hovers briefly over the form field. */
	A3DPDFEFormField m_eFormField;						/*!< Specifies whether the form field can be seen, either on screen or in print. */
	A3DPDFETextOrientation m_eTextOrientation;			/*!< Orientation of the text inside the field. */
	A3DBool m_bIsReadOnly;								/*!< Defines if the field is editable. */
	A3DBool m_bIsRequired;								/*!< Defines if the field is required. */
	A3DBool m_bIsLocked;								/*!< If locked, prevents any further changes to any form field properties (in Acrobat 'Properties' dialog box). */	
	A3DBool m_bHasBorder;								/*!< If true, there is a border around the field. */
	A3DPDFRgbColorData m_sBorderColor;					/*!< Color of the border of the field (if any). */
	A3DPDFEThicknessBorder m_eThicknessBorder;			/*!< Thickness of the border. */
	A3DPDFELineStyleBorder m_eLineStyleBorder;			/*!< Line style of the border. */
	A3DBool m_bHasFillColor;							/*!< If true, the following field (m_sFillColor) is used. */
	A3DPDFRgbColorData m_sFillColor;					/*!< Color which the inside of the field will be filled with (if m_bHasFillColor is true). */
	A3DPDFRgbColorData m_sTextColor;					/*!< Color of the text. */
	A3DUTF8Char* m_pcFontName;							/*!<
															Font name of the text. 
		It should be the name of the font as appearing in Acrobat font list, but without spaces, and with style separated with a comma. 
		For example, 'Calibri Bold Italic' should be specified as "Calibri,BoldItalic" ; 
		or 'Century Gothic' should be specified as "CenturyGothic".
		Also, specific values exist for Adobe default fonts:
		eTimesRoman is "TiRo" ; eTimesItalic is  "TiIt" ; eTimesBold is "TiBo" ; eTimesBoldItalic is "TiBI" ;
		eHelvetica is "Helv" ; eHelveticaOblique is "HeOb" ; eHelveticaBold is "HeBo" ; eHelveticaBoldOblique is "HeBO" ;
		eCourier is "Cour" ; eCourierOblique is "CoOb" ; eCourierBold is "CoBo" ; eCourierBoldOblique is "CoBO". */
	A3DInt32 m_iFontSize; 								/*!< Size of the font. */
} A3DPDFDigitalSignatureData;


/*!
\ingroup a3d_publish_page_module
\brief Function to create a DigitalSignature

The DigitalSignature is primarily created with this function, and it should be positionned on the page with the function \ref A3DPDFPageInsertDigitalSignature.

\param [in,out] pDoc The Document object to work with.
\param [in] pDigitalSignatureData The DigitalSignature parameters. The name is mandatory.
\param [out] ppDigitalSignature The DigitalSignature created.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFDigitalSignatureCreate, (A3DPDFDocument* pDoc, const A3DPDFDigitalSignatureData* pDigitalSignatureData, A3DPDFDigitalSignature** ppDigitalSignature));


/*!
\ingroup a3d_publish_page_module
\brief Function to insert a DigitalSignature in a page

\param [in,out] pPage The Page object to work with.
\param [in] pDigitalSignature The DigitalSignature object to insert on the page.
\param [in] pRectData The rectangle to specify the position on the page.
\return \ref A3D_SUCCESS \n
\version 8.0
*/
A3D_API (A3DStatus, A3DPDFPageInsertDigitalSignature, (A3DPDFPage* pPage, A3DPDFDigitalSignature* pDigitalSignature, const A3DPDFRectData* pRectData));


/*!
\ingroup a3d_publish_bill_of_material_module
\brief Structure that defines an element in a BOM.
Each element can contain several instances. We can get the uuids for each instance.
\version 8.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DUTF8Char* m_pcName;/*!< Name of the current element. */
	A3DInt32 m_iLevel;/*!< The level in the assembly. */
} A3DPDFBomElementInfoData;


/*!
\ingroup a3d_publish_bill_of_material_module
\brief Function to get a bill of material (BOM) from a modelfile. 
The function returns an array of elements in the BOM. 
Each element is the set of components in the assembly associated to the part.

\param [in] pModelFile The model file to work with.
\param [in] pPrcWriteHelper Used to get PRC data such as unique identifiers for PRC nodes.
\param [in] bHierarchical True if the BOM is hierarchical, false if it is flattened.
\param [out] piNbElements The number of elements in the BOM. In a bom table, it would be the number of lines.
\param [out] ppBomElementInfo Array of details of the elements in the BOM.
\param [out] pp3DNodesReferences Array of details of the node references for elements in the BOM.
\return \ref A3D_SUCCESS \n
\version 8.1
*/
A3D_API (A3DStatus, A3DPDFGetBOMInfo, (A3DAsmModelFile* pModelFile, 
										A3DRWParamsPrcWriteHelper* pPrcWriteHelper,
										A3DBool bHierarchical,
										A3DInt32 *piNbElements,
										A3DPDFBomElementInfoData **ppBomElementInfo,
										A3DPDF3DNodesReferencesData **pp3DNodesReferences));

/*!
\ingroup a3d_publish_bill_of_material_module
\brief Function to free the memory allocated for the information of the BOM

\param [out] ppBomElementInfo Array of details of the elements in the BOM.
\param [out] pp3DNodesReferences Array of details of the node references for elements in the BOM.
\return \ref A3D_SUCCESS \n
\version 8.1
*/
A3D_API (A3DStatus, A3DPDFFreeBOMInfo, (A3DInt32 iNbElements,
	A3DPDFBomElementInfoData **ppBomElementInfo,
	A3DPDF3DNodesReferencesData **pp3DNodesReferences));

/*!
\defgroup a3d_publish_template_module Template Module
\ingroup a3d_publishpdf_module
\brief Template functions

This module describes the functions and structures that allow you to define a PDF Document from a layout template.
*/

/*!
\ingroup a3d_publish_page_module
\brief Structure that defines a graphic rectangle.
\version 9.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DPDFRectDData m_sRectangleData;
	A3DPDFRgbColorData m_sLineColor;
	A3DPDFRgbColorData m_sFillColor;
	A3DDouble m_dWidth;
	A3DDouble m_dDashSize;				/*!< The size of the visible part of a dashed line in points. If O the line will be plain. */
	A3DDouble m_dGapSize;				/*!< The size of the invisible part of a dashed line in points. If O the line will be plain. */
} A3DPDFGraphicRectangleData;

/*!
\ingroup a3d_publish_page_module
\brief Function to create a graphic line

\param [in,out] pPage The Page object to work with.
\param [in] pGraphicRectangleData The Graphic rectangle parameters. 
\return \ref A3D_SUCCESS \n
\version 9.1
*/
A3D_API (A3DStatus, A3DPDFPageDrawRectangle,(A3DPDFPage* pPage, const A3DPDFGraphicRectangleData* pGraphicRectangleData));

/*!
\ingroup a3d_publish_page_module
\brief Structure that defines a graphic line.
\version 9.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DDouble m_dXStartPoint;			/*!< The x coordinate of start point of the line. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dYStartPoint;			/*!< The y coordinate of the start point of the line. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dXEndPoint;				/*!< The x coordinate of the end point of the line. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dYEndPoint;				/*!< The y coordinate of the end point of the line. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DPDFRgbColorData m_sLineColor;
	A3DDouble m_dWidth;
	A3DDouble m_dDashSize;				/*!< The size of the visible part of a dashed line in points. If O the line will be plain. */
	A3DDouble m_dGapSize;				/*!< The size of the invisible part of a dashed line in points. If O the line will be plain. */
} A3DPDFGraphicLineData;

/*!
\ingroup a3d_publish_page_module
\brief Function to create a graphic line

\param [in,out] pPage The page object to work with.
\param [in] pGraphicLineData The Graphic line parameters.
\return \ref A3D_SUCCESS \n
\version 9.1
*/
A3D_API(A3DStatus, A3DPDFPageDrawLine, (A3DPDFPage* pPage, const A3DPDFGraphicLineData* pGraphicLineData));

/*!
\ingroup a3d_publish_page_module
\brief Structure that defines a graphic circle arc.
\version 9.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DDouble m_dXStartPoint;			/*!< The x coordinate of start point of the arc. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dYStartPoint;			/*!< The y coordinate of the start point of the arc. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dXEndPoint;				/*!< The x coordinate of the end point of the arc. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dYEndPoint;				/*!< The y coordinate of the end point of the arc. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dXCenterPoint;			/*!< The x coordinate of the center point of the arc. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DDouble m_dYCenterPoint;			/*!< The y coordinate of the center point of the arc. The coordinate origin (0, 0) is the bottom left of the page. The unit is point. */
	A3DPDFRgbColorData m_sArcColor;
	A3DPDFRgbColorData *m_pFillColor;	/*!< Optional: the filling color. */
	A3DDouble m_dWidth;
	A3DDouble m_dDashSize;				/*!< The size of the visible part of a dashed line in points. If O the line will be plain. */
	A3DDouble m_dGapSize;				/*!< The size of the invisible part of a dashed line in points. If O the line will be plain. */
} A3DPDFGraphicArcData;

/*!
\ingroup a3d_publish_page_module
\brief Function to create a graphic circle arc

\param [in,out] pPage The page object to work with.
\param [in] pGraphicArcData The Graphic arc parameters.
\return \ref A3D_SUCCESS \n
\version 9.1
*/
A3D_API(A3DStatus, A3DPDFPageDrawArc, (A3DPDFPage* pPage, const A3DPDFGraphicArcData* pGraphicArcData));

/*!
\ingroup a3d_publish_page_module
\brief Structure that defines a graphic bezier curve.
\version 9.1
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DInt32 m_iNumberOfPoints;			/*!< The number of points in the next array. */
	A3DDouble *m_pdPoints;				/*!< The coordinates x, y of the points. The coordinate origin (0, 0) is the bottom left of the page. The unit is point.
											 They must be given as x1, y1, x2, y2, x3, y3, ..., xn, yn. So the size of the array will be 2*m_iNumberOfPoints.*/
	A3DPDFRgbColorData m_sCurveColor;	/*!< The color of the curve. */
	A3DPDFRgbColorData *m_pFillColor;	/*!< Optional: the filling color. */
	A3DDouble m_dWidth;					/*!< The width of the curve. */
	A3DDouble m_dDashSize;				/*!< The size of the visible part of a dashed curve in points. If O the curve will be plain. */
	A3DDouble m_dGapSize;				/*!< The size of the invisible part of a dashed curve in points. If O the curve will be plain. */
} A3DPDFGraphicBezierCurveData;

/*!
\ingroup a3d_publish_page_module
\brief Function to create a graphic bezier curve

\param [in,out] pPage The page object to work with.
\param [in] pGraphicBezierCurveData The Graphic Bezier curve parameters.
\return \ref A3D_SUCCESS \n
\version 9.1
*/
A3D_API(A3DStatus, A3DPDFPageDrawBezierCurve, (A3DPDFPage* pPage, const A3DPDFGraphicBezierCurveData* pGraphicBezierCurveData));

/*!
\ingroup a3d_publish_page_module
\brief Graphic types
\version 9.1
*/
typedef enum
{
	kA3DPDFGraphicLine = 0,		/*!< Graphic line. */
	kA3DPDFGraphicArc,			/*!< Graphic arc. */
	kA3DPDFGraphicBezierCurve			/*!< Graphic bezier curve. */
} A3DPDFEGraphicType;

/*!
\ingroup a3d_publish_page_module
\brief Structure that defines a graphic path.
\version 9.1

The elements are given ordered from the first to the last element to be drawn. For example, if there are 4 graphics, and m_peGraphicOrder is:
m_peGraphicOrder[0]=kA3DPDFGraphicArc, m_peGraphicOrder[1]=kA3DPDFGraphicLine, m_peGraphicOrder[2]=kA3DPDFGraphicArc, m_peGraphicOrder[3]=kA3DPDFGraphicLine, 
m_iNumberOfLines is 2
m_iNumberOfArcs is 2
the first element to be drawn will be m_pArcsData[0]
the second will be m_pLinesData[0]
the third m_pArcsData[1]
the last m_pLinesData[1]
*/
typedef struct
{
	A3DUns16 m_usStructSize;
	A3DInt32 m_iNumberOfGraphics;						/*!< The total number of lines, arcs, beziers of the path, equal to the size of the next array. */
	A3DPDFEGraphicType*	m_peGraphicOrder;				/*!< The order to draw the following elements. */
	A3DInt32 m_iNumberOfLines;							/*!< The number of lines of the path. */
	A3DPDFGraphicLineData * m_pLinesData;				/*!< The data of the lines of the path, ordered from the first line to be drawn to the last. */
	A3DInt32 m_iNumberOfArcs;							/*!< The number of arcs of the path. */
	A3DPDFGraphicArcData * m_pArcsData;					/*!< The data of the arcs of the path, ordered from the first arc to be drawn to the last. */
	A3DInt32 m_iNumberOfBezierCurves;					/*!< The number of curves of the path. */
	A3DPDFGraphicBezierCurveData * m_pCurvesData;		/*!< The data of the curves of the path, ordered from the first curve to be drawn to the last. */
	A3DPDFRgbColorData m_sPathColor;					/*!< The path color, overrides the colors given in LinesData, ArcsData, CurvesData. */
	A3DPDFRgbColorData *m_pFillColor;					/*!< Optional: the filling color. Overrides the colors given in LinesData, ArcsData, CurvesData. */
	A3DDouble m_dWidth;									/*!< The width of the path. Overrides the colors given in LinesData, ArcsData, CurvesData. */
	A3DDouble m_dDashSize;								/*!< The size of the visible part of a dashed path in points. If O the path will be plain. Overrides the colors given in LinesData, ArcsData, CurvesData. */
	A3DDouble m_dGapSize;								/*!< The size of the invisible part of a dashed path in points. If O the path will be plain. Overrides the colors given in LinesData, ArcsData, CurvesData. */
} A3DPDFGraphicCompositePathData;

/*!
\ingroup a3d_publish_page_module
\brief Function to create a graphic composite path

\param [in,out] pPage The page object to work with.
\param [in] pGraphicPathData The parameters of the elements to be drawn.
\return \ref A3D_SUCCESS \n
\version 9.1
*/
A3D_API(A3DStatus, A3DPDFPageDrawCompositePath, (A3DPDFPage* pPage, A3DPDFGraphicCompositePathData* pGraphicPathData));


/*!
\ingroup a3d_publish_template_module
\brief Function to automatically update Publish data into a document.
Updated data is caroussel, slide tables, attributes, and text fields.

\param [in] pDoc The Document object to work with.
\param [in]  pcAnnot3DUID Identifier of the 3D annot to update.
If not provided, use idxPage and idx3dAnnot to identiofy the annotation to update.
\param [in]  idxPage Identifier of the 3D annot to update: index of the page in the document (starting from 0).
If -1, looks in all the document for the first annot 3D found
\param [in]  idx3dAnnot Identifier of the 3D annot to update: index of the annotation in the page (starting from 0).
If -1, looks in all page the first annot 3D found
\param [in] pModelFile The Document object to work with.
\param [in] pParamsExportData The PRC export parameters.
\param [in,out] ppPrcWriteHelper Used to get PRC data such as unique identifiers of PRC nodes.
\param [in] p3DArtworkData The 3D Artwork parameters.
\param [in] p3DAnnotData The 3D Annot parameters.
\param [in] pcIn3dAttribsFile Xml file with attributes to apply to the 3D data.
\param [in] pcInTextFieldDataFile Xml files with texts to store into text fields in the document.

\return \ref A3D_SUCCESS \n
\version 9.1
*/
A3D_API(A3DStatus, A3DPDFDocumentUpdateData, (
	A3DPDFDocument* pDoc,
	// 3Dannot identifier:
	const A3DUTF8Char* pcAnnot3DUID,
	const A3DInt32 idxPage,
	const A3DInt32 idx3dAnnot,
	// modelfile to use to update 3D data
	A3DAsmModelFile* pModelFile,
	const A3DRWParamsExportPrcData* pParamsExportData,
	A3DRWParamsPrcWriteHelper** ppPrcWriteHelper,
	// options to create the replaced 3D annot
	const A3DPDF3DArtworkData2* p3DArtworkData,
	const A3DPDF3DAnnotData* p3DAnnotData,

	const A3DUTF8Char* pcIn3dAttribsFile,
	const A3DUTF8Char* pcInTextFieldDataFile
	));

#endif
