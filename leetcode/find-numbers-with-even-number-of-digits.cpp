class Solution
{
public:
    int findNumbers(std::vector<int>& nums) 
    {
        int ans = 0;

        for (int num : nums)
        {
            int numberOfDigits = 0;
            while (num > 0)
            {
                num /= 10;
                ++numberOfDigits;
            }

            if (numberOfDigits % 2 == 0) ++ans;
        }

        return ans;
    }
};
