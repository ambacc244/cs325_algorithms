#include <iostream>
#include <fstream>

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

  ifstream input;
  input.open("data.txt");

  ofstream output;
  output.open("insert.out");

  int size;

  while(input >> size){

    int array[size];

    for(int i=0; i<size; i++)
      input >> array[i];

    insertionSort(array, size);

    for(int i=0; i<size; i++)
      output<<array[i]<<" ";

    output<<"\n";
  }

  input.close();
  output.close();

  return 0;
}
