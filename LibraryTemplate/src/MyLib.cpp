#include "MyLib.h"
#include "impl/MyLibImpl.h"

MyLib::MyLib(int some_argument) : m_impl(std::make_unique<MyLibImpl>(some_argument)) {
}

MyLib::~MyLib() = default;

bool MyLib::init(int some_argument) {
    return m_impl->init(some_argument);
}

int MyLib::someWork(int some_argument) {
    return m_impl->someWork(some_argument);
}