#pragma once
#include <memory>

class MyLib {
public:
    MyLib(int some_argument);
    ~MyLib();
    MyLib(MyLib &rhs) = default;
    MyLib(MyLib &&rhs) = default;
    MyLib& operator=(MyLib &rhs) = default;
    MyLib& operator=(MyLib &&rhs) = default;

    bool init(int some_argument);

    int someWork(int some_argument);

private:
    class MyLibImpl;
    std::unique_ptr<MyLibImpl> m_impl;
};