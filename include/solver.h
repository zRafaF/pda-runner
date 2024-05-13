#pragma once

#include <memory>
#include <string>
#include <vector>

#include "pda.h"
#include "solvingTree.h"

class Solver {
   public:
    struct SolveResult {
        bool isAccepted;
        std::vector<SolvingTree::State> computation;

        SolveResult(bool _isAccepted, std::vector<SolvingTree::State> _computation) : isAccepted(_isAccepted), computation(_computation) {}
    };

    Solver(std::shared_ptr<Pda> _pda);

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