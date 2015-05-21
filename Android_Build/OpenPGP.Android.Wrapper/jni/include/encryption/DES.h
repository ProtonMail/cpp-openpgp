#ifndef __DES__
#define __DES__

#include <algorithm>

#include <utilities/includes.h>
#include <encryption/SymAlg.h>
#include <encryption/DES_Const.h>

class DES : public SymAlg{
    private:
        uint64_t keys[16];
        std::string run(const std::string & data);

    public:
        DES();
        DES(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
