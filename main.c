/*
 * main.c
 *
 *  Created on: Nov 29, 2018
 *      Author: philipchen
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool checkIfAllNodesVisited(bool* test);

int main(){

	/*
	 * Setting up the weight matrix
	 */
	const int maxSize = 128;
	const char delimiters[] = " \n\t"; // used for string tokenizer
	char* tokenizer; // the tokenizer to break each line
	char inLine[maxSize];
	int line = 0;
	int maxLines = 0;
	FILE* infile;
	char userInput;
	char userInput2;

	printf("Enter a starting node (between A-H): ");
	scanf(" %c", &userInput);
	printf("Enter an ending node (between A-H): ");
	scanf(" %c", &userInput2);

	// The if statement is just to uppercase the letters based on ascii code
	if(userInput >= 97 && userInput <= 104){
			userInput = userInput - 32;
	}
	if(userInput2 >= 97 && userInput2 <= 104){
				userInput2 = userInput2 - 32;
	}

	// change the file path
	infile = fopen("/Users/philipchen/Desktop/WeightMatrix.txt", "r");

	while(!feof(infile)){
		fgets(inLine, maxSize, infile); // get a line from the file
		maxLines++;
	}

	// reset the pointer to beginning of file
	rewind(infile);

	/*
	 * For the main algorithm
	 */
	int weightMatrix[maxLines-1][maxLines-1]; // minus 1 since we do not want to store the first line of file
	int nextNode = -1;
	int distance[maxLines - 1];
	int path[maxLines-1];
	bool visitedNode[maxLines -1];
	int startNode = userInput - 65;
	int endNode = userInput2 - 65;
	int min = 999;

	/*
	 * Storing the data into the weight matrix
	 */
	while(!feof(infile)){
		int temp = 0; // used to not take the first character of every line
		fgets(inLine, maxSize, infile);
		if(line > 0){
			tokenizer = strtok(inLine, delimiters);
			while(tokenizer != NULL){
				if(temp > 0){
					int tempInt = atoi(tokenizer);
					if(tempInt == 0){
						tempInt = 999;
					}
					// minus 1 since we do not want to store the first char of each line
					// and the first line of the file is just a 'filler'
					weightMatrix[line - 1][temp - 1] = tempInt;
				}
				tokenizer = strtok(NULL, delimiters);
				temp++;
			}
		}
		line++;
	}

	while((userInput >= 'A' && userInput <= 'H') && (userInput2 >= 'A' && userInput2 <= 'H')){
		/*
			 * the main algorithm
			 */
			// initialize the arrays
			for(int i = 0; i < maxLines - 1; i++){
				distance[i] = weightMatrix[startNode][i];
				path[i] = userInput - 'A'; // change to -1 later
				visitedNode[i] = false;
			}
			visitedNode[startNode] = true;

			while(!checkIfAllNodesVisited(visitedNode)){
				for(int col = 0; col < maxLines - 1; col++){
					if((visitedNode[col] == false) && distance[col] < min){
						min = distance[col];
						nextNode = col;
					}
				}
				visitedNode[nextNode] = true;
				distance[nextNode] = min;
				for(int i = 0; i < maxLines - 1; i++){
					if((visitedNode[i] == false) && (weightMatrix[nextNode][i] + min < distance[i])){
						distance[i] = weightMatrix[nextNode][i] + min;

						// the previous node that will go to that specified node
						path[i] = nextNode;
					}
				}
				min = 999;
			}

			distance[startNode] = 0;

			printf("The weight cost from %c to %c is: %d\n", userInput, userInput2, distance[endNode]);

			int k = endNode;
			int index = 0;
			int tempArray[maxLines - 1];
			while(k != userInput - 'A'){
				tempArray[index] = k;
				k = path[k];
				index++;
			}

			/*
			 * printing the route
			 */
			printf("The shortest route from %c to %c is: \n", userInput, userInput2);
			printf("%c->", startNode + 'A');
			for(int i = index - 1; i >= 0; i--){
				if(i == 0){
					printf("%c\n", tempArray[i] + 'A');
				}
				else{
					printf("%c->", tempArray[i] + 'A');
				}
			}

			// prompt user to input again
			printf("Enter a starting node (between A-H): ");
			scanf(" %c", &userInput);
			printf("Enter an ending node (between A-H): ");
			scanf(" %c", &userInput2);
			if(userInput >= 97 && userInput <= 104){
					userInput = userInput - 32;
			}
			if(userInput2 >= 97 && userInput2 <= 104){
						userInput2 = userInput2 - 32;
			}
			startNode = userInput - 65;
			endNode = userInput2 - 65;
	}
	fclose(infile);

	return 0;
}

bool checkIfAllNodesVisited(bool* test){
	for(int i = 0; i < sizeof test; i++){
		if(test[i] == false){
			return false;
		}
	}
	return true;
}

