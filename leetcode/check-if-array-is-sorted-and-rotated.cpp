class Solution 
{
public:
    bool check(std::vector<int>& nums) 
    {
        bool rotationEncountered = false;

        for (size_t i = 1; i < nums.size(); ++i)
        {
            if (nums[i - 1] > nums[i])
            {
                if (not rotationEncountered) rotationEncountered = true;
                else return false;
            }
        }

        return (not rotationEncountered) || (nums.back() <= nums.front());
    }
};
