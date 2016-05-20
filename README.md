#AperiodicDFAExperiment

AperiodicDFAExperiment is a project for my master work in UrFU. It is designed for generation automata using string representation, verification several automata properties, such as strong connectivity and aperiodicity, and searching shortest reset word.

It is Visual Studio 2013 solution, which includes 4 projects.
AperiodicDFAExperiment contatins the most important base code.
MPI project contains main file with MPI realization of brute force using code from AperiodicDFSExperiment.
DrawAutomaton draws automaton.
And Tests project contatins tests for AperiodicDFAExperiment code.

For compilation MPI project on Windows you need [Microsoft Compute Cluster Pack SDK](https://www.microsoft.com/en-us/download/details.aspx?id=239).
For using DrawAutomaton you need Graphviz (Please, fix path in draw.cpp:97). 