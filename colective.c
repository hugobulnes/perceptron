/*
Timothy Tea timea1337@gmail.com
Aldair Hernandez a.hernandez3270@gmail.com
Hugo Blnes hb0624267@swccd.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **loadFromFile(char *fileName,int rows,int cols);
char **createTwoD(int rows,int cols);
double randomWeight();
double calcRowNet(int trainingDataCols, char *trainingData, double *weights);
void correctWeights(char* row, int col, double learningRate, double sigma, double *weights);
void displayIterationResults(double errR, int numIterations, double *weights, int numCols);
void displayFinal (int iterationNum, double iterationP, int errC, double *weights,int numCols);

//////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {//takes command line args
  //seed the random function
  srand(time(NULL));

  int i;
  int trainingDataRows = 128;
  int trainingDataCols = 17;
  int maxIterations = 500000; //number of iterations that are going to be run
  int numIterations = 0;
  int output;
  int maxError = 5;//argv[3]
  int errC = 0;
  double errP = (double)maxError/100;
  double iterationP = 1;
  double sigma;
  double *weights = malloc(sizeof(double)*(trainingDataCols-1)); //17 is the number of columns in the input
  double learningRate = 0.0005; //argv[2]
  double netTemp;
  char *fileName = "in.txt"; //argv[1]

  char **trainingData = loadFromFile(fileName,trainingDataRows,trainingDataCols);


  //generating the random weights array
  for(i=0; i< trainingDataCols; i++){
    weights[i] = randomWeight();
  }


  //Start of iteration
  while(numIterations < maxIterations && !(iterationP <= errP)) {
    errC = 0;//Reset error after each iteration

   // printf("\nIteration %d @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n", numIterations);

    for(i =0; i<trainingDataRows; i++) { // Do for each row
      netTemp = calcRowNet(trainingDataCols-1,trainingData[i],weights);//storing the netTotal of each Row
      output = (netTemp>.5) ? 1 : 0;

      if(output != (trainingData[i][trainingDataCols-1]-48)) {//checks if weights need to be adjusted,if so then adjusts the weights
        sigma = (trainingData[i][trainingDataCols-1]-48) - output;
        correctWeights(trainingData[i],trainingDataCols-1, learningRate, sigma, weights);
        errC++; // Increase error
      }//end of if
      //displayIterationResults((double)errC/trainingDataRows,numIterations,weights,trainingDataCols-1);
    }//end of for
    //displayIterationResults((double)errC/trainingDataRows,numIterations,weights,trainingDataCols-1);
    //printf("%d\n\n", errC);
    numIterations++; //increase iteration counter
    iterationP = (double)errC/trainingDataRows;
  }//end of while

 displayFinal(numIterations,iterationP,errC,weights,trainingDataCols-1);



  return 0;
}
/////////////////////////////////////////////////////////////////////////////End of Main




/////////////////////////////////////////////////////////////////////////////////////
double calcRowNet(int trainingDataCols, char *trainingData, double *weights){

  double dot = 0.0;
  int i;
  for(i =0; i<trainingDataCols; i++){
    dot += (trainingData[i]-48)*weights[i]; //adds the answers to the variable dot
  }

  return dot; //returns the dot product

}
////////////////////////////////////////////////////////////////////End of calcRowNet



////////////////////////////////////////////////////////////////
char **loadFromFile(char *fileName,int rows,int cols) {
    char lineRead[100];
    char **temp = createTwoD(rows,cols);

    FILE *puzzleFile = fopen(fileName, "r");   //open a file from user for reading

    if( puzzleFile == NULL) {
        printf("File not found");
        exit(1);
    }
        int i =0,j,colCount;// i keep track of rows, j keep track of col of, colCount is only made to get rid of a comma
  while( fgets(lineRead, 100, puzzleFile) != NULL){
        if(lineRead[0] == '\n')
            continue;
        colCount =0;//reset colCount

        //loading a 2D array with the values read from the file
        for(j =0; j<cols;) {
            if(lineRead[colCount] != ',') {
                temp[i][j] = lineRead[colCount];
                //printf("%c ",temp[i][j]);
                j++;//added here so there is no overflow when encounters comma
                //printf("colCount = %d  i = %d  j = %d\n",colCount,i,j);
            }
            colCount++;
        }
        //printf("\n");
        i++;//moves on to the next row

  }//end of while

  fclose(puzzleFile);

  return temp;
}
//////////////////////////////////////////////////////////////////////End of loadFromFile()



/////////////////////////////////////////////////////////////////////////////////////////
//This function return a random number from 0 - 1
double randomWeight(){
  //create a random number in the range of 0 -100
  int temp = rand() %100;
  double randNum = (temp * 1.0 /100);
  return randNum;

}
//////////////////////////////////////////////////////////////////////End of randomWeight()


//////////////////////////////////////////////////
char **createTwoD(int rows,int cols) {

    char **trainingData = malloc(sizeof(int)*rows);
    int i;
    for(i=0; i<rows; i++) {
        trainingData[i] = malloc(sizeof(int)*cols);
    }
    return trainingData;
}
//////////////////////////////////////////////////End of createTwoD

/////////////////////////////////////////////////////////end of displayIterationResults
void displayIterationResults(double errR, int numIterations, double *weights, int numCols){
  int i;
  for(i = 0; i < numCols; i++)
    printf("%.1f ", weights[i]); // Print Weights
  printf("   Iteration Error = %.2f\n", errR); //Print Iteration Error
}

/////////////////////////////////////////////////////////end of displayIterationResults

//////////////////////////////////////////////////
//Correct the weights
//@param row, the input row
//@param col, number of columns
//@param learningRate, learning rate
//@param output, the output from the dot product function
//@param weights, the weights array
void correctWeights(char* row, int col, double learningRate, double sigma, double *weights) {
  int i;
  for(i=0; i< col; i++){
    *(weights+i) += (row[i]-48) * learningRate * sigma;
  }

}
//////////////////////////////////////////////////end of correctWeights()


void displayFinal (int iterationNum, double iterationP, int errC, double *weights, int numCols){
  printf("IterationError = %.9f,  errCnt = %d,  repNum = %d\n\n", iterationP, errC, iterationNum);
   int i;
  for(i = 0; i < numCols; i++)
    printf("wt[%d]: %f   \n",i, weights[i]); // Print Weights
}

