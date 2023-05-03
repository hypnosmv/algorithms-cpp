#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    Solution(const uint& n) :
        adjacent(n),
        isMachine(n, false),
        status(n, Status::Unvisited)
    {}
    
    void addEdge(const uint& node1, const uint& node2, const uint& weight)
    {
        adjacent[node1].emplace_back(node2, weight);
        adjacent[node2].emplace_back(node1, weight);
    }
    
    void addMachine(const uint& machine)
    {
        isMachine[machine] = true;
    }
    
    uint get()
    {
        dfs(0, -1, 0);
        return minTime;
    }
    
private:
    struct Node
    {
        uint id;
        uint weight;

        Node(const uint& id, const uint& weight) :
            id(id),
            weight(weight)
        {}
    };

    enum Status
    {
        Unvisited = 0,
        Clear = 1,
        Threat = 2,
        MAX = 3
    };

    std::vector<std::vector<Node>> adjacent;
    std::vector<bool> isMachine;
    std::vector<Status> status;
    uint minTime = 0;

    uint dfs(const uint& index, const uint& previous, const uint& prevWeight)
    {   
        std::vector<uint> threatMinCuts;

        for (auto& neighbor : adjacent[index]) 
        {
            if (neighbor.id != previous)
            {
                uint minCut = dfs(neighbor.id, index, neighbor.weight);
                if (status[neighbor.id] == Status::Threat) threatMinCuts.push_back(minCut);
            }
        }

        if (threatMinCuts.size() == 0) status[index] = isMachine[index] ? Status::Threat : Status::Clear;
        else
        {
            status[index] = Status::Threat;
            std::sort(threatMinCuts.begin(), threatMinCuts.end());

            if (isMachine[index]) for (auto& minCut : threatMinCuts) minTime += minCut;
            else
            {
                for (size_t i = 0; i < threatMinCuts.size() - 1; ++i) minTime += threatMinCuts[i];
                return std::min(prevWeight, *threatMinCuts.crbegin());
            }
        }
        
        return prevWeight;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    uint nodes = 0;
    std::cin >> nodes;
    
    Solution solution(nodes);
    
    uint machines = 0;
    std::cin >> machines;
    
    for (uint i = 1; i < nodes; ++i)
    {
        uint node1 = 0;
        uint node2 = 0;
        uint weight = 0;
        std::cin >> node1 >> node2 >> weight;
        
        solution.addEdge(node1, node2, weight);
    }
    
    for (uint i = 0; i < machines; ++i)
    {
        uint machine = 0;
        std::cin >> machine;
        
        solution.addMachine(machine);
    }
    
    std::cout << solution.get() << std::endl;
}