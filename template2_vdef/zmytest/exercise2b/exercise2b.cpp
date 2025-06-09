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
#include "../pq/pq.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void TestPQHeapInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQHeap<int> Test:" << endl;
    try {

        // Test 1: Basic construction and priority queue operations
        cout << "--- Test 1: Basic Construction and Operations ---" << endl;
        lasd::Vector<int> vec(10);
        SetAt(loctestnum, loctesterr, vec, true, 0, 20);
        SetAt(loctestnum, loctesterr, vec, true, 1, 15);
        SetAt(loctestnum, loctesterr, vec, true, 2, 18);
        SetAt(loctestnum, loctesterr, vec, true, 3, 10);
        SetAt(loctestnum, loctesterr, vec, true, 4, 12);
        SetAt(loctestnum, loctesterr, vec, true, 5, 25);
        SetAt(loctestnum, loctesterr, vec, true, 6, 17);
        SetAt(loctestnum, loctesterr, vec, true, 7, 5);
        SetAt(loctestnum, loctesterr, vec, true, 8, 8);
        SetAt(loctestnum, loctesterr, vec, true, 9, 30);

        lasd::PQHeap<int> pq(vec);
        
        // Basic property tests
        EmptyTest(loctestnum, loctesterr, pq, false);
        SizeTest(loctestnum, loctesterr, pq, 10);
        
        // Test tip (should be maximum element)
        Tip(loctestnum, loctesterr, pq, true, 30);
        
        // Test tip and remove operations
        TipNRemove(loctestnum, loctesterr, pq, true, 30);
        SizeTest(loctestnum, loctesterr, pq, 9);
        Tip(loctestnum, loctesterr, pq, true, 25);
        
        TipNRemove(loctestnum, loctesterr, pq, true, 25);
        SizeTest(loctestnum, loctesterr, pq, 8);
        Tip(loctestnum, loctesterr, pq, true, 20);

        // Test remove tip
        RemoveTip(loctestnum, loctesterr, pq, true);
        SizeTest(loctestnum, loctesterr, pq, 7);
        Tip(loctestnum, loctesterr, pq, true, 18);

        // Test 2: Insert operations
        cout << "--- Test 2: Insert Operations ---" << endl;
        Insert(loctestnum, loctesterr, pq, 35);
        SizeTest(loctestnum, loctesterr, pq, 8);
        Tip(loctestnum, loctesterr, pq, true, 35);

        Insert(loctestnum, loctesterr, pq, 22);
        SizeTest(loctestnum, loctesterr, pq, 9);
        Tip(loctestnum, loctesterr, pq, true, 35);

        Insert(loctestnum, loctesterr, pq, 40);
        SizeTest(loctestnum, loctesterr, pq, 10);
        Tip(loctestnum, loctesterr, pq, true, 40);

        // Test move insert
        InsertMove(loctestnum, loctesterr, pq, 45);
        SizeTest(loctestnum, loctesterr, pq, 11);
        Tip(loctestnum, loctesterr, pq, true, 45);

        // Test 3: Change operations
        cout << "--- Test 3: Change Operations ---" << endl;
        // Change root to smaller value
        Change(loctestnum, loctesterr, pq, true, 0, 1);
        Tip(loctestnum, loctesterr, pq, true, 40);

        // Change leaf to larger value
        Change(loctestnum, loctesterr, pq, true, pq.Size()-1, 50);
        Tip(loctestnum, loctesterr, pq, true, 50);

        // Change middle element
        Change(loctestnum, loctesterr, pq, true, 3, 60);
        Tip(loctestnum, loctesterr, pq, true, 60);

        // Test move change
        ChangeMove(loctestnum, loctesterr, pq, 5, 65);
        Tip(loctestnum, loctesterr, pq, true, 65);

        // Test invalid index change
        ChangeInvalidIndexTest(loctestnum, loctesterr, pq, 100, 999);

        // Test 4: Empty priority queue operations
        cout << "--- Test 4: Empty PQ Operations ---" << endl;
        lasd::PQHeap<int> emptyPQ;
        EmptyTest(loctestnum, loctesterr, emptyPQ, true);
        SizeTest(loctestnum, loctesterr, emptyPQ, 0);

        // Test operations on empty PQ
        TipEmptyTest(loctestnum, loctesterr, emptyPQ);
        RemoveTipEmptyTest(loctestnum, loctesterr, emptyPQ);
        TipNRemoveEmptyTest(loctestnum, loctesterr, emptyPQ);

        // Insert into empty PQ
        Insert(loctestnum, loctesterr, emptyPQ, 42);
        EmptyTest(loctestnum, loctesterr, emptyPQ, false);
        SizeTest(loctestnum, loctesterr, emptyPQ, 1);
        Tip(loctestnum, loctesterr, emptyPQ, true, 42);

        // Remove the only element
        TipNRemove(loctestnum, loctesterr, emptyPQ, true, 42);
        EmptyTest(loctestnum, loctesterr, emptyPQ, true);
        SizeTest(loctestnum, loctesterr, emptyPQ, 0);

        // Test 5: Copy and Move Constructors
        cout << "--- Test 5: Copy and Move Operations ---" << endl;
        CopyConstructorTest(loctestnum, loctesterr, pq);
        
        lasd::PQHeap<int> pqCopy(pq);
        SizeTest(loctestnum, loctesterr, pqCopy, pq.Size());
        Tip(loctestnum, loctesterr, pqCopy, true, 65);

        // Test move constructor
        MoveConstructorTest(loctestnum, loctesterr, pq);
        // Note: pq may be in moved-from state after this

        // Reconstruct pq for further tests
        pq = lasd::PQHeap<int>(vec);

        for(int i = 0; i < 5; i++) {
            Insert(loctestnum, loctesterr, pq, 100 + i);
        }

        // Test 6: Constructor from container
        cout << "--- Test 6: Container Constructor ---" << endl;
        ConstructFromContainerTest(loctestnum, loctesterr, vec);

        // Test 7: Stress test with multiple operations
        cout << "--- Test 7: Stress Test ---" << endl;
        lasd::PQHeap<int> stressPQ;
        
        // Insert many elements
        for(int i = 0; i < 50; i++) {
            Insert(loctestnum, loctesterr, stressPQ, rand() % 1000);
        }
        SizeTest(loctestnum, loctesterr, stressPQ, 50);

        // Remove half of them
        for(int i = 0; i < 25; i++) {
            int expectedTip = stressPQ.Tip();  // saves the copy of the value
            TipNRemove(loctestnum, loctesterr, stressPQ, true, expectedTip);
        }

        // Test 8: Duplicate elements
        cout << "--- Test 8: Duplicate Elements ---" << endl;
        lasd::PQHeap<int> dupPQ;
        for(int i = 0; i < 10; i++) {
            Insert(loctestnum, loctesterr, dupPQ, 5);
        }
        SizeTest(loctestnum, loctesterr, dupPQ, 10);
        Tip(loctestnum, loctesterr, dupPQ, true, 5);

        // Remove all duplicates
        for(int i = 0; i < 10; i++) {
            TipNRemove(loctestnum, loctesterr, dupPQ, true, 5);
        }
        EmptyTest(loctestnum, loctesterr, dupPQ, true);

        // Test 9: Mixed insert and remove operations
        cout << "--- Test 9: Mixed Operations ---" << endl;
        lasd::PQHeap<int> mixedPQ;
        
        Insert(loctestnum, loctesterr, mixedPQ, 10);
        Insert(loctestnum, loctesterr, mixedPQ, 20);
        TipNRemove(loctestnum, loctesterr, mixedPQ, true, 20);
        Insert(loctestnum, loctesterr, mixedPQ, 30);
        Insert(loctestnum, loctesterr, mixedPQ, 5);
        Tip(loctestnum, loctesterr, mixedPQ, true, 30);
        RemoveTip(loctestnum, loctesterr, mixedPQ, true);
        Tip(loctestnum, loctesterr, mixedPQ, true, 10);

        // Test 10: Large dataset performance
        cout << "--- Test 10: Large Dataset ---" << endl;
        lasd::PQHeap<int> largePQ;
        
        // Insert 50 random elements
        lasd::Vector<int> insertedValues(50);
        int maxValue = 0;
        for(ulong i = 0; i < 50; i++) {
            int val = rand() % 10000;
            insertedValues[i] = val;
            maxValue = max(maxValue, val);
            Insert(loctestnum, loctesterr, largePQ, val);
        }
        SizeTest(loctestnum, loctesterr, largePQ, 50);

        // Remove all elements and verify they come out in descending order
        lasd::Vector<int> removedValues(50); // Fixed: pre-allocate size
        for(ulong i = 0; i < 50; i++) {
            int topValue = largePQ.Tip();
            TipNRemove(loctestnum, loctesterr, largePQ, true, topValue);
            removedValues[i] = topValue;
        }

        bool descending = true;
        // Verify removed values are in descending order
        for(ulong i = 1; i < removedValues.Size(); i++) {
            if (removedValues[i-1] < removedValues[i]){
                descending = false;
                break; // Optional: exit early once we find violation
            }
        }

        if(descending) {
            testnum++;
        }

        EmptyTest(loctestnum, loctesterr, largePQ, true);

        // Test 11: Change operations stress test
        cout << "--- Test 11: Change Operations Stress Test ---" << endl;
        lasd::PQHeap<int> changePQ;
        for(int i = 0; i < 20; i++) {
            Insert(loctestnum, loctesterr, changePQ, i);
        }

        // Change multiple elements

        for(ulong i = 0; i < changePQ.Size(); i += 2) {
            Change(loctestnum, loctesterr, changePQ, true, i, static_cast<int>(100 + i));
        }

        // Verify tip is correct
        Tip(loctestnum, loctesterr, changePQ, true, 118); // 100 + 18

        // Test 12: Edge cases with negative numbers
        cout << "--- Test 12: Negative Numbers ---" << endl;
        lasd::PQHeap<int> negPQ;
        Insert(loctestnum, loctesterr, negPQ, -10);
        Insert(loctestnum, loctesterr, negPQ, -5);
        Insert(loctestnum, loctesterr, negPQ, -15);
        Insert(loctestnum, loctesterr, negPQ, 0);
        Insert(loctestnum, loctesterr, negPQ, 5);

        Tip(loctestnum, loctesterr, negPQ, true, 5);
        TipNRemove(loctestnum, loctesterr, negPQ, true, 5);
        Tip(loctestnum, loctesterr, negPQ, true, 0);
        TipNRemove(loctestnum, loctesterr, negPQ, true, 0);
        Tip(loctestnum, loctesterr, negPQ, true, -5);

        // Test 13: Repeated operations
        cout << "--- Test 13: Repeated Operations ---" << endl;
        lasd::PQHeap<int> repeatPQ;
        
        for(int cycle = 0; cycle < 5; cycle++) {
            // Fill
            for(int i = 0; i < 10; i++) {
                Insert(loctestnum, loctesterr, repeatPQ, rand() % 100);
            }
            
            // Partially empty
            for(int i = 0; i < 5; i++) {
                if(!repeatPQ.Empty()) {
                    RemoveTip(loctestnum, loctesterr, repeatPQ, true);
                }
            }
            
            // Change some elements
            for(ulong i = 0; i < min((ulong)3, repeatPQ.Size()); i++) {
                Change(loctestnum, loctesterr, repeatPQ, true, i, rand() % 200);
            }
        }

        // Final cleanup
        while(!repeatPQ.Empty()) {
            RemoveTip(loctestnum, loctesterr, repeatPQ, true);
        }
        EmptyTest(loctestnum, loctesterr, repeatPQ, true);

        // Test 14: Extreme values
        cout << "--- Test 14: Extreme Values ---" << endl;
        lasd::PQHeap<int> extremePQ;
        Insert(loctestnum, loctesterr, extremePQ, numeric_limits<int>::max());
        Insert(loctestnum, loctesterr, extremePQ, numeric_limits<int>::min());
        Insert(loctestnum, loctesterr, extremePQ, 0);

        Tip(loctestnum, loctesterr, extremePQ, true, numeric_limits<int>::max());
        TipNRemove(loctestnum, loctesterr, extremePQ, true, numeric_limits<int>::max());
        Tip(loctestnum, loctesterr, extremePQ, true, 0);
        TipNRemove(loctestnum, loctesterr, extremePQ, true, 0);
        Tip(loctestnum, loctesterr, extremePQ, true, numeric_limits<int>::min());

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error!" << endl;
    }

    cout << "End of PQHeap<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


void TestPQHeapDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "== Begin PQHeap<double> Test ==" << endl;

    try {
        // Test 1: Basic operations with doubles
        cout << "-- Test 1: Basic Double Operations --" << endl;
        lasd::PQHeap<double> pq;
        
        Insert(loctestnum, loctesterr, pq, 3.14159);
        Insert(loctestnum, loctesterr, pq, 2.71828);
        Insert(loctestnum, loctesterr, pq, 1.41421);
        Insert(loctestnum, loctesterr, pq, 1.73205);

        SizeTest(loctestnum, loctesterr, pq, 4);
        Tip(loctestnum, loctesterr, pq, true, 3.14159);

        // Test 2: Precision handling
        cout << "-- Test 2: Precision Handling --" << endl;
        lasd::PQHeap<double> precisionPQ;
        Insert(loctestnum, loctesterr, precisionPQ, 1.0000001);
        Insert(loctestnum, loctesterr, precisionPQ, 1.0000000);
        Insert(loctestnum, loctesterr, precisionPQ, 0.9999999);


        double expectedTip = precisionPQ.Tip(); // Copia locale sicura
        TipNRemove(loctestnum, loctesterr, precisionPQ, true, expectedTip);

        // Test 3: Special values
        cout << "-- Test 3: Special Double Values --" << endl;
        lasd::PQHeap<double> specialPQ;
        Insert(loctestnum, loctesterr, specialPQ, 0.0);
        Insert(loctestnum, loctesterr, specialPQ, -0.0);
        Insert(loctestnum, loctesterr, specialPQ, numeric_limits<double>::infinity());
        Insert(loctestnum, loctesterr, specialPQ, -numeric_limits<double>::infinity());

        Tip(loctestnum, loctesterr, specialPQ, true, numeric_limits<double>::infinity());
        TipNRemove(loctestnum, loctesterr, specialPQ, true, numeric_limits<double>::infinity());

        // Test 4: Change operations with doubles
        cout << "-- Test 4: Change Operations --" << endl;
        Change(loctestnum, loctesterr, pq, true, 0, 4.0);
        Tip(loctestnum, loctesterr, pq, true, 4.0);

        Change(loctestnum, loctesterr, pq, true, 1, 0.5);
        Tip(loctestnum, loctesterr, pq, true, 4.0);

        // Test 5: Large dataset with doubles
        cout << "-- Test 5: Large Dataset --" << endl;
        lasd::PQHeap<double> largePQ;
        double maxVal = -numeric_limits<double>::infinity();

        for(int i = 0; i < 50; i++) {
            double val = (rand() % 10000) / 100.0;
            maxVal = max(maxVal, val);
            Insert(loctestnum, loctesterr, largePQ, val);
        }

        SizeTest(loctestnum, loctesterr, largePQ, 50);
        Tip(loctestnum, loctesterr, largePQ, true, maxVal);

        // Remove all elements
        while(!largePQ.Empty()) {
            RemoveTip(loctestnum, loctesterr, largePQ, true);
        }
        EmptyTest(loctestnum, loctesterr, largePQ, true);

        // Test 6: Constructor from container
        cout << "-- Test 6: Container Constructor --" << endl;
        lasd::Vector<double> vec(5);
        SetAt(loctestnum, loctesterr, vec, true, 0, 1.1);
        SetAt(loctestnum, loctesterr, vec, true, 1, 2.2);
        SetAt(loctestnum, loctesterr, vec, true, 2, 3.3);
        SetAt(loctestnum, loctesterr, vec, true, 3, 4.4);
        SetAt(loctestnum, loctesterr, vec, true, 4, 5.5);

        lasd::PQHeap<double> containerPQ(vec);
        SizeTest(loctestnum, loctesterr, containerPQ, 5);
        Tip(loctestnum, loctesterr, containerPQ, true, 5.5);

        // Test 7: Copy and move operations
        cout << "-- Test 7: Copy and Move --" << endl;
        lasd::PQHeap<double> copyPQ(containerPQ);
        SizeTest(loctestnum, loctesterr, copyPQ, 5);
        Tip(loctestnum, loctesterr, copyPQ, true, 5.5);

        lasd::PQHeap<double> movePQ(std::move(copyPQ));
        SizeTest(loctestnum, loctesterr, movePQ, 5);
        EmptyTest(loctestnum, loctesterr, copyPQ, true);

        // Test 8: Repeated operations
        cout << "-- Test 8: Repeated Operations --" << endl;
        lasd::PQHeap<double> repeatPQ;
        
        for(int j = 0; j < 10; j++) {
            for(int i = 0; i < 5; i++) {
                Insert(loctestnum, loctesterr, repeatPQ, (rand() % 100) / 10.0);
            }
            
            for(int i = 0; i < 2; i++) {
                if(!repeatPQ.Empty()) {
                    // FIX: Store the tip value in a local variable before calling TipNRemove
                    double tipValue = repeatPQ.Tip();  // Make a copy to avoid dangling reference
                    TipNRemove(loctestnum, loctesterr, repeatPQ, true, tipValue);
                }
                
            }
            
            if(repeatPQ.Size() > 0) {
                Change(loctestnum, loctesterr, repeatPQ, true, 0, (rand() % 200) / 10.0);
            }
        }

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << "!! Unmanaged exception caught !!" << endl;
    }

    cout << "== End of PQHeap<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ") ==" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


void TestPQHeapString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQHeap<string> Test:" << endl;
    
    try {
        // Test 1: Basic string operations
        cout << "--- Test 1: Basic String Operations ---" << endl;
        lasd::PQHeap<string> pq;
        
        Insert(loctestnum, loctesterr, pq, string("Zebra"));
        Insert(loctestnum, loctesterr, pq, string("Apple"));
        Insert(loctestnum, loctesterr, pq, string("Banana"));
        Insert(loctestnum, loctesterr, pq, string("Cherry"));

        SizeTest(loctestnum, loctesterr, pq, 4);
        Tip(loctestnum, loctesterr, pq, true, string("Zebra"));

        TipNRemove(loctestnum, loctesterr, pq, true, string("Zebra"));
        Tip(loctestnum, loctesterr, pq, true, string("Cherry"));

        // Test 2: Case sensitivity
        cout << "--- Test 2: Case Sensitivity ---" << endl;
        Insert(loctestnum, loctesterr, pq, string("apple"));
        Insert(loctestnum, loctesterr, pq, string("Apple"));
        Insert(loctestnum, loctesterr, pq, string("APPLE"));

        Tip(loctestnum, loctesterr, pq, true, string("apple")); // lowercase 'a' > uppercase 'A'

        // Test 3: Empty strings and special characters
        cout << "--- Test 3: Special String Cases ---" << endl;
        lasd::PQHeap<string> specialPQ;
        Insert(loctestnum, loctesterr, specialPQ, string(""));
        Insert(loctestnum, loctesterr, specialPQ, string("a"));
        Insert(loctestnum, loctesterr, specialPQ, string("A"));
        Insert(loctestnum, loctesterr, specialPQ, string("aa"));
        Insert(loctestnum, loctesterr, specialPQ, string("Z"));

        Tip(loctestnum, loctesterr, specialPQ, true, string("aa"));

        // Test 4: Long strings
        cout << "--- Test 4: Long Strings ---" << endl;
        string longStr1(100, 'z');
        string longStr2(100, 'a');
        string longStr3(99, 'z');
        longStr3 += 'a';

        lasd::PQHeap<string> longPQ;
        Insert(loctestnum, loctesterr, longPQ, longStr1);
        Insert(loctestnum, loctesterr, longPQ, longStr2);
        Insert(loctestnum, loctesterr, longPQ, longStr3);

        Tip(loctestnum, loctesterr, longPQ, true, longStr1);

        // Test 5: Change operations
        cout << "--- Test 5: Change Operations ---" << endl;
        Change(loctestnum, loctesterr, pq, true, 0, string("ZZZ"));
        Tip(loctestnum, loctesterr, pq, true, string("ZZZ"));

        Change(loctestnum, loctesterr, pq, true, 1, string("AAA"));
        Tip(loctestnum, loctesterr, pq, true, string("ZZZ"));

        // Test invalid index
        ChangeInvalidIndexTest(loctestnum, loctesterr, pq, 100, string("Invalid"));

        // Test 6: Duplicate strings
        cout << "--- Test 6: Duplicate Strings ---" << endl;
        lasd::PQHeap<string> dupPQ;
        for(int i = 0; i < 10; i++) {
            Insert(loctestnum, loctesterr, dupPQ, string("Hello"));
        }
        
        SizeTest(loctestnum, loctesterr, dupPQ, 10);
        Tip(loctestnum, loctesterr, dupPQ, true, string("Hello"));

        // Remove all duplicates
        for(int i = 0; i < 10; i++) {
            TipNRemove(loctestnum, loctesterr, dupPQ, true, string("Hello"));
        }
        EmptyTest(loctestnum, loctesterr, dupPQ, true);

        // Test 7: Constructor from container
        cout << "--- Test 7: Container Constructor ---" << endl;
        lasd::Vector<string> vec(5);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("Dog"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("Cat"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("Bird"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("Fish"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("Lion"));

        lasd::PQHeap<string> containerPQ(vec);
        SizeTest(loctestnum, loctesterr, containerPQ, 5);
        Tip(loctestnum, loctesterr, containerPQ, true, string("Lion"));

        // Test 8: Copy and move operations
        cout << "--- Test 8: Copy and Move Operations ---" << endl;
        CopyConstructorTest(loctestnum, loctesterr, containerPQ);
        
        lasd::PQHeap<string> copyPQ(containerPQ);
        SizeTest(loctestnum, loctesterr, copyPQ, 5);

        lasd::PQHeap<string> movePQ(std::move(copyPQ));
        SizeTest(loctestnum, loctesterr, movePQ, 5);
        EmptyTest(loctestnum, loctesterr, copyPQ, true);

        // Test 9: Large dataset
        cout << "--- Test 9: Large String Dataset ---" << endl;
        lasd::PQHeap<string> largePQ;
        string maxStr = "";
        
        for(int i = 0; i < 50; i++) {
            string str = "String" + to_string(rand() % 1000);
            if(str > maxStr) maxStr = str;
            Insert(loctestnum, loctesterr, largePQ, str);
        }
        
        SizeTest(loctestnum, loctesterr, largePQ, 50);
        Tip(loctestnum, loctesterr, largePQ, true, maxStr);

        // Test 10: Mixed operations
        cout << "--- Test 10: Mixed String Operations ---" << endl;
        lasd::PQHeap<string> mixedPQ;
        
        Insert(loctestnum, loctesterr, mixedPQ, string("Medium"));
        Insert(loctestnum, loctesterr, mixedPQ, string("High"));
        Insert(loctestnum, loctesterr, mixedPQ, string("Low"));
        
        Tip(loctestnum, loctesterr, mixedPQ, true, string("Medium")); // M > H > L

        Change(loctestnum, loctesterr, mixedPQ, true, 2, string("VeryHigh"));
        Tip(loctestnum, loctesterr, mixedPQ, true, string("VeryHigh"));

        RemoveTip(loctestnum, loctesterr, mixedPQ, true);
        Tip(loctestnum, loctesterr, mixedPQ, true, string("Medium"));

        // Test 11: Special Characters
        cout << "--- Test 11: Special Characters ---" << endl;

        lasd::PQHeap<string> specialCharPQ;
        Insert(loctestnum, loctesterr, specialCharPQ, string("hello\nworld"));
        Insert(loctestnum, loctesterr, specialCharPQ, string("hello@world"));
        Insert(loctestnum, loctesterr, specialCharPQ, string("hello#world"));

        Tip(loctestnum, loctesterr, specialCharPQ, true, string("hello@world"));

        TipNRemove(loctestnum, loctesterr, specialCharPQ, true, string("hello@world"));
        TipNRemove(loctestnum, loctesterr, specialCharPQ, true, string("hello#world"));
        TipNRemove(loctestnum, loctesterr, specialCharPQ, true, string("hello\nworld"));

        EmptyTest(loctestnum, loctesterr, specialCharPQ, true);

    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error in PQHeap<string> test!" << endl;
    }

    cout << "== End PQHeap<string> Test (Errors/Tests: " << loctesterr << "/" << loctestnum << ") ==" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


void testSimpleExercise2B(unsigned int &testnum, unsigned int &testerr) {
    std::cout << std::endl << "==== Begin of testSimpleExercise2B ====" << std::endl;
  
    TestPQHeapInt(testnum, testerr);
    TestPQHeapDouble(testnum, testerr);
    TestPQHeapString(testnum, testerr);
  
    std::cout << std::endl << "==== End of testSimpleExercise2B (Errors/Tests: "
              << testerr << "/" << testnum << ") ====" << std::endl;
  }

