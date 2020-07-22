#include <iostream>
#include <fstream>
#include <list>
#include <queue>

using namespace std;

class Graph{

    int V; //number of vertices
    list<int> *adj;

public:
    Graph(int V);
    void addEdge(int v, int w);
    void BFS(int s, int *order);
};

Graph::Graph(int V){

    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){

    adj[v].push_back(w);
}

void Graph::BFS(int s, int *order){

    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    list<int> queue;

    visited[s] = true;
    queue.push_back(s);

    list<int>::iterator i;

    int j = 0;
    while(!queue.empty()){

        s = queue.front();
        printf("%d ", s);
        order[j++] = s;
        queue.pop_front();

        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
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

void printResult(ofstream &output, int possibility, int num_rivalrie, int *result, string *name){

  if(possibility == 1){
    output << "No" ;
  }
  else{
    output << "Yes\n";
    output << "Babyfaces: ";

    for(int i = 0; i< num_rivalrie; i++)
      if(result[i] == 0)
      output << name[i] << " " ;

    output << "\nHeels: ";

    for(int i = 0; i< num_rivalrie; i++)
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
    g.addEdge(k, j);
    rivalries[i][0] = j;
    rivalries[i][1] = k;
    printf("%d, %d \n", rivalries[i][0], rivalries[i][1]);
  }

  int order[num_wrestler];

  g.BFS(0, order);

  for(i = 0; i < num_wrestler; i++){
    cout << order[i] << " ";
  }

  int check[num_wrestler];

  for(i = 0; i < num_wrestler; i++){
    if(order[i]%2 == 0){
     check[order[i]] = 0;
    }
    else{
      check[order[i]] = 1;
    }
  }

/**
  for(i = 0; i < num_wrestler; i++){
    cout << check[i] << " ";
  }
**/
  int result;
  result = checkResult(num_rivalrie, check, rivalries);

  printResult(output, result, num_rivalrie, check, name);

  input.close();
  output.close();

  return 0;
}
