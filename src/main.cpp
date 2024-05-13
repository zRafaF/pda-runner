#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "pda.h"
#include "solvingTree.h"

Pda inputPda() {
    std::vector<Pda::Transition> transitions;

    std::string input;

    std::getline(std::cin, input, ' ');
    std::stoi(input);

    std::getline(std::cin, input);
    const int numOfTransitions = std::stoi(input);

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

    return Pda(transitions, finalStates);
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
    Pda pda = inputPda();
    std::vector<std::string> words = inputWords();

    for (auto word : words) {
        std::shared_ptr<SolvingTree> tree(new SolvingTree(std::make_shared<Pda>(pda), word));
    }

    return 0;
}