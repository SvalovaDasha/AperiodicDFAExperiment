#include "stdafx.h"
#include "CppUnitTest.h"

#include "Tools.h"
#include "../AperiodicDFAExperiment/Constants.h"
#include "../AperiodicDFAExperiment/Verifications.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		
	TEST_CLASS(OneSymbolCycleDetectionTest)
	{
	public:

		TEST_METHOD(OneStateTest)
		{
            int n = 1;
            int a[] = {0, 0};
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::SymbolProducesNontrivialCycle(string_representation), L"Loop is not a cyrcle");
		}

        TEST_METHOD(TwoStatesTest1)
        {
            int n = 2;
            int a[] = { 0, 1, 1, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::SymbolProducesNontrivialCycle(string_representation), L"Loop is not a cyrcle.");
        }

        TEST_METHOD(TwoStatesTest2)
        {
            int n = 2;
            int a[] = { 1, 0, 1, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::SymbolProducesNontrivialCycle(string_representation), L"Loop is not a cyrcle.");
        }

        TEST_METHOD(TwoStatesTest3)
        {
            int n = 2;
            int a[] = { 1, 0, 1, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::SymbolProducesNontrivialCycle(string_representation), L"It must be one symbol cycle.");
        }

        TEST_METHOD(TwoStatesTest4)
        {
            int n = 2;
            int a[] = { 1, 0, 0, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::SymbolProducesNontrivialCycle(string_representation), L"It must be a-cycle.");
        }

        TEST_METHOD(TwoStatesTest5)
        {
            int n = 2;
            int a[] = { 0, 1, 1, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::SymbolProducesNontrivialCycle(string_representation), L"It must be b-cycle.");
        }

        TEST_METHOD(TwoStatesTest6)
        {
            int n = 2;
            int a[] = { 1, 1, 1, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::SymbolProducesNontrivialCycle(string_representation), L"Loop is not a cyrcle.");
        }

        TEST_METHOD(TwoStatesTest7)
        {
            int n = 2;
            int a[] = { 1, 1, 0, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::SymbolProducesNontrivialCycle(string_representation), L"It must be a,b-cycles.");
        }

        TEST_METHOD(ThreeStatesTest1)
        {
            int n = 3;
            int a[] = { 1, 0, 2, 0, 0, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::SymbolProducesNontrivialCycle(string_representation), L"It must be a-cycle.");
        }

        TEST_METHOD(ThreeStatesTest2)
        {
            int n = 3;
            int a[] = { 1, 0, 0, 2, 0, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::SymbolProducesNontrivialCycle(string_representation), L"It must be a-cycle.");
        }

        TEST_METHOD(ThreeStatesTest3)
        {
            int n = 3;
            int a[] = { 1, 0, 1, 2, 0, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::SymbolProducesNontrivialCycle(string_representation));
        }

        TEST_METHOD(FourStatesTest1)
        {
            int n = 4;
            int a[] = { 1, 2, 1, 2, 1, 2, 1, 2 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::SymbolProducesNontrivialCycle(string_representation));
        }

        TEST_METHOD(FourStatesTest2)
        {
            int n = 4;
            int a[] = { 1, 2, 2, 3, 3, 0, 1, 3 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::SymbolProducesNontrivialCycle(string_representation));
        }

	};

    TEST_CLASS(IndexTest)
    {
    public:

        TEST_METHOD(IndexTest1)
        {
            int expected = 0;
            int state = 0;
            int a = 0;
            int actual = index(state, a);
            Assert::AreEqual(expected, actual);
        }

        TEST_METHOD(IndexTest2)
        {
            int expected = 1;
            int state = 0;
            int a = 1;
            int actual = index(state, a);
            Assert::AreEqual(expected, actual);
        }

        TEST_METHOD(IndexTest3)
        {
            int expected = 7;
            int state = 3;
            int a = 1;
            int actual = index(state, a);
            Assert::AreEqual(expected, actual);
        }

        TEST_METHOD(IndexTest4)
        {
            int expected = 6;
            int state = 3;
            int a = 0;
            int actual = index(state, a);
            Assert::AreEqual(expected, actual);
        }

    };

    TEST_CLASS(GetFirstUntaggedStateTest)
    {
    public:

        TEST_METHOD(AllUntaggedTest1)
        {
            int expected = 0;
            int a[5] = { -1, -1, -1, -1, -1};
            int n = 5;
            std::vector<int> tags = Tools::VectorFromArray(a, n);
            int actual = Verifications::GetFirstUntaggedState(tags);
            Assert::AreEqual(expected, actual);
        }

        TEST_METHOD(AllUntaggedTest2)
        {
            int expected = 0;
            int a[5] = { -1, 2, 2, 2, -1 };
            int n = 5;
            std::vector<int> tags = Tools::VectorFromArray(a, n);
            int actual = Verifications::GetFirstUntaggedState(tags);
            Assert::AreEqual(expected, actual);
        }

        TEST_METHOD(AllUntaggedTest3)
        {
            int expected = 2;
            int a[3] = { 1, 2, -1};
            int n = 3;
            std::vector<int> tags = Tools::VectorFromArray(a, n);
            int actual = Verifications::GetFirstUntaggedState(tags);
            Assert::AreEqual(expected, actual);
        }

        TEST_METHOD(AllUntaggedTest4)
        {
            int expected = 8;
            int a[10] = { 0, 0, 0, 5, 6, 5, 7, 8, -1, -1 };
            int n = 10;
            std::vector<int> tags = Tools::VectorFromArray(a, n);
            int actual = Verifications::GetFirstUntaggedState(tags);
            Assert::AreEqual(expected, actual);
        }

        TEST_METHOD(AllUntaggedTest5)
        {
            int expected = -1;
            int a[10] = { 0, 0, 7, 3, 2, 0 };
            int n = 6;
            std::vector<int> tags = Tools::VectorFromArray(a, n);
            int actual = Verifications::GetFirstUntaggedState(tags);
            Assert::AreEqual(expected, actual);
        }

    };
}