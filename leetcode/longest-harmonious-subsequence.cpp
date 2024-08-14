class Solution 
{
public:
    int findLHS(std::vector<int>& nums) 
    {
        int ans = 0;

        for (size_t i = 0; i < nums.size(); ++i)
        {
            int smallerCount = 0;
            int biggerCount = 0;
            int equalCount = 0;

            for (size_t j = i + 1; j < nums.size(); ++j)
            {                
                switch (nums[i] - nums[j])
                {
                    case -1:
                        ++smallerCount;
                        break;
                    case 1:
                        ++biggerCount;
                        break;
                    case 0:
                        ++equalCount;
                        break;
                    default:
                        break;
                }
            }

            int runAns = (smallerCount != 0 || biggerCount != 0) ? equalCount + std::max(smallerCount, biggerCount) + 1 : 0;
            ans = std::max(runAns, ans);
        }

        return ans;
    }
};
