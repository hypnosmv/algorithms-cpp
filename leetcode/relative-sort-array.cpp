class Solution
{
public:
    std::vector<int> relativeSortArray(std::vector<int>& arr1, std::vector<int>& arr2)
    {
        std::unordered_map<int, int> occuranceArr1;
        for (const int& number : arr1) ++occuranceArr1[number];

        std::vector<int> ans;
        for (const int& number : arr2)
        {
            std::fill_n(std::back_inserter(ans), occuranceArr1[number], number);
            occuranceArr1[number] = 0;
        }

        size_t relativeOrderSize = ans.size();
        for (const auto& [number, count] : occuranceArr1)
        {
            if (count > 0) std::fill_n(std::back_inserter(ans), count, number);
        }

        std::sort(ans.begin() + relativeOrderSize, ans.end());
        return ans;
    }
};
