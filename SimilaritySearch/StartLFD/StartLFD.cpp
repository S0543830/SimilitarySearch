// StartLFD.cpp : main project file.
#include "stdafx.h"


#define	WIDTH			256
#define HEIGHT			256


int			winw = WIDTH, winh = HEIGHT;

pVer		vertex = NULL;
pTri		triangle = NULL;
int			NumVer = 0, NumTri = 0;		// total number of vertex and triangle.


// translate and scale of model 1
Ver Translate1; 
double Scale1;

//std::ofstream pt("C:\\Program Files (x86)\\Aras\\Innovator\\Innovator\\Server\\temp\\ShapeDescriptors\\DATA_desc2.xml"); // Testenvironment server
std::ofstream pt("D:\\DATA_desc2.xml");


int ReadFacesFrom3DPdf(String^ pdf3dFileName, List<Face^>^% faceList)
{
	Pdf3DReaderService^ reader = nullptr;
	try
	{
		reader = gcnew Pdf3DReaderService();
		return reader->ReadPdf3D(pdf3dFileName, faceList);
	}
	finally
	{
		if (reader != nullptr)
			delete reader;
	}
}

// Used in Modell-method
void FindCenter(unsigned char *srcBuff, int width, int height, double *CenX, double *CenY)
{
	int					x, y, count;
	unsigned char		*pImage;
	int					maxX, minX, maxY, minY;

	count = 0;
	pImage = srcBuff;

	// ***********************************************************************************************
	// if use "mean" to each 2D shape independnetly, the origin will be moved a lot in 3D
	// if ues "center" to each 2D shape independnetly, the origin will be moved only a little in 3D
	// if center can be defined in 3D, the origin will not be moved any more.
	// But this will not very robust in 3D similarity transformation
	// In addition, to make center of each 2D shape more close to user drawn 2D shapes,
	// it's better to define center for each 2D shape independently

	// uee center of max and min to be center
	maxX = maxY = -1;
	minX = minY = INT_MAX;
	for (y = 0; y<height; y++)
		for (x = 0; x<width; x++)
		{
			if (*pImage < 255)
			{
				if (x > maxX) maxX = x;
				if (x < minX) minX = x;
				if (y > maxY) maxY = y;
				if (y < minY) minY = y;
			}
			pImage++;
		}

	if (maxX > 0)
	{
		*CenX = (maxX + minX) / 2.0;
		*CenY = (maxY + minY) / 2.0;
	}
	else
		*CenX = *CenY = -1;		// nothing to be rendered
}

// used in Main
void display(void)
{
	int				i, j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	//		glColor3f((GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0);
	for (i = 0; i<NumTri; i++)
	{
		glColor3f((GLfloat)triangle[i].r, (GLfloat)triangle[i].g, (GLfloat)triangle[i].b);
		glBegin(GL_POLYGON);
		for (j = 0; j<triangle[i].NodeName; j++)
			glVertex3d(vertex[triangle[i].v[j]].coor[0], vertex[triangle[i].v[j]].coor[1], vertex[triangle[i].v[j]].coor[2]);
		glEnd();
	}
	glPopMatrix();

	glutSwapBuffers();
}

// Used in Modell-method
void RenderToMem(unsigned char *bmBits, unsigned char *bmColor, pVer CamVertex, pVer v, pTri t, int nv, int nt)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//	gluLookAt(CAMSCALE*CamVertex->coor[0], CAMSCALE*CamVertex->coor[1], CAMSCALE*CamVertex->coor[2],
	gluLookAt(CamVertex->coor[0], CamVertex->coor[1], CamVertex->coor[2],
		0, 0, 0,
		0, 1, 0);
	//				v3.x, v3.y, v3.z);

	vertex = v;
	triangle = t;
	NumVer = nv;
	NumTri = nt;
	display();

	glReadBuffer(GL_BACK);
	//	glReadPixels(0, 0, winw, winh, GL_RED, GL_UNSIGNED_BYTE, bmBits);
	glReadPixels(0, 0, winw, winh, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, bmBits);
	if (bmColor)
		glReadPixels(0, 0, winw, winh, GL_RGB, GL_UNSIGNED_BYTE, bmColor);
}

// Calculate shape descriptors from given model
bool CalculateShapeDescriptors(const std::string& currentPath, pVer vertex, int NumVer, pTri triangle, int NumTri, double src_FdCoeff[ANGLE][CAMNUM][FD_COEFF_NO], double cir_Coeff[ANGLE][CAMNUM], double ecc_Coeff[ANGLE][CAMNUM], double src_ArtCoeff[ANGLE][CAMNUM][ART_ANGULAR][ART_RADIAL])
{
	unsigned char *srcBuff[CAMNUM], *ColorBuff[CAMNUM], *EdgeBuff, *YuvBuff; // CAMNNUM = 10
	int destCam, i, srcCam;
	int CamNumVer[ANGLE], CamNumTri[ANGLE];
	char filename[400];
	pVer CamVertex[ANGLE]; // type pVer only contains coord[3]
	pTri CamTriangle[ANGLE]; // type pTri contains int vertex[15] |int NodeName | double r,g,b
	clock_t	start, finish;	

	// for fourier descriptor
	sPOINT			*Contour;
	unsigned char	*ContourMask;

	double			CenX[CAMNUM], CenY[CAMNUM];
	int				total;

	// initialize ART
	GenerateBasisLUT();
	// initialize: read camera set
	for (destCam = 0; destCam < ANGLE; destCam++) // #define ANGLE 10
	{
		sprintf_s(filename, (currentPath + "/../../../3DAlignment/12_%d").c_str(), destCam);
		if (ReadObj(filename, CamVertex + destCam, CamTriangle + destCam, CamNumVer + destCam, CamNumTri + destCam) != 1)
			return false;
	}

	for (i = 0; i < CAMNUM; i++)
	{
		srcBuff[i] = (unsigned char *)malloc(winw * winh * sizeof(unsigned char));
		ColorBuff[i] = (unsigned char *)malloc(3 * winw * winh * sizeof(unsigned char));
	}
	YuvBuff = (unsigned char *)malloc(3 * winw * winh * sizeof(unsigned char));
	// add edge to test retrieval
	EdgeBuff = (unsigned char *)malloc(winw * winh * sizeof(unsigned char));

	// for Fourier Descriptor
	total = winw * winh;
	Contour = (sPOINT *)malloc(total * sizeof(sPOINT));
	ContourMask = (unsigned char *)malloc(total * sizeof(unsigned char));

	// record execute time --- start
	start = clock();

	// get the translatation and scale of the two model

	// ****************************************************************
	// Corase alignment
	// ****************************************************************

	// Translate and scale model 1
	// fname not needed here:
	// fname[strlen(fname) - 1] = 0x00;
	TranslateScale(vertex, NumVer, triangle, NumTri, NULL, &Translate1, &Scale1);

	// read RED only, so size is winw*winh
	for (srcCam = 0; srcCam < ANGLE; srcCam++)
	{
		// capture CAMNUM silhouette of srcfn to memory
		for (i = 0; i<CAMNUM; i++)
			// RenderToMem(srcBuff[i], ColorBuff[i], CamVertex[srcCam]+i, vertex1, triangle1, NumVer1, NumTri1);
			RenderToMem(srcBuff[i], NULL, CamVertex[srcCam] + i, vertex, triangle, NumVer, NumTri);

		// find center for each shape
		for (i = 0; i<CAMNUM; i++)
			FindCenter(srcBuff[i], winw, winh, CenX + i, CenY + i);

		// get Zernike moment
		FindRadius(srcBuff, CenX, CenY);
		for (i = 0; i<CAMNUM; i++)
		{
			// from depth
			EdgeDetect(EdgeBuff, srcBuff[i], winw, winh);
			ExtractCoefficients(srcBuff[i], src_ArtCoeff[srcCam][i], EdgeBuff, CenX[i], CenY[i]);
		}

		Console::Write("\nStart Calculating FourierDescriptors "); Console::Write(srcCam);
		// get Fourier descriptor
		for (i = 0; i < CAMNUM; i++)
		{
		//	Console::Write(" .");
			FourierDescriptor(src_FdCoeff[srcCam][i], srcBuff[i], winw, winh, Contour, ContourMask, CenX[i], CenY[i]);
		}
		// get eccentricity
//		for (i = 0; i<CAMNUM; i++)
	//		ecc_Coeff[srcCam][i] = Eccentricity(srcBuff[i], winw, winh, CenX[i], CenY[i]);

		// get circularity
	//	for (i = 0; i<CAMNUM; i++)
	//	{
	//		EdgeDetectSil(EdgeBuff, srcBuff[i], winw, winh);
	//		cir_Coeff[srcCam][i] = Circularity(srcBuff[i], winw, winh, EdgeBuff);
	//	}
	}

	// record execute time --- end
	finish = clock();

	return true;
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1, 1, -1, 1, 0.0, 2.0);
	glViewport(0, 0, (GLsizei)winw, (GLsizei)winh);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	if (argc != 2)
	{
		printf_s("Please pass the path of the 3D-PDF file to be analyzed as the first parameter.");
		return -1;
	}
	
	// Read 3D-PDF and determine faces
	String^ pdf3dFileName = gcnew String(argv[1]); Console::Write("3d-PDF FileName: "); Console::WriteLine(pdf3dFileName);
	List<Face^>^ faceList = nullptr;
	int result = ReadFacesFrom3DPdf(pdf3dFileName, faceList);


	// Next steps
	if (result == 0)
	{
		// Translate faces into raw C
		int numver = 0;
		for each (Face^ face in faceList)
		{
			numver += face->VertexCoords->Length / 3;
		}
		// allocate memory of vertex
		pVer vertex = (pVer)malloc(numver * sizeof(Ver));
		memset(vertex, 0, numver * sizeof(Ver));
		// Assign vertices
		int currentVertex = 0;
		for each (Face^ face in faceList)
		{
			for (int i = 0; i < face->VertexCoords->Length; i += 3)
			{
				vertex[currentVertex].coor[0] = (double)face->VertexCoords[i];
				vertex[currentVertex].coor[1] = (double)face->VertexCoords[i + 1];
				vertex[currentVertex].coor[2] = (double)face->VertexCoords[i + 2];

				currentVertex++;
			}
		}

		int numtri = 0;
		for each (Face^ face in faceList)
		{
			numtri += face->VertexIndices->Length / 3;
		}
		// allocate memory of triangle
		pTri triangle = (pTri)malloc(numtri * sizeof(Tri));
		memset(triangle, 0, numtri * sizeof(Tri));
		// Assign triangles
		int currentTriangle = 0;
		int previousVertexIndices = 0;
		for each (Face^ face in faceList)
		{
			for (int i = 0; i < face->VertexIndices->Length; i += 3)
			{
				triangle[currentTriangle].v[0] = (int)face->VertexIndices[i] + previousVertexIndices;
				triangle[currentTriangle].v[1] = (int)face->VertexIndices[i + 1] + previousVertexIndices;
				triangle[currentTriangle].v[2] = (int)face->VertexIndices[i + 2] + previousVertexIndices;
				triangle[currentTriangle].NodeName = 3;
				currentTriangle++;
			}
			previousVertexIndices += face->VertexIndices->Length;
		}

		// Calculate shape descriptors based on image rendered by OpenGL
		double			ecc_Coeff[ANGLE][CAMNUM];
		double			cir_Coeff[ANGLE][CAMNUM];
		double			src_FdCoeff[ANGLE][CAMNUM][FD_COEFF_NO];
		double			src_ArtCoeff[ANGLE][CAMNUM][ART_ANGULAR][ART_RADIAL];

		String^ codeBase = Assembly::GetEntryAssembly()->CodeBase;
		System::UriBuilder^ uri = gcnew System::UriBuilder(codeBase);
		String^ currentPath = System::IO::Path::GetDirectoryName(Uri::UnescapeDataString(uri->Path));
		bool bResult = CalculateShapeDescriptors(marshal_as<std::string>(currentPath), vertex, numver, triangle, numtri, src_FdCoeff, cir_Coeff, ecc_Coeff, src_ArtCoeff);
		
		int q8_FdCoeff[ANGLE][CAMNUM][FD_COEFF_NO];

		for (int i = 0; i<ANGLE; i++)
			for (int j = 0; j<CAMNUM; j++)
			{
				for (int k = 0; k<FD_COEFF_NO; k++)
				{
					int itmp = (int)(256 * 2 * src_FdCoeff[i][j][k]);
					if (itmp>255)
						q8_FdCoeff[i][j][k] = 255;
					else
						q8_FdCoeff[i][j][k] = itmp;
				}
			}

		// Getting q8_ArtCoeff
		int QUANT8 = 256;
		int itmp;
		int q8_ArtCoeff[ANGLE][CAMNUM][ART_COEF];
		//double q4_ArtCoeff[ANGLE][CAMNUM][ART_COEF_2];
		
		for (int i = 0; i<ANGLE; i++)
			for (int j = 0; j<CAMNUM; j++)
			{
				// the order is the same with that defined in MPEG-7, total 35 coefficients
				int k = 0;
				int p = 0;
				for (int r = 1; r<ART_RADIAL; r++, k++)
				{
					itmp = (int)(QUANT8 *  src_ArtCoeff[i][j][p][r]);
					if (itmp>255)
						q8_ArtCoeff[i][j][k] = 255;
					else
						q8_ArtCoeff[i][j][k] = itmp;
				}

				for (int p = 1; p<ART_ANGULAR; p++)
					for (int r = 0; r<ART_RADIAL; r++, k++)
					{
						itmp = (int)(QUANT8 *  src_ArtCoeff[i][j][p][r]);
						if (itmp>255)
							q8_ArtCoeff[i][j][k] = 255;
						else
							q8_ArtCoeff[i][j][k] = itmp;
					}
			}
		//Verbinde mit Server
		Datenbank objDatenbank;
		objDatenbank.connect2Server("141.45.92.215","INDEXIERUNG","s0543830","Sicherheit-123" );
		// Datenbank füllen

		if (pt)
		{
			string StrFd;
			string StrArt;

			StrFd.append("<Fd_Coeff>");
			StrArt.append("<Art_Coeff>");

			for (int i = 0; i < ANGLE; i++)
			{
				StrFd.append("\n\t<");
				StrFd.append(to_string(i));
				StrFd.append(">\n");

				StrArt.append("\n\t<");
				StrArt.append(to_string(i));
				StrArt.append(">\n");
			
				for (int j = 0; j < CAMNUM; j++)
				{
					StrFd.append("\t\t<");
					StrFd.append(to_string(i));
					StrFd.append(to_string(j));
					StrFd.append(">[");
					
					StrArt.append("\t\t<");
					StrArt.append(to_string(i));
					StrArt.append(to_string(j));
					StrArt.append(">[");

					for (int k = 0; k < FD_COEFF_NO; k++)
					{
						//StrFd.append(to_string(src_FdCoeff[i][j][k]));
						StrFd.append(to_string(q8_FdCoeff[i][j][k]));
						if ( k < ( FD_COEFF_NO-1))
						{
							StrFd.append("; ");
						}
					}

					for (int k = 0; k < ART_COEF; k ++)
					{
						StrArt.append(to_string(q8_ArtCoeff[i][j][k]));
						if (k < (ART_COEF - 1))
						{
							StrArt.append("; ");
						}
					}

					StrFd.append("]</");
					StrFd.append(to_string(i));
					StrFd.append(to_string(j));
					StrFd.append(">\n");

					StrArt.append("]</");
					StrArt.append(to_string(i));
					StrArt.append(to_string(j));
					StrArt.append(">\n");

				} //end CANUM

				StrFd.append("\t</");
				StrFd.append(to_string(i));
				StrFd.append(">");

				StrArt.append("\t</");
				StrArt.append(to_string(i));
				StrArt.append(">");
				} // end ANGLE

			StrFd.append("\n</Fd_Coeff>\n");
			StrArt.append("\n</Art_Coeff>");

			pt<< StrFd;
			pt << StrArt;
			pt.close();
		} //end if pt

		// free memory of 3D model
		free(vertex);
		free(triangle);

	}

return result;
}
