#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
    stack <int> st;
    int N;
    cin >> N;
    while (N--)
    {
        string str;
        cin >> str;
        if (str.compare("push") == 0)
        {
            int a;
            cin >> a;
            st.push(a);
        }
        else if (str.compare("top") == 0)
        {
            cout << st.top()<<endl;
        }
        else if (str.compare("size") == 0)
        {
            cout << st.size()<<endl;
        }
        else if (str.compare("empty") == 0)
        {
            if (st.empty()) cout << 1 << endl;
            else cout << 0 << endl;
        }
        else if (str.compare("pop") == 0)
        {
            if (st.empty()) cout << -1 << endl;
            else {
                int a = st.top();
                cout << a << endl;
                st.pop();
            }
        }
    }
}
