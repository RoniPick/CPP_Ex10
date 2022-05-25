
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "OrgChart.hpp"
using namespace ariel;

int main() {
  OrgChart organization;
  organization.add_root("Roni")
      .add_sub("Roni", "Anthony")         // Now Anthonr is subordinate to Roni
      .add_sub("Roni", "Sabrina")         // Now Sabrina is subordinate to Roni
      .add_sub("Roni", "Adam")            // Now Adam is subordinate to Roni
      .add_sub("Anthony", "Meir")         // Now the Meir is subordinate to Anthony
      .add_sub("Sabrina", "Barak");       // Now the Barak is subordinate to Sabrina

  cout << organization << endl << endl;


  cout << "Level Order: " ;
  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
    cout << (*it) << " " ;
  } // prints: Roni Anthony Sabrina Adam Meir Barak 

  cout << endl << endl;

  cout << "Reverse Level Order: " ;
  for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it){
    cout << (*it) << " " ;
  } // prints: Meir Barak Anthony Sabrina Adam Roni

  cout << endl << endl;

   cout << "PreOrder: " ;
  for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: Roni Anthony Meir Sabrina Barak Adam

  cout << endl << endl;

  cout << "Level Order: " ;
  for (auto element : organization){ // this should work like level order
    cout << element << " " ;
  } // prints: Roni Anthony Sabrina Adam Meir Barak


  cout << endl;
  cout << endl;

cout << "Size of each name in Level Order: " ;
  // demonstrate the arrow operator:
  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
    cout <<it->size() << " " ;
  } // prints: 4 7 7 4 4 5
    cout << endl;

}