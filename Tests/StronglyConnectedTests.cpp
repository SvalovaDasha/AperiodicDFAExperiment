#include "stdafx.h"
#include "CppUnitTest.h"

#include "Tools.h"
#include "../AperiodicDFAExperiment/Constants.h"
#include "../AperiodicDFAExperiment/Verifications.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(StronglyConnectedTest)
    {
    public:

        TEST_METHOD(OneStateTest)
        {
            int n = 1;
            int a[] = { 0, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::IsStronglyConnected(string_representation), L"One state is strongly connected");
        }

        TEST_METHOD(TwoStateTest)
        {
            int n = 2;
            int a[] = { 0, 1, 1, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::IsStronglyConnected(string_representation));
        }

        TEST_METHOD(TwoStateTest2)
        {
            int n = 2;
            int a[] = { 0, 1, 1, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::IsStronglyConnected(string_representation));
        }

        TEST_METHOD(TwoStateTest3)
        {
            int n = 2;
            int a[] = { 1, 0, 0, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::IsStronglyConnected(string_representation));
        }

        TEST_METHOD(ThreeStatesTest1)
        {
            int n = 3;
            int a[] = { 1, 0, 1, 2, 2, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::IsStronglyConnected(string_representation));
        }

        TEST_METHOD(ThreeStatesTest2)
        {
            int n = 3;
            int a[] = { 1, 0, 0, 2, 0, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::IsStronglyConnected(string_representation));
        }

        TEST_METHOD(ThreeStatesTest3)
        {
            int n = 3;
            int a[] = { 1, 0, 1, 2, 0, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::IsStronglyConnected(string_representation));
        }

        TEST_METHOD(FourStatesTest1)
        {
            int n = 4;
            int a[] = { 1, 2, 1, 2, 1, 2, 1, 2 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::IsStronglyConnected(string_representation));
        }

        TEST_METHOD(FourStatesTest2)
        {
            int n = 4;
            int a[] = { 1, 2, 2, 3, 3, 0, 1, 3 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::IsStronglyConnected(string_representation));
        }

        TEST_METHOD(SixStatesTest1)
        {
            int n = 6;
            int a[] = { 1, 0, 2, 0, 3, 4, 5, 4, 3, 2, 5, 3 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::IsStronglyConnected(string_representation));
        }

        TEST_METHOD(SixStatesTest2)
        {
            int n = 6;
            int a[] = { 1, 0, 2, 0, 3, 4, 5, 4, 3, 2, 5, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::SymbolProducesNontrivialCycle(string_representation));
        }

    };

    TEST_CLASS(IsAllTrueTest)
    {
    public:

        TEST_METHOD(AllTrue)
        {
            std::vector<bool> a(6, true);
            Assert::IsTrue(Verifications::IsAllTrue(a));
        }

        TEST_METHOD(AllFalse)
        {
            std::vector<bool> a(7, false);
            Assert::IsFalse(Verifications::IsAllTrue(a));
        }

        TEST_METHOD(FalseAndTrue)
        {
            std::vector<bool> a(6, true);
            a[4] = false;
            Assert::IsFalse(Verifications::IsAllTrue(a));
        }

    };

    TEST_CLASS(GetReversedTest)
    {
    public:

        TEST_METHOD(GetReversed)
        {   /*
            0|2
            1|0 3
            2|0 1
            3|1 2 3
            */
            int n = 4;
            int a[] = { 1, 2, 2, 3, 3, 0, 1, 3 };
            int ex0[] = { 2 };
            int ex1[] = { 0, 3 };
            int ex2[] = { 0, 1 };
            int ex3[] = { 1, 2, 3 };
            std::vector<std::vector<int> > expected(n);
            expected[0] = Tools::VectorFromArray(ex0, 1);
            expected[1] = Tools::VectorFromArray(ex1, 2);
            expected[2] = Tools::VectorFromArray(ex2, 2);
            expected[3] = Tools::VectorFromArray(ex3, 3);
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);

            std::vector<std::vector<int> > actual = Verifications::GetReversed(string_representation);
            Assert::AreEqual(expected.size(), actual.size(), L"Different sizes.");
            for(size_t i = 0; i < actual.size(); i++){
                Assert::AreEqual(expected[i].size(), actual[i].size(), L"Different sizes.");
                for(size_t j = 0; j < actual[i].size(); j++)
                    Assert::AreEqual(expected[i][j], actual[i][j], L"Different values.");
            }
        }

        TEST_METHOD(OneStateGetReversed)
        {   
            int n = 1;
            int a[] = { 0, 0 };
            int ex0[] = { 0, 0 };
            std::vector<std::vector<int> > expected(n);
            expected[0] = Tools::VectorFromArray(ex0, 2);
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);

            std::vector<std::vector<int> > actual = Verifications::GetReversed(string_representation);
            Assert::AreEqual(expected.size(), actual.size(), L"Different sizes.");
            Assert::AreEqual(expected[0].size(), actual[0].size(), L"Different sizes.");
            for(size_t j = 0; j < actual[0].size(); j++)
                Assert::AreEqual(expected[0][j], actual[0][j], L"Different values.");
        }
    };
}