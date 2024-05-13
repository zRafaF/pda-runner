#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "pda.h"
#include "solver.h"

// Função que lê a entrada do PDA
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

// Função que lê as palavras a serem testadas, terminando com um *
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

    // Para cada palavra
    for (auto word : words) {
        // Resolve o PDA
        auto result = solver.solve(word);

        // Imprime o resultado
        std::cout << word << ": " << (result.isAccepted ? "sim" : "nao") << std::endl;
        while (!result.computation.empty()) {
            std::cout << result.computation.top() << (result.computation.size() == 1 ? "." : " |-") << std::endl;
            result.computation.pop();
        }
        std::cout << std::endl;
    }

    return 0;
}