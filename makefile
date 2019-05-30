###############################################################
# Program:
#     Week 13, Genealogy
#     Brother Ercanbrack, CS235
# Author:
#     John Reiley
# Summary:
#     Makes magic happen.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o
	g++ -o a.out week13.o -g -std=c++11
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
##############################################################
week13.o: week13.cpp vector.h bst.h person.h sortBinary.h bnode.h stack.h
	g++ -c week13.cpp -g -std=c++11
