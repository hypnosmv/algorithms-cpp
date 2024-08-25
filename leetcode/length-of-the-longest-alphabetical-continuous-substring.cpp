class Solution
{
public:
    int longestContinuousSubstring(std::string& str)
    {
        int ans = 1;
        int current = 1; 

        for (int i = 1; i < str.size(); ++i)
        {
            if (static_cast<char>(str[i] - 1) == str[i - 1])
            {
                ++current;
            }
            else
            {
                ans = std::max(ans, current);
                current = 1;
            }
        }

        ans = std::max(ans, current);

        return ans;
    }
};
