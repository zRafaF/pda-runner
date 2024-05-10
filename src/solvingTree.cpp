#include "solvingTree.h"

SolvingTree::SolvingTree(std::shared_ptr<Pda> _pda, std::string _input) {
    state = SolvingTree::State(0, std::stack<char>());
    pda = _pda;
    input = _input;
}

SolvingTree::SolvingTree(SolvingTree::State _state, std::shared_ptr<SolvingTree> _parent, std::vector<std::shared_ptr<SolvingTree>> _children) {
    state = _state;
    parentNode = _parent;
    childrenTrees = _children;
    pda = _parent->pda;
    input = _parent->input;
}

/**
 * Insere um filho na árvore de solução
 */
void SolvingTree::insertChild(std::shared_ptr<SolvingTree> child) {
    childrenTrees.push_back(child);
}