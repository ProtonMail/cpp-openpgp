//
//  vobject_parameters.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
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

#ifndef vobject_parameters_hpp
#define vobject_parameters_hpp

#include <string>
#include <unordered_map>
#include <map>
#include <list>
#include <vector>

#include "charset.hpp"

namespace vinnie {
    
    class VObjectParameters {
    public:
        typedef std::shared_ptr<VObjectParameters> Ptr;
        
    private:
        std::unordered_map<std::string, std::vector<std::string>> _multipmap;
        
        std::vector<std::string> _get(const std::string& key);
        void _put(std::string key, std::string value);
        void _putAll(std::string key, std::vector<std::string> values);
        std::string sanitizeKey(std::string key);
        std::vector<std::string> _removeAll(std::string key);
        
        bool _equals(const VObjectParameters& rhs);
        
    public:
        
        VObjectParameters();
        VObjectParameters(const VObjectParameters::Ptr& original);
        VObjectParameters(std::unordered_map<std::string, std::vector<std::string>> map);
        
        void putAll(std::string key, std::vector<std::string> values);
        //
        std::vector<std::string> get(const std::string& key);
        void put(std::string key, std::string value);
        bool remove(std::string key, std::string value);
        std::vector<std::string> removeAll(std::string key);
        
        std::vector<std::string> replace(std::string key, std::string value);
        std::vector<std::string> replaceAll(std::string key, std::vector<std::string> values);
        
        void clear();
        void clear(std::string key);
        std::string first(std::string key);
        bool isQuotedPrintable();
        
        Charset::Ptr getCharset();
        std::unordered_map<std::string, std::vector<std::string>> getMap() const;
        
        
        //public int hashCode()
        //public String toString()
        
        //
        bool operator==(const VObjectParameters& rhs);
        void print();
        bool equals(const Ptr& obj);
    };
    bool operator==(const VObjectParameters::Ptr& lhs, const VObjectParameters::Ptr& rhs);
    
    bool operator==(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs);
    
    bool operator==(const std::unordered_map<std::string, std::vector<std::string>>& lhs,
                    const std::unordered_map<std::string, std::vector<std::string>>& rhs);
    

}

#endif /* vobject_parameters_hpp */
