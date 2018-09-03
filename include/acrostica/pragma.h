/*
 * Acrostica - Simple acrostic creator
 * Copyright © 2018 James McCoy <jamessan@jamessan.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// c:\qt\qt5.11.1\5.11.1\msvc2017_64\include\qtcore\qvector.h(683): warning C4127: conditional expression is constant [C:\views\acrostica\build\src\acrostica.vcxproj]
//  c:\qt\qt5.11.1\5.11.1\msvc2017_64\include\qtcore\qvector.h(683): note: consider using 'if constexpr' statement instead
//  c:\qt\qt5.11.1\5.11.1\msvc2017_64\include\qtcore\qvector.h(676): note: while compiling class template member function
//   'void QVector<int>::append(const T &)'
//          with
//          [
//              T=int
//          ]
//  c:\qt\qt5.11.1\5.11.1\msvc2017_64\include\qtcore\qvector.h(283): note: see reference to function template instantiation 'void QVector<int>::append(const T &)' being compiled
//          with
//          [
//              T=int
//          ]
//  c:\qt\qt5.11.1\5.11.1\msvc2017_64\include\qtcore\qabstractitemmodel.h(269): note: see reference to class template instantiation 'QVector<int>' being compiled
#pragma warning(disable:4127)

// c:\qt\5.11\msvc2015\include\qtcore\qmap.h(129): warning C4718: 'QMapNode<QChar,int>::doDestroySubTree': recursive call has no side effects, deleting
#pragma warning(disable:4718)

// Enable some useful "disabled by default" warnings

// enumerator 'identifier' in a switch of enum 'enumeration' is not handled
#pragma warning(default:4062)

// 'class': class has virtual functions, but destructor is not virtual
#pragma warning(default:4265)

// nonstandard extension used : 'var' : loop control variable declared in the for-loop is used outside the for-loop scope
#pragma warning(default:4289)

// 'operator': expression is always false
#pragma warning(default:4296)

// missing type specifier - int assumed. Note: C no longer supports default-int
#pragma warning(default:4431)
