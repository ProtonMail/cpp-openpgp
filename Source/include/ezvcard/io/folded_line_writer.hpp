//
//  folded_line_writer.hpp
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

#ifndef folded_line_writer_hpp
#define folded_line_writer_hpp

#include <stdio.h>
#include <sstream>
#include "charset.hpp"


namespace vinnie {
    
    /**
     * Automatically folds lines as they are written.
     * @author Michael Angstadt
     */
    class FoldedLineWriter {
    public:
        typedef std::shared_ptr<FoldedLineWriter> Ptr;
        
    private:
        const static std::string CRLF;
        
        std::shared_ptr<std::stringstream> _writer;
        
        int8_t _lineLength = 75;
        bool _lineLengthEnabled = false;
        
        std::string _indent = " ";
        int8_t _curLineLength = 0;
        
        
    public:
        FoldedLineWriter(const std::shared_ptr<std::stringstream>& writer);
        
        std::shared_ptr<std::stringstream> getWriter();
        
        void writeln();
        void write(std::string s);
        void write(char s);
        void write(std::string str, bool quotedPrintable, Charset::Ptr charset);
        void write(std::string cbuf, size_t off, size_t len);
        void write(std::string cbuf, size_t off, size_t len, bool quotedPrintable, Charset::Ptr charset);
        
        int8_t getLineLength();
        void setLineLength(int8_t lineLength);
        void disableLineLength();
        
        std::string getIndent();
        void setIndent(std::string indent);
        
        bool isWhitespace(char ch);
    };
    
}
#endif /* folded_line_writer_hpp */
