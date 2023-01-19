// ASU CSE310 Assignment #5 Fall 2022
// Name of Author: Ian Carlson
// ASU ID: 1223065376
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

#include "LinkedList.h"
#include <string>
#include <math.h>
using namespace std;

class Hash
{
   private:
      LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
      int m; 
      int n;                    //slots number of the hash table
	public:
      Hash(int size);
      ~Hash();
      bool hashSearch(string model, string make, int vin);
      bool hashInsert(string model, string make, int vin, double price);
      bool hashDelete(string model, string make, int vin);
      int hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);
  };

//constructor
Hash::Hash(int size)
{
   n = 0;
   m = size;
   hashTable = new LinkedList[size];
}

//Destructor
Hash::~Hash()
{
  for(int i = 0; i < m; ++i){
      hashTable[i].~LinkedList();
   } 

 n = 0;
 m = 0;  
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashSearch(string model, string make, int vin)
{
   bool found = false;
   
   string s = to_string(vin);
   string key = model + make + s;

   int index = hashFunction(key);
   found = hashTable[index].searchCar(vin);

   if (found == true){
      cout << "\n" << left
          << setw(18) << model
          << setw(18) << make
          << setw(8)  << vin
          << " is found inside the hash table." << endl;
   }
   else{
      cout << "\n" << left
           << setw(18) << model
           << setw(18) << make
           << setw(8)  << vin
           << " is NOT found inside the hash table." << endl;
   }
  
   return found;
}

//hashInsert inserts a Car with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string model, string make, int vin, double price)
{
   bool success; 
   string s = to_string(vin);
   string key = model + make + s;

   int index = hashFunction(key);

   bool found = hashTable[index].searchCar(vin);

   if(found){
      return false;
   }

   success = hashTable[index].insertCar(model, make, vin, price);
   
   if(success){
        n++;
   }
   return success;
}

//hashDelete deletes a Car with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashDelete(string model, string make, int vin)
{
   string s = to_string(vin);
   string key = model + make + s;
   int index = hashFunction(key);
   hashSearch(model, make, vin);
   bool sucess = hashTable[index].deleteCar(vin);
   if(sucess){
      n--;
      cout << "\n";
      cout << setw(18) << model
           << setw(18) << make
           << setw(8)  << vin
           << " is deleted from hash table." << endl;
   }
   else{
      cout << "\n";
      cout << setw(18) << model
           << setw(18) << make
           << setw(8)  << vin
           << " is NOT deleted from hash table." << endl;
   }
   return sucess;
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor()
{
    double loadFactor = 0;
    for(int i = 0; i < m; i++){
        if(hashTable[i].getSize() > loadFactor){
            loadFactor = hashTable[i].getSize();
        }
    }

   double idealLoadFactor = double(n) / double(m);
   double ratio = loadFactor / idealLoadFactor;
    cout.precision(2);
    cout << "\nThe ideal load factor is: " << fixed << idealLoadFactor << endl;
    cout << "My hash table real load factor is: " << fixed << loadFactor << endl;
    cout << "My hash table performance ratio is: " << fixed << ratio << endl;
    return ratio;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
   for(int i = 0; i < m; i++){
      cout << "\nHashTable[" << i << "], size = " << hashTable[i].getSize() << endl;
      hashTable[i].displayList();
   }
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we will hash the key to
int Hash::hashFunction(string key)
{
   int k = 0;
   for (int i = 0; i < key.length(); i++)
   {
       char x = key.at(i);
        k += int(x);
       
   }
   double fib = sqrt(5) - 1;
   double c1 = 17;
   double c2 = 13;


   double result = k * fib;
   double result1 = result * c1 + result * c2;
   int result2 = (int) result1 % m;


   return result2;
}