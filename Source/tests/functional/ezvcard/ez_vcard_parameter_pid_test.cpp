//
//  ez_vcard_pid_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/13/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>

#include "pid.hpp"

namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_parameter_pid_test)
        {
            TEST(constructor) {
                Pid::Ptr pid = std::make_shared<Pid>(1);
                VERIFY_ARE_EQUAL(1, pid->getLocalId());
                VERIFY_ARE_EQUAL(UINT32_MAX, pid->getClientPidMapReference());
                
                pid = std::make_shared<Pid>(1, 2);
                VERIFY_ARE_EQUAL(1, pid->getLocalId());
                VERIFY_ARE_EQUAL(2, pid->getClientPidMapReference());
            }

            TEST(valueOf) {
                auto expected = std::make_shared<Pid>(1, 2);
                auto actual = Pid::valueOf("1.2");
                VERIFY_IS_NOT_NULL(actual);
                VERIFY_IS_TRUE(expected == actual);
                actual = Pid::valueOf("aaaa bbb ccc 11");
                VERIFY_IS_NULL(actual);
                actual = Pid::valueOf("1111.ksdfjlkasfj");
                VERIFY_IS_NOT_NULL(actual);
                VERIFY_ARE_EQUAL(1111, actual->getLocalId());
                actual = Pid::valueOf("aaaa.11.111.ksdfjlkasfj");
                VERIFY_IS_NULL(actual);
                
                expected = std::make_shared<Pid>(1);
                actual = Pid::valueOf("1.");
                VERIFY_IS_NOT_NULL(actual);
                VERIFY_IS_TRUE(expected == actual);
                
                expected = std::make_shared<Pid>(1);
                actual = Pid::valueOf("1");
                VERIFY_IS_TRUE(expected == actual);
            }
            
            //            @Test(expected = NumberFormatException.class)
            //            public void valueOf_invalid() {
            //                Pid.valueOf("1.foo");
            //            }
            //
            //            @Test(expected = NumberFormatException.class)
            //            public void valueOf_more_than_one_dot() {
            //                Pid.valueOf("1.2.2");
            //            }
            //
            
            TEST(toString) {
                auto pid = std::make_shared<Pid>(1, 2);
                VERIFY_IS_TRUE("1.2" == pid->toString());
                
                pid = std::make_shared<Pid>(1);
                VERIFY_IS_TRUE("1" == pid->toString());
            }
            
            TEST(equals) {
                Pid::Ptr pid_1 = std::make_shared<Pid>(1);
                Pid::Ptr pid_2 = std::make_shared<Pid>(2);
                Pid::Ptr pid_3 = std::make_shared<Pid>(1,2);
                Pid::Ptr pid_4 = std::make_shared<Pid>(2,2);
                Pid::Ptr pid_5 = std::make_shared<Pid>(2,3);
                
                Pid::Ptr pid_1_1 = std::make_shared<Pid>(1);
                Pid::Ptr pid_3_1 = std::make_shared<Pid>(1,2);
                
                
                VERIFY_IS_FALSE(pid_1 == pid_2);
                VERIFY_IS_FALSE(pid_1 == pid_3);
                VERIFY_IS_FALSE(pid_1 == pid_4);
                VERIFY_IS_FALSE(pid_1 == pid_5);
                VERIFY_IS_FALSE(pid_2 == pid_3);
                VERIFY_IS_FALSE(pid_2 == pid_4);
                VERIFY_IS_FALSE(pid_2 == pid_5);
                VERIFY_IS_FALSE(pid_3 == pid_4);
                VERIFY_IS_FALSE(pid_3 == pid_5);
                VERIFY_IS_FALSE(pid_4 == pid_5);
                
                VERIFY_IS_TRUE(pid_1 == pid_1_1);
                VERIFY_IS_TRUE(pid_3 == pid_3_1);
                
            }
        }
    }
}
