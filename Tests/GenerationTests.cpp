#include "stdafx.h"
#include "CppUnitTest.h"

#include "Tools.h"
#include "../AperiodicDFAExperiment/Constants.h"
#include "../AperiodicDFAExperiment/Generation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(StringRepresentationByFlagGenerationTest)
    {
    public:

        TEST_METHOD(TwoStateTest1)
        {
            std::vector<int> flag(1, 1);
            Generation::StringRepresentationGenerator generator(flag);
            std::vector<int> expected(4, 0);
            expected[1] = 1;
            std::vector<int> actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual));

            expected[3] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual));

            expected[3] = 0;
            expected[2] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual));

            expected[3] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(TwoStateTest2)
        {
            std::vector<int> flag(1, 0);
            Generation::StringRepresentationGenerator generator(flag);
            std::vector<int> expected(4, 0);
            expected[0] = 1;
            std::vector<int> actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"1 step");

            expected[3] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"2 step");

            expected[3] = 0;
            expected[2] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"3 step");

            expected[3] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"4 step");

            expected[3] = 0;
            expected[2] = 0;
            expected[1] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"5 step");

            expected[3] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"6 step");

            expected[3] = 0;
            expected[2] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"7 step");

            expected[3] = 1;
            actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"8 step");

        }

        TEST_METHOD(FourStateTest)
        {
            int n = 4;
            int a[] = { 0, 1, 5 }; // i.e. min string representation is 1 2 0 0 3 0 0
            std::vector<int> flag = Tools::VectorFromArray(a, n-1);
            Generation::StringRepresentationGenerator generator(flag);
            int min[] = {1, 2, 0, 0, 0, 3, 0, 0};
            int after5steps[] = { 1, 2, 0, 0, 0, 3, 1, 1 };
            int after20steps[] = { 1, 2, 0, 0, 1, 3, 1, 0 };
            int max[] = {1, 2, 2, 2, 2, 3, 3, 3};
            std::vector<int> expected = Tools::VectorFromArray(min, n * k);
            std::vector<int> actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"Min is incorrect");

            expected = Tools::VectorFromArray(after5steps, n * k);
            for(int i = 0; i < 5; i++)
                actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"String after 5 steps is incorrect");

            expected = Tools::VectorFromArray(after20steps, n * k);
            for(int i = 0; i < 15; i++)
                actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"String after 20 steps is incorrect");

            expected = Tools::VectorFromArray(max, n * k);
            int counter = 21;
            int expected_counter = 433; // 1 * 1 * 3 * 3 *3 * 1 * 4 * 4 + 1, i.e. two times for max
            while(!generator.Finished()){
                counter++;
                actual = generator.Next();
            }
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"Max is incorrect");
            Assert::AreEqual(expected_counter, counter, L"Number of iterations is incorrect");
        }

        TEST_METHOD(FourStateTest2)
        {
            int n = 4;
            int a[] = { 1, 3, 5 };
            std::vector<int> flag = Tools::VectorFromArray(a, n - 1);
            Generation::StringRepresentationGenerator generator(flag);
            int min[] = { 0, 1, 0, 2, 0, 3, 0, 0 };
            int after10steps[] = { 0, 1, 0, 2, 0, 3, 2, 2 };
            int after55steps[] = { 0, 1, 1, 2, 0, 3, 1, 3 };
            int max[] = { 0, 1, 1, 2, 2, 3, 3, 3 };
            std::vector<int> expected = Tools::VectorFromArray(min, n * k);
            std::vector<int> actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"Min is incorrect");

            expected = Tools::VectorFromArray(after10steps, n * k);
            for(int i = 0; i < 10; i++)
                actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"String after 10 steps is incorrect");

            expected = Tools::VectorFromArray(after55steps, n * k);
            for(int i = 0; i < 45; i++)
                actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"String after 55 steps is incorrect");

            expected = Tools::VectorFromArray(max, n * k);
            int counter = 56;
            int expected_counter = 97; 
            while(!generator.Finished()){
                counter++;
                actual = generator.Next();
            }
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"Max is incorrect");
            Assert::AreEqual(expected_counter, counter, L"Numbers of iteration is incorrect");
        }

        TEST_METHOD(FourStateTest3)
        {
            int n = 4;
            int a[] = { 0, 1, 2 };
            std::vector<int> flag = Tools::VectorFromArray(a, n - 1);
            Generation::StringRepresentationGenerator generator(flag);
            int min[] = { 1, 2, 3, 0, 0, 0, 0, 0 };
            int after100steps[] = { 1, 2, 3, 0, 1, 2, 1, 0 };
            int after600steps[] = { 1, 2, 3, 2, 1, 1, 2, 0 };
            int max[] = { 1, 2, 3, 3, 3, 3, 3, 3 };
            std::vector<int> expected = Tools::VectorFromArray(min, n * k);
            std::vector<int> actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"Min is incorrect");

            expected = Tools::VectorFromArray(after100steps, n * k);
            for(int i = 0; i < 100; i++)
                actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"String after 100 steps is incorrect");

            expected = Tools::VectorFromArray(after600steps, n * k);
            for(int i = 0; i < 500; i++)
                actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"String after 600 steps is incorrect");

            expected = Tools::VectorFromArray(max, n * k);
            int counter = 601;
            int expected_counter = 1025;
            while(!generator.Finished()){
                counter++;
                actual = generator.Next();
            }
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"Max is incorrect");
            Assert::AreEqual(expected_counter, counter, L"Numbers of iteration is incorrect");
        }

        TEST_METHOD(FiveStateTest)
        {
            int n = 5;
            int a[] = { 1, 3, 4, 5 };
            std::vector<int> flag = Tools::VectorFromArray(a, n - 1);
            Generation::StringRepresentationGenerator generator(flag);
            int min[] = { 0, 1, 0, 2, 3, 4, 0, 0, 0, 0 };
            int after500steps[] = { 0, 1, 0, 2, 3, 4, 4, 0, 0, 0 };
            int after1000steps[] = { 0, 1, 1, 2, 3, 4, 3, 0, 0, 0 };
            int max[] = { 0, 1, 1, 2, 3, 4, 4, 4, 4, 4 };
            std::vector<int> expected = Tools::VectorFromArray(min, n * k);
            std::vector<int> actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"Min is incorrect");

            expected = Tools::VectorFromArray(after500steps, n * k);
            for(int i = 0; i < 500; i++)
                actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"String after 500 steps is incorrect");

            expected = Tools::VectorFromArray(after1000steps, n * k);
            for(int i = 0; i < 500; i++)
                actual = generator.Next();
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"String after 1000 steps is incorrect");

            expected = Tools::VectorFromArray(max, n * k);
            int counter = 1001;
            int expected_counter = 1251;
            while(!generator.Finished()){
                counter++;
                actual = generator.Next();
            }
            Assert::IsTrue(Tools::AreEqual(expected, actual), L"Max is incorrect");
            Assert::AreEqual(expected_counter, counter, L"Numbers of iteration is incorrect");
        }

    };

    TEST_CLASS(FlagGenerationTest)
    {
    public:
        TEST_METHOD(TwoStateTest){
            std::vector<std::vector<int> > all = Generation::GenerateAllFlags(2);
            size_t expected_number = 2;
            int ex0[] = { 0 };
            int ex1[] = { 1 };
            std::vector<int> expected0 = Tools::VectorFromArray(ex0, 1);
            std::vector<int> expected1 = Tools::VectorFromArray(ex1, 1);
            Assert::AreEqual(expected_number, all.size());
            Assert::IsTrue(Tools::AreEqual(expected0, all[0]));
            Assert::IsTrue(Tools::AreEqual(expected1, all[1]));
        }

        TEST_METHOD(FiveStateTest){
            std::vector<std::vector<int> > all = Generation::GenerateAllFlags(5);
            size_t expected_number = 42;
            Assert::AreEqual(expected_number, all.size()); // right quantity
            for(size_t i = 0; i < all.size(); i++){
                Assert::IsTrue(Tools::IsCorrect(all[i])); // each is correct
                for(size_t j = i + 1; j < all.size(); j++)
                    Assert::IsFalse(Tools::AreEqual(all[i], all[j])); // and unique
            }
        }
    };
}