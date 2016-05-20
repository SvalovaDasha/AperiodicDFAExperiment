#include "stdafx.h"
#include "CppUnitTest.h"

#include "Tools.h"
#include "../AperiodicDFAExperiment/Constants.h"
#include "../AperiodicDFAExperiment/ShortestResetWord.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(RecoverPathLabelTest)
    {
    public:

        TEST_METHOD(TenStates)
        {
            int n = 10;
            int start = 9;
            // 0  1  2  3  4  5  6  7  8  9
            int a_parent[] = { 0, 0, 5, 4, 1, 3, 2, 6, 1, 4 };
            int a_letter[] = { 2, 0, 0, 1, 0, 1, 1, 0, 1, 1 };
            int a_expected[] = { 0, 0, 1 };
            std::vector<int> parent = Tools::VectorFromArray(a_parent, n);
            std::vector<int> letter = Tools::VectorFromArray(a_letter, n);
            std::vector<int> expected = Tools::VectorFromArray(a_expected, 3);
            std::vector<int> actual = SRW::RecoverPathLabel(parent, letter, start);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(ElevenStates)
        {
            int n = 11;
            int start = 8;
            // 0  1  2  3  4  5  6  7  8  9  10
            int a_parent[] = { 0, 2, 7, 4, 4, 1, 3, 6, 10, 5, 9 };
            int a_letter[] = { 1, 0, 0, 1, 2, 1, 1, 0, 1, 1, 0 };
            int a_expected[] = { 1, 1, 0, 0, 0, 1, 1, 0, 1 };
            std::vector<int> parent = Tools::VectorFromArray(a_parent, n);
            std::vector<int> letter = Tools::VectorFromArray(a_letter, n);
            std::vector<int> expected = Tools::VectorFromArray(a_expected, 9);
            std::vector<int> actual = SRW::RecoverPathLabel(parent, letter, start);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }
    };

    TEST_CLASS(GetLabelOfPathToSingletonTest)
    {
    public:

        TEST_METHOD(TwoStateTest)
        {
            int a_exp[] = { 0 };
            std::vector<int> expected = Tools::VectorFromArray(a_exp, 1);
            int g0[] = { 1, 2 };
            std::vector<std::vector<int> > graph(4, Tools::VectorFromArray(g0, 2));
            graph[0].clear();
            std::vector<int> actual = SRW::GetLabelsOfPathToSingleton(graph);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(ThreeStateTest1)
        {
            int a_exp[] = { 0, 1 };
            std::vector<int> expected = Tools::VectorFromArray(a_exp, 2);
            int g1[] = { 2, 1 };
            int g2[] = { 4, 4 };
            int g3[] = { 6, 5 };
            int g4[] = { 2, 4 };
            int g5[] = { 2, 5 };
            int g6[] = { 6, 4 };
            int g7[] = { 6, 5 };
            std::vector<std::vector<int> > graph(8);
            graph[1] = Tools::VectorFromArray(g1, 2);
            graph[2] = Tools::VectorFromArray(g2, 2);
            graph[3] = Tools::VectorFromArray(g3, 2);
            graph[4] = Tools::VectorFromArray(g4, 2);
            graph[5] = Tools::VectorFromArray(g5, 2);
            graph[6] = Tools::VectorFromArray(g6, 2);
            graph[7] = Tools::VectorFromArray(g7, 2);
            std::vector<int> actual = SRW::GetLabelsOfPathToSingleton(graph);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(ThreeStateTest2)
        {
            int a_exp[] = { 0, 1, 1, 0 };
            std::vector<int> expected = Tools::VectorFromArray(a_exp, 4);
            int g1[] = { 2, 4 };
            int g2[] = { 4, 4 };
            int g3[] = { 1, 5 };
            int g4[] = { 2, 2 };
            int g5[] = { 7, 3 };
            int g6[] = { 7, 5 };
            int g7[] = { 6, 6 };
            std::vector<std::vector<int> > graph(8);
            graph[1] = Tools::VectorFromArray(g1, 2);
            graph[2] = Tools::VectorFromArray(g2, 2);
            graph[3] = Tools::VectorFromArray(g3, 2);
            graph[4] = Tools::VectorFromArray(g4, 2);
            graph[5] = Tools::VectorFromArray(g5, 2);
            graph[6] = Tools::VectorFromArray(g6, 2);
            graph[7] = Tools::VectorFromArray(g7, 2);
            std::vector<int> actual = SRW::GetLabelsOfPathToSingleton(graph);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }
    };

    TEST_CLASS(GetSubsetsGraphTest)
    {
    public:

        TEST_METHOD(TwoStateTest)
        {
            std::vector<int> string_representation = Tools::VectorFromString("0 1 1 0");
            std::vector<std::vector<int> > expected = Tools::MatrixFromString("|1 2|2 1|3 3");
            std::vector<std::vector<int> > actual;
            SRW::GetSubsetsGraph(string_representation, actual);
            Assert::AreEqual(expected.size(), actual.size());
            for(size_t i = 0; i < actual.size(); i++)
                Assert::IsTrue(Tools::AreEqual(expected[i], actual[i]));
        }

        TEST_METHOD(TreeStateTest1)
        {
            std::vector<int> string_representation = Tools::VectorFromString("1 0 2 2 1 2");
            std::vector<std::vector<int> > expected = Tools::MatrixFromString("|2 1|4 4|6 5|2 4|2 5|6 4|6 5");
            std::vector<std::vector<int> > actual;
            SRW::GetSubsetsGraph(string_representation, actual);
            Assert::AreEqual(expected.size(), actual.size());
            for(size_t i = 0; i < actual.size(); i++)
                Assert::IsTrue(Tools::AreEqual(expected[i], actual[i]));
        }

        TEST_METHOD(TreeStateTest2)
        {
            std::vector<int> string_representation = Tools::VectorFromString("2 1 0 1 0 1");
            std::vector<std::vector<int> > expected = Tools::MatrixFromString("|4 2|1 2|5 2|1 2|5 2|1 2|5 2");
            std::vector<std::vector<int> > actual;
            SRW::GetSubsetsGraph(string_representation, actual);
            Assert::AreEqual(expected.size(), actual.size());
            for(size_t i = 0; i < actual.size(); i++)
                Assert::IsTrue(Tools::AreEqual(expected[i], actual[i]));
        }

    };

    TEST_CLASS(GetGetShortestResetWordTest)
    {
    public:

        TEST_METHOD(TwoStateTest)
        {
            int a[] = { 0, 1, 0, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, 4);
            int ex[] = { 0 };
            std::vector<int> expected = Tools::VectorFromArray(ex, 1);
            std::vector<int> actual = SRW::GetShortestResetWord(string_representation);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(TreeStateTest1)
        {
            int a[] = { 1, 0, 2, 2, 1, 2 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, 6);
            int ex[] = { 0, 1 };
            std::vector<int> expected = Tools::VectorFromArray(ex, 2);
            std::vector<int> actual = SRW::GetShortestResetWord(string_representation);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(TreeStateTest2)
        {
            int a[] = { 2, 1, 0, 1, 0, 1 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, 6);
            int ex[] = { 1 };
            std::vector<int> expected = Tools::VectorFromArray(ex, 1);
            std::vector<int> actual = SRW::GetShortestResetWord(string_representation);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(FourStateTest1)
        {
            int a[] = { 1, 1, 1, 2, 2, 3, 3, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, 8);
            int ex[] = { 0, 1, 1, 1, 0, 1, 1, 1, 0 };
            std::vector<int> expected = Tools::VectorFromArray(ex, 9);
            std::vector<int> actual = SRW::GetShortestResetWord(string_representation);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(FoutStateTest2)
        {
            int a[] = { 0, 1, 2, 3, 3, 2, 2, 0 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, 8);
            int ex[] = { 0, 1, 1, 0, 1, 0, 1, 1, 0 };
            std::vector<int> expected = Tools::VectorFromArray(ex, 9);
            std::vector<int> actual = SRW::GetShortestResetWord(string_representation);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(KariAutomatonTest)
        {
            int n = 6;
            int a[] = { 1, 0, 2, 1, 0, 3, 4, 2, 5, 4, 3, 2 };
            std::vector<int> string_representation = Tools::VectorFromArray(a, n * 2);
            int ex[] = { 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 };
            std::vector<int> expected = Tools::VectorFromArray(ex, 25);
            std::vector<int> actual = SRW::GetShortestResetWord(string_representation);
            size_t expected_size = (n - 1) * (n - 1);
            Assert::AreEqual(expected_size, actual.size(), L"It's not extreme.");
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(UnsynchronizedTwoState)
        {
            std::vector<int> string_representation = Tools::VectorFromString("1 0 0 1");
            std::vector<int> expected;
            std::vector<int> actual = SRW::GetShortestResetWord(string_representation);
            Assert::AreEqual(expected.size(), actual.size());
        }

        TEST_METHOD(UnsynchronizedTreeState)
        {
            std::vector<int> string_representation = Tools::VectorFromString("1 0 0 2 2 1");
            std::vector<int> expected;
            std::vector<int> actual = SRW::GetShortestResetWord(string_representation);
            Assert::AreEqual(expected.size(), actual.size());
        }

    };

}
