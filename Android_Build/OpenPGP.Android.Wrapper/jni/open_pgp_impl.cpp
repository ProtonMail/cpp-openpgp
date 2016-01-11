

#include "open_pgp_impl.hpp"

std::shared_ptr<OpenPgpTest> OpenPgpTest::create_with_listener() {
    return std::make_shared<OpenPgpImpl>();
}

OpenPgpImpl::OpenPgpImpl () {

}

std::string OpenPgpImpl::decrypt_message()  {
	return "hello word";
}

