#include "doctest.h"
#include "sources/OrgChart.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <iterator>

using namespace ariel;
using namespace std;

TEST_CASE("Good input"){
    OrgChart organization;
    organization.add_root("Roni");
    CHECK_EQ(organization.get_root(), "Roni");

    //Lior is under Roni
    organization.add_sub("Roni", "Lior");
    //Gal is under Roni
    organization.add_sub("Roni", "Gal");
    //Itzik is under Gal
    organization.add_sub("Gal", "Itzik");
    //Dana is under Lior
    organization.add_sub("Lior", "Dana");

    ///LEVEL ORDER///
    vector<string> ans1 = {"Roni", "Lior", "Gal", "Itzik", "Dana"};
    vector<string> v1 = {"1", "2", "3", "4", "5"};
    size_t i=0;
    //Adding each name into a help vector
    for(auto it=organization.begin_level_order(); it!=organization.end_level_order(); it++){
        v1[i] = *(it);
        i++;
    }

    //Checking each value if it is in the currect place
    for(size_t i=0; i<ans1.size(); i++){
        CHECK_EQ(ans1[i], v1[i]);
    }


    ///REVERSE ORDER///
    vector<string> ans2 = {"Dana", "Itzik", "Gal", "Lior", "Roni"};
    vector<string> v2 = {"1", "2", "3", "4", "5"};
    i=0;
    //Adding each name into a help vector
    for(auto it=organization.begin_reverse_order(); it!=organization.end_reverse_order(); it++){
        v2[i] = *(it);
        i++;
    }

    //Checking each value if it is in the currect place
    for(size_t i=0; i<ans2.size(); i++){
        CHECK_EQ(ans2[i], v2[i]);
    }


    ///PREORDER///
    vector<string> ans3 = {"Roni", "Lior", "Dana", "Gal", "Itzik"};
    vector<string> v3 = {"1", "2", "3", "4", "5"};
    i=0;
    //Adding each name into a help vector
    for(auto it=organization.begin_preorder(); it!=organization.end_preorder(); it++){
        v3[i] = *(it);
        i++;
    }

    //Checking each value if it is in the currect place
    for(size_t i=0; i<ans3.size(); i++){
        CHECK_EQ(ans3[i], v3[i]);
    }


    ///changing the name of the root
    organization.add_root("Shachar");
    CHECK_NE(organization.get_root(), "Roni");
    CHECK_EQ(organization.get_root(), "Shachar");

}



TEST_CASE("Wrong checks"){
    OrgChart organization;
    organization.add_root("Roni");

    //adding sub under someone who doesnt in the tree
    CHECK_THROWS(organization.add_sub("Aviv", "Lior"));
    CHECK_THROWS(organization.add_sub("Gal", "Yam"));


    //Lior is under Roni
    organization.add_sub("Roni", "Lior");
    //Gal is under Roni
    organization.add_sub("Roni", "Gal");
    //Itzik is under Gal
    organization.add_sub("Gal", "Itzik");
    //Dana is under Lior
    organization.add_sub("Lior", "Dana");


    ///Adding to the vector in REVERSE ORDER, checking vs LEVEL ORDER///
    vector<string> ans1 = {"Roni", "Lior", "Gal", "Itzik", "Dana"};
    vector<string> v1 = {"1", "2", "3", "4", "5"};
    size_t i=0;
    //Adding each name into a help vector
    for(auto it=organization.begin_reverse_order(); it!=organization.end_reverse_order(); it++){
        v1[i] = *(it);
        i++;
    }

    //Checking each value if it is in the currect place
    for(size_t i=0; i<ans1.size(); i++){
        CHECK_NE(ans1[i], v1[i]);
    }


     ///Adding to the vector in LEVEL ORDER, checking vs REVERSE ORDER///
    vector<string> ans2 = {"Dana", "Itzik", "Gal", "Lior", "Roni"};
    vector<string> v2 = {"1", "2", "3", "4", "5"};
    i=0;
    //Adding each name into a help vector
    for(auto it=organization.begin_reverse_order(); it!=organization.end_reverse_order(); it++){
        v2[i] = *(it);
        i++;
    }

    //Checking each value if it is in the currect place
    for(size_t i=0; i<ans2.size(); i++){
        CHECK_NE(ans2[i], v2[i]);
    }

}