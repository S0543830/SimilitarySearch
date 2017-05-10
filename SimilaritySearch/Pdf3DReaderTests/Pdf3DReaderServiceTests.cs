using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using NUnit.Framework;
using SimilaritySearch.Pdf3DReader;

namespace SimilaritySearch.Pdf3DReaderTests
{
    [TestFixture]
    public class Pdf3DReaderServiceTests
    {
        [Test]
        public void TestInitialization()
        {
            using (var reader = new Pdf3DReader.Pdf3DReaderService())
            {
                // First initialization
                Assert.IsTrue(reader.Init());

                // ...and second one
                Assert.IsTrue(reader.Init());
            }
        }


        [Test]
        public void TestReadPdf3DWasher()
        {
            var fileName = @"..\..\..\..\Data\MP1914.pdf" ;//@"..\..\..\..\Data\simple_cube.prc";
            var codeBase = Assembly.GetExecutingAssembly().CodeBase;
            var uri = new UriBuilder(codeBase);
            var path = Uri.UnescapeDataString(uri.Path);
            fileName = Path.Combine(Path.GetDirectoryName(path), fileName);
            Assert.IsTrue(File.Exists(fileName), $"3D-PDF file {fileName} does not exist.");
            using (var reader = new Pdf3DReaderService())
            {
                List<Face> faceList = null;
                Assert.AreEqual(0, reader.ReadPdf3D(fileName, out faceList));
                reader.ReadPdf3D(fileName, out faceList);
                // The washer contains 4 faces
                Assert.AreEqual(4, faceList.Count);
            }
        }

        [Test]
        public void TestReadPdf3DCube()
        {
            var fileName = @"..\..\..\..\Data\186455.pdf";//@"..\..\..\..\Data\simple_cube.prc";
            var codeBase = Assembly.GetExecutingAssembly().CodeBase;
            var uri = new UriBuilder(codeBase);
            var path = Uri.UnescapeDataString(uri.Path);
            fileName = Path.Combine(Path.GetDirectoryName(path), fileName);
            Assert.IsTrue(File.Exists(fileName), $"3D-PDF file {fileName} does not exist.");
            using (var reader = new Pdf3DReaderService())
            {
                List<Face> faceList = null;
                Assert.AreEqual(0, reader.ReadPdf3D(fileName, out faceList));
                // The cube contains 6 faces
                Assert.AreEqual(6, faceList.Count);
                foreach (var face in faceList)
                {
                    Assert.AreEqual(6, face.Normals.Length);
                    Assert.AreEqual(18, face.VertexCoords.Length);
                    Assert.AreEqual(6, face.VertexIndices.Length);
                }
            }
        }

        [Test]
        public void TestReadPdf3DScrew()
        {
            var fileName = @"..\..\..\..\Data\BP0370.pdf";
            var codeBase = Assembly.GetExecutingAssembly().CodeBase;
            var uri = new UriBuilder(codeBase);
            var path = Uri.UnescapeDataString(uri.Path);
            fileName = Path.Combine(Path.GetDirectoryName(path), fileName);
            Assert.IsTrue(File.Exists(fileName), $"3D-PDF file {fileName} does not exist.");
            using (var reader = new Pdf3DReaderService())
            {
                List<Face> faceList = null;
                Assert.AreEqual(0, reader.ReadPdf3D(fileName, out faceList));

                // The screw contains 24 faces
                Assert.AreEqual(24, faceList.Count);
            }
        }

        [Test]
        public void TestReadPdf3DTheReplicator()
        {
            var fileName = @"..\..\..\..\Data\MP2378.pdf";
            var codeBase = Assembly.GetExecutingAssembly().CodeBase;
            var uri = new UriBuilder(codeBase);
            var path = Uri.UnescapeDataString(uri.Path);
            fileName = Path.Combine(Path.GetDirectoryName(path), fileName);
            Assert.IsTrue(File.Exists(fileName), $"3D-PDF file {fileName} does not exist.");
            using (var reader = new Pdf3DReaderService())
            {
                List<Face> faceList = null;
                Assert.AreEqual(0, reader.ReadPdf3D(fileName, out faceList));

                // The replicator contains 252 faces
                Assert.AreEqual(252, faceList.Count);
            }
        }
    }
}
