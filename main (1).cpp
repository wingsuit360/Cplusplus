#include <iostream>
#include <vector>

using namespace std;

class car {
private:
    vector<string> detail;
    vector<int> wear;
    vector<int> wear_k;
    int calc_wear(int i, int km);
    int calc_price();
    int calc_wear(int km);
public:
    car();
    bool drive(int km);
};

car::car()
{
    for (int i = 0; i < 10; ++i)
    {
        wear.push_back(0);
    }
    detail.push_back("d1");
    wear_k.push_back(1);
    detail.push_back("d2");
    wear_k.push_back(2);
    detail.push_back("d3");
    wear_k.push_back(3);
    detail.push_back("d4");
    wear_k.push_back(4);
    detail.push_back("d5");
    wear_k.push_back(5);
    detail.push_back("d6");
    wear_k.push_back(6);
    detail.push_back("d7");
    wear_k.push_back(7);
    detail.push_back("d8");
    wear_k.push_back(8);
    detail.push_back("d9");
    wear_k.push_back(9);
    detail.push_back("d10");
    wear_k.push_back(10);
}

int car::calc_wear(int i, int km)
{
    if (wear[i] != 100)
    {
        if (wear[i] + km*wear_k[i] >= 100)
        {
            wear[i] = 100;
            cout << detail[i] << " is broken" << endl;
            return 100;
        }
        else
        {
            wear[i] += km * wear_k[i];
            return wear[i];
        }
    }
    return 100;
}

 car::calc_price()
{
    int w = 0;
    for (int i = 0; i < 10; ++i)
    {
        w += wear[i];
    }
    return (int)((double)1000000*(1 - (double)w/1000));
}

int car::calc_wear(int km)
{
    int w = 0;
    for (int i = 0; i < 10; ++i)
    {
        if (calc_wear(i, km) == 100) ++w;
    }
    if (w >= 6)
    {
        cout << "You car is broken, sell it!" << endl;
        cout << "Best price for this junk: " << calc_price() << endl;
    }
    return w;
}

bool car::drive(int km)
{
    if (calc_wear(km) < 6) return true;
    return false;
}

int main()
{
    car c;
    while (1)
    {
        cout << "Enter distance: ";
        int d;
        cin >> d;
        if (!c.drive(d)) break;
    }
}
