//
//  RFC4880.h
//  UNNetPGP
//
//  Created by Yanfeng Zhang on 1/21/15.
//  Copyright (c) 2015 UP-NEXT. All rights reserved.
//

#ifndef UNNetPGP_RFC4880_h
#define UNNetPGP_RFC4880_h

/************************************/
/** Version.
 * OpenPGP has two different protocol versions: version 3 and version 4.
 *
 *  RFC4880 5.2
************************************/
typedef enum {
    RFC4880_V2 = 2,		/* Version 2 (essentially the same as v3) */
    RFC4880_V3 = 3,		/* Version 3 */
    RFC4880_V4 = 4		/* Version 4 */
} RFC4880_VERSION;


/************************************/
/* Packet Tags - RFC4880, 4.2 */
/************************************/
typedef enum {
    RFC4880_PTAG_RESERVED               = 0,    /* Reserved - a packet tag MUST NOT have this value */
    RFC4880_PTAG_PUBK_ENCED_SESSION_KEY = 1,	/* Public-Key Encrypted Session Key Packet */
    RFC4880_PTAG_SIGNATURE              = 2,    /* Signature Packet */
    RFC4880_PTAG_SYMK_ENCED_SESSION_KEY = 3,	/* Symmetric-Key Encrypted Session Key Packet */
    RFC4880_PTAG_ONE_PASS_SIG           = 4,	/* One-Pass Signature Packet */
    RFC4880_PTAG_SECRET_KEY = 5,	/* Secret Key Packet */
    RFC4880_PTAG_PUBLIC_KEY = 6,	/* Public Key Packet */
    RFC4880_PTAG_SECRET_SUBKEY = 7,	/* Secret Subkey Packet */
    RFC4880_PTAG_COMPRESSED = 8,	/* Compressed Data Packet */
    RFC4880_PTAG_SE_DATA = 9,/* Symmetrically Encrypted Data Packet */
    RFC4880_PTAG_MARKER = 10,/* Marker Packet */
    RFC4880_PTAG_LITDATA = 11,	/* Literal Data Packet */
    RFC4880_PTAG_TRUST = 12,	/* Trust Packet */
    RFC4880_PTAG_USER_ID = 13,	/* User ID Packet */
    RFC4880_PTAG_PUBLIC_SUBKEY = 14,	/* Public Subkey Packet */
    RFC4880_PTAG_RESERVED2 = 15,	/* reserved */
    RFC4880_PTAG_RESERVED3 = 16,	/* reserved */
    RFC4880_PTAG_USER_ATTR = 17,	/* User Attribute Packet */
    RFC4880_PTAG_SE_IP_DATA = 18,	/* Sym. Encrypted and Integrity
                                     * Protected Data Packet */
    OPS_PTAG_CT_MDC = 19,	/* Modification Detection Code Packet */
    
} RFC4880_PTAG;

/************************************/
/** Signature Type.
 * OpenPGP defines different signature types that allow giving
 * different meanings to signatures.  Signature types include 0x10 for
 * generitc User ID certifications (used when Ben signs Weasel's key),
 * Subkey binding signatures, document signatures, key revocations,
 * etc.
 *
 * Different types are used in different places, and most make only
 * sense in their intended location (for instance a subkey binding has
 * no place on a UserID).
 *
 * RFC4880 5.2.1
 */
/************************************/
typedef enum {
    RFC4880_SIG_BINARY = 0x00,	/* Signature of a binary document */
    RFC4880_SIG_TEXT = 0x01,	/* Signature of a canonical text document */
    RFC4880_SIG_STANDALONE = 0x02,	/* Standalone signature */
    
    RFC4880_CERT_GENERIC = 0x10,/* Generic certification of a User ID and
                             * Public Key packet */
    RFC4880_CERT_PERSONA = 0x11,/* Persona certification of a User ID and
                             * Public Key packet */
    RFC4880_CERT_CASUAL = 0x12,	/* Casual certification of a User ID and
                             * Public Key packet */
    RFC4880_CERT_POSITIVE = 0x13,	/* Positive certification of a
                                 * User ID and Public Key packet */
    
    RFC4880_SIG_SUBKEY = 0x18,	/* Subkey Binding Signature */
    RFC4880_SIG_PRIMARY = 0x19,	/* Primary Key Binding Signature */
    RFC4880_SIG_DIRECT = 0x1f,	/* Signature directly on a key */
    
    RFC4880_SIG_REV_KEY = 0x20,	/* Key revocation signature */
    RFC4880_SIG_REV_SUBKEY = 0x28,	/* Subkey revocation signature */
    RFC4880_SIG_REV_CERT = 0x30,/* Certification revocation signature */
    
    RFC4880_SIG_TIMESTAMP = 0x40,	/* Timestamp signature */
    
    RFC4880_SIG_3RD_PARTY = 0x50/* Third-Party Confirmation signature */
} RFC4880_SIG_TYPE;


/************************************/
/** Public Key Algorithm Numbers.
 * OpenPGP assigns a unique Algorithm Number to each algorithm that is part of OpenPGP.
 *
 * This lists algorithm numbers for public key algorithms.
 *
 * RFC4880 9.1
 *************************************/
typedef enum {
    RFC4880_PKA_NOTHING	= 0,	/* No PKA */
    RFC4880_PKA_RSA = 1,	/* RSA (Encrypt or Sign) */
    RFC4880_PKA_RSA_ENCRYPT_ONLY = 2,	/* RSA Encrypt-Only (deprecated -
                                         * \see RFC4880 13.5) */
    RFC4880_PKA_RSA_SIGN_ONLY = 3,	/* RSA Sign-Only (deprecated -
                                     * \see RFC4880 13.5) */
    RFC4880_PKA_ELGAMAL = 16,	/* Elgamal (Encrypt-Only) */
    RFC4880_PKA_DSA = 17,	/* DSA (Digital Signature Algorithm) */
    RFC4880_PKA_RESERVED_ELLIPTIC_CURVE = 18,	/* Reserved for Elliptic
                                                 * Curve */
    RFC4880_PKA_RESERVED_ECDSA = 19,	/* Reserved for ECDSA */
    RFC4880_PKA_ELGAMAL_ENCRYPT_OR_SIGN = 20,	/* Deprecated. */
    RFC4880_PKA_RESERVED_DH = 21,	/* Reserved for Diffie-Hellman
                                     * (X9.42, as defined for
                                     * IETF-S/MIME) */
    RFC4880_PKA_PRIVATE00 = 100,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE01 = 101,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE02 = 102,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE03 = 103,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE04 = 104,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE05 = 105,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE06 = 106,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE07 = 107,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE08 = 108,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE09 = 109,/* Private/Experimental Algorithm */
    RFC4880_PKA_PRIVATE10 = 110	/* Private/Experimental Algorithm */
} RFC4880_PKA_ALG_T;

/************************************/
/** Hashing Algorithm Numbers.
 * OpenPGP assigns a unique Algorithm Number to each algorithm that is
 * part of OpenPGP.
 *
 * This lists algorithm numbers for hash algorithms.
 *
 * RFC4880 9.4
 *************************************/
typedef enum {
    RFC4880_HASH_UNKNOWN = -1,	/* used to indicate errors */
    RFC4880_HASH_MD5 = 1,	/* MD5 */
    RFC4880_HASH_SHA1 = 2,	/* SHA-1 */
    RFC4880_HASH_RIPEMD = 3,	/* RIPEMD160 */
    
    RFC4880_HASH_SHA256 = 8,	/* SHA256 */
    RFC4880_HASH_SHA384 = 9,	/* SHA384 */
    RFC4880_HASH_SHA512 = 10,	/* SHA512 */
    RFC4880_HASH_SHA224 = 11	/* SHA224 */
} RFC4880_HASH_ALG;


//
//
///************************************/
///* Packet Tags - RFC4880, 4.2 */
///************************************/
//
///** Packet Tag - Bit 7 Mask (this bit is always set).
// * The first byte of a packet is the "Packet Tag".  It always
// * has bit 7 set.  This is the mask for it.
// *
// * \see RFC4880 4.2
// */
//#define OPS_PTAG_ALWAYS_SET		0x80
//
///** Packet Tag - New Format Flag.
// * Bit 6 of the Packet Tag is the packet format indicator.
// * If it is set, the new format is used, if cleared the
// * old format is used.
// *
// * \see RFC4880 4.2
// */
//#define OPS_PTAG_NEW_FORMAT		0x40
//
//
///** Old Packet Format: Mask for content tag.
// * In the old packet format bits 5 to 2 (including)
// * are the content tag.  This is the mask to apply
// * to the packet tag.  Note that you need to
// * shift by #OPS_PTAG_OF_CONTENT_TAG_SHIFT bits.
// *
// * \see RFC4880 4.2
// */
//#define OPS_PTAG_OF_CONTENT_TAG_MASK	0x3c
///** Old Packet Format: Offset for the content tag.
// * As described at #OPS_PTAG_OF_CONTENT_TAG_MASK the
// * content tag needs to be shifted after being masked
// * out from the Packet Tag.
// *
// * \see RFC4880 4.2
// */
//#define OPS_PTAG_OF_CONTENT_TAG_SHIFT	2
///** Old Packet Format: Mask for length type.
// * Bits 1 and 0 of the packet tag are the length type
// * in the old packet format.
// *
// * See #__ops_ptag_of_lt_t for the meaning of the values.
// *
// * \see RFC4880 4.2
// */
//#define OPS_PTAG_OF_LENGTH_TYPE_MASK	0x03
//
//
///** Old Packet Format Lengths.
// * Defines the meanings of the 2 bits for length type in the
// * old packet format.
// *
// * \see RFC4880 4.2.1
// */
//typedef enum {
//    OPS_PTAG_OLD_LEN_1 = 0x00,	/* Packet has a 1 byte length -
//                                 * header is 2 bytes long. */
//    OPS_PTAG_OLD_LEN_2 = 0x01,	/* Packet has a 2 byte length -
//                                 * header is 3 bytes long. */
//    OPS_PTAG_OLD_LEN_4 = 0x02,	/* Packet has a 4 byte
//                                 * length - header is 5 bytes
//                                 * long. */
//    OPS_PTAG_OLD_LEN_INDETERMINATE = 0x03	/* Packet has a
//                                             * indeterminate length. */
//} __ops_ptag_of_lt_t;
//
//
///** New Packet Format: Mask for content tag.
// * In the new packet format the 6 rightmost bits
// * are the content tag.  This is the mask to apply
// * to the packet tag.  Note that you need to
// * shift by #OPS_PTAG_NF_CONTENT_TAG_SHIFT bits.
// *
// * \see RFC4880 4.2
// */
//#define OPS_PTAG_NF_CONTENT_TAG_MASK	0x3f
///** New Packet Format: Offset for the content tag.
// * As described at #OPS_PTAG_NF_CONTENT_TAG_MASK the
// * content tag needs to be shifted after being masked
// * out from the Packet Tag.
// *
// * \see RFC4880 4.2
// */
//#define OPS_PTAG_NF_CONTENT_TAG_SHIFT	0
//
///* PTag Content Tags */
///***************************/
//
///** Package Tags (aka Content Tags) and signature subpacket types.
// * This enumerates all rfc-defined packet tag values and the
// * signature subpacket type values that we understand.
// *
// * \see RFC4880 4.3
// * \see RFC4880 5.2.3.1
// */

//
//enum {
//    OPS_REVOCATION_NO_REASON	= 0,
//    OPS_REVOCATION_SUPERSEDED	= 1,
//    OPS_REVOCATION_COMPROMISED	= 2,
//    OPS_REVOCATION_RETIRED		= 3,
//    OPS_REVOCATION_NO_LONGER_VALID	= 0x20
//};
//
///** Structure to hold one error code */
//typedef struct {
//    __ops_errcode_t   errcode;
//} __ops_parser_errcode_t;
//
///** Structure to hold one packet tag.
// * \see RFC4880 4.2
// */
//typedef struct {
//    unsigned        new_format;	/* Whether this packet tag is new
//                                 * (1) or old format (0) */
//    unsigned        type;	/* content_tag value - See
//                             * #__ops_content_enum for meanings */
//    __ops_ptag_of_lt_t length_type;	/* Length type (#__ops_ptag_of_lt_t)
//                                     * - only if this packet tag is old
//                                     * format.  Set to 0 if new format. */
//    unsigned        length;	/* The length of the packet.  This value
//                             * is set when we read and compute the length
//                             * information, not at the same moment we
//                             * create the packet tag structure. Only
//                             * defined if #readc is set. *//* XXX: Ben, is this correct? */
//    unsigned        position;	/* The position (within the
//                                 * current reader) of the packet */
//    unsigned	size;	/* number of bits */
//} __ops_ptag_t;
//

//
///** Structure to hold one DSA public key params.
// *
// * \see RFC4880 5.5.2
// */
//typedef struct {
//    BIGNUM         *p;	/* DSA prime p */
//    BIGNUM         *q;	/* DSA group order q */
//    BIGNUM         *g;	/* DSA group generator g */
//    BIGNUM         *y;	/* DSA public key value y (= g^x mod p
//                         * with x being the secret) */
//} __ops_dsa_pubkey_t;
//
///** Structure to hold an RSA public key.
// *
// * \see RFC4880 5.5.2
// */
//typedef struct {
//    BIGNUM         *n;	/* RSA public modulus n */
//    BIGNUM         *e;	/* RSA public encryption exponent e */
//} __ops_rsa_pubkey_t;
//
///** Structure to hold an ElGamal public key params.
// *
// * \see RFC4880 5.5.2
// */
//typedef struct {
//    BIGNUM         *p;	/* ElGamal prime p */
//    BIGNUM         *g;	/* ElGamal group generator g */
//    BIGNUM         *y;	/* ElGamal public key value y (= g^x mod p
//                         * with x being the secret) */
//} __ops_elgamal_pubkey_t;
//

//
///** Structure to hold a pgp public key */
//typedef struct {
//    __ops_version_t		version;/* version of the key (v3, v4...) */
//    time_t			birthtime;
//    time_t			duration;
//    /* validity period of the key in days since
//     * creation.  A value of 0 has a special meaning
//     * indicating this key does not expire.  Only used with
//     * v3 keys.  */
//    unsigned		days_valid;	/* v4 duration */
//    __ops_pubkey_alg_t	alg;	/* Public Key Algorithm type */
//    union {
//        __ops_dsa_pubkey_t dsa;	/* A DSA public key */
//        __ops_rsa_pubkey_t rsa;	/* An RSA public key */
//        __ops_elgamal_pubkey_t elgamal;	/* An ElGamal public key */
//    }			key;	/* Public Key Parameters */
//} __ops_pubkey_t;
//
///** Structure to hold data for one RSA secret key
// */
//typedef struct {
//    BIGNUM         *d;
//    BIGNUM         *p;
//    BIGNUM         *q;
//    BIGNUM         *u;
//} __ops_rsa_seckey_t;
//
///** __ops_dsa_seckey_t */
//typedef struct {
//    BIGNUM         *x;
//} __ops_dsa_seckey_t;
//
///** __ops_elgamal_seckey_t */
//typedef struct {
//    BIGNUM         *x;
//} __ops_elgamal_seckey_t;

/** s2k_usage_t
 */
typedef enum {
    RFC4880_S2KU_NONE = 0,
    RFC4880_S2KU_ENCRYPTED_AND_HASHED = 254,
    RFC4880_S2KU_ENCRYPTED = 255
} RFC4880_s2k_usage_t;

/** s2k_specifier_t
 */
typedef enum {
    RFC4880_S2KS_SIMPLE = 0,
    RFC4880_S2KS_SALTED = 1,
    RFC4880_S2KS_ITERATED_AND_SALTED = 3
} RFC4880_s2k_specifier_t;

/** Symmetric Key Algorithm Numbers.
 * OpenPGP assigns a unique Algorithm Number to each algorithm that is
 * part of OpenPGP.
 *
 * This lists algorithm numbers for symmetric key algorithms.
 *
 * \see RFC4880 9.2
 */
typedef enum {
    RFC4880_SA_PLAINTEXT = 0,	/* Plaintext or unencrypted data */
    RFC4880_SA_IDEA = 1,	/* IDEA */
    RFC4880_SA_TRIPLEDES = 2,	/* TripleDES */
    RFC4880_SA_CAST5 = 3,	/* CAST5 */
    RFC4880_SA_BLOWFISH = 4,	/* Blowfish */
    RFC4880_SA_AES_128 = 7,	/* AES with 128-bit key (AES) */
    RFC4880_SA_AES_192 = 8,	/* AES with 192-bit key */
    RFC4880_SA_AES_256 = 9,	/* AES with 256-bit key */
    RFC4880_SA_TWOFISH = 10,	/* Twofish with 256-bit key (TWOFISH) */
    RFC4880_SA_CAMELLIA_128 = 100,	/* Camellia with 128-bit key (CAMELLIA) */
    RFC4880_SA_CAMELLIA_192 = 101,	/* Camellia with 192-bit key */
    RFC4880_SA_CAMELLIA_256 = 102	/* Camellia with 256-bit key */
} RFC4880_symm_alg_t;
//
//#define OPS_SA_DEFAULT_CIPHER	OPS_SA_CAST5
//

//
//#define	OPS_DEFAULT_HASH_ALGORITHM	OPS_HASH_SHA256
//
//void   __ops_calc_mdc_hash(const uint8_t *,
//                           const size_t,
//                           const uint8_t *,
//                           const unsigned,
//                           uint8_t *);
//unsigned   __ops_is_hash_alg_supported(const __ops_hash_alg_t *);
//
///* Maximum block size for symmetric crypto */
//#define OPS_MAX_BLOCK_SIZE	16
//
///* Maximum key size for symmetric crypto */
//#define OPS_MAX_KEY_SIZE	32
//
///* Salt size for hashing */
//#define OPS_SALT_SIZE		8
//
///* Max hash size */
//#define OPS_MAX_HASH_SIZE	64
//
///** __ops_seckey_t
// */
//typedef struct __ops_seckey_t {
//    __ops_pubkey_t			pubkey;		/* public key */
//    __ops_s2k_usage_t		s2k_usage;
//    __ops_s2k_specifier_t		s2k_specifier;
//    __ops_symm_alg_t		alg;		/* symmetric alg */
//    __ops_hash_alg_t		hash_alg;	/* hash algorithm */
//    uint8_t				salt[OPS_SALT_SIZE];
//    unsigned			octetc;
//    uint8_t				iv[OPS_MAX_BLOCK_SIZE];
//    union {
//        __ops_rsa_seckey_t		rsa;
//        __ops_dsa_seckey_t		dsa;
//        __ops_elgamal_seckey_t		elgamal;
//    }				key;
//    unsigned			checksum;
//    uint8_t			       *checkhash;
//} __ops_seckey_t;
//

//

/************************************/
/* Packet Tags - RFC4880, 4.2 */
/************************************/
//typedef enum {
//    RFC4880_PTAG_RESERVED               = 0,    /* Reserved - a packet tag MUST NOT have this value */
//    RFC4880_PTAG_PUBK_ENCED_SESSION_KEY = 1,	/* Public-Key Encrypted Session Key Packet */
//    RFC4880_PTAG_SIGNATURE              = 2,    /* Signature Packet */
//    RFC4880_PTAG_SYMK_ENCED_SESSION_KEY = 3,	/* Symmetric-Key Encrypted Session Key Packet */
//    RFC4880_PTAG_ONE_PASS_SIG           = 4,	/* One-Pass Signature Packet */
//    OPS_PTAG_CT_SECRET_KEY = 5,	/* Secret Key Packet */
//    OPS_PTAG_CT_PUBLIC_KEY = 6,	/* Public Key Packet */
//    OPS_PTAG_CT_SECRET_SUBKEY = 7,	/* Secret Subkey Packet */
//    OPS_PTAG_CT_COMPRESSED = 8,	/* Compressed Data Packet */
//    OPS_PTAG_CT_SE_DATA = 9,/* Symmetrically Encrypted Data Packet */
//    OPS_PTAG_CT_MARKER = 10,/* Marker Packet */
//    OPS_PTAG_CT_LITDATA = 11,	/* Literal Data Packet */
//    OPS_PTAG_CT_TRUST = 12,	/* Trust Packet */
//    OPS_PTAG_CT_USER_ID = 13,	/* User ID Packet */
//    OPS_PTAG_CT_PUBLIC_SUBKEY = 14,	/* Public Subkey Packet */
//    OPS_PTAG_CT_RESERVED2 = 15,	/* reserved */
//    OPS_PTAG_CT_RESERVED3 = 16,	/* reserved */
//    OPS_PTAG_CT_USER_ATTR = 17,	/* User Attribute Packet */
//    OPS_PTAG_CT_SE_IP_DATA = 18,	/* Sym. Encrypted and Integrity
//                                     * Protected Data Packet */
//    OPS_PTAG_CT_MDC = 19,	/* Modification Detection Code Packet */
//    
//    OPS_PARSER_PTAG = 0x100,/* Internal Use: The packet is the "Packet
//                             * Tag" itself - used when callback sends
//                             * back the PTag. */
//    OPS_PTAG_RAW_SS = 0x101,/* Internal Use: content is raw sig subtag */
//    OPS_PTAG_SS_ALL = 0x102,/* Internal Use: select all subtags */
//    OPS_PARSER_PACKET_END = 0x103,
//    
//    /* signature subpackets (0x200-2ff) (type+0x200) */
//    /* only those we can parse are listed here */
//    OPS_PTAG_SIG_SUBPKT_BASE = 0x200,	/* Base for signature
//                                         * subpacket types - All
//                                         * signature type values
//                                         * are relative to this
//                                         * value. */
//    OPS_PTAG_SS_CREATION_TIME = 0x200 + 2,	/* signature creation time */
//    OPS_PTAG_SS_EXPIRATION_TIME = 0x200 + 3,	/* signature
//                                                 * expiration time */
//    
//    OPS_PTAG_SS_EXPORT_CERT = 0x200 + 4,	/* exportable certification */
//    OPS_PTAG_SS_TRUST = 0x200 + 5,	/* trust signature */
//    OPS_PTAG_SS_REGEXP = 0x200 + 6,	/* regular expression */
//    OPS_PTAG_SS_REVOCABLE = 0x200 + 7,	/* revocable */
//    OPS_PTAG_SS_KEY_EXPIRY = 0x200 + 9,	/* key expiration
//                                         * time */
//    OPS_PTAG_SS_RESERVED = 0x200 + 10,	/* reserved */
//    OPS_PTAG_SS_PREFERRED_SKA = 0x200 + 11,	/* preferred symmetric
//                                             * algs */
//    OPS_PTAG_SS_REVOCATION_KEY = 0x200 + 12,	/* revocation key */
//    OPS_PTAG_SS_ISSUER_KEY_ID = 0x200 + 16,	/* issuer key ID */
//    OPS_PTAG_SS_NOTATION_DATA = 0x200 + 20,	/* notation data */
//    OPS_PTAG_SS_PREFERRED_HASH = 0x200 + 21,	/* preferred hash
//                                                 * algs */
//    OPS_PTAG_SS_PREF_COMPRESS = 0x200 + 22,	/* preferred
//                                             * compression
//                                             * algorithms */
//    OPS_PTAG_SS_KEYSERV_PREFS = 0x200 + 23,	/* key server
//                                             * preferences */
//    OPS_PTAG_SS_PREF_KEYSERV = 0x200 + 24,	/* Preferred Key
//                                             * Server */
//    OPS_PTAG_SS_PRIMARY_USER_ID = 0x200 + 25,	/* primary User ID */
//    OPS_PTAG_SS_POLICY_URI = 0x200 + 26,	/* Policy URI */
//    OPS_PTAG_SS_KEY_FLAGS = 0x200 + 27,	/* key flags */
//    OPS_PTAG_SS_SIGNERS_USER_ID = 0x200 + 28,	/* Signer's User ID */
//    OPS_PTAG_SS_REVOCATION_REASON = 0x200 + 29,	/* reason for
//                                                 * revocation */
//    OPS_PTAG_SS_FEATURES = 0x200 + 30,	/* features */
//    OPS_PTAG_SS_SIGNATURE_TARGET = 0x200 + 31,	/* signature target */
//    OPS_PTAG_SS_EMBEDDED_SIGNATURE = 0x200 + 32,	/* embedded signature */
//    
//    OPS_PTAG_SS_USERDEFINED00 = 0x200 + 100,	/* internal or
//                                                 * user-defined */
//    OPS_PTAG_SS_USERDEFINED01 = 0x200 + 101,
//    OPS_PTAG_SS_USERDEFINED02 = 0x200 + 102,
//    OPS_PTAG_SS_USERDEFINED03 = 0x200 + 103,
//    OPS_PTAG_SS_USERDEFINED04 = 0x200 + 104,
//    OPS_PTAG_SS_USERDEFINED05 = 0x200 + 105,
//    OPS_PTAG_SS_USERDEFINED06 = 0x200 + 106,
//    OPS_PTAG_SS_USERDEFINED07 = 0x200 + 107,
//    OPS_PTAG_SS_USERDEFINED08 = 0x200 + 108,
//    OPS_PTAG_SS_USERDEFINED09 = 0x200 + 109,
//    OPS_PTAG_SS_USERDEFINED10 = 0x200 + 110,
//    
//    /* pseudo content types */
//    OPS_PTAG_CT_LITDATA_HEADER = 0x300,
//    OPS_PTAG_CT_LITDATA_BODY = 0x300 + 1,
//    OPS_PTAG_CT_SIGNATURE_HEADER = 0x300 + 2,
//    OPS_PTAG_CT_SIGNATURE_FOOTER = 0x300 + 3,
//    OPS_PTAG_CT_ARMOUR_HEADER = 0x300 + 4,
//    OPS_PTAG_CT_ARMOUR_TRAILER = 0x300 + 5,
//    OPS_PTAG_CT_SIGNED_CLEARTEXT_HEADER = 0x300 + 6,
//    OPS_PTAG_CT_SIGNED_CLEARTEXT_BODY = 0x300 + 7,
//    OPS_PTAG_CT_SIGNED_CLEARTEXT_TRAILER = 0x300 + 8,
//    OPS_PTAG_CT_UNARMOURED_TEXT = 0x300 + 9,
//    OPS_PTAG_CT_ENCRYPTED_SECRET_KEY = 0x300 + 10,	/* In this case the
//                                                     * algorithm specific
//                                                     * fields will not be
//                                                     * initialised */
//    OPS_PTAG_CT_SE_DATA_HEADER = 0x300 + 11,
//    OPS_PTAG_CT_SE_DATA_BODY = 0x300 + 12,
//    OPS_PTAG_CT_SE_IP_DATA_HEADER = 0x300 + 13,
//    OPS_PTAG_CT_SE_IP_DATA_BODY = 0x300 + 14,
//    OPS_PTAG_CT_ENCRYPTED_PK_SESSION_KEY = 0x300 + 15,
//    
//    /* commands to the callback */
//    OPS_GET_PASSPHRASE = 0x400,
//    OPS_GET_SECKEY = 0x400 + 1,
//    
//    /* Errors */
//    OPS_PARSER_ERROR = 0x500,	/* Internal Use: Parser Error */
//    OPS_PARSER_ERRCODE = 0x500 + 1	/* Internal Use: Parser Error
//                                     * with errcode returned */


/************************************/
/* RFC4880 **** Packet Headers
/************************************/



/************************************/
/* RFC4880 **** Packet Tags 4.3
/************************************/









#endif
