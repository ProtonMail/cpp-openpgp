//
//  rfc4880_ascii_armor.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/4/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef rfc4880_ascii_armor_h
#define rfc4880_ascii_armor_h

#include <exception>
#include <string>
#include <vector>

// protonmail customize header
const std::string protonmail_cryoto_headerMessage = "---BEGIN ENCRYPTED MESSAGE---";
const std::string protonmail_cryoto_tailMessage = "---END ENCRYPTED MESSAGE---";
const std::string protonmail_cryoto_headerRandomKey = "---BEGIN ENCRYPTED RANDOM KEY---";
const std::string protonmail_cryoto_tailRandomKey = "---END ENCRYPTED RANDOM KEY---";


enum ASCII_ARMOR {
    MESSAGE = 0,
    PUBLIC_KEY = 1,
    PRIVATE_KEY = 2,
    MESSAGE_PART_X_Y = 3,
    MESSAGE_PART_X = 4,
    SIGNATURE = 5,
    SIGNED_MESSAGE = 6,
    MAX
};

inline const std::string toString(ASCII_ARMOR v)
{
    switch (v)
    {
        case MESSAGE:   return "MESSAGE";
        case PUBLIC_KEY:   return "PUBLIC KEY BLOCK";
        case PRIVATE_KEY: return "PRIVATE KEY BLOCK";
        case MESSAGE_PART_X_Y: return "MESSAGE, PART X/Y";
        case MESSAGE_PART_X: return "MESSAGE, PART X";
        case SIGNATURE: return "SIGNATURE";
        case SIGNED_MESSAGE: return "SIGNED MESSAGE";
        default:
            throw std::runtime_error("Error: armor type is not supported");
    }
}
//
//const std::vector<std::string> supported_ascii_armor = {
//    "MESSAGE",                               // Used for signed, encrypted, or compressed files.
//    "PUBLIC KEY BLOCK",                      // Used for armoring public keys.
//    "PRIVATE KEY BLOCK",                     // Used for armoring private keys.
//    "MESSAGE, PART X/Y",                     // Used for multi-part messages, where the armor is split amongst Y parts, and this is the Xth part out of Y.
//    "MESSAGE, PART X",                       // Used for multi-part messages, where this is the Xth part of an unspecified number of parts. Requires the MESSAGE-ID Armor Header to be used.
//    "SIGNATURE",                             // Used for detached signatures, OpenPGP/MIME signatures, and cleartext signatures. Note that PGP 2.x uses BEGIN PGP MESSAGE for detached signatures.
//    "SIGNED MESSAGE",                        // Used for cleartext signatures; header not really part of RFC 4880.
//};


//// ASCII data at beginning and end of OpenPGP packet
//const std::string ASCII_Armor_Header[7] = {
//    "MESSAGE",                               // Used for signed, encrypted, or compressed files.
//    "PUBLIC KEY BLOCK",                      // Used for armoring public keys.
//    "PRIVATE KEY BLOCK",                     // Used for armoring private keys.
//    "MESSAGE, PART X/Y",                     // Used for multi-part messages, where the armor is split amongst Y parts, and this is the Xth part out of Y.
//    "MESSAGE, PART X",                       // Used for multi-part messages, where this is the Xth part of an unspecified number of parts. Requires the MESSAGE-ID Armor Header to be used.
//    "SIGNATURE",                             // Used for detached signatures, OpenPGP/MIME signatures, and cleartext signatures. Note that PGP 2.x uses BEGIN PGP MESSAGE for detached signatures.
//    "SIGNED MESSAGE",                        // Used for cleartext signatures; header not really part of RFC 4880.
//};



// ASCII descriptor of OpenPGP packet
const std::string ASCII_Armor_Key[5] = {
    "Version",                              // which states the OpenPGP implementation and version used to encode the message.
    
    "Comment",                              // a user-defined comment. OpenPGP defines all text to be in UTF-8. A comment may be any UTF-8 string. However, the whole point of armoring is to provide seven-bit-clean data.
    // Consequently, if a comment has characters that are outside the US-ASCII range of UTF, they may very well not survive transport.
    
    "MessageID",                            // a 32-character string of printable characters. The string must be the same for all parts of a multi-part message that uses the "PART X" Armor Header. MessageID strings should be
    // unique enough that the recipient of the mail can associate all the parts of a message with each other. A good checksum or cryptographic hash function is sufficient.
    // The MessageID SHOULD NOT appear unless it is in a multi-part message. If it appears at all, it MUST be computed from the finished (encrypted, signed, etc.) message in a deterministic
    // fashion, rather than contain a purely random value. This is to allow the legitimate recipient to determine that the MessageID cannot serve as a covert means of leaking cryptographic key
    // information.
    
    "Hash",                                 // a comma-separated list of hash algorithms used in this message. This is used only in cleartext signed messages.
    
    "Charset",                              // a description of the character set that the plaintext is in. Please note that OpenPGP defines text to be in UTF-8. An implementation will get best results by translating into and out
};


#endif /* rfc4880_ascii_armor_h */
