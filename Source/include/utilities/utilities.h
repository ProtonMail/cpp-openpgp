#ifndef __pm_openpgp__utilities__
#define __pm_openpgp__utilities__

#include <stdio.h>
#include <string>

#endif




namespace ProtonMail {

    
    
    
    std::string encrypt_mailbox_password(std::string plaintext, std::string salt_value);
    std::string decrypt_mailbox_password(std::string enc_value, std::string salt_value);


    


}
