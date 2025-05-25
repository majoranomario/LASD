#include <iostream>

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"

#include "../set/set.hpp"


/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */


void stestSetLstInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    std::cout << std::endl << "Begin of SetLst<int> Test:" << std::endl;
    try {
      lasd::SetLst<int> set1;
      for (int val : {1, 3, 5, 7, 9}) {
        set1.Insert(val);
      }
      ConstructFromTraversableTest<int>(loctestnum, loctesterr, set1);
      CopyMoveTest<int>(loctestnum, loctesterr, set1);
  
      TestInsert<int>(loctestnum, loctesterr, set1, 6, true);
      TestInsert<int>(loctestnum, loctesterr, set1, 3, false); // già presente
  
      TestRemove<int>(loctestnum, loctesterr, set1, 9, true);
      TestRemove<int>(loctestnum, loctesterr, set1, 42, false); // non presente
  
      lasd::SetLst<int> set2(set1);
      EqualityOperatorsTest<int>(loctestnum, loctesterr, set1, set2, true);
  
      lasd::SetLst<int> set3;
      for (int val : {2, 8, 10}) {
        set3.Insert(val);
      }
      lasd::SetLst<int> minmaxSet(set3);
      MinMaxOperationsTest<int>(loctestnum, loctesterr, minmaxSet, 2, 10);
  
      lasd::SetLst<int> set4;
      for (int val : {2, 4, 6, 8}) {
        set4.Insert(val);
      }
      lasd::SetLst<int> predSuccSet(set4);
      PredecessorTest<int>(loctestnum, loctesterr, predSuccSet, 6, false, 4);
      SuccessorTest<int>(loctestnum, loctesterr, predSuccSet, 6, false, 8);
      PredecessorTest<int>(loctestnum, loctesterr, predSuccSet, 2, true);
      SuccessorTest<int>(loctestnum, loctesterr, predSuccSet, 8, true);
  
      RemovePredecessorTest<int>(loctestnum, loctesterr, predSuccSet, 6, false);
      RemoveSuccessorTest<int>(loctestnum, loctesterr, predSuccSet, 4, false);
      ClearEmptyTest<int>(loctestnum, loctesterr, set1);
    } catch (...) {
      loctestnum++; loctesterr++;
      std::cout << std::endl << "Unmanaged error!" << std::endl;
    }
    std::cout << "End of SetLst<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
    testnum += loctestnum;
    testerr += loctesterr;
  }

  void stestSetLstFloat(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    std::cout << std::endl << "Begin of SetLst<float> Test:" << std::endl;
  
    try {
      // 1. Costruzione iniziale
      lasd::SetLst<float> set1;
      for (float val : {1.41f, 2.71f, 3.14f}) {
        set1.Insert(val);
      }
  
      ConstructFromTraversableTest<float>(loctestnum, loctesterr, set1);
      CopyMoveTest<float>(loctestnum, loctesterr, set1);
  
      TestInsert<float>(loctestnum, loctesterr, set1, 6.28f, true);
      TestInsert<float>(loctestnum, loctesterr, set1, 3.14f, false); // già presente
  
      TestRemove<float>(loctestnum, loctesterr, set1, 1.41f, true);
      TestRemove<float>(loctestnum, loctesterr, set1, 9.81f, false); // non presente
  
      lasd::SetLst<float> set2;
      for (float val : {2.71f, 3.14f, 6.28f}) { // coerente con lo stato aggiornato di set1
        set2.Insert(val);
      }
  
      EqualityOperatorsTest<float>(loctestnum, loctesterr, set1, set2, true);
  
      // 2. Test Min/Max
      lasd::SetLst<float> minmaxSet;
      for (float val : {1.0f, 2.0f, 3.0f, 4.0f, 5.0f}) {
        minmaxSet.Insert(val);
      }
      MinMaxOperationsTest<float>(loctestnum, loctesterr, minmaxSet, 1.0f, 5.0f);
  
      // 3. Test Predecessor / Successor
      lasd::SetLst<float> predSuccSet;
      for (float val : {2.0f, 4.0f, 6.0f, 8.0f}) {
        predSuccSet.Insert(val);
      }
  
      PredecessorTest<float>(loctestnum, loctesterr, predSuccSet, 6.0f, false, 4.0f);
      SuccessorTest<float>(loctestnum, loctesterr, predSuccSet, 6.0f, false, 8.0f);
  
      PredecessorTest<float>(loctestnum, loctesterr, predSuccSet, 2.0f, true); // nessun predecessore
      SuccessorTest<float>(loctestnum, loctesterr, predSuccSet, 8.0f, true);   // nessun successore
  
      RemovePredecessorTest<float>(loctestnum, loctesterr, predSuccSet, 6.0f, false);
      RemoveSuccessorTest<float>(loctestnum, loctesterr, predSuccSet, 4.0f, false);
  
      // 4. Clear e test su struttura vuota
      ClearEmptyTest<float>(loctestnum, loctesterr, set1);
    } catch (...) {
      loctestnum++;
      loctesterr++;
      std::cout << std::endl << "Unmanaged error!" << std::endl;
    }
  
    std::cout << "End of SetLst<float> Test! (Errors/Tests: "
              << loctesterr << "/" << loctestnum << ")" << std::endl;
  
    testnum += loctestnum;
    testerr += loctesterr;
  
    std::cout << "Test completato senza crash." << std::endl;
  }
  
  
  void stestSetLstString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    std::cout << std::endl << "Begin of SetLst<string> Test:" << std::endl;
  
    try {
      lasd::SetLst<std::string> set1;
      for (std::string val : {"apple", "banana", "cherry"}) {
        set1.Insert(val);
      }
  
      ConstructFromTraversableTest<std::string>(loctestnum, loctesterr, set1);
      CopyMoveTest<std::string>(loctestnum, loctesterr, set1);
  
      TestInsert<std::string>(loctestnum, loctesterr, set1, "date", true);
      TestInsert<std::string>(loctestnum, loctesterr, set1, "banana", false); // già presente
  
      TestRemove<std::string>(loctestnum, loctesterr, set1, "cherry", true);
      TestRemove<std::string>(loctestnum, loctesterr, set1, "kiwi", false); // non presente
  
      lasd::SetLst<std::string> set2(set1);
      EqualityOperatorsTest<std::string>(loctestnum, loctesterr, set1, set2, true);
  
      // Test Min/Max
      lasd::SetLst<std::string> minmaxSet;
      for (std::string val : {"alpha", "kilo", "zulu"}) {
        minmaxSet.Insert(val);
      }
      MinMaxOperationsTest<std::string>(loctestnum, loctesterr, minmaxSet, "alpha", "zulu");
  
      // Test Predecessor / Successor
      lasd::SetLst<std::string> predSuccSet;
      for (std::string val : {"cat", "dog", "elephant", "giraffe"}) {
        predSuccSet.Insert(val);
      }
  
      PredecessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "elephant", false, "dog");
      SuccessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "elephant", false, "giraffe");
  
      PredecessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "cat", true);      // nessun predecessore
      SuccessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "giraffe", true);    // nessun successore
  
      RemovePredecessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "elephant", false);
      RemoveSuccessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "dog", false);
  
      ClearEmptyTest<std::string>(loctestnum, loctesterr, set1);
  
    } catch (...) {
      loctestnum++; loctesterr++;
      std::cout << std::endl << "Unmanaged error!" << std::endl;
    }
  
    std::cout << "End of SetLst<string> Test! (Errors/Tests: " 
              << loctesterr << "/" << loctestnum << ")" << std::endl;
  
    testnum += loctestnum;
    testerr += loctesterr;
  }


void stestSetVecInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  std::cout << std::endl << "Begin of SetVec<int> Test:" << std::endl;
  try {
      lasd::SetVec<int> set1;
      for (int val : {1, 7, 3, 5, 9}) {
        set1.Insert(val);
      }
      ConstructFromTraversableTestSetVec<int>(loctestnum, loctesterr, set1);
      CopyMoveTest<int>(loctestnum, loctesterr, set1);

      TestInsert<int>(loctestnum, loctesterr, set1, 6, true);
      TestInsert<int>(loctestnum, loctesterr, set1, 3, false); // già presente

      TestRemove<int>(loctestnum, loctesterr, set1, 9, true);
      TestRemove<int>(loctestnum, loctesterr, set1, 42, false); // non presente

      lasd::SetVec<int> set2(set1);
      EqualityOperatorsTest<int>(loctestnum, loctesterr, set1, set2, true);

      lasd::SetVec<int> set3;
      for (int val : {2, 8, 10}) {
          set3.Insert(val);
      }
      lasd::SetVec<int> minmaxSet(set3);
      MinMaxOperationsTest<int>(loctestnum, loctesterr, minmaxSet, 2, 10);

      lasd::SetVec<int> set4;
      for (int val : {2, 4, 6, 8}) {
          set4.Insert(val);
      }
      lasd::SetVec<int> predSuccSet(set4);
      PredecessorTest<int>(loctestnum, loctesterr, predSuccSet, 6, false, 4);
      SuccessorTest<int>(loctestnum, loctesterr, predSuccSet, 6, false, 8);
      PredecessorTest<int>(loctestnum, loctesterr, predSuccSet, 2, true);
      SuccessorTest<int>(loctestnum, loctesterr, predSuccSet, 8, true);

      RemovePredecessorTest<int>(loctestnum, loctesterr, predSuccSet, 6, false);
      RemoveSuccessorTest<int>(loctestnum, loctesterr, predSuccSet, 4, false);
      ClearEmptyTest<int>(loctestnum, loctesterr, set1);
  }
  catch (...) {
      loctestnum++; loctesterr++;
      std::cout << std::endl << "Unmanaged error!" << std::endl;
  }
  std::cout << "End of SetVec<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestSetVecFloat(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    std::cout << std::endl << "Begin of SetVec<float> Test:" << std::endl;
    try {
        lasd::SetVec<float> set1;
        for (float val : {1.1f, 3.3f, 5.5f, 7.7f, 9.9f}) {
            set1.Insert(val);
        }
        ConstructFromTraversableTestSetVec<float>(loctestnum, loctesterr, set1);
        CopyMoveTest<float>(loctestnum, loctesterr, set1);

        TestInsert<float>(loctestnum, loctesterr, set1, 6.6f, true);
        TestInsert<float>(loctestnum, loctesterr, set1, 3.3f, false); // già presente

        TestRemove<float>(loctestnum, loctesterr, set1, 9.9f, true);
        TestRemove<float>(loctestnum, loctesterr, set1, 42.42f, false); // non presente

        lasd::SetVec<float> set2(set1);
        EqualityOperatorsTest<float>(loctestnum, loctesterr, set1, set2, true);

        lasd::SetVec<float> set3;
        for (float val : {2.2f, 8.8f, 10.1f}) {
            set3.Insert(val);
        }
        lasd::SetVec<float> minmaxSet(set3);
        MinMaxOperationsTest<float>(loctestnum, loctesterr, minmaxSet, 2.2f, 10.1f);

        lasd::SetVec<float> set4;
        for (float val : {2.2f, 4.4f, 6.6f, 8.8f}) {
            set4.Insert(val);
        }
        lasd::SetVec<float> predSuccSet(set4);
        PredecessorTest<float>(loctestnum, loctesterr, predSuccSet, 6.6f, false, 4.4f);
        SuccessorTest<float>(loctestnum, loctesterr, predSuccSet, 6.6f, false, 8.8f);
        PredecessorTest<float>(loctestnum, loctesterr, predSuccSet, 2.2f, true);
        SuccessorTest<float>(loctestnum, loctesterr, predSuccSet, 8.8f, true);

        RemovePredecessorTest<float>(loctestnum, loctesterr, predSuccSet, 6.6f, false);
        RemoveSuccessorTest<float>(loctestnum, loctesterr, predSuccSet, 4.4f, false);
        ClearEmptyTest<float>(loctestnum, loctesterr, set1);
    }
    catch (...) {
        loctestnum++; loctesterr++;
        std::cout << std::endl << "Unmanaged error!" << std::endl;
    }
    std::cout << "End of SetVec<float> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void stestSetVecString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    std::cout << std::endl << "Begin of SetVec<std::string> Test:" << std::endl;
    try {
        lasd::SetVec<std::string> set1;
        for ( std::string val : {"apple", "banana", "cherry", "date", "fig"}) {
          set1.Insert(val);
        }
        ConstructFromTraversableTestSetVec<std::string>(loctestnum, loctesterr, set1);
        CopyMoveTest<std::string>(loctestnum, loctesterr, set1);

        TestInsert<std::string>(loctestnum, loctesterr, set1, "grape", true);
        TestInsert<std::string>(loctestnum, loctesterr, set1, "banana", false); // già presente

        TestRemove<std::string>(loctestnum, loctesterr, set1, "fig", true);
        TestRemove<std::string>(loctestnum, loctesterr, set1, "kiwi", false); // non presente

        lasd::SetVec<std::string> set2(set1);
        EqualityOperatorsTest<std::string>(loctestnum, loctesterr, set1, set2, true);

        lasd::SetVec<std::string> set3;
        for ( std::string val : {"avocado", "blueberry", "cantaloupe"}) {
            set3.Insert(val);
        }
        lasd::SetVec<std::string> minmaxSet(set3);
        MinMaxOperationsTest<std::string>(loctestnum, loctesterr, minmaxSet, "avocado", "cantaloupe");

        lasd::SetVec<std::string> set4;
        for ( std::string val : {"avocado", "blackberry", "clementine", "date"}) {
            set4.Insert(val);
        }
        lasd::SetVec<std::string> predSuccSet(set4);
        PredecessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "clementine", false, "blackberry");
        SuccessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "clementine", false, "date");
        PredecessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "avocado", true);
        SuccessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "date", true);

        RemovePredecessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "clementine", false);
        RemoveSuccessorTest<std::string>(loctestnum, loctesterr, predSuccSet, "blackberry", false);
        ClearEmptyTest<std::string>(loctestnum, loctesterr, set1);
    }
    catch (...) {
        loctestnum++; loctesterr++;
        std::cout << std::endl << "Unmanaged error!" << std::endl;
    }
    std::cout << "End of SetVec<std::string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
    testnum += loctestnum;
    testerr += loctesterr;
}
  

void testSimpleExercise1B(unsigned int & testCount, unsigned int & errorCount) {
    std::cout << std::endl << "Begin of TEST EXERCISE B:" << std::endl;
  
    stestSetLstInt(testCount, errorCount);
    stestSetLstString(testCount, errorCount);
    stestSetLstFloat(testCount, errorCount);
    stestSetVecInt(testCount,errorCount);
    stestSetVecFloat(testCount,errorCount);
    stestSetVecString(testCount,errorCount);
  
    std::cout << std::endl << "End of TEST EXERCISE B!" << std::endl;
    std::cout << "Test eseguiti: " << testCount << std::endl;
    std::cout << "Errori riscontrati: " << errorCount << std::endl;
}
  