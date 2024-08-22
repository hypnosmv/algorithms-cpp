class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        std::unordered_map<int, std::vector<int>> numToIndexes;

        for (size_t i = 0; i < nums.size(); ++i)
        {
            numToIndexes[nums[i]].push_back(i);
        }

        for (const auto& [firstNum, indexes] : numToIndexes)
        {
            int secondNum = target - firstNum;

            if (firstNum == secondNum && indexes.size() == 2)
            {
                return indexes;
            }

            if (firstNum != secondNum && numToIndexes.contains(secondNum))
            {
                return {numToIndexes[firstNum][0], numToIndexes[secondNum][0]};
            }
        }

        return {};
    }
};
