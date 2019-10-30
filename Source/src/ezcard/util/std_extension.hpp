//
//  std_extension.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/23/17.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#ifndef std_extension_hpp
#define std_extension_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

//namespace vector {


//bool operator==(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs);
    
//}


//namespace map {


//bool operator==(const std::unordered_map<std::string, std::vector<std::string>>& lhs,
//                const std::unordered_map<std::string, std::vector<std::string>>& rhs);


//}



//bool operator==(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs) {
//
//    if (lhs.size() != rhs.size()) {
//        return false;
//    }
//
//    auto pred_list = [] (decltype(*lhs.begin()) c, decltype(c) d)
//    {
//        return c == d;
//    };
//
//    if (!std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred_list)) {
//        return false;
//    }
//
//    return true;
//}
//
//bool operator==(const std::unordered_map<std::string, std::vector<std::string>>& lhs,
//                const std::unordered_map<std::string, std::vector<std::string>>& rhs) {
//    if (lhs.size() != rhs.size()) {
//        return false;
//    }
//
//    auto pred = [] (decltype(*lhs.begin()) a, decltype(a) b)
//    {
//        if (a.first != b.first) {
//            return false;
//        }
//        std::vector<std::string> a_value = a.second;
//        std::vector<std::string> b_value = b.second;
//        if (a_value.size() != b_value.size()) {
//            return false;
//        }
//
//        auto pred_list = [] (decltype(*a_value.begin()) c, decltype(c) d)
//        {
//            return c == d;
//        };
//
//        if (!std::equal(a_value.begin(), a_value.end(), b_value.begin(), pred_list)) {
//            return false;
//        }
//        return true;
//    };
//
//    if (!std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred)) {
//        return false;
//    }
//
//    return true;
//}

#endif /* std_extension_hpp */
