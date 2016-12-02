//
//  folded_line_writer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
        bool _lineLengthEnabled = true;
        
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
