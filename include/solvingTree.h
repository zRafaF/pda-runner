#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "pda.h"

#define MAX_DEPTH 100

class SolvingTree {
   public:
    /**
     * @brief Estrutura que representa o estado atual do PDA (Computação)
     */
    struct State {
        std::string currentWord;
        size_t currentNodeIdx;
        std::stack<char> stack;

        State() : currentWord(""), currentNodeIdx(0), stack(std::stack<char>()) {}
        State(std::string _currentWord, size_t _currentNodeIdx, std::stack<char> _stack) : currentWord(_currentWord), currentNodeIdx(_currentNodeIdx), stack(_stack) {}
    };

    struct ComputationResult {
        bool isAccepted;
        std::vector<SolvingTree::State> computation;

        ComputationResult(bool _isAccepted, std::vector<SolvingTree::State> _computation) : isAccepted(_isAccepted), computation(_computation) {}
    };

    struct TransitionComputingResult {
        bool isAccepted;
        SolvingTree::State state;

        TransitionComputingResult(bool _isAccepted, SolvingTree::State _state) : isAccepted(_isAccepted), state(_state) {}
    };

    /**
     * @brief Constructor de um objeto SolvingTree raiz
     */
    SolvingTree(std::shared_ptr<Pda> _pda, std::string _input);

    /**
     * @brief Constructor de um objeto SolvingTree filho
     */
    SolvingTree(SolvingTree::State _state, std::shared_ptr<SolvingTree> _parent);

    SolvingTree::ComputationResult compute(std::shared_ptr<SolvingTree> _myPointer);

   private:
    void insertChild(std::shared_ptr<SolvingTree> child);

    SolvingTree::TransitionComputingResult computeTransition(Pda::Transition transition);

    SolvingTree::State state;
    std::shared_ptr<Pda> pda;

    std::shared_ptr<SolvingTree> parentNode;
    std::vector<std::shared_ptr<SolvingTree>> childrenTrees;
    unsigned int depth = 0;
};
std::ostream& operator<<(std::ostream& os, const SolvingTree::State& state);
