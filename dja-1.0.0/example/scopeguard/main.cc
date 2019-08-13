
#include "dja/core/scoprguard.h"

void testScopeGuard())
{
    std::function<void()> f = [] {
        std::cout << "cleanup from unnormal exit"
                  << "\n";
    };

    // normal exit
    {
        auto gd = make_guard(f);
        //...
        gd.dismiss();
    }

    // error occur
    {
        auto gd = make_guard(f);
        //...
        throw 1;
    }

    // abnormal exit
    {
        auto gd = make_guard(f);
        return;
        //...
    }
}

int main(int argc, char *argv[])
{
    try
    {
        testScopeGuard();
    }
    catch (...)
    {
        // the function f will be automatically called in this block
    }

    return 0;
}