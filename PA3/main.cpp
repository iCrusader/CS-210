#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
const int MAX = 5; //Number of vertices
const int INF = INT_MAX; // define infinity

void primAlgo(int G[MAX][MAX])
{
    //initialize the starting point can be changed
    int initialVertex = 0;
    //set the visited array start with the initial vertex
    vector<int> visited = {initialVertex};
    //Mini Spanning Tree array that store the vertices and their costs
    int MST[MAX-1][3]; // 3 columns to store minCost, startMinV, nextMinV.
    //Store number of edges
    int edgeNum = 0;

    //initialize unvisited list base on the initial vertex
    vector<int> unvisited;
    for (int i = 0; i < MAX; i++) {
        if (i != initialVertex) {
            unvisited.push_back(i);
        }
    }
    // using Prim's Algorithm
    while (!unvisited.empty())
    {
        // initialize variables
        int minCost = INF;
        int nextMinV = 0;
        int startMinV = 0;

        for (int v1 = 0; v1 < visited.size(); v1++)
        {
            for (int v2 = 0; v2 < unvisited.size(); v2++)
            {
                if (G[visited[v1]][unvisited[v2]] > 0 && G[visited[v1]][unvisited[v2]] < minCost) {
                    minCost = G[visited[v1]][unvisited[v2]];
                    startMinV = visited[v1];
                    nextMinV = unvisited[v2];
                }
            }
        }
        //add new vertex to visited and remove from unvisited
        visited.push_back(nextMinV);
        unvisited.erase(remove(unvisited.begin(), unvisited.end(), nextMinV), unvisited.end());
        //Store the value inside the Spanning Tree array
        MST[edgeNum][0] = minCost;
        MST[edgeNum][1] = startMinV;
        MST[edgeNum][2] = nextMinV;
        //increment edge number
        edgeNum++;
    }
    //Print the result
    cout << "Prim's MST is Edge -> Cost\n";
    for (int i = 0; i < edgeNum; i++) {
        cout << MST[i][1] << " - " << MST[i][2] << " -> " << MST[i][0] << endl;
    }
}

int main() {
    int G[MAX][MAX] = {{0, 3, 65, 0, 0},
                       {3, 0, 85, 20, 45},
                       {65, 85, 0, 41, 77},
                       {0, 20, 41, 0, 51},
                       {0, 45, 77, 51, 0}};
    primAlgo(G);
    return 0;
}