#pragma once

#include <memory>
#include <string>
#include <vector>

#include "pda.h"

class SolvingTree {
   public:
    /**
     * @brief Estrutura que representa o estado atual do PDA (Computação)
     */
    struct State {
        size_t currentNodeIdx;
        std::stack<char> stack;

        State() : currentNodeIdx(0), stack(std::stack<char>()) {}
        State(size_t _currentNodeIdx, std::stack<char> _stack) : currentNodeIdx(_currentNodeIdx), stack(_stack) {}
    };

    /**
     * @brief Constructor de um objeto SolvingTree raiz
     */
    SolvingTree(std::shared_ptr<Pda> _pda, std::string _input);

    /**
     * @brief Constructor de um objeto SolvingTree não raiz
     *
     * @param _state Estado do PDA
     * @param _parent Nodo pai
     * @param _children Filhos do Nodo
     */
    SolvingTree(SolvingTree::State _state, std::shared_ptr<SolvingTree> _parent, std::vector<std::shared_ptr<SolvingTree>> _children);

    void insertChild(std::shared_ptr<SolvingTree> child);

   private:
    SolvingTree::State state;
    std::shared_ptr<Pda> pda;
    std::string input;

    std::shared_ptr<SolvingTree> parentNode;
    std::vector<std::shared_ptr<SolvingTree>> childrenTrees;
};