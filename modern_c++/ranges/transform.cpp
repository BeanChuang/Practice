#include <iostream>
#include <algorithm>
#include <vector>
#include <ranges>

using namespace std;

int main() 
{
    string s {"[ 1, 2,  3] ^%"};

    ranges::for_each(s, [](const char c) { cout << c << " "; });
    cout << endl;

    for (const auto& sub_range : s 
        | views::filter([](char c) { return isdigit(c) or c == ','; })
        | views::split(',')) {
        for (auto ch : sub_range) {
            cout << ch << " ";
        }
        cout << endl;
    }
    return 0;
}