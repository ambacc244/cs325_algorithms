#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include<math.h>

using namespace std;

void stoogeSort(int *array, int left, int right){

  int size = right-left+1;

  if(size == 2 && array[left] > array[right])
    swap(array[left],array[right]);
  else if(size > 2){
      int m = floor(size/3);

      stoogeSort(array,left, right-m);
      stoogeSort(array,left+m, right);
      stoogeSort(array,left, right-m);
  }
}

int main() {

  int increase = 200;
  int size;
  clock_t time1, time2;
  float timeDiff;
  float total = 0;

  ofstream output;
  output.open("stoogeTime.out");

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
        stoogeSort(array, 0, size-1);
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
