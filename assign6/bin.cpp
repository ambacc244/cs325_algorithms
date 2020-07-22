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

      if(leftArray[indexLeft] < rightArray[indexRight]){
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

int firstFit(int capacity, int num_item, int *item){

  int box = 0;
	int bin[num_item];
  int next = 1;
  int i,j;

  for(i=0; i<num_item; i++)
    bin[i] = 0;

  for(i=0; i<num_item; i++){
    next = 1;
    for(j=0; j<box; j++){
  		if(item[i] + bin[j] <= capacity){
  			bin[j] = bin[j] + item[i];
        next = 0;
//        printf("iteam %d is saved into bin %d\n",i, j);
        break;
      }
    }

    if(next == 1){
  	  box++;
      bin[box-1] = item[i];
//      printf("iteam %d is saved into bin %d\n",i, box-1);
    }
  }

  return box;
}

int firstFitDecreasing(int capacity, int num_item, int *item){

  int box;

  mergeSort(item, 0, num_item-1);
/**
  for(int i=0; i<num_item; i++)
    printf ("%d ", item[i]);
  printf ("\n");
**/
  box = firstFit(capacity, num_item, item);

  return box;
}

int bestFit(int capacity, int num_item, int *item){

  int box = 0;
	int bin[num_item];
	int total_wight;
	int bin_number;
  int i, j;

  for(i=0; i<num_item; i++)
    bin[i] = 0;

	for(i=0; i<num_item; i++){
		total_wight = 0;

		for(j=0; j<box; j++){
			if((bin[j] + item[i]) <= capacity && total_wight < bin[j]){
				total_wight = bin[j];
				bin_number = j;
      }
    }

		if(total_wight == 0){
			box++;
			bin[box-1] = item[i];
  //    printf("iteam %d is saved into bin %d\n",i, box-1);
    }
		else{
			bin[bin_number] = bin[bin_number] + item[i];
  //    printf("iteam %d is saved into bin %d\n",i, bin_number);
    }
  }
/**
  for(i=0; i<box; i++)
    printf("%d, ", bin[i]);
  printf("\n");
**/
  return box;
}

void printResult(ofstream &output, int case_num, int first_fit, int first_fit_decreasing, int best_fit){

  output << "Test Case " << case_num << " Fist Fit: " << first_fit << ", First Fit Decreasing: " << first_fit_decreasing << ", Best Fit: " << best_fit << "\n";
}

int main(){

  ifstream input;
  input.open("bin.txt");

  ofstream output;
  output.open("bin.out");

  int num_case;
  int capacity;
  int num_item;

  int first_fit = 0;
  int first_fit_decreasing = 0;
  int best_fit = 0;

  input >> num_case;

  for(int i = 0; i < num_case; i++){

    input >> capacity;
    input >> num_item;

    int item[num_item];

    for(int j = 0 ; j< num_item; j++)
      input >> item[j];

    first_fit = firstFit(capacity, num_item, item);
    best_fit = bestFit(capacity, num_item, item);
    first_fit_decreasing = firstFitDecreasing(capacity, num_item, item);


  if(num_item == 0)
    printResult(output, i+1, 0, 0, 0);
  else
    printResult(output, i+1, first_fit, first_fit_decreasing, best_fit);

  }

  input.close();
  output.close();

  return 0;
}
