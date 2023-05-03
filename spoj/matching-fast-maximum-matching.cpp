#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>

class HopcroftKarp
{
public:
    HopcroftKarp(const int& C, const int& B)
        : C(C), B(B)
    {
        cowAdjacent.resize(C+1);
        cowPair.resize(C+1, 0);
        bullPair.resize(B+1, 0);
        dist.resize(C+1, 0);
    }
    
    void add(const int& cow, const int& bull)
    {
        cowAdjacent[cow].push_back(bull);
    }
    
    int get()
    {
        int maxPairs = 0;
        
        while(bfs())
            for(int c = 1; c <= C; ++c)
                if(cowPair[c] == 0 && dfs(c)) ++maxPairs;
        
        return maxPairs;
    }
    
private:
    int C;
    int B;
    std::vector<std::vector<int>> cowAdjacent;
    std::vector<int> cowPair;
    std::vector<int> bullPair;
    std::vector<int> dist;
    
    bool dfs(const int& cow)
    {
        if (cow == 0) return true;
        
        for(size_t i = 0; i < cowAdjacent[cow].size(); ++i)
        {
            if(dist[bullPair[cowAdjacent[cow][i]]] == dist[cow] + 1 && 
               dfs(bullPair[cowAdjacent[cow][i]]))
            {
                bullPair[cowAdjacent[cow][i]] = cow;
                cowPair[cow] = cowAdjacent[cow][i];
                return true;
            }
        }
        
        dist[cow] = INT_MAX;
        return false;
    }
    
    bool bfs()
    {
        std::queue<int> Q;
        
        for(int c = 1; c <= C; ++c)
        {
            if (cowPair[c] == 0)
            {
                dist[c] = 0;
                Q.push(c);
            }
            else dist[c] = INT_MAX;
        }
        dist[0] = INT_MAX;
        
        while(not Q.empty())
        {
            int c = Q.front();
            Q.pop();
            
            if(dist[c] < dist[0])
            {
                for(size_t i = 0; i < cowAdjacent[c].size(); ++i)
                { 
                    if(dist[bullPair[cowAdjacent[c][i]]] == INT_MAX)
                    {
                        dist[bullPair[cowAdjacent[c][i]]] = dist[c] + 1;
                        Q.push(bullPair[cowAdjacent[c][i]]);
                    }
                }
            }
        }
        
        return dist[0] != INT_MAX;
    }
};

int main() 
{
    std::ios_base::sync_with_stdio(false);
    
    int C = 0, B = 0, T = 0;
    std::cin >> C >> B >> T;
    
    HopcroftKarp ans(C, B);
    
    while(T--)
    {
        int cow = 0, bull = 0;
        std::cin >> cow >> bull;
        
        ans.add(cow, bull);
    }
    
    std::cout << ans.get() << std::endl;
}
