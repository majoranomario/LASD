
#include <iostream>

using namespace std;

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"
#include "../set/set.hpp"
#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"
#include "../heap/heap.hpp"
#include "../heap/vec/heapvec.hpp"

#include "../zmytest/exercise1a/test.hpp"
#include "../zmytest/exercise1b/test.hpp"
#include "../zmytest/exercise2a/test.hpp"
#include "../zmytest/exercise2b/test.hpp"


/* ************************************************************************** */

using namespace lasd;

void mytest() {
     
    cout << endl << "~*~#~*~ Welcome to the LASD MyTest Suite ~*~#~*~ " << endl;

    uint loctestnum, loctesterr;
    uint stestnum = 0, stesterr = 0;

    // Execute test of Exercise 1A  
    testSimpleExercise1A(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;

    // Execute test of Exercise 1B
    testSimpleExercise1B(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;

    // Execute test of Exercise 2A
    testSimpleExercise2A(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;
    
    // Execute test of Exercise 2B
    testSimpleExercise2B(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;

    // Summary
    cout << endl << "======================" << endl;
    cout << "TOTALE TEST ESEGUITI: " << stestnum << endl;
    cout << "TOTALE ERRORI:        " << stesterr << endl;
    cout << "======================" << endl;
    
    cout << "\n=== END OF TEST ===" << endl;
}

