template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::greater<typename Container::value_type>
> class PriorityQueue : public std::priority_queue<T, Container, Compare>
{
public:
    typedef typename
        std::priority_queue<
        T,
        Container,
        Compare>::container_type::const_iterator const_iterator;

    bool contains(const T& val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first != last) 
        {
            if (*first == val) return true;
            ++first;
        }
        return false;
    }
    //const_iterator find(const T& val) const
    //{
    //    auto first = this->c.cbegin();
    //    auto last = this->c.cend();
    //    while (first != last) 
    //    {
    //        if (*first == val) return first;
    //        ++first;
    //    }
    //    return last;
    //}
};