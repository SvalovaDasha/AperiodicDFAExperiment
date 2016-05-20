#include "stdafx.h"
#include "CppUnitTest.h"

#include "Tools.h"
#include "../AperiodicDFAExperiment/Constants.h"
#include "../AperiodicDFAExperiment/Verifications.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(PartialOrderTest)
    {
    public:

        TEST_METHOD(TwoStateTest)
        {
            int n = 2;
            int a[] = { 0, 1, 1, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::PreservesNontrivialPartialOrder(string_representation));
        }

        TEST_METHOD(TwoStateTest2)
        {
            int n = 2;
            int a[] = { 0, 1, 1, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::PreservesNontrivialPartialOrder(string_representation));
        }

        TEST_METHOD(ThreeStateTest)
        {
            int n = 3;
            int a[] = { 1, 2, 2, 2, 2, 2 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::PreservesNontrivialPartialOrder(string_representation));
        }

        TEST_METHOD(ThreeStateTest2)
        {
            int n = 3;
            int a[] = { 1, 2, 2, 2, 0, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::PreservesNontrivialPartialOrder(string_representation));
        }

        TEST_METHOD(FourStateTest)
        {
            int n = 4;
            int a[] = { 1, 0, 2, 0, 3, 1, 3, 2 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::PreservesNontrivialPartialOrder(string_representation));
        }

        TEST_METHOD(FiveStateTest)
        {
            int n = 5;
            int a[] = { 0, 1, 1, 2, 2, 3, 4, 0, 4, 4 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::PreservesNontrivialPartialOrder(string_representation));
        }

        TEST_METHOD(FiveStateTest2)
        {
            int n = 5;
            int a[] = { 0, 1, 1, 2, 2, 3, 4, 0, 4, 3 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsTrue(Verifications::PreservesNontrivialPartialOrder(string_representation));
        }

        TEST_METHOD(FiveStateTest3)
        {
            int n = 5;
            int a[] = { 0, 1, 1, 2, 2, 3, 4, 0, 2, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * k);
            Assert::IsFalse(Verifications::PreservesNontrivialPartialOrder(string_representation));
        }

    };
}