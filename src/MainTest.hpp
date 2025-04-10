#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <iostream>
using namespace std;

int main(int argc, const char **argv) {
    doctest::Context context(argc, argv);
    int test_result = context.run();
    context.setAsDefaultForAssertsOutOfTestCases();
    if (context.shouldExit()) return test_result;

    cout << "Hello, World!" << endl;
    return 0;
}