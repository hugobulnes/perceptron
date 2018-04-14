#include <stdio.h>

float vectorMultiplication(float *row, int l, float *weights);
void weightsCorrection(float *row, int l, float *weights, float r, float sigma);


int main(void){
	
	// Initial variables
	const float T = 0.5;
	const float r = 0.1;
	int nRows = 4;
	int nCols = 3;

	float w[3] = {0,0,0};
	float inputs[4][3] = {
		{ 1,0,0 },
		{ 1,0,1 },
		{ 1,1,0 },
		{ 1,1,1 }
	};
	float desiredOutput[4] = { 1,1,1,0 };

	float net, sigma;
	float iterError = 100;
	int iterCounter = 0;

	//Function
	while(iterError > 0){ //check if desiredOutput true

		printf("Iteration : %d **********************\n", iterCounter);

		iterError = 0; //restart iterError

		for(int i = 0; i < nRows; i++){
			net = vectorMultiplication(inputs[i], nCols, w, T);

			sigma = net > T ? 1 : 0;//Threshold comparison

			//Check if desired != actual
			if(desiredOutput[i] != sigma){
				sigma = desiredOutput[i] - sigma;
				weightsCorrection(inputs[i], nCols, w, r, sigma);
				iterError += 0.25;
			}
			
			printf(" %.*f, %.*f, %.*f,  iterationError: %f \n", 
					1, w[0], 1, w[1], 1, w[2], iterError);
			
		}
		iterCounter++;
	}	

	return 0;
}

//Correct the weights array
void weightsCorrection(float *row, int l, float *weights, float r, float sigma){
	for(int i = 0; i < l; i++){
		*(weights+i) += *(row+i) * r * sigma;
	}
}

//Calculate NET value
float vectorMultiplication(float *row, int l, float *weights){

	float net = 0;
	
	for(int i = 0; i < l; i++){
		net += *(row+i) * *(weights+i);
	}
	return net;
}
