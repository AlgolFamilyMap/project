//
//  FamilyMap.hpp
//  familyMap
//
//  Created by 동국4조 on 2016. 4. 10..
//  Copyright © 2016년 동국4조. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;

#ifndef FamilyMap_h
#define FamilyMap_h

struct treeNode{
    int level; // 항렬
    string myName; // my name
    string parentName; // parent name
    string wifeName; // wife name
    treeNode* bro; // level node
    treeNode* son; // chile node
};


class FamilyMap{
    
private:
    treeNode *root, *dummy;
    
public:
    FamilyMap(); // construct
    ~FamilyMap(); // destruct
    // 항렬, my name, father name, wife name(default " ")
    void insert(int level, string myName, string parentName, string wife = " ");
    void remove(int level, string myName); // delete node and chilren
    void printMap(); // family map print
    
    bool empty(); // is map empty?
    void printMenu(); // menu consol print
    
    /* add error detecting function */
};

#endif /* FamilyMap_hpp */