/**************************************************//**
 * @file StorageManager.cpp
 * @brief Here are defined all methods from StorageManager class
/**************************************************/

/**************************************************/
//Libraries

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <StorageManager.h>

/**************************************************/
//Namespaces

using namespace std;

/**************************************************/
// Public

/*****************************/
// Methods
void storageManager::readFile() {

    ifstream file;
    string text;

    file.open("file.csv", ios::in);
    
    if (file.fail()) {

        cout<<"There has been an error while opening the file."<<endl;
        exit(1);

    }

    while (!file.eof()) {
        getline(file, text, ',');
        cout<<text<<endl;
    }

    file.close();

}

/*********************************************/
//Libraries

/*********************************************/
//Libraries