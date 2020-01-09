#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <cxxabi.h>
#ifdef X86
#include <execinfo.h>
#endif

using namespace std;
using word_freq_map = multimap<size_t, string, greater<size_t>>;

const char *demangle(const char *mangled_name);
word_freq_map count_word_freq(ifstream &ifs);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "usage : demo file" << endl;
        return 0;
    }

    try
    {
        ifstream ifs(argv[1]);

        for (const auto &iter : count_word_freq(ifs))
        {
            cout << iter.second << "\t->\t" << iter.first << endl;
        }

        cout << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what()
                  << ", exception with type "
                  << demangle(typeid(e).name())
                  << endl;
    }
    catch (...)
    {
        std::cout << "caught a unknonw exception with type "
                  << demangle(abi::__cxa_current_exception_type()->name())
                  << std::endl;
    }

    return 0;
}

const char *demangle(const char *mangled_name)
{
    int status;

    return abi::__cxa_demangle(mangled_name, 0, 0, &status);
}

word_freq_map count_word_freq(ifstream &ifs)
{
    map<string, size_t> str_amount;

    transform(istream_iterator<string>(ifs),
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

    word_freq_map order_map;

    transform(begin(str_amount),
              end(str_amount),
              inserter(order_map, begin(order_map)),
              [](auto pair) {
                  return make_pair(pair.second, pair.first);
              });

    return order_map;
}