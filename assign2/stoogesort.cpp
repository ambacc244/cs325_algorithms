#include <iostream>
#include <fstream>
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

  ifstream input;
  input.open("data.txt");

  ofstream output;
  output.open("stooge.out");

  int size;

  while(input >> size){

    int array[size];

    for(int i=0; i<size; i++)
      input >> array[i];

    stoogeSort(array, 0, size-1);

    for(int i=0; i<size; i++)
      output<<array[i]<<" ";

    output<<"\n";
  }

  input.close();
  output.close();

  return 0;
}
