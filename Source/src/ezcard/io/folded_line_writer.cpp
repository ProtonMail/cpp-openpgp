//
//  folded_line_writer.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
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

#include <ezvcard/io/folded_line_writer.hpp>
#include <ezvcard/util/quoted_printable.hpp>

namespace vinnie {
    
    const std::string FoldedLineWriter::CRLF = "\r\n";
    
    
    /**
     * Creates a folded line writer.
     * @param writer the writer object to wrap
     */
    FoldedLineWriter::FoldedLineWriter(const std::shared_ptr<std::stringstream>& writer) {
        _writer = writer;
    }
    
    
    void FoldedLineWriter::writeln() {
        write(CRLF);
    }
    
    void FoldedLineWriter::write(std::string s) {
        write(s, false, nullptr);
    }
    
    void FoldedLineWriter::write(char s) {
        std::stringstream ss;
        ss << s;
        write(ss.str());
    }
    
    
    /**
     * Writes a string.
     * @param str the string to write
     * @param quotedPrintable true to encode the string in quoted-printable
     * encoding, false not to
     * @param charset the character set to use when encoding the string into
     * quoted-printable
     * @throws IOException if there's a problem writing to the output stream
     */
    void FoldedLineWriter::write(std::string str, bool quotedPrintable, Charset::Ptr charset) {
        write(str, 0, str.size(), quotedPrintable, charset);
    }
    
    /**
     * Writes a portion of an array of characters.
     * @param cbuf the array of characters
     * @param off the offset from which to start writing characters
     * @param len the number of characters to write
     * @throws IOException if there's a problem writing to the output stream
     */
    void FoldedLineWriter::write(std::string str, size_t off, size_t len) {
        write(str, off, len, false, nullptr);
    }
    
    /**
     * Writes a portion of an array of characters.
     * @param cbuf the array of characters
     * @param off the offset from which to start writing characters
     * @param len the number of characters to write
     * @param quotedPrintable true to encode the string in quoted-printable
     * encoding, false not to
     * @param charset the character set to use when encoding the string into
     * quoted-printable
     * @throws IOException if there's a problem writing to the output stream
     */
    void FoldedLineWriter::write(std::string cbuf, size_t off, size_t len, bool quotedPrintable, Charset::Ptr charset) {
        if (quotedPrintable) {
            std::string buff(cbuf, off, len);
            QuotedPrintable codec(charset);
            cbuf = codec.encode(buff);
            off = 0;
            len = cbuf.size();
        }
        
        if (_lineLengthEnabled == false) {
            /*
             * If line folding is disabled, then write directly to the Writer.
             */
            std::string buff(cbuf, off, len);
            *_writer.get() << buff;
            return;
        }
        
        int effectiveLineLength = _lineLength;
        if (quotedPrintable) {
            /*
             * Account for the "=" character that must be appended onto each
             * line.
             */
            effectiveLineLength -= 1;
        }
        
        int encodedCharPos = -1;
        auto start = off;
        auto end = off + len;
        for (auto i = start; i < end; i++) {
            char c = cbuf[i];
            
            /*
             * Keep track of the quoted-printable characters to prevent them
             * from being cut in two at a folding boundary.
             */
            if (encodedCharPos >= 0) {
                encodedCharPos++;
                if (encodedCharPos == 3) {
                    encodedCharPos = -1;
                }
            }
            
            if (c == '\n') {
                
                std::string buff(cbuf, start, i - start + 1);
                *_writer.get() << buff;
                
                _curLineLength = 0;
                start = i + 1;
                continue;
            }
            
            if (c == '\r') {
                if (i == end - 1 || cbuf[i + 1] != '\n') {
                    std::string buff(cbuf, start, i - start + 1);
                    *_writer.get() << buff;
                    
                    _curLineLength = 0;
                    start = i + 1;
                } else {
                    _curLineLength++;
                }
                continue;
            }
            
            if (c == '=' && quotedPrintable) {
                encodedCharPos = 0;
            }
            
            if (_curLineLength >= effectiveLineLength) {
                /*
                 * If the last characters on the line are whitespace, then
                 * exceed the max line length in order to include the whitespace
                 * on the same line.
                 *
                 * This is to prevent the whitespace from merging with the
                 * folding whitespace of the following folded line and
                 * potentially being lost.
                 *
                 * Old syntax style allows multiple whitespace characters to be
                 * used for folding, so it could get lost here. New syntax style
                 * only allows one character to be used.
                 */
                if (isWhitespace(c)) {
                    while (isWhitespace(c) && i < end - 1) {
                        i++;
                        c = cbuf[i];
                    }
                    if (i >= end - 1) {
                        /*
                         * The rest of the char array is whitespace, so leave
                         * the loop.
                         */
                        break;
                    }
                }
                
                /*
                 * If we are in the middle of a quoted-printable encoded
                 * character, then exceed the max line length so the sequence
                 * doesn't get split up across multiple lines.
                 */
                if (encodedCharPos > 0) {
                    i += 3 - encodedCharPos;
                    if (i >= end - 1) {
                        /*
                         * The rest of the char array was a quoted-printable
                         * encoded char, so leave the loop.
                         */
                        break;
                    }
                }
                
                /*TODO::fix later
                 * If the last char is the low (second) char in a surrogate
                 * pair, don't split the pair across two lines.
                 */
                //            if (Character.isLowSurrogate(c)) {
                //                i++;
                //                if (i >= end - 1) {
                //                    /*
                //                     * Surrogate pair finishes the char array, so leave the
                //                     * loop.
                //                     */
                //                    break;
                //                }
                //            }
                
                
                std::string buff(cbuf, start, i - start);
                *_writer.get() << buff;
                
                if (quotedPrintable) {
                    *_writer.get() << '=';
                }
                
                *_writer.get() << CRLF;
                
                /*
                 * Do not include indentation whitespace if the value is
                 * quoted-printable.
                 */
                _curLineLength = 1;
                if (!quotedPrintable) {
                    
                    *_writer.get() << _indent;
                    _curLineLength = _indent.size() + 1;
                }
                start = i;
                
                continue;
            }
            
            _curLineLength++;
        }
        std::string buff(cbuf, start, end - start);
        *_writer.get() << buff;
    }
    
    /**
     * Gets the maximum length a line can be before it is folded (excluding the
     * newline, defaults to 75).
     * @return the line length or null if folding is disabled
     */
    int8_t FoldedLineWriter::getLineLength() {
        return _lineLength;
    }
    
    /**
     * Sets the maximum length a line can be before it is folded (excluding the
     * newline, defaults to 75).
     * @param lineLength the line length or null to disable folding
     * @throws IllegalArgumentException if the line length is less than or equal
     * to zero, or the line length is less than the length of the indent string
     */
    void FoldedLineWriter::setLineLength(int8_t lineLength) {
        if (lineLength <= 0) {
            throw std::invalid_argument("Line length must be greater than 0.");
        }
        if (lineLength <= _indent.size()) {
            throw std::invalid_argument("Line length must be greater than indent string length.");
        }
        _lineLength = lineLength;
        _lineLengthEnabled = true;
    }
    
    void FoldedLineWriter::disableLineLength() {
        _lineLengthEnabled = false;
    }
    
    bool FoldedLineWriter::isWhitespace(char ch) {
        return ch == ' ' || ch == '\t';
    }
    
    /**
     * Gets the string that is prepended to each folded line (defaults to a
     * single space character).
     * @return the indent string
     */
    std::string FoldedLineWriter::getIndent() {
        return _indent;
    }
    
    /**
     * Sets the string that is prepended to each folded line (defaults to a
     * single space character).
     * @param indent the indent string (cannot be empty, may only contain tabs
     * and spaces). Note that data streams using {@link SyntaxStyle#NEW} syntax
     * MUST use an indent string that contains EXACTLY ONE character.
     * @throws IllegalArgumentException if the indent string is empty, or the
     * length of the indent string is greater than the max line length, or the
     * indent string contains illegal characters
     */
    void FoldedLineWriter::setIndent(std::string indent) {
        if (indent.size() == 0) {
            throw std::invalid_argument("Indent string cannot be empty.");
        }
        
        if (_lineLengthEnabled == true && indent.size() >= _lineLength) {
            throw std::invalid_argument("Indent string length must be less than the line length.");
        }
        
        for (int i = 0; i < indent.length(); i++) {
            char c = indent[i];
            switch (c) {
                case ' ':
                case '\t':
                    break;
                default:
                    throw std::invalid_argument("Indent string can only contain tabs and spaces.");
            }
        }
        
        _indent = indent;
    }
    
    /**
     * Gets the wrapped {@link Writer} object.
     * @return the writer object
     */
    std::shared_ptr<std::stringstream> FoldedLineWriter::getWriter() {
        return _writer;
    }
    
}
