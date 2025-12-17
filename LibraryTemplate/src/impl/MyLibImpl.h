#pragma once
#include "MyLib.h"

class MyLib::MyLibImpl {
public:
    MyLibImpl(int some_argument);

    bool init(int some_argument);

    int some_work(int some_argument);

private:
    int m_some_private_field{0};
};
