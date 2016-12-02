//
//  ez_vcard_agent_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
