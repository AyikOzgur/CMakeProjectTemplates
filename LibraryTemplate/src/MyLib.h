#pragma once
#include <memory>

class MyLib {
public:
    MyLib(int some_argument);
    ~MyLib();

    bool init(int some_argument);

    int some_work(int some_argument);

private:
    class MyLibImpl;
    std::unique_ptr<MyLibImpl> m_impl;
};