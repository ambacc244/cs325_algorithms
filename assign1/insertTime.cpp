#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void insertionSort(int *array, int size){

  int index;
  int val;

  for(int i=1; i<size; i++){

    val = array[i];
    index = i-1;

    while(index >= 0 && array[index] > val){
        array[index+1] = array[index];
        index--;
      }
      array[index+1] = val;
  }
}

int main() {

  int increase = 200;
  int size;
  clock_t time1, time2;
  float timeDiff;
  float total = 0;

  ofstream output;
  output.open("insertTime.out");

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
        insertionSort(array, size);
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
