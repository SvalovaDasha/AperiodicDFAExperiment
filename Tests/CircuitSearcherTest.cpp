#include "stdafx.h"
#include "CppUnitTest.h"

#include "Tools.h"
#include "../AperiodicDFAExperiment/Constants.h"
#include "../AperiodicDFAExperiment/Verifications.h"
#include "../AperiodicDFAExperiment/CircuitsSearcher.h"
#include "../AperiodicDFAExperiment/ShortestResetWord.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{

    TEST_CLASS(IsIdentityTest)
    {
    public:
        TEST_METHOD(FourStateTest){
            std::vector<int> string_representation = Tools::VectorFromString("1 0 2 0 3 1 3 2");
            std::vector<std::vector<int> > words = Tools::MatrixFromString("0 1|1 0|0|0 0 0 0 1 1");
            std::vector<int> states = Tools::VectorFromString("0 2 0 1");
            std::vector<bool> expected = Tools::BoolVectorFromString("1 1 0 1");
            IdentityChecker checker(string_representation, std::vector<std::vector<int> >());
            for(size_t i = 0; i < expected.size(); i++){
                if(expected[i])
                    Assert::IsTrue(checker.IsIdentity(words[i], states[i]));
                else
                    Assert::IsFalse(checker.IsIdentity(words[i], states[i]));
            }
        }
    };

    TEST_CLASS(GetStatesInSubsetTest)
    {
    public:
        TEST_METHOD(ThreeStatesSubset){
            int subset = 14;
            std::vector<int> expected = Tools::VectorFromString("1 2 3");
            std::vector<int> str_repr;
            IdentityChecker checker(str_repr, std::vector<std::vector<int> >());
            std::vector<int> actual = checker.GetStatesInSubset(subset, 16);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }

        TEST_METHOD(FiveStatesSubset){
            int subset = 1 + 4 + 8 + 64 + 256;
            std::vector<int> expected = Tools::VectorFromString("0 2 3 6 8");
            std::vector<int> str_repr;
            IdentityChecker checker(str_repr, std::vector<std::vector<int> >());
            std::vector<int> actual = checker.GetStatesInSubset(subset, 9);
            Assert::IsTrue(Tools::AreEqual(expected, actual));
        }
    };

    TEST_CLASS(SubGraphComponentsTest){
        TEST_METHOD(TwoStates1){
            std::string str("1|0");
            auto graph = Tools::MatrixFromString(str);
            std::vector<int> components(graph.size());
            ComponentsSearcher searcher(graph);
            searcher.FindSubGraphComponents(components, 0);
            for(size_t i = 0; i < components.size(); i++)
                Assert::AreEqual(0, components[i]);
        }

        TEST_METHOD(TwoStates2){
            std::string str("1|1");
            auto graph = Tools::MatrixFromString(str);
            ComponentsSearcher searcher(graph);
            std::vector<int> components(graph.size());
            searcher.FindSubGraphComponents(components, 0);
            for(size_t i = 0; i < components.size(); i++)
                Assert::AreEqual(int(i), components[i]);
        }

        TEST_METHOD(FiveStates){
            std::string str("1|3|1|2|2 3");
            auto graph = Tools::MatrixFromString(str);
            ComponentsSearcher searcher(graph);
            std::vector<int> components(graph.size());
            searcher.FindSubGraphComponents(components, 0);
            std::vector<int> expected = Tools::VectorFromString("1 2 2 2 0");
            for(size_t i = 0; i < components.size(); i++)
                Assert::AreEqual(expected[i], components[i]);
        }

        TEST_METHOD(FiveStatesWithBorder){
            std::string str("1|3|1|2|2 3");
            auto graph = Tools::MatrixFromString(str);
            ComponentsSearcher searcher(graph);
            std::vector<int> components(graph.size());
            searcher.FindSubGraphComponents(components, 2);
            std::vector<int> expected = Tools::VectorFromString("-1 -1 2 1 0");
            for(size_t i = 0; i < components.size(); i++)
                Assert::AreEqual(expected[i], components[i]);
        }

        TEST_METHOD(SixStates){
            std::string str("1 2|3 2|1 5|4|3 5|4");
            auto graph = Tools::MatrixFromString(str);
            ComponentsSearcher searcher(graph);
            std::vector<int> components(graph.size());
            searcher.FindSubGraphComponents(components, 0);
            std::vector<int> expected = Tools::VectorFromString("0 1 1 2 2 2");
            for(size_t i = 0; i < components.size(); i++)
                Assert::AreEqual(expected[i], components[i]);
        }

        TEST_METHOD(SixStatesWithBorder){
            std::string str("1 2|3 2|1 5|4|3 5|4");
            auto graph = Tools::MatrixFromString(str);
            ComponentsSearcher searcher(graph);
            std::vector<int> components(graph.size());
            searcher.FindSubGraphComponents(components, 2);
            std::vector<int> expected = Tools::VectorFromString("-1 -1 0 1 1 1");
            for(size_t i = 0; i < components.size(); i++)
                Assert::AreEqual(expected[i], components[i]);
        }

        TEST_METHOD(EightStates){
            std::string str("1|2 3 4|5 6|5|0 3|3|2 7|5 6");
            auto graph = Tools::MatrixFromString(str);
            ComponentsSearcher searcher(graph);
            std::vector<int> components(graph.size());
            searcher.FindSubGraphComponents(components, 0);
            std::vector<int> expected = Tools::VectorFromString("0 0 1 2 0 2 1 1");
            for(size_t i = 0; i < components.size(); i++)
                Assert::AreEqual(expected[i], components[i]);
        }

        TEST_METHOD(EightStatesWithBorder){
            std::string str("1|2 3 4|5 6|5|0 3|3|2 7|5 6");
            auto graph = Tools::MatrixFromString(str);
            ComponentsSearcher searcher(graph);
            std::vector<int> components(graph.size());
            searcher.FindSubGraphComponents(components, 1);
            std::vector<int> expected = Tools::VectorFromString("-1 0 2 3 1 3 2 2");
            for(size_t i = 0; i < components.size(); i++)
                Assert::AreEqual(expected[i], components[i]);
        }

    };

    TEST_CLASS(CircuitSearcherTest){
        TEST_METHOD(TwoStates1){
            int n = 2;
            std::string str("1|1");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected;
            expected.push_back(Tools::MatrixFromString(""));
            expected.push_back(Tools::MatrixFromString("1 1"));
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }
        
        TEST_METHOD(TwoStates2){
            int n = 2;
            std::string str("1|0");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected;
            expected.push_back(Tools::MatrixFromString("0 1 0"));
            expected.push_back(Tools::MatrixFromString(""));
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }
        
        TEST_METHOD(ThreeStates1){
            int n = 3;
            std::string str("1|0 2|2");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected;
            expected.push_back(Tools::MatrixFromString("0 1 0"));
            expected.push_back(Tools::MatrixFromString(""));
            expected.push_back(Tools::MatrixFromString("2 2"));
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }
        
        TEST_METHOD(ThreeStates2){
            int n = 3;
            std::string str("1|0 2|1");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected;
            expected.push_back(Tools::MatrixFromString("0 1 0"));
            expected.push_back(Tools::MatrixFromString("1 2 1"));
            expected.push_back(Tools::MatrixFromString(""));
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }
        
        TEST_METHOD(ThreeStates3){
            int n = 3;
            std::string str("1|0 2|0 1");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected;
            expected.push_back(Tools::MatrixFromString("0 1 0|0 1 2 0"));
            expected.push_back(Tools::MatrixFromString("1 2 1"));
            expected.push_back(Tools::MatrixFromString(""));
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }

        TEST_METHOD(ThreeStates4){
            int n = 3;
            std::string str("1|2|0 1");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected;
            expected.push_back(Tools::MatrixFromString("0 1 2 0"));
            expected.push_back(Tools::MatrixFromString("1 2 1"));
            expected.push_back(Tools::MatrixFromString(""));
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }
        
        TEST_METHOD(FoutStates1){
            int n = 4;
            std::string str("1|3|0|2 0");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[0] = Tools::MatrixFromString("0 1 3 2 0|0 1 3 0");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }

        TEST_METHOD(FoutStates2){
            int n = 4;
            std::string str("1|2|3|2 1 0");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[0] = Tools::MatrixFromString("0 1 2 3 0");
            expected[1] = Tools::MatrixFromString("1 2 3 1");
            expected[2] = Tools::MatrixFromString("2 3 2");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }
        
        TEST_METHOD(FoutStates3){
            int n = 4;
            std::string str("1 2 3|2|3|0 1 2");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[0] = Tools::MatrixFromString("0 1 2 3 0|0 2 3 0|0 3 0");
            expected[1] = Tools::MatrixFromString("1 2 3 1");
            expected[2] = Tools::MatrixFromString("2 3 2");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }

        TEST_METHOD(FoutStates4){
            int n = 4;
            std::string str("1 3|0 2|1 3|2 0");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[0] = Tools::MatrixFromString("0 1 0|0 1 2 3 0|0 3 2 1 0|0 3 0");
            expected[1] = Tools::MatrixFromString("1 2 1");
            expected[2] = Tools::MatrixFromString("2 3 2");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }
        
        TEST_METHOD(FiveStates){
            int n = 5;
            std::string str("1|3|1|2|2 3");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[1] = Tools::MatrixFromString("1 3 2 1");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
                Assert::AreEqual(s > 1, searcher.ThereAreNoCircuitsLast());
            }
        }

        TEST_METHOD(FiveStates2){
            int n = 5;
            std::string str("4|0 3|1|2|2 3");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[0] = Tools::MatrixFromString("0 4 2 1 0|0 4 3 2 1 0");
            expected[1] = Tools::MatrixFromString("1 3 2 1");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }

        TEST_METHOD(FiveStates3){
            int n = 5;
            std::string str("1|2 3 4|3|4 0|0 1");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[0] = Tools::MatrixFromString("0 1 2 3 4 0|0 1 2 3 0|0 1 3 4 0|0 1 3 0|0 1 4 0");
            expected[1] = Tools::MatrixFromString("1 2 3 4 1|1 3 4 1|1 4 1");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
            }
        }
        
        TEST_METHOD(SixStates){
            int n = 6;
            std::string str("1 2|2 3|1 5|5|3 5|4");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[1] = Tools::MatrixFromString("1 2 1");
            expected[3] = Tools::MatrixFromString("3 5 4 3");
            expected[4] = Tools::MatrixFromString("4 5 4");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
                Assert::AreEqual(s > 4, searcher.ThereAreNoCircuitsLast());
            }
        }

        TEST_METHOD(SixStatesWithUnexistingTransitions){
            int n = 6;
            std::string str("1 2|3 2|1 5|6 4|3 5|4 6");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[1] = Tools::MatrixFromString("1 2 1");
            expected[3] = Tools::MatrixFromString("3 4 3");
            expected[4] = Tools::MatrixFromString("4 5 4");
            for(int s = 0; s < n; s++){
                auto stable_set = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), stable_set.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], stable_set[i]));
                }
            }
        }

        TEST_METHOD(EightStates){
            int n = 8;
            std::string str("1|2 3 4|5 6|5|0 3|3|2 7|5 6");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[0] = Tools::MatrixFromString("0 1 4 0");
            expected[2] = Tools::MatrixFromString("2 6 2");
            expected[3] = Tools::MatrixFromString("3 5 3");
            expected[6] = Tools::MatrixFromString("6 7 6");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
                Assert::AreEqual(s > 6, searcher.ThereAreNoCircuitsLast());
            }
        }
        
        TEST_METHOD(TenStates){
            int n = 10;
            std::string str("1 2|2|3 5|4|3 1 5|2 6|7 8 9|8|9 0|0 6|");
            auto graph = Tools::MatrixFromString(str);
            CircuitsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[0] = Tools::MatrixFromString("0 1 2 3 4 5 6 7 8 9 0|0 1 2 3 4 5 6 7 8 0|0 1 2 3 4 5 6 8 9 0|0 1 2 3 4 5 6 8 0|"
                                                  "0 1 2 3 4 5 6 9 0|0 1 2 5 6 7 8 9 0|0 1 2 5 6 7 8 0|0 1 2 5 6 8 9 0|0 1 2 5 6 8 0|"
                                                  "0 1 2 5 6 9 0|0 2 3 4 5 6 7 8 9 0|0 2 3 4 5 6 7 8 0|0 2 3 4 5 6 8 9 0|0 2 3 4 5 6 8 0|"
                                                  "0 2 3 4 5 6 9 0|0 2 5 6 7 8 9 0|0 2 5 6 7 8 0|0 2 5 6 8 9 0|0 2 5 6 8 0|0 2 5 6 9 0|");
            expected[1] = Tools::MatrixFromString("1 2 3 4 1");
            expected[2] = Tools::MatrixFromString("2 3 4 5 2|2 5 2");
            expected[3] = Tools::MatrixFromString("3 4 3");
            expected[6] = Tools::MatrixFromString("6 7 8 9 6|6 8 9 6|6 9 6");
            for(int s = 0; s < n; s++){
                auto circuits = searcher.GetCircuitStartedAt(s);
                Assert::AreEqual(expected[s].size(), circuits.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], circuits[i]));
                }
                Assert::AreEqual(s > 6, searcher.ThereAreNoCircuitsLast());
            }
        }
        
    };
    /*
    TEST_CLASS(StableWordsSearcherTest)
    {
    public:
        TEST_METHOD(TwoStates1){
            int n = 2;
            std::string str("0 1|1 0");
            auto graph = Tools::MatrixFromString(str);
            StableWordsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected;
            expected.push_back(Tools::MatrixFromString("0|1 1"));
            expected.push_back(Tools::MatrixFromString("0"));
            for(int s = 0; s < n; s++){
                auto stable_set = searcher.GetStableSetOf(s);
                Assert::AreEqual(expected[s].size(), stable_set.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], stable_set[i]));
                }
            }
        }

        TEST_METHOD(TwoStates2){
            int n = 2;
            std::string str("1 1|0 0");
            auto graph = Tools::MatrixFromString(str);
            StableWordsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[0] = Tools::MatrixFromString("0 0|1 0|0 1|1 1");
            for(int s = 0; s < n; s++){
                auto stable_set = searcher.GetStableSetOf(s);
                Assert::AreEqual(expected[s].size(), stable_set.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], stable_set[i]));
                }
            }
        }

        TEST_METHOD(SixStates1){
            int n = 6;
            std::string str("1 2|3 2|1 5|6 4|3 5|4 6");
            auto graph = Tools::MatrixFromString(str);
            StableWordsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(n, Tools::MatrixFromString(""));
            expected[1] = Tools::MatrixFromString("1 0");
            expected[3] = Tools::MatrixFromString("1 0");
            expected[4] = Tools::MatrixFromString("1 0");
            for(int s = 0; s < n; s++){
                auto stable_set = searcher.GetStableSetOf(s);
                Assert::AreEqual(expected[s].size(), stable_set.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], stable_set[i]));
                }
            }
        }

        TEST_METHOD(SubSetsOfFourStates){
            std::vector<std::vector<int> > graph;
            std::vector<int> string_representation = Tools::VectorFromString("1 0 2 0 3 1 3 2");
            SRW::GetSubsetsGraph(string_representation, graph);
            Verifications::RemoveSingletonStates(graph);
            StableWordsSearcher searcher(graph);
            std::vector<std::vector<std::vector<int> > > expected(graph.size(), Tools::MatrixFromString(""));
            expected[3] = Tools::MatrixFromString("0 1"); // {0, 1}
            expected[5] = Tools::MatrixFromString("0 1"); // {0, 2}
            expected[6] = Tools::MatrixFromString("0 1"); // {1, 2}
            expected[7] = Tools::MatrixFromString("0 1"); // {0, 1, 2}
            for(int s = 0; s < int(expected.size()); s++){
                auto stable_set = searcher.GetStableSetOf(s);
                Assert::AreEqual(expected[s].size(), stable_set.size());
                for(size_t i = 0; i < expected[s].size(); i++){
                    Assert::IsTrue(Tools::AreEqual(expected[s][i], stable_set[i]));
                }
            }
        }
    };*/
}