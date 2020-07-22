#include <iostream>
#include <fstream>

using namespace std;

void sort(int array[][3], int size){

  int index;
  int val[3];

  for(int i=1; i<size; i++){

    val[0] = array[i][0];
    val[1] = array[i][1];
    val[2] = array[i][2];
    index = i-1;

    while(index >= 0 && array[index][1]  <= val[1]){

      if(array[index][1]  == val[1] && array[index][2] >  val[2]){
        break;
      }

      array[index+1][0] = array[index][0];
      array[index+1][1] = array[index][1];
      array[index+1][2] = array[index][2];
      index--;
    }
    array[index+1][0] = val[0];
    array[index+1][1] = val[1];
    array[index+1][2] = val[2];
  }
}

int *findActivities(int array[][3], int size){

  int temp[size];
  int *result = new int[size];
  int index;

  for(int i=0; i<size; i++)
      temp[i]=0;

  for(int i=0; i<size; i++){

    for(int j=0; j<size; j++)
      if(temp[j] == 0){
          temp[j] = 2;
          index = j;
          break;
      }

    for(int j=index+1; j<size; j++){

      if(temp[j] == 0 && ((array[index][1] == array[j][1] && array[index][2] == array[j][2]) || (array[index][1] <= array[j][1] && array[index][2] > array[j][1]) || (array[index][1] < array[j][2] && array[index][2] >= array[j][2])))
        temp[j] = 1;
    }

    result[i] = array[index][0];
//    printf("%d\n", result[i]);
  }
  return result;
}

void printResult(ofstream &output, int case_num, int size, int *result){

    int val = result[0];
    int count = 1;

    output << "Set " << case_num << "\n";

    for(int i=0; i<size; i++){
      if(val != result[i+1])
        count++;
      else
        break;
      val = result[i+1];
    }
    output << "Number of activities selected = " << count << "\n";

    output << "Activities: ";

    for(int i=count-1; i>-1; i--){
      output << result[i] << " ";
    }
    output << "\n\n";
}

int main() {

  ifstream input;
  input.open("act.txt");

  ofstream output;
  output.open("act.out");

  int size;
  int case_num = 0;

  while(input >> size){

    int array[size][3];

    case_num++;

    for(int i=0; i<size; i++){
      for(int j=0; j<3; j++){
        input >> array[i][j];
//        printf("%d ",array[i][j]);
      }
//      printf("\n");
    }

    sort(array, size);

    int *result;

    result = findActivities(array, size);
/**
    for(int i=0; i<size; i++)
      printf("%d ",result[i]);
**/
  printResult(output, case_num, size, result);

/**
    for(int i=0; i<size; i++){
      for(int j=0; j<3; j++){
        printf("%d ",array[i][j]);
      }
      printf("\n");
    }
**/


  }

  input.close();
  output.close();

  return 0;
}
