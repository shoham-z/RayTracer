//
// Created by shoham on 6/17/22.
//

#include "Util.h"


template <typename T> void assertEquals(T expected, T actual, const std::string& message) {
    if (expected == actual) return;
    std::cout << message << std::endl;
    exit(-1);
}