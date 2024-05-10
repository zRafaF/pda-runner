#include "pda.h"

Pda::Pda() {
}

std::map<size_t, std::vector<Pda::Transition>> Pda::addTransition(Pda::Transition _transition) {
    const size_t origin = _transition.origin;
    // if (transitions.count(origin) == 0) {
    //     transitions[origin] = std::vector<Pda::Transition>();
    // }
    transitions[origin].push_back(_transition);

    return transitions;
}

void Pda::printPda() {
    for (auto transitionsPair : transitions) {
        auto nodeTransitions = transitionsPair.second;

        std::cout << "Node q" << transitionsPair.first << std::endl;

        for (auto transition : nodeTransitions) {
            std::cout << transition.c << ", " << transition.T << "/" << transition.xy << " | target: " << transition.target << std::endl;
        }

        std::cout << "\n";
    }
}