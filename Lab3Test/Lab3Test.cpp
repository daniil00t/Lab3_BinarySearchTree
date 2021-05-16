#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3Test
{
	TEST_CLASS(Lab3Test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::IsTrue(1 == true);
		}
	};
}
