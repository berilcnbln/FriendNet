/** * Author: Beril Canbulan
* ID: 21602648
* Section: 01
* Assignment: 5
*/

#include "FriendNet.h"
#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>

#define N 100009
using namespace std;

FriendNet::FriendNet(const string fileName){
    char fileNameChar[fileName.length()];
    strcpy(fileNameChar, fileName.c_str());
    FILE *fptr = fopen(fileNameChar, "r");
    if(!fptr)
        cout << "File does not exist\n";

    int n, id, m;
    char name[109];
    fscanf(fptr, "%d", &n);
    this -> noOfPeople =n;
    for(int i = 0; i < n; i++){
        fscanf(fptr, "%d %s %d", &id, &name, &m);
//        I am interested in ids only, so I will save names just in case to the map
        addToMap(name, id);
        for(int j = 0; j < m; j++){
            int currentFriend;
               fscanf(fptr, "%d", &currentFriend);
               
            addFriend(id, currentFriend);
        }
    }

    fclose(fptr);
}

void FriendNet::listFriends(const string personName, const int hopNo) {
    if(dic2.count(personName) == 0){
        printf("%s does not exist in the network.\n", personName.c_str());
        return ;
    }

    queue<int> q;
    int hops[N] = {0};
    string name;
    bool visited[N] = {false};
     bool printed = false;

    int id = convertStringToNum(personName);
    q.push(id);
      visited[id] =true;
    hops[id] =0;

    printf("People accessible from %s within %d hops: ", personName.c_str(), hopNo);

    while(!q.empty() && hopNo >= 0){
        id = q.front();

        q.pop();
        //skip if the friends of the current person don't matter
        name = convertNumToString(id);
        if(id != convertStringToNum(personName)) {
            printed = true;

            cout << name << ", ";
        }
        if(hops[id] == hopNo)
            continue;
        for( vector<int> to: adjList[id]){
            if(!visited[to]){

                visited[to] = true;
                q.push(to);
                hops[to] = hops[id] + 1;
            }
        }
    }

    if(!printed)
        cout << "NOBODY";

    cout << endl;
}

void FriendNet::addFriend(int id1, int id2) {
    adjList[id1].push_back(id2);
}

int FriendNet::convertStringToNum(const string& in) {
    return dic2[in];
}

string FriendNet::convertNumToString(int in) {
    return dic1[in];

}

void FriendNet::addToMap(const string& name, int id) {
    if(id >= 0) {
        dic1[id] =name;
        dic2[name] =id;
    }
}

FriendNet::FriendNet(const FriendNet &aNet) {
    this->noOfPeople = aNet.noOfPeople;

    for(int i=0; i<this->noOfPeople; i++){
        for(int j: aNet.adjList[i])
            (this->adjList[i]).push_back(j);
    }
    dic1= aNet.dic1;

    dic2 =aNet.dic2;
}

FriendNet::~FriendNet() {

}

void FriendNet::dfs(int currentNode, int &componentNodeNumber, int &componentDegreeNumber, bool *visited){
    visited[currentNode] = true;
    componentNodeNumber++;
    componentDegreeNumber += adjList[currentNode].size();

    for(vector<int> to: adjList[currentNode]){
        if(!visited[to]){
            dfs(to, componentNodeNumber, componentDegreeNumber, visited);
        }
    }
}

void FriendNet::displayAverageDegrees() {
    bool visited[N]={false};
    double averageDegree[N];
      int componentNumber=0;

    for(int i=0; i<this->noOfPeople; i++){
        int componentNodeNumber = 0, componentDegreeNumber=0;
        if(!visited[i]){
            dfs(i, componentNodeNumber, componentDegreeNumber, visited);
            averageDegree[componentNumber++] = (1.0 * componentDegreeNumber) / componentNodeNumber;
        }
    }

    printf("There are %d connected components. The average degrees are: \n", componentNumber);
    for(int i = 0; i < componentNumber; i++){
           printf("For component %d: %.2lf\n", i, averageDegree[i]);
    }
}

void FriendNet::displayDiameters() {
    bool *visited = new bool[this->noOfPeople];
    int *depth = new int[this -> noOfPeople];
    queue<int> q;
    vector<int> result;

    for(int i=0; i < this -> noOfPeople; i++)
        visited[i] = false;

    for(int i = 0; i < noOfPeople; i++){
//     I meet a node that is not visited, it is a new component
        if(!visited[i]){
            int maxDepth, currentFurthestNode = i;
            bool visitedBefore[noOfPeople];
            for(int j = 0; j < noOfPeople; j++){
                depth[j] = 0;
                   visitedBefore[j] = visited[j];
            }

                 bfs(currentFurthestNode, q, visited, depth, currentFurthestNode, maxDepth);

            for(int j = 0; j < noOfPeople; j++) {
                depth[j] = 0;
                visited[j] = visitedBefore[j];
            }

//            printf("Started with %s\n", convertNumToString(currentFurthestNode).c_str());
            bfs(currentFurthestNode, q, visited, depth, currentFurthestNode, maxDepth);
//            printf("Ended with %s node\n", convertNumToString(currentFurthestNode).c_str());
            result.push_back(maxDepth);
        }
    }

    printf("There are %d connected components. The diameters are: \n", result.size());
    for(int i=0; i<result.size(); i++)
        printf("For component %d: %d\n", i, result[i]);


    delete [] visited;
       delete [] depth;
    depth =NULL;
    visited =NULL;
}

void FriendNet::bfs(int i, queue<int> &q, bool *visited, int *depth, int &currentFurthestNode, int &maxDepth) {
    currentFurthestNode = 0, maxDepth = -1;
    visited[i]=true;
    q.push(i);
    while(!q.empty()){
        int top =q.front();
        if(depth[top] > maxDepth){
            maxDepth=depth[top];
            currentFurthestNode =top;
        }
        q.pop();
        for(vector<int> to: adjList[top]){
            
             if(!visited[to]){
                visited[to] =true;

                depth[to] = depth[top] + 1;

                q.push(to);
            }
        }
    }
}
