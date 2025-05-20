#include <cstdio>
#include <array>



int main()
{
    std::array<int, 4>arr;

    printf("Sizeof array: %lu\n", arr.size());

    return 0;
}


#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> inMST(n, false);  // Track nodes in MST
        vector<int> minDist(n, INT_MAX);  // Min distance to MST
        int totalCost = 0, edgesUsed = 0;

        // Min-heap (priority queue) storing {cost, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, 0});  // Start with first point

        while (edgesUsed < n) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (inMST[u]) continue;  // Ignore already added nodes

            inMST[u] = true;
            totalCost += cost;
            edgesUsed++;

            // Update minDist and push new edges to pq
            for (int v = 0; v < n; v++) {
                if (!inMST[v]) {
                    int dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                    if (dist < minDist[v]) {
                        minDist[v] = dist;
                        pq.push({dist, v});
                    }
                }
            }
        }

        return totalCost;
    }
};
