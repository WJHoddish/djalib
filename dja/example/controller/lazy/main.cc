
#include "dja11/lazy/lazy.h"

int main(int argc, char *argv[])
{
    std::function<int(int)> func = ([](int x) {
        return x * 3;
    });
    auto lazyman = make_lazy(func, 3);
    std::cout << lazyman.getValue() << std::endl;

    return 0;
}