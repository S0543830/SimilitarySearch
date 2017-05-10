// Create structure for facet data
A3DTessBaseData sTessBaseData;
A3D_INITIALIZE_DATA(sTessBaseData);
sTessBaseData.m_uiCoordSize = 9 * facetSize;
sTessBaseData.m_pdCoords = (A3DDouble*) allocCllBck(sTessBaseData.m_uiCoordSize * sizeof(A3DDouble));
 
// Create structure for nomal vector data
A3DTess3DData sTess3DData;
A3D_INITIALIZE_DATA(sTess3DData);
sTess3DData.m_uiNormalSize = 3 * facetSize;
sTess3DData.m_pdNormals = (A3DDouble*) allocCllBck(sTess3DData.m_uiNormalSize * sizeof(A3DDouble));
 
// Total amount of indices is calculated as follows:
// (one normal + one triangle (3 points)) * number of facets 
sTess3DData.m_uiTriangulatedIndexSize = 4 * facetSize;
sTess3DData.m_puiTriangulatedIndexes = (A3DUns32*) allocCllBck(sTess3DData.m_uiTriangulatedIndexSize * sizeof(A3DUns32));
 
// Set up variables used in reading STL data.
A3DUTF8Char name[100];
A3DUTF8Char dummy[100];
A3DDouble x, y, z;
A3DInt32 iRet = 0;
A3DUns32 i = 0;
A3DUns32 j = 0;
const A3DUTF8Char* pcName = NULL;
 
rewind(stlFile);
curr = 0;
facetSize = 0;
memset(sBuffer, 0, A3D_MAX_BUFFER);

while(fgets(sBuffer, A3D_MAX_BUFFER, stlFile) > 0) {
	sscanf(sBuffer, "%s", key);
	if(!_stricmp(key, "solid")) {
		iRet = sscanf(sBuffer, "%s %s", key, name);
		if (iRet != 2)
			sprintf(name,"unnamed");
	} else if (!_stricmp(key, "facet")) {
		iRet = sscanf(sBuffer,"%s %s %lf %lf %lf",key,dummy,&x,&y,&z);
		sTess3DData.m_puiTriangulatedIndexes[4 * facetSize] = i;
		sTess3DData.m_puiTriangulatedIndexes[4 * facetSize + 1] = j;
		sTess3DData.m_puiTriangulatedIndexes[4 * facetSize + 2] = j + 3;
		sTess3DData.m_puiTriangulatedIndexes[4 * facetSize + 3] = j + 6;
		sTess3DData.m_pdNormals[i++] = x;
		sTess3DData.m_pdNormals[i++] = y;
		sTess3DData.m_pdNormals[i++] = z;
		facetSize++;
	} else if (!_stricmp(key, "vertex")) {
		iRet = sscanf(sBuffer, "%s %lf %lf %lf", key, &x, &y, &z);
		sTessBaseData.m_pdCoords[j++] = x;
		sTessBaseData.m_pdCoords[j++] = y;
		sTessBaseData.m_pdCoords[j++] = z;
	}
	curr += strlen(sBuffer);
	prgIncCllBck(curr);
	memset(sBuffer, 0, A3D_MAX_BUFFER);
}

fclose(stlFile);
prgEndCllBck();
 
// one can consider that STL consists in one single face made of total amount of triangles 
A3DTessFaceData sTessFaceData;
A3D_INITIALIZE_DATA(sTessFaceData);
sTessFaceData.m_usUsedEntitiesFlags = kA3DTessFaceDataTriangleOneNormal; 
sTessFaceData.m_uiSizesTriangulatedSize = 1; /* size of the next array */
sTessFaceData.m_puiSizesTriangulated = &facetSize;
sTessFaceData.m_uiStartTriangulated = 0;
 
// so, only one face 
sTess3DData.m_uiFaceTessSize = 1;
sTess3DData.m_psFaceTessData = &sTessFaceData;
A3DTess3D* pTess3D = NULL;
A3DTess3DCreate(&sTess3DData, &pTess3D);
A3DTessBaseSet(pTess3D, &sTessBaseData);
 
// create a PolyBrepModel representation item 
A3DRiPolyBrepModel *pRiPolyBrepModel = NULL;
A3DRiPolyBrepModelData sPolyBrepModelData;
A3D_INITIALIZE_DATA(sPolyBrepModelData);
sPolyBrepModelData.m_bIsClosed = TRUE;
A3DRiPolyBrepModelCreate(&sPolyBrepModelData, &pRiPolyBrepModel);
 
// assign the tessellation to the PolyBrepModel 
A3DRiRepresentationItemData sRiData;
A3D_INITIALIZE_DATA(sRiData);
sRiData.m_pTessBase = pTess3D;
A3DRiRepresentationItemSet(pRiPolyBrepModel, &sRiData);