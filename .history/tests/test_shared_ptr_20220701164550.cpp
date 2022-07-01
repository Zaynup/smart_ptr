#include "../src/shared_ptr.h"

int main()
{
    // shared_ptr<int> p = new int(1024);
    shared_ptr<int> p(new int(1024));
    if (p)
    {
    }
}