UPOalglib
==========

Collection of algorithms and abstract data types developed at the [Computer Science Institute](http://www.di.unipmn.it) of the [University of Piemonte Orientale](http://www.uniupo.it) for the *Algorithm 1 - Lab* course.

UPOalglib is free software: you can redistribute it and/or modify
it under the terms of the **GNU General Public License** as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

UPOalglib is distributed in the hope that it will be useful,
but **without any warranty**; without even the implied warranty of
**merchandability** or **fitness for a particular purpose**.  See the
**GNU General Public License** for more details.

You should have received a copy of the **GNU General Public License**
along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.

**Requirements:** 
* it is **strongly** recommended to have a Linux Fedora enviroment due to a ``relocation R_X86_64_32 against `.rodata'`` error on other distributions;
* an ISO C11 compatible enviroment;
* GNU GCC 6.3.1 or later;
* a C memory debugger, like Valgrind;
* GNU GDB 7.11 or later;
* GNU Makefile 4.1 or later;

**Compiling:**
* in order to compile the API: _**make clean bin**_;
* in order to compile the tests: _**make clean test**_;
* in order to test the implementations: _**./test/test_name_of_the_executable_in_test_directory**_;
