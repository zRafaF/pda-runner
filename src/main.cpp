// #define DEBUG

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "pda.h"
#include "solver.h"

std::shared_ptr<Pda> inputPda() {
    std::string input;

    // Pula o primeiro argumento já que os nodos são computados a partir das transições
    std::getline(std::cin, input, ' ');

    std::getline(std::cin, input);
    const int numOfTransitions = std::stoi(input);

    std::vector<Pda::Transition> transitions;
    for (int i = 0; i < numOfTransitions; i++) {
        std::getline(std::cin, input, ' ');
        const int originState = std::stoi(input);
        std::getline(std::cin, input, ' ');
        const char inputChar = input[0];
        std::getline(std::cin, input, ' ');
        const char stackChar = input[0];
        std::getline(std::cin, input, ' ');
        const std::string stackString = input;
        std::getline(std::cin, input);
        const int targetState = std::stoi(input);

        transitions.push_back(
            Pda::Transition(
                originState,
                inputChar,
                stackChar,
                stackString,
                targetState));
    }

    std::getline(std::cin, input);
    const int numOfFinalStates = std::stoi(input);

    std::vector<int> finalStates;

    for (int i = 0; i < numOfFinalStates; i++) {
        if (i == numOfFinalStates - 1) {
            std::getline(std::cin, input);

        } else {
            std::getline(std::cin, input, ' ');
        }
        finalStates.push_back(std::stoi(input));
    }

    return std::make_shared<Pda>(transitions, finalStates);
}

std::vector<std::string> inputWords() {
    std::vector<std::string> words;

    std::string input;

    std::getline(std::cin, input);

    while (input != "*") {
        words.push_back(input);
        std::getline(std::cin, input);
    }

    return words;
}

int main() {
    std::shared_ptr<Pda> pda = inputPda();
    std::vector<std::string> words = inputWords();
    Solver solver(pda);

#ifdef DEBUG
    pda->printPda();
#endif

    for (auto word : words) {
#ifdef DEBUG
        std::cout << "Solving word: " << word << std::endl;
#endif

        auto result = solver.solve(word);

        std::cout << word << ": " << (result.isAccepted ? "sim" : "nao") << std::endl;

        for (auto state : result.computation) {
            std::cout << state << " |-" << std::endl;
        }
    }

    return 0;
}