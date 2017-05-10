#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;


namespace SimilaritySearch
{
	namespace Pdf3DReader {

		/// <summary>
		/// The equivalent of an A3DTessFaceData but also comprising normals, vertex coordinates and indexes.
		/// The current implementation is limited to triangle based tesselations.
		/// </summary>
		public ref class Face
		{
		public:
			Face(array<double>^ vertexCoords, array<double>^ normals, array<int>^ vertexIndices)
			{
				VertexCoords = vertexCoords;
				Normals = normals;
				VertexIndices = vertexIndices;
			}

			/// <summary>
			/// Get/set the 0-based vertex coordinates. It contains 3 double values for each point.
			/// </summary>
			property array<double>^ VertexCoords;

			/// <summary>
			/// Get/set the 0-based normals. It contains 3 double values for each normal vector.
			/// </summary>
			property array<double>^ Normals;

			/// <summary>
			/// Get/set the vertex index per triangle. It contains 3 index values for each triangle.
			/// </summary>
			property array<int>^ VertexIndices;
		};
	}
}
