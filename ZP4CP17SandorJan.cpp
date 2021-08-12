#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

#ifdef _WIN32
typedef unsigned char u_char;
typedef unsigned short u_short;
#endif

using namespace std;

struct Date
{
    u_char day;
    u_char month;
    u_short year;

    Date()
    {
        day = 0;
        month = 0;
        year = 0;
    }

    Date(const u_char &d, const u_char &m, const u_short &y)
    {
        day = d;
        month = m;
        year = y;
    }

    friend bool operator==(const Date &left, const Date &right)
    {
        return (left.day == right.day) && (left.month == right.month) && (left.year == right.year);
    }

    friend ostream &operator<<(ostream &output, const Date &date)
    {
        output << to_string(date.day) << "." << to_string(date.month) << "." << date.year;
        return output;
    }
};

struct Hash
{
    size_t operator()(const Date &date) const
    {
        return date.day + date.month + date.year;
    }
};

int main(int argc, char const *argv[])
{
#ifdef _WIN32
    const char *file_name = "Datum.jpg";
#else
    const char *file_name = "Datum";
#endif

    // file open
    ifstream input(file_name, ios::in | ios::binary);
    if (input.is_open() == false)
    {
        cout << "Could not open binary file '" << file_name << "'." << endl;
        return EXIT_FAILURE;
    }

    // file read
    char date[4]; // [0] => day, [1] => month, [2-3] => year little endian
    unordered_set<Date, Hash> dates;
    while (input.eof() == false)
    {
        input.read(date, sizeof(date));
        dates.insert(Date(date[0], date[1], ((u_char)date[3] << 8) | (u_char)date[2])); // dd, mm, yyyy
    }

    // print
    int printed = 0;
    for (Date date : dates)
    {
        cout << date;
        printed++;
        if (printed % 10 == 0)
            cout << endl;
        else
            cout << "  ";
    }
    cout << endl;
    cout << "Unordered Set Bucket Count: " << dates.bucket_count() << endl;
    for (int i = 0; i < dates.bucket_count(); i++)
    {
        cout << "Bucket #" << i << " has " << dates.bucket_size(i) << " items." << endl;
    }
    cout << "Bucket load_factor: " << dates.load_factor() << endl;

    return EXIT_SUCCESS;
}