#include <iostream>
#include <fstream>
#include <time.h>

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

int main() {

  int increase = 200;
  int size;
  clock_t time1, time2;
  float timeDiff;
  float total = 0;

  ofstream output;
  output.open("mergeTime.out");

  srand(time(NULL));

  for(int i=1; i<11 ;i++){

      size = increase*i;
      output << size << " ";
      total =0;
      int array[size];

      for(int j=0; j<5; j++){

        for(int k=0; k<size; k++){
          array[k] = rand()%10001;
        }
        time1 = clock();
        mergeSort(array, 0, size-1);
        time2 = clock();

        timeDiff = ((float)time2 - (float)time1)/CLOCKS_PER_SEC;
        output << timeDiff << " ";

        total = total+timeDiff;
      }
      printf("Size: %d, Average: %f\n",size, total/5);
      output << total/5 << "\n";
  }

  output.close();
  return 0;
}
