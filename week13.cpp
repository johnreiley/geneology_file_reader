
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "person.h"
#include "vector.h"
#include "sortBinary.h"
using namespace std;

// function definition
int readGED(Vector <Person> & genealogy, string fileName);

/************************************************
 * MAIN :
 * this function is the main driver for the 
 * genealogy application that parses a GED file
 * and displays the names sorted and in heiarical
 * order.
 * *********************************************/
int main(int argc, const char* argv[])
{
   char fileName[50];

   if (argc == 1)
   {
      cout << "Enter the name of the file: ";
      cin >> fileName;
   }
   else if (argc == 2)
   {
      strcpy(fileName, argv[1]);
   }

   // create a list
   Vector <Person> genealogy;
   // call read GED
   if (!readGED(genealogy, fileName))
      return 0;
   
   // call genealogy sort
   sortBinary(genealogy);

   // display
   for (VectorIterator <Person> it = genealogy.begin(); it != genealogy.end(); it++)
      cout << *it;
}


int readGED(Vector <Person> & genealogy, string fileName)
{
   // open the file
   ifstream fin;
   fin.open(fileName);

   if (fin.fail())
   {
      cout << "ERROR: Could not open file named " << fileName << endl;
      return 0;
   }
   // while loop
   string parse = "";
   string parse2 = "";
   int index;
   while (getline(fin, parse))
   {
      if (parse.find("0 @I") != std::string::npos)
      {
         // create a person
         Person individual = Person();
         // find the ID
         index = parse.find("@I");
         parse2 = parse.substr(index, index + 3);
         individual.setId(parse2);
         parse2 = "";
         // look for the info until find a new person
         while (parse.find("0 @I") != std::string::npos)
         {
            // is there a given name?
            if (parse.find("GIVN") != std::string::npos)
            {
               for (int i = 7; i < parse.length(); i++)
               {
                  parse2 += parse[i];
               }
               individual.setGvnNm(parse2);
               parse2.clear();
            }
            // is there a surname?
            if (parse.find("SURN") != std::string::npos)
            {
               for (int i = 7; i < parse.length(); i++)
               {
                  parse2 += parse[i];
               }
               individual.setLstNm(parse2);
               parse2.clear();
            }
            // is there a birthdate?
            if (parse.find("BIRT") != std::string::npos)
            {
               getline(fin, parse);
               index = 7;
               for (int i = index; i < parse.length(); i++)
               {
                  parse2 += parse[i];
               }
               // split the birth year from month
               string year = "";
               for (int i = parse2.length() - 1; (isdigit(parse[i]) || parse[i] == '/'); i--)
               {
                  year += parse2[i];
                  parse2.pop_back();
               }
               // remove the space
               parse2.pop_back();
               // reverse it because it's backwards
               reverse(year.begin(), year.end());
               string rest = parse2;

               // assign year and date to Person
               individual.setBrthDt(rest);
               individual.setBrthYr(year);

               parse2.clear();

               getline(fin, parse);
            }
         }

         // insert completed person
         genealogy.push_back(individual);
      }
   }

}

