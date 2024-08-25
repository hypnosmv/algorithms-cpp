class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        std::unordered_map<int, int> valToLastIdx;

        for (int i = 0; i < nums.size(); ++i)
        {
            valToLastIdx[nums[i]] = i;
        }

        auto getIdxOfNextUniqueVal = 
            [&nums](int idx)
            {
                int previousValue = nums[idx];
                while (idx < nums.size() && nums[idx] == previousValue) ++idx;

                return idx;
            };

        std::vector<std::vector<int>> ans;

        for (int i = 0; i < nums.size(); i = getIdxOfNextUniqueVal(i))
        {
            for (int j = i + 1; j < nums.size(); j = getIdxOfNextUniqueVal(j))
            {
                int desiredVal = -(nums[i] + nums[j]);
                auto it = valToLastIdx.find(desiredVal);

                if (it != valToLastIdx.end() && it->second > j)
                {
                    ans.push_back({nums[i], nums[j], it->first});
                }
            }
        }

        return ans;
    };
};
