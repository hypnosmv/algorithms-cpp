#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

template<typename T>
class SegmentedTree
{
public:
    SegmentedTree(const size_t& N, const T& value)
    {
        resize(N, value);
    }

    SegmentedTree(const size_t& N, const T& value, const std::function<T(const T&, const T&)>& compare) 
        : compare(compare)
    {
        resize(N, value);
    }

    void insert(size_t index, const T& value)
    {
        index += base;
        tree[index] = value;

        update(index);
    }

    void insert(const std::vector<T>& sequence)
    {
        std::copy(sequence.begin(), sequence.end(), tree.begin() + base);

        for (size_t i = base; i < sequence.size() + base; ++i) 
            update(i);
    }

    T get(size_t index1, size_t index2) const
    {
        if (index1 == index2) return tree[index1 + base];

        index1 += base;
        index2 += base;

        T value1 = tree[index1];
        T value2 = tree[index2];

        while (index1 / 2 != index2 / 2)
        {
            if (index1 % 2 == 0) value1 = compare(value1, tree[index1 + 1]);
            if (index2 % 2 == 1) value2 = compare(tree[index2 - 1], value2);

            index1 /= 2;
            index2 /= 2;
        }

        return compare(value1, value2);
    }

    const std::vector<T>& getTree() const
    {
        return tree;
    }

private:
    std::vector<T> tree;
    size_t base;
    std::function<T(const T&, const T&)> compare = [](const T& lhs, const T& rhs) { return std::max(lhs, rhs); };

    void resize(const size_t& N, const T& value)
    {
        tree.resize(2 * std::pow(2, std::ceil(std::log2(N))), value);
        base = tree.size() / 2;
    }

    void update(size_t index)
    {
        while (index > 1)
        {
            index /= 2;
            tree[index] = compare(tree[2 * index], tree[2 * index + 1]);
        }
    }
};

int main() 
{
    struct Vertex
    {
        long long best;
        long long sum;
        long long prefix;
        long long suffix;

        Vertex(const long long& value)
            : best(value), sum(value), prefix(value), suffix(value)
        {}
    };

    auto compare = [](const Vertex& lhs, const Vertex& rhs)
    {
        Vertex out(0);
        out.best = std::max(std::max(lhs.best, rhs.best), lhs.suffix + rhs.prefix);
        out.sum = lhs.sum + rhs.sum;
        out.prefix = std::max(lhs.prefix, lhs.sum + rhs.prefix);
        out.suffix = std::max(rhs.suffix, rhs.sum + lhs.suffix);
        return out;
    };
    
    std::ios_base::sync_with_stdio(false);
    
    size_t N = 0;
    std::cin >> N;
    
    SegmentedTree<Vertex> tree(N, Vertex(0), compare);
    
    std::vector<Vertex> sequence(N, 0);
    for(size_t i = 0; i < N; ++i)
    {
        long long num = 0;
        std::cin >> num;
        
        sequence[i] = Vertex(num);
    }
    
    tree.insert(sequence);
    
    long long queries = 0;
    std::cin >> queries;
    
    while(queries--)
    {
        size_t x = 0;
        size_t y = 0;
        std::cin >> x >> y;
        --x, --y;
        
        std::cout << tree.get(x, y).best << std::endl;
    }
}