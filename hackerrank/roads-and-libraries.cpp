#include <iostream>
#include <vector>
#include <stack>

using uint64 = unsigned long long;

class Solution
{
public:
    Solution(const uint64& numberOfCities, const uint64& libraryCost, const uint64& roadCost) :
        libraryCost(libraryCost),
        roadCost(roadCost),
        graph(numberOfCities)
    {}

    void addRoad(const uint64& city1, const uint64& city2)
    {
        graph[city1].push_back(city2);
        graph[city2].push_back(city1);
    }

    uint64 determineCost()
    {
        std::vector<bool> visited(graph.size(), false);
        std::stack<uint64> stack;

        std::vector<uint64> disconnectedNodeCount;
        size_t disconnectedIndex = 0;

        for (size_t i = 0; i < graph.size(); ++i) 
        {
            if (visited[i]) continue;
            disconnectedNodeCount.push_back(0);
            
            stack.push(i);
            while (not stack.empty()) 
            {
                uint64 v = stack.top();
                stack.pop();

                if (visited[v]) continue;
                visited[v] = true;
                ++disconnectedNodeCount[disconnectedIndex];

                for (auto& w : graph[v]) 
                    if (not visited[w]) 
                        stack.push(w);
            }

            ++disconnectedIndex;
        }

        uint64 totalCost = 0;
        for (auto& nodeCount : disconnectedNodeCount)
            totalCost += std::min((nodeCount - 1) * roadCost + libraryCost, nodeCount * libraryCost);

        return totalCost;
    }

private:
    uint64 libraryCost;
    uint64 roadCost;

    std::vector<std::vector<uint64>> graph;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    long long tests = 0;
    std::cin >> tests;
    
    while (tests--)
    {
        uint64 numberOfCities = 0;
        long long numberOfRoads = 0;
        uint64 libraryCost = 0;
        uint64 roadCost = 0;
        
        std::cin >> numberOfCities >> numberOfRoads >> libraryCost >> roadCost;
        
        Solution solution(numberOfCities, libraryCost, roadCost);
        while (numberOfRoads--)
        {
            uint64 city1 = 0;
            uint64 city2 = 0;
            std::cin >> city1 >> city2;
            --city1, --city2;
            
            solution.addRoad(city1, city2);
        }
        
        std::cout << solution.determineCost() << std::endl;
    }
}