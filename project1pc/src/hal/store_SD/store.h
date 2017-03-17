/*
 * Store.h
 *
 *  Created on: 11/12/2016
 *      Author: Prueba
 */

#ifndef STORE_H_
#define STORE_H_



int STORE_storeInSD(char * newStr);
void STORE_storeInFile(char * data);

#define MAXIMUM_ARRAY 6000 //con este l�mite guardamos cada 10 segundos aprox.
#define MAXIMUM_CHARAC 60

#endif /* STORE_H_ */
