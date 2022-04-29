#include <bits/stdc++.h>
#include <math.h>
const int mod = 1000000007;
int mutex;
int full;
int empty;
int x;

void producer()
{
    empty--;
    full++;
    mutex = 0;
    cout << "the added item is : " << x << endl;
    x++;
    mutex = 1;
}

void consumer()
{
    empty++;
    full--;
    mutex = 0;
    cout << "the removed item is : " << x << endl;
    x--;
    mutex = 1;
}

int32_t main()
{
    cout << "Welcome to the system :" << endl;
    cout << "1. Press 1 for Producer" << endl;
    cout << "2. Press 2 for Consumer" << endl;
    cout << "3. Press 3 for Exit" << endl;

    mutex = 1;
    full = 0;
    x = 0;
    cout << "Enter the size of the buffer : ";
    cin >> empty;

    while (true)
    {

        int c;
        cin >> c;
        if (c == 1)
        {
            if (mutex && empty != 0)
            {
                producer();
            }
            else
            {
                cout << "The buffer is full ." << endl;
            }
        }

        else if (c == 2)
        {
            if (mutex and full != 0)
            {
                consumer();
            }
            else
            {
                cout << "The buffer is empty." << endl;
            }
        }

        else
        {
            cout << "The END .. " << endl;
            break;
        }
    }
}