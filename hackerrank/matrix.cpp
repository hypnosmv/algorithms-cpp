#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    Solution(const unsigned& n) :
        adjacent(n),
        isMachine(n, false),
        status(n, Status::Unvisited)
    {}
    
    void addEdge(const unsigned& node1, const unsigned& node2, const unsigned& weight)
    {
        adjacent[node1].emplace_back(node2, weight);
        adjacent[node2].emplace_back(node1, weight);
    }
    
    void addMachine(const unsigned& machine)
    {
        isMachine[machine] = true;
    }
    
    unsigned get()
    {
        dfs(0, -1, 0);
        return minTime;
    }
    
private:
    struct Node
    {
        unsigned id;
        unsigned weight;

        Node(const unsigned& id, const unsigned& weight) :
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
    unsigned minTime = 0;

    unsigned dfs(const unsigned& index, const unsigned& previous, const unsigned& prevWeight)
    {   
        std::vector<unsigned> threatMinCuts;

        for (auto& neighbor : adjacent[index]) 
        {
            if (neighbor.id != previous)
            {
                unsigned minCut = dfs(neighbor.id, index, neighbor.weight);
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
    
    unsigned nodes = 0;
    std::cin >> nodes;
    
    Solution solution(nodes);
    
    unsigned machines = 0;
    std::cin >> machines;
    
    for (unsigned i = 1; i < nodes; ++i)
    {
        unsigned node1 = 0;
        unsigned node2 = 0;
        unsigned weight = 0;
        std::cin >> node1 >> node2 >> weight;
        
        solution.addEdge(node1, node2, weight);
    }
    
    for (unsigned i = 0; i < machines; ++i)
    {
        unsigned machine = 0;
        std::cin >> machine;
        
        solution.addMachine(machine);
    }
    
    std::cout << solution.get() << std::endl;
}