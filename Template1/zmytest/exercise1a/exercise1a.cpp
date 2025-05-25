#include <iostream>

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"

#include "../list/list.hpp"


/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void stestVectorEqualNotEqual(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin Equal/NonEqual Vector Tests:" << endl;

  try {
    lasd::Vector<int> v1(3);
    lasd::Vector<int> v2(3);
    for (ulong i = 0; i < 3; i++) {
      v1[i] = static_cast<int>(i);
      v2[i] = static_cast<int>(i);
    }
    EqualVector(loctestnum, loctesterr, v1, v2, true);
    NonEqualVector(loctestnum, loctesterr, v1, v2, false);

    v2[1] = 99;
    EqualVector(loctestnum, loctesterr, v1, v2, false);
    NonEqualVector(loctestnum, loctesterr, v1, v2, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << "Unmanaged error in Equal/NonEqual test!" << endl;
  }

  cout << "End Equal/NonEqual Tests! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorAccessResizeClear(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin Access/Resize/Clear Tests:" << endl;

  try {
    lasd::Vector<std::string> vec(4);
    vec[0] = "a"; vec[1] = "b"; vec[2] = "c"; vec[3] = "d";

    AccessOperator(loctestnum, loctesterr, vec, 2, true, std::string("c"));
    ModifyElement(loctestnum, loctesterr, vec, 2, std::string("z"), true, std::string("z"));
    FrontBack(loctestnum, loctesterr, vec, true, string("a"), string("d"));

    lasd::Vector<std::string> expectedAfterResize(3);
    expectedAfterResize[0] = std::string("a"); expectedAfterResize[1] = "b"; expectedAfterResize[2] = std::string("z");

    ResizeVector(loctestnum, loctesterr, vec, 3, true, expectedAfterResize);

    ClearVector(loctestnum, loctesterr, vec, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << "Unmanaged error in Access/Resize/Clear tests!" << endl;
  }

  cout << "End Access/Resize/Clear Tests! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorCopyMove(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin Copy/Move Constructor Tests:" << endl;

  try {
    lasd::Vector<double> original(3);
    original[0] = 1.1; original[1] = 2.2; original[2] = 3.3;

    CopyConstructorTest(loctestnum, loctesterr, original, true);

    lasd::Vector<double> movable(3);
    movable[0] = 4.4; movable[1] = 5.5; movable[2] = 6.6;

    lasd::Vector<double> expectedAfterMove(3);
    expectedAfterMove[0] = 4.4; expectedAfterMove[1] = 5.5; expectedAfterMove[2] = 6.6;

    MoveConstructorTest(loctestnum, loctesterr, std::move(movable), expectedAfterMove, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << "Unmanaged error in Copy/Move tests!" << endl;
  }

  cout << "End Copy/Move Constructor Tests! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorAccessOutOfRange(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin Access Out of Range Tests:" << endl;

  try {
    lasd::Vector<int> vec(2);
    vec[0] = 100; vec[1] = 200;

    AccessOutOfRange(loctestnum, loctesterr, vec, 2, true); // index 2 out of range
    AccessOutOfRange(loctestnum, loctesterr, vec, 5, true); // index 5 out of range
    AccessOutOfRange(loctestnum, loctesterr, vec, 1, false); // index 1 in range, should error (no exception)
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << "Unmanaged error in OutOfRange tests!" << endl;
  }

  cout << "End Access Out of Range Tests! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<int> Test:" << endl;
  try {
    {
      lasd::SortableVector<int> vec;
      Empty(loctestnum, loctesterr, vec, true);

      GetFront(loctestnum, loctesterr, vec, false, 0);
      GetBack(loctestnum, loctesterr, vec, false, 0);
      SetAt(loctestnum, loctesterr, vec, false, 1, 0);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0);

      Exists(loctestnum, loctesterr, vec, false, 0);

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
    }
    {
      lasd::SortableVector<int> vec(3);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 3);

      SetAt(loctestnum, loctesterr, vec, true, 0, 4);
      SetAt(loctestnum, loctesterr, vec, true, 1, 3);
      SetAt(loctestnum, loctesterr, vec, true, 2, 1);

      GetFront(loctestnum, loctesterr, vec, true, 4);
      
      GetBack(loctestnum, loctesterr, vec, true, 1);

      SetFront(loctestnum, loctesterr, vec, true, 5);
      SetBack(loctestnum, loctesterr, vec, true, 4);

      Exists(loctestnum, loctesterr, vec, true, 4);

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 12);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 60);

      vec.Sort();

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

      vec.Resize(2);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 12);
    }
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<double> Test:" << endl;
  try {
    lasd::SortableVector<double> vec(3);
    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 3);

    SetAt(loctestnum, loctesterr, vec, true, 0, 5.5);
    SetAt(loctestnum, loctesterr, vec, true, 1, 3.3);
    SetAt(loctestnum, loctesterr, vec, true, 2, 1.1);

    GetFront(loctestnum, loctesterr, vec, true, 5.5);
    GetBack(loctestnum, loctesterr, vec, true, 1.1);

    Exists(loctestnum, loctesterr, vec, true, 3.3);

    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 9.9);
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 1.0, 19.965);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestVectorString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<string> Test:" << endl;
  try {
    lasd::SortableVector<string> vec(2);

    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 2);

    SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));

    GetFront(loctestnum, loctesterr, vec, true, string("A"));
    GetBack(loctestnum, loctesterr, vec, true, string("B"));

    Exists(loctestnum, loctesterr, vec, true, string("A"));

    MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) { MapStringAppend(str, string(" ")); });
    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XA B "));
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XB A "));

    Exists(loctestnum, loctesterr, vec, false, string("A"));

    lasd::SortableVector<string> copvec(vec);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) { MapStringAppend(str, string("!")); });
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

    copvec = move(vec);
    FoldPreOrder(loctestnum, loctesterr, copvec, true, &FoldStringConcatenate, string("?"), string("?A !B !"));

    lasd::SortableVector<string> movvec(move(vec));
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?A B "));
    movvec.Sort();
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?A B "));
    SetAt(loctestnum, loctesterr, vec, false, 1, string(""));
    vec.Resize(1);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));

    movvec.Clear();
    Empty(loctestnum, loctesterr, movvec, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}


void stestListInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  std::cout << std::endl << "Begin of List<int> Test:" << std::endl;
  try {
    lasd::List<int> lst;

    // Stato iniziale
    EmptyTest(loctestnum, loctesterr, lst, true);
    SizeTest(loctestnum, loctesterr, lst, 0);

    // Inserimento frontale
    InsertAtFront(loctestnum, loctesterr, lst, true, 10);
    InsertAtFront(loctestnum, loctesterr, lst, true, 20);
    InsertAtFront(loctestnum, loctesterr, lst, true, 30); // Lista: 30 -> 20 -> 10

    // Test di accesso
    FrontTest(loctestnum, loctesterr, lst, true, 30);
    BackTest(loctestnum, loctesterr, lst, true, 10);
    AccessTest(loctestnum, loctesterr, lst, true, 1, 20);

    // Rimozione e accesso
    FrontNRemove(loctestnum, loctesterr, lst, true, 30); // Rimuove 30
    BackNRemove(loctestnum, loctesterr, lst, true, 10);  // Rimuove 10

    // Stato della lista
    SizeTest(loctestnum, loctesterr, lst, 1);
    FrontTest(loctestnum, loctesterr, lst, true, 20);
    BackTest(loctestnum, loctesterr, lst, true, 20);

    // Clear
    ClearTest(loctestnum, loctesterr, lst);
    EmptyTest(loctestnum, loctesterr, lst, true);
    SizeTest(loctestnum, loctesterr, lst, 0);

    // Test su lista vuota
    RemoveFromFront(loctestnum, loctesterr, lst, false);
    BackNRemove(loctestnum, loctesterr, lst, false, 0);
    FrontTest(loctestnum, loctesterr, lst, false, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    std::cout << std::endl << "Unmanaged error!" << std::endl;
  }

  std::cout << "End of List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestListDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  std::cout << std::endl << "Begin of List<double> Test:" << std::endl;
  try {
    lasd::List<double> lst1, lst2;

    // Test iniziale
    EmptyTest(loctestnum, loctesterr, lst1, true);
    SizeTest(loctestnum, loctesterr, lst1, 0);

    // Inserimento in testa
    InsertAtFront(loctestnum, loctesterr, lst1, true, 2.2);
    InsertAtFront(loctestnum, loctesterr, lst1, true, 3.3);
    InsertAtFront(loctestnum, loctesterr, lst1, true, 4.4); // Lista: 4.4 -> 3.3 -> 2.2

    // Inserimento in coda
    InsertAtBack(loctestnum, loctesterr, lst1, true, 5.5); // Lista: 4.4 -> 3.3 -> 2.2 -> 5.5

    // Accesso
    FrontTest(loctestnum, loctesterr, lst1, true, 4.4);
    BackTest(loctestnum, loctesterr, lst1, true, 5.5);
    AccessTest(loctestnum, loctesterr, lst1, true, 2, 2.2);

    // Clonazione e confronto
    lst2 = lst1;
    EqualList(loctestnum, loctesterr, lst1, lst2, true);
    NonEqualList(loctestnum, loctesterr, lst1, lst2, false);

    // Modifica lst2 per renderla diversa
    RemoveFromBack(loctestnum, loctesterr, lst2, true);
    InsertAtBack(loctestnum, loctesterr, lst2, true, 9.9);

    EqualList(loctestnum, loctesterr, lst1, lst2, false);
    NonEqualList(loctestnum, loctesterr, lst1, lst2, true);

    // Rimozione
    FrontNRemove(loctestnum, loctesterr, lst1, true, 4.4);
    BackNRemove(loctestnum, loctesterr, lst1, true, 5.5);

    SizeTest(loctestnum, loctesterr, lst1, 2);
    AccessTest(loctestnum, loctesterr, lst1, true, 0, 3.3);
    AccessTest(loctestnum, loctesterr, lst1, true, 1, 2.2);

    // Clear e test su lista vuota
    ClearTest(loctestnum, loctesterr, lst1);
    EmptyTest(loctestnum, loctesterr, lst1, true);
    SizeTest(loctestnum, loctesterr, lst1, 0);

    // Eccezioni su lista vuota
    RemoveFromFront(loctestnum, loctesterr, lst1, false);
    BackTest(loctestnum, loctesterr, lst1, false, 0.0);

  } catch (...) {
    loctestnum++; loctesterr++;
    std::cout << "\nUnmanaged error!" << std::endl;
  }

  std::cout << "End of List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void stestListString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  std::cout << std::endl << "Begin of List<string> Test:" << std::endl;
  try {
    lasd::List<std::string> lst1, lst2;

    // Test iniziale
    EmptyTest(loctestnum, loctesterr, lst1, true);
    SizeTest(loctestnum, loctesterr, lst1, 0);

    // Inserimento in testa
    InsertAtFront(loctestnum, loctesterr, lst1, true, string("world"));
    InsertAtFront(loctestnum, loctesterr, lst1, true, string("beautiful"));
    InsertAtFront(loctestnum, loctesterr, lst1, true, string("Hello")); // Lista: Hello -> beautiful -> world

    // Inserimento in coda
    InsertAtBack(loctestnum, loctesterr, lst1, true, string("!")); // Lista: Hello -> beautiful -> world -> !

    // Accesso
    FrontTest(loctestnum, loctesterr, lst1, true, string("Hello"));
    BackTest(loctestnum, loctesterr, lst1, true, string("!"));
    AccessTest(loctestnum, loctesterr, lst1, true, 1, string("beautiful"));

    // Clonazione e confronto
    lst2 = lst1;
    EqualList(loctestnum, loctesterr, lst1, lst2, true);
    NonEqualList(loctestnum, loctesterr, lst1, lst2, false);

    // Modifica lst2 per renderla diversa
    RemoveFromBack(loctestnum, loctesterr, lst2, true);
    InsertAtBack(loctestnum, loctesterr, lst2, true, string("?"));

    EqualList(loctestnum, loctesterr, lst1, lst2, false);
    NonEqualList(loctestnum, loctesterr, lst1, lst2, true);

    // Rimozione
    FrontNRemove(loctestnum, loctesterr, lst1, true, string("Hello"));
    BackNRemove(loctestnum, loctesterr, lst1, true, string("!"));

    SizeTest(loctestnum, loctesterr, lst1, 2);
    AccessTest(loctestnum, loctesterr, lst1, true, 0, string("beautiful"));
    AccessTest(loctestnum, loctesterr, lst1, true, 1, string("world"));

    // Clear e test su lista vuota
    ClearTest(loctestnum, loctesterr, lst1);
    EmptyTest(loctestnum, loctesterr, lst1, true);
    SizeTest(loctestnum, loctesterr, lst1, 0);

    // Eccezioni su lista vuota
    RemoveFromFront(loctestnum, loctesterr, lst1, false);
    BackTest(loctestnum, loctesterr, lst1, false, string(""));

  } catch (...) {
    loctestnum++; loctesterr++;
    std::cout << "\nUnmanaged error!" << std::endl;
  }

  std::cout << "End of List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testSimpleExercise1A(unsigned int & testCount, unsigned int & errorCount) {
  std::cout << std::endl << "Begin of TEST EXERCISE A:" << std::endl;


  stestVectorEqualNotEqual(testCount, errorCount);
  stestVectorAccessResizeClear(testCount, errorCount);
  stestVectorCopyMove(testCount, errorCount);
  stestVectorAccessOutOfRange(testCount, errorCount);
  stestVectorInt(testCount, errorCount);
  stestVectorDouble(testCount, errorCount);
  stestVectorString(testCount, errorCount);
  stestListInt(testCount, errorCount);
  stestListDouble(testCount, errorCount);
  stestListString(testCount, errorCount);

  std::cout << std::endl << "End of TEST EXERCISE B!" << std::endl;
  std::cout << "Test eseguiti: " << testCount << std::endl;
  std::cout << "Errori riscontrati: " << errorCount << std::endl;
}








