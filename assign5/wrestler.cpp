#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Graph{

  int num;
  list<int> *node;

  public:
    Graph(int num_wrestler);
    void addEdge(int v1, int v2);
    void BFS(int f, int *order, int &index);
};

Graph::Graph(int num_wrestler){

    this->num = num_wrestler;
    node = new list<int>[num_wrestler];
}

void Graph::addEdge(int v1, int v2){

    node[v1].push_back(v2);
    node[v2].push_back(v1);
}

void Graph::BFS(int f, int *order, int &index){

    bool *visit = new bool[num];

    for(int i = 0; i < num; i++)
        visit[i] = false;
    visit[f] = true;

    list<int> que;
    que.push_back(f);

    list<int>::iterator i;

    while(!que.empty()){

        f = que.front();
        order[index++] = f;
        que.pop_front();

        for (i = node[f].begin(); i != node[f].end(); ++i)
            if (!visit[*i]){
                que.push_back(*i);
                visit[*i] = true;
            }
    }
}

int checkResult(int num_rivalrie, int *result, int **rivalries){

  int v, w;

  for(int i = 0; i < num_rivalrie; i++){

    v = rivalries[i][0];
    w = rivalries[i][1];
//    printf("%d, %d \n", result[v], result[w]);
    if(result[v]+result[w] != 1){
      return 1;
    }
  }
  return 0;
}

void printResult(ofstream &output, int possibility, int num_wrestler, int *result, string *name){

  if(possibility == 1){
    output << "No" ;
  }
  else{
    output << "Yes\n";
    output << "Babyfaces: ";

    for(int i = 0; i< num_wrestler; i++)
      if(result[i] == 0)
      output << name[i] << " " ;

    output << "\nHeels: ";

    for(int i = 0; i< num_wrestler; i++)
      if(result[i] == 1)
      output << name[i] << " ";
  }
}

int main() {

  ifstream input;
  input.open("wrestler.txt");

  ofstream output;
  output.open("wrestler.out");

  int num_wrestler;
  int num_rivalrie;

  input >> num_wrestler;

  Graph g(num_wrestler);

  int i, j, k;
  string temp;
  string name[num_wrestler];

  for(i = 0; i < num_wrestler; i++){
    input >> temp;
    name[i] = temp;
//    std::cout << name[i] << "\n";
  }

  input >> num_rivalrie;

  int **rivalries = new int*[num_rivalrie];

  for(i = 0; i < num_rivalrie; i++)
    rivalries[i] = new int[2];


  for(i = 0; i < num_rivalrie; i++){

      input >> temp;
      for(j = 0; j <num_wrestler; j++)
        if(temp == name[j])
          break;

      input >> temp;
      for(k = 0; k <num_wrestler; k++)
        if(temp == name[k])
            break;

//      printf("%d, %d \n", j, k);
    g.addEdge(j, k);
    rivalries[i][0] = j;
    rivalries[i][1] = k;
//    printf("%d, %d \n", rivalries[i][0], rivalries[i][1]);
  }

/**
  int index = 0;

  for(i = 0; i < num_wrestler; i++){
    k = 0;
    for(int j = 0; j <num_wrestler; j++){
      if(order[j] != i)
        k++;
    }

    if(k == num_wrestler){
      g.BFS(i, order, index);
    }
    if(index == num_wrestler)
      break;
  }

  for(i = 0; i < num_wrestler; i++){
    cout << order[i] << " ";
  }
**/

  int check[num_wrestler];

  for(i = 0; i < num_wrestler; i++)
    check[i] = 3;

  for(i = 0; i < num_rivalrie; i++){
    if(check[rivalries[i][0]]==3 && check[rivalries[i][1]]==3){
        check[rivalries[i][0]] = 0;
        check[rivalries[i][1]] = 1;
    }
    else if((check[rivalries[i][0]]==0 || check[rivalries[i][0]]==1) && check[rivalries[i][1]]==3){
      if(check[rivalries[i][0]]==0)
        check[rivalries[i][1]] = 1;
      else
        check[rivalries[i][1]] = 0;
    }
    else if((check[rivalries[i][1]]==0 || check[rivalries[i][1]]==1) && check[rivalries[i][0]]==3){
      if(check[rivalries[i][1]]==0)
        check[rivalries[i][0]] = 1;
      else
        check[rivalries[i][0]] = 0;
    }
  }

  for(i = 0; i < num_wrestler; i++){
    cout << check[i] << " ";
  }


  int result;
  result = checkResult(num_rivalrie, check, rivalries);

  printResult(output, result, num_wrestler, check, name);

  input.close();
  output.close();

  return 0;
}
