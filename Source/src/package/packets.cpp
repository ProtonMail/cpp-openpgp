#include <package/packets.h>

unsigned int partialBodyLen(uint8_t first_octet){
    return 1 << (first_octet & 0x1f);
}

std::string read_packet_header(std::string & data, uint8_t & tag, bool & format, uint8_t & partial){
    
  
    
   
//
//
//    // used for partial body lengths
//    var real_packet_length = -1;
//    if (!format) {
//        // 4.2.1. Old Format Packet Lengths
//        switch (packet_length_type) {
//            case 0:
//                // The packet has a one-octet length. The header is 2 octets
//                // long.
//                packet_length = input[mypos++];
//                break;
//            case 1:
//                // The packet has a two-octet length. The header is 3 octets
//                // long.
//                packet_length = (input[mypos++] << 8) | input[mypos++];
//                break;
//            case 2:
//                // The packet has a four-octet length. The header is 5
//                // octets long.
//                packet_length = (input[mypos++] << 24) | (input[mypos++] << 16) | (input[mypos++] <<
//                                                                                   8) | input[mypos++];
//                break;
//            default:
//                // 3 - The packet is of indeterminate length. The header is 1
//                // octet long, and the implementation must determine how long
//                // the packet is. If the packet is in a file, this means that
//                // the packet extends until the end of the file. In general,
//                // an implementation SHOULD NOT use indeterminate-length
//                // packets except where the end of the data will be clear
//                // from the context, and even then it is better to use a
//                // definite length, or a new format header. The new format
//                // headers described below have a mechanism for precisely
//                // encoding data of indeterminate length.
//                packet_length = len;
//                break;
//        }
//
//    } else // 4.2.2. New Format Packet Lengths
//    {
//
//        // 4.2.2.1. One-Octet Lengths
//        if (input[mypos] < 192) {
//            packet_length = input[mypos++];
//            util.print_debug("1 byte length:" + packet_length);
//            // 4.2.2.2. Two-Octet Lengths
//        } else if (input[mypos] >= 192 && input[mypos] < 224) {
//            packet_length = ((input[mypos++] - 192) << 8) + (input[mypos++]) + 192;
//            util.print_debug("2 byte length:" + packet_length);
//            // 4.2.2.4. Partial Body Lengths
//        } else if (input[mypos] > 223 && input[mypos] < 255) {
//            packet_length = 1 << (input[mypos++] & 0x1F);
//            util.print_debug("4 byte length:" + packet_length);
//            // EEEK, we're reading the full data here...
//            var mypos2 = mypos + packet_length;
//            bodydata = [input.subarray(mypos, mypos + packet_length)];
//            var tmplen;
//            while (true) {
//                if (input[mypos2] < 192) {
//                    tmplen = input[mypos2++];
//                    packet_length += tmplen;
//                    bodydata.push(input.subarray(mypos2, mypos2 + tmplen));
//                    mypos2 += tmplen;
//                    break;
//                } else if (input[mypos2] >= 192 && input[mypos2] < 224) {
//                    tmplen = ((input[mypos2++] - 192) << 8) + (input[mypos2++]) + 192;
//                    packet_length += tmplen;
//                    bodydata.push(input.subarray(mypos2, mypos2 + tmplen));
//                    mypos2 += tmplen;
//                    break;
//                } else if (input[mypos2] > 223 && input[mypos2] < 255) {
//                    tmplen = 1 << (input[mypos2++] & 0x1F);
//                    packet_length += tmplen;
//                    bodydata.push(input.subarray(mypos2, mypos2 + tmplen));
//                    mypos2 += tmplen;
//                } else {
//                    mypos2++;
//                    tmplen = (input[mypos2++] << 24) | (input[mypos2++] << 16) | (input[mypos2++] << 8) | input[mypos2++];
//                    bodydata.push(input.subarray(mypos2, mypos2 + tmplen));
//                    packet_length += tmplen;
//                    mypos2 += tmplen;
//                    break;
//                }
//            }
//            real_packet_length = mypos2 - mypos;
//            // 4.2.2.3. Five-Octet Lengths
//        } else {
//            mypos++;
//            packet_length = (input[mypos++] << 24) | (input[mypos++] << 16) | (input[mypos++] <<
//                                                                               8) | input[mypos++];
//        }
    
    

    uint8_t ctb = data[0]; // Name "ctb" came from Version 2 [RFC 1991]
    format = ctb & 0x40; // get packet length type (OLD = false 0; NEW = true 1)
    unsigned int remove = 1; // how much more stuff to remove from raw string
    size_t length = 0; // length of the data without the header
    std::string partialPacket = "";
    if (!partial) { // if partial continue packets have not been found
        if (!(ctb & 0x80)){
            throw std::runtime_error("Error: First bit of packet header MUST be 1.");
        }
        
        if (!format){ // Old length type RFC4880 sec 4.2.1
            // old format header
            tag = (ctb & 0x3F) >> 2; // bit 5-2 //tag = (ctb >> 2) & 15;// get tag value
            auto packet_length_type = ctb & 0x03; // bit 1-0
            
            switch (packet_length_type) {
                case 0:
                    // The packet has a one-octet length. The header is 2 octets long.
                    remove += 1;
                    length = static_cast <uint8_t> (data[1]);
                    break;
                case 1:
                    // The packet has a two-octet length. The header is 3 octets long.
                    remove += 2;
                    length = static_cast<size_t>(toint(data.substr(1, 2), 256));
                    break;
                case 2:
                    // The packet has a four-octet length. The header is 5 octets long.
                    remove += 5;
                    length = static_cast<size_t>(toint(data.substr(2, 5), 256));
                    break;
                default:
                    // 3 - The packet is of indeterminate length. The header is 1
                    // octet long, and the implementation must determine how long
                    // the packet is. If the packet is in a file, this means that
                    // the packet extends until the end of the file. In general,
                    // an implementation SHOULD NOT use indeterminate-length
                    // packets except where the end of the data will be clear
                    // from the context, and even then it is better to use a
                    // definite length, or a new format header. The new format
                    // headers described below have a mechanism for precisely
                    // encoding data of indeterminate length.
                    length = data.size() - 1;
                    break;
            }
        }
        else{   												           // New length type RFC4880 sec 4.2.2
            tag = ctb & 63;                                                // get tag value
            uint8_t first_octet = static_cast <unsigned char> (data[1]);
            if (first_octet < 192){                                        // 0 - 191; A one-octet Body Length header encodes packet lengths of up to 191 octets.
                remove += 1;
                length = first_octet;
            }
            else if (first_octet >= 192 && first_octet <= 223){          // 192 - 8383; A two-octet Body Length header encodes packet lengths of 192 to 8383 octets.
                remove += 2;
                length = static_cast<size_t>(toint(data.substr(1, 2), 256) - (192 << 8) + 192);
            }
            else if (first_octet > 223 && first_octet <= 244){ //Partial Body Length headers encode a packet of indeterminate length, effectively making it a stream.
                //partial = 1;  // set to partial start  not in use
                length = partialBodyLen(first_octet);
                remove += 1;
                
                partialPacket += data.substr(remove, length); // Get packet
                data = data.substr(remove + length, data.size() - remove - length);
                remove = 0;
                length = 0;
                
                //reading the full data here
                while (true) {
                    uint8_t first_octet_check = static_cast <unsigned char> (data[0]);
                    if (first_octet_check < 192) {
                        remove += 1;
                        length = first_octet_check;
                        break;
                    } else if (first_octet_check >= 192 && first_octet_check <= 223) {
                        remove += 2;
                        length = static_cast<size_t>(toint(data.substr(0, 2), 256) - (192 << 8) + 192);
                        break;
                    } else if (first_octet_check > 223 && first_octet_check <= 244) {
                        length = partialBodyLen(first_octet_check);
                        remove += 1;
                        partialPacket += data.substr(remove, length); // Get packet
                        data = data.substr(remove + length, data.size() - remove - length);
                        remove = 0;
                        length = 0;
                    } else if (first_octet == 255){
                        remove += 5;
                        length = static_cast<size_t>(toint(data.substr(1, 4), 256));
                        break;
                    }
                }
            } else if (first_octet == 255){ // 8384 - 4294967295; A five-octet Body Length header encodes packet lengths of up to 4,294,967,295 (0xFFFFFFFF) octets in length.
                remove += 5;
                length = static_cast<size_t>(toint(data.substr(2, 4), 256));
            }
        }
    }
    else{ // partial continue removed not in use
        throw std::runtime_error("Error: failed parse packet !");
    }
    std::string packet = partialPacket + data.substr(remove, length);						// Get packet
    data = data.substr(remove + length, data.size() - remove - length);		// Remove packet from key
    return packet;
}

Packet::Ptr read_packet_raw(const bool format, const uint8_t tag, uint8_t & partial, std::string & packet_data){
    Packet::Ptr out;
    if (partial > 1){
        out = std::make_shared<Partial>();
    }
    else{
        switch (tag){
            case 0:
                throw std::runtime_error("Error: Tag number MUST NOT be 0.");
                break;
            case 1:
                out = std::make_shared<Tag1>();
                break;
            case 2:
                out = std::make_shared<Tag2>();
                break;
            case 3:
                out = std::make_shared<Tag3>();
                break;
            case 4:
                out = std::make_shared<Tag4>();
                break;
            case 5:
                out = std::make_shared<Tag5>();
                break;
            case 6:
                out = std::make_shared<Tag6>();
                break;
            case 7:
                out = std::make_shared<Tag7>();
                break;
            case 8:
                out = std::make_shared<Tag8>();
                break;
            case 9:
                out = std::make_shared<Tag9>();
                break;
            case 10:
                out = std::make_shared<Tag10>();
                break;
            case 11:
                out = std::make_shared<Tag11>();
                break;
            case 12:
                out = std::make_shared<Tag12>();
                break;
            case 13:
                out = std::make_shared<Tag13>();
                break;
            case 14:
                out = std::make_shared<Tag14>();
                break;
            case 17:
                out = std::make_shared<Tag17>();
                break;
            case 18:
                out = std::make_shared<Tag18>();
                break;
            case 19:
                out = std::make_shared<Tag19>();
                break;
            case 60:
                out = std::make_shared<Tag60>();
                break;
            case 61:
                out = std::make_shared<Tag61>();
                break;
            case 62:
                out = std::make_shared<Tag62>();
                break;
            case 63:
                out = std::make_shared<Tag63>();
                break;
            default:
                throw std::runtime_error("Error: Tag not defined.");
                break;
        }
    }
    
    // fill in data
    out -> set_tag(tag);
    out -> set_format(format);
    out -> set_partial(partial);
    out -> set_size((unsigned int)packet_data.size());
    out -> read(packet_data);
    
    if (partial){
        partial = 2;
    }
    
    return out;
}

Packet::Ptr read_packet(std::string & data, uint8_t & partial){
    bool format;
    uint8_t tag = 0;
    std::string packet_data = read_packet_header(data, tag, format, partial);
    return read_packet_raw(format, tag, partial, packet_data);
}
