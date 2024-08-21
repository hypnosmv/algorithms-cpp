class Solution
{
public:
    int maximumDifference(std::vector<int>& nums)
    {
        int ans = -1;
        int minNumber = std::numeric_limits<int>::max();

        for (const auto& num : nums)
        {
            minNumber = std::min(num, minNumber);
            ans = std::max(num - minNumber, ans);
        }

        if (ans <= 0) return -1;
        return ans;
    }
};
