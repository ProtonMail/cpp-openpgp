//
//  std_extension.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/23/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
