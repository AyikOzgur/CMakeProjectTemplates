#include "MyLibImpl.h"

MyLib::MyLibImpl::MyLibImpl(int some_argument) {
}

bool MyLib::MyLibImpl::init(int some_argument) {
    m_some_private_field = some_argument;
    return false;
}

int MyLib::MyLibImpl::someWork(int some_argument) {
    m_some_private_field = some_argument;
    return 0;
}