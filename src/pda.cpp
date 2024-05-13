#include "pda.h"

std::vector<Pda::Transition> Pda::addTransition(Pda::Transition _transition) {
    const size_t origin = _transition.originIdx;
    const size_t target = _transition.targetIdx;

    if (nodes.count(origin) == 0) {
        nodes.insert(std::make_pair(origin, Pda::Node("q" + std::to_string(origin), std::vector<Pda::Transition>(), false)));
    }
    if (nodes.count(target) == 0) {
        nodes.insert(std::make_pair(target, Pda::Node("q" + std::to_string(target), std::vector<Pda::Transition>(), false)));
    }

    nodes.at(origin).transitions.push_back(_transition);

    return nodes.at(origin).transitions;
}

std::map<size_t, Pda::Node> Pda::setFinalStates(std::vector<int> _finalStates) {
    for (auto finalState : _finalStates) {
        nodes.at(finalState).isFinal = true;
    }
    return nodes;
}

void Pda::printPda() {
    for (auto nodePair : nodes) {
        const auto node = nodePair.second;
        std::cout << "Node " << node.name << (node.isFinal ? " (final)" : "") << std::endl;
        for (auto transition : node.transitions) {
            std::cout << transition.c << ", " << transition.T << "/" << transition.xy << " | target: " << transition.targetIdx << std::endl;
        }

        std::cout << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Pda::Transition& transition) {
    os << transition.originIdx << ", " << transition.c << ", " << transition.T << "/" << transition.xy << " | target: " << transition.targetIdx;

    return os;
}