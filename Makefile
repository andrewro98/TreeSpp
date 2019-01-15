CXX			 := g++
#CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
CXXFLAGS := -g
BUILD    := ./build
INCLUDE  := ./include
SRC			 := ./src
TEST 		 := ./test
TESTBUILD := ./testbuild
TESTEXE	 := ./testexe

sparse_bst.o: $(INCLUDE)/sparse_bst.h $(INCLUDE)/tree.h $(INCLUDE)/exceptions.h
	$(CXX) $(CXXFLAGS) -o $(BUILD)/sparse_bst.o -c $(INCLUDE)/sparse_bst.h

dense_bst.o: $(INCLUDE)/dense_bst.h $(INCLUDE)/tree.h
	$(CXX) $(CXXFLAGS) -o $(BUILD)/dense_bst.o -c $(INCLUDE)/dense_bst.h

test_dense_bst.o: $(TEST)/test_dense_bst.cpp $(INCLUDE)/dense_bst.h
	$(CXX) $(CXXFLAGS) -o $(TESTBUILD)/test_dense_bst.o -c $(TEST)/test_dense_bst.cpp

test_dense_bst: test_dense_bst.o dense_bst.o
	$(CXX) $(CXXFLAGS) -o $(TESTEXE)/test_dense_bst $(TESTBUILD)/test_dense_bst.o $(BUILD)/dense_bst.o
