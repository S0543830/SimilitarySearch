// PDF3dReader.h

#pragma once

#include <string>
#include <iostream>

#define INITIALIZE_A3D_API
#include <A3DSDKIncludes.h>
#include <A3DSDKLicenseKey.h>

#include <msclr\marshal_cppstd.h>

#include "Face.h"

using namespace msclr::interop;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO; 
using namespace System::Reflection;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

#define CHECK_RET(function_call) {\
	iRet = function_call; if(iRet != A3D_SUCCESS) { std::cout << "Error number=" << iRet << std::endl; return iRet; }\
}

namespace SimilaritySearch 
{
	namespace Pdf3DReader 
	{
		
		public ref class Pdf3DReaderService
		{
		public:
			
			Pdf3DReaderService()
			{
			}

			~Pdf3DReaderService()
			{
				if (stOut && stOut != stdout)
					fclose(stOut);
				stOut = stdout;
				Terminate();
			}

			!Pdf3DReaderService()
			{
				Terminate();
			}

			int ReadPdf3D(String^ pdf3DFileName, [Out] List<Face^>^% faceList)
			{
				if (!Init())
				{
					printf("Cannot initialize HOOPS Exchange toolkit\n");
					return A3D_ERROR;
				}
				
				A3DAsmModelFile* pModelFile = sHoopsExchangeLoader->m_psModelFile;

				A3DStream3DPDFData* pStream3DPDFData;
				A3DInt32 iNumStreams;
				A3DGet3DPDFStreams(marshal_as<std::string>(pdf3DFileName).c_str(), &pStream3DPDFData, &iNumStreams);
				// a real use case might parse every stream in the input file. Here, we just take the first one (pStream3DPDFData[0]).
				if (pStream3DPDFData[0].m_bIsPrc) // test whether the data is PRC or U3D
				{
					// even an input PRC file must be read in memory and mapped into modelfile data structures
					A3DRWParamsPrcReadHelper* pPrcReadHelper;
					A3DAsmModelFileLoadFromPrcStream(pStream3DPDFData[0].m_pcStream, pStream3DPDFData[0].m_iLength, &pPrcReadHelper, &pModelFile);
				}
				else
				{
					printf("Cannot read PDF file containing U3D\n");
					return A3D_NOT_IMPLEMENTED;
				}

				A3DStatus iRet;
				// Comment in this code in if you physical properties one day
				//A3DPhysicalPropertiesData sPhysPropsData;
				//A3D_INITIALIZE_DATA(A3DPhysicalPropertiesData, sPhysPropsData);
				//iRet = A3DComputeModelFilePhysicalProperties(pModelFile, &sPhysPropsData);

				// Retrieve files path from model files
				A3DUns32 nbFiles = 0, nbAssemblyFiles = 0, nbMissingFiles = 0;
				A3DUTF8Char** ppPaths = NULL, ** ppAssemblyPaths = NULL, ** ppMissingPaths = NULL;
				CHECK_RET(A3DAsmGetFilesPathFromModelFile(sHoopsExchangeLoader->m_psModelFile, &nbFiles, &ppPaths, &nbAssemblyFiles,
					&ppAssemblyPaths, &nbMissingFiles, &ppMissingPaths));

				faceList = gcnew List<Face^>();
				return TraverseModel(pModelFile, faceList);
			}

		internal:
			/// <summary>
			/// Load HOOPS Exchange DLL and check if the license is valid.
			/// </summary>
			/// <returns>
			/// true if DLL has been loaded and the license is valid.
			/// </returns>
			bool Init()
			{
				if (stbA3DLoaded)
					return true;

#	ifdef _WIN64
				String^ libPath = _T("..\\..\\..\\..\\HOOPS_Exchange\\bin\\win64\\");
#	else
				String^ libPath = _T("..\\..\\..\\..\\HOOPS_Exchange\\bin\\win32\\");
#	endif
				String^ codeBase = Assembly::GetExecutingAssembly()->CodeBase;
				UriBuilder^ uri = gcnew UriBuilder(codeBase);
				String^ path = Uri::UnescapeDataString(uri->Path);
				libPath = Path::Combine(Path::GetDirectoryName(path), libPath);

				if (!A3DSDKLoadLibrary(marshal_as<std::string>(libPath).c_str()))
				{
					printf("Cannot load the HOOPS Exchange library\n");
					return false;
				}

				A3DLicPutLicense(A3DLicPutLicenseFile, pcCustomerKey, pcVariableKey);
				A3DInt32 iMajorVersion = 0, iMinorVersion = 0;
				A3DDllGetVersion(&iMajorVersion, &iMinorVersion);
				if (A3DDllInitialize(A3D_DLL_MAJORVERSION, A3D_DLL_MINORVERSION) != A3D_SUCCESS)
				{
					printf("Cannot initialize the HOOPS Exchange library\n");
					A3DSDKUnloadLibrary();
					return false;
				}

				sHoopsExchangeLoader = new A3DSDKHOOPSExchangeLoader(marshal_as<std::wstring>(libPath).c_str());
				if (sHoopsExchangeLoader->m_eSDKStatus != A3D_SUCCESS)
				{
					printf("Cannot initialize the A3DSDKHOOPSExchangeLoader\n");
					A3DSDKUnloadLibrary();
					return false;
				}

				stbA3DLoaded = true;

				return true;
			}

			void Terminate()
			{
				if (stbA3DLoaded)
				{
					A3DDllTerminate();
					A3DSDKUnloadLibrary();
					if (sHoopsExchangeLoader != NULL)
						delete sHoopsExchangeLoader;
					stbA3DLoaded = false;
				}
			}

			static A3DStatus TraverseModel(const A3DAsmModelFile* pModelFile, List<Face^>^% faceList)
			{
				A3DStatus iRet = A3D_SUCCESS;
				A3DAsmModelFileData sData;
				A3D_INITIALIZE_DATA(A3DAsmModelFileData, sData);

				iRet = A3DAsmModelFileGet(pModelFile, &sData);
				if (iRet == A3D_SUCCESS)
				{
					A3DUns32 ui;
					for (ui = 0; ui < sData.m_uiPOccurrencesSize; ++ui)
						TraversePOccurrence(sData.m_ppPOccurrences[ui], faceList);

					CHECK_RET(A3DAsmModelFileGet(NULL, &sData));
				}
				else
				{
					printf("Cannot retrieve the model file\n");
				}

				return iRet;
			}

			static A3DStatus TraversePOccurrence(const A3DAsmProductOccurrence* pOccurrence, List<Face^>^% faceList)
			{
				A3DStatus iRet = A3D_SUCCESS;
				A3DAsmProductOccurrenceData sData;
				A3D_INITIALIZE_DATA(A3DAsmProductOccurrenceData, sData);

				iRet = A3DAsmProductOccurrenceGet(pOccurrence, &sData);
				if (iRet == A3D_SUCCESS)
				{
					A3DUns32 ui;

					// Transformation of the occurrence
					//sData.m_pLocation, occurrence);

					if (sData.m_pPrototype)
					{
						TraversePOccurrence(sData.m_pPrototype, faceList);
					}

					if (sData.m_pExternalData)
					{
						TraversePOccurrence(sData.m_pExternalData, faceList);
					}

					for (ui = 0; ui < sData.m_uiPOccurrencesSize; ++ui)
						TraversePOccurrence(sData.m_ppPOccurrences[ui], faceList);

					if (sData.m_pPart)
						TraversePartDef(sData.m_pPart, faceList);

					CHECK_RET(A3DAsmProductOccurrenceGet(NULL, &sData));
				}
				else
				{
					printf("Cannot retrieve the product occurence data\n");
				}

				return iRet;
			}

			static A3DStatus TraversePartDef(const A3DAsmPartDefinition* pPart, List<Face^>^% faceList)
			{
				A3DStatus iRet = A3D_SUCCESS;
				A3DAsmPartDefinitionData sData;
				A3D_INITIALIZE_DATA(A3DAsmPartDefinitionData, sData);

				iRet = A3DAsmPartDefinitionGet(pPart, &sData);
				if (iRet == A3D_SUCCESS)
				{
					A3DUns32 ui;

					for (ui = 0; ui < sData.m_uiRepItemsSize; ++ui)
					{
						TraverseRepItem(sData.m_ppRepItems[ui], faceList);
					}

					A3DAsmPartDefinitionGet(NULL, &sData);
				}
				else
				{
					printf("Cannot retrieve the part definition data\n");
				}

				return iRet;
			}

			static A3DStatus TraverseRepItem(const A3DRiRepresentationItem* pRepItem, List<Face^>^% faceList)
			{
				A3DStatus iRet = A3D_SUCCESS;
				A3DEEntityType eType;

				CHECK_RET(A3DEntityGetType(pRepItem, &eType));

				switch (eType)
				{
				case kA3DTypeRiBrepModel:
					iRet = TraverseRepItemContent(pRepItem, faceList);
					break;
				default:
					iRet = A3D_NOT_IMPLEMENTED;
					break;
				}
				return iRet;
			}

			static A3DStatus TraverseRepItemContent(const A3DRiRepresentationItem* pRi, List<Face^>^% faceList)
			{
				A3DStatus iRet = A3D_SUCCESS;
				A3DRiRepresentationItemData sData;
				A3D_INITIALIZE_DATA(A3DRiRepresentationItemData, sData);

				iRet = A3DRiRepresentationItemGet(pRi, &sData);
				if (iRet == A3D_SUCCESS)
				{
					TraverseTessBase(sData.m_pTessBase, faceList);

					A3DRiRepresentationItemGet(NULL, &sData);
				}
				else
				{
					printf("Cannot retrieve the RepItem content\n");
				}

				return A3D_SUCCESS;
			}

			static A3DStatus TraverseTessBase(const A3DTessBase* pTess, List<Face^>^% faceList)
			{
				A3DEEntityType eType;
				A3DStatus iRet = A3DEntityGetType(pTess, &eType);
				if (iRet == A3D_SUCCESS)
				{
					switch (eType)
					{
					case kA3DTypeTess3D:
						Traverse3DTess(pTess, faceList);
						break;
					default:
						break;
					}
				}

				return iRet;
			}

			static A3DStatus Traverse3DTess(const A3DTess3D* pTess, List<Face^>^% faceList)
			{
				A3DTessBaseData sBaseData;
				A3D_INITIALIZE_DATA(A3DTessBaseData, sBaseData);
				A3DStatus iBaseRet = A3DTessBaseGet(pTess, &sBaseData);

				A3DTess3DData sData;
				A3D_INITIALIZE_DATA(A3DTess3DData, sData);
				A3DStatus iRet = A3DTess3DGet(pTess, &sData);

				if (iBaseRet == A3D_SUCCESS && iRet == A3D_SUCCESS && sData.m_bHasFaces)
				{
					// Face data: From here we can retrieve the necessary data form the 3 arrays.
					for (A3DUns32 ui = 0; ui < sData.m_uiFaceTessSize; ++ui)
					{
						A3DTessFaceData& sFace = sData.m_psFaceTessData[ui];

						// Type(s) of the entities of the face. 
						A3DUns16 flags = sFace.m_usUsedEntitiesFlags;
						// ToDo: For now we handle triangles only: No triangle fans and strips
						unsigned short handledOptions = kA3DTessFaceDataTriangle | kA3DTessFaceDataTriangleTextured |
							kA3DTessFaceDataTriangleOneNormal | kA3DTessFaceDataTriangleOneNormalTextured;
						if (flags & handledOptions)
						{
							// For triangle types, the m_puiSizesTriangulated member specifies the number of triangles for this face. 
							A3DUns32 numberOfTriangles = sFace.m_puiSizesTriangulated[0];

							// The description of the triangles of the face begins at this position
							// in the m_puiTriangulatedIndexes array filled above.
							A3DUns32 startTriangulated = sFace.m_uiStartTriangulated;

							// Number of indexes per entry
							int indexesPerEntry = GetIndexesPerEntry(flags);

							// Number of normal per triangle
							int normalsPerTriangle = GetNormalsPerTriangle(flags);

							// Add face data for this face to the list
							faceList->Add(CreateFaceData(indexesPerEntry, normalsPerTriangle, numberOfTriangles, startTriangulated, sBaseData, sData));
						}
						else
						{
							printf("Can only handle faces with the kA3DTessFaceDataTriangleTextured or the kA3DTessFaceDataTriangle flag\n");
							return A3D_NOT_IMPLEMENTED;
						}
					}

					A3DTessBaseGet(NULL, &sBaseData);
					A3DTess3DGet(NULL, &sData);
				}
				else
				{
					printf("Cannot retrieve the 3D face tesselation\n");
				}

				return iRet;
			}

			// ToDo: Handle normalsPerTriangle
			static Face^ CreateFaceData(int indexesPerEntry, int normalsPerTriangle, A3DUns32 numberOfTriangles, A3DUns32 startTriangulated,
				const A3DTessBaseData& sBaseData, const A3DTess3DData& sData)
			{
				// Dimension for normals and vertex coords
				int dimension = 3;

				// The arrays
				array<double>^ vertexCoords = gcnew array<double>(numberOfTriangles * dimension * 3);
				array<double>^ normals = gcnew array<double>(numberOfTriangles * dimension);
				array<int>^ vertexIndices = gcnew array<int>(numberOfTriangles * 3);

				// Normal and vertex indexes: Array of indexes of points in A3DTessBaseData::m_pdCoords.
				// Case indexesPerEntry = 2 and normalsPerTriangle = 3
				// All the vertex and normal indexes are stored in the A3DTess3D.
				// The A3DTessFaceData::m_usUsedEntitiesFlags describe how to interpret these indexes.
				// They are stored as follows for triangle data:
				// N = normal index
				// P = point coordinates index
				// N, P		N, P		N, P		N, P		N, P		N,  P		Face 0
				//	\	first triangle /			\		second triangle /
				//
				// Case indexesPerEntry = 3 and normalsPerTriangle = 3
				// All the vertex, normal and texture indexes are stored in the A3DTess3D.
				// The A3DTessFaceData::m_usUsedEntitiesFlags describe how to interpret these indexes.
				// They are stored as follows for triangle data:
				// N = normal index
				// U = UV index for texture
				// P = point coordinates index
				// N, U, P		N, U, P		N, U, P		N, U, P		N, U, P		N, U, P		Face 0
				//		\		first triangle /			\		second triangle /
				// Extract normals:
				long currentNormal = 0;
				for (A3DUns32 ui = startTriangulated; ui < startTriangulated + (indexesPerEntry * numberOfTriangles * 3) ; ui += indexesPerEntry * 3)
				{
					// Extract normal index
					A3DUns32 normalIndex = sData.m_puiTriangulatedIndexes[ui];

					// Extract normal values
					normals[currentNormal] = sData.m_pdNormals[normalIndex];
					normals[currentNormal + 1] = sData.m_pdNormals[normalIndex + 1];
					normals[currentNormal + 2] = sData.m_pdNormals[normalIndex + 2];

					currentNormal += dimension;
				}

				// Extract vertex coordinates:
				long currentVertex = 0;
				long currentVertexIndex = 0;
				for (A3DUns32 ui = startTriangulated; ui < startTriangulated + (indexesPerEntry * numberOfTriangles * 3) ; ui += indexesPerEntry)
				{
					// Extract vertex index
					A3DUns32 vertexIndex = sData.m_puiTriangulatedIndexes[ui + indexesPerEntry - 1];

					// Extract vertex coordinates
					vertexCoords[currentVertex] = sBaseData.m_pdCoords[vertexIndex];
					vertexCoords[currentVertex + 1] = sBaseData.m_pdCoords[vertexIndex + 1];
					vertexCoords[currentVertex + 2] = sBaseData.m_pdCoords[vertexIndex + 2];

					// Set vertex index
					vertexIndices[currentVertexIndex] = currentVertexIndex;

					currentVertex += dimension;
					++currentVertexIndex;
				}
				Face^ faceData = gcnew Face(vertexCoords, normals, vertexIndices);

				return faceData;
			}

			static int GetIndexesPerEntry(A3DUns16 flags)
			{
				if (flags & (kA3DTessFaceDataTriangle | kA3DTessFaceDataTriangleOneNormalTextured))
					return 2;
				else if (flags & kA3DTessFaceDataTriangleTextured)
					return 3;
				else if (flags & kA3DTessFaceDataTriangleOneNormal)
					return 1;

				return 0;
			}

			static int GetNormalsPerTriangle(A3DUns16 flags)
			{
				if (flags & (kA3DTessFaceDataTriangleOneNormal | kA3DTessFaceDataTriangleOneNormalTextured))
					return 1;
				else if (flags & (kA3DTessFaceDataTriangle | kA3DTessFaceDataTriangleTextured))
					return 3;

				return 0;
			}

	private:
			// Fields:
			bool stbA3DLoaded = false;
			FILE* stOut = stdout;
			int stiSize = 0;
			A3DSDKHOOPSExchangeLoader* sHoopsExchangeLoader;
		};
	}
}
