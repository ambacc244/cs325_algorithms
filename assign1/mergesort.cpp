#include <iostream>
#include <fstream>

using namespace std;

void mergeArray(int *array, int left, int middle, int right){

    int size1 = middle-left+1;
    int size2 = right-middle;

    int leftArray[size1];
    int rightArray[size2];

    for(int i=0; i<size1; i++)
        leftArray[i] = array[left+i];

    for(int j=0; j<size2; j++)
        rightArray[j] = array[middle+1+j];

    int indexLeft = 0;
    int indexRight = 0;
    int indexBoth = left;

    while(indexLeft<size1 && indexRight<size2){

      if(leftArray[indexLeft] > rightArray[indexRight]){
        array[indexBoth] = rightArray[indexRight];
        indexRight++;
      }
      else{
        array[indexBoth] = leftArray[indexLeft];
        indexLeft++;
      }
      indexBoth++;
    }

    while (indexLeft < size1){
        array[indexBoth] = leftArray[indexLeft];
        indexLeft++;
        indexBoth++;
    }

    while (indexRight < size2){
        array[indexBoth] = rightArray[indexRight];
        indexRight++;
        indexBoth++;
    }
}

void mergeSort(int *array, int left, int right){

  int middle = left + (right-left)/2;

  if(left<right){

    mergeSort(array, left, middle);
    mergeSort(array, middle+1, right);

    mergeArray(array, left, middle, right);
  }
}

int main(){

  ifstream input;
  input.open("data.txt");

  ofstream output;
  output.open("merge.out");

  int size;

  while(input >> size){

    int array[size];

    for(int i=0; i<size; i++)
      input >> array[i];

    mergeSort(array, 0, size-1);

    for(int i=0; i<size; i++)
      output<<array[i]<<" ";

    output<<"\n";
  }

  input.close();
  output.close();

  return 0;
}
