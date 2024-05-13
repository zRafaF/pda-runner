#include "solver.h"

Solver::Solver(std::shared_ptr<Pda> _pda) {
    pda = _pda;
}

void Solver::initialize(std::string _input) {
    input = _input;
    computation = std::vector<SolvingTree::State>();
    solvingTree = std::make_shared<SolvingTree>(pda, input);
}

SolvingTree::ComputationResult Solver::solve(std::string _input) {
    initialize(_input);
    auto result = solvingTree->compute(solvingTree);

    return result;
}