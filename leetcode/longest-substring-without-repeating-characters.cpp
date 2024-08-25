class Solution
{
public:
    int lengthOfLongestSubstring(std::string& str)
    {
        int left = 0;
        int right = 0;
        int ans = 0;
        std::unordered_multiset<int> letters;

        while (right < str.size())
        {
            letters.emplace(str[right]);

            if (letters.count(str[right]) > 1)
            {
                do letters.erase(letters.find(str[left]));
                while (left < right && str[left++] != str[right]);
            }

            ans = std::max(static_cast<int>(letters.size()), ans);
            ++right;
        }

        return ans;
    }
};
