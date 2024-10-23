#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class GapBuffer
{
public:
    int gap_size;
    vector<char> v;
    int l, r;
    int cursor;
    int gap_factor;
    // add assertions or checks for when array size is less than gap size;
    GapBuffer()
    {
        this->gap_size = 20;
        this->gap_factor = 20;
        this->v = vector<char>(gap_size, '\0');
        this->cursor = 0;
        this->l = 0;
        this->r = this->gap_size - 1;
    }
    GapBuffer(int gs)
    {
        this->gap_size = gs;
        this->gap_factor = gs;
        this->v = vector<char>(gs, '\0');
        this->l = 0;
        this->r = gs - 1;
        this->cursor = 0;
    }

    void initialize(string s)
    {
        for (char c : s)
        {
            this->insert(c);
        }
    }
    void left()
    {
        if (l > 0)
        {
            l--;
            v[r] = v[l];
            v[l] = '\0';
            r--;
        }
    }
    void right()
    {
        int n = v.size();
        if (r < n - 1)
        {
            v[l] = v[r + 1];
            v[r + 1] = '\0';
            l++;
            r++;
        }
    }
    int maxCursor()
    {
        return this->v.size() - this->gap_size;
    }
    void insert(char c)
    {
        v[l] = c;
        l++;
        gap_size--;
        cursor++;
        if (gap_size == 0)
            resize();
    }
    void move(int cur)
    {
        // moves the buffer to the character l.
        int maxCursor = this->v.size() - this->gap_size;
        if (cur < 0)
        {
            return;
        }
        cur = min(cur, maxCursor);
        while (l > cur)
        {
            this->left();
        }

        while (l < cur)
        {
            this->right();
        }
    }
    int back()
    {
        if (l > 0)
        {
            l--;
            v[l] = '\0';
            gap_size++;
            return 1;
        }
        return 0;
    }

    void resize()
    {
        int n = v.size();
        vector<char> temp(gap_factor + n);
        for (int i = 0; i < gap_factor + n; i++)
        {
            if (i < l)
            {
                temp[i] = v[i];
            }
            else if (i >= l && i < l + gap_factor)
            {
                temp[i] = '\0';
            }
            else
            {
                temp[i] = v[i - gap_factor];
            }
        }
        r = gap_factor + l - 1;
        this->gap_size = this->gap_factor;
        this->v = temp;
        //
    }

    void display()
    {

        for (char c : v)
        {
            if (c != '\0')
                cout << c;
            else
            {
            }
        }
        // cout << endl
        //      << "Cursor is at " << cursor << endl;
        // cout << "GAP IS AT" << l << " " << r << endl;
        // cout << "GAP SIZE IS " << gap_size << endl;
    }
    string breakBuffer()
    {
        string temp = "";
        for (int i = l; i < v.size(); i++)
        {
            if (v[i] != '\0')
            {
                temp += v[i];
                v[i] = '\0';
                this->gap_size++;
            }
        }
        return temp;
    }
};

// int main()
// {
//     GapBuffer a(4);
//     a.initialize("abcd");
//     a.display();
//     while (true)
//     {
//         cout << "ENTER 1 for left , 2 for right, 3 for insert , 4 for exit, 5 for back  , 6 for move" << endl;
//         int b;
//         cin >> b;
//         if (b == 1)
//         {
//             a.left();
//         }
//         else if (b == 2)
//         {
//             a.right();
//         }
//         else if (b == 3)
//         {
//             char c;
//             cin >> c;
//             a.insert(c);
//         }
//         else if (b == 4)
//         {
//             break;
//         }
//         else if (b == 5)
//         {
//             a.back();
//         }
//         else if (b == 6)
//         {
//             int n;
//             cin >> n;
//             a.move(n);
//         }
//         a.display();
//     }
//     return 0;
// }