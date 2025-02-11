#include <bits/stdc++.h>

using namespace std;

template <class T>
class testV1
{
public:
    testV1() = default;
    virtual void showV1(T x)
    {
        cout << x << endl;
    }
};

template <class T>
class testV2 : public testV1<T>
{
public:
    testV2()
    {
        cout << "testV2()" << endl;
    }
    void showV1(T x) override
    {
        cout << (x + 1) << endl;
    }
};

int main()
{
    testV2<int> *t = new testV2<int>();
    t->showV1(10);

    delete t;
    return 0;
}
