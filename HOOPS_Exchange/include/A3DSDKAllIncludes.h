
// EXCHANGE-PUBLISH HEADERS
//
// NOTE: starting with 5.1, HOOPS Publish Lite is discontinued and HOOPS Publish has only an implicit Advanced level.
//
// Common basic headers: the same headers for Publish or Exchange products:
//		A3DSDK.h
//		A3DSDKLicense.h
// Basic headers with restriction for Lite - Version for Publish Lite only:
//		A3DPDFErrorCodes.h
//		A3DPDFPublishLiteRestrictedDefs.h
//		A3DPDFBase.h
// Basic headers with no restriction - Version for Publish Advanced or with-Exchange use (not Lite):
//		A3DSDKErrorCodes.h
//		A3DSDKBase.h
// RW header with restriction for Publish use - Version only for Publish use (Lite or Advanced)(not with-Exchange):
//		A3DPDFReadWrite.h
// RW header with no restriction - Version for with-Exchange use:
//		A3DSDKReadWrite.h
// Publish headers for all Publish use (Lite or Advanced or with-Exchange):
//		A3DPDFPublishSDK.h
//		A3DPDFInitializeFunctions.h
// Exchange headers only for Publish Advanced or with-Exchange use (not Lite):
//		all other A3DSDK*.h. 

// Starting with 5.1, HOOPS Publish is implicitly HOOPS Publish Advanced
#ifdef HOOPS_PRODUCT_PUBLISH
#define HOOPS_PRODUCT_PUBLISH_ADVANCED
#endif


#ifdef HOOPS_PRODUCT_PUBLISH_LITE
// Publish Lite
#include <A3DSDK.h>
#include <A3DPDFErrorCodes.h>
#include <A3DPDFPublishLiteRestrictedDefs.h>
#include <A3DPDFBase.h>
#include <A3DSDKLicense.h>
#include <A3DPDFReadWrite.h>
#else 
// Publish Advanced or Exchange included
#include <A3DSDK.h>
#include <A3DSDKTypes.h>
#include <A3DSDKErrorCodes.h>
#include <A3DSDKBase.h>
#include <A3DSDKRootEntities.h>
#include <A3DSDKGeometry.h>
#include <A3DSDKMisc.h>
#include <A3DSDKGeometryCrv.h>
#include <A3DSDKGeometrySrf.h>
#include <A3DSDKTopology.h>
#include <A3DSDKTessellation.h>
#include <A3DSDKGraphics.h>
#include <A3DSDKStructure.h>
#if defined HOOPS_PRODUCT_PUBLISH_ADVANCED
#include <A3DPDFReadWrite.h> // Publish Advanced : specific file
#else
#include <A3DSDKReadWrite.h> // Exchange included : SDK file
#endif
#include <A3DSDKRepItems.h>
#include <A3DSDKMarkup.h>
#include <A3DSDKGlobalData.h>
#include <A3DSDKTexture.h>
#include <A3DSDKTools.h>
#include <A3DSDKDraw.h>
#include <A3DSDKMath.h>
#include <A3DSDKInitializeFunctions.h>
#include <A3DSDKLicense.h>
#include <A3DSDKAvancedTools.h>
#include <A3DSDKMarkupLeaderDefinition.h>
#include <A3DSDKMarkupDefinition.h>
#include <A3DSDKMarkupText.h>
#include <A3DSDKMarkupSymbol.h>
#include <A3DSDKMarkupDimension.h>
#include <A3DSDKMarkupTolerance.h>
#include <A3DSDKMarkupWelding.h>
#include <A3DSDKDrawing.h>
#include <A3DSDKLicenseKey.h>
#include <A3DSDKConvert.hxx>
#endif

// all Publish products
#if defined HOOPS_PRODUCT_PUBLISH_LITE || defined HOOPS_PRODUCT_PUBLISH_ADVANCED || defined HOOPS_PRODUCT_PUBLISHPLUSEXCHANGE
#include <A3DPDFPublishSDK.h>
#include <A3DPDFInitializeFunctions.h>
#endif
