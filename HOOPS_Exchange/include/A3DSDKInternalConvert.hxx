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

#ifndef __A3DSDKINTERNALCONVERTER_H__
#define __A3DSDKINTERNALCONVERTER_H__

#include <ctype.h>

#ifndef _MAX_PATH
#define _MAX_PATH 1000
#endif

typedef struct
{
	A3DEModellerType eModeller;
	const char *extension;
} MapExtensionCAD;

static const MapExtensionCAD stMapExtensionCAD[] =
{
	{kA3DModellerIges, "IGS"},
	{kA3DModellerIges, "IGES"},
	{kA3DModellerStep, "STP"},
	{kA3DModellerStep, "STEP"},
	{kA3DModellerU3D,  "U3D"},
	{kA3DModellerParasolid,  "X_T"},
	{kA3DModellerParasolid,  "XMT_TXT"},
	{kA3DModellerPrc,  "PRC"},
	{kA3DModellerPDF,  "PDF"},
	{kA3DModellerJt,   "JT"},
	{kA3DModellerWrl,  "WRL"},
	{kA3DModellerWrl,  "VRML" },
	{kA3DModellerStl,  "STL"},
	{kA3DModellerAcis, "SAT"},
	{kA3DModellerAcis, "SAB"},
	{kA3DModellerXML, "XML"}
};


void A3DImport::Init(const A3DUTF8Char* pFileName)
{
	size_t iSize = strlen(pFileName);
	m_psFileName = new A3DUTF8Char[iSize+1];

#ifdef _MSC_VER
	strcpy_s(m_psFileName, iSize+1, pFileName);
#else
	strcpy(m_psFileName,pFileName);
	m_psFileName[iSize] = 0;
#endif

	A3D_INITIALIZE_DATA(A3DRWParamsLoadData, m_sLoadData);
	m_sLoadData.m_sGeneral.m_bReadSolids = true;
	m_sLoadData.m_sGeneral.m_bReadSurfaces = true;
	m_sLoadData.m_sGeneral.m_bReadWireframes = true;
	m_sLoadData.m_sGeneral.m_bReadPmis = true;
	m_sLoadData.m_sGeneral.m_bReadAttributes = true;
	m_sLoadData.m_sGeneral.m_bReadHiddenObjects = true;
	m_sLoadData.m_sGeneral.m_bReadConstructionAndReferences = false;
	m_sLoadData.m_sGeneral.m_bReadActiveFilter = true;
	m_sLoadData.m_sGeneral.m_bReadDrawings = false;
	m_sLoadData.m_sGeneral.m_eReadGeomTessMode = kA3DReadGeomAndTess;
	m_sLoadData.m_sGeneral.m_eDefaultUnit = kA3DUnitUnknown;
	m_sLoadData.m_sTessellation.m_eTessellationLevelOfDetail = kA3DTessLODMedium;
	m_sLoadData.m_sAssembly.m_bUseRootDirectory = true;
	m_sLoadData.m_sMultiEntries.m_bLoadDefault = true;
	m_sLoadData.m_sPmi.m_bAlwaysSubstituteFont = false;
	m_sLoadData.m_sPmi.m_pcSubstitutionFont = (char*) "Myriad CAD";
}


#if defined _UNICODE || defined UNICODE
A3DImport::A3DImport(const A3DUniChar* pcFileName):m_psFileName(NULL)
{
	if (A3DMiscUTF16ToUTF8)
	{
		A3DUTF8Char acFileNameUTF8[_MAX_PATH];
		A3DMiscUTF16ToUTF8(pcFileName, acFileNameUTF8);

		Init(acFileNameUTF8);
	}
}
#endif

A3DImport::A3DImport(const A3DUTF8Char* pcFileName):m_psFileName(NULL)
{
	if (A3DMiscUTF16ToUTF8)
		Init(pcFileName);
}



A3DImport::~A3DImport()
{
	delete [] m_psFileName;
}


#if defined _UNICODE || defined UNICODE
A3DExport::A3DExport(const A3DUniChar* pcFileName) :m_eFormat(kA3DModellerUnknown), m_psFileName(NULL), m_pNbPkParts(NULL), m_pPkParts(NULL)
{
	if (A3DMiscUTF16ToUTF8)
	{
		A3DUTF8Char acFileNameUTF8[_MAX_PATH];
		A3DMiscUTF16ToUTF8(pcFileName, acFileNameUTF8);

		Init(acFileNameUTF8);
	}
}
#endif

A3DExport::A3DExport(const A3DUTF8Char* pcFileName) :m_eFormat(kA3DModellerUnknown), m_psFileName(NULL), m_pNbPkParts(NULL), m_pPkParts(NULL)
{
	Init(pcFileName);
}

A3DExport::A3DExport(int* pNbPkParts, int** pPkParts) : m_pNbPkParts(pNbPkParts), m_pPkParts(pPkParts)
{
	m_psFileName = NULL;
	Init(NULL);
}

A3DExport::~A3DExport()
{
	delete [] m_psFileName;
}

void A3DExport::FindFormat()
{
	if(m_psFileName == NULL)
		return;

	size_t iSize = strlen(m_psFileName);
	char* pExtension = m_psFileName+iSize;
	while(*pExtension != '.' && pExtension != m_psFileName)
		pExtension--;

	if (pExtension == m_psFileName)
		return;

	++pExtension;
	char sExtension[16];

#ifdef _MSC_VER
	strcpy_s(sExtension, pExtension);
	_strupr_s(sExtension);
#else
	strcpy(sExtension,pExtension);
	unsigned int iExt = 0;
	while(sExtension[iExt] != '\0')
	{
		sExtension[iExt] = toupper(sExtension[iExt]);
		iExt++;
	}
#endif

	size_t i, iNbExtension = sizeof(stMapExtensionCAD)/sizeof(MapExtensionCAD);
	for(i = 0; i < iNbExtension && m_eFormat == kA3DModellerUnknown; ++i)
	{
		if(strcmp(stMapExtensionCAD[i].extension,sExtension) == 0)
			m_eFormat = stMapExtensionCAD[i].eModeller;
	}
}

void A3DExport::Init(const A3DUTF8Char* pFileName)
{
#ifndef HOOPS_PRODUCT_PUBLISH_ADVANCED
	A3D_INITIALIZE_DATA(A3DRWParamsExportIgesData, m_sExportIgesData);

	A3D_INITIALIZE_DATA(A3DRWParamsExportStepData, m_sExportStepData);

	A3D_INITIALIZE_DATA(A3DRWParamsExportJTData, m_sExportJTData);
	m_sExportJTData.m_eWriteGeomTessMode = kA3DWriteGeomAndTess;
	m_sExportJTData.m_bWritePMI = TRUE;

	A3D_INITIALIZE_DATA(A3DRWParamsExportParasolidData, m_sExportParasolidData);

	A3D_INITIALIZE_DATA(A3DRWParamsExportStlData, m_sExportStlData);
	m_sExportStlData.m_eTessellationLevelOfDetail = kA3DTessLODMedium;

	A3D_INITIALIZE_DATA(A3DRWParamsExportAcisData, m_sExportAcisData);

	A3D_INITIALIZE_DATA(A3DRWParamsExportXMLData, m_sExportXMLData);
	m_sExportXMLData.m_bExportMetadata=true;
	m_sExportXMLData.m_bExportTransformations=true;
	m_sExportXMLData.m_bExportColorMaterial=true;
	m_sExportXMLData.m_bExportProductInformationByFormat = false;

	A3D_INITIALIZE_DATA(A3DRWParamsTranslateToPkPartsData, m_sTranslateToPkPartsData);

#endif
	A3D_INITIALIZE_DATA(A3DRWParamsExportU3DData, m_sExportU3DData);
	m_sExportU3DData.m_eU3DVersion = kA3DECMA3;

	A3D_INITIALIZE_DATA(A3DRWParamsExportPrcData, m_sExportPrcData);
	m_sExportPrcData.m_eCompressBrepType = kA3DCompressionMedium;

	if(pFileName == NULL)
		return;

	size_t iSize = strlen(pFileName);
	if (iSize == 0)
		return;

	m_psFileName = new A3DUTF8Char[iSize+1];
#ifdef _MSC_VER
	strcpy_s(m_psFileName, iSize+1, pFileName);
#else
	strcpy(m_psFileName,pFileName);
	m_psFileName[iSize] = 0;
#endif

	FindFormat();
}

#ifdef WIN32
A3DSDKHOOPSExchangeLoader::A3DSDKHOOPSExchangeLoader(const TCHAR* pcLibraryPath) :m_psModelFile(NULL), m_eSDKStatus(A3D_ERROR), m_bSDKLoaded(false), m_bKeepParsedEntities(false)
{
	m_eSDKStatus = LoadSDK(pcLibraryPath);
}

A3DStatus A3DSDKHOOPSExchangeLoader::LoadSDK(const TCHAR* pcLibraryPath) 
{
	A3DStatus iRet;
	if(!A3DSDKLoadLibrary(pcLibraryPath))
		return A3D_ERROR;

	m_bSDKLoaded = true;

	A3DLicPutLicense(A3DLicPutLicenseFile, pcCustomerKey, pcVariableKey);

	A3DInt32 iMajorVersion = 0, iMinorVersion = 0;
	iRet = A3DDllGetVersion(&iMajorVersion, &iMinorVersion);
	if (iRet != A3D_SUCCESS)
		return iRet;

	iRet = A3DDllInitialize(A3D_DLL_MAJORVERSION, A3D_DLL_MINORVERSION);
	return iRet;
}

#else
A3DSDKHOOPSExchangeLoader::A3DSDKHOOPSExchangeLoader(const A3DUTF8Char* pcLibraryPath, bool bDisableHandlingSIGSEGV):m_psModelFile(NULL),m_eSDKStatus(A3D_ERROR),m_bSDKLoaded(false)
{
	m_eSDKStatus = LoadSDK(pcLibraryPath, bDisableHandlingSIGSEGV);
}

A3DStatus A3DSDKHOOPSExchangeLoader::LoadSDK(const A3DUTF8Char* pcLibraryPath, bool bDisableHandlingSIGSEGV) 
{
	A3DStatus iRet;
	if(!A3DSDKLoadLibrary(pcLibraryPath))
		return A3D_ERROR;

	m_bSDKLoaded = true;
	A3DLicPutLicense(A3DLicPutLicenseFile, pcCustomerKey, pcVariableKey);

	if (bDisableHandlingSIGSEGV)
		A3DDisableHandleSIGSEGV();

	A3DInt32 iMajorVersion = 0, iMinorVersion = 0;
	iRet = A3DDllGetVersion(&iMajorVersion, &iMinorVersion);
	if (iRet != A3D_SUCCESS)
		return iRet;

	iRet = A3DDllInitialize(A3D_DLL_MAJORVERSION, A3D_DLL_MINORVERSION);
	return iRet;
}
#endif



A3DSDKHOOPSExchangeLoader::~A3DSDKHOOPSExchangeLoader()
{
	if (m_psModelFile)
		A3DAsmModelFileDelete(m_psModelFile);

	if (m_eSDKStatus == A3D_SUCCESS)
		A3DDllTerminate();

	if (m_bSDKLoaded)
		A3DSDKUnloadLibrary();
}

A3DStatus A3DSDKHOOPSExchangeLoader::Import(const A3DImport& sImport)
{
	if (m_eSDKStatus != A3D_SUCCESS)
		return m_eSDKStatus;

	m_bKeepParsedEntities = sImport.m_sLoadData.m_sSpecifics.m_sParasolid.m_bKeepParsedEntities;

	A3DStatus iRet = A3DAsmModelFileLoadFromFile(sImport.m_psFileName, &sImport.m_sLoadData, &m_psModelFile);
	return iRet;
}

A3DStatus A3DSDKHOOPSExchangeLoader::Export(A3DExport& sExport) const
{
	if (m_eSDKStatus != A3D_SUCCESS)
		return m_eSDKStatus;

	A3DStatus iRet = A3D_ERROR;

#ifndef HOOPS_PRODUCT_PUBLISH_ADVANCED
	if (sExport.m_pNbPkParts && sExport.m_pPkParts)
	{
		iRet = A3DAsmModelFileTranslateToPkParts(	m_psModelFile, 
													&sExport.m_sExportParasolidData, 
													&sExport.m_sTranslateToPkPartsData, 
													sExport.m_pNbPkParts,
													sExport.m_pPkParts);

		if (!iRet && !m_bKeepParsedEntities)
			iRet = A3D_WRITE_KEEPPARSEDENTITIES_DISABLED;
		return iRet;
	}
#endif

	if (m_psModelFile == NULL)
		return A3D_ERROR;

	switch (sExport.m_eFormat)
	{
#ifndef HOOPS_PRODUCT_PUBLISH_ADVANCED
	case kA3DModellerIges:
		iRet = A3DAsmModelFileExportToIgesFile(m_psModelFile, &sExport.m_sExportIgesData, sExport.m_psFileName);
		break;
	case kA3DModellerStep :
		iRet = A3DAsmModelFileExportToStepFile(m_psModelFile, &sExport.m_sExportStepData, sExport.m_psFileName);
		break;
	case kA3DModellerJt :
		iRet = A3DAsmModelFileExportToJTFile(m_psModelFile, &sExport.m_sExportJTData, sExport.m_psFileName);
		break;
	case kA3DModellerParasolid :
		iRet = A3DAsmModelFileExportToParasolidFile(m_psModelFile, &sExport.m_sExportParasolidData, sExport.m_psFileName);
		break;
	case kA3DModellerWrl :
		iRet = A3DAsmModelFileExportToVrmlFile(m_psModelFile, sExport.m_psFileName);
		break;
	case kA3DModellerStl :
		iRet = A3DAsmModelFileExportToStlFile(m_psModelFile, &sExport.m_sExportStlData, sExport.m_psFileName);
		break;
	case kA3DModellerAcis :
		iRet = A3DAsmModelFileExportToAcisFile(m_psModelFile, &sExport.m_sExportAcisData, sExport.m_psFileName);
		break;
	case kA3DModellerXML :
		iRet = A3DAsmModelFileExportToXMLFile(m_psModelFile, &sExport.m_sExportXMLData, sExport.m_psFileName,NULL,NULL,NULL);
		break;
#endif
	case kA3DModellerU3D :
		iRet = A3DAsmModelFileExportToU3DFile(m_psModelFile, &sExport.m_sExportU3DData, sExport.m_psFileName);
		break;
	case kA3DModellerPrc :
		iRet = A3DAsmModelFileExportToPrcFile(m_psModelFile, &sExport.m_sExportPrcData, sExport.m_psFileName,NULL);
		break;
	default :
		iRet = A3D_WRITE_WRITER_NOT_IMPLEMENTED;
		break;
	}

	return iRet ;
}

A3DStatus A3DSDKHOOPSExchangeLoader::Convert(const A3DImport& sImport, A3DExport& sExport)
{
	A3DStatus iRet = Import(sImport);
	if (iRet != A3D_SUCCESS && iRet != A3D_LOAD_MISSING_COMPONENTS)
		return iRet;

	iRet = Export(sExport);
	return iRet;
}
#endif // __A3DSDKINTERNALCONVERTER_H__


