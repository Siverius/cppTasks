#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>

bool asc(int a, int b)
{
    return a < b;
}

bool desc(int a, int b)
{
    return a > b;
}

bool even(int a)
{
    return a%2 == 0 && a != 0;
}

bool odd(int a)
{
    return a%2 != 0;
}

int multiply(int a, int b)
{
    return a*b;
}

int IsOneK(int a)
{
    return a == 1000;
}

int main()
{
    std::vector<int> v{1,5,85,47,52,42,35,96,58,57,15};
    std::sort(v.begin(), v.end(), desc);
    std::reverse(v.begin(), v.end());    
    
    std::cout << " 1+2 Sort & reverse:" << std::endl << std::endl;
    
    for (auto element : v)
    {
        std::cout << element << std::endl;
    }
    
    std::cout << "\n 3 min_element:" << std::endl << std::endl;
    std::vector<int>::iterator min_element = std::min_element(v.begin(), v.end());
    std::cout << "Min.element: " << *min_element << std::endl;
    
    std::cout << "\n 4 max_element:" << std::endl << std::endl;
    std::vector<int>::iterator max_element = std::max_element(v.begin(), v.end());
    std::cout << "Max.element: " << *max_element << std::endl;
    
    std::cout << "\n 5 count_if:" << std::endl << std::endl;
    int even_elements_count = std::count_if(v.begin(), v.end(), even);
    std::cout << "Count of even values: " << even_elements_count << std::endl;
    
    std::cout << "\n 6 replace_if:" << std::endl << std::endl;
    std::replace_if(v.begin(), v.end(), odd, 1000);
    
    for (auto element : v)
    {
        std::cout << element << std::endl;
    }
    
    std::cout << "\n 7 remove_if:" << std::endl << std::endl;
    std::remove_if(v.begin(), v.end(), IsOneK);
    
    for (auto element : v)
    {
        std::cout << element << std::endl;
    }
    
    std::cout << "\n 8 partial_sum:" << std::endl << std::endl;
    int result[10];
    std::partial_sum(v.begin(), v.end(), result);
    
    for (auto element : v)
    {
        std::cout << element << std::endl;
    }
    std::cout << "==========" << std::endl;
    for (auto r : result)
    {
        std::cout << r << std::endl;
    }
    
    std::cout << "\n 9 accumulate:" << std::endl << std::endl;
    int out = std::accumulate(v.begin(), v.end(), 1, multiply);
    
    std::cout << out << std::endl;
    
    std::cout << "\n 10 find:" << std::endl << std::endl;
    int forty_two = 42;
    auto res42 = std::find(v.begin(), v.end(), forty_two);
    
    if(res42 != v.end())
    {
        std::cout << "There are some 42`s" << std::endl;
    }
    else
    {
        std::cout << "That`s very bad universe with no 42`s :(" << std::endl;
    }
}


















