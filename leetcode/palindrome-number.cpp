class Solution 
{
public:
    bool isPalindrome(const int& num)
    {
        if (num < 0) return false;

        int tmp = num;
        long long revNum = 0;

        while (tmp != 0)
        {
            revNum *= 10;
            revNum += tmp % 10;
            tmp /= 10;
        }

        return num == revNum;
    }
};