#ifndef TECMFS_CONTROLLERNODE_H
#define TECMFS_CONTROLLERNODE_H

class ControllerNode{
public:
    int cantDisks;
    float diskSize;
    int cantBlocks;             //Cantidad de bloques en los que se divide cada disco. Igual a cantDisks para que la diagonal tenga la paridad ///
    float blockSizeBits;         //Tamaño de todos los bloques

    void sendStripeData(int stripeNumber);          //Devuelve la información contenida en todos los bloques del stripe
    const char* getDataFromBlock(int diskNumber, int stripeNumber);  //Devuelve los datos binarios de un bloque específico

    const char* getMeta(int diskNumber);
    const char* parseMeta();
    int getDiskByMeta();

    //
};


#endif //TECMFS_CONTROLLERNODE_H