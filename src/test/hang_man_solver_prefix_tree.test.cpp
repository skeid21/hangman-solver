#include <gtest/gtest.h>
#include "../dict.hpp"
#include "../hang_man_solver_prefix_tree.hpp"
#include "../oracle.hpp"

TEST(HangManSolverPrefixTree, SolveSucceds)
{
    dictionary_container_t dictionary {
        "bob", "tom", "job", "bab", "bat", "baj"
    };
    Oracle oracle("bob", 5);
    auto response = HangManSolverPrefixTree::solve(oracle, dictionary);
    ASSERT_EQ(response, "bob");
}