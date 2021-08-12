#include <iostream>
#include <unordered_map>
#include <cstring>

using namespace std;

char *str2lowercase(const char *str)
{
    int len = strlen(str);
    char *result = new char[len + 1];
    for (int i = 0; i < len; i++)
    {
        result[i] = tolower(str[i]);
    }
    result[len] = '\0';
    return result;
}

struct OvoceCena
{
    const char *ovoce;
    float cena;

    friend bool operator==(const OvoceCena &left, const OvoceCena &right)
    {
        return (strcmp(str2lowercase(left.ovoce), str2lowercase(right.ovoce)) == 0) && (left.cena == right.cena);
    }
};

struct Hash
{
    size_t operator()(const char *key) const
    {
        int len = strlen(key);
        return 31 * tolower(key[0]) + tolower(key[len - 1]) + len;
    }
};

struct Eq
{
    bool operator()(const char *key1, const char *key2) const
    {
        return strcmp(str2lowercase(key1), str2lowercase(key2)) == 0;
    }
};

int main(int argc, char const *argv[])
{
    const OvoceCena vlozitOvoce[] =
        {{"Jablka", 24.20},
         {"Blumy", 63.60},
         {"CITRONY", 25.00},
         {"Blumy", 63.60},
         {"grepy", 19.50},
         {"mandarinky", 25.10},
         {"POMELO", 32.20},
         {"Ananas", 40.60},
         {"mango", 18.80},
         {"KIWI", 3.60},
         {"jahody", 86.40},
         {"Hrozny", 55.60}};

    const char *vypsatOvoce[] =
        {"citrony", "ANANAS", "Jahody", "broskve", "Pomelo", "mirabelky"};

    unordered_map<const char *, float, Hash, Eq> map;

    for (auto item : vlozitOvoce)
    {
        map.insert(make_pair(item.ovoce, item.cena));
    }

    for (auto key : vypsatOvoce)
    {
        cout << "Trying to get '" << key << "'" << endl;
        auto item = map.find(key);
        if (item == map.end())
        {
            cout << "???" << endl;
        }
        else
        {
            cout << "Name: " << item->first << "\nPrice: " << item->second << endl;
        }
    }

    cout << "Bucket count: " << map.bucket_count() << endl;
    cout << "Load factor: " << map.load_factor() << endl;

    return 0;
}
