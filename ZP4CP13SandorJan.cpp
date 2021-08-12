#include <iostream>
#include <list>
#include <map>

using namespace std;

#include "C++ 13 uloha"

Datum::Datum(char d, const char *m, short r)
{
  den = d;
  mesic = m;
  rok = r;
}

bool operator<(Datum const &date1, Datum const &date2)
{
  static map<string, int> monthstr_to_int_map = {
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

  if (date1.rok == date2.rok)
  {
    if (monthstr_to_int_map[date1.mesic] == monthstr_to_int_map[date2.mesic])
    {
      return date1.den < date2.den;
    }
    return monthstr_to_int_map[date1.mesic] < monthstr_to_int_map[date2.mesic];
  }
  return date1.rok < date2.rok;
}

void print_dates(const list<Datum> &dates)
{
  int printed_dates = 0;
  for (auto it = dates.begin(); it != dates.end(); it++)
  {
    cout << (short)(*it).den << ". " << (*it).mesic << " " << (*it).rok << "   ";
    if (++printed_dates % 5 == 0)
    {
      cout << endl;
    }
  }
  cout << endl;
}

bool is_not_holiday_date(const Datum &date)
{
  if (date.mesic.compare("cerven") == 0 || date.mesic.compare("cervenec") == 0)
  {
    return false;
  }
  return true;
}

int main(int argc, char const *argv[])
{
  list<Datum> dates;
  int len_D = sizeof(D) / sizeof(Datum);
  for (int i = 0; i < len_D; i++)
  {
    dates.push_back(D[i]);
  }
  dates.sort();
  print_dates(dates);
  dates.remove_if(is_not_holiday_date);
  print_dates(dates);
  return 0;
}
