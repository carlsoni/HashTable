// ASU CSE310 Assignment #5 Fall 2022
// Name of Author: Ian Carlson
// ASU ID: 1223065376
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Car
//   object's hash value.     
//             in order to to get a hash index I send a string key to the hash function in the following format
//   modelmakevin. I then take the value of each character of the string and sum them up into a double. I then 
//   multiplied this sum value by the fiinacci number and stored it in k. I then used the formula k * c1 + k * c2
//   where c1 and c2 are prime number constants. I then took this result and used it in result mod hashSize to get a 
//   consistant hash key.
//
//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.
//             The funtion worked well with no values being higher then 2.5. With the size of the longest linked list being 26. 
//    with the largest performance ration being 2.25.
//
My hash table real load factor is: 26.00
//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
//          If I were to change my hash function to have fewer collisons. I would probably add more "randomness" to getting the index. 
//    such as using the length of the sting and another multplication of k*fibbinaci number by another prime number.  
********************************************************************************/

#include "Hash.h"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

//This function used to get a Car key which is the combination of model, make and vin
string getKey(string oneLine, string& model, string& make, int& vin);
void getCar(string oneLine, string& model, string& make, int& vin, double& price);
int main()
{
   int size = 0 ;
   int numOfCommand = 0;
   string model, make;
   int vin;
   double price;
   bool success;
   //declare any other necessary variables here
   //----
   string line;
   string line1;
   string insertionEnd = "InsertionEnd";

   cout << "Enter the size of the hash table: ";
   cin >> size;
   cin.ignore(20, '\n');

   //Instantiate the hash table with the relevant number of slots
   Hash* hash1 = new Hash(size);

   // runs a loop where it collects a line of input from the user assuming all values are cars 
   // with the correct input params. Stops the loop when it recves the line "InsertionEnd"
   do {
         getline(cin, line);
         if(line == insertionEnd){
            break;
         }else{
            // pares the string into valid input for insertingthe car into the hash table 
            getCar(line, model, make, vin, price);
            // inserts the car data into the hash tabe
            success = hash1->hashInsert(model, make, vin, price);
         }
   } while(true);

   
   //cout << "\nEnter number of commands: ";   //***need to comment out in submitting

   // grabs the number of commands
   cin >> numOfCommand;
   cin.ignore(20, '\n');
   string firstToken;
   string command;

   
   // lopps through the number of comands 
   for(int i= 0; i < numOfCommand; i++)
   {
   	//get one line command, extract the first token, if only one token
      getline(cin, line);
      
      // creates a copy of the user line input 
      line1 = line;


      // parses the first token of the users input which is assumned to be in the correct format, other wise it 
      // states that it is an invalid command
      string delimiter = ",";
      int pos=line1.find(delimiter);
      string token = line1.substr(0,pos);
      firstToken = token;
      line1.erase(0, pos+delimiter.length());

      pos=line1.find(delimiter);
      token = line1.substr(0,pos);
      command = token;
      line1.erase(0, pos+delimiter.length());

      // if the only token is the first token, then it is assumed the input is one of the two commands being, "hashDisplay" or "hasLoadFactor"
      if(firstToken == command){
         // displays all the values in the hash table
          if(firstToken.compare("hashDisplay") == 0)
         {
            hash1->hashDisplay();
         }
         // prints the ideal load factor, the current load factor and performance ratio which is depenedent on the ideal loak facttor and the actual load factor
         else if(firstToken.compare("hashLoadFactor")==0){
            hash1->hashLoadFactor();
         }
      }
      else  //more than one tokens, check the command name, extract the remaining tokens
      {
         // if the input command is somthing that has several tokens then it will compute the command by parseing the string into the appropriate varibles
         command = getKey(line, model, make, vin);

         // searches the has table for a car that may or may not be in the hash table
         if(command.compare("hashSearch")==0){
            hash1->hashSearch(model, make, vin);
         }

         // deletes a car that is in the hash table or will print out an error message if it is not in the hash, then the program says the car is NOT deleted
         else  if(command.compare("hashDelete")==0){
            hash1->hashDelete(model, make, vin);
         }
         else{
            cout<<"Invalid command"<<endl;
          }
      }
   } //end for loop
   return 0;
}


void getCar(string oneLine, string& model, string& make, int& vin, double& price)
{
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   model = token;
   oneLine.erase(0, pos+delimiter.length());
   
   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   make = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   vin = stoi(token);
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   price = stod(token);
   oneLine.erase(0, pos+delimiter.length());
}

//****************************************************************************************
//Given one line, this function extracts the model, make, vin info. of a Car
//This function is completed and given here as a study guide for extracting tokens

string getKey(string oneLine, string& model, string& make, int& vin)
{
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   string command = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   model = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   make = token;
   oneLine.erase(0, pos+delimiter.length());

    
   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   vin = stoi(token);
   oneLine.erase(0, pos+delimiter.length());

   return command;
}