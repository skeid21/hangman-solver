
#ifndef hang_man_solver_prefix_tree_hpp
#define hang_man_solver_prefix_tree_hpp

#include "dict.hpp"
#include "oracle.hpp"

class HangManSolverPrefixTree
{
public:
    static std::string solve(Oracle& oracle, const dictionary_container_t& dictionary);
};


#endif /* hang_man_solver_prefix_tree_hpp */
