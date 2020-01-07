#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "usage : demo file" << endl;
        return 0;
    }

    ifstream in(argv[1]);

    map<string, size_t> str_amount;

    transform(istream_iterator<string>(in),
              istream_iterator<string>(),
              inserter(str_amount, begin(str_amount)),
              [&](const string &str) {
                  auto iter = str_amount.find(str);
                  if (iter != end(str_amount))
                  {
                      iter->second += 1;
                      return make_pair(str, iter->second);
                  }
                  else
                      return make_pair(str, size_t(1));
              });

    multimap<size_t, string, greater<size_t>> order_map;

    transform(begin(str_amount),
              end(str_amount),
              inserter(order_map, begin(order_map)),
              [](auto pair) {
                  return make_pair(pair.second, pair.first);
              });

    for (const auto &iter : order_map)
    {
        cout << iter.second << "\t->\t" << iter.first << endl;
    }

    cout << endl;

    return 0;
}