#include <iostream>
#include <algorithm>
#include <vector>
#include <ranges>

using namespace std;

int main() 
{
    vector<int> v{1, 7, 7, 8, 3, 5, 8, 9};
    ranges::for_each(v, [](const auto& x){ cout << x << " "; });
    cout << endl;
    
    ranges::sort(v);
    // remove the duplicate element
    const auto dup = ranges::unique(v);
    v.erase(dup.begin(), dup.end());
    
    ranges::for_each(v, [](const auto& x){ cout << x << " "; });
    cout << endl;

    return 0;
}