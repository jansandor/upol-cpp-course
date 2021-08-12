#include <iostream>
#include <set>
#include <iomanip>

#include "Mince"

using namespace std;

int main(int argc, char const *argv[])
{
    int pohybSize = sizeof(pohyb) / sizeof(pohyb[0]);
    multiset<int> coins;
    // vlozeni a odebirani prvku
    for (int i = 0; i < pohybSize; i++)
    {
        if (pohyb[i] > 0)
        {
            coins.insert(pohyb[i]);
        }
        else
        {
            auto pos = coins.find(-pohyb[i]);
            if (pos != coins.end())
            {
                coins.erase(pos);
            }
        }
    }
    // tisk
    const int coinValues[] = {M1, M2, M5, M10, M20, M50};
    int coinValuesSize = sizeof(coinValues) / sizeof(coinValues[0]);
    for (int i = 0; i < coinValuesSize; i++)
    {
        int coinCount = coins.count(coinValues[i]);
        if (coinCount <= 0)
        {
            continue;
        }
        string coinStr = "M" + to_string(coinValues[i]);
        cout << setfill(' ') << setw(3) << coinStr << " " << coinCount << "x" << endl;
    }

    return 0;
}
