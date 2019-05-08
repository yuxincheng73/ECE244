/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: chengy73
 *
 * Created on November 29, 2018, 7:12 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string line, command;
    TreeDB tree;
    
    cout << "> ";
    
    getline(cin, line); 
    
    while(!cin.eof()) {
        //read user input
        stringstream lineStream(line);
        lineStream >> command;
        
        //parse the command
        if(command == "insert") {
            //parse the input
            string name, readActive;
            unsigned int IPaddress;
            bool active = false;
            
            lineStream >> name >> IPaddress >> readActive;
            if(readActive == "active")
                active = true;
            
            //create a new dbentry to be inserted
            DBentry* input = new DBentry(name, IPaddress, active);
            
            //insert node and print
            if(tree.insert(input))
                cout << "Success" << endl;
            else {
                cout << "Error: entry already exists" << endl;
                delete input;
            }
        }
        else if(command == "find") {
            //parse the input
            string name;
            lineStream >> name;
            DBentry* result = tree.find(name);
            
            //find the node and print it or print an error
            if(result == NULL) {
                cout << "Error: entry does not exist" << endl;
            }
            else 
                cout << *result << endl;
        }
        else if(command == "remove") {
            //parse the input
            string name;
            lineStream >> name;
            
            //remove the node and print success or an error
            if(tree.remove(name)) {
                cout << "Success" << endl;
            }
            else
                cout << "Error: entry does not exist" << endl;
        }
        else if(command == "printall") {
            //print all nodes
            cout << tree;
        }
        else if(command == "printprobes") {
            //parse the input
            string name;
            lineStream >> name;
            
            //print the number of probes or an error
            if(tree.find(name) == NULL)
                cout << "Error: entry does not exist" << endl;
            else 
                tree.printProbes();
        }
        else if(command == "removeall") {
            //delete everything
            tree.clear();
            cout << "Success" << endl;
        }
        else if(command == "countactive") {
            //count the nodes active and print them
            tree.countActive();
        }
        else if(command == "updatestatus") {
            //parse the input
            string name, readActive;
            bool active = false;
            lineStream >> name >> readActive;
            if(readActive == "active")
                active = true;
            
            //update active and print or an error
            if(tree.find(name) == NULL)
                cout << "Error: entry does not exist" << endl;
            else {
                tree.find(name)->setActive(active);
                cout << "Success" << endl;
            }
        }
        //if command doesn't match any of the above
        else {
            cout << "Error: Invalid command" << endl;
        }
        
        //next user input
        lineStream.clear();
        lineStream.ignore(1000, '\n');
        cout << "> ";
        getline(cin, line);
    }
    return 0;
}

