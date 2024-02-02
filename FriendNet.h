/** * Author: Beril Canbulan
*/

#ifndef FRIENDNET_FRIENDNET_H
#define FRIENDNET_FRIENDNET_H

#define N 100009
#include <string>
#include <bits/stdc++.h>
using namespace std;

class FriendNet{
    public:
    FriendNet(string fileName); 

    FriendNet(const FriendNet& aNet); 

    ~FriendNet(); 

    void listFriends(string personName, int hopNo);

    void displayAverageDegrees();

    void displayDiameters();

    private:

    int noOfPeople;

    map<int, string> dic1;
    map<string, int> dic2;

      vector<int> adjList[N];

    int convertStringToNum(const string& in);

    string convertNumToString(int in);

    void addFriend(int id1, int id2);

    void addToMap(const string& name, int id);

    void dfs(int currentNode, int &componentNodeNumber, int &componentDegreeNumber, bool *visited);

    void bfs(int i, queue<int> &q, bool *visited, int *depth, int &currentFurthestNode, int &maxDepth);
    };


#endif //FRIENDNET_FRIENDNET_H
