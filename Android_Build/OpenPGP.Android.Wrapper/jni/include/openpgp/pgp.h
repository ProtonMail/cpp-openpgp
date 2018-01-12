//
//  pgp.h
//  UNNetPGP
//
//  Created by Yanfeng Zhang on 1/21/15.
//  Copyright (c) 2015 UP-NEXT. All rights reserved.
//

#ifndef __UNNetPGP__pgp__
#define __UNNetPGP__pgp__

#include <stdio.h>


#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <utility>

#include <config/rfc4880_ascii_armor.h>

#include <utilities/consts.h>
#include <openpgp/pgptime.h>
#include <utilities/radix64.h>
#include <package/packet.h>
#include <base/BaseObject.h>


class PGP : public BaseObject{
protected:
    bool armored;                                                     // default true
    uint8_t ASCII_Armor;                                              // what type of key is this
    std::vector <std::pair <std::string, std::string> > Armor_Header; // messages in the header
    std::vector <Packet::Ptr> packets;                                // main data
    
    // modifies output string so each line is no longer than MAX_LINE_SIZE long
    std::string format_string(std::string data, uint8_t line_length = MAX_LINE_LENGTH) const;
    
public:
    typedef std::shared_ptr <PGP> Ptr;
    
    PGP();
    PGP(const PGP & copy);                                  // clone another PGP instance
    PGP(std::string & data, bool isRaw = false);                                // data fed into this constructor will be consumed
    PGP(std::ifstream & f);                                 // read from file; file not modified
    ~PGP();
    
    void read(std::string & data);                          // read base64 key, including ASCII Armor; some data is consumed
    void read(std::ifstream & file);                        // read base64 key from file; file not modified
    void read_raw(std::string & data);                      // read binary data; data is consumed; called by read()
    void read_raw(std::ifstream & file);                    // read binary data from file; file not modified
    virtual std::string show(const uint8_t indents = 0, const uint8_t indent_size = 4) const;   // display information; indents is used to tab the output if desired
    virtual std::string raw(const uint8_t header = 0, const uint8_t tag = 255) const;                                    // write packets only; header is for writing default (0), old (1) or new (2) header formats    tag the package filter
    virtual std::string write(const uint8_t armor = 0, const uint8_t header = 0, const uint8_t tag = 255) const;         // armor: use default = 0, no armor = 1, armored = 2; header: same as raw()

    // Accessors
    bool get_armored() const;
    uint8_t get_ASCII_Armor() const;
    std::vector <std::pair <std::string, std::string> > get_Armor_Header() const;
    std::vector <Packet::Ptr> get_packets() const;          // get copy of all packet pointers (for looping through packets)
    std::vector <Packet::Ptr> get_packets_clone() const;    // clone all packets (for modifying packets)
    void update_packet(int index, Packet::Ptr ptr); //sort term.
    
    // Modifiers
    void set_armored(const bool a);
    void set_ASCII_Armor(const uint8_t armor);
    void set_Armor_Header(const std::vector <std::pair <std::string, std::string> > & header);
    void set_packets(const std::vector <Packet::Ptr> & p);  // clones the input packets
    
    virtual bool meaningful() const = 0;                    // check if packet sequence is meaningful and correct
    
    PGP & operator=(const PGP & copy);                      // get deep copy object
    virtual Ptr clone() const = 0;                          // get deep copy pointer
};




#endif /* defined(__UNNetPGP__pgp__) */
