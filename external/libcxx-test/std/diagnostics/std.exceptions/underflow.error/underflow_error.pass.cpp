/****************************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// test underflow_error

#include <stdexcept>
#include <type_traits>
#include <cstring>
#include <string>
#include <cassert>
#include "libcxx_tc_common.h"

int tc_libcxx_diagnostics_stdexcept_underflow_error(void)
{
    static_assert((std::is_base_of<std::runtime_error, std::underflow_error>::value),
                 "std::is_base_of<std::runtime_error, std::underflow_error>::value");
    static_assert(std::is_polymorphic<std::underflow_error>::value,
                 "std::is_polymorphic<std::underflow_error>::value");
    {
    const char* msg = "underflow_error message";
    std::underflow_error e(msg);
    TC_ASSERT_EXPR(std::strcmp(e.what(), msg) == 0);
    std::underflow_error e2(e);
    TC_ASSERT_EXPR(std::strcmp(e2.what(), msg) == 0);
    e2 = e;
    TC_ASSERT_EXPR(std::strcmp(e2.what(), msg) == 0);
    }
    {
    std::string msg("another underflow_error message");
    std::underflow_error e(msg);
    TC_ASSERT_EXPR(e.what() == msg);
    std::underflow_error e2(e);
    TC_ASSERT_EXPR(e2.what() == msg);
    e2 = e;
    TC_ASSERT_EXPR(e2.what() == msg);
    }
    TC_SUCCESS_RESULT();
    return 0;
}
