#ifndef DICTIONARYTEST_HPP
#define DICTIONARYTEST_HPP

#include "../../container/dictionary.hpp"
#include <iostream>
#include <stdexcept>

/* ************************************************************************** */

// DictionaryContainer member functions!

template <typename Data>
void InsertC(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, const Data & val) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insertion in the dictionary container of the value \"" << val << "\": ";
    con.Insert(val);
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void InsertM(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, Data && val) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insertion in the dictionary container of the value \"" << val << "\": ";
    con.Insert(std::move(val));
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void Remove(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, const Data & val) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Removal from the dictionary container of the value \"" << val << "\": ";
    con.Remove(val);
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void InsertC(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, bool chk, const Data & val) {
  testnum++;
  bool tst;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insertion in the dictionary container of the value \"" << val << "\"; ";
    std::cout << "it " << ((tst = con.Insert(val)) ? "has" : "has not") << " been inserted: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void InsertM(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, bool chk, Data && val) {
  testnum++;
  bool tst;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insertion in the dictionary container of the value \"" << val << "\"; ";
    std::cout << "it " << ((tst = con.Insert(std::move(val))) ? "has" : "has not") << " been inserted: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void Remove(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, bool chk, const Data & val) {
  testnum++;
  bool tst;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Removal from the dictionary container of the value \"" << val << "\"; ";
    std::cout << "it " << ((tst = con.Remove(val)) ? "has" : "has not") << " been removed: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void InsertC(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, const lasd::TraversableContainer<Data> & mc) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insertion in the dictionary container of the values of the given linear container: ";
    con.InsertAll(mc);
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void InsertM(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, lasd::MappableContainer<Data> && mc) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insertion in the dictionary container of the values of the given linear container: ";
    con.InsertAll(std::move(mc));
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void Remove(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, const lasd::TraversableContainer<Data> & mc) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Removal from the dictionary container of the values of the given linear container: ";
    con.RemoveAll(mc);
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void InsertAllC(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, bool chk, const lasd::TraversableContainer<Data> & mc) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insertion in the dictionary container of the values of the given mappable container; ";
    std::cout << ((tst = con.InsertAll(mc)) ? "all" : "not all") << " values have been inserted: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void InsertAllM(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, bool chk, lasd::MappableContainer<Data> && mc) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insertion in the dictionary container of the values of the given mappable container; ";
    std::cout << ((tst = con.InsertAll(std::move(mc))) ? "all" : "not all") << " values have been inserted: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void RemoveAll(uint & testnum, uint & testerr, lasd::DictionaryContainer<Data> & con, bool chk, const lasd::TraversableContainer<Data> & mc) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Removal from the dictionary container of the values of the given linear container; ";
    std::cout << ((tst = con.RemoveAll(mc)) ? "all" : "not all") << " values have been removed: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

// OrderedDictionaryContainer member functions!

template <typename Data>
void Min(uint & testnum, uint & testerr, lasd::OrderedDictionaryContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Min of the ordered dictionary container with value \"" << con.Min() << "\": ";
    tst = ((con.Min() == val) == chk);
    std::cout << (tst ? "Correct!" : "Error!") << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((!chk) ? "Correct!" : "Error!") << std::endl;
    tst = !chk;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void RemoveMin(uint & testnum, uint & testerr, lasd::OrderedDictionaryContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Removal of the min from the ordered dictionary container with value \"" << val << "\": ";
    con.RemoveMin();
    tst = !chk; // Se aspettavamo un errore (chk false), allora rimuovere è errore, altrimenti corretto
    std::cout << (tst ? "Error!" : "Correct!") << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << "\"" << exc.what() << "\": " << (chk ? "Error!" : "Correct!") << std::endl;
    tst = !chk;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void Max(uint & testnum, uint & testerr, lasd::OrderedDictionaryContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Max of the ordered dictionary container with value \"" << con.Max() << "\": ";
    tst = ((con.Max() == val) == chk);
    std::cout << (tst ? "Correct!" : "Error!") << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((!chk) ? "Correct!" : "Error!") << std::endl;
    tst = !chk;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void RemoveMax(uint & testnum, uint & testerr, lasd::OrderedDictionaryContainer<Data> & con, bool chk, const Data & val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Removal of the max from the ordered dictionary container with value \"" << val << "\": ";
    con.RemoveMax();
    tst = !chk;
    std::cout << (tst ? "Error!" : "Correct!") << std::endl;
  }
  catch (std::length_error & exc) {
    std::cout << "\"" << exc.what() << "\": " << (chk ? "Error!" : "Correct!") << std::endl;
    tst = !chk;
  }
  catch (std::exception & exc) {
    tst = false;
    std::cout << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

#endif // DICTIONARYTEST_HPP
