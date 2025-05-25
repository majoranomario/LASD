
#include <iostream>

using namespace std;

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../set/set.hpp"
#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"

#include "../zmytest/exercise1a/test.hpp"
#include "../zmytest/exercise1b/test.hpp"


/* ************************************************************************** */

using namespace lasd;

void mytest() {
     
    cout << endl << "~*~#~*~ Welcome to the LASD Test Suite ~*~#~*~ " << endl;

    
    uint loctestnum, loctesterr;
    uint stestnum = 0, stesterr = 0;

    // Esegui test dell'esercizio 1A
    testSimpleExercise1A(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;

    // Esegui test dell'esercizio 1B
    testSimpleExercise1B(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;

    // Sommario generale
    cout << endl << "======================" << endl;
    cout << "TOTALE TEST ESEGUITI: " << stestnum << endl;
    cout << "TOTALE ERRORI:        " << stesterr << endl;
    cout << "======================" << endl;
    

    /*SetVec<int> set1 = SetVec<int>();

    set1.Insert(5);

    SetVec<int> set2 = SetVec<int>(set1);

    cout << (set1 == set2);*/

    cout << "\n=== FINE TEST ===" << endl;
}

