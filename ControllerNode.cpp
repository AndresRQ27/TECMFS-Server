#include "ControllerNode.h"

string ControllerNode::calcParity(vector<const char*> diskSumsList){
    string finalParity = diskSumsList[0];      //Primero se usa el vector de primer disco
    for (int disk = 1; disk < diskSumsList.size(); disk++){
        finalParity = xorCalc(finalParity, diskSumsList[disk]); //Se aplica XOR para un disco y el siguiente
    }

    return finalParity;
}

string ControllerNode::xorCalc(string disk1, string disk2){
    string returnString = "";
    if (disk1.length() == disk2.length()){
        for (int bit = 0; bit < disk1.length(); bit++){
            if (disk1[bit] != disk2[bit]){     //XOR
                returnString.append("1");
            }
            else{
                returnString.append("0");
            }
        }
    }
    else{       //Si los discos son de diferente tamaño
        string biggestDisk = disk1;
        string smallestDisk = disk2;
        if (biggestDisk.length() < disk2.length()){       //Si el siguiente disco es más grande
            biggestDisk = disk2;
            smallestDisk = disk1;
        }

        const char* defaultFillCharXOR = "0";
        for (int bit = 0; bit < biggestDisk.length(); bit++){
            if ((int)smallestDisk.length() <= bit){       //Cuando se llega al fin del disco pequeño, se empieza a comparar el grande con 0s
                if (biggestDisk[bit] != defaultFillCharXOR[0]){     //Si el bit del disco grande es diferente a 0, en este caso
                    returnString.append("1");
                }
                else{
                    returnString.append("0");
                }
            }
            else{
                if (disk1[bit] != disk2[bit]){
                    returnString.append("1");
                }
                else{
                    returnString.append("0");
                }
            }
        }
    }
    return returnString;
}

string ControllerNode::restoreWithParity(int missingDiskNumber, vector<const char*> allDisks){
    string savedParity = this->parity;
    string parityWithoutMissingDisk = "";       //Después se va usar para comparar con el savedParity
    int firstNotMisDiskSum = 0;

    for (int diskNumber = 0; diskNumber < allDisks.size(); diskNumber++){
        if (missingDiskNumber != diskNumber){
            parityWithoutMissingDisk = allDisks[diskNumber];    //Al principio va a tener la suma del primer disco que no sea el que falta
            firstNotMisDiskSum = diskNumber;
            break;
        }
    }

    for (int disk = 0; disk < allDisks.size(); disk++){     //Se recorre todos los discos, pero no se calcula para el que falta
        if (disk != missingDiskNumber && disk != firstNotMisDiskSum){   //Si no es el disco que falta ni el primero de los discos que no es el que falta
            parityWithoutMissingDisk = xorCalc(parityWithoutMissingDisk, allDisks[disk]);
        }
    }

    //Aplicando el XOR
    string missingDiskData = xorCalc(savedParity, parityWithoutMissingDisk);
    int diskUsedStorage = this->disksStorageUsed[missingDiskNumber];
    if (missingDiskData.length() != diskUsedStorage){
        missingDiskData.erase(diskUsedStorage);
    }

    return missingDiskData;
}

const char* ControllerNode::getDataFromBlock(int diskNumber, int stripeNumber){

}

void ControllerNode::saveToDisk(json sendData, int videoNumber){
    //Se guarda en el Controller un "catálogo"
    if (database.size() == videoNumber){    //Si no espacio para la información de un video, se crea
        vector<string> videoInfo;
        database.push_back(videoInfo);
        database[videoNumber] = {sendData["metadata"], sendData["identifier"]}; //Primero se agrega el título y el primer bloque
    }
    if (database.size() == videoNumber+1){  //Si ya está el espacio para la información de un video
        database[videoNumber].push_back(sendData["identifier"]);    //Sólo se agrega el siguiente bloque que va a tener parte del video
    }

    ///send
}