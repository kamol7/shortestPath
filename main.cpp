#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define white 0
#define gray 1
#define black 2

class Node{
public:
    int parent=-1;
    int sumOfCycle=-1;
    int distance=-1;
    bool isCycle=false;
    vector< pair < int , int > > adjacentNode;

};

class Graph{
public:
    int numberOfNode;
    Node *dataOfTree;
    int numberOfEdge;
    int numberOfQuary;
    int *visit;

    Graph(int,int);
    void takeInput();
    void addNode(int,int,int);
    int dfs(int,int);
    void makeTreeDistance(int);
    void makeNormal(int);
    void makeConnected();
    int quary(int,int);
    void askQuary();

};


Graph::Graph(int x,int y) {
    numberOfNode= x;
    numberOfEdge=y;
    dataOfTree = new Node[numberOfNode];
    visit = new int[numberOfNode];
    for (int i = 0; i < numberOfNode; ++i) {
        visit[i]=white;
    }
}



void Graph::takeInput() {
    int from,to,w;
    for(int i=0;i<numberOfEdge;i++){
        cin>>from>>to>>w;
        addNode(from,to,w);
    }

}



void Graph::addNode(int a, int b,int w) {
    a--;
    b--;
    dataOfTree[a].adjacentNode.emplace_back(b,w);
    dataOfTree[b].adjacentNode.emplace_back(a,w);
}

int Graph::dfs(int source, int parent) {

        dataOfTree[source].parent=parent;
        visit[source]=gray;
        cout<<source<<endl;

        for(pair<int,int> child : dataOfTree[source].adjacentNode){
            if(child.first==source)continue;
            if(visit[child.first]==gray){
                dataOfTree[child.first].isCycle=true;
                dataOfTree[child.first].parent=parent;
                return child.first;
            }
            cout<<"child : "<<child.first<<endl;
            dfs(child.first,parent);
        }
        cout<<"outside dfs"<<endl;
        dataOfTree[source].isCycle=false;
        cout<<source<<endl;
        cout<<"dfs debug\n";
    return source;
}

void Graph::makeTreeDistance(int source) {
    dataOfTree[source].distance=0;
    visit[source]=black;
    int sum=dataOfTree[source].adjacentNode[1].second;
    dataOfTree[source].adjacentNode.pop_back();
    stack <int> storeData;
    storeData.push(source);

    while(!storeData.empty()){
        int child= storeData.top();
        storeData.pop();
        for(pair <int , int > temp : dataOfTree[child].adjacentNode){
            if(visit[temp.first]==black) continue;
            visit[temp.first]=black;
            dataOfTree[temp.first].sumOfCycle=true;
            dataOfTree[temp.first].distance = dataOfTree[child].distance+temp.second;
            sum+=temp.second;
            storeData.push(temp.first);
        }
    }
    int x=dataOfTree[source].parent;
    dataOfTree[x].sumOfCycle=sum;
}

void Graph::makeNormal(int source) {
    cout<<source<<endl;
    cout<<"we are in\n";
    dataOfTree[source].distance=0;
    dataOfTree[source].isCycle=false;
    dataOfTree[source].parent=source;
    visit[source]=black;
    stack <int> storeData;
    storeData.push(source);
    while(!storeData.empty()){
        int child= storeData.top();
        storeData.pop();
        for(pair<int,int> temp : dataOfTree[child].adjacentNode){
            if(visit[temp.first]==black) continue;
            visit[temp.first]=black;
            dataOfTree[temp.first].isCycle=false;
            dataOfTree[temp.first].parent=source;
            dataOfTree[temp.first].distance= dataOfTree[child].distance+ temp.second;
            cout<<dataOfTree[temp.first].distance<<endl;

            storeData.push(temp.first);
        }
    }
    cout<<"Here we come\n";
}

void Graph::makeConnected() {
    for(int i=0;i<numberOfNode;i++){
        if(visit[i]==white){
            int x= dfs(i,i);
            if(dataOfTree[x].isCycle== true) makeTreeDistance(x);
            else makeNormal(x);
        }
    }

}

int Graph::quary(int from, int two) {
    if(dataOfTree[from].distance==-1 || dataOfTree[two].distance==-1){
        return -1;
    }
    if(dataOfTree[from].parent != dataOfTree[two].parent) return -1;
    if(dataOfTree[from].isCycle == true){
        int parent= dataOfTree[from].parent;
        int sum= dataOfTree[parent].sumOfCycle;
        int dis= abs(dataOfTree[from].distance - dataOfTree[two].distance);
        sum= sum-dis;
        return min(sum,dis);
    }
    else {
        int x=  abs(dataOfTree[from].distance - dataOfTree[two].distance);
        return x;
    }
}

void Graph::askQuary() {
    cin>>numberOfQuary;
    int x,y;
    for(int i=0;i<numberOfQuary;i++){
        cin>>x>>y;
        x--;
        y--;
        cout<<quary(x,y)<<endl;
    }

}
void solve(int caseNumber){
    printf("Case %d:\n",caseNumber);
    int x,y;
    cin>>x>>y;
    auto *obj= new Graph(x,y);
    obj->takeInput();
    obj->makeConnected();
    obj->askQuary();
    free(obj);
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int test;
    cin>>test;
    for(int i=1;i<=test;i++){
        solve(i);
    }
    return 0;
}