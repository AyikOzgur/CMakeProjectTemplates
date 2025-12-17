#include "MyLib.h"
#include "impl/MyLibImpl.h"

MyLib::MyLib(int some_argument) : m_impl(std::make_unique<MyLibImpl>(some_argument)) {
}

MyLib::~MyLib() = default;

bool MyLib::init(int some_argument) {
    return m_impl->init(some_argument);
}

int MyLib::some_work(int some_argument) {
    return m_impl->some_work(some_argument);
}