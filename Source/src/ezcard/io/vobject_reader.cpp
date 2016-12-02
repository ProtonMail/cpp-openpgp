//
//  vobject_reader.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include <ezvcard/io/vobject_reader.hpp>

#include <utilities/utility.h>
#include <ezvcard/util/string_util.hpp>


namespace vinnie {
    
    
    
    VObjectReader::VObjectReader(const std::string& str, SyntaxRules syntaxRules) : _syntaxRules(syntaxRules) {
        _reader = std::istringstream(str);
        auto r = _reader.str();
        _stack = std::make_shared<ComponentStack>(syntaxRules.getDefaultSyntaxStyle());
        context = std::make_shared<Context>(_stack->_names);
        _buffer = std::make_shared<Buffer>();
        
        //    if (reader instanceof InputStreamReader) {
        //        InputStreamReader isr = (InputStreamReader) reader;
        //        defaultQuotedPrintableCharset = Charset.forName(isr.getEncoding());
        //    } else {
        //        defaultQuotedPrintableCharset = Charset.defaultCharset();
        //    }
    }
    
    VObjectReader::~VObjectReader() {
        
    }
    
    //    /**
    //     * <p>
    //     * Gets the default character set to use when decoding quoted-printable
    //     * values of properties that lack CHARSET parameters, or of properties whose
    //     * CHARSET parameters are not recognized by the local JVM.
    //     * </p>
    //     * <p>
    //     * By default, this is set to the character set of the {@link Reader} object
    //     * that this class was constructed with. If the character set of the
    //     * {@link Reader} object could not be determined, then it will be set to the
    //     * local JVM's default character set.
    //     * </p>
    //     * @return the default quoted-printable character set
    //     */
    //    public Charset getDefaultQuotedPrintableCharset() {
    //        return defaultQuotedPrintableCharset;
    //    }
    //
    //    /**
    //     * <p>
    //     * Sets the character set to use when decoding quoted-printable values of
    //     * properties that lack CHARSET parameters, or of properties whose CHARSET
    //     * parameters are not recognized by the local JVM.
    //     * </p>
    //     * <p>
    //     * By default, this is set to the character set of the {@link Reader} object
    //     * that this class was constructed with. If the character set of the
    //     * {@link Reader} object could not be determined, then it will be set to the
    //     * local JVM's default character set.
    //     * </p>
    //     * @param charset the default quoted-printable character set (cannot be
    //     * null)
    //     */
    //    public void setDefaultQuotedPrintableCharset(Charset charset) {
    //        defaultQuotedPrintableCharset = charset;
    //    }
    //
    
    
    
    /**
     * <p>
     * Gets whether the reader will decode parameter values that use circumflex
     * accent encoding (enabled by default). This escaping mechanism allows
     * newlines and double quotes to be included in parameter values. It is only
     * supported by new style syntax.
     * </p>
     *
     * <table class="simpleTable">
     * <caption>Characters encoded by circumflex accent encoding</caption>
     * <tr>
     * <th>Raw Character</th>
     * <th>Encoded Character</th>
     * </tr>
     * <tr>
     * <td>{@code "}</td>
     * <td>{@code ^'}</td>
     * </tr>
     * <tr>
     * <td><i>newline</i></td>
     * <td>{@code ^n}</td>
     * </tr>
     * <tr>
     * <td>{@code ^}</td>
     * <td>{@code ^^}</td>
     * </tr>
     * </table>
     *
     * <p>
     * Example:
     * </p>
     *
     * <pre>
     * GEO;X-ADDRESS="Pittsburgh Pirates^n115 Federal St^nPittsburgh, PA 15212":40.446816;80.00566
     * </pre>
     *
     * @return true if circumflex accent decoding is enabled, false if not
     * @see <a href="http://tools.ietf.org/html/rfc6868">RFC 6868</a>
     */
    bool VObjectReader::isCaretDecodingEnabled() {
        return _caretDecodingEnabled;
    }
    
    /**
     * <p>
     * Sets whether the reader will decode parameter values that use circumflex
     * accent encoding (enabled by default). This escaping mechanism allows
     * newlines and double quotes to be included in parameter values. It is only
     * supported by new style syntax.
     * </p>
     *
     * <table class="simpleTable">
     * <caption>Characters encoded by circumflex accent encoding</caption>
     * <tr>
     * <th>Raw Character</th>
     * <th>Encoded Character</th>
     * </tr>
     * <tr>
     * <td>{@code "}</td>
     * <td>{@code ^'}</td>
     * </tr>
     * <tr>
     * <td><i>newline</i></td>
     * <td>{@code ^n}</td>
     * </tr>
     * <tr>
     * <td>{@code ^}</td>
     * <td>{@code ^^}</td>
     * </tr>
     * </table>
     *
     * <p>
     * Example:
     * </p>
     *
     * <pre>
     * GEO;X-ADDRESS="Pittsburgh Pirates^n115 Federal St^nPittsburgh, PA 15212":geo:40.446816,-80.00566
     * </pre>
     *
     * @param enable true to use circumflex accent decoding, false not to
     * @see <a href="http://tools.ietf.org/html/rfc6868">RFC 6868</a>
     */
    void VObjectReader::setCaretDecodingEnabled(bool enable) {
        _caretDecodingEnabled = enable;
    }
    
    
    
    /**
     * <p>
     * Starts or continues to parse the data off the input stream.
     * </p>
     * <p>
     * This method blocks until one of the following events happen:
     * </p>
     * <ol>
     * <li>The end of the input stream has been reached or</li>
     * <li>One of the methods in the given {@link VObjectDataListener}
     * implementation has invoked {@link Context#stop()}.</li>
     * </ol>
     * @param listener callback interface for handling data as it is read off
     * the input stream
     * @throws IOException if there's a problem reading from the input stream
     */
    void VObjectReader::parse(const VObjectDataListener::Ptr& listener) {
        context->_stop = false;
        while (!_eos && !context->_stop) {
            context->_lineNumber = _lineNumber;
            _buffer->clear();
            context->unfoldedLine->clear();
            
            VObjectProperty::Ptr property = parseProperty(listener);
            if (context->unfoldedLine->size() == 0) {
                //input stream was empty
                return;
            }
            
            if (property == nullptr) {
                if (listener != nullptr) {
                    listener->onWarning(Warning::MALFORMED_LINE, nullptr, nullptr, context);
                }
                continue;
            }
            
            /*
             * Note: Property names are trimmed when checking for BEGIN and END
             * properties because old style syntax allows there to be whitespace
             * around the colon character for these two properties. Component
             * names are trimmed for the same reason.
             */
            auto name = property->getName();
            name = ProtonMail::str_trim(name);
            if (str_equals("BEGIN", name)) {
                auto value = property->getValue();
                std::string componentName = str_to_upper(ProtonMail::str_trim(value));
                if (componentName.length() == 0) {
                    if (listener != nullptr) {
                        listener->onWarning(Warning::EMPTY_BEGIN, nullptr, nullptr, context);
                    }
                    continue;
                }
                if (listener != nullptr) {
                    listener->onComponentBegin(componentName, context);
                }
                _stack->push(componentName);
                continue;
            }
            
            if (str_equals("END", name)) {
                auto value = property->getValue();
                std::string componentName = str_to_upper(ProtonMail::str_trim(value));
                if (componentName.length() == 0) {
                    if (listener != nullptr) {
                        listener->onWarning(Warning::EMPTY_END, nullptr, nullptr, context);
                    }
                    continue;
                }
                
                //find the component that this END property matches up with
                auto popCount = _stack->popCount(componentName);
                if (popCount == 0) {
                    //END property does not match up with any BEGIN properties, so ignore
                    if (listener != nullptr) {
                        listener->onWarning(Warning::UNMATCHED_END, nullptr, nullptr, context);
                    }
                    continue;
                }
                
                while (popCount > 0) {
                    std::string poppedName = _stack->pop();
                    if (listener != nullptr) {
                        listener->onComponentEnd(poppedName, context);
                    }
                    popCount--;
                }
                continue;
            }
            
            if (str_equals("VERSION", name)) {
                std::string parentComponent = _stack->peekName();
                if (_syntaxRules.hasSyntaxRules(parentComponent)) {
                    SyntaxStyle style = _syntaxRules.getSyntaxStyle(parentComponent, property->getValue());
                    if (style == NONE) {
                        if (listener != nullptr) {
                            listener->onWarning(Warning::UNKNOWN_VERSION, property, nullptr, context);
                        }
                    } else {
                        if (listener != nullptr) {
                            listener->onVersion(property->getValue(), context);
                        }
                        _stack->updateSyntax(style);
                        continue;
                    }
                }
            }
            
            if (listener != nullptr) {
                listener->onProperty(property, context);
            }
        }
    }
    
    
    /**
     * Parses the next property off the input stream.
     * @param listener the data listener (for reporting warnings)
     * @return the parsed property or null if the property could not be parsed
     * @throws IOException if there was a problem reading from the input stream
     */
    const VObjectProperty::Ptr VObjectReader::parseProperty(const VObjectDataListener::Ptr& listener) {
        VObjectProperty::Ptr property_ = std::make_shared<VObjectProperty>();
        
        /*
         * The syntax style to assume the data is in.
         */
        SyntaxStyle syntax_ = _stack->peekSyntax();
        
        /*
         * The name of the parameter we're currently inside of.
         */
        std::string curParamName_ = "";
        
        /*
         * The character that was used to escape the current character (for
         * parameter values).
         */
        char paramValueEscapeChar_ = 0;
        
        /*
         * Are we currently inside a parameter value that is surrounded with
         * double-quotes?
         */
        bool inQuotes_ = false;
        
        /*
         * Are we currently inside the property value?
         */
        bool inValue_ = false;
        
        /*
         * Does the line use quoted-printable encoding, and does it end all of
         * its folded lines with a "=" character?
         */
        bool foldedQuotedPrintableLine_ = false;
        
        /*
         * Are we currently inside the whitespace that prepends a folded line?
         */
        bool inFoldedLineWhitespace_ = false;
        
        /*
         * The current character.
         */
        char ch_ = 0;
        
        /*
         * The previous character.
         */
        char prevChar_;
        
        while (true) {
            prevChar_ = ch_;
            int read = nextChar();
            if (read < 0) {
                //end of stream
                _eos = true;
                break;
            }
            
            ch_ = (char) read;
            if (prevChar_ == '\r' && ch_ == '\n') {
                /*
                 * The newline was already processed when the "\r" character was
                 * encountered, so ignore the accompanying "\n" character.
                 */
                continue;
            }
            
            if (isNewline(ch_)) {
                foldedQuotedPrintableLine_ = (inValue_ && prevChar_ == '=' && property_->getParameters()->isQuotedPrintable());
                if (foldedQuotedPrintableLine_) {
                    /*
                     * Remove the "=" character that sometimes appears at the
                     * end of quoted-printable lines that are followed by a
                     * folded line.
                     */
                    auto b = _buffer->get();
                    _buffer->chop();
                    context->unfoldedLine->chop();
                }
                
                //keep track of the current line number
                _lineNumber++;
                
                continue;
            }
            
            if (isNewline(prevChar_)) {
                if (isWhitespace(ch_)) {
                    /*
                     * This line is a continuation of the previous line (the
                     * line is folded).
                     */
                    inFoldedLineWhitespace_ = true;
                    continue;
                }
                
                if (foldedQuotedPrintableLine_) {
                    /*
                     * The property's parameters indicate that the property
                     * value is quoted-printable. And the previous line ended
                     * with an equals sign. This means that folding whitespace
                     * may not be prepended to folded lines like it should.
                     */
                } else {
                    /*
                     * We're reached the end of the property.
                     */
                    _leftOver = ch_;
                    break;
                }
            }
            
            if (inFoldedLineWhitespace_) {
                if (isWhitespace(ch_) && syntax_ == SyntaxStyle::OLD) {
                    /*
                     * 2.1 allows multiple whitespace characters to be used for
                     * folding (section 2.1.3).
                     */
                    continue;
                }
                inFoldedLineWhitespace_ = false;
            }
            
            context->unfoldedLine->append(ch_);
            if (inValue_) {
                _buffer->append(ch_);
                continue;
            }
            
            //decode escaped parameter value character
            if (paramValueEscapeChar_ != 0) {
                char escapeChar = paramValueEscapeChar_;
                paramValueEscapeChar_ = 0;
                
                switch (escapeChar) {
                    case '\\':
                        switch (ch_) {
                            case '\\':
                                _buffer->append(ch_);
                                continue;
                            case ';':
                                /*
                                 * Semicolons can only be escaped in old style parameter
                                 * values. If a new style parameter value has
                                 * semicolons, the value should be surrounded in double
                                 * quotes.
                                 */
                                _buffer->append(ch_);
                                continue;
                        }
                        break;
                    case '^':
                        switch (ch_) {
                            case '^':
                                _buffer->append(ch_);
                                continue;
                            case 'n':
                                //_buffer << NEWLine
                                //buffer.append(NEWLINE);
                                continue;
                            case '\'':
                                _buffer->append('"');
                                continue;
                        }
                        break;
                }
                
                /*
                 * Treat the escape character as a normal character because it's
                 * not a valid escape sequence.
                 */
                _buffer->append(escapeChar);
                _buffer->append(ch_);
                continue;
            }
            
            //check for a parameter value escape character
            if (!curParamName_.empty()) {
                switch (syntax_) {
                    case OLD:
                        if (ch_ == '\\') {
                            paramValueEscapeChar_ = ch_;
                            continue;
                        }
                        break;
                    case NEW:
                        if (ch_ == '^' && _caretDecodingEnabled) {
                            paramValueEscapeChar_ = ch_;
                            continue;
                        }
                        break;
                    default:
                        break;
                }
            }
            
            //set the group
            if (ch_ == '.' && property_->getGroup().empty() && property_->getName().empty()) {
                property_->setGroup(_buffer->getAndClear());
                continue;
            }
            
            if ((ch_ == ';' || ch_ == ':') && !inQuotes_) {
                if (property_->getName().empty()) {
                    //set the property name
                    property_->setName(_buffer->getAndClear());
                } else {
                    //set a parameter value
                    std::string paramValue = _buffer->getAndClear();
                    if (syntax_ == SyntaxStyle::OLD) {
                        //old style allows whitespace to surround the "=", so remove it
                        paramValue = ltrim(paramValue);
                    }
                    property_->getParameters()->put(curParamName_, paramValue);
                    curParamName_ = "";
                }
                
                if (ch_ == ':') {
                    //the rest of the line is the property value
                    inValue_ = true;
                }
                continue;
            }
            
            if (!property_->getName().empty()) {
                //it's a multi-valued parameter
                if (ch_ == ',' && !curParamName_.empty() && !inQuotes_ && syntax_ != SyntaxStyle::OLD) {
                    std::string paramValue = _buffer->getAndClear();
                    property_->getParameters()->put(curParamName_, paramValue);
                    continue;
                }
                
                //set the parameter name
                if (ch_ == '=' && curParamName_.empty()) {
                    std::string paramName = str_to_lower( _buffer->getAndClear() );
                    if (syntax_ == SyntaxStyle::OLD) {
                        //old style allows whitespace to surround the "=", so remove it
                        paramName = rtrim(paramName);
                    }
                    curParamName_ = paramName;
                    continue;
                }
                
                //entering/leaving a double-quoted parameter value (new style only)
                if (ch_ == '"' && !curParamName_.empty() && syntax_ != SyntaxStyle::OLD) {
                    inQuotes_ = !inQuotes_;
                    continue;
                }
            }
            _buffer->append(ch_);
        }
        
        /*
         * Line or stream ended before the property value was reached.
         */
        if (!inValue_) {
            return nullptr;
        }
        
        property_->setValue(_buffer->getAndClear());
        if (property_->getParameters()->isQuotedPrintable()) {
            decodeQuotedPrintable(property_, listener);
        }
        
        return property_;
    }
    
    
    /**
     * Gets the next character in the input stream.
     * @return the next character or -1 if the end of the stream has been
     * reached
     * @throws IOException if there's a problem reading from the input stream
     */
    int VObjectReader::nextChar() {
        if (_leftOver >= 0) {
            /*
             * Use the character that was left over from the previous invocation
             * of "readLine()".
             */
            int ch = _leftOver;
            _leftOver = -1;
            return ch;
        }
        auto d = _reader.str();
        auto out = _reader.get();
        return out;
    }
    
    
    /**
     * Determines if the given character is a newline character.
     * @param ch the character
     * @return true if it's a newline character, false if not
     */
    bool VObjectReader::isNewline(char ch) {
        return ch == '\n' || ch == '\r';
    }
    
    /**
     * Determines if the given character is a space or a tab.
     * @param ch the character
     * @return true if it's a space or a tab, false if not
     */
    bool VObjectReader::isWhitespace(char ch) {
        return ch == ' ' || ch == '\t';
    }
    
    
    /**
     * Decodes the given property's value from quoted-printable encoding.
     * @param property the property
     * @param listener the data listener
     */
    void VObjectReader::decodeQuotedPrintable(const VObjectProperty::Ptr& property, const VObjectDataListener::Ptr& listener) {
        //    Charset charset = getCharset(property, listener);
        //    if (charset == null) {
        //        charset = defaultQuotedPrintableCharset;
        //    }
        //    
        //    String value = property.getValue();
        //    QuotedPrintableCodec codec = new QuotedPrintableCodec(charset.name());
        //    try {
        //        value = codec.decode(value);
        //    } catch (DecoderException e) {
        //        listener.onWarning(Warning.QUOTED_PRINTABLE_ERROR, property, e, context);
        //        return;
        //    }
        //    
        //    property.setValue(value);
        std::string value = property->getValue();
        //    QuotedPrintableCodec codec = new QuotedPrintableCodec(charset.name());
        try {
            value = ProtonMail::quote_printable_decode(value);
        } catch (std::exception& e) {
            if (listener != nullptr) {
                listener->onWarning(Warning::QUOTED_PRINTABLE_ERROR, property, &e, context);
            }
            return;
        }
        property->setValue(value);
    }
    //
    //    /**
    //     * Gets the character set the given property is encoded in.
    //     * @param property the property
    //     * @param listener the data listener
    //     * @return the character set or null if the character is not set or could
    //     * not be determined
    //     */
    //    private Charset getCharset(VObjectProperty property, VObjectDataListener listener) {
    //        Exception thrown;
    //        try {
    //            return property.getParameters().getCharset();
    //        } catch (IllegalCharsetNameException e) {
    //            //name contains illegal characters
    //            thrown = e;
    //        } catch (UnsupportedCharsetException e) {
    //            //not recognized by the JVM
    //            thrown = e;
    //        }
    //
    //        listener.onWarning(Warning.UNKNOWN_CHARSET, property, thrown, context);
    //        return null;
    //    }
    //
    
}
