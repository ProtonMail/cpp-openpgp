//
//  openpgp_bad_pgp_test.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 11/16/16.
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


#ifndef openpgp_bad_pgp_test_hpp
#define openpgp_bad_pgp_test_hpp

#include <stdio.h>

namespace tests {
    namespace open_pgp_tests {
        auto private_key_dino_nov_16_2016 =
        "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
        "Version: OpenPGP.js v1.2.0" "\n"
        "Comment: http://openpgpjs.org" "\n"
        "" "\n"
        "xcMGBFgjHbwBCACz+VWDjLBrwDgZTKj6xXlsf9GWXWJr8gP49cPVwI4J5CRF" "\n"
        "eBFOrCgcnxRhkt2NG4LvvoGdkFrGO07CXfZB79s0BcoUXot+PV1tIPl8XpUm" "\n"
        "lShdWMr7IHyX3CZa32SJpw2bfnKGYoOvJK6DU4pDLpHi5EtSMBdDlCrgUwEu" "\n"
        "bWB/eKQVQZlLC8gWZaiTO9p9UvlCFtzRdZwwGg11cpg5Vuew579KnDD8IIyg" "\n"
        "L1TxeW9Yx/IaOA1cyaPtLFKyQxtgK105AB9AzmLHSx0w2+Ts4DgoTRMHZmuW" "\n"
        "dZSACNTn5+xlvitm8+7GoZevJjP9HPQICifmPDclctNZrZe2tLELB901ABEB" "\n"
        "AAH+CQMIP9/kpHBaOSNgJmAm4I9W0NbH/aGEmpbDR8vygRjkE9uTKWzWZh+a" "\n"
        "aydWSD4g7g/1asu0mCMtXwlGsKoA+3bpr3EwsXZVhz0ae1WsXFGrLhrRox/m" "\n"
        "/WW8eRjaTBAAJUFSbyLWfgBzdCH42+5NIlWZYUyuKcEzV46wBBGIIxHcdgTZ" "\n"
        "GW1sjbxuA7NbPO+GIzxGy+lWjzqo9gwRsflbUkYWIMpsJNJQGQj4FPi0b8kj" "\n"
        "HKnAxuFLs0EJcAB0cf/qU0Y3VIm09+yWoesdoOREhv4UQpHZGf8C8BR+phby" "\n"
        "hMK/2JdkRR9h101S3YABQGy0gwysQpKD8Kg11HET0HI/NyUE2hCSFNIKFQNX" "\n"
        "SDkGwf2AmF2M2WEOkav4pFf+61hPZJW0mbeSOz5FB4cQFglKnZ56sEtTCwaB" "\n"
        "4PR9qp67BlRT20TJdub4m6T9aqcI0C5z+p5znPKhb5jZBtqf+3RmxH9GJUu5" "\n"
        "2ZTXVKp+1vHNo6PwF2hWsjKgOwAuB0F9L0eokFgYc0fedZEl4q5bS+PhbBET" "\n"
        "fOC1n1pjncFzuwB2EedxXiRGKpY9fSkTZdB6pzv6sJCBOGA47XQ5fhRAu9F1" "\n"
        "UOyBxatqx0ACLabssN966GxeSW5hJZCYZkJ6Ck9rc/jAEKxr5yd+0wDEmuMq" "\n"
        "ltd5eTtcSXSBSwE6G6ikE7zh78M33ZPbIdsf0dCijqA1/LjJKlvq5boS7kKF" "\n"
        "1/SlJd0h7aqlqCkDjD/+CuNGboWdeoewTJcPbxlCOoAkvBPYPZuH5Ox2X/Mt" "\n"
        "Nt2u7aZLDTjvZoiLkl3rKUJAQRyYjI1aJmqEDNDQJqWYWAJDU+2fNb5PoSbK" "\n"
        "iy7/7ZgGManhy150xm79J9Tqb5G2swQ731STfiVPor76/W1quNonzVpx5kZI" "\n"
        "cXjM8DVabg7NGozw3unsxtRfUbBCC1r9zRk8anZudHN0NDBAcHJvdG9ubWFp" "\n"
        "bC5jb20+wsByBBABCAAmBQJYIx2/BgsJCAcDAgkQOAo3TRfHa/gEFQgCCgMW" "\n"
        "AgECGwMCHgEAAFTeCACd7CQoUakXZGJhkdsxCrZLokS6TchtzRGdRINuSE9y" "\n"
        "e7whI131AlWmQ+ABApETzNYBvTQToSkcfl/4WgYruC+wnq1zUOjwLerTAYFj" "\n"
        "k1xfhrjNwo5xX2C6VN4o9i9AsjP1UfI6ZTcMFQEcYdNFuOW6KyUrs7uEJffZ" "\n"
        "lWifjozho9FKCxPvxHRdgiD+eeGHRZWFUCtJAyU2UjX55OHlh5v9XExUA9O8" "\n"
        "H/mWs/ZqRZJpfRiBNk//F1k4RIVhxa7hC12cgSWs2Oeuj6e9611LuhttweZo" "\n"
        "tjpeD6Xn8L5Voc40IxkOtH2xJTwuxFaCNj2byi31h3vl3FA85QoelQG449EX" "\n"
        "x8MGBFgjHbwBCADD35XjUQDTFscUz0Fr/O32cP+CwLDOLiaQEK0v2sZLwwve" "\n"
        "NQpj/ATgDQeHjN6G7tE8omG4KpVUTmfkTQgLey8yd0u5AZw5lOHUEQBTArcF" "\n"
        "mcMLrQgrENDzQhVG0W2rpBP4h+qSuQqB3bVAPZxHTQSy/dTGLi+HYqFMe3uM" "\n"
        "xZKS0+cQ2u1v3Kj8AUKtnkMUvJWmHyIA9LLnExjj26zoyvqM4wl9cZA8fxqS" "\n"
        "C7ZLSbEw+TC53SFKYy1lQ/YhKBzXnEVmygU4tn3KBE5tQoKe3sA55Eu8WvK7" "\n"
        "GYdZChi/MwLBJZ76pHdlQ4skRBIt+R70B0wPjHLSmL8BSG7ESDACMrJZABEB" "\n"
        "AAH+CQMIpPgyv+ryyvVg4DnopWObDM7ZXPb1DzcUl4PfbD9xEshptM64M3j/" "\n"
        "O+HY5/Zm4pLUWoum7jIGgKYcgZ/Wc1KUPNr26PivYXqzP04gvzrXK26FT84X" "\n"
        "rwmLvk7DBje1KckqfIFiXFNZ0pAVOv4fKV9v8+WfuEz4wY3HRu+ljYi1JXZj" "\n"
        "mhP1ZIY0WTbsyVQbER8bRxiDwO2TYmf8P40EV/4TPH4djCUP2RRZxpTQVTna" "\n"
        "GrC0ZTdAz1Dn72jrxau4zvwPEErnWz5HwBRtMnJeGtzxUDH5jvkqWhzLMUmw" "\n"
        "UcjbW3WDDAueMOhf95pRnAVv440YniaEdGGP10oOf0ukwIt/KPjY18nbmiSs" "\n"
        "UTCOge5sG4cywNPRKgN+iuZRKKK6iVy4kOZY4Bgs3I8j6L21hmcdOkfWW73l" "\n"
        "pjO8tUdFlV8D5c/wI6tsOnyNpQMLOrjQU/LpzyDLX6QsaRceJOGoCreAVOgQ" "\n"
        "PnyfkR4hvAWa9olJa3TQV7h6PdhEzo9yNXyh7DVB8GL/lBt92eaVrqkdhEkB" "\n"
        "VqwMzzcruZIMl+l0YBiaxZaw3RFs09kHIjKGHg493zOHT/+/NAe8w4H7mmya" "\n"
        "InSTjGYULhbQ0kbe5jOjFEZ34bSXRebsRzipZP9Vno0yYWeJL5Spa8QE3AM3" "\n"
        "uqC/n68cNqQ13Tf7r5V8WrfVoqFDWc3UgmwVrddBsRDt+eN2nGQgAgqpnYGd" "\n"
        "ylbeR82tSbFatRJ94MzcDsmacQhS9quNu2bTDQVx+jimQVqn1fywQs4OluLv" "\n"
        "OkiTyOn2yRzfvCpmUOKS6wLJHak1GK2PENe+8eCloRmng9MRT1zgWH/8mUVz" "\n"
        "eCBKFtBKM2T5UI0qjLiS/RlvjBJlLjw/dy1Eu01RC1Q/biOQgVZo2zHaHJQg" "\n"
        "h1eIPfRl4yLWd28LSzo9trvdtUz+fNMOwsBfBBgBCAATBQJYIx3ACRA4CjdN" "\n"
        "F8dr+AIbDAAAap4IAKcNbT4iGmLJg9WQnTVcP+TedMmrNOK2KjdAf+I0tLK7" "\n"
        "NY8RxKs9wGBD1mbLKPKi1gkaavqJTVvEitgYB9cljveuTsvo3+O88hPCDmcP" "\n"
        "hI/Hm+ykeoq6wnky3F3YiB9XGPpNZvReSBdX72dSmZqq4e+qy3pdKVwxLgIL" "\n"
        "S51IL80+p3I0I7fJ8kKLYO2JVBrFb22mCY0pEJDI/3DxoID+yPVXouiKOXM4" "\n"
        "ShKoZXhv7Z6nWVkyTYjRAZhZIfPEHnp1AR803GXWRrkgyXc4Cw0H1R5rE2v9" "\n"
        "Ot9tWs34+eIDrgbzv2PcWOExF7uCCpdgFoXrS2uPg2c9NzNp7OliUvx2LFU=" "\n"
        "=e8an" "\n"
        "-----END PGP PRIVATE KEY BLOCK-----" "\n";
        //https://www.igolder.com/pgp/encryption/
        auto feng30_bad_message_from_outside =
        "-----BEGIN PGP MESSAGE-----" "\n"
        "Version: BCPG C# v1.6.1.0" "\n"
        "" "\n"
        "hQEMAwfS5Po9/xJxAQgAqS4rTx9Eb+FLYIwONqnjpGPgZa56cUZJJaks3+5JZN83" "\n"
        "zqwa+7yqyiPkj730p7xiTbF1iB0TD8m6J3BL6zHgAUKJ0mt/9UXBTia6Dt5Dyqhc" "\n"
        "lZIcTO17Kao7yU3pCDQbTZsqHvmHAJS7FBD4Ki11c5MPlqf7CE7yHLllT2NCDxn5" "\n"
        "tC2Pwpu1BLhCt5QxXfN6bt/QJB6yihNWEuD7iE15SUhig2q1CgktYmlFI7P/7zGw" "\n"
        "BWIb4LxJWtLyyqWbPK92XpKkISGXRrrRGdoW8yyYANYy6VCKQRIw1VkK3b52lrBH" "\n"
        "8rB7jr6ynE9WsCs1K6Gfp0bOT2l/6rj+WbkuOw1fwclD1y0ZWvd0stg5kJYfQgwj" "\n"
        "xAl7sDQTF4bnUu/mbc2s4XjPtNwsYNREYY67HAdHRozWfDE/GlDv3Rg5CkYZSStq" "\n"
        "LRsfCw==" "\n"
        "=akw+" "\n"
        "-----END PGP MESSAGE-----" "\n";
        //
        auto feng30_passphrase = "123";
        auto feng30_private_key =
        "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
        "Version: ProtonMail v0.1.0" "\n"
        "Comment: https://protonmail.com" "\n"
        "" "\n"
        "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" "\n"
        "=ePY/" "\n"
        "-----END PGP PRIVATE KEY BLOCK-----" "\n";
        
        
        
        
        auto from_user_test_one =
        "-----BEGIN PGP MESSAGE-----" "\n"
        "Version: Cryptix OpenPGP 0.20050418" "\n"
        "" "\n"
        "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" "\n"
        "EIfhGZc=" "\n"
        "=iRtJ" "\n"
        "-----END PGP MESSAGE-----";
        
        
        
    }
}


#endif /* openpgp_bad_pgp_test_hpp */
