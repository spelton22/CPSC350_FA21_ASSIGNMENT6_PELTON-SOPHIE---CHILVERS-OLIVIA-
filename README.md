# CPSC350_FA21_ASSIGNMENT6_PELTON-SOPHIE---CHILVERS-OLIVIA-

1.Olivia Chilvers 
  -- 2366117
  -- ochilvers@chapman.edu
 --  CPSC 350-01
  -- Assignment 6

2.Sophie Pelton
   -- 2370862
   -- spelton@chapman.edu
  -- CPSC 350-01
  -- Assignment 6


3.Main.cpp -- bst.h -- Faculty.cpp -- Faculty.h -- FileProcessor.cpp -- FileProcessor.h -- GenStack.h -- LinkedList.h -- Makefile -- Person.cpp -- Person.h -- PersonBST.h -- Rollback.cpp -- Rollback.h -- Simulation.cpp -- Simulation.h -- Student.cpp -- Student.h

4. #2 prints out only the information of the faculty and not their advisees; We did this to focus only on the faculty details and less clutter
  #4 prints out the faculty information and the IDs of the advisees; We did this to prevent clutter of all the student’s individual info
  #10 wont let the user delete a faculty member if it is the last one; We did this since it would not make sense for the students to have no advisors
  #12 reassigns the removed advisee to a new advisor if there exists another advisor; If not, the advisee stays with the advisor


5. https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm

https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170

https://www.javatpoint.com/how-to-split-strings-in-cpp

https://stackoverflow.com/questions/21807658/check-if-the-input-is-a-number-or-string-in-c

http://cplusplus.com/forum/beginner/102463/#:~:text=Why%20is%20it%20skipping%20the%20first%20getline%3F,-1&text=The%20cause%20is%20probably%20elsewhere%20in%20the%20program.&text=int%20x%3B%20cin%20%3E%3E%20x,remaining%20in%20the%20input%20buffer.

https://stackoverflow.com/questions/9941987/there-are-no-arguments-that-depend-on-a-template-parameter

https://stackoverflow.com/questions/3273993/how-do-i-validate-user-input-as-a-double-in-c

6. make all
  ./assignment6.exe
