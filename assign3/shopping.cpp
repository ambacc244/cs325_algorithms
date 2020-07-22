#include <iostream>
#include <fstream>
#include <algorithm>
#include<math.h>

using namespace std;

int *orderArray(float array[][2], int size){

  int *order = new int[size];
  int index;

  for(int i=0; i<size; i++){
    index = 0;
    for(int j=0; j<size; j++){
      if(i == j){
        //nothing
      }
      else if(array[i][0] > array[j][0]){
        index++;
      }
      else if(array[i][0] == array[j][0]){
        if(i<j)
          index++;
      }
    }
    order[i] = index;
  }

  return order;
}

void shopping(int num_items, int num_family, float items[][2], int *family, int **result){

  int capacity;
  int total;
  int *sort = orderArray(items, num_items);
  int k;
/**
  for(int i=0; i<num_items; i++)
    printf("%d ", sort[i]);
**/
  for(int i=0; i<num_family; i++){
    capacity = family[i];
//    printf("capacity: %d\n", capacity);
    total = 0;

    for(int j=0; j<num_items; j++){
      if(items[j][1] > capacity){
        result[i][j] = 0;
      }
      else{
        total = total + items[j][1];
      }
//      printf("%d", result[i][j]);
    }

    if(total>capacity){
      for(int j=0; i<num_items; j++){
        for(int k=0; k<num_items; k++){
          if(sort[k] == j && result[i][k] == 1){
            result[i][k] = 0;
            total = total - items[k][1];
            break;
          }
        }
        if(total<capacity)
          break;
      }
    }
//    printf("%d \n", total);
  }
/**
  for(int j=0; j<num_family; j++)
    for(int k=0; k<num_items; k++)
      printf("%d", result[j][k]);
**/
  free(sort);
}
int computeTotal(int num_items, int num_family, float items[][2], int **result){

  int total = 0;

  for(int i=0; i<num_family; i++){
    for(int j=0; j<num_items; j++){
      if(result[i][j]==1)
        total = total + items[j][0];
    }
  }

  return total;
}

void printOutput(ofstream &output, int case_num, int total, int num_items, int num_family, float items[][2], int **result){

  output << "Test Case " << case_num+1 << "\n";
  output << "Total Price " << total << "\n";
  output << "Member Items: " << "\n";

  for(int i=0; i<num_family; i++){
    output << "   " << i+1 << ":  ";
    for(int j=0; j<num_items; j++)
      if(result[i][j] == 1)
        output << j+1 << " ";

    output << "\n";
  }

  output << "\n\n";
}

int main(){

  ifstream input;
  input.open("shopping.txt");

  ofstream output;
  output.open("shopping.out");

  int cases;
  int num_items;
  int num_family;
  int total;

  input >> cases;
//    printf("cases: %d\n", cases);
  for(int i=0; i<cases; i++){
    input >> num_items;
//    printf("num_items: %d\n", num_items);
    float items[num_items][2];
    int *order[num_items];

    for(int j=0; j<num_items; j++){
      input >> items[j][0];
//      printf("items price: %f\n", items[j][0]);
      input >> items[j][1];
//      printf("items wight: %f\n", items[j][1]);
    }

    input >> num_family;
//    printf("num_family: %d\n", num_family);
    int family[num_family];

    int **result = new int *[num_family];

    for(int j=0; j<num_family; j++){
        result[j] = new int[num_items];
        for(int k=0; k<num_items; k++){
          result[j][k] = 1;
  //        printf("%d", result[i][j]);
        }
    }

    for(int j=0; j<num_family; j++){
      input >> family[j];
//      printf("family capacity: %d\n", family[j]);
    }

    shopping(num_items, num_family, items, family, result);
/**
    for(int j=0; j<num_family; j++)
        for(int k=0; k<num_items; k++)
          printf("%d", result[j][k]);
**/
    total = computeTotal(num_items, num_family, items, result);
//    printf("total: %d\n", total);
    printOutput(output, i, total, num_items, num_family, items, result);
  }

  input.close();
  output.close();
}
