//
//  quoted_printable.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include <ezvcard/util/quoted_printable.hpp>
#include <ctype.h>



std::string QuotedPrintable::encode(const std::string &input)
{
    auto c = _charset->getString(input);
    return _encode(c);
}


std::string QuotedPrintable::decode(const std::string &input)
{
    return _decode(input);
}


std::string QuotedPrintable::_encode(const std::string &input)
{
    std::stringstream ss;
    char byte;
    const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    for (int i = 0; i < input.length() ; ++i)
    {
        byte = input[i];
        
        if ((byte == 0x20) || ((byte >= 33) && (byte <= 126) && (byte != 61)))
        {
            ss << byte;
        }
        else
        {
            ss << '=';
            ss << hex[((byte >> 4) & 0x0F)];
            ss << hex[(byte & 0x0F)];
        }
    }
    return ss.str();
}


std::string QuotedPrintable::_decode(const std::string &input)
{
    //                    0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ?  @  A   B   C   D   E   F
    const int hexVal[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};
    
    std::stringstream ss;
    
    for (int i = 0; i < input.length(); ++i)
    {
        //if (input.at(i).toAscii() == '=')
        if (input[i] == '=')
        {
            auto h1 = (hexVal[input[++i] - '0'] << 4);
            auto h2 = hexVal[input[++i] - '0'];
            ss << (h1 + h2);
        }
        else
        {
            ss << input[i];
        }
    }
    
    return ss.str();
}

QuotedPrintable::QuotedPrintable(const Charset::Ptr& name) {
    _charset = name;
}

//
//
//
///**
// * BitSet of printable characters as defined in RFC 1521.
// */
//private static final BitSet PRINTABLE_CHARS = new BitSet(256);
//
//private static final BitSet CRLF_CHARS = new BitSet(256);
//
//private static final BitSet HEX_CHARS = new BitSet(256);
//
//private static final byte ESCAPE_CHAR = '=';
//
//private static final byte TAB = 9;
//
//private static final byte SPACE = 32;
//
//private static final byte CR = '\r';
//
//private static final byte LF = '\n';
//
//private static final int BYTES_PER_LINE = 76;
//
//// Static initializer for printable chars collection
//
//static {
//    // alpha characters
//    for (int i = 33; i <= 60; i++) {
//        PRINTABLE_CHARS.set(i);
//    }
//    for (int i = 62; i <= 126; i++) {
//        PRINTABLE_CHARS.set(i);
//    }
//    PRINTABLE_CHARS.set(TAB);
//    PRINTABLE_CHARS.set(SPACE);
//
//    CRLF_CHARS.set(CR);
//    CRLF_CHARS.set(LF);
//
//    // normalized hex is numeric & upper alpha
//    for (int i = 48; i <= 57; i++) {
//        HEX_CHARS.set(i);
//    }
//    for (int i = 65; i <= 70; i++) {
//        HEX_CHARS.set(i);
//    }
//}
//
//public QuotedPrintable() {
//    super("quoted-printable", StandardCodecs.aliases_QuotedPrintable);
//}

//private static class Decoder extends CodecDecoder {
//    public Decoder(Codec codec) {
//        super(codec);
//    }
//
//    public byte[] decode(byte[] encoded) {
//        if (encoded == null) {
//            return null;
//        }
//        ByteArrayOutputStream buffer = new ByteArrayOutputStream();
//        for (int i = 0; i < encoded.length; i++) {
//            int b = encoded[i];
//            if (PRINTABLE_CHARS.get(b) || CRLF_CHARS.get(b)) {
//                buffer.write(b);
//            } else {
//                if (b == ESCAPE_CHAR) {
//                    if ((++i) < encoded.length) {
//                        byte b1 = encoded[i];
//                        if (HEX_CHARS.get(b1)) {
//                            int u = Character.digit((char) b1, 16);
//                            if ((++i) < encoded.length) {
//                                byte b2 = encoded[i];
//                                if (HEX_CHARS.get(b2)) {
//                                    int l = Character.digit((char) encoded[i], 16);
//                                    buffer.write((char) ((u << 4) + l));
//                                } else {
//                                    Object[] arguments = {"quoted-printable"};
//                                    String message = ResourceBundle.formatResourceBundleMessage(QuotedPrintable.class,
//                                                                                                "CODEC_DECODER_MALFORMED_INPUT", arguments);
//                                    throw new MalformedInputException(message);
//                                }
//                            } else {
//                                Object[] arguments = {"quoted-printable"};
//                                String message = ResourceBundle.formatResourceBundleMessage(QuotedPrintable.class,
//                                                                                            "CODEC_DECODER_MALFORMED_INPUT", arguments);
//                                throw new MalformedInputException(message);
//                            }
//                        } else {
//                            // remove mta extra whitespace
//                            while (b1 != CR) {
//                                if (b1 != SPACE && b1 != TAB) {
//                                    Object[] arguments = {"quoted-printable"};
//                                    String message = ResourceBundle.formatResourceBundleMessage(QuotedPrintable.class,
//                                                                                                "CODEC_DECODER_MALFORMED_INPUT", arguments);
//                                    throw new MalformedInputException(message);
//                                }
//                                b1 = encoded[++i]; // eats the CR and WS
//                            }
//                            b1 = encoded[++i]; // eats the LF
//                            assert b1 == LF;
//                        }
//                    } else {
//                        Object[] arguments = {"quoted-printable"};
//                        String message = ResourceBundle.formatResourceBundleMessage(QuotedPrintable.class,
//                                                                                    "CODEC_DECODER_MALFORMED_INPUT", arguments);
//                        throw new MalformedInputException(message);
//                    }
//                } else {
//                    Object[] arguments = {"quoted-printable"};
//                    String message = ResourceBundle.formatResourceBundleMessage(QuotedPrintable.class,
//                                                                                "CODEC_DECODER_MALFORMED_INPUT", arguments);
//                    throw new MalformedInputException(message);
//                }
//            }
//        }
//        return buffer.toByteArray();
//    }
//}
//
//public CodecDecoder newDecoder() {
//    return new Decoder(this);
//}
//
//private static class Encoder extends CodecEncoder {
//    public Encoder(Codec codec) {
//        super(codec);
//    }
//
//    private void encodeQuotedPrintable(int b, ByteArrayOutputStream buffer) {
//        buffer.write(ESCAPE_CHAR);
//        char hex1 = Character.toUpperCase(Character.forDigit((b >> 4) & 0xF, 16));
//        char hex2 = Character.toUpperCase(Character.forDigit(b & 0xF, 16));
//        buffer.write(hex1);
//        buffer.write(hex2);
//    }
//
//    private void emitCRLF(ByteArrayOutputStream buffer) {
//        buffer.write('\r');
//        buffer.write('\n');
//    }
//
//    public byte[] encode(byte[] bytes) {
//        if (bytes == null) {
//            return null;
//        }
//        ByteArrayOutputStream buffer = new ByteArrayOutputStream();
//
//        final byte[] SOFT_LINE_BREAK = {'=', '\r', '\n'};
//
//        int count = 0;
//        boolean inCRLF = false;
//        for (int i = 0; i < bytes.length; i++) {
//            int b = bytes[i];
//            if (b < 0) {
//                b = 256 + b;
//            }
//            if (b == '\r') {
//                inCRLF = true;
//                emitCRLF(buffer);
//            } else {
//                if (b == '\n') {
//                    if (!inCRLF) {
//                        emitCRLF(buffer);
//                    }
//                } else if (PRINTABLE_CHARS.get(b)) {
//                    // subtract one for the soft line break
//                    if ((++count) > BYTES_PER_LINE - 1) {
//                        buffer.write(SOFT_LINE_BREAK, 0, SOFT_LINE_BREAK.length);
//                        count = 1;
//                    }
//                    buffer.write(b);
//                } else {
//                    // subtract one for the soft line break
//                    if ((count += 3) > BYTES_PER_LINE - 1) {
//                        buffer.write(SOFT_LINE_BREAK, 0, SOFT_LINE_BREAK.length);
//                        count = 3;
//                    }
//                    encodeQuotedPrintable(b, buffer);
//                }
//                inCRLF = false;
//            }
//        }
//        return buffer.toByteArray();
//    }
//}
//
//public CodecEncoder newEncoder() {
//    return new Encoder(this);
//}
