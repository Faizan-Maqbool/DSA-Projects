#include<iostream>
#include<vector>
#include<limits.h>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>

using namespace std;

#define V 7

int parent[V];
int parent1[V];

int minimum_distance(vector<int>& distance,vector <bool>& visited) {
    int minimum = INT_MAX;
    int index;
    for(int i = 0; i < V; i++) {
        if(visited[i] == false && distance[i] < minimum) {
            minimum = distance[i];
            index = i;
        }
    }
    return index;
}

void dijkastra_algorithm(int graph[V][V], int source) {
    vector<int> distance(V,INT_MAX);
    vector <bool> visited(V,false);
    int cost;
    distance[source] = 0;
    for(int i = 0; i < V; i++) {
        int target = minimum_distance(distance, visited);
        for(int j = 0; j < V; j++) {
            if(graph[target][j] != 0 && visited[j] == false) {
                cost = distance[target] + graph[target][j];
                if(cost < distance[j]) {
                    distance[j] = cost;
                    parent[j] = target;
                }
            }
        }
        visited[target] = true;
    }
}

void prims(int graph[V][V],int src){
		
	vector<int> value(V,INT_MAX);	
	vector<bool> processed(V,false);
    int U;
    parent1[src]=src;
    value [src]=0;

    for (int i=0;i<V-1;i++){
        U=minimum_distance(value,processed);
        processed[U]=true;

        for (int j=0;j<V;j++){
            if (graph[U][j]!=0 && processed[j]!=true && value[U]!=INT_MAX && (graph[U][j]<value[j])){
                value[j]=graph[U][j];
                parent1[j]=U;
            }
        }

    }
}

void initialGraph(int graph[V][V]){
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = 0;
        }
        
    }
    
}

void initializeweights(string s,string d, int duration, int graph[V][V], string Source[V], string Destination[V] ){
    int sI,dI;
    bool sourceCheck=false;
    bool destinationCheck=false;
    //Finding Location of source Vertex
    for (int i=0;i<V;i++){
        if (Source[i]==s){
           
            sI=i;
            sourceCheck=true;
            break;
        }
    }
    //Finding Location of destination vertex
    for (int j=0;j<V;j++){
        if (Destination[j]==d){
            dI=j;
            destinationCheck=true;
            break;
        }
    }
    //Adding weight at that edge
    if (sourceCheck==true && destinationCheck==true){
        graph[sI][dI]=duration;
    }
    
}


int main(){
    int graph[V][V];
    string source[V]={"Incheon International Airport (ICN) - Seoul, South Korea","Kansai International Airport (KIX) - Osaka, Japan","Marrakesh Menara Airport (RAK) - Marrakesh, Morocco","Queenstown Airport (ZQN) - Queenstown, New Zealand","Munich Airport (MUC) - Munich, Germany","Singapore Changi Airport (SIN) - Singapore","Denver International Airport (DEN) - Denver, Colorado, United States"};
    string Destination[V]={"Incheon International Airport (ICN) - Seoul, South Korea","Kansai International Airport (KIX) - Osaka, Japan","Marrakesh Menara Airport (RAK) - Marrakesh, Morocco","Queenstown Airport (ZQN) - Queenstown, New Zealand","Munich Airport (MUC) - Munich, Germany","Singapore Changi Airport (SIN) - Singapore","Denver International Airport (DEN) - Denver, Colorado, United States"};
    initialGraph(graph);

    ifstream fin;
    fin.open("DistanceDataSet.csv");
    string line, word;
    vector<string> lineData;
    int lines = 0;

    while (getline(fin, line)) {
        //reading data and adding to vector
        stringstream s(line);
        while (getline(s, word, ',')) {
            lineData.push_back(word);
        }
        //type casting weights from string to int
        stringstream s3(lineData[2]);
        int duration;
        s3>>duration;
        //adding data to linked list
        if (lines != 0)
        {
            initializeweights(lineData[0], lineData[1], duration, graph, source, Destination );
        }
        //clearing vector
        lineData.clear();
        lines++;
    }

    int choice;
    cout<<"Choose the source you want the distance from:"<<endl;
    for (int i=0;i<7;i++){
        cout<<(i+1)<<"-"<<source[i]<<endl;
    }

    cin>>choice;
    choice=choice-1;
    dijkastra_algorithm(graph, choice);
    cout<<"Shortest Path:"<<endl;
    for (int i = 0; i < V; i++){
        cout<<source[parent[i]]<<" --> "<<source[i]<<" : "<<graph[parent[i]][i]<<endl;
    }

    cout<<endl;

    prims(graph,0);
    cout<<"shipping methodolgy among different countries"<<endl;
    for (int i = 0; i < V; i++){
        cout<<source[parent1[i]]<<" --> "<<source[i]<<" : "<<graph[parent1[i]][i]<<endl;
    }
}
