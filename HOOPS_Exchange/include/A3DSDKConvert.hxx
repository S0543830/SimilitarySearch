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

#ifndef __A3DSDKHOOPSEXCHANGELOADER_H__
#define __A3DSDKHOOPSEXCHANGELOADER_H__

class A3DImport;
class A3DExport;


class A3DSDKHOOPSExchangeLoader
{
public:
#ifdef WIN32
	A3DSDKHOOPSExchangeLoader(const TCHAR* pcLibraryPath);
#else
	A3DSDKHOOPSExchangeLoader(const A3DUTF8Char* pcLibraryPath, bool bDisableHandlingSIGSEGV = false);
#endif

	~A3DSDKHOOPSExchangeLoader();

	A3DStatus Import(const A3DImport& sImport);
	A3DStatus Export(A3DExport& sExport) const;
	A3DStatus Convert(const A3DImport& sImport,A3DExport& sExport);

public:

	A3DAsmModelFile* m_psModelFile;
	A3DStatus m_eSDKStatus;
	bool m_bSDKLoaded;
	A3DBool m_bKeepParsedEntities;

private :
#ifdef WIN32
	A3DStatus LoadSDK(const TCHAR* pcLibraryPath);
#else
	A3DStatus LoadSDK(const A3DUTF8Char* pcLibraryPath, bool bDisableHandlingSIGSEGV);
#endif

};

class A3DImport
{
	friend class A3DSDKHOOPSExchangeLoader;
public: 
	A3DImport(const wchar_t* pcFileName);
	A3DImport(const A3DUTF8Char* pcFileName);

	~A3DImport();
public:

	A3DRWParamsLoadData m_sLoadData;

private:
	A3DUTF8Char* m_psFileName;

	void Init(const A3DUTF8Char* pFileName);
};


class A3DExport
{
	friend class A3DSDKHOOPSExchangeLoader;
public: 

	A3DExport(const wchar_t* pcFileName);
	A3DExport(const A3DUTF8Char* pcFileName);
	A3DExport(int* pNbPkParts, int** pPkParts);

	~A3DExport();

public: 

#ifndef HOOPS_PRODUCT_PUBLISH_ADVANCED
	A3DRWParamsExportIgesData		m_sExportIgesData;
	A3DRWParamsExportStepData		m_sExportStepData;
	A3DRWParamsExportJTData			m_sExportJTData;
	A3DRWParamsExportParasolidData  m_sExportParasolidData;
	A3DRWParamsExportStlData		m_sExportStlData;
	A3DRWParamsExportAcisData		m_sExportAcisData;
	A3DRWParamsExportXMLData		m_sExportXMLData;
	A3DRWParamsTranslateToPkPartsData m_sTranslateToPkPartsData;
#endif
	A3DRWParamsExportU3DData		m_sExportU3DData;
	A3DRWParamsExportPrcData        m_sExportPrcData;

private :
	void FindFormat();

	void Init(const A3DUTF8Char* pFileName);

	A3DUTF8Char* m_psFileName;
	A3DEModellerType m_eFormat;

	int* m_pNbPkParts;
	int** m_pPkParts;
};

#endif // __A3DSDKHOOPSEXCHANGELOADER_H__



