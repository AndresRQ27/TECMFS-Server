//
// Created by sebas97012 on 12/1/17.
//

#ifndef TECMFS_SERVER_HANDY_FUNCTIONS_H
#define TECMFS_SERVER_HANDY_FUNCTIONS_H

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <bitset>
typedef unsigned char byte;

class handy_functions {
public:
   static std::string toBinary(std::string uCharBytes);
    static void Write(std::string N,std::string fileName,std::string extension);
    static std::string LoadVideo(std::string filename);
    static std::string binaryToVideo(std::string binary);

};


#endif //TECMFS_SERVER_HANDY_FUNCTIONS_H
