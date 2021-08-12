#include <iostream>
#include <regex>
#include <string>
#include <map>

using namespace std;

static map<string, int> monthstr_to_int = {
    {"leden", 1},
    {"unor", 2},
    {"brezen", 3},
    {"duben", 4},
    {"kveten", 5},
    {"cerven", 6},
    {"cervenec", 7},
    {"srpen", 8},
    {"zari", 9},
    {"rijen", 10},
    {"listopad", 11},
    {"prosinec", 12}};

bool __is_valid_date(int day, int month, int year)
{
    if (month < 1 || month > 12)
    {
        cout << "Mesic mimo rozsah" << endl;
        return false;
    }
    if (day < 1 || day > 31)
    {
        cout << "Den je mimo rozsah" << endl;
        return false;
    }
    if (month == 2 && day > 29)
    {
        cout << "Unor ma nejvyse 29 dni" << endl;
        return false;
    }
    if (month == 2 && day == 29)
    {
        if (year % 100 == 0 && year % 400 == 0)
        {
            return true;
        }
        if (year % 100 != 0 && year % 4 == 0)
        {
            return true;
        }
        else
        {
            cout << "Rok neni prestupny" << endl;
            return false;
        }
    }
    return true;
}

bool is_valid_date(int day, const string& month, int year)
{
    if(int m = monthstr_to_int[month]){
        return __is_valid_date(day, m, year);
    }
    return false;
}

bool is_valid_date(int day, int month, int year)
{
    return __is_valid_date(day, month, year);
}

int main(int argc, char const *argv[])
{
    const char *mmm[] =
        {"leden", "unor", "brezen", "duben", "kveten", "cerven",
         "cervenec", "srpen", "zari", "rijen", "listopad", "prosinec"};

    const char *datum[] =
        {"4. 10. 1957", "1989-07-06", "24. rijen 1976", "26.05.1982",
         "31.06.2013", "1992-O9-20", "19.13.2013", "22. ledn 2010",
         "29. 2. 1956", "2003-20-13", "19. 3. 215", "31. 4. 2010",
         "12. listopad 2005", "31. prosinec 1999", "28. rijen 1918",
         "2000-6-15", "1. leden 1969", "5. kveten 1945", "13. unor 1946",
         "7. kveten 1952", "12.prosinec 1901", "25. 4 1961",
         "27. zari 1905", "23. prosinec 1947", "1971-11-15",
         "29. unor 2004", "2012-01-3", "07-09-1974", "1992-02-30",
         "1900-02-29", "1. 1. 2012", "31. 12. 2016", "31. brezen 2007"};

    // d|dd. m|mm. rrrr
    regex reg1("([[:digit:]]{1,2})\\.[[:space:]]([[:digit:]]{1,2})\\.[[:space:]]([[:digit:]]{4})");
    // dd.mm.rrrr
    regex reg2("([0-9]{2})\\.([0-9]{2})\\.([[:digit:]]{4})");
    // rrrr-mm-dd
    regex reg3("([[:digit:]]{4})-([0-9]{2})-([0-9]{2})");
    // d|dd. mmm rrrr
    regex reg4("([[:digit:]]{1,2})\\.[[:space:]]([a-z]{4,8})[[:space:]]([[:digit:]]{4})");

    cmatch matches;
    int day, month, year;
    for (auto str : datum)
    {
        cout << str << " : ";
        // d|dd. m|mm. rrrr
        if (regex_match(str, matches, reg1))
        {
            try
            {
                day = stoi(string(matches[1].first, matches[1].second));
                month = stoi(string(matches[2].first, matches[2].second));
                year = stoi(string(matches[3].first, matches[3].second));
                if (is_valid_date(day, month, year))
                {
                    cout << "OK" << endl;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        // dd.mm.rrrr
        else if (regex_match(str, matches, reg2))
        {
            try
            {
                day = stoi(string(matches[1].first, matches[1].second));
                month = stoi(string(matches[2].first, matches[2].second));
                year = stoi(string(matches[3].first, matches[3].second));
                if (is_valid_date(day, month, year))
                {
                    cout << "OK" << endl;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        // rrrr-mm-dd
        else if (regex_match(str, matches, reg3))
        {
            try
            {
                day = stoi(string(matches[3].first, matches[3].second));
                month = stoi(string(matches[2].first, matches[2].second));
                year = stoi(string(matches[1].first, matches[1].second));
                if (is_valid_date(day, month, year))
                {
                    cout << "OK" << endl;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        // d|dd. mmm rrrr
        else if (regex_match(str, matches, reg4))
        {
            try
            {
                day = stoi(string(matches[1].first, matches[1].second));
                string month(matches[2].first, matches[2].second);
                year = stoi(string(matches[3].first, matches[3].second));
                if (is_valid_date(day, month, year))
                {
                    cout << "OK" << endl;
                }
                else{
                    cout << "bad format" << endl;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            cout << "bad format" << endl;
        }
    }

    return 0;
}
