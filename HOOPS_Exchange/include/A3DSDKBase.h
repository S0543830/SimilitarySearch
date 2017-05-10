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
\brief      Functions and structures that apply to all entities
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCBASE_H__
#define __A3DPRCBASE_H__


#ifndef __A3DPRCSDK_H__
#error A3DSDK.h must be included before current file
#endif
#ifndef  __A3DPRCTYPES_H__
#error A3DSDKTypes.h must be included before current file
#endif
#ifndef __A3DPRCERRORCODES_H__
#error A3DSDKErrorCodes.h must be included before current file
#endif


/*!
\defgroup a3d_base_module Base Module

This section describes the functions you use to start, configure, 
and terminate a session with the \COMPONENT_A3D_LIBRARY.

This section includes code samples that demonstrate how functions and structures are used. 
These code samples are provided "as is", without warranty of any kind. 

@{
*/

/*!
\defgroup a3d_base_functions Base Functions
\ingroup a3d_base_module
\brief Starts, configures, and terminates a session with the \COMPONENT_A3D_LIBRARY.

The functions in this section start and terminate a session with the \COMPONENT_A3D_LIBRARY. 
@{
*/

/*!
\brief Starts a session with the \COMPONENT_A3D_LIBRARY

This function initializes the internal structures in the \COMPONENT_A3D_LIBRARY. 

\version 2.0

\param iMajorVersion The major version of the \COMPONENT_A3D_API. Set this value to \ref A3D_DLL_MAJORVERSION
\param iMinorVersion The minor version of the \COMPONENT_A3D_API. Set this value to \ref A3D_DLL_MINORVERSION

\return \ref A3D_INITIALIZE_ALREADY_CALLED \n
\return \ref A3D_SUCCESS \n

\warning You must call this function before calling any other functions in the \COMPONENT_A3D_API, with these exceptions:
<ul>
<li>You can call \ref A3DDllGetVersion anytime.</li>
<li>To have the \COMPONENT_A3D_LIBRARY produce an XML trace file, 
you must call \ref A3DDllActivateXMLTrace before calling this function.</li>
</ul>

\par Sample code

\include BaseFunctions.cpp
*/
A3D_API (A3DStatus, A3DDllInitialize,(A3DInt32 iMajorVersion, A3DInt32 iMinorVersion));


/*!
\brief Disables internal SIGSEGV handling (Linux only)

This function deactivates the handling of the SIGSEGV signal on Linux.
By default, SIGSEGV is handled and an exception is thrown to return \ref A3D_EXCEPTION.

\warning You must call this function before \ref A3DDllInitialize

\return \ref A3D_SUCCCESS \n
\return \ref A3D_ERROR if not on Linux \n
*/
A3D_API( A3DStatus, A3DDisableHandleSIGSEGV, ());

/*!
\brief Terminates a session with the \COMPONENT_A3D_LIBRARY

This function terminates a session with the \COMPONENT_A3D_LIBRARY. 
It deallocates memory it has previously allocated for its internal use. 

You must call this function to end a session with the \COMPONENT_A3D_LIBRARY.

\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_SUCCESS \n

\warning You can call this function only after successfully calling \ref A3DDllInitialize.

\warning When your process is done with A3DLIBS.dll (after calling \ref A3DDllTerminate), you \b MUST unload that DLL, 
as shown in the sample code for \ref A3DDllInitialize.
Unloading the DLL helps to avoid conflicts that can occur when multiple processes use A3DLIBS.dll. 

\warning Processes must avoid parallel access to A3DLIBS.dll. 


*/
A3D_API (A3DStatus, A3DDllTerminate,());

/*!
\brief Gets the version identifiers for the currently installed \COMPONENT_A3D_LIBRARY

This function returns the version of the currently installed \COMPONENT_A3D_LIBRARY.
Use these version identifiers to determine whether that library is compatible with your application.
The value returned through the \c piMajorVersion argument is identical to the Acrobat version identifier. 
The value returned through the \c piMinorVersion argument is specific to the \COMPONENT_A3D_LIBRARY.

To ensure compatibility,
the \ref A3D_DLL_MAJORVERSION must be identical 
to the major version of currently installed \COMPONENT_A3D_LIBRARY, and 
the \ref A3D_DLL_MINORVERSION must be less than or equal 
to the minor version of the currently installed \COMPONENT_A3D_LIBRARY.

You can call \ref A3DDllGetVersion anytime, even before calling \ref A3DDllInitialize and after calling \ref A3DDllTerminate.
This function does not allocate memory. 	

\version 2.0

\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDllGetVersion,(A3DInt32* piMajorVersion, A3DInt32* piMinorVersion));

/*!
@} <!-- End of module a3d_base_functions --> 
*/

/*!
\defgroup a3d_message_functions Custom Report
\ingroup a3d_base_module
\brief Specifies custom reporting of messages

The function and types in this section enable you to customize reporting of
messages, warnings, and errors from the \COMPONENT_A3D_LIBRARY. 

These messages are the ones returned by the PRC core reading, being independent
from the ones being potentially sent to log file, when using \ref A3DAsmModelFileLoadFromFile.
@{
*/

/*!
A callback function the \COMPONENT_A3D_LIBRARY invokes to report general messages. 
These messages are English only.

If this callback function is not provided, the library sends warning messages to the null device. 

\version 2.0
*/
typedef A3DInt32 (*A3DCallbackReportMessage)(A3DUTF8Char*); 

/*!
A callback function the \COMPONENT_A3D_LIBRARY invokes to report warnings. 
The returned message begins with a unique error code, which you can use for localization.
In some cases, the second argument provides additional information about the warning. These messages are English only.

If this callback function is not provided, the library sends warning messages to the null device. 

\version 2.0
*/
typedef A3DInt32 (*A3DCallbackReportWarning)(A3DUTF8Char*, A3DUTF8Char*);

/*!
A callback function the \COMPONENT_A3D_LIBRARY invokes to report error messages. 
The returned message begins with a unique error code, which you can use for localization.
In some cases, the second argument provides additional information about the error. These messages are English only.

If this callback function is not provided, the library sends error messages to the null device. 

\version 2.0
*/
typedef A3DInt32 (*A3DCallbackReportError)(A3DUTF8Char*, A3DUTF8Char*);

/*!
\brief Specifies custom functions the \COMPONENT_A3D_LIBRARY uses for reporting messages, warnings and errors. 

This function configures the \COMPONENT_A3D_LIBRARY with the callback functions 
the \COMPONENT_A3D_LIBRARY uses for reporting messages, warnings and errors.

To ensure your callback is aware of early-occurring messages, call the \ref A3DDllSetCallbacksReport function immediately 
after the \ref A3DDllInitialize function is successfully called.

\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_SUCCESS \n

\warning If you do not call this function, the \COMPONENT_A3D_LIBRARY sends all messages to the null device.
The first string returned by the two functions above corresponds to a unique error code.
You can use that code to localize messages supplied to your users.

\par Sample code
\include OutputFunctions.cpp

*/
A3D_API (A3DStatus, A3DDllSetCallbacksReport,( A3DCallbackReportMessage, A3DCallbackReportWarning, A3DCallbackReportError ));

/*!
@} <!-- End of module a3d_message_functions-->
*/

/*!
\defgroup a3d_progress_functions Custom Progress-Indicator  
\ingroup a3d_base_module
\brief Specifies a custom progress indicator

This section describes the function and types that enable you 
to specify a custom progress indicator, such as a status bar.
@{
*/

/*!
A callback function the \COMPONENT_A3D_LIBRARY invokes as it prepares 
to perform a potentially time-consuming process. 
The argument identifies the processing phase, as follows:
<TABLE border=1 rules="all" cellspacing="1">
	<TR><TH>Processing phase</TH><TH>Description</TH></TR>
	<TR>
		<TD>1</TD><TD>Parsing the file</TD>
	</TR>
	<TR>
		<TD>2</TD><TD>Writing file </TD>
	</TR>
	<TR>
		<TD>3</TD><TD>Reading or building the model, which follows parsing the file (processing phase 1)</TD>
	</TR>
</TABLE>

\version 2.0
*/
typedef A3DVoid (*A3DCallbackProgressStart)(A3DInt32);
/*!
A callback function the \COMPONENT_A3D_LIBRARY invokes 
to report an approximate size of the PRC stream being processed.
The size is independent of units and is bounded only by the limit of the A3DInt32 type.

\version 2.0
*/
typedef A3DVoid (*A3DCallbackProgressSize)(A3DInt32);
/*!
A callback function the \COMPONENT_A3D_LIBRARY intermittently invokes while processing the PRC stream. 
As processing proceeds, the argument increments from 0 to a maximum of Size, where
Size is the argument provided in \ref A3DCallbackProgressSize.

\version 2.0
*/
typedef A3DVoid (*A3DCallbackProgressIncrement)(A3DInt32);
/*!
A callback function the \COMPONENT_A3D_LIBRARY invokes when it finishes the process.

\version 2.0
*/
typedef A3DVoid (*A3DCallbackProgressEnd)();

/*!
A callback function the \COMPONENT_A3D_LIBRARY invokes to provide a text string relevant to the processing phase. 
In the case of reading PRC data from a file, the argument provides the name of the file containing the PRC stream.

\version 2.0
*/
typedef A3DVoid (*A3DCallbackProgressTitle)(A3DUTF8Char* msg);

/*!
\fn A3DStatus A3DDllSetCallbacksProgress(A3DCallbackProgressStart fnPrgStart, A3DCallbackProgressSize fnPrgSize,
	A3DCallbackProgressIncrement fnPrgIncrement, A3DCallbackProgressEnd fnPrgEnd, A3DCallbackProgressTitle fnPrgTitle,
	A3DInt32* piBreak)
\brief Sets callbacks for progress bar facility

This function configures the \COMPONENT_A3D_LIBRARY with the callback functions 
that implement a custom progress indicator, such as a status bar. 

The last argument passed to this function sets a break. 
The \COMPONENT_A3D_LIBRARY checks this variable 
at every significant step in processing the PRC.
If the value is non-zero, the \COMPONENT_A3D_LIBRARY stops processing the PRC data.

\version 2.0

\attention The \COMPONENT_A3D_LIBRARY stops processing the PRC data if the last argument passed to this function is non-zero.

\par Sample code
\include ProgressbarFunctions.cpp

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_CALLBACK_INVALID_BREAK_VALUE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDllSetCallbacksProgress,(A3DCallbackProgressStart, 
												A3DCallbackProgressSize, 
												A3DCallbackProgressIncrement, 
												A3DCallbackProgressEnd, 
												A3DCallbackProgressTitle,
												A3DInt32*));

/*!
@} <!-- End of module a3d_progress_functions -->
*/

/*!
\defgroup a3d_malloc_functions Custom Memory Allocation 
\ingroup a3d_base_module
\brief Specifies custom memory-allocation functions

This section describes the function and types that enable you 
to specify custom memory-allocation functions that the \COMPONENT_A3D_LIBRARY uses 
in place of the standard \c malloc and \c free functions.
@{
*/

/*!
A callback function the \COMPONENT_A3D_LIBRARY invokes to allocate memory.

\version 2.0
*/
typedef A3DPtr (*A3DCallbackMemoryAlloc)(size_t);

/*!
A callback function the \COMPONENT_A3D_LIBRARY invokes to free memory.

\version 2.0
*/
typedef A3DVoid (*A3DCallbackMemoryFree)(A3DPtr);

/*!
\brief Specifies custom memory-allocation functions
This function specifies callback functions the \COMPONENT_A3D_LIBRARY uses for memory allocation and and deallocation. 

If this function is not called, the standard <code>malloc</code> and <code>free</code> functions 
are used for memory allocation and deallocation.

\version 2.0

\par Sample code
\include AllocationFunctions.cpp

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_CALLBACK_MEMORY_FUNCTIONS_ALREADY_SET \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DDllSetCallbacksMemory,(	A3DCallbackMemoryAlloc, 
												A3DCallbackMemoryFree ));
/*!
@} <!-- End of module a3d_malloc_functions -->
*/

/*!
\defgroup a3d_type_functions Type Determination
\ingroup a3d_base_module
\brief Determines the type of a PRC entity
@{
*/

/*!
\brief Gets the actual type of the entity

This function returns an integer that specifies an Entity type. 
The integer corresponds to one of the values described by the \ref A3DEEntityType enumeration. 

\version 2.0

\par Sample code
\include TypeCastingFunctions.cpp

\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n

\sa A3DEntity
*/
A3D_API (A3DStatus, A3DEntityGetType,(	const A3DEntity* pEntity,
													A3DEEntityType* peEntityType));

/*!
\ingroup a3d_type_functions
\brief Indicates whether an entity base type corresponds to the \ref kA3DTypeRootBaseWithGraphics type enumeration.

This function returns a value of <code>TRUE</code> 
if an entity type is based on the abstract root type 
for a PRC entity that can represent graphic data. 
Such an abstract root type is identified by the \ref kA3DTypeRootBaseWithGraphics type enumeration. 

\version 2.0
You may need to use this function to sort entities for particular treatments.

*/
A3D_API (A3DBool, A3DEntityIsBaseWithGraphicsType,(const A3DEntity* pEntity));

/*!
\ingroup a3d_type_functions
\brief Indicates whether an entity base type corresponds to the \ref kA3DTypeRootBase type enumeration

This function returns a value of <code>TRUE</code> 
if an entity type is based on the abstract root type 
for any PRC entity (with or without graphic data). 
Such an abstract root type is identified by the \ref kA3DTypeRootBase type enumeration. 

\version 2.0
You may need to use this function to sort entities for particular treatments.

*/
A3D_API (A3DBool, A3DEntityIsBaseType,(const A3DEntity* pEntity));

/*!
@} <!-- End of module a3d_type_functions -->
*/

/*!
\defgroup a3d_debug_functions XML Trace File Generation
\ingroup a3d_base_module
\brief Generates an XML trace file (for debugging).

@{
*/

/*!
\ingroup a3d_debug_functions
This function generates an XML trace file that lists the \COMPONENT_A3D_API functions 
that are called during a session. 
A session begins when you call the \ref A3DDllInitialize function 
and ends when you call the \ref A3DDllTerminate function.

\version 2.0

To activate an XML trace, call this function BEFORE calling any other \COMPONENT_A3D_API functions.

\warning This function may slow down your process. Use XML trace only for debugging.
\warning The XML file produced by this feature can be very large.
	It includes entries for every COMPONENT_A3D_API function call made during a session. 
\note XML trace file is created in the temporary folder (<b>TEMP</b> for Windows)

*/
A3D_API (A3DVoid, A3DDllActivateXMLTrace,(A3DBool activate));

A3D_API (A3DStatus, A3DXmlParsing,(	const A3DAsmModelFile* pModelfile,
												const A3DUTF8Char* pcFileName));

/*!
@} <!-- End of module a3d_debug_functions -->
*/

/*!
@} <!-- End of module a3d_base_module -->
*/

A3D_API (A3DStatus, A3DSDKInitializeInternalPointer,( HMODULE hModule));
#endif	/*	__A3DPRCBASE_H__ */
