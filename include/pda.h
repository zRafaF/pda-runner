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

    /**
     * @brief Estrutura de nodo do PDA
     */
    struct Node {
        std::string name;                          // Nome do nodo
        std::vector<Pda::Transition> transitions;  // Transições do nodo
        bool isFinal;                              // Indica se o nodo é final

        Node(std::string _name, std::vector<Transition> _transitions, bool _isFinal) : name(_name), transitions(_transitions), isFinal(_isFinal) {}
    };

    Pda() {
    }
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

    /**
     * @brief Insere um novo nodo no PDA
     *
     * @param _transition Transição a ser inserida
     *
     * @return Vetor de transições do nodo de origem
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

    std::map<size_t, Pda::Node> getNodes() { return nodes; }

    /**
     * @brief Define os estados finais do PDA. \n Joga uma exceção caso o estado final não exista
     *
     * @param _finalStates Vetor de índices dos estados finais
     *
     * @return Mapa de nodos do PDA
     */
    std::map<size_t, Pda::Node> setFinalStates(std::vector<int> _finalStates);

   private:
    std::map<size_t, Pda::Node> nodes;
};

std::ostream& operator<<(std::ostream& os, const Pda::Transition& transition);
