#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

class Pda {
   public:
    struct Transition {
        size_t origin;   // Índice do nó de origem
        char c;          // Letra a consumir
        char T;          // Letra no topo da pilha
        std::string xy;  // Letras a serem empilhadas
        size_t target;   // Índice do nó de destino

        Transition(size_t _origin, char _c, char _T, std::string _xy, size_t _target) : origin(_origin), c(_c), T(_T), xy(_xy), target(_target) {}
    };

    /**
     * @brief Construtor do PDA vazio
     */
    Pda();

    /**
     * @brief Constroi um PDA com as transições preenchidas
     */
    template <typename... Args>
    Pda(Pda::Transition _transition, Args... args) {
        addTransition(_transition);
        addTransition(args...);
    }
    std::map<size_t, std::vector<Pda::Transition>> getTransitions() { return transitions; }

    /**
     * @brief Insere um novo nodo no PDA
     *
     * @param _node Novo nó **OBS:** O índice deve ser preenchido
     */
    std::map<size_t, std::vector<Pda::Transition>> addTransition(Pda::Transition _transition);

    template <typename... Args>
    void addTransition(Pda::Transition _transition, Args... args) {
        addTransition(_transition);
        addTransition(args...);
    }

    /**
     * @brief Imprime todos os nós do PDA
     */
    void printPda();

   private:
    /**
     * @brief Mapa de transições do PDA
     *
     * O primeiro elemento do par é o índice do nó de origem ex: 0 = q0, 1 = q1, ...
     */
    std::map<size_t, std::vector<Pda::Transition>> transitions;

    std::stack<char> stack;
};