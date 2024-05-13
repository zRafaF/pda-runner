#pragma once

#include <memory>
#include <string>
#include <vector>

#include "pda.h"
#include "solvingTree.h"

class Solver {
   public:
    Solver(std::shared_ptr<Pda> _pda);

    /**
     * @brief Resolve o PDA
     *
     * @param _input Palavra a ser resolvida
     *
     * @return Resultado da resolução
     */
    SolvingTree::ComputationResult solve(std::string _input);

   private:
    /**
     * @brief Inicializa as variáveis do solver
     */
    void initialize(std::string _input);

    std::shared_ptr<Pda> pda;
    std::string input;
    std::vector<SolvingTree::State> computation;
    std::shared_ptr<SolvingTree> solvingTree;
};