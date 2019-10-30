//
//  bcrypt.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 3/28/17.
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

#ifndef bcrypt_hpp
#define bcrypt_hpp

#include <stdio.h>

#include <string>
#include <sstream>
#include <vector>


namespace ProtonMail {
    
    
    class BCryptRandom {
    public:
        int32_t generateNumberBetween(const int32_t& first, const int32_t& second);
        std::vector<int32_t> generateNumberSequenceBetween(const int32_t& first, const int32_t& second, const int32_t& length, bool unique);
        int32_t chooseNumberFromSequence(std::vector<int32_t> sequence, const int32_t& length);
        bool isNumber(const int32_t& number, std::vector<int32_t> sequence, const int32_t& length);
        
        std::vector<int32_t> generateRandomDataOfLength(const int32_t& length);
        std::vector<int32_t> generateRandomSignedDataOfLength(const int32_t& length);
        std::string generateRandomStringOfLength(const int32_t& length);
    };
    
    
    class BCrypt {
        
    public:
        std::vector<int32_t> crypt_raw(std::vector<int32_t> password, std::vector<int32_t> salt, int32_t log_rounds, std::vector<int64_t> cdata);
        std::string hashpw(const std::string& password, const std::string& salt);
        
        std::string gensalt(int32_t log_rounds, BCryptRandom& random);
        std::string gensalt(int32_t log_rounds);
        std::string gensalt();
        bool checkpw(const std::string& plaintext, const std::string& hashed);

    private:
        
        std::string encode_base64(const std::vector<int32_t>& data, const size_t& len);
        std::vector<int32_t> decode_base64(std::string s, int maxolen);
        void encipher(std::vector<int64_t>& lr, int off);
        int64_t streamtoword(std::vector<int32_t> data, std::vector<int32_t>& offp);
        
        void init_key();
        void key(std::vector<int32_t>& key);
        void ekskey(std::vector<int32_t> data, std::vector<int32_t> key);
        
        int8_t char64(char x);
        
        std::vector<int64_t> P;
        std::vector<int64_t> S;
        
    };
    
    
    
    
    
    
    

//        /**
//         Generates a random number between low and high and places it into the receiver.
//         
//         :param: first   The first
//         :param: second  The second
//         
//         :returns: Int32  Random 32-bit number
//         */
//        class func generateNumberBetween(_ first: Int32, _ second: Int32) -> Int32 {
//            var low : Int32
//            var high : Int32
//            
//            if first <= second {
//                low  = first
//                high = second
//            }
//                else {
//                    low  = second
//                    high = first
//                }
//                
//                let modular = UInt32((high - low) + 1)
//                let random : UInt32 = arc4random()
//                
//                return Int32(random % modular) + low
//                }
//                
//            /**
//             Generates an optionally unique sequence of random numbers between low and high and places them into the sequence.
//             
//             :param: length      The length of the sequence (must be at least 1)
//             :param: low         The low number (must be lower or equal to high).
//             :param: high        The high number (must be equal or higher than low).
//             :param: onlyUnique  TRUE if only unique values are to be generated, FALSE otherwise.
//             
//             The condition is checked that if `onlyUnique` is TRUE the `length` cannot exceed the range of `low` to `high`.
//             
//             :returns: [Int32]
//             */
//                class func generateNumberSequenceBetween(_ first: Int32, _ second: Int32, ofLength length: Int, withUniqueValues unique: Bool) -> [Int32] {
//                    if length < 1 {
//                        return [Int32]()
//                    }
//                    
//                    var sequence : [Int32] = [Int32](repeating: 0, count: length)
//                    if unique {
//                        if (first <= second && (length > (second - first) + 1)) ||
//                            (first > second  && (length > (first - second) + 1)) {
//                                return [Int32]()
//                            }
//                        
//                        var loop : Int = 0
//                        while loop < length {
//                            let number = JKBCryptRandom.generateNumberBetween(first, second)
//                            
//                            // If the number is unique, add it to the sequence
//                            if !JKBCryptRandom.isNumber(number, inSequence: sequence, ofLength: loop) {
//                                sequence[loop] = number
//                                loop += 1
//                            }
//                        }
//                    }
//                    else {
//                        // Repetitive values are allowed
//                        for i in 0 ..< length {
//                            sequence[i] = JKBCryptRandom.generateNumberBetween(first, second)
//                        }
//                    }
//                    
//                    return sequence
//                }
//                
//            /**
//             Randomly chooses a number from the provided sequence and places it into the receiver.
//             
//             :param: sequence    The sequence selected from (must not be nil and must be of at least `length` elements)
//             :param: length      The length of the sequence (must be at least 1)
//             
//             :returns: Int? Int if `length` is properly set and `sequence` is not nil; nil otherwise.
//             */
//                class func chooseNumberFromSequence(_ sequence: [Int32], ofLength length: Int) -> Int32? {
//                    if length < 1 || length > sequence.count {
//                        return nil
//                    }
//                    
//                    // Generate a random index into the sequence
//                    let number = JKBCryptRandom.generateNumberBetween(0, Int32(length - 1))
//                    
//                    return sequence[Int(number)]
//                }
//                
//            /**
//             Returns true if the provided number appears within the sequence.
//             
//             :param: number      The number to search for in the sequence.
//             :param: sequence    The sequence to search in (must not be nil and must be of at least `length` elements)
//             :param: length      The length of the sequence to test (must be at least 1)
//             
//             :returns: Bool      TRUE if `number` is found in sequence, FALSE if not found.
//             */
//                class func isNumber(_ number: Int32, inSequence sequence: [Int32], ofLength length: Int) -> Bool {
//                    if length < 1 || length > sequence.count {
//                        return false
//                    }
//                    
//                    for i in 0 ..< length {
//                        if sequence[i] == number {
//                            // The number was found, return true
//                            return true
//                        }
//                    }
//                    
//                    // The number was not found, return false
//                    return false
//                }
//                
//            /**
//             Returns an NSData populated with bytes whose values range from 0 to 255.
//             
//             :param: length  The length of the resulting NSData (must be at least 1)
//             
//             :returns: NSData   NSData containing random bytes.
//             */
//                class func generateRandomDataOfLength(_ length: Int) -> Data {
//                    if length < 1 {
//                        return Data()
//                    }
//                    
//                    var sequence = JKBCryptRandom.generateNumberSequenceBetween(0, 255, ofLength: length, withUniqueValues: false)
//                    var randomData : [UInt8] = [UInt8](repeating: 0, count: length)
//                    
//                    for i in 0 ..< length {
//                        randomData[i] = UInt8(sequence[i])
//                    }
//                    
//                    return Data(bytes: UnsafePointer<UInt8>(randomData), count:length)
//                }
//                
//            /**
//             Returns an NSData populated with bytes whose values range from -128 to 127.
//             
//             :param: length  The length of the resulting NSData (must be at least 1)
//             
//             :returns: NSData   NSData containing random signed bytes.
//             */
//                class func generateRandomSignedDataOfLength(_ length: Int) -> Data {
//                    if length < 1 {
//                        return Data()
//                    }
//                    
//                    var sequence = JKBCryptRandom.generateNumberSequenceBetween(-128, 127, ofLength: length, withUniqueValues: false)
//                    var randomData : [Int8] = [Int8](repeating: 0, count: length)
//                    
//                    for i in 0 ..< length {
//                        randomData[i] = Int8(sequence[i])
//                    }
//                    
//                    return Data(bytes:randomData, count:length)
//                }
//                
//            /**
//             Returns a String populated with random characters.
//             
//             :param: length  The length of the resulting String (must be at least 1)
//             
//             :returns: String   String containing random ASCII encoded characters.
//             */
//                class func generateRandomStringOfLength(_ length: Int) -> String {
//                    if length < 1 {
//                        return String()
//                    }
//                    
//                    var sequence = JKBCryptRandom.generateNumberSequenceBetween(0, 255, ofLength: length, withUniqueValues: false)
//                    var randomString : String = String()
//                    
//                    for i in 0 ..< length {
//                        let nextCharacter = UnicodeScalar(UInt8(sequence[i]))
//                        randomString.append(String(nextCharacter))
//                    }
//                    
//                    // init?<S : SequenceType where UInt8 == UInt8>(bytes: S, encoding: NSStringEncoding)
//                    
//                    return randomString
//                }
//                }
    
    
    
    
}


#endif /* bcrypt_hpp */
