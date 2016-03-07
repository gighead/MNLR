/*
 * fwdAlgorithm.c
 *
 *  Created on: May 1, 2015
 *      Author: tsp3859
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fwdAlgorithmHelper.h"
#include "boolean.h"
#include "tierUtils.h"

char *fwdInterface = NULL;
char *fwdTierAddr = NULL;
int fwdSet = -1;

extern boolean containsTierAddress(char testStr[20]);
extern int getTierValue(char strCheck[]);
extern boolean setByTierPartial(char inTier[20], boolean setFWDFields);
extern boolean setByTierOnly(char inTier[20], boolean setFWDFields);
extern boolean setByTierManually(char inTier[20], boolean setFWDFields);
extern int getUniqueChildIndex(char strCheck[]);

int packetForwardAlgorithm(char currentTier[], char desTier[]);
boolean optimusForwardAlgorithm(char currentTier[], char desTier[]);
boolean algorithmOptimusG(char currentTier[], char desTier[],
		int tierValueCurrent);
boolean algorithmG2(char currentTier[], char desTier[]);
boolean algorithmG3(char currentTier[], char desTier[]);
boolean algorithmG4(char currentTier[], char desTier[]);

/**
 * packetForwardAlgorithm(char[],char[])
 *
 * method to perform packet forwarding
 *
 * @param currentTier (char[]) - current tier address
 * @param desTier     (char[]) - destination tier address
 *
 * @return returnValue   (int) - algorithm return value (-1/0/1)
 */
int packetForwardAlgorithm(char currentTier[], char desTier[]) {

	//printf("Entering packetForwardAlgorithm \n");

	int returnValue = -1;
	boolean checkOFA = false;


	if ((strlen(currentTier) == strlen(desTier))
			&& ((strncmp(currentTier, desTier, strlen(currentTier)) == 0))) {

		// case1

		printf("Case: 1 \n");
		boolean checkFWDSet =setByTierManually(desTier,true);

		if (checkFWDSet == true) {

			checkOFA = true;
			fwdSet = 0;
			returnValue = 0;

		} else {

			//printf("ERROR: Failed to set FWD Tier Address (Case: 1)\n");
			fwdSet = 1;
			returnValue = 1;
		}

	} else {

		if (containsTierAddress(desTier) == true) {

			// Case2

			printf("Case: 2 \n");

			printf("TEST: containsTierAddress - return value - true \n");
			boolean checkFWDSet = setByTierOnly(desTier, true);

			if (checkFWDSet == true) {

				checkOFA = true;
				fwdSet = 0;
				returnValue = 0;

			} else {

				printf("ERROR: Failed to set FWD Tier Address (Case: 2)\n");
				fwdSet = 1;
				returnValue = 1;
			}

		} else {

			//Goto case3
			/*
			Check 3:
			Is  (My_TV ==  Dest_TV)  && TV == 1
			Process 1: Full mesh topology
              	Check my neighbor table
              	Dest_Label is in my neighbor table
				Forward the MPLR encapsulated packet to the port of access corresponding to the Dest_Label
				Not in my neighbor table – goto Process 2
				Process 2: Linear topology
				              	Check My_UID, Dest_UID
				If (My_UID < Dest_UID )  
				Send MNLR packet to TV.(My_UID + 1 )
				Else  - Send MNLR packet to TV.( My_UID -1) }

			*/

			int myTierValue = atoi(currentTier[0]);
			int destTierValue = atoi(desTier[0]);

			printf("Case: 3 \n");
			if( (myTierValue == destTierValue) && (myTierValue == 1)) {

				//case3A
				if (containsTierAddress(desTier) == true) {

					// same as case2
					printf("Case: 3A \n");

					printf("TEST: containsTierAddress - return value - true \n");
					boolean checkFWDSet = setByTierOnly(desTier, true);

					if (checkFWDSet == true) {

						checkOFA = true;
						fwdSet = 0;
						returnValue = 0;

					} else {

						printf("ERROR: Failed to set FWD Tier Address (Case: 2)\n");
						fwdSet = 1;
						returnValue = 1;
					}

				} else {

					//Goto case3B
					char curUID[20];
					char destUID[20];
					char nextUID[20];
					getUID(curUID,currentTier);
					getUID(destUID,desTier);
					boolean checkUIDComp = false;

					checkUIDComp = compareUIDs(curUID,destUID)){ // curUID is smaller

					if(checkUIDComp){

						//formNextUID(nextUID,curUID,true); //+1 case

					}
					else{
						
						//formNextUID(nextUID,curUID,false); //-1 case

					}

					//sendPacketTo Next UID




			}

			
			if()


	}	

	return returnValue;
}

boolean compareUIDs(char* curUID,char* destUID) {

	//compare the UID's of both current NOde and the destination node
	int ic =0;
	int id = 0;
	char curPart[20];
	char destPart[20];
	int k;

	while(curUID[ic]! = '/0' && destUID[id]! = '/0' ){

		k  =0;
		while(curUID[ic]! = '/0' && curUID[ic]! = '.'){
			curPart[k++] = curUID[ic];
			ic++;
		}
		curPart[k++] = '/0';

		k  =0;
		while(destUID[id]! = '/0' && destUID[id]! = '.'){
			destPart[k++] = curUID[ic];
			id++;
		}
		destPart[k++] = '/0';

		int curPartVal = getValFromString(curPart);
		int destPartVal = getValFromString(destPart);

		if(curPartVal < destPartVal)
			return True;
		else if(curPartVal > destPartVal)
			return False;
		else{
			//equal case 
			//continue
			ic++;
			id++;
			memset(curPart,'/0');

			memset(destPart,'/0');
		}
			


	}

	if(destUID[id]! = '/0' )
		return false;

	return true; //Should never come to this case as destID is always > curID length
	
	//compare the parts (1 < 2)
	//return True if MyUID is < Dest UID

}

void getUID(char* curUID,char* currentTier){

	int i = 0;
	////Truncate and store the truncated part as the Tier value the UID's of both the current and the destination 

	while(currentTier[i] != '.'){
		i++;

	}
	i = i+1;

	int k = 0;

	while(currentTier[i] != '\0'){
			curUID[k] = currentTier[i];
			i++;
			k++;

	}



}


