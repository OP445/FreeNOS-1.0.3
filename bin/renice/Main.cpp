#include "renice.h"

int main(int argc, char **argv)
{
    Renice app(argc, argv);
    return app.run();
}
