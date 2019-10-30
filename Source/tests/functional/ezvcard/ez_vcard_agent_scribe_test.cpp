//
//  ez_vcard_agent_scribe_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include <stdio.h>



//
///**
// * @author Michael Angstadt
// */
//public class AgentScribeTest {
//    private final AgentScribe scribe = new AgentScribe();
//    private final Sensei<Agent> sensei = new Sensei<Agent>(scribe);
//    
//    private final VCard vcard = new VCard();
//    private final String url = "http://mi5.co.uk/007";
//    private final Agent withUrl = new Agent(url);
//    private final Agent withVCard = new Agent(vcard);
//    private final Agent empty = new Agent();
//    
//    @Test
//    public void dataType() {
//        sensei.assertDataType(withUrl).versions(V2_1).run(VCardDataType.URL);
//        sensei.assertDataType(withUrl).versions(V3_0, V4_0).run(VCardDataType.URI);
//        
//        sensei.assertDataType(withVCard).run(null);
//        sensei.assertDataType(empty).run(null);
//    }
//    
//    @Test
//    public void writeText() {
//        sensei.assertWriteText(withUrl).run(url);
//        
//        for (VCardVersion version : values()) {
//            try {
//                scribe.writeText(withVCard, new WriteContext(version, null, false));
//                fail();
//            } catch (EmbeddedVCardException e) {
//                assertEquals(vcard, e.getVCard());
//            }
//        }
//        
//        sensei.assertWriteText(empty).skipMe();
//    }
//    
//    @Test
//    public void parseText_url() {
//        sensei.assertParseText(url).dataType(VCardDataType.URL).run(withUrl);
//        sensei.assertParseText(url).dataType(VCardDataType.URI).run(withUrl);
//    }
//    
//    @Test
//    public void parseText_vcard_2_1() {
//        try {
//            sensei.assertParseText("").versions(V2_1).run();
//            fail();
//        } catch (EmbeddedVCardException e) {
//            Agent property = (Agent) e.getProperty();
//            assertNull(property.getUrl());
//            assertNull(property.getVCard());
//            
//            e.injectVCard(vcard);
//            assertNull(property.getUrl());
//            assertEquals(vcard, property.getVCard());
//        }
//    }
//    
//    @Test
//    public void parseText_vcard_3_0() {
//        try {
//            sensei.assertParseText("BEGIN:VCARD\\nEND:VCARD").versions(V3_0).run();
//            fail();
//        } catch (EmbeddedVCardException e) {
//            Agent property = (Agent) e.getProperty();
//            assertNull(property.getUrl());
//            assertNull(property.getVCard());
//            
//            e.injectVCard(vcard);
//            assertNull(property.getUrl());
//            assertEquals(vcard, property.getVCard());
//        }
//    }
//    
//    @Test
//    public void parseHtml() {
//        sensei.assertParseHtml("<a href=\"" + url + "\"></a>").run(withUrl);
//        sensei.assertParseHtml("<div>" + url + "</div>").run(withUrl);
//        
//        try {
//            //@formatter:off
//            sensei.assertParseHtml(
//                                   "<div class=\"agent vcard\">" +
//                                   "<span class=\"fn\">Jane Doe</span>" +
//                                   "<div class=\"agent vcard\">" +
//                                   "<span class=\"fn\">Joseph Doe</span>" +
//                                   "</div>" +
//                                   "</div>").run();
//            //@formatter:on
//            
//            fail();
//        } catch (EmbeddedVCardException e) {
//            Agent property = (Agent) e.getProperty();
//            assertNull(property.getUrl());
//            assertNull(property.getVCard());
//            
//            e.injectVCard(vcard);
//            assertNull(property.getUrl());
//            assertEquals(vcard, property.getVCard());
//        }
//    }
//}
