//
//  ez_vcard_agent_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/12/17.
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



#include <stdio.h>


///**
// * @author Michael Angstadt
// */
//public class AgentTest {
//    @Test
//    public void set_value() {
//        VCard vcard = new VCard();
//        Agent agent = new Agent();
//        
//        agent.setUrl("one");
//        assertEquals("one", agent.getUrl());
//        assertNull(agent.getVCard());
//        
//        agent.setVCard(vcard);
//        assertNull(agent.getUrl());
//        assertEquals(vcard, agent.getVCard());
//        
//        agent.setUrl("one");
//        assertEquals("one", agent.getUrl());
//        assertNull(agent.getVCard());
//    }
//    
//    @Test
//    public void constructors() {
//        VCard vcard = new VCard();
//        Agent agent = new Agent();
//        assertNull(agent.getUrl());
//        assertNull(agent.getVCard());
//        
//        agent = new Agent("one");
//        assertEquals("one", agent.getUrl());
//        assertNull(agent.getVCard());
//        
//        agent = new Agent(vcard);
//        assertNull(agent.getUrl());
//        assertEquals(vcard, agent.getVCard());
//    }
//    
//    @Test
//    public void validate() {
//        Agent property = new Agent();
//        assertValidate(property).versions(VCardVersion.V2_1, VCardVersion.V3_0).run(8);
//        assertValidate(property).versions(VCardVersion.V4_0).run(8, 2);
//        
//        VCard agentVCard = new VCard();
//        property.setVCard(agentVCard);
//        assertValidate(property).versions(VCardVersion.V2_1).run(10);
//        assertValidate(property).versions(VCardVersion.V3_0).run(10, 10);
//        assertValidate(property).versions(VCardVersion.V4_0).run(10, 2);
//        
//        property.setUrl("http://example.com");
//        assertValidate(property).versions(VCardVersion.V2_1, VCardVersion.V3_0).run();
//        assertValidate(property).versions(VCardVersion.V4_0).run(2);
//    }
//    
//    @Test
//    public void toStringValues() {
//        Agent property = new Agent();
//        assertFalse(property.toStringValues().isEmpty());
//    }
//    
//    @Test
//    public void copy() {
//        Agent original = new Agent();
//        assertCopy(original);
//        
//        original = new Agent("url");
//        assertCopy(original);
//        
//        original = new Agent(new VCard());
//        assertCopy(original).notSame("getVCard");
//    }
//    
//    @Test
//    public void equals() {
//        VCard vcard = new VCard();
//        VCard vcard2 = new VCard();
//        vcard2.setVersion(VCardVersion.V4_0);
//        
//        //@formatter:off
//        assertNothingIsEqual(
//                             new Agent(),
//                             new Agent("url"),
//                             new Agent("url2"),
//                             new Agent(vcard),
//                             new Agent(vcard2)
//                             );
//        
//        assertEqualsMethod(Agent.class)
//        .constructor().test()
//        .constructor("url")
//        .test()
//        .test(new Agent(new VCard()), new Agent(new VCard()));
//        //@formatter:on
//    }
//}
