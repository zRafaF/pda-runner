#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "pda.h"

#define MAX_DEPTH 999

class SolvingTree {
   public:
    /**
     * @brief Estrutura que representa o estado atual do PDA (Computação)
     */
    struct State {
        std::string currentWord;  // Palavra atual
        size_t currentNodeIdx;    // Índice do nó atual
        std::stack<char> stack;   // Pilha atual

        State() : currentWord(""), currentNodeIdx(0), stack(std::stack<char>()) {}
        State(std::string _currentWord, size_t _currentNodeIdx, std::stack<char> _stack) : currentWord(_currentWord), currentNodeIdx(_currentNodeIdx), stack(_stack) {}
    };

    /**
     * @brief Estrutura que representa o resultado da computação
     */
    struct ComputationResult {
        bool isAccepted;                             // Indica se a palavra foi aceita
        std::stack<SolvingTree::State> computation;  // Computação realizada

        ComputationResult(bool _isAccepted, std::stack<SolvingTree::State> _computation) : isAccepted(_isAccepted), computation(_computation) {}
    };

    /**
     * @brief Estrutura que representa o resultado da computação de uma transição
     */
    struct TransitionComputingResult {
        bool isAccepted;
        SolvingTree::State state;

        TransitionComputingResult(bool _isAccepted, SolvingTree::State _state) : isAccepted(_isAccepted), state(_state) {}
    };

    /**
     * @brief Constructor de um objeto SolvingTree raiz
     *
     * @param _pda PDA a ser resolvido
     *
     * @param _input Palavra a ser resolvida
     */
    SolvingTree(std::shared_ptr<Pda> _pda, std::string _input);

    /**
     * @brief Constructor de um objeto SolvingTree filho
     *
     * @param _state Estado do filho
     *
     * @param _parent Smart pointer para o pai
     */
    SolvingTree(SolvingTree::State _state, std::shared_ptr<SolvingTree> _parent);

    SolvingTree::ComputationResult compute(std::shared_ptr<SolvingTree> _myPointer);

   private:
    /**
     * @brief Insere um novo filho na árvore
     *
     * @param child Filho a ser inserido
     */
    void insertChild(std::shared_ptr<SolvingTree> child);

    /**
     * @brief Computa uma transição (Verifica se é possível realizar a transição)
     *
     * @param transition Transição a ser computada
     *
     * @return Resultado da computação
     */
    SolvingTree::TransitionComputingResult computeTransition(Pda::Transition transition);

    SolvingTree::State state;
    std::shared_ptr<Pda> pda;

    std::shared_ptr<SolvingTree> parentNode;
    std::vector<std::shared_ptr<SolvingTree>> childrenTrees;
    unsigned int depth = 0;
};

// Sobrecarga do operador de impressão para o estado
std::ostream& operator<<(std::ostream& os, const SolvingTree::State& state);
