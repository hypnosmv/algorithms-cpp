#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

std::pair<int,int> calculateLongestPath(std::unordered_map<int, std::vector<int>>& graph, const int& start)
{
    std::pair<int,int> longest = std::make_pair(0,0);
    std::vector<bool> discovered(graph.size()+1, false);
    std::stack<std::pair<int,int>> S;
    S.emplace(start, 0);
    
    while(S.size() != 0)
    {
        std::pair<int,int> v = S.top();
        S.pop();
        if (discovered[v.first] == false)
        {
            if (v.second > longest.second)
            {
                longest = v;
            }
            
            discovered[v.first] = true;            
            for (auto& neighbour : graph[v.first])
            {
                S.push(std::make_pair(neighbour, v.second + 1));
            }
        }
    }
    
    return longest;
}

int main() 
{
    std::ios_base::sync_with_stdio(false);
    
    int tests = 0;
    std::cin >> tests;
    
    std::unordered_map<int, std::vector<int>> graph;
    
    for (int i = 0; i < tests; ++i)
    {
        int v1 = 0;
        int v2 = 0;
        
        std::cin >> v1 >> v2;
        if (v1 != 0 && v2 != 0)
        {
            graph[v1].push_back(v2);
            graph[v2].push_back(v1);
        }
    }
    
    int furthestVertex = calculateLongestPath(graph, 1).first;
    std::cout << calculateLongestPath(graph, furthestVertex).second << std::endl;
}