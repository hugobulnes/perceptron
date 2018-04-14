#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **loadFromFile(char *fileName,int rows,int cols);
char **createTwoD(int rows,int cols);
double randomWeight();
double calcRowNet(int trainingDataCols, char *trainingData, double *weights);
void correctWeights(char* row, int col, double learningRate, double sigma, double *weights);
void displayIterationResults(double errR, int numIterations, double *weights, int numCols);

//////////////////////////////////////////////////////////////////////////////////
int main() {
  //seed the random function  
  srand(time(NULL));
  
  int i;
  int trainingDataRows = 4;
  int trainingDataCols = 4;
  int maxIterations = 10; //number of iterations that are going to be run 
  int numIterations = 0;
  int output;
  int maxError = 0;
  int errC = maxError + 1;
  double sigma;
  double *weights = malloc(sizeof(double)*(trainingDataCols-1)); //17 is the number of columns in the input
  double learningRate = 0.1;
  double netTemp;
  char *fileName = "in.txt";
  
  char **trainingData = loadFromFile(fileName,trainingDataRows,trainingDataCols);

  
  //generating the random weights array
  for(i=0; i< trainingDataCols; i++){
    weights[i] = randomWeight();
  }
  
  
  //Start of iteration
  while(numIterations < maxIterations && !(errC <= maxError)) {
    errC = 0;//Reset error after each iteration
    
    printf("\nIteration %d @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n", numIterations);
    
    for(i =0; i<trainingDataRows; i++) { // Do for each row
      netTemp = calcRowNet(trainingDataCols-1,trainingData[i],weights);//storing the netTotal of each Row
      //printf("netTemp = %f\n",netTemp);
      output = (netTemp>.5) ? 1 : 0;
      
      if(output != (trainingData[i][trainingDataCols-1]-48)) {//checks if weights need to be adjusted,if so then adjusts the weights
        sigma = (trainingData[i][trainingDataCols-1]-48) - output;
        correctWeights(trainingData[i],trainingDataCols-1, learningRate, sigma, weights);
        errC++; // Increase error 
      }//end of if 
      displayIterationResults((double)errC/trainingDataRows,numIterations,weights,trainingDataCols-1);
    }//end of for
    
    
    //displayIterationResults((double)(errC/trainingDataRows),numIterations,weights,trainingDataCols-1);
  
      
    numIterations++; //increase iteration counter
  }//end of while
  
  
  
  
    
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
  //return randNum;
  return 0; //testing 
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



