#ifndef TECMFS_CONTROLLERNODE_H
#define TECMFS_CONTROLLERNODE_H

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class ControllerNode{
public:
    int cantDisks;
    float diskSize;
    int cantBlocks;             //Cantidad de bloques en los que se divide cada disco. Igual a cantDisks para que la diagonal tenga la paridad ///
    float blockSizeBits;         //Tamaño de todos los bloques

    string parity;              //Se usa para guardar paridad y calcular los discos
    vector<int> disksStorageUsed;   //Tamaño en bits del espacio ocupado en el disco
    json database;


    string calcParity(vector<const char*> diskSumsList);    //Calcula la paridad entre todos los discos
    string xorCalc(string disk1, string disk2);

    //Para enviar videos a la aplicación de prueba
    void sendVideoData(int stripeNumber);          //Devuelve la información contenida en todos los bloques que contienen un video
    const char* getDataFromBlock(int diskNumber, int stripeNumber);  //Devuelve los datos binarios de un bloque específico

    string restoreWithParity(int missingDiskNumber, vector<const char*> allDisks);      //Da el valor en binario del vector del disco
};


#endif //TECMFS_CONTROLLERNODE_H