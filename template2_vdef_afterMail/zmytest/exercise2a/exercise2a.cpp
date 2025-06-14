#include <iostream>
#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"

#include "../heap/heap.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void TestHeapInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Heap<int> Test:" << endl;
    try {

    // Test 1: Basic construction and heap property verification
    cout << "--- Test 1: Basic Construction ---" << endl;
    lasd::Vector<int> vec(14);
    SetAt(loctestnum, loctesterr, vec, true, 0, 20);
    SetAt(loctestnum, loctesterr, vec, true, 1, 15);
    SetAt(loctestnum, loctesterr, vec, true, 2, 18);
    SetAt(loctestnum, loctesterr, vec, true, 3, 10);
    SetAt(loctestnum, loctesterr, vec, true, 4, 12);
    SetAt(loctestnum, loctesterr, vec, true, 5, 14);
    SetAt(loctestnum, loctesterr, vec, true, 6, 17);
    SetAt(loctestnum, loctesterr, vec, true, 7, 5);
    SetAt(loctestnum, loctesterr, vec, true, 8, 8);
    SetAt(loctestnum, loctesterr, vec, true, 9, 11);
    SetAt(loctestnum, loctesterr, vec, true, 10, 9);
    SetAt(loctestnum, loctesterr, vec, true, 11, 6);
    SetAt(loctestnum, loctesterr, vec, true, 12, 13);
    SetAt(loctestnum, loctesterr, vec, true, 13, 7);

    lasd::HeapVec<int> heap1(vec);

    // Verify heap properties

    IsHeap(loctestnum, loctesterr, heap1, true);
    Empty(loctestnum, loctesterr, heap1, false);
    Size(loctestnum, loctesterr, heap1, true, 14);

    // Test front and back access
    GetFront(loctestnum, loctesterr, heap1, true, 20); // Max element should be at front
    GetBack(loctestnum, loctesterr, heap1, true, 7);   // Last element

    // Test random access
    GetAt(loctestnum, loctesterr, heap1, true, 0, 20);
    GetAt(loctestnum, loctesterr, heap1, true, 1, 15);
    GetAt(loctestnum, loctesterr, heap1, true, 2, 18);

    // Test traversal methods
    cout << "Traverse: ";
    Traverse(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);
    cout << "TraversePreOrder: ";
    TraversePreOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);
    cout << "TraversePostOrder: ";
    TraversePostOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);

    // Test 2: Edge cases - Empty heap
    cout << "--- Test 2: Empty Heap ---" << endl;
    lasd::HeapVec<int> emptyHeap;
    Empty(loctestnum, loctesterr, emptyHeap, true);
    Size(loctestnum, loctesterr, emptyHeap, true, 0);
    IsHeap(loctestnum, loctesterr, emptyHeap, true); // Empty heap is valid

    // Test accessing empty heap (should throw exceptions)
    GetFront(loctestnum, loctesterr, emptyHeap, false, 0);
    GetBack(loctestnum, loctesterr, emptyHeap, false, 0);
    GetAt(loctestnum, loctesterr, emptyHeap, false, 0, 0);

    // Test 3: Single element heap
    cout << "--- Test 3: Single Element Heap ---" << endl;
    lasd::Vector<int> singleVec(1);
    SetAt(loctestnum, loctesterr, singleVec, true, 0, 42);
    lasd::HeapVec<int> singleHeap(singleVec);

    Empty(loctestnum, loctesterr, singleHeap, false);
    Size(loctestnum, loctesterr, singleHeap, true, 1);
    IsHeap(loctestnum, loctesterr, singleHeap, true);
    GetFront(loctestnum, loctesterr, singleHeap, true, 42);
    GetBack(loctestnum, loctesterr, singleHeap, true, 42);
    GetAt(loctestnum, loctesterr, singleHeap, true, 0, 42);

    // Test 4: Already sorted heap (descending order)
    cout << "--- Test 4: Pre-sorted Heap ---" << endl;
    lasd::Vector<int> sortedVec(14);
    for(int i = 0; i < 14; ++i) {
        SetAt(loctestnum, loctesterr, sortedVec, true, i, 13 - i);
    }

    lasd::HeapVec<int> sortedHeap(sortedVec);
    IsHeap(loctestnum, loctesterr, sortedHeap, true);
    GetFront(loctestnum, loctesterr, sortedHeap, true, 13);

    // Test 5: Copy and Move Constructors
    cout << "--- Test 5: Copy and Move Operations ---" << endl;
    lasd::HeapVec<int> heap2(heap1); // Copy constructor
    EqualLinear(loctestnum, loctesterr, heap1, heap2, true);
    NonEqualLinear(loctestnum, loctesterr, heap1, heap2, false);

    lasd::HeapVec<int> heap3(std::move(heap2)); // Move constructor
    EqualLinear(loctestnum, loctesterr, heap1, heap3, true);
    EqualLinear(loctestnum, loctesterr, heap1, heap2, false); // heap2 should be empty now
    Empty(loctestnum, loctesterr, heap2, true);
    Size(loctestnum, loctesterr, heap2, true, 0);

    // Test 6: Assignment operators
    cout << "--- Test 6: Assignment Operators ---" << endl;
    heap2 = heap3; // Copy assignment
    EqualLinear(loctestnum, loctesterr, heap2, heap3, true);
    Empty(loctestnum, loctesterr, heap2, false);

    lasd::HeapVec<int> heap4;
    heap4 = std::move(heap2); // Move assignment
    EqualLinear(loctestnum, loctesterr, heap3, heap4, true);
    Empty(loctestnum, loctesterr, heap2, true);

    // Test 7: Heap Sort functionality
    cout << "--- Test 7: HeapSort ---" << endl;
    lasd::HeapVec<int> heapToSort(heap1);
    IsHeap(loctestnum, loctesterr, heapToSort, true);

    heapToSort.Sort();
    IsHeap(loctestnum, loctesterr, heapToSort, false); // After sort, it's no longer a heap

    // Verify sorted order
    IsHeapSorted(loctestnum,loctesterr,heapToSort,true);

    // Test 8: Re-heapify after sort
    cout << "--- Test 8: Re-heapify ---" << endl;
    heapToSort.Heapify();
    IsHeap(loctestnum, loctesterr, heapToSort, true);

    // Test 9: Fold operations
    cout << "--- Test 9: Fold Operations ---" << endl;
    FoldPreOrder(loctestnum, loctesterr, heap1, true, &FoldAdd<int>, 0, 165);
    FoldPostOrder(loctestnum, loctesterr, heap1, true, &FoldAdd<int>, 0, 165);

    // Test with multiplication
    FoldPreOrder(loctestnum, loctesterr, singleHeap, true, &FoldMultiply<int>, 1, 42);
    FoldPostOrder(loctestnum, loctesterr, singleHeap, true, &FoldMultiply<int>, 1, 42);

    // Test 10: Map operations and heap property preservation
    cout << "--- Test 10: Map Operations ---" << endl;
    lasd::HeapVec<int> heapForMap(heap1);

    // Map operation that preserves order
    MapPreOrder(loctestnum, loctesterr, heapForMap, true, [](int& x) { x += 1; });
    heapForMap.Heapify();
    IsHeap(loctestnum, loctesterr, heapForMap, true); 
    GetFront(loctestnum, loctesterr, heapForMap, true, 21); // Max should be 20+1=21

    // Map operation that destroys heap property
    MapPostOrder(loctestnum, loctesterr, heapForMap, true, &MapNegateIfPositive<int>);
    IsHeap(loctestnum, loctesterr, heapForMap, false); // Should no longer be heap

    // Restore heap property
    heapForMap.Heapify();
    IsHeap(loctestnum, loctesterr, heapForMap, true);

    // Test 11: Boundary conditions
    cout << "--- Test 11: Boundary Conditions ---" << endl;
    GetAt(loctestnum, loctesterr, heap1, false, 100, 0); // Out of bounds
    GetAt(loctestnum, loctesterr, heap1, false, -1, 0);  // Negative index

    // Test setting values
    SetAt(loctestnum, loctesterr, heap1, true, 0, 1);
    GetAt(loctestnum, loctesterr, heap1, true, 0, 1);
    IsHeap(loctestnum, loctesterr, heap1, false); // Heap property violated

    heap1.Heapify(); // Restore heap
    IsHeap(loctestnum, loctesterr, heap1, true);

    // Test 12: Large dataset performance
    cout << "--- Test 12: Large Dataset ---" << endl;
    lasd::Vector<int> largeVec(30);
    for(uint i = 0; i < 30; ++i) {
        SetAt(loctestnum, loctesterr, largeVec, true, i, rand() % 10000);
    }

    lasd::HeapVec<int> largeHeap(largeVec);
    IsHeap(loctestnum, loctesterr, largeHeap, true);
    Size(loctestnum, loctesterr, largeHeap, true, 30);

    largeHeap.Sort();
    IsHeap(loctestnum, loctesterr, largeHeap, false);

    // Verify large heap is sorted

    IsHeapSorted(loctestnum, loctesterr, largeHeap, true);

    // Test 13: Duplicate elements
    cout << "--- Test 13: Duplicate Elements ---" << endl;
    lasd::Vector<int> dupVec(6);
    SetAt(loctestnum, loctesterr, dupVec, true, 0, 5);
    SetAt(loctestnum, loctesterr, dupVec, true, 1, 5);
    SetAt(loctestnum, loctesterr, dupVec, true, 2, 3);
    SetAt(loctestnum, loctesterr, dupVec, true, 3, 3);
    SetAt(loctestnum, loctesterr, dupVec, true, 4, 1);
    SetAt(loctestnum, loctesterr, dupVec, true, 5, 1);

    lasd::HeapVec<int> dupHeap(dupVec);
    IsHeap(loctestnum, loctesterr, dupHeap, true);
    GetFront(loctestnum, loctesterr, dupHeap, true, 5);

    dupHeap.Sort();
    GetAt(loctestnum, loctesterr, dupHeap, true, 0, 1);
    GetAt(loctestnum, loctesterr, dupHeap, true, 5, 5);

    // All elements are = 
    cout << "--- Test: All Equal Elements ---" << endl;
    lasd::Vector<int> equalVec(10);
    for(uint i = 0; i < 10; ++i)
        SetAt(loctestnum, loctesterr, equalVec, true, i, 42);
    lasd::HeapVec<int> equalHeap(equalVec);
    IsHeap(loctestnum, loctesterr, equalHeap, true);
    GetFront(loctestnum, loctesterr, equalHeap, true, 42);

    // indexes out of range
    cout << "--- Test: Out-of-Bounds Access ---" << endl;
    GetAt(loctestnum, loctesterr, equalHeap, false, 10, 0);
    GetAt(loctestnum, loctesterr, equalHeap, false, 1000, 0);
    
    // Duplicates
    cout << "--- Test: Multiple Heapify and Sort ---" << endl;
    lasd::HeapVec<int> repeatHeap(equalHeap);
    Traverse(loctestnum, loctesterr, repeatHeap, true, &TraversePrint<int>);

    for(int i = 0; i < 5; ++i) {
        Traverse(loctestnum, loctesterr, repeatHeap, true, &TraversePrint<int>);
        IsHeap(loctestnum, loctesterr, repeatHeap, true); 
        repeatHeap.Heapify();
        Traverse(loctestnum, loctesterr, repeatHeap, true, &TraversePrint<int>);
        IsHeap(loctestnum, loctesterr, repeatHeap, true); 
        repeatHeap.Sort();
    }

        // Test 14: Vector-like Interface (deep checks)
    cout << "--- Test 14: Vector Interface and Edge Cases ---" << endl;

    lasd::HeapVec<int> vectorHeap(heap1); // copia heap1 originale

    // --- operator[] Read/Write Access ---
    try {
        int& ref = vectorHeap[3];
        loctestnum++;
        int old = ref;
        ref = 123456;
        if (vectorHeap[3] == 123456) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: operator[] failed to modify element!" << endl;
        }
        ref = old; // restore
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: operator[] threw unexpectedly!" << endl;
    }

    // --- operator[] Out of Bounds ---
    try {
        int x = vectorHeap[1000]; (void)x;
        loctestnum++; loctesterr++;
        cout << "Error: operator[] did not throw on out-of-bounds access!" << endl;
    } catch (...) {
        loctestnum++; // comportamento corretto
    }

    // --- operator[] Const version ---
    try {
        const lasd::HeapVec<int>& constHeap = vectorHeap;
        if (constHeap[1] == heap1[1]) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: operator[] const failed to return correct value!" << endl;
        }
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: operator[] const threw unexpectedly!" << endl;
    }

    // --- Front() const (solo lettura) ---
    try {
        const lasd::HeapVec<int>& constHeap = vectorHeap;
        loctestnum++;
        if (constHeap.Front() == heap1[0]) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Front() const failed to return correct value!" << endl;
        }
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Front() const threw unexpectedly!" << endl;
    }

    // --- Front() mutable (modifica) ---
    try {
        int& frontRef = vectorHeap.Front();
        int originalFront = frontRef;
        frontRef = -999;
        if (vectorHeap[0] == -999) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Front() did not return a reference!" << endl;
        }
        frontRef = originalFront; // restore
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Front() threw unexpectedly!" << endl;
    }

    // --- Back() const (solo lettura) ---
    try {
        const lasd::HeapVec<int>& constHeap = vectorHeap;
        loctestnum++;
        if (constHeap.Back() == heap1[heap1.Size() - 1]) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Back() const failed to return correct value!" << endl;
        }
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Back() const threw unexpectedly!" << endl;
    }

    // --- Back() mutable (modifica) ---
    try {
        int& backRef = vectorHeap.Back();
        int originalBack = backRef;
        backRef += 100;
        if (vectorHeap[vectorHeap.Size() - 1] == originalBack + 100) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Back() did not return a reference!" << endl;
        }
        backRef = originalBack; // restore
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Back() threw unexpectedly!" << endl;
    }

    // --- Clear() Empties Heap Completely ---
    vectorHeap.Clear();
    Empty(loctestnum, loctesterr, vectorHeap, true);
    Size(loctestnum, loctesterr, vectorHeap, true, 0);
    IsHeap(loctestnum, loctesterr, vectorHeap, true);

    // --- Access After Clear() Should Throw ---
    try {
        int val = vectorHeap.Front(); (void)val;
        loctestnum++; loctesterr++;
        cout << "Error: Front() did not throw after Clear()!" << endl;
    } catch (...) {
        loctestnum++; // Correct
    }

    try {
        int val = vectorHeap.Back(); (void)val;
        loctestnum++; loctesterr++;
        cout << "Error: Back() did not throw after Clear()!" << endl;
    } catch (...) {
        loctestnum++; // Correct
    }

    try {
        int val = vectorHeap[0]; (void)val;
        loctestnum++; loctesterr++;
        cout << "Error: operator[] did not throw after Clear()!" << endl;
    } catch (...) {
        loctestnum++; // Correct
    }   
        
        // --- Deep Test: Clear() on HeapVec<int> ---
    cout << "--- Deep Test: Clear() on HeapVec<int> ---" << endl;

    lasd::Vector<int> vecClearInt(4);
    vecClearInt[0] = 42;
    vecClearInt[1] = 7;
    vecClearInt[2] = 100;
    vecClearInt[3] = 3;

    lasd::HeapVec<int> hvInt(vecClearInt);

    cout << "[Before Clear()]" << endl;
    cout << "Size: " << hvInt.Size() << endl;
    cout << "Empty: " << (hvInt.Empty() ? "true" : "false") << endl;
    cout << "IsHeap: " << (hvInt.IsHeap() ? "true" : "false") << endl;

    bool valuesOkInt = true;
    for (ulong i = 0; i < hvInt.Size(); ++i) {
        try {
            loctestnum++;
            int val = hvInt[i];
            cout << "hvInt[" << i << "] = " << val << endl;
        } catch (...) {
            loctestnum++; loctesterr++;
            cout << "Error: operator[] threw unexpectedly on valid index (int)!" << endl;
            valuesOkInt = false;
        }
    }
    if (valuesOkInt) {
        cout << "OK: operator[] access succeeded before Clear() (int)." << endl;
    }

    hvInt.Clear();

    cout << "\n[After Clear()]" << endl;

    loctestnum++;
    if (hvInt.Size() != 0) {
        loctesterr++;
        cout << "Error: Size after Clear() is not zero (int): " << hvInt.Size() << endl;
    } else {
        cout << "OK: Size is zero after Clear() (int)." << endl;
    }

    loctestnum++;
    if (!hvInt.Empty()) {
        loctesterr++;
        cout << "Error: Empty() returned false after Clear() (int)." << endl;
    } else {
        cout << "OK: Empty() returned true after Clear() (int)." << endl;
    }

    loctestnum++;
    if (!hvInt.IsHeap()) {
        loctesterr++;
        cout << "Error: IsHeap() returned false on empty heap (int)!" << endl;
    } else {
        cout << "OK: IsHeap() returned true after Clear() (int)." << endl;
    }

    try {
        loctestnum++;
        int test = hvInt[0]; // Should throw
        loctesterr++;
        cout << "Error: operator[] did not throw after Clear() (int); returned: " << test << endl;
    } catch (...) {
        cout << "OK: operator[] threw exception as expected after Clear() (int)." << endl;
    }

    cout << "\n[Reusability Test After Clear() (int)]" << endl;

    lasd::Vector<int> newvecInt(2);
    newvecInt[0] = 55;
    newvecInt[1] = 66;

    hvInt = lasd::HeapVec<int>(newvecInt); // Move assignment

    loctestnum++;
    if (hvInt.Size() == 2 && hvInt.IsHeap()) {
        cout << "OK: HeapVec<int> reused successfully after Clear()." << endl;
        cout << "hvInt[0] = " << hvInt[0] << ", hvInt[1] = " << hvInt[1] << endl;
    } else {
        loctesterr++;
        cout << "Error: Reuse after Clear() failed (int). Size: " << hvInt.Size()
            << ", IsHeap: " << hvInt.IsHeap() << endl;
    }


    cout << "--- Test Exists() --- ";

    lasd::Vector<int> initialValues(7);

    // Manually assign values using operator[]
    initialValues[0] = 20;
    initialValues[1] = 15;
    initialValues[2] = 10;
    initialValues[3] = 7;
    initialValues[4] = 9;
    initialValues[5] = 5;
    initialValues[6] = 6;

    lasd::HeapVec<int> originalHeap(initialValues);

    // Create a copy of the heap with a non-trivial name
    lasd::HeapVec<int> copiedHeap(originalHeap);

    std::cout << "--- Testing Exists method on copiedHeap ---" << std::endl;

    // Test for values that should exist in the heap
    Exists(loctestnum, loctesterr, copiedHeap, true, 20);
    Exists(loctestnum, loctesterr, copiedHeap, true, 15);
    Exists(loctestnum, loctesterr, copiedHeap, true, 7);

    // Test for values that should NOT exist in the heap
    Exists(loctestnum, loctesterr, copiedHeap, false, 100);
    Exists(loctestnum, loctesterr, copiedHeap, false, 0);

    std::cout << "Exists method test cases passed: " << loctestnum - loctesterr << std::endl;
    std::cout << "Exists method test cases failed: " << loctesterr << std::endl;

    }
    catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
    }

    cout << "End of Heap<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void TestHeapDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "== Begin Heap<double> Test ==" << endl;
  
    try {
      // Test 1: Inserimento e costruzione base
      cout << "-- Test 1: Base Construction --" << endl;
      lasd::Vector<double> vec(10);
      const std::array<double, 10> vals = {4.5, 3.25, 1.125, 0.0, 2.25, 5.5, 0.0, 8.25, 10.5, 11.5};
  
      for (size_t i = 0; i < vals.size(); ++i)
        SetAt(loctestnum, loctesterr, vec, true, i, vals[i]);
  
      lasd::HeapVec<double> heap(vec);
      IsHeap(loctestnum, loctesterr, heap, true);
      Size(loctestnum, loctesterr, heap, true, 10);
      GetFront(loctestnum, loctesterr, heap, true, 11.5);
  
      // Test 2: Precisione
      cout << "-- Test 2: Floating Point Precision --" << endl;
      lasd::Vector<double> precisionVec(4);
      precisionVec[0] = 1.0000001;
      precisionVec[1] = 1.0000000;
      precisionVec[2] = 0.9999999;
      precisionVec[3] = 0.9999998;
  
      lasd::HeapVec<double> precisionHeap(precisionVec);
      IsHeap(loctestnum, loctesterr, precisionHeap, true);
      GetFront(loctestnum, loctesterr, precisionHeap, true, 1.0000001);
  
      // Test 3: Valori speciali
      cout << "-- Test 3: Special Double Values --" << endl;
      lasd::Vector<double> specialVec(5);
      specialVec[0] = -5.5;
      specialVec[1] = 0.0;
      specialVec[2] = 3.14159;
      specialVec[3] = -0.0;
      specialVec[4] = 2.71828;
  
      lasd::HeapVec<double> specialHeap(specialVec);
      IsHeap(loctestnum, loctesterr, specialHeap, true);
      GetFront(loctestnum, loctesterr, specialHeap, true, 3.14159);
  
      // Test 4: Costruttore di copia
      cout << "-- Test 4: Copy Constructor --" << endl;
      lasd::HeapVec<double> heapCopy(heap);
      EqualLinear(loctestnum, loctesterr, heap, heapCopy, true);
  
      // Test 5: Ordinamento e traversali
      cout << "-- Test 5: Sort and Traversal --" << endl;
      cout << "Pre-sort traversal: ";
      TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
  
      heap.Sort();
      IsHeap(loctestnum, loctesterr, heap, false);
  
      cout << "Post-sort traversal: ";
      TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
      TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
  
      // Test 6: Ricostruzione heap
      cout << "-- Test 6: Re-heapify --" << endl;
      heap.Heapify();
      IsHeap(loctestnum, loctesterr, heap, true);
      cout << "After heapify traversal: ";
      TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
  
      // Test 7: Operazioni di mappatura
      cout << "-- Test 7: Map Operation --" << endl;
      MapPreOrder(loctestnum, loctesterr, heap, true, [](double & x) { x *= 2.0; });
      GetFront(loctestnum, loctesterr, heap, true, 23.0);
      IsHeap(loctestnum, loctesterr, heap, true);
  
      // Test 8: Fold
      cout << "-- Test 8: Fold Operation --" << endl;
      double expectedSum = 93.75;
    FoldPreOrder(loctestnum, loctesterr, heap, true, &FoldAdd<double>, 0.0, expectedSum);
    FoldPostOrder(loctestnum, loctesterr, heap, true, &FoldAdd<double>, 0.0, expectedSum);

  
      // Test: valori doppi speciali come NaN e infiniti
      cout << "-- Extra Test: NaN / Inf Handling --" << endl;
      lasd::Vector<double> specialVec2(5);
      specialVec2[0] = std::numeric_limits<double>::quiet_NaN();
      specialVec2[1] = std::numeric_limits<double>::infinity();
      specialVec2[2] = -std::numeric_limits<double>::infinity();
      specialVec2[3] = 1.0;
      specialVec2[4] = 0.0;
  
      lasd::HeapVec<double> specialHeap2(specialVec2);
      bool isHeap = specialHeap2.IsHeap();
      cout << "IsHeap with special values: " << (isHeap ? "True" : "False") << endl;
  
      lasd::Vector<double> initialVec(5);
      initialVec[0] = 64.0;
      initialVec[1] = 32.0;
      initialVec[2] = 16.0;
      initialVec[3] = 8.0;
      initialVec[4] = 4.0;

      lasd::Vector<double> foldResult(3);
      foldResult[0]= 62.0;
      foldResult[1] = 31.0;
      foldResult[2] = 15.5;
  
      cout << "-- Extra Test: Repeated Map+Fold --" << endl;
        lasd::HeapVec<double> repeatHeap(initialVec);

        for (int i = 0; i < 3; ++i) {
            MapPreOrder(loctestnum, loctesterr, repeatHeap, true, [](double & x) { x /= 2.0; });
            FoldPreOrder(loctestnum, loctesterr, repeatHeap, true, &FoldAdd<double>, 0.0, foldResult[i]);
            cout << "Fold sum after iteration " << i << ": " << foldResult[i] << endl;
            repeatHeap.Heapify();
            IsHeap(loctestnum, loctesterr, repeatHeap, true);
        }

        cout << "--- Test 14b (Read-Only + Mutable): Vector Interface (HeapVec<double>) ---" << endl;

        lasd::Vector<double> vecRO(5);
        vecRO[0] = 42.0;
        vecRO[1] = 3.14;
        vecRO[2] = 1.618;
        vecRO[3] = 2.718;
        vecRO[4] = 0.577;
        
        lasd::HeapVec<double> doubleHeap(vecRO); 
        
        // const read-only  operator[]
        for (ulong i = 0; i < doubleHeap.Size(); ++i) {
            try {
                loctestnum++;
                double val = doubleHeap[i]; // accesso read-only
                cout << "hv[" << i << "] = " << val << endl;
            } catch (...) {
                loctestnum++; loctesterr++;
                cout << "Errore: operator[] ha lanciato un'eccezione in lettura!" << endl;
            }
        }
        
        // operator[] Out of Bounds
        try {
            double x = doubleHeap[999]; (void)x;
            loctestnum++; loctesterr++;
            cout << "Error: operator[] did not throw on out-of-bounds (double)!" << endl;
        } catch (...) {
            loctestnum++;
        }
        
        // Const access operator[]
        try {
            const lasd::HeapVec<double>& constHeap = doubleHeap;
            if (constHeap[1] == 3.14) {
                loctestnum++;
            } else {
                loctestnum++; loctesterr++;
                cout << "Error: operator[] const failed (double)!" << endl;
            }
        } catch (...) {
            loctestnum++; loctesterr++;
            cout << "Error: operator[] const threw (double)!" << endl;
        }
        
        // Front() const 
        try {
            const lasd::HeapVec<double>& constHeap = doubleHeap;
            loctestnum++;
            if (constHeap.Front() == 42.0) {
                loctestnum++;
            } else {
                loctestnum++; loctesterr++;
                cout << "Error: Front() const failed (double)!" << endl;
            }
        } catch (...) {
            loctestnum++; loctesterr++;
            cout << "Error: Front() const threw (double)!" << endl;
        }
        
        // Front() mutable 
        try {
            double& f = doubleHeap.Front();
            double orig = f;
            f += 100;
            if (doubleHeap[0] == orig + 100) {
                loctestnum++;
            } else {
                loctestnum++; loctesterr++;
                cout << "Error: Front() ref failed (double)!" << endl;
            }
            f = orig;
        } catch (...) {
            loctestnum++; loctesterr++;
            cout << "Error: Front() threw (double)!" << endl;
        }
        
        // Back() const 
        try {
            const lasd::HeapVec<double>& constHeap = doubleHeap;
            loctestnum++;
            if (constHeap.Back() == 0.577) {
                loctestnum++;
            } else {
                loctestnum++; loctesterr++;
                cout << "Error: Back() const failed (double)!" << endl;
            }
        } catch (...) {
            loctestnum++; loctesterr++;
            cout << "Error: Back() const threw (double)!" << endl;
        }
        
        // Back() mutable 
        try {
            double& b = doubleHeap.Back();
            double orig = b;
            b -= 50;
            if (doubleHeap[doubleHeap.Size() - 1] == orig - 50) {
                loctestnum++;
            } else {
                loctestnum++; loctesterr++;
                cout << "Error: Back() ref failed (double)!" << endl;
            }
            b = orig;
        } catch (...) {
            loctestnum++; loctesterr++;
            cout << "Error: Back() threw (double)!" << endl;
        }
        
        // Clear + post-clear checks
        doubleHeap.Clear();
        Empty(loctestnum, loctesterr, doubleHeap, true);
        Size(loctestnum, loctesterr, doubleHeap, true, 0);
        IsHeap(loctestnum, loctesterr, doubleHeap, true);

        try { doubleHeap.Front(); loctestnum++; loctesterr++; } catch (...) { loctestnum++; }
        try { doubleHeap.Back(); loctestnum++; loctesterr++; } catch (...) { loctestnum++; }
        try { doubleHeap[0]; loctestnum++; loctesterr++; } catch (...) { loctestnum++; }

        cout << "--- Deep Test: Clear() on HeapVec<double> ---" << endl;

        lasd::Vector<double> vecClear(4);
        vecClear[0] = 9.81;
        vecClear[1] = 3.14;
        vecClear[2] = 1.618;
        vecClear[3] = 2.718;

        lasd::HeapVec<double> hv(vecClear);

        cout << "[Before Clear()]" << endl;
        cout << "Size: " << hv.Size() << endl;
        cout << "Empty: " << (hv.Empty() ? "true" : "false") << endl;
        cout << "IsHeap: " << (hv.IsHeap() ? "true" : "false") << endl;

        bool valuesOk = true;
        for (ulong i = 0; i < hv.Size(); ++i) {
            try {
                loctestnum++;
                double val = hv[i];
                cout << "hv[" << i << "] = " << val << endl;
            } catch (...) {
                loctestnum++; loctesterr++;
                cout << "Error: operator[] threw unexpectedly on valid index!" << endl;
                valuesOk = false;
            }
        }
        if (valuesOk) {
            cout << "OK: operator[] access succeeded before Clear()." << endl;
        }

        hv.Clear();

        cout << "\n[After Clear()]" << endl;

        loctestnum++;
        if (hv.Size() != 0) {
            loctesterr++;
            cout << "Error: Size after Clear() is not zero (" << hv.Size() << ")" << endl;
        } else {
            cout << "OK: Size is zero after Clear()." << endl;
        }

        loctestnum++;
        if (!hv.Empty()) {
            loctesterr++;
            cout << "Error: Empty() returned false after Clear()." << endl;
        } else {
            cout << "OK: Empty() returned true after Clear()." << endl;
        }

        loctestnum++;
        if (!hv.IsHeap()) {
            loctesterr++;
            cout << "Error: IsHeap() returned false on an empty heap!" << endl;
        } else {
            cout << "OK: IsHeap() returned true after Clear()." << endl;
        }

        try {
            loctestnum++;
            double test = hv[0]; // Should throw
            loctesterr++;
            cout << "Error: operator[] did not throw after Clear(); returned: " << test << endl;
        } catch (...) {
            cout << "OK: operator[] threw exception as expected after Clear()." << endl;
        }

        cout << "\n[Reusability Test After Clear()]" << endl;

        lasd::Vector<double> newvec(2);
        newvec[0] = 7.77;
        newvec[1] = 8.88;

        hv = lasd::HeapVec<double>(newvec); // Move assignment

        loctestnum++;
        if (hv.Size() == 2 && hv.IsHeap()) {
            cout << "OK: HeapVec reused successfully after Clear()." << endl;
            cout << "hv[0] = " << hv[0] << ", hv[1] = " << hv[1] << endl;
        } else {
            loctesterr++;
            cout << "Error: Reuse after Clear() failed. Size: " << hv.Size()
                << ", IsHeap: " << hv.IsHeap() << endl;
        }


            // Create a vector with size 5 for doubles
        lasd::Vector<double> initialValues(5);

        // Manually assign values using operator[]
        initialValues[0] = 3.14;
        initialValues[1] = 2.71;
        initialValues[2] = 1.41;
        initialValues[3] = 0.577;
        initialValues[4] = 1.618;

        // Create the original heap from the vector
        lasd::HeapVec<double> originalHeap(initialValues);

        // Create a copy of the heap with a non-trivial name
        lasd::HeapVec<double> copiedHeap(originalHeap);

        std::cout << "--- Testing Exists method on copiedHeap (double) ---" << std::endl;

        // Test for values that should exist in the heap
        Exists(loctestnum, loctesterr, copiedHeap, true, 3.14);
        Exists(loctestnum, loctesterr, copiedHeap, true, 1.618);

        // Test for values that should NOT exist in the heap
        Exists(loctestnum, loctesterr, copiedHeap, false, 42.0);
        Exists(loctestnum, loctesterr, copiedHeap, false, -1.0);

        std::cout << "Exists method test cases passed: " << loctestnum - loctesterr << std::endl;
        std::cout << "Exists method test cases failed: " << loctesterr << std::endl;
    } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error!" << endl;
    }

    cout << "End of Heap<double> Test! (Errors/Tests: "
        << loctesterr << "/" << loctestnum << ")" << endl;

    testnum += loctestnum;
    testerr += loctesterr;

  }

  
void TestHeapString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Heap<string> Test:" << endl;
    try {

    // Test 1: Basic string heap construction
    cout << "--- Test 1: Basic String Heap ---" << endl;
    lasd::Vector<string> vec(10);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("Elephant"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("Dog"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("Bear"));
    SetAt(loctestnum, loctesterr, vec, true, 3, string("Apple"));
    SetAt(loctestnum, loctesterr, vec, true, 4, string("Cat"));
    SetAt(loctestnum, loctesterr, vec, true, 5, string("Fish"));
    SetAt(loctestnum, loctesterr, vec, true, 6, string("Ant"));
    SetAt(loctestnum, loctesterr, vec, true, 7, string("Iguana"));
    SetAt(loctestnum, loctesterr, vec, true, 8, string("Kangaroo"));
    SetAt(loctestnum, loctesterr, vec, true, 9, string("Lion"));

    lasd::HeapVec<string> heap(vec);
    IsHeap(loctestnum, loctesterr, heap, true);
    Size(loctestnum, loctesterr, heap, true, 10);

    // In lexicographic order, "Lion" should be the maximum
    GetFront(loctestnum, loctesterr, heap, true, string("Lion"));

    // Test 2: Empty strings and edge cases
    cout << "--- Test 2: Edge Cases ---" << endl;
    lasd::Vector<string> edgeVec(5);
    SetAt(loctestnum, loctesterr, edgeVec, true, 0, string(""));
    SetAt(loctestnum, loctesterr, edgeVec, true, 1, string("a"));
    SetAt(loctestnum, loctesterr, edgeVec, true, 2, string("A"));
    SetAt(loctestnum, loctesterr, edgeVec, true, 3, string("aa"));
    SetAt(loctestnum, loctesterr, edgeVec, true, 4, string("Z"));

    lasd::HeapVec<string> edgeHeap(edgeVec);
    IsHeap(loctestnum, loctesterr, edgeHeap, true);
    GetFront(loctestnum, loctesterr, edgeHeap, true, string("aa")); // Lexicographically largest

    // Test 3: Case sensitivity
    cout << "--- Test 3: Case Sensitivity ---" << endl;
    lasd::Vector<string> caseVec(4);
    SetAt(loctestnum, loctesterr, caseVec, true, 0, string("apple"));
    SetAt(loctestnum, loctesterr, caseVec, true, 1, string("Apple"));
    SetAt(loctestnum, loctesterr, caseVec, true, 2, string("APPLE"));
    SetAt(loctestnum, loctesterr, caseVec, true, 3, string("aPpLe"));

    lasd::HeapVec<string> caseHeap(caseVec);
    IsHeap(loctestnum, loctesterr, caseHeap, true);
    GetFront(loctestnum, loctesterr, caseHeap, true, string("apple")); // 'a' > 'A' in ASCII

    // Test 4: Copy operations
    cout << "--- Test 4: Copy Operations ---" << endl;
    lasd::HeapVec<string> heap2(heap);
    EqualLinear(loctestnum, loctesterr, heap, heap2, true);

    lasd::HeapVec<string> heap3(std::move(heap2));
    EqualLinear(loctestnum, loctesterr, heap, heap3, true);
    Empty(loctestnum, loctesterr, heap2, true);

    // Test 5: String manipulation via Map
    cout << "--- Test 5: String Manipulation ---" << endl;
    cout << "Pre-map traversal: ";
    TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

    MapPreOrder(loctestnum, loctesterr, heap, true, [](string & str) { 
        MapStringAppend(str, string("*")); 
    });

    cout << "Post-map traversal: ";
    TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

    // Test heap property after modification
    IsHeap(loctestnum, loctesterr, heap, true); // Should still be heap since we just appended

    // Test 6: More complex string operations
    cout << "--- Test 6: Complex String Operations ---" << endl;
    MapPreOrder(loctestnum, loctesterr, heap, true, [](string & str) { 
        MapStringAppend(str, string(" ")); 
    });

    cout << "After adding spaces: ";
    TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

    // Test 7: Fold operations with strings
    cout << "--- Test 7: String Fold Operations ---" << endl;
    string expectedPostOrder = "?";
    TraversePostOrder(loctestnum, loctesterr, heap, true, [&expectedPostOrder](const string& s) {
        expectedPostOrder += s;
    });

    FoldPostOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, 
                    string("?"), expectedPostOrder);

    string expectedPreOrder = "?";
    TraversePreOrder(loctestnum, loctesterr, heap, true, [&expectedPreOrder](const string& s) {
        expectedPreOrder += s;
    });

    FoldPreOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, 
                    string("?"), expectedPreOrder);

    // Test 8: Sort functionality
    cout << "--- Test 8: String Sort ---" << endl;
    heap.Sort();
    IsHeap(loctestnum, loctesterr, heap, false);

    cout << "Sorted heap: ";
    TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

    IsHeapSorted(loctestnum, loctesterr, heap, true);

    // Test 9: Re-heapify
    cout << "--- Test 9: Re-heapify ---" << endl;
    heap.Heapify();
    IsHeap(loctestnum, loctesterr, heap, true);

    cout << "Re-heapified: ";
    TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

    // Test 10: Long strings
    cout << "--- Test 10: Long Strings ---" << endl;
    lasd::Vector<string> longVec(3);
    SetAt(loctestnum, loctesterr, longVec, true, 0, 
            string("This is a very long string to test heap behavior with lengthy text"));
    SetAt(loctestnum, loctesterr, longVec, true, 1, 
            string("Another long string that should be compared lexicographically"));
    SetAt(loctestnum, loctesterr, longVec, true, 2, 
            string("Zebra - this should be the maximum due to starting with Z"));

    lasd::HeapVec<string> longHeap(longVec);
    IsHeap(loctestnum, loctesterr, longHeap, true);
    GetFront(loctestnum, loctesterr, longHeap, true, 
                string("Zebra - this should be the maximum due to starting with Z"));

    // Test 11: Duplicate strings
    cout << "--- Test 11: Duplicate Strings ---" << endl;
    lasd::Vector<string> dupVec(6);
    SetAt(loctestnum, loctesterr, dupVec, true, 0, string("Hello"));
    SetAt(loctestnum, loctesterr, dupVec, true, 1, string("Hello"));
    SetAt(loctestnum, loctesterr, dupVec, true, 2, string("World"));
    SetAt(loctestnum, loctesterr, dupVec, true, 3, string("World"));
    SetAt(loctestnum, loctesterr, dupVec, true, 4, string("Apple"));
    SetAt(loctestnum, loctesterr, dupVec, true, 5, string("Apple"));

    lasd::HeapVec<string> dupHeap(dupVec);
    IsHeap(loctestnum, loctesterr, dupHeap, true);
    GetFront(loctestnum, loctesterr, dupHeap, true, string("World"));

    dupHeap.Sort();
    GetAt(loctestnum, loctesterr, dupHeap, true, 1, string("Apple"));
    GetAt(loctestnum, loctesterr, dupHeap, true, 2, string("Hello"));
    GetAt(loctestnum, loctesterr, dupHeap, true, 3, string("Hello"));
    GetAt(loctestnum, loctesterr, dupHeap, true, 4, string("World"));
    GetAt(loctestnum, loctesterr, dupHeap, true, 5, string("World"));

    // Test 12: Invalid index access
    cout << "--- Test 12: Invalid Index Access ---" << endl;
    GetAt(loctestnum, loctesterr, dupHeap, false, 100, string(""));
    GetAt(loctestnum, loctesterr, dupHeap, false, -1, string(""));

    // Test 13: SetAt modifies values
    cout << "--- Test 13: SetAt Impact ---" << endl;
    SetAt(loctestnum, loctesterr, dupHeap, true, 0, string("ZZZ"));
    IsHeap(loctestnum, loctesterr, dupHeap, false);
    dupHeap.Heapify();
    IsHeap(loctestnum, loctesterr, dupHeap, true);
    GetFront(loctestnum, loctesterr, dupHeap, true, string("ZZZ"));

    // Test 14: Move semantics
    cout << "--- Test 14: Move Semantics ---" << endl;
    lasd::HeapVec<string> movedHeap(std::move(dupHeap));
    Empty(loctestnum, loctesterr, dupHeap, true);
    Size(loctestnum, loctesterr, movedHeap, true, 6);

    // --- Stringhe speciali ---
    cout << "--- Test: Empty and Duplicate Strings ---" << endl;
    lasd::Vector<std::string> strVec(5);
    strVec[0] = "";
    strVec[1] = "aaa";
    strVec[2] = "bbb";  
    strVec[3] = "aaa";
    strVec[4] = "ccc";
    lasd::HeapVec<std::string> strHeap(strVec);
    IsHeap(loctestnum, loctesterr, strHeap, true);           // OK dopo heapify
    GetFront(loctestnum, loctesterr, strHeap, true, string("ccc"));  

    // --- Test con caratteri speciali ---
    cout << "--- Test: Special Characters ---" << endl;
    lasd::Vector<std::string> specialStrVec(3);
    specialStrVec[0] = "abc\n";
    specialStrVec[1] = "abc\t";
    specialStrVec[2] = "abc ";
    lasd::HeapVec<std::string> specialStrHeap(specialStrVec);
    IsHeap(loctestnum, loctesterr, specialStrHeap, true);


    // --- Ripetizioni ---
    cout << "--- Test: Multiple Heapify and Sort ---" << endl;
    lasd::HeapVec<std::string> repeatHeap(strHeap);
    for(int i = 0; i < 4; ++i) {
        repeatHeap.Heapify();
        IsHeap(loctestnum, loctesterr, repeatHeap, true);
        repeatHeap.Sort();
        IsHeap(loctestnum, loctesterr, repeatHeap, false);
    }

    // Vector Interface Deep Check
    cout << "--- Vector Interface ---" << endl;

    lasd::Vector<string> stringVecCopy(5);
    stringVecCopy[0] = "alpha";
    stringVecCopy[1] = "beta";
    stringVecCopy[2] = "gamma";
    stringVecCopy[3] = "delta";
    stringVecCopy[4] = "epsilon";
    lasd::HeapVec<std::string> stringHeap(stringVecCopy);

    try {
        loctestnum++;
        if (stringHeap.Front() == "gamma") { // "gamma" è il max lexicografico
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Front() const returned incorrect value (string)!" << endl;
        }

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Front() const threw unexpectedly (string)!" << endl;
    }

    try {
        loctestnum++;
        if (stringHeap[0] == "gamma") { // "gamma" è il max lexicografico
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: operator[] returned incorrect value (string)!" << endl;
        }

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: operator[]  threw unexpectedly (string)!" << endl;
    }


    // operator[] Out of Bounds
    try {
        std::string x = stringHeap[500]; (void)x;
        loctestnum++; loctesterr++;
        cout << "Error: operator[] did not throw on out-of-bounds (string)!" << endl;
    } catch (...) {
        loctestnum++;
    }

    //operator[] + Back
    try {
        const lasd::HeapVec<std::string>& constHeap = stringHeap;
        std::string lastElement = constHeap[constHeap.Size() - 1];  // leggi ultimo elemento
        if (constHeap.Back() == lastElement) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Back() const failed (string)! Expected: " << lastElement
                 << " Got: " << constHeap.Back() << endl;
        }
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Back() const threw (string)!" << endl;
    }    

    // Front and Back
    try {
        std::string& f = stringHeap.Front();
        std::string orig = f;
        f += "_front";
        if (stringHeap[0] == orig + "_front") {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Front() ref failed (string)!" << endl;
        }
        f = orig;
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Front() threw (string)!" << endl;
    }

    try {
        std::string& b = stringHeap.Back();
        std::string orig = b;
        b = "tail_" + b;
        if (stringHeap[stringHeap.Size() - 1] == "tail_" + orig) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Back() ref failed (string)!" << endl;
        }
        b = orig;
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Back() threw (string)!" << endl;
    }
    
    try {
        std::string& s = stringHeap[2];
        std::string orig = s;
        s = "modified";
        if (stringHeap[2] == "modified") {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: operator[] ref failed!" << endl;
        }
        s = orig;  // restore
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: operator[] threw unexpectedly!" << endl;
    }

        // --- Test Front() const (non mutable)
    try {
        const lasd::HeapVec<std::string>& constHeap = stringHeap;
        loctestnum++;
        if (constHeap.Front() == "gamma") {  
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Front() const returned incorrect value!" << endl;
        }
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Front() const threw unexpectedly!" << endl;
    }

    // --- Test Front() mutable (non const)
    try {
        std::string& frontRef = stringHeap.Front();
        std::string orig = frontRef;
        frontRef += "_mut";
        if (stringHeap[0] == orig + "_mut") {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Front() mutable reference failed!" << endl;
        }
        frontRef = orig;  // restore
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Front() mutable threw!" << endl;
    }

    // --- Test Back() const (non mutable)
    try {
        const lasd::HeapVec<std::string>& constHeap = stringHeap;
        loctestnum++;
        if (constHeap.Back() == stringHeap[stringHeap.Size() - 1]) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Back() const returned incorrect value!" << endl;
        }
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Back() const threw unexpectedly!" << endl;
    }

    // --- Test Back() mutable (non const)
    try {
        std::string& backRef = stringHeap.Back();
        std::string orig = backRef;
        backRef = "tail_" + orig;
        if (stringHeap[stringHeap.Size() - 1] == "tail_" + orig) {
            loctestnum++;
        } else {
            loctestnum++; loctesterr++;
            cout << "Error: Back() mutable reference failed!" << endl;
        }
        backRef = orig;  // restore
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "Error: Back() mutable threw!" << endl;
    }

    // Clear + post-clear checks
    stringHeap.Clear();
    Empty(loctestnum, loctesterr, stringHeap, true);
    Size(loctestnum, loctesterr, stringHeap, true, 0);
    IsHeap(loctestnum, loctesterr, stringHeap, true);

    try { stringHeap.Front(); loctestnum++; loctesterr++; } catch (...) { loctestnum++; }
    try { stringHeap.Back(); loctestnum++; loctesterr++; } catch (...) { loctestnum++; }
    try { stringHeap[0]; loctestnum++; loctesterr++; } catch (...) { loctestnum++; }
        
    // --- Deep Test: Clear() on HeapVec<string> ---
    cout << "--- Deep Test: Clear() on HeapVec<string> ---" << endl;

    lasd::Vector<std::string> vecClearStr(4);
    vecClearStr[0] = "apple";
    vecClearStr[1] = "banana";
    vecClearStr[2] = "cherry";
    vecClearStr[3] = "date";

    lasd::HeapVec<std::string> hvStr(vecClearStr);

    cout << "[Before Clear()]" << endl;
    cout << "Size: " << hvStr.Size() << endl;
    cout << "Empty: " << (hvStr.Empty() ? "true" : "false") << endl;
    cout << "IsHeap: " << (hvStr.IsHeap() ? "true" : "false") << endl;

    bool valuesOkStr = true;
    for (ulong i = 0; i < hvStr.Size(); ++i) {
        try {
            loctestnum++;
            std::string val = hvStr[i];
            cout << "hvStr[" << i << "] = " << val << endl;
        } catch (...) {
            loctestnum++; loctesterr++;
            cout << "Error: operator[] threw unexpectedly on valid index (string)!" << endl;
            valuesOkStr = false;
        }
    }
    if (valuesOkStr) {
        cout << "OK: operator[] access succeeded before Clear() (string)." << endl;
    }

    hvStr.Clear();

    cout << "\n[After Clear()]" << endl;

    loctestnum++;
    if (hvStr.Size() != 0) {
        loctesterr++;
        cout << "Error: Size after Clear() is not zero (string): " << hvStr.Size() << endl;
    } else {
        cout << "OK: Size is zero after Clear() (string)." << endl;
    }

    loctestnum++;
    if (!hvStr.Empty()) {
        loctesterr++;
        cout << "Error: Empty() returned false after Clear() (string)." << endl;
    } else {
        cout << "OK: Empty() returned true after Clear() (string)." << endl;
    }

    loctestnum++;
    if (!hvStr.IsHeap()) {
        loctesterr++;
        cout << "Error: IsHeap() returned false on empty heap (string)!" << endl;
    } else {
        cout << "OK: IsHeap() returned true after Clear() (string)." << endl;
    }

    try {
        loctestnum++;
        std::string test = hvStr[0]; // Should throw
        loctesterr++;
        cout << "Error: operator[] did not throw after Clear() (string); returned: " << test << endl;
    } catch (...) {
        cout << "OK: operator[] threw exception as expected after Clear() (string)." << endl;
    }

    cout << "\n[Reusability Test After Clear() (string)]" << endl;

    lasd::Vector<std::string> newvecStr(2);
    newvecStr[0] = "kiwi";
    newvecStr[1] = "lemon";

    hvStr = lasd::HeapVec<std::string>(newvecStr); // Move assignment

    loctestnum++;
    if (hvStr.Size() == 2 && hvStr.IsHeap()) {
        cout << "OK: HeapVec<string> reused successfully after Clear()." << endl;
        cout << "hvStr[0] = " << hvStr[0] << ", hvStr[1] = " << hvStr[1] << endl;
    } else {
        loctesterr++;
        cout << "Error: Reuse after Clear() failed (string). Size: " << hvStr.Size()
            << ", IsHeap: " << hvStr.IsHeap() << endl;
    }

    cout << "-- Test: Exists() ---";

    lasd::Vector<std::string> initialValues(4);

    // Manually assign values using operator[]
    initialValues[0] = "apple";
    initialValues[1] = "banana";
    initialValues[2] = "cherry";
    initialValues[3] = "date";

    // Create the original heap from the vector
    lasd::HeapVec<std::string> originalHeap(initialValues);

    // Create a copy of the heap with a non-trivial name
    lasd::HeapVec<std::string> copiedHeap(originalHeap);

    std::cout << "--- Testing Exists method on copiedHeap (string) ---" << std::endl;

    // Test for values that should exist in the heap
    Exists(loctestnum, loctesterr, copiedHeap, true, std::string("banana"));
    Exists(loctestnum, loctesterr, copiedHeap, true, std::string("date"));

    // Test for values that should NOT exist in the heap
    Exists(loctestnum, loctesterr, copiedHeap, false, std::string("fig"));
    Exists(loctestnum, loctesterr, copiedHeap, false, std::string("grape"));

    std::cout << "Exists method test cases passed: " << loctestnum - loctesterr << std::endl;
    std::cout << "Exists method test cases failed: " << loctesterr << std::endl;


    } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error!" << endl;
    }

    cout << "End of Heap<string> Test! (Errors/Tests: "
        << loctesterr << "/" << loctestnum << ")" << endl;

    testnum += loctestnum;
    testerr += loctesterr;
}

void MytestSimpleExercise2A(unsigned int &testnum, unsigned int &testerr) {
    std::cout << std::endl << "==== Begin of testSimpleExercise2A ====" << std::endl;
  
    TestHeapInt(testnum, testerr);
    TestHeapDouble(testnum, testerr);
    TestHeapString(testnum, testerr);
  
    std::cout << "==== End of testSimpleExercise2A (Errors/Tests: "
              << testerr << "/" << testnum << ") ====" << std::endl;
  }
  

