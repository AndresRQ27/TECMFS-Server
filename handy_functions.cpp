//
// Created by sebas97012 on 12/1/17.
//

#include "handy_functions.h"

std::string handy_functions::toBinary(std::string uCharBytes) {
    std::string string;
    std::string bits;
    for (int i = 0; i < uCharBytes.size(); i++) {
        bits = std::bitset<8>(uCharBytes[i]).to_string();
        string+=bits;
    }
    return string;
}

void handy_functions::Write(std::string N, std::string fileName, std::string extension) {
    fileName=fileName+extension;
    const char * c = fileName.c_str();
    std::ofstream out;
    out.open(c, std::ios::app);
    out<<N;
    out.close();
}

std::string handy_functions::LoadVideo(std::string filename) {
    std::ifstream file(filename,std::ios::binary);
    std::vector<byte> vector((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    std::string str(vector.begin(),vector.end());
    file.close();
    return str;
}

std::string handy_functions::binaryToVideo(std::string binary) {
    std::string videoChars;
    for (int i = 0; i < binary.size(); i += 8) {
        std::string chaR;
        for (int j = 0; j < 8; j++)
            chaR += binary[i + j];
        unsigned char c1 = static_cast<unsigned char>(std::stoi(chaR, nullptr, 2));
        chaR.erase();
        videoChars += c1;
    }
    return videoChars;
}
