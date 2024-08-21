class Solution 
{
public:
    int numJewelsInStones(const std::string& jewels, const std::string& stones)
    {
        int ans = 0;

        std::unordered_map<char, int> segregatedStones;
        for (const char& stone : stones) ++segregatedStones[stone];

        for (const auto& [stone, count] : segregatedStones)
        {
            if (jewels.find(stone) != std::string::npos) ans += count;
        }

        return ans;
    }
};
