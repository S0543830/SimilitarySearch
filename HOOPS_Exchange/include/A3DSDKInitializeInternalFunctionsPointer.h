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
\brief      Header file to intialize internal pointer fuctions to make sure that A3DLibs exported fuction called inside A3DLibs use the same pointer (obtain
with GetProcAdress ) as an external application. Only way to remove crash on linux when using the fpic fuction. 
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
 */

#ifndef A3DSDK_INITIALIZE_FUNCTION_POINTERS
#define A3DSDK_INITIALIZE_FUNCTION_POINTERS


#ifdef A3D_STATIC

#include "A3DInternalSDKRedefineFunctions.h"

#ifdef INITIALIZE_FUNCTIONS_POINTERS
#undef INITIALIZE_FUNCTIONS_POINTERS
#endif

#else

#undef A3D_API

#ifdef INITIALIZE_FUNCTIONS_POINTERS
#		define A3D_API(returnvalue,name,params) \
			typedef returnvalue (*PF_##name) params; \
			PF_##name name##_ = NULL; \
			extern "C" returnvalue name params

#include "A3DSDK.h"
#include "A3DSDKTypes.h"
#include "A3DSDKErrorCodes.h"
#include "A3DSDKBase.h"
#include "A3DInternalSDKBase.h"
#include "A3DInternalSDKTools.h"
#include "A3DSDKTessellation.h"
#include "A3DSDKGlobalData.h"
#include "A3DSDKGraphics.h"
#include "A3DSDKStructure.h"
#include "A3DSDKReadWrite.h"
#include "A3DSDKAvancedTools.h"
#include "A3DSDKDrawing.h"
#include "A3DSDKGeometry.h"
#include "A3DSDKGeometryCrv.h"
#include "A3DSDKGeometrySrf.h"
#include "A3DSDKGlobalData.h"
#include "A3DSDKGraphics.h"
#undef	__A3DSDKLICENSE_H__
#include "A3DSDKLicense.h"
#include "A3DSDKMarkup.h"
#include "A3DSDKMarkupLeaderDefinition.h"
#include "A3DSDKMarkupDefinition.h"
#include "A3DSDKMarkupDimension.h"
#include "A3DSDKMarkupDimension.h"


#include "A3DSDKMarkupSymbol.h"
#include "A3DSDKMarkupText.h"
#include "A3DSDKMarkupTolerance.h"
#include "A3DSDKMarkupWelding.h"
#include "A3DSDKMath.h"
#include "A3DSDKMisc.h"
#include "A3DSDKReadWrite.h"
#include "A3DSDKRepItems.h"
#include "A3DSDKRootEntities.h"
#include "A3DSDKStructure.h"
#include "A3DSDKTessellation.h"
#include "A3DSDKTexture.h"
#include "A3DSDKTools.h"
#include "A3DSDKTopology.h"
#include "A3DSDKTypes.h"
#include "A3DSDKDraw.h"
#include "A3DInternalSDKAccelerators.h"
#include "A3DInternalSDKAnimations.h"
#include "A3DInternalSDKMarkupDefinition.h"
#include "A3DInternalSDKNoNameFunctions.h"
#include "A3DInternalSDKProtection.h"
#include "A3DInternalSDKRestrictedTools.h"
#include "A3DInternalSDKTools.h"
#include "A3DInternalSDKCheckInitFunctions.h"
#include "A3DInternalSDKInitializeFunctions.h"

//#if defined HOOPS_PRODUCT_PUBLISH_LITE || defined HOOPS_PRODUCT_PUBLISH_ADVANCED || defined HOOPS_PRODUCT_PUBLISHPLUSEXCHANGE
#include <A3DPDFPublishSDK.h>
//#endif

#else 
#		define A3D_API(returnvalue,name,params) \
			typedef returnvalue (*PF_##name) params; \
			extern PF_##name name##_; \
			extern "C" returnvalue name params 
#endif



#define A3D_API_CALL extern "C"

#endif // A3D_STATIC

#ifdef INITIALIZE_FUNCTIONS_POINTERS

#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif 

A3D_API_CALL A3DStatus A3DSDKInitializeInternalPointer( HMODULE hModule)
{
#undef A3D_API
#ifdef WIN32
	A3DAnimU3DMotionResourceGet_     =	(PF_A3DAnimU3DMotionResourceGet)GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(64));
	
 A3DAnimU3DMotionResourceCreate_ =	(PF_A3DAnimU3DMotionResourceCreate)					GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(65));
 A3DAnimU3DMotionInformationGet_ =	(PF_A3DAnimU3DMotionInformationGet)					GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(66));
 A3DAnimU3DMotionInformationCreate_ = (PF_A3DAnimU3DMotionInformationCreate)			GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(67));
 A3DAnimU3DAnimationModifierGet_ =	(PF_A3DAnimU3DAnimationModifierGet)					GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(68));
 A3DAnimU3DAnimationModifierCreate_ = (PF_A3DAnimU3DAnimationModifierCreate)			GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(69));
 A3DAnimAnimationLibraryGet_ =		(PF_A3DAnimAnimationLibraryGet)						GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(70));
 A3DAnimAnimationLibraryCreate_ = (PF_A3DAnimAnimationLibraryCreate) 					GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(71));
 A3DRootBaseAnimationLibraryGet_ = (PF_A3DRootBaseAnimationLibraryGet)					GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(72));
 A3DRootBaseAnimationLibrarySet_ = (PF_A3DRootBaseAnimationLibrarySet)					GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(73));
 A3DAnimAnimationLibraryAdd_ = (PF_A3DAnimAnimationLibraryAdd)							GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(74));
 A3DPMIHighlight_ = (PF_A3DPMIHighlight) 												GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(239));
 A3DSettingsFor3DPDFConverter_ = (PF_A3DSettingsFor3DPDFConverter)			  		    GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(248));
 A3DCopyAndAdaptBrepModelUnitize_ = (PF_A3DCopyAndAdaptBrepModelUnitize)				GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(243));
 A3DAsmModelFileExportToGraphVizFile_ =	(PF_A3DAsmModelFileExportToGraphVizFile)		GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(249));
 A3DAsmProductOccurrenceCreateAttributeFile_ = (PF_A3DAsmProductOccurrenceCreateAttributeFile) GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(324));
 A3DGlobalFlush_ = (PF_A3DGlobalFlush) 													GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(434));
 A3DTopoFaceLiftCurves_ = (PF_A3DTopoFaceLiftCurves) 									GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(620));
 A3DTopoFaceSetSurface_ = (PF_A3DTopoFaceSetSurface)									GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(630));
 A3DTopoEdgeSetCurve_ = (PF_A3DTopoEdgeSetCurve)										GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(631));
 A3DTopoCoEdgeSetUVCurve_ = (PF_A3DTopoCoEdgeSetUVCurve) GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(632));
 A3DAsmModelFileFindFreeEdgesInTessellation_ = (PF_A3DAsmModelFileFindFreeEdgesInTessellation) GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(1233));
 A3DMiscExtractPrcFromPdf_ = (PF_A3DMiscExtractPrcFromPdf)								GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(1330));
 A3DMiscGetEnglishFontNameFromLocalFontName_ = (PF_A3DMiscGetEnglishFontNameFromLocalFontName) GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(1333));
 A3DMarkupDatumCreate_ =				 (PF_A3DMarkupDatumCreate)						GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2151));
 A3DMkpMarkupSet_ =						(PF_A3DMkpMarkupSet)							GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2152));
 A3DMarkupTextCreate_ =					(PF_A3DMarkupTextCreate)						GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2153));
 A3DMarkupGDTCreate_ =					(PF_A3DMarkupGDTCreate)							GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2154));
 A3DMarkupDimensionCreate_ = (PF_A3DMarkupDimensionCreate)								GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2155));
 A3DMDDimensionValueCreate_ = (PF_A3DMDDimensionValueCreate)							GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2156));
 A3DMDDimensionValueFormatCreate_ = (PF_A3DMDDimensionValueFormatCreate)				GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2157));
 A3DMDFCFDrawingRowCreate_ = (PF_A3DMDFCFDrawingRowCreate)								GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2158));
 A3DMDFeatureControlFrameCreate_ = (PF_A3DMDFeatureControlFrameCreate)					GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2159));
 A3DMDFCFRowDatumCreate_ = (PF_A3DMDFCFRowDatumCreate)									GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2160));
 A3DMarkupTextSet_		 = (PF_A3DMarkupTextSet)										GetProcAddress(hModule,(LPCSTR)MAKEINTRESOURCE(2161));

#	define A3D_API(returntype,name,params) \
	if(name##_ == NULL) \
	name##_ = (PF_##name)GetProcAddress(hModule,#name); 
	
#else // WIN32
#		define A3D_API(returntype,name,params) \
	name##_ = (PF_##name)dlsym(hModule,#name);
#endif // WIN32

#undef 	__A3DPRCSDK_H__
#include "A3DSDK.h"

#undef 	__A3DPRCTYPES_H__
#include "A3DSDKTypes.h"

//#undef __A3DPRCERRORCODES_H__
//#include "A3DSDKErrorCodes.h"

#undef __A3DPRCBASE_H__
#include "A3DSDKBase.h"

/*
#undef	__A3DPRCINTERNALBASE_H__
#include "A3DInternalSDKBase.h"
*/

#undef	__A3DPRCTESSELLATION_H__
#include "A3DSDKTessellation.h"

#undef	__A3DPRCGLOBALDATA_H__
#include "A3DSDKGlobalData.h"

#undef	__A3DPRCGRAPHICS_H__
#include "A3DSDKGraphics.h"

#undef	__A3DPRCSTRUCTURE_H__
#include "A3DSDKStructure.h"

#undef	__A3DPRCREADWRITE_H__
#include "A3DSDKReadWrite.h"

#undef	__A3DSDKADVANCEDTOOLS_H__
#include "A3DSDKAvancedTools.h"

#undef	__A3DPRCDRAWING_H__
#include "A3DSDKDrawing.h"

#undef	__A3DPRCGEOMETRY_H__
#include "A3DSDKGeometry.h"

#undef	__A3DPRCGEOMETRYCRV_H__
#include "A3DSDKGeometryCrv.h"

#undef	__A3DPRCGEOMETRYSRF_H__
#include "A3DSDKGeometrySrf.h"

#undef	__A3DSDKLICENSE_H__
#include "A3DSDKLicense.h"

#undef	__A3DPRCMARKUP_H__
#include "A3DSDKMarkup.h"

 #undef	__A3DPRCMARKUPLEADERDEFINITION__
#include "A3DSDKMarkupLeaderDefinition.h"

 #undef	__A3DPRCMARKUPDEFINITION__
#include "A3DSDKMarkupDefinition.h"

 #undef	__A3DPRCMarkupDimension_H__
#include "A3DSDKMarkupDimension.h"

 #undef	__A3DPRCMARKUPSYMBOL_H__
#include "A3DSDKMarkupSymbol.h"

 #undef __A3D_MARKUPTEXT__
 #undef	__A3DPRCMarkupText_H__
#include "A3DSDKMarkupText.h"

#undef	__A3DPRCMARKUPTOLERANCE_H__
#undef __A3D_MARKUPDATUMN__
#undef __A3D_MARKUPGDT__
#include "A3DSDKMarkupTolerance.h"

 #undef	__A3DPRCMarkupWelding_H__
#include "A3DSDKMarkupWelding.h"

 #undef	__A3DPRCMATH_H__
#include "A3DSDKMath.h"

 #undef	__A3DPRCMISC_H__
#include "A3DSDKMisc.h"

 #undef	__A3DPRCREPITEMS_H__
#include "A3DSDKRepItems.h"

 #undef	__A3DPRCROOTENTITIES_H__
#include "A3DSDKRootEntities.h"

 #undef	__A3DPRCTEXTURE_H__
#include "A3DSDKTexture.h"

 #undef	__A3DPRCTOOLS_H__
#include "A3DSDKTools.h"

 #undef	__A3DPRCTOPOLOGY_H__
#include "A3DSDKTopology.h"

 #undef	__A3DPRCDRAWMODELFILE_H__
#include "A3DSDKDraw.h"

#undef	 __A3DPRCACCELERATORS_H__
#include "A3DInternalSDKAccelerators.h"

 #undef	__A3DPRCANIMATIONS_H__
#include "A3DInternalSDKAnimations.h"

 #undef	__A3DPRCINTERNALMARKUPDEFINITION_H__
#include "A3DInternalSDKMarkupDefinition.h"

 #undef	__A3DINTERNALSDKNONAMEFUNCTION_H__
#include "A3DInternalSDKNoNameFunctions.h"

#undef	 __A3DPRCRESTRICTEDTOOLS_H__
#include "A3DInternalSDKRestrictedTools.h"

//#undef	__A3DPRCINTERNALTOOLS_H__
//#include "A3DInternalSDKTools.h"


//#if defined HOOPS_PRODUCT_PUBLISH_LITE || defined HOOPS_PRODUCT_PUBLISH_ADVANCED || defined HOOPS_PRODUCT_PUBLISHPLUSEXCHANGE
#undef __A3DPDFPUBLISHSDK_H__
#include <A3DPDFPublishSDK.h>
//#endif


	return A3D_SUCCESS;

#undef A3D_API
}
#endif //INITIALIZE_FUNCTIONS_POINTERS

#endif //A3DSDK_INITIALIZE_FUNCTION_POINTERS
