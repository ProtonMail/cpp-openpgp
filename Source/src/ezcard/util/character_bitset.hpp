//
//  character_bitset.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/18/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef character_bitset_hpp
#define character_bitset_hpp

#include <stdio.h>
#include <bitset>
#include <string>

class CharacterBitSet {
private:
    std::bitset<128> _bitSet;
    std::string _characters;
    
    std::hash<std::bitset<128>> hash_fn;
    
public:
    typedef std::shared_ptr<CharacterBitSet> Ptr;
    
    CharacterBitSet(const std::string& characters);
    std::string characters();
    std::bitset<128> bitSet();
    bool containsOnly(const std::string& string);
    bool containsOnly(const std::string& string, int startIndex);
    bool containsAny(const std::string& string);
    bool containsAny(const std::string& string, int startIndex);
    
    size_t hashCode();
    
    static void setRang(std::bitset<128>& bits, int from, int end);
    
    //    @Override
    //    public boolean equals(Object obj) {
    //        if (this == obj) return true;
    //        if (obj == null) return false;
    //        if (getClass() != obj.getClass()) return false;
    //        CharacterBitSet other = (CharacterBitSet) obj;
    //        return bitSet.equals(other.bitSet);
    //    }
    //
    //    @Override
    //    public String toString() {
    //        return characters;
    //    }
    
    bool operator==(const CharacterBitSet& rhs);

};

#endif /* character_bitset_hpp */
