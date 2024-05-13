#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

class Pda {
   public:
    /**
     * @brief Estrutura de transição do PDA
     */
    struct Transition {
        size_t originIdx;  // Índice do nó de origem
        char c;            // Letra a consumir
        char T;            // Letra no topo da pilha
        std::string xy;    // Letras a serem empilhadas
        size_t targetIdx;  // Índice do nó de destino

        Transition(size_t _origin, char _c, char _T, std::string _xy, size_t _target) : originIdx(_origin), c(_c), T(_T), xy(_xy), targetIdx(_target) {}
    };

    struct Node {
        std::string name;
        std::vector<Pda::Transition> transitions;
        bool isFinal;

        Node(std::string _name, std::vector<Transition> _transitions, bool _isFinal) : name(_name), transitions(_transitions), isFinal(_isFinal) {}
    };

    /**
     * @brief Construtor do PDA vazio
     */
    Pda() {
    }

    /**
     * @brief Constrói um PDA com as transições preenchidas
     */
    template <typename... Args>
    Pda(Pda::Transition _transition, Args... args, std::vector<int> _finalStates) {
        addTransition(_transition);
        addTransition(_transition, args...);
        setFinalStates(_finalStates);
    }

    Pda(std::vector<Pda::Transition> _transitions, std::vector<int> _finalStates) {
        for (auto transition : _transitions) {
            addTransition(transition);
        }
        setFinalStates(_finalStates);
    }

    // std::map<size_t, std::vector<Pda::Transition>> getTransitions() { return transitions; }

    /**
     * @brief Insere um novo nodo no PDA
     *
     * @param _node Novo nó **OBS:** O índice deve ser preenchido
     */
    std::vector<Pda::Transition> addTransition(Pda::Transition _transition);

    template <typename... Args>
    void addTransition(Pda::Transition _transition, Args... args) {
        addTransition(_transition);
        addTransition(args...);
    }

    /**
     * @brief Imprime todos os nós do PDA
     */
    void printPda();

    std::map<size_t, Pda::Node> setFinalStates(std::vector<int> _finalStates);

   private:
    std::map<size_t, Pda::Node> nodes;
    std::stack<std::string> stack;
};