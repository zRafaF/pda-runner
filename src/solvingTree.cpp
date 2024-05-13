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

void SolvingTree::insertChild(std::shared_ptr<SolvingTree> child) {
    childrenTrees.push_back(child);
}

SolvingTree::ComputationResult SolvingTree::compute(std::shared_ptr<SolvingTree> _myPointer) {
    SolvingTree::ComputationResult result(false, std::stack<SolvingTree::State>());

    // Verifica se a profundidade máxima foi atingida
    if (depth > MAX_DEPTH)
        return result;

    std::vector<Pda::Transition> possibleTransitions;
    const auto currentNode = pda->getNodes().at(state.currentNodeIdx);

    // Para cada transição do nó atual
    for (auto transition : currentNode.transitions) {
        // Verifica se a transição é válida
        auto transactionResult = computeTransition(transition);

        if (transactionResult.isAccepted) {
            // Adiciona a nova arvore na lista de filhos
            auto newChild = std::make_shared<SolvingTree>(transactionResult.state, _myPointer);
            insertChild(newChild);

            // Verifica se a palavra foi aceita
            auto childResult = newChild->compute(newChild);
            if (childResult.isAccepted) {
                childResult.computation.push(state);
                return childResult;
            }
        }
    }

    // Condição de parada da recursão
    if (currentNode.isFinal && state.currentWord == "&") {
        result.isAccepted = true;
        result.computation.push(state);
    }

    return result;
}

SolvingTree::TransitionComputingResult SolvingTree::computeTransition(Pda::Transition transition) {
    SolvingTree::TransitionComputingResult result(false, state);

    if (transition.originIdx == result.state.currentNodeIdx) {
        if (transition.c == '&' || transition.c == result.state.currentWord[0]) {
            if (transition.c != '&') {
                // Remove o primeiro caractere da palavra
                result.state.currentWord = result.state.currentWord.substr(1);

                // Se a palavra acabou, adiciona um & para indicar que a palavra foi consumida
                if (result.state.currentWord.empty()) {
                    result.state.currentWord = "&";
                }
            }

            // Verifica se o topo da pilha é igual ou vazio
            if (transition.T == result.state.stack.top() || transition.T == '&') {
                if (transition.T != '&') {
                    result.state.stack.pop();
                }

                // Adiciona os caracteres da string xy invertidos na pilha
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

// Overload do operador <<
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