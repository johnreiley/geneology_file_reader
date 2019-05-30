#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
public:
   // default
   Person() : givenName(""), lastName(""), birthDate(""), birthYear(""), id("") {}
   // non-default
   Person(string given, string last, string date, string year, string id) :
         givenName(given), lastName(last), birthDate(date), birthYear(year), id(id) {}
   // copy
   Person(const Person & rhs) { this->givenName = rhs.givenName; this->lastName = rhs.lastName; 
                                this->birthDate = rhs.birthDate; this->birthYear = rhs.birthYear; 
                                this->id = rhs.id; }
   
   void setGvnNm(string given) { this->givenName = given; }
   void setLstNm(string last)  { this->lastName = last;   }
   void setBrthDt(string date) { this->birthDate = date;  }
   void setBrthYr(string year) { this->birthYear = year;  }
   void setId(string id)       { this->id = id; }

   string getGvnNm()  const { return givenName; }
   string getLstNm()  const { return lastName;  }
   string getBrthDt() const { return birthDate; }
   string getBrthYr() const { return birthYear; }
   string getId()     const { return id;        }

   Person operator = (const Person & rhs);
   bool operator > (const Person & rhs);
   bool operator < (const Person & rhs);
   bool operator >= (const Person & rhs);
   bool operator <= (const Person & rhs);

   //ostream & operator << (const Person & rhs);

private:
   string givenName;
   string lastName;
   string birthDate;
   string birthYear;
   string id;
};

/*******************************************************
 * ASSIGNMENT operator
 * ****************************************************/
Person Person :: operator = (const Person & rhs)
{
   this->givenName = rhs.givenName; 
   this->lastName  = rhs.lastName; 
   this->birthDate = rhs.birthDate; 
   this->birthYear = rhs.birthYear;
   this->id        = rhs.id;

   return *this;
}

/*******************************************************
 * GREATER THAN operator
 * ****************************************************/
bool Person :: operator > (const Person & rhs)
{
   if (this->getLstNm > rhs.getLstNm)
      return true;
   else if (this->getGvnNm > rhs.getGvnNm)
      return true;
   else if (this->getBrthYr > rhs. getBrthYr)
      return true;
   else
      return false;
}

/*******************************************************
 * LESS THAN operator
 * ****************************************************/
bool Person :: operator < (const Person & rhs)
{
   if (this->getLstNm < rhs.getLstNm)
      return true;
   else if (this->getGvnNm < rhs.getGvnNm)
      return true;
   else if (this->getBrthYr < rhs. getBrthYr)
      return true;
   else
      return false;
}

/*******************************************************
 * GREATER THAN OR EQUAL TO operator
 * ****************************************************/
bool Person :: operator >= (const Person & rhs)
{
   if (this->getLstNm >= rhs.getLstNm)
      return true;
   else if (this->getGvnNm >= rhs.getGvnNm)
      return true;
   else if (this->getBrthYr >= rhs. getBrthYr)
      return true;
   else
      return false;
}

/*******************************************************
 * LESS THAN OR EQUAL TO operator
 * ****************************************************/
bool Person :: operator <= (const Person & rhs)
{
   if (this->getLstNm <= rhs.getLstNm)
      return true;
   else if (this->getGvnNm <= rhs.getGvnNm)
      return true;
   else if (this->getBrthYr <= rhs. getBrthYr)
      return true;
   else
      return false;
}

/*******************************************************
 * INSERTION operator
 * ****************************************************/
ostream & operator << (ostream & out, const Person & rhs)
{
   if (rhs.getGvnNm() != "")
   out << rhs.getGvnNm();
   if (rhs.getLstNm() != "" && rhs.getGvnNm() == "")
      out << rhs.getLstNm();
   else if (rhs.getLstNm() != "")
      out << " " << rhs.getLstNm();
   if (rhs.getBrthDt() != "" || rhs.getBrthYr() != "")
   {
      out << ", b.";
      if (rhs.getBrthDt() != "")
         out << " " << rhs.getBrthDt();
      if (rhs.getBrthYr() != "")
         out << " " << rhs.getBrthYr();
   }
   return out;
}

#endif //PERSON_H