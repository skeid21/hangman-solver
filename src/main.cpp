#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <chrono>

#include "oracle.hpp"
#include "hang_man_solver.hpp"
#include "hang_man_solver_prefix_tree.hpp"

#include "dict.hpp"

static int s_test_count = 100;
static std::vector<int> s_test_word_indices;
using namespace std;
using namespace std::chrono;
typedef std::string (*Solver)(Oracle &, const dictionary_container_t &dict);

void runTest(
    Solver solver,
    int wordIndex,
    int &did_win,
    int &wrong_word)
{
    const dictionary_container_t &dict = getDictionary();
    Oracle oracle(*std::next(dict.begin(), wordIndex), 5);

    auto word = solver(oracle, dict);
    if (oracle.didWin(word))
    {
        did_win++;
    }

    if (word != oracle.getWord())
    {
        wrong_word++;
    }
}

void runTests(Solver solver)
{
    auto prev_time = high_resolution_clock::now();
    int did_win = 0;
    int wrong_word = 0;
    for (int scan = 0; scan < s_test_count; ++scan)
    {
        runTest(
            solver,
            s_test_word_indices[scan],
            did_win,
            wrong_word);
    }
    auto cur_time = high_resolution_clock::now();

    auto time_diff = duration_cast<duration<double>>(cur_time - prev_time);
    auto average_time = time_diff.count() / (float)(s_test_count);

    std::cout << "=================" << std::endl;
    std::cout << "= Test Completed" << std::endl;
    std::cout << "= Test Took: " << average_time << std::endl;
    std::cout << "= Won " << did_win << " out of " << s_test_count << std::endl;
    std::cout << "= Got " << wrong_word << " words wrong out of " << s_test_count << std::endl;
    std::cout << "==================" << std::endl
              << std::endl;
}

int main(int argc, const char *argv[])
{

    std::srand(std::time(nullptr));
    auto dict = getDictionary();
    for (int scan = 0; scan < s_test_count; ++scan)
    {
        s_test_word_indices.push_back(std::rand() % dict.size());
    }

    runTests(HangManSolver::solve);
    runTests(HangManSolverPrefixTree::solve);
}
