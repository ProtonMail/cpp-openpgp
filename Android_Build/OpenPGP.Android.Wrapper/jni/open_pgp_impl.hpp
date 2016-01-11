#pragma once

#include "open_pgp_test.hpp"


class OpenPgpImpl : public OpenPgpTest {

public:
    OpenPgpImpl();
    std::string decrypt_message();


};

