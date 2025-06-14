#ifndef CONTAINERTEST_HPP
#define CONTAINERTEST_HPP

#include <iostream>
#include "../../container/container.hpp"

/* ************************************************************************** */

void Empty(uint&, uint&, const lasd::Container&, bool);
void Size(uint&, uint&, const lasd::Container&, bool, ulong);

/* ************************************************************************** */

void Clear(uint&, uint&, lasd::ClearableContainer&);

/* ************************************************************************** */

void TestIsConsistent(uint&, uint&, const lasd::Container&);
void Resize(uint&, uint&, lasd::ResizableContainer&, ulong);
void ClearAfterResize(uint&, uint&, lasd::ResizableContainer&, ulong);
void TestDoubleResize(uint&, uint&, lasd::ResizableContainer&, ulong, ulong);
void TestResizeToSameValue(uint&, uint&, lasd::ResizableContainer&, ulong);
void TestResizeToZero(uint&, uint&, lasd::ResizableContainer&);
void TestMultipleOperations(uint&, uint&, lasd::ResizableContainer&);

/* ************************************************************************** */

#endif
