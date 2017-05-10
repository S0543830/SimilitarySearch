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
\brief      Header file for initializing data
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/
// File Version: 10.06.18

#ifndef _A3DPDFINITIALIZEMACRO_H_
#define _A3DPDFINITIALIZEMACRO_H_

/*!
Before invoking any function, you must initialize the structure that the data
will be stored in by using this macro.
\attention Use of memset: malloc must be included before this file.
*/
#define A3D_INITIALIZE_DATA( MAC_TYPE, MAC_VALUE) \
	A3D_INITIALIZE_##MAC_TYPE( MAC_VALUE )

/*!
To initialize a data array
*/
#define A3D_INITIALIZE_ARRAY_DATA( MAC_TYPE, MAC_PT_VALUE, MAC_SIZE) \
{	\
	for( A3DUns32 uiInitMacCnt=0; uiInitMacCnt<MAC_SIZE; uiInitMacCnt++) \
	{ A3D_INITIALIZE_##MAC_TYPE( MAC_PT_VALUE[uiInitMacCnt] ) }\
}

#define A3D_INITIALIZE_DATA_VAR( s) \
	{ memset(&(s), 0, sizeof(s)); (s).m_usStructSize = sizeof(s);} 


/*
Do not use the next macro.
Use only A3D_INITIALIZE_DATA or A3D_INITIALIZE_ARRAY_DATA
*/

#define A3D_INITIALIZE_A3DRWParamsExportU3DData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )


#define A3D_INITIALIZE_A3DRWParamsExportPrcData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )



#define A3D_INITIALIZE_A3DRWParamsLoadData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DRWParamsGeneralData( (MAC_VALUE.m_sGeneral)) \
	A3D_INITIALIZE_A3DRWParamsPmiData( (MAC_VALUE.m_sPmi)) \
	A3D_INITIALIZE_A3DRWParamsTessellationData( (MAC_VALUE.m_sTessellation)) \
	A3D_INITIALIZE_A3DRWParamsAssemblyData( (MAC_VALUE.m_sAssembly)) \
	A3D_INITIALIZE_A3DRWParamsMultiEntriesData( (MAC_VALUE.m_sMultiEntries)) \
	A3D_INITIALIZE_A3DRWParamsSpecificLoadData( (MAC_VALUE.m_sSpecifics)) \
	A3D_INITIALIZE_A3DRWParamsIncrementalLoadData( (MAC_VALUE.m_sIncremental))

#define A3D_INITIALIZE_A3DRWParamsIncrementalLoadData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsSpecificLoadData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DRWParamsCatiaV4Data( (MAC_VALUE.m_sCatiaV4)) \
	A3D_INITIALIZE_A3DRWParamsCatiaV5Data( (MAC_VALUE.m_sCatiaV5)) \
	A3D_INITIALIZE_A3DRWParamsUnigraphicsData( (MAC_VALUE.m_sUnigraphics)) \
	A3D_INITIALIZE_A3DRWParamsProEData( (MAC_VALUE.m_sProE)) \
	A3D_INITIALIZE_A3DRWParamsStepData( (MAC_VALUE.m_sStep)) \
	A3D_INITIALIZE_A3DRWParamsIGESData( (MAC_VALUE.m_sIGES)) \
	A3D_INITIALIZE_A3DRWParamsIFCData( (MAC_VALUE.m_sIFC)) \
	A3D_INITIALIZE_A3DRWParamsJTData( (MAC_VALUE.m_sJT)) \
	A3D_INITIALIZE_A3DRWParamsParasolidData( (MAC_VALUE.m_sParasolid)) \
	A3D_INITIALIZE_A3DRWParamsSolidworksData( (MAC_VALUE.m_sSolidworks)) \
	A3D_INITIALIZE_A3DRWParamsInventorData((MAC_VALUE.m_sInventor))

#define A3D_INITIALIZE_A3DRWParamsSolidworksData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	(MAC_VALUE).m_bLoadAllConfigsData = false;

#define A3D_INITIALIZE_A3DRWParamsInventorData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	(MAC_VALUE).m_bUseTessForFile = true;

#define A3D_INITIALIZE_A3DRWParamsParasolidData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsJTData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	(MAC_VALUE).m_eReadTessellationLevelOfDetail = JTTessLODHigh;

#define A3D_INITIALIZE_A3DRWParamsIGESData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsIFCData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	(MAC_VALUE).m_bFACETED_BREPAsOneFace = true;

#define A3D_INITIALIZE_A3DRWParamsStepData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	(MAC_VALUE).m_eNameFromNAUO=kA3DStepNameFromNAUO_DESCRIPTION; \
	(MAC_VALUE).m_bSplitSHELL_BASED_SURFACE_MODEL=true; \
	(MAC_VALUE).m_bHealOrientations = false;

#define A3D_INITIALIZE_A3DRWParamsProEData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )\
	(MAC_VALUE).m_eFamilyTables = A3DProEFamTabOrUseTessellation;\
	(MAC_VALUE).m_bBoolOpUseGenericIfNoTess = false;\
	(MAC_VALUE).m_bFlexCompUseGenericIfNoTess = false;\
	(MAC_VALUE).m_bHideSkeletons = false;

#define A3D_INITIALIZE_A3DRWParamsUnigraphicsData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsCatiaV5Data( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsCatiaV4Data( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsMultiEntriesData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsAssemblyData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsSearchDirData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsTessellationData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsPmiData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DRWParamsGeneralData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )


#define A3D_INITIALIZE_A3DAsmModelFileData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )



#define A3D_INITIALIZE_A3DVector3dData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DVector2dData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )




#define A3D_INITIALIZE_A3DPDFPageData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFPageData2( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFTextData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFImageData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDF3DAnnotData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDF3DArtworkData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( (MAC_VALUE).m_sPMIColor )

#define A3D_INITIALIZE_A3DPDF3DArtworkData2( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( (MAC_VALUE).m_sPMIColor ) \
	A3D_INITIALIZE_A3DPDFSectionDisplayData( (MAC_VALUE).m_sDisplaySectionData )

#define A3D_INITIALIZE_A3DPDFSectionDisplayData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( (MAC_VALUE).m_sCuttingPlaneColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( (MAC_VALUE).m_sIntersectionColor )

#define A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFRectData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFSnapshotOptionsData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFViewData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DVector3dData( (MAC_VALUE.m_sPosition)) \
	A3D_INITIALIZE_A3DVector3dData( (MAC_VALUE.m_sTarget)) \
	A3D_INITIALIZE_A3DVector3dData( (MAC_VALUE.m_sUpVector))

#define A3D_INITIALIZE_A3DPDFDocumentInformationData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFTextDataEx( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFTableData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFLinkData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFFieldData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRectData( (MAC_VALUE.m_sRect)) 

#define A3D_INITIALIZE_A3DStream3DPDFData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFAnimTransformationData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFAnimAppearanceData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )\
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sColor )

#define A3D_INITIALIZE_A3DPDFAnimCameraData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )\
	A3D_INITIALIZE_A3DVector3dData( (MAC_VALUE.m_sPosition)) \
	A3D_INITIALIZE_A3DVector3dData( (MAC_VALUE.m_sTarget)) \
	A3D_INITIALIZE_A3DVector3dData( (MAC_VALUE.m_sUpVector))

#define A3D_INITIALIZE_A3DPDFAnimKeyFrameData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFAnimMotionData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFAnimMotionData2( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFTargetEntityData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFAnimationData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFButtonData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sFillColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sBorderColor )

#define A3D_INITIALIZE_A3DPDFTextFieldData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sBorderColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sFillColor )

#define A3D_INITIALIZE_A3DPDFCheckBoxData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sFillColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sBorderColor )

#define A3D_INITIALIZE_A3DPDFRadioButtonData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sFillColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sBorderColor )

#define A3D_INITIALIZE_A3DPDFListBoxData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sFillColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sBorderColor )

#define A3D_INITIALIZE_A3DPDFDropDownListData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sFillColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sBorderColor )

#define A3D_INITIALIZE_A3DPDFDigitalSignatureData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sFillColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sBorderColor )

#define A3D_INITIALIZE_A3DPDFBarCodeData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sFillColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sBorderColor )

#define A3D_INITIALIZE_A3DPDF3DNodesReferencesData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFBomElementInfoData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )

#define A3D_INITIALIZE_A3DPDFGraphicRectangleData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )\
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sLineColor ) \
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sFillColor )

#define A3D_INITIALIZE_A3DPDFGraphicLineData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )\
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sLineColor ) 

#define A3D_INITIALIZE_A3DPDFGraphicArcData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )\
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sArcColor )

#define A3D_INITIALIZE_A3DPDFGraphicBezierCurveData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )\
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sCurveColor )

#define A3D_INITIALIZE_A3DPDFGraphicCompositePathData( MAC_VALUE ) \
	A3D_INITIALIZE_DATA_VAR( MAC_VALUE )\
	A3D_INITIALIZE_A3DPDFRgbColorData( MAC_VALUE.m_sPathColor )



#endif // _A3DPDFINITIALIZEMACRO_H_
