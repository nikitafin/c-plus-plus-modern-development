#include <string>

class ReversibleString
{
public:
    ReversibleString() : ReversibleString("")
    {
    }
    ReversibleString(const std::string & str) : data(str)
    {
    }

    void Reverse()
    {
        for (int i = 0, j = data.size() - 1; i < j; ++i, --j)
        {
            std::swap(data[i], data[j]);
        }
    }
    std::string ToString() const
    {
        return data;
    }

private:
    std::string data;
};

#include <iostream>
using namespace std;

int main()
{
    ReversibleString s("live");
    s.Reverse();
    cout << s.ToString() << endl;

    s.Reverse();
    const ReversibleString & s_ref = s;
    string tmp = s_ref.ToString();
    cout << tmp << endl;

    ReversibleString empty;
    cout << '"' << empty.ToString() << '"' << endl;

    return 0;
}
