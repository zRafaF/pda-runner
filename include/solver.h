#pragma once

#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "pda.h"
#include "solvingTree.h"

class Solver {
   public:
    Solver(Pda _pda);

   private:
    Pda pda;
    std::string input;
    std::vector<SolvingTree::State> computation;
    std::unique_ptr<SolvingTree> solvingTree;
};