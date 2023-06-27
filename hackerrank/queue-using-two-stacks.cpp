#include <iostream>
#include <stack>
#include <string>

class TwoStackQueue
{
public:
    void pushInput()
    {
        std::string value;
        std::cin >> value;
        stack.push(std::stoi(value));
    }
    
    void pop()
    {
        if (queue.empty())
        {
            while (not stack.empty())
            {
                queue.push(stack.top());
                stack.pop();
            }
        }
        
        queue.pop();
    }
    
    void outputFront()
    {
        if (queue.empty())
        {
            while (not stack.empty())
            {
                queue.push(stack.top());
                stack.pop();
            }
        }
        
        std::cout << queue.top() << std::endl;
    }
    
private:
    std::stack<int> stack;
    std::stack<int> queue;
};

int main()
{    
    std::ios_base::sync_with_stdio(false);
    
    int tests = 0;
    std::cin >> tests;
    
    TwoStackQueue queue;
    
    while(tests--)
    {
        int query = 0;
        std::cin >> query;
        
        switch(query)
        {
            case 1:
                queue.pushInput();
                break;
            case 2:
                queue.pop();
                break;
            case 3:
                queue.outputFront();
                break;
            default:
                break;
        }
    }
}