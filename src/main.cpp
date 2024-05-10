#include <iostream>
#include <memory>

#include "pda.h"
#include "solvingTree.h"

int main() {
    std::string input = "aabb";
    Pda pda(Pda::Transition(0, 'a', '&', "A", 0), Pda::Transition(0, '&', '&', "&", 1), Pda::Transition(1, 'b', 'A', "&", 1), Pda::Transition(1, '&', 'Z', "Z", 2));
    std::shared_ptr<SolvingTree> tree(new SolvingTree(std::make_shared<Pda>(pda), input));

    pda.printPda();

    return 0;
}