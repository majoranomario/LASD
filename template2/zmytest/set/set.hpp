#ifndef SETLST_COMPLETE_TESTS_HPP
#define SETLST_COMPLETE_TESTS_HPP

#include "../../set/lst/setlst.hpp"
#include "../../set/vec/setvec.hpp"
#include <iostream>

/* ************************************************************************** */

// Test che verifica la correttezza del costruttore da TraversableContainer
template <typename Data, typename Container>
void ConstructFromTraversableTest(uint & testnum, uint & testerr, const Container & container) {
  testnum++;
  try {
    lasd::SetLst<Data> set(container);
    std::cout << " " << testnum << " (" << testerr << ") Construct from TraversableContainer: Correct!" << std::endl;
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in Construct from TraversableContainer: " << exc.what() << std::endl;
    testerr++;
  }
}

// Test che verifica il costruttore da MappableContainer (move)
template <typename Data, typename Container>
void ConstructFromMappableTest(uint & testnum, uint & testerr, Container && container) {
  testnum++;
  try {
    lasd::SetLst<Data> set(std::move(container));
    std::cout << " " << testnum << " (" << testerr << ") Construct from MappableContainer (move): Correct!" << std::endl;
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in Construct from MappableContainer: " << exc.what() << std::endl;
    testerr++;
  }
}

// Test Copy & Move Constructor e Assignment
template <typename Data>
void CopyMoveTest(uint & testnum, uint & testerr, const lasd::SetLst<Data> & original) {
  testnum++;
  try {
    lasd::SetLst<Data> copyConstructed(original);
    lasd::SetLst<Data> copyAssigned;
    copyAssigned = original;

    lasd::SetLst<Data> moveConstructed(std::move(copyConstructed));
    lasd::SetLst<Data> moveAssigned;
    moveAssigned = std::move(copyAssigned);

    std::cout << " " << testnum << " (" << testerr << ") Copy & Move constructors and assignments: Correct!" << std::endl;
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in Copy/Move test: " << exc.what() << std::endl;
    testerr++;
  }
}

// Test operator== e operator!=
template <typename Data>
void EqualityOperatorsTest(uint & testnum, uint & testerr, const lasd::SetLst<Data> & set1, const lasd::SetLst<Data> & set2, bool expectedEq) {
  testnum++;
  try {
    bool eq = (set1 == set2);
    bool neq = (set1 != set2);
    bool ok = (eq == expectedEq) && (neq == !expectedEq);
    std::cout << " " << testnum << " (" << testerr << ") Equality operators: " << (ok ? "Correct!" : "Error!") << std::endl;
    testerr += (ok ? 0 : 1);
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in EqualityOperatorsTest: " << exc.what() << std::endl;
    testerr++;
  }
}

template <typename Data>
void MinMaxOperationsTest(uint & testnum, uint & testerr, lasd::SetLst<Data> & set, const Data & expectedMin, const Data & expectedMax) {
  testnum++;
  try {
    bool ok = true;

    // Verifico Min e Max iniziali
    if (set.Min() != expectedMin) {
      std::cerr << "Error: Min() diverso da expectedMin\n";
      ok = false;
    }

    if (set.Max() != expectedMax) {
      std::cerr << "Error: Max() diverso da expectedMax\n";
      ok = false;
    }

    
    // Rimuovo il minimo e verifico il valore rimosso
    Data minNRem = set.MinNRemove();
    if (minNRem != expectedMin) {
      std::cerr << "Error: MinNRemove() diverso da expectedMin\n";
      ok = false;
    }


    // Rimuovo il massimo (ultimo elemento rimasto)
    Data maxNRem = set.MaxNRemove();
    std::cout << maxNRem << " ";
    if (maxNRem != expectedMax) {
      std::cerr << "Error: MaxNRemove() diverso da expectedMax\n";
      ok = false;
    }

    std::cout << testnum << " (" << testerr << ") Min/Max operations: " 
              << (ok ? "Correct!" : "Error!") << std::endl;
    testerr += (ok ? 0 : 1);

  } catch (const std::exception & exc) {
    std::cout << testnum << " Exception in MinMaxOperationsTest: " << exc.what() << std::endl;
    testerr++;
  }
}


// Test Predecessor() con casi positivi e di eccezione
template <typename Data>
void PredecessorTest(uint & testnum, uint & testerr, const lasd::SetLst<Data> & set, const Data & val, bool expectException, const Data & expectedPred = Data()) {
  testnum++;
  try {
    const Data & pred = set.Predecessor(val);
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") Predecessor(" << val << ") expected exception but got " << pred << ": Error!" << std::endl;
      testerr++;
    } else {
      bool ok = (pred == expectedPred);
      std::cout << " " << testnum << " (" << testerr << ") Predecessor(" << val << ") = " << pred << ": " << (ok ? "Correct!" : "Error!") << std::endl;
      testerr += (ok ? 0 : 1);
    }
  } catch (...) {
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") Predecessor(" << val << ") exception: Correct!" << std::endl;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") Predecessor(" << val << ") unexpected exception: Error!" << std::endl;
      testerr++;
    }
  }
}

// Test Successor() con casi positivi e di eccezione
template <typename Data>
void SuccessorTest(uint & testnum, uint & testerr, const lasd::SetLst<Data> & set, const Data & val, bool expectException, const Data & expectedSucc = Data()) {
  testnum++;
  try {
    const Data & succ = set.Successor(val);
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") Successor(" << val << ") expected exception but got " << succ << ": Error!" << std::endl;
      testerr++;
    } else {
      bool ok = (succ == expectedSucc);
      std::cout << " " << testnum << " (" << testerr << ") Successor(" << val << ") = " << succ << ": " << (ok ? "Correct!" : "Error!") << std::endl;
      testerr += (ok ? 0 : 1);
    }
  } catch (...) {
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") Successor(" << val << ") exception: Correct!" << std::endl;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") Successor(" << val << ") unexpected exception: Error!" << std::endl;
      testerr++;
    }
  }
}

// Test RemovePredecessor() e RemoveSuccessor() - controlla che rimuovano senza eccezioni o con eccezioni quando appropriate
template <typename Data>
void RemovePredecessorTest(uint & testnum, uint & testerr, lasd::SetLst<Data> & set, const Data & val, bool expectException) {
  testnum++;
  try {
    set.RemovePredecessor(val);
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") RemovePredecessor(" << val << ") expected exception but succeeded: Error!" << std::endl;
      testerr++;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") RemovePredecessor(" << val << ") succeeded: Correct!" << std::endl;
    }
  } catch (...) {
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") RemovePredecessor(" << val << ") exception: Correct!" << std::endl;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") RemovePredecessor(" << val << ") unexpected exception: Error!" << std::endl;
      testerr++;
    }
  }
}

template <typename Data>
void RemoveSuccessorTest(uint & testnum, uint & testerr, lasd::SetLst<Data> & set, const Data & val, bool expectException) {
  testnum++;
  try {
    set.RemoveSuccessor(val);
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") RemoveSuccessor(" << val << ") expected exception but succeeded: Error!" << std::endl;
      testerr++;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") RemoveSuccessor(" << val << ") succeeded: Correct!" << std::endl;
    }
  } catch (...) {
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") RemoveSuccessor(" << val << ") exception: Correct!" << std::endl;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") RemoveSuccessor(" << val << ") unexpected exception: Error!" << std::endl;
      testerr++;
    }
  }
}

// Test Clear() e Empty()
template <typename Data>
void ClearEmptyTest(uint & testnum, uint & testerr, lasd::SetLst<Data> & set) {
  testnum++;
  try {
    set.Clear();
    bool isEmpty = set.Empty();
    std::cout << " " << testnum << " (" << testerr << ") Clear() and Empty(): " << (isEmpty ? "Correct!" : "Error!") << std::endl;
    testerr += (isEmpty ? 0 : 1);
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in ClearEmptyTest: " << exc.what() << std::endl;
    testerr++;
  }
}

template <typename Data>
void TestInsert(uint & testnum, uint & testerr, lasd::SetLst<Data> & set, const Data & val, bool expected) {
  testnum++;
  bool result = set.Insert(val);
  std::cout << " " << testnum << " (" << testerr << ") Insert " << val << ": ";
  if (result == expected) {
    std::cout << "Correct!" << std::endl;
  } else {
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}

template <typename Data>
void TestInsertMove(uint & testnum, uint & testerr, lasd::SetLst<Data> & set, Data && val, bool expected) {
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") InsertMove " << val << ": ";
  bool result = set.Insert(std::move(val));
  if (result == expected) {
    std::cout << "Correct!" << std::endl;
  } else {
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}

template <typename Data>
void TestRemove(uint & testnum, uint & testerr, lasd::SetLst<Data> & set, const Data & val, bool expected) {
  testnum++;
  try {
    bool result = set.Remove(val);
    std::cout << " " << testnum << " (" << testerr << ") Remove " << val << ": ";
    if (result == expected) {
      std::cout << "Correct!" << std::endl;
    } else {
      std::cout << "Error!" << std::endl;
      testerr++;
    }
  } catch (std::exception & exc) {
    std::cout << "Exception on Remove: " << exc.what() << std::endl;
    if (!expected) {
      std::cout << "Correct!" << std::endl;
    } else {
      std::cout << "Error!" << std::endl;
      testerr++;
    }
  }
}

template <typename Data>
void TestRemoveMin(uint & testnum, uint & testerr, lasd::SetLst<Data> & set, const Data & expectedMin) {
  testnum++;
  try {
    set.RemoveMin();
    std::cout << " " << testnum << " (" << testerr << ") RemoveMin: ";
    if (!set.Exists(expectedMin)) {
      std::cout << "Correct! Min removed." << std::endl;
    } else {
      std::cout << "Error! Min still exists." << std::endl;
      testerr++;
    }
  } catch (std::exception & exc) {
    std::cout << "Exception on RemoveMin: " << exc.what() << std::endl;
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}

template <typename Data>
void TestRemoveMax(uint & testnum, uint & testerr, lasd::SetLst<Data> & set, const Data & expectedMax) {
  testnum++;
  try {
    set.RemoveMax();
    std::cout << " " << testnum << " (" << testerr << ") RemoveMax: ";
    if (!set.Exists(expectedMax)) {
      std::cout << "Correct! Max removed." << std::endl;
    } else {
      std::cout << "Error! Max still exists." << std::endl;
      testerr++;
    }
  } catch (std::exception & exc) {
    std::cout << "Exception on RemoveMax: " << exc.what() << std::endl;
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}

/* *********************************************************************************** */

//SetVec test

/* ************************************************************************** */

// Test che verifica la correttezza del costruttore da TraversableContainer
template <typename Data, typename Container>
void ConstructFromTraversableTestSetVec(uint & testnum, uint & testerr, const Container & container) {
  testnum++;
  try {
    lasd::SetVec<Data> set(container);
    std::cout << " " << testnum << " (" << testerr << ") Construct from TraversableContainer: Correct!" << std::endl;
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in Construct from TraversableContainer: " << exc.what() << std::endl;
    testerr++;
  }
}

// Test che verifica il costruttore da MappableContainer (move)
template <typename Data, typename Container>
void ConstructFromMappableTestSetVec(uint & testnum, uint & testerr, Container && container) {
  testnum++;
  try {
    lasd::SetVec<Data> set(std::move(container));
    std::cout << " " << testnum << " (" << testerr << ") Construct from MappableContainer (move): Correct!" << std::endl;
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in Construct from MappableContainer: " << exc.what() << std::endl;
    testerr++;
  }
}

// Test Copy & Move Constructor e Assignment
template <typename Data>
void CopyMoveTest(uint & testnum, uint & testerr, const lasd::SetVec<Data> & original) {
  testnum++;
  try {
    lasd::SetVec<Data> copyConstructed(original);
    lasd::SetVec<Data> copyAssigned;
    copyAssigned = original;

    lasd::SetVec<Data> moveConstructed(std::move(copyConstructed));
    lasd::SetVec<Data> moveAssigned;
    moveAssigned = std::move(copyAssigned);

    std::cout << " " << testnum << " (" << testerr << ") Copy & Move constructors and assignments: Correct!" << std::endl;
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in Copy/Move test: " << exc.what() << std::endl;
    testerr++;
  }
}

// Test operator== e operator!=
template <typename Data>
void EqualityOperatorsTest(uint & testnum, uint & testerr, const lasd::SetVec<Data> & set1, const lasd::SetVec<Data> & set2, bool expectedEq) {
  testnum++;
  try {
    bool eq = (set1 == set2);
    bool neq = (set1 != set2);
    bool ok = (eq == expectedEq) && (neq == !expectedEq);
    std::cout << " " << testnum << " (" << testerr << ") Equality operators: " << (ok ? "Correct!" : "Error!") << std::endl;
    testerr += (ok ? 0 : 1);
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in EqualityOperatorsTest: " << exc.what() << std::endl;
    testerr++;
  }
}

template <typename Data>
void MinMaxOperationsTest(uint & testnum, uint & testerr, lasd::SetVec<Data> & set, const Data & expectedMin, const Data & expectedMax) {
  testnum++;
  try {
    bool ok = true;

    if (set.Min() != expectedMin) {
      std::cerr << "Error: Min() diverso da expectedMin\n";
      ok = false;
    }

    if (set.Max() != expectedMax) {
      std::cerr << "Error: Max() diverso da expectedMax\n";
      ok = false;
    }

    
    // Rimuovo il minimo e verifico il valore rimosso
    Data minNRem = set.MinNRemove();
    if (minNRem != expectedMin) {
      std::cerr << "Error: MinNRemove() diverso da expectedMin\n";
      ok = false;
    }


    // Rimuovo il massimo (ultimo elemento rimasto)
    Data maxNRem = set.MaxNRemove();
    std::cout << maxNRem << " ";
    if (maxNRem != expectedMax) {
      std::cerr << "Error: MaxNRemove() diverso da expectedMax\n";
      ok = false;
    }

    std::cout << testnum << " (" << testerr << ") Min/Max operations: " 
              << (ok ? "Correct!" : "Error!") << std::endl;
    testerr += (ok ? 0 : 1);

  } catch (const std::exception & exc) {
    std::cout << testnum << " Exception in MinMaxOperationsTest: " << exc.what() << std::endl;
    testerr++;
  }
}


// Test Predecessor() con casi positivi e di eccezione
template <typename Data>
void PredecessorTest(uint & testnum, uint & testerr, const lasd::SetVec<Data> & set, const Data & val, bool expectException, const Data & expectedPred = Data()) {
  testnum++;
  try {
    const Data & pred = set.Predecessor(val);
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") Predecessor(" << val << ") expected exception but got " << pred << ": Error!" << std::endl;
      testerr++;
    } else {
      bool ok = (pred == expectedPred);
      std::cout << " " << testnum << " (" << testerr << ") Predecessor(" << val << ") = " << pred << ": " << (ok ? "Correct!" : "Error!") << std::endl;
      testerr += (ok ? 0 : 1);
    }
  } catch (...) {
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") Predecessor(" << val << ") exception: Correct!" << std::endl;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") Predecessor(" << val << ") unexpected exception: Error!" << std::endl;
      testerr++;
    }
  }
}

// Test Successor() con casi positivi e di eccezione
template <typename Data>
void SuccessorTest(uint & testnum, uint & testerr, const lasd::SetVec<Data> & set, const Data & val, bool expectException, const Data & expectedSucc = Data()) {
  testnum++;
  try {
    const Data & succ = set.Successor(val);
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") Successor(" << val << ") expected exception but got " << succ << ": Error!" << std::endl;
      testerr++;
    } else {
      bool ok = (succ == expectedSucc);
      std::cout << " " << testnum << " (" << testerr << ") Successor(" << val << ") = " << succ << ": " << (ok ? "Correct!" : "Error!") << std::endl;
      testerr += (ok ? 0 : 1);
    }
  } catch (...) {
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") Successor(" << val << ") exception: Correct!" << std::endl;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") Successor(" << val << ") unexpected exception: Error!" << std::endl;
      testerr++;
    }
  }
}

// Test RemovePredecessor() e RemoveSuccessor() - controlla che rimuovano senza eccezioni o con eccezioni quando appropriate
template <typename Data>
void RemovePredecessorTest(uint & testnum, uint & testerr, lasd::SetVec<Data> & set, const Data & val, bool expectException) {
  testnum++;
  try {
    set.RemovePredecessor(val);
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") RemovePredecessor(" << val << ") expected exception but succeeded: Error!" << std::endl;
      testerr++;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") RemovePredecessor(" << val << ") succeeded: Correct!" << std::endl;
    }
  } catch (...) {
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") RemovePredecessor(" << val << ") exception: Correct!" << std::endl;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") RemovePredecessor(" << val << ") unexpected exception: Error!" << std::endl;
      testerr++;
    }
  }
}

template <typename Data>
void RemoveSuccessorTest(uint & testnum, uint & testerr, lasd::SetVec<Data> & set, const Data & val, bool expectException) {
  testnum++;
  try {
    set.RemoveSuccessor(val);
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") RemoveSuccessor(" << val << ") expected exception but succeeded: Error!" << std::endl;
      testerr++;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") RemoveSuccessor(" << val << ") succeeded: Correct!" << std::endl;
    }
  } catch (...) {
    if (expectException) {
      std::cout << " " << testnum << " (" << testerr << ") RemoveSuccessor(" << val << ") exception: Correct!" << std::endl;
    } else {
      std::cout << " " << testnum << " (" << testerr << ") RemoveSuccessor(" << val << ") unexpected exception: Error!" << std::endl;
      testerr++;
    }
  }
}

// Test Clear() e Empty()
template <typename Data>
void ClearEmptyTest(uint & testnum, uint & testerr, lasd::SetVec<Data> & set) {
  testnum++;
  try {
    set.Clear();
    bool isEmpty = set.Empty();
    std::cout << " " << testnum << " (" << testerr << ") Clear() and Empty(): " << (isEmpty ? "Correct!" : "Error!") << std::endl;
    testerr += (isEmpty ? 0 : 1);
  } catch (const std::exception & exc) {
    std::cout << " " << testnum << " Exception in ClearEmptyTest: " << exc.what() << std::endl;
    testerr++;
  }
}

template <typename Data>
void TestInsert(uint & testnum, uint & testerr, lasd::SetVec<Data> & set, const Data & val, bool expected) {
  testnum++;
  bool result = set.Insert(val);
  std::cout << " " << testnum << " (" << testerr << ") Insert " << val << ": ";
  if (result == expected) {
    std::cout << "Correct!" << std::endl;
  } else {
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}

template <typename Data>
void TestInsertMove(uint & testnum, uint & testerr, lasd::SetVec<Data> & set, Data && val, bool expected) {
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") InsertMove " << val << ": ";
  bool result = set.Insert(std::move(val));
  if (result == expected) {
    std::cout << "Correct!" << std::endl;
  } else {
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}

template <typename Data>
void TestRemove(uint & testnum, uint & testerr, lasd::SetVec<Data> & set, const Data & val, bool expected) {
  testnum++;
  try {
    bool result = set.Remove(val);
    std::cout << " " << testnum << " (" << testerr << ") Remove " << val << ": ";
    if (result == expected) {
      std::cout << "Correct!" << std::endl;
    } else {
      std::cout << "Error!" << std::endl;
      testerr++;
    }
  } catch (std::exception & exc) {
    std::cout << "Exception on Remove: " << exc.what() << std::endl;
    if (!expected) {
      std::cout << "Correct!" << std::endl;
    } else {
      std::cout << "Error!" << std::endl;
      testerr++;
    }
  }
}

template <typename Data>
void TestRemoveMin(uint & testnum, uint & testerr, lasd::SetVec<Data> & set, const Data & expectedMin) {
  testnum++;
  try {
    set.RemoveMin();
    std::cout << " " << testnum << " (" << testerr << ") RemoveMin: ";
    if (!set.Exists(expectedMin)) {
      std::cout << "Correct! Min removed." << std::endl;
    } else {
      std::cout << "Error! Min still exists." << std::endl;
      testerr++;
    }
  } catch (std::exception & exc) {
    std::cout << "Exception on RemoveMin: " << exc.what() << std::endl;
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}

template <typename Data>
void TestRemoveMax(uint & testnum, uint & testerr, lasd::SetVec<Data> & set, const Data & expectedMax) {
  testnum++;
  try {
    set.RemoveMax();
    std::cout << " " << testnum << " (" << testerr << ") RemoveMax: ";
    if (!set.Exists(expectedMax)) {
      std::cout << "Correct! Max removed." << std::endl;
    } else {
      std::cout << "Error! Max still exists." << std::endl;
      testerr++;
    }
  } catch (std::exception & exc) {
    std::cout << "Exception on RemoveMax: " << exc.what() << std::endl;
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}


#endif
