/*
Hash.h
Base class for inheritance

Copyright (c) 2013 Jason Lee

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __HASH__
#define __HASH__

#include <iostream>
#include <memory>

#include "includes.h"

class Hash{
    public:
        typedef std::shared_ptr<Hash> Ptr;

        Hash();
        virtual ~Hash();
        virtual void update(const std::string & str) = 0;
        virtual std::string hexdigest() = 0;
        std::string digest();
        virtual unsigned int blocksize() const = 0;  // blocksize in bits
        virtual unsigned int digestsize() const = 0; // digest size in bits

    protected:
        std::string stack;
        uint64_t clen;
};
#endif
