#include "solvingTree.h"

SolvingTree::SolvingTree(std::shared_ptr<Pda> _pda, std::string _input) {
    // Inicializando o estado inicial com Z no topo da pilha
    state = SolvingTree::State(_input, 0, std::stack<char>(std::deque<char>({'Z'})));

    pda = _pda;
    depth = 0;
}

SolvingTree::SolvingTree(SolvingTree::State _state, std::shared_ptr<SolvingTree> _parent) {
    state = _state;
    parentNode = _parent;
    pda = _parent->pda;
    depth = _parent->depth + 1;
}

/**
 * Insere um filho na árvore de solução
 */
void SolvingTree::insertChild(std::shared_ptr<SolvingTree> child) {
    childrenTrees.push_back(child);
}

SolvingTree::ComputationResult SolvingTree::compute(std::shared_ptr<SolvingTree> _myPointer) {
    SolvingTree::ComputationResult result(false, std::stack<SolvingTree::State>());

    if (depth > MAX_DEPTH) {
        return result;
    }
    std::vector<Pda::Transition> possibleTransitions;
    const auto currentNode = pda->getNodes().at(state.currentNodeIdx);

    for (auto transition : currentNode.transitions) {
        auto transactionResult = computeTransition(transition);
        // std::cout << "Current State: " << state << std::endl;

        // std::cout << "Computing transition: " << transition << std::endl;

        // std::cout << "Transaction result: " << transactionResult.isAccepted << "\n\n\n\n";
        if (transactionResult.isAccepted) {
            auto newChild = std::make_shared<SolvingTree>(transactionResult.state, _myPointer);
            insertChild(newChild);
            auto childResult = newChild->compute(newChild);
            if (childResult.isAccepted) {
                childResult.computation.push(state);
                return childResult;
            }
        }
    }

    if (currentNode.isFinal && state.currentWord == "&") {
        result.isAccepted = true;
        result.computation.push(state);
        return result;
    }
    return result;
}

SolvingTree::TransitionComputingResult SolvingTree::computeTransition(Pda::Transition transition) {
    SolvingTree::TransitionComputingResult result(false, state);

    if (transition.originIdx == result.state.currentNodeIdx) {
        if (transition.c == '&' || transition.c == result.state.currentWord[0]) {
            if (transition.c != '&') {
                result.state.currentWord = result.state.currentWord.substr(1);
                if (result.state.currentWord.empty()) {
                    result.state.currentWord = "&";
                }
            }
            if (transition.T == result.state.stack.top() || transition.T == '&') {
                if (transition.T != '&') {
                    result.state.stack.pop();
                }

                std::string reversedXy = transition.xy;
                std::reverse(reversedXy.begin(), reversedXy.end());

                for (auto c : reversedXy) {
                    if (c != '&')
                        result.state.stack.push(c);
                }
                result.state.currentNodeIdx = transition.targetIdx;
                result.isAccepted = true;
            }
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const SolvingTree::State& state) {
    os << "(q" << state.currentNodeIdx << ", " << state.currentWord << ", ";
    std::stack<char> stack_copy = state.stack;

    while (!stack_copy.empty()) {
        os << stack_copy.top();
        stack_copy.pop();
    }
    os << ")";
    return os;
}