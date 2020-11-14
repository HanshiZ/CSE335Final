#include "pch.h"
#include "CppUnitTest.h"
#include "TriangleMesh.h"
#include "Vertex.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Gdiplus;


namespace Testing
{


	TEST_CLASS(TriangleMeshTest)
	{
	public:

		TEST_METHOD(CreateEmpty)
		{
			auto mesh = make_shared<CTriangleMesh>();
			Assert::AreEqual(0, mesh->GetNumTriangles());
		}


	};
}
