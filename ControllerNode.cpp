#include "ControllerNode.h"

void ControllerNode::sendStripeData(int stripeNumber){    //Devulve la información contenida en todos los bloques del stripe
    const char* StripeData;
    for (int currentDiskNumber = 0; currentDiskNumber < cantDisks; currentDiskNumber++){
        const char* blockData = getDataFromBlock(currentDiskNumber,stripeNumber);
        if (blockData == ""){       //Cuando se reciba vacío, significa que no hay datos en los siguientes bloques

        }
    }
}

const char* ControllerNode::getDataFromBlock(int diskNumber, int stripeNumber){

}