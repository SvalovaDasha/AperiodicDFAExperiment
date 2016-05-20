#include "stdafx.h"
#include "CppUnitTest.h"

#include "Tools.h"
#include "../AperiodicDFAExperiment/Constants.h"
#include "../AperiodicDFAExperiment/Verifications.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(IsAperiodicTest)
    {
    public:
        TEST_METHOD(TwoState1){
            std::vector<int> string_representation = Tools::VectorFromString("1 0 0 1");
            Assert::IsFalse(Verifications::IsAperiodic(string_representation));
        }

        TEST_METHOD(TwoState2){
            std::vector<int> string_representation = Tools::VectorFromString("1 1 0 0");
            Assert::IsFalse(Verifications::IsAperiodic(string_representation));
        }

        TEST_METHOD(TwoState3){
            std::vector<int> string_representation = Tools::VectorFromString("0 1 0 1");
            Assert::IsTrue(Verifications::IsAperiodic(string_representation));
        }

        TEST_METHOD(ThreeState1){
            std::vector<int> string_representation = Tools::VectorFromString("0 1 0 2 1 0");
            Assert::IsFalse(Verifications::IsAperiodic(string_representation));
        }

        TEST_METHOD(ThreeState2){
            std::vector<int> string_representation = Tools::VectorFromString("0 1 1 2 2 2");
            Assert::IsTrue(Verifications::IsAperiodic(string_representation));
        }

        TEST_METHOD(FourStateTest1){
            std::vector<int> string_representation = Tools::VectorFromString("1 0 2 0 3 1 3 2");
            Assert::IsTrue(Verifications::IsAperiodic(string_representation));
        }

        TEST_METHOD(FourStateTest2){
            std::vector<int> string_representation = Tools::VectorFromString("0 1 2 3 2 1 0 3");
            Assert::IsTrue(Verifications::IsAperiodic(string_representation)); 
        }

        TEST_METHOD(FourStateTest3){
            std::vector<int> string_representation = Tools::VectorFromString("1 1 1 2 2 3 3 0");
            Assert::IsFalse(Verifications::IsAperiodic(string_representation));
        }

    };
}