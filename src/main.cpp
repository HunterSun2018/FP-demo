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

    unordered_map<size_t, string> str_list;

    // transform(begin(str_amount),
    //           end(str_amount),
    //           insert_iterator(str_list, begin(str_list)),
    //           [](auto pair) {
    //               return make(pair->second, pair->first);
    //           });

    // vector<string> text;
    // copy(is, eof, back_inserter(text));
    // copy(begin(str_amount), end(str_amount), ostream_iterator<string, size_t>(cout, " "));
    for (const auto &iter : str_amount)
    {
        cout << iter.first << "\t\t" << iter.second << endl;
    }

    cout << endl;

    return 0;
}