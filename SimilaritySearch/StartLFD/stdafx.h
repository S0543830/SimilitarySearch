// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// TODO: reference additional headers your program requires here

#include <msclr\marshal_cppstd.h>

#include <gl/glut.h> 
#include <gl/gl.h>
#include <gl/glu.h>

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <string>

extern "C" {
#include "../3DAlignment/ds.h"
#include "../3DAlignment/RegionShape.h"
#include "../3DAlignment/RWObj.h"
#include "../3DAlignment/Circularity.h"
#include "../3DAlignment/FourierDescriptor.h"
#include "../3DAlignment/Eccentricity.h"
#include "../3DAlignment/Edge.h"
#include "../3DAlignment/TranslateScale.h"
#include "../3DAlignment/Bitmap.h"
}

using namespace msclr::interop;
using namespace System;
using namespace SimilaritySearch::Pdf3DReader;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Text;
using namespace std;
using namespace System::Data;
using namespace System::Data::Common;
using namespace System::Data::SqlClient;

#include "Datenbank.h"