

#ifndef hang_man_solver_hpp
#define hang_man_solver_hpp

#include <stdio.h>

#include "dict.hpp"
#include "oracle.hpp"

class HangManSolver
{
public:
    static std::string solve(Oracle& oracle, const dictionary_container_t& dictionary);
};

#endif /* hang_man_solver_hpp */
