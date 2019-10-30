//
//  ez_vcard_listmultimap_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include <stdio.h>


#include "utils_test.h"

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/buffer.hpp>
#include "list_multi_map.hpp"


namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_listmultimap_test)
        {
            TEST(first) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("one", "11");
                map.put("one", "111");
                
                VERIFY_ARE_EQUAL("1", map.first("one"));
                VERIFY_IS_TRUE(map.first("two").empty());
            }
            
            TEST(get) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("two", "22");
                map.put("two", "2");
                
                auto getlist = map.get("one");
                auto check = std::vector<std::string>{"1"};
                VERIFY_ARE_EQUAL(getlist, check);
                
                getlist = map.get("two");
                check = std::vector<std::string>{"22", "2"};
                VERIFY_ARE_EQUAL(getlist, check);
                VERIFY_IS_TRUE(map.get("three").empty());
            }
            
            TEST(containsKey) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("two", "22");
                map.put("two", "2");
                
                VERIFY_IS_TRUE(map.containsKey("one"));
                VERIFY_IS_TRUE(map.containsKey("two"));
                VERIFY_IS_FALSE(map.containsKey("three"));
            }
            
            TEST(put) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("one", "111");
                map.put("one", "11");
                map.put("two", "2");
                auto getlist = map.get("one");
                auto check = std::vector<std::string>{"1", "111", "11"};
                VERIFY_ARE_EQUAL(getlist, check);
                getlist = map.get("two");
                check = std::vector<std::string>{"2"};
                VERIFY_ARE_EQUAL(getlist, check);
            }
            
            TEST(putAll) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.putAll("one", {"111", "11"});
                map.put("two", "2");
                
                auto getlist = map.get("one");
                auto check = std::vector<std::string>{"1", "111", "11"};
                VERIFY_ARE_EQUAL(getlist, check);
                getlist = map.get("two");
                check = std::vector<std::string>{"2"};
                VERIFY_ARE_EQUAL(getlist, check);
                map.putAll("one", {});
                getlist = map.get("one");
                check = std::vector<std::string>{"1", "111", "11"};
                VERIFY_ARE_EQUAL(getlist, check);
                getlist = map.get("two");
                check = std::vector<std::string>{"2"};
                VERIFY_ARE_EQUAL(getlist, check);
            }
            
            TEST(replace_string) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("one", "111");
                
                auto getlist = map.replace("one", "11");
                auto check = std::vector<std::string>{"1", "111"};
                VERIFY_ARE_EQUAL(getlist, check);
                
                getlist = map.get("one");
                check = std::vector<std::string>{"11"};
                VERIFY_ARE_EQUAL(getlist, check);
            }
            
            TEST(replace_collection) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("one", "111");
                
                auto getlist = map.replace("one", std::vector<std::string>{"11", "1111"});
                auto check = std::vector<std::string>{"1", "111"};
                VERIFY_ARE_EQUAL(getlist, check);

                getlist = map.get("one");
                check = std::vector<std::string>{"11", "1111"};
                VERIFY_ARE_EQUAL(getlist, check);
            }
            
            TEST(replace_null_value_string) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("one", "111");
                
                auto getlist = map.replace("one", "");
                auto check = std::vector<std::string>{"1", "111"};
                VERIFY_ARE_EQUAL(getlist, check);
                VERIFY_IS_TRUE(map.isEmpty());
            }
            
            TEST(remove) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("two", "22");
                map.put("two", "2");
                
                VERIFY_IS_FALSE(map.remove("three", "3"));
                VERIFY_IS_FALSE(map.remove("two", "222"));
                VERIFY_IS_TRUE(map.remove("two", "2"));
                
                auto getlist = map.get("two");
                auto check = std::vector<std::string>{"22"};
                VERIFY_ARE_EQUAL(check, getlist);
                
                getlist = map.get("one");
                check = std::vector<std::string>{"1"};
                VERIFY_ARE_EQUAL(getlist, check);
                
                getlist = map.keySet();
                check = std::vector<std::string>{"one", "two"};
                VERIFY_ARE_EQUAL(getlist, check);
                
                //make sure it remove an empty list from the map
                VERIFY_IS_TRUE(map.remove("one", "1"));
                
                getlist = map.keySet();
                check = std::vector<std::string>{"two"};
                VERIFY_ARE_EQUAL(getlist, check);
            }
            
            TEST(removeAll) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("two", "22");
                map.put("two", "2");
                
                VERIFY_ARE_EQUAL(3, map.size());
                VERIFY_IS_TRUE(map.removeAll("three").empty());
                VERIFY_ARE_EQUAL(3, map.size());
                
                auto two = map.get("two");
                auto check = std::vector<std::string>{"22", "2"};
                VERIFY_ARE_EQUAL(check, map.removeAll("two"));
                VERIFY_IS_TRUE(two.size() == 2);
                VERIFY_IS_TRUE(map.get("two").empty());
                VERIFY_ARE_EQUAL(1, map.size());
            }
            
            TEST(keySet) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("one", "111");
                map.put("one", "11");
                map.put("two", "2");
                map.put("three", "3");
                
                auto actual = map.keySet();
                auto check = std::vector<std::string> {"one", "two", "three"};
                VERIFY_ARE_EQUAL(actual, check);
            }

            TEST(values) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                map.put("one", "111");
                map.put("one", "11");
                map.put("two", "2");
                map.put("three", "3");
                
                auto actual = map.values();
                VERIFY_ARE_EQUAL(5, actual.size());
                auto it = std::find(actual.begin(), actual.end(), "1");
                VERIFY_IS_TRUE(it != actual.end());
                it = std::find(actual.begin(), actual.end(), "111");
                VERIFY_IS_TRUE(it != actual.end());
                
                it = std::find(actual.begin(), actual.end(), "11");
                VERIFY_IS_TRUE(it != actual.end());
                it = std::find(actual.begin(), actual.end(), "2");
                VERIFY_IS_TRUE(it != actual.end());
                it = std::find(actual.begin(), actual.end(), "3");
                VERIFY_IS_TRUE(it != actual.end());
                it = std::find(actual.begin(), actual.end(), "0911");
                VERIFY_IS_TRUE(it == actual.end());
            }
            
            TEST(isEmpty) {
                ListMultimap<std::string, std::string> map;
                VERIFY_IS_TRUE(map.isEmpty());
                map.put("one", "1");
                VERIFY_IS_FALSE(map.isEmpty());
                map.removeAll("one");
                VERIFY_IS_TRUE(map.isEmpty());
            }
            
            TEST(size) {
                ListMultimap<std::string, std::string> map;
                
                VERIFY_ARE_EQUAL(0, map.size());
                
                map.put("one", "1");
                map.put("one", "111");
                map.put("one", "11");
                map.put("two", "2");
                map.put("three", "3");
                
                VERIFY_ARE_EQUAL(5, map.size());
                
                map.removeAll("one");
                
                VERIFY_ARE_EQUAL(2, map.size());
            }
            
//             TEST(copy_constructor() {
//                ListMultimap<String, String> original = new ListMultimap<String, String>();
//                original.put("one", "1");
//                original.put("one", "111");
//                original.put("one", "11");
//                original.put("two", "2");
//                original.put("three", "3");
//                
//                //make sure the copy was successful
//                ListMultimap<String, String> copy = new ListMultimap<String, String>(original);
//                assertEquals(Arrays.asList("1", "111", "11"), copy.get("one"));
//                assertEquals(Arrays.asList("2"), copy.get("two"));
//                assertEquals(Arrays.asList("3"), copy.get("three"));
//                
//                //make sure the objects aren't linked
//                
//                original.removeAll("one");
//                assertEquals(Arrays.asList("1", "111", "11"), copy.get("one"));
//                
//                original.put("four", "4");
//                assertTrue(copy.get("four").isEmpty());
//                
//                original.put("two", "22");
//                assertEquals(Arrays.asList("2"), copy.get("two"));
//                
//                copy.removeAll("two");
//                assertEquals(Arrays.asList("2", "22"), original.get("two"));
//                
//                copy.put("five", "5");
//                assertTrue(original.get("five").isEmpty());
//                
//                copy.put("three", "33");
//                assertEquals(Arrays.asList("3"), original.get("three"));
//            }
            
             TEST(clear) {
                ListMultimap<std::string, std::string> map;
                map.put("one", "1");
                VERIFY_ARE_EQUAL(1, map.size());
                map.clear();
                VERIFY_ARE_EQUAL(0, map.size());
            }
            
//             TEST(sanitizeKey) {
//                ListMultimap<String, String> map = new ListMultimap<String, String>() {
//                    @Override
//                    protected String sanitizeKey(String key) {
//                        return key.toLowerCase();
//                    }
//                };
//                map.put("one", "1");
//                map.put("One", "111");
//                map.putAll("oNe", Arrays.asList("1111"));
//                
//                assertEquals("1", map.first("onE"));
//                
//                List<String> expected = Arrays.asList("1", "111", "1111");
//                assertEquals(expected, map.get("ONe"));
//                
//                assertTrue(map.remove("oNE", "1"));
//                assertEquals(Arrays.asList("111", "1111"), map.removeAll("OnE"));
//                assertTrue(map.isEmpty());
//            }
            
//             TEST(asMap) {
//                ListMultimap<std::string, std::string> map;
//                map.put("foo", "1");
//                map.put("foo", "2");
//                map.put("bar", "1");
//                
//                auto m = map.asMap();
//                VERIFY_ARE_EQUAL(2, m.size());
//                VERIFY_ARE_EQUAL(Arrays.asList("1", "2"), m.get("foo"));
//                VERIFY_ARE_EQUAL(Arrays.asList("1"), m.get("bar"));
//                
//                try {
//                    m.get("foo").add("3");
//                    fail();
//                } catch (UnsupportedOperationException e) {
//                    //expected
//                }
//                
//                try {
//                    m.put("foo", new ArrayList<String>());
//                    fail();
//                } catch (UnsupportedOperationException e) {
//                    //expected
//                }
//            }
            
//            TEST(iterator) {
//                ListMultimap<std::string, std::string> map;
//                map.put("foo", "1");
//                map.put("foo", "2");
//                map.put("bar", "1");
//                
//                Iterator<Map.Entry<String, List<String>>> it = map.iterator();
//                
//                Map.Entry<String, List<String>> entry = it.next();
//                assertEquals("foo", entry.getKey());
//                assertEquals(Arrays.asList("1", "2"), entry.getValue());
//                try {
//                    entry.getValue().add("3");
//                    fail();
//                } catch (UnsupportedOperationException e) {
//                    //expected
//                }
//                try {
//                    entry.setValue(new ArrayList<String>());
//                    fail();
//                } catch (UnsupportedOperationException e) {
//                    //expected
//                }
//                try {
//                    it.remove();
//                    fail();
//                } catch (UnsupportedOperationException e) {
//                    //expected
//                }
//                
//                entry = it.next();
//                assertEquals("bar", entry.getKey());
//                assertEquals(Arrays.asList("1"), entry.getValue());
//                try {
//                    entry.getValue().add("3");
//                    fail();
//                } catch (UnsupportedOperationException e) {
//                    //expected
//                }
//                try {
//                    entry.setValue(new ArrayList<String>());
//                    fail();
//                } catch (UnsupportedOperationException e) {
//                    //expected
//                }
//                try {
//                    it.remove();
//                    fail();
//                } catch (UnsupportedOperationException e) {
//                    //expected
//                }
//                
//                assertFalse(it.hasNext());
//            }
//
//             TEST(equals) {
//                ListMultimap<std::string, std::string> map;
//                assertEqualsMethodEssentials(map);
//                
//                ListMultimap<String, String> one = new ListMultimap<String, String>();
//                ListMultimap<String, String> two = new ListMultimap<String, String>();
//                two.put("foo", "1");
//                assertNotEqualsBothWays(one, two);
//                
//                one.put("foo", "1");
//                assertEqualsAndHash(one, two);
//                
//            }
            
//            @Test
//            public void WrappedList_addAll() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                
//                assertFalse(list.addAll(new ArrayList<String>()));
//                
//                assertTrue(list.addAll(Arrays.asList("1", "2")));
//                assertEquals(Arrays.asList("1", "2"), list);
//                assertEquals(Arrays.asList("1", "2"), map.get("foo"));
//                
//                assertTrue(list.addAll(Arrays.asList("3", "4")));
//                assertEquals(Arrays.asList("1", "2", "3", "4"), list);
//                assertEquals(Arrays.asList("1", "2", "3", "4"), map.get("foo"));
//            }
//            
//            @Test
//            public void WrappedList_addAll_index() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                
//                assertFalse(list.addAll(0, new ArrayList<String>()));
//                
//                assertTrue(list.addAll(0, Arrays.asList("1", "2")));
//                assertEquals(Arrays.asList("1", "2"), list);
//                assertEquals(Arrays.asList("1", "2"), map.get("foo"));
//                
//                assertTrue(list.addAll(0, Arrays.asList("3", "4")));
//                assertEquals(Arrays.asList("3", "4", "1", "2"), list);
//                assertEquals(Arrays.asList("3", "4", "1", "2"), map.get("foo"));
//            }
//            
//            @Test
//            public void WrappedList_get() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                
//                map.put("foo", "1");
//                assertEquals("1", list.get(0));
//            }
//            
//            @Test
//            public void WrappedList_set() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                
//                map.put("foo", "1");
//                assertEquals("1", list.set(0, "2"));
//                assertEquals(Arrays.asList("2"), list);
//                assertEquals(Arrays.asList("2"), map.get("foo"));
//            }
//            
//            @Test
//            public void WrappedList_add() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                
//                list.add("1");
//                assertEquals(Arrays.asList("1"), list);
//                assertEquals(Arrays.asList("1"), map.get("foo"));
//            }
//            
//            @Test
//            public void WrappedList_add_index() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                
//                list.add(0, "1");
//                assertEquals(Arrays.asList("1"), list);
//                assertEquals(Arrays.asList("1"), map.get("foo"));
//            }
//            
//            @Test
//            public void WrappedList_remove() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                
//                assertFalse(list.remove("2"));
//                assertTrue(list.remove("1"));
//                
//                assertEquals(Arrays.asList(), list);
//                assertEquals(Arrays.asList(), map.get("foo"));
//                assertCollectionContains(map.keySet());
//            }
//            
//            @Test
//            public void WrappedList_removeAll() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("foo", "2");
//                map.put("foo", "3");
//                
//                assertFalse(list.removeAll(Arrays.asList()));
//                assertEquals(Arrays.asList("1", "2", "3"), list);
//                assertCollectionContains(map.keySet(), "foo");
//                
//                assertFalse(list.removeAll(Arrays.asList("4")));
//                assertEquals(Arrays.asList("1", "2", "3"), list);
//                assertCollectionContains(map.keySet(), "foo");
//                
//                assertTrue(list.removeAll(Arrays.asList("1", "2")));
//                assertEquals(Arrays.asList("3"), list);
//                assertCollectionContains(map.keySet(), "foo");
//                
//                assertTrue(list.removeAll(Arrays.asList("3")));
//                assertEquals(Arrays.asList(), list);
//                assertCollectionContains(map.keySet());
//            }
//            
//            @Test
//            public void WrappedList_retainAll() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("foo", "2");
//                map.put("foo", "3");
//                
//                assertFalse(list.retainAll(Arrays.asList("1", "2", "3")));
//                assertEquals(Arrays.asList("1", "2", "3"), list);
//                assertCollectionContains(map.keySet(), "foo");
//                
//                assertTrue(list.retainAll(Arrays.asList("1", "4")));
//                assertEquals(Arrays.asList("1"), list);
//                assertCollectionContains(map.keySet(), "foo");
//                
//                assertTrue(list.retainAll(Arrays.asList()));
//                assertEquals(Arrays.asList(), list);
//                assertCollectionContains(map.keySet());
//            }
//            
//            @Test
//            public void WrappedList_clear() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("foo", "2");
//                map.put("foo", "3");
//                
//                list.clear();
//                assertTrue(list.isEmpty());
//                assertCollectionContains(map.keySet());
//                
//                list.clear();
//                assertTrue(list.isEmpty());
//                assertCollectionContains(map.keySet());
//            }
//            
//            @Test
//            public void WrappedList_indexOf() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("foo", "1");
//                
//                assertEquals(-1, list.indexOf("2"));
//                assertEquals(0, list.indexOf("1"));
//                assertEquals(0, map.get("foo").indexOf("1"));
//            }
//            
//            @Test
//            public void WrappedList_lastIndexOf() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("foo", "1");
//                
//                assertEquals(-1, list.lastIndexOf("2"));
//                assertEquals(1, list.lastIndexOf("1"));
//                assertEquals(1, map.get("foo").lastIndexOf("1"));
//            }
//            
//            @Test
//            public void WrappedList_subList() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                map.putAll("foo", Arrays.asList("1", "2", "3", "4"));
//                
//                List<String> list = map.get("foo");
//                List<String> subList = list.subList(0, 2);
//                
//                assertEquals("1", subList.remove(0));
//                assertEquals(Arrays.asList("2"), subList);
//                assertEquals(Arrays.asList("2", "3", "4"), list);
//                assertEquals(Arrays.asList("2", "3", "4"), map.get("foo"));
//                
//                subList.add(0, "5");
//                assertEquals(Arrays.asList("5", "2"), subList);
//                assertEquals(Arrays.asList("5", "2", "3", "4"), list);
//                assertEquals(Arrays.asList("5", "2", "3", "4"), map.get("foo"));
//                
//                subList.clear();
//                assertEquals(Arrays.asList(), subList);
//                assertEquals(Arrays.asList("3", "4"), list);
//                assertEquals(Arrays.asList("3", "4"), map.get("foo"));
//                
//                list = map.get("bar");
//                subList = list.subList(0, 0);
//                
//                subList.add("1");
//                assertEquals(Arrays.asList("1"), subList);
//                assertEquals(Arrays.asList("1"), list);
//                assertEquals(Arrays.asList("1"), map.get("bar"));
//            }
//            
//            @Test
//            public void WrappedList_subSubList() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                map.putAll("foo", Arrays.asList("1", "2", "3", "4"));
//                
//                List<String> list = map.get("foo");
//                List<String> subList = list.subList(0, 2);
//                List<String> subSubList = subList.subList(0, 1);
//                
//                assertEquals("1", subSubList.remove(0));
//                assertEquals(Arrays.asList(), subSubList);
//                assertEquals(Arrays.asList("2"), subList);
//                assertEquals(Arrays.asList("2", "3", "4"), list);
//                assertEquals(Arrays.asList("2", "3", "4"), map.get("foo"));
//                
//                subSubList.add(0, "5");
//                assertEquals(Arrays.asList("5"), subSubList);
//                assertEquals(Arrays.asList("5", "2"), subList);
//                assertEquals(Arrays.asList("5", "2", "3", "4"), list);
//                assertEquals(Arrays.asList("5", "2", "3", "4"), map.get("foo"));
//                
//                subSubList.clear();
//                assertEquals(Arrays.asList(), subSubList);
//                assertEquals(Arrays.asList("2"), subList);
//                assertEquals(Arrays.asList("2", "3", "4"), list);
//                assertEquals(Arrays.asList("2", "3", "4"), map.get("foo"));
//            }
//            
//            @Test
//            public void WrappedList_equals() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                
//                assertEqualsMethodEssentials(list);
//                assertTrue(list.equals(Arrays.asList("1")));
//                assertFalse(list.equals(Arrays.asList("2")));
//            }
//            
//            @Test
//            public void WrappedList_hashCode() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("bar", "1");
//                
//                assertEquals(list.hashCode(), map.get("bar").hashCode());
//            }
//            
//            @Test
//            public void WrappedList_contains() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                
//                assertFalse(list.contains("3"));
//                assertTrue(list.contains("1"));
//            }
//            
//            @Test
//            public void WrappedList_containsAll() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("foo", "2");
//                map.put("foo", "3");
//                
//                assertFalse(list.containsAll(Arrays.asList("4")));
//                assertTrue(list.containsAll(Arrays.asList("1")));
//            }
//            
//            @Test
//            public void WrappedList_listIterator() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("foo", "2");
//                map.put("foo", "3");
//                map.put("foo", "4");
//                
//                ListIterator<String> it = list.listIterator();
//                
//                assertFalse(it.hasPrevious());
//                assertTrue(it.hasNext());
//                assertEquals(-1, it.previousIndex());
//                assertEquals(0, it.nextIndex());
//                assertEquals("1", it.next());
//                assertEquals(Arrays.asList("1", "2", "3", "4"), list);
//                assertEquals(Arrays.asList("1", "2", "3", "4"), map.get("foo"));
//                
//                assertTrue(it.hasPrevious());
//                assertTrue(it.hasNext());
//                assertEquals(0, it.previousIndex());
//                assertEquals(1, it.nextIndex());
//                it.remove();
//                assertEquals(Arrays.asList("2", "3", "4"), list);
//                assertEquals(Arrays.asList("2", "3", "4"), map.get("foo"));
//                
//                assertFalse(it.hasPrevious());
//                assertTrue(it.hasNext());
//                assertEquals(-1, it.previousIndex());
//                assertEquals(0, it.nextIndex());
//                assertEquals("2", it.next());
//                assertEquals(Arrays.asList("2", "3", "4"), list);
//                assertEquals(Arrays.asList("2", "3", "4"), map.get("foo"));
//                
//                assertTrue(it.hasPrevious());
//                assertTrue(it.hasNext());
//                assertEquals(0, it.previousIndex());
//                assertEquals(1, it.nextIndex());
//                it.set("5");
//                assertEquals(Arrays.asList("5", "3", "4"), list);
//                assertEquals(Arrays.asList("5", "3", "4"), map.get("foo"));
//                
//                assertTrue(it.hasPrevious());
//                assertTrue(it.hasNext());
//                assertEquals(0, it.previousIndex());
//                assertEquals(1, it.nextIndex());
//                assertEquals("3", it.next());
//                assertEquals(Arrays.asList("5", "3", "4"), list);
//                assertEquals(Arrays.asList("5", "3", "4"), map.get("foo"));
//                
//                assertTrue(it.hasPrevious());
//                assertTrue(it.hasNext());
//                assertEquals(1, it.previousIndex());
//                assertEquals(2, it.nextIndex());
//                assertEquals("3", it.previous());
//                assertEquals(Arrays.asList("5", "3", "4"), list);
//                assertEquals(Arrays.asList("5", "3", "4"), map.get("foo"));
//                
//                assertTrue(it.hasPrevious());
//                assertTrue(it.hasNext());
//                assertEquals(0, it.previousIndex());
//                assertEquals(1, it.nextIndex());
//                assertEquals("3", it.next());
//                assertEquals(Arrays.asList("5", "3", "4"), list);
//                assertEquals(Arrays.asList("5", "3", "4"), map.get("foo"));
//                
//                assertTrue(it.hasPrevious());
//                assertTrue(it.hasNext());
//                assertEquals(1, it.previousIndex());
//                assertEquals(2, it.nextIndex());
//                assertEquals("4", it.next());
//                assertEquals(Arrays.asList("5", "3", "4"), list);
//                assertEquals(Arrays.asList("5", "3", "4"), map.get("foo"));
//                
//                assertTrue(it.hasPrevious());
//                assertFalse(it.hasNext());
//                assertEquals(2, it.previousIndex());
//                assertEquals(3, it.nextIndex());
//                it.add("6");
//                assertEquals(Arrays.asList("5", "3", "4", "6"), list);
//                assertEquals(Arrays.asList("5", "3", "4", "6"), map.get("foo"));
//                
//                assertTrue(it.hasPrevious());
//                assertFalse(it.hasNext());
//                assertEquals(3, it.previousIndex());
//                assertEquals(4, it.nextIndex());
//            }
//            
//            @Test
//            public void WrappedList_listIterator_empty_add() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                
//                ListIterator<String> it = list.listIterator();
//                
//                assertFalse(it.hasPrevious());
//                assertFalse(it.hasNext());
//                assertEquals(-1, it.previousIndex());
//                assertEquals(0, it.nextIndex());
//                it.add("1");
//                assertEquals(Arrays.asList("1"), list);
//                assertEquals(Arrays.asList("1"), map.get("foo"));
//                
//                assertTrue(it.hasPrevious());
//                assertFalse(it.hasNext());
//                assertEquals(0, it.previousIndex());
//                assertEquals(1, it.nextIndex());
//            }
//            
//            @Test
//            public void WrappedList_listIterator_index() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("foo", "2");
//                map.put("foo", "3");
//                map.put("foo", "4");
//                
//                ListIterator<String> it = list.listIterator(1);
//                
//                assertTrue(it.hasPrevious());
//                assertTrue(it.hasNext());
//                assertEquals(0, it.previousIndex());
//                assertEquals(1, it.nextIndex());
//                assertEquals("2", it.next());
//            }
//            
//            @Test
//            public void WrappedList_iterator() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> list = map.get("foo");
//                map.put("foo", "1");
//                map.put("foo", "2");
//                map.put("foo", "3");
//                map.put("foo", "4");
//                
//                Iterator<String> it = list.iterator();
//                
//                assertTrue(it.hasNext());
//                assertEquals("1", it.next());
//                assertTrue(it.hasNext());
//                assertEquals("2", it.next());
//                assertTrue(it.hasNext());
//                assertEquals("3", it.next());
//                assertTrue(it.hasNext());
//                assertEquals("4", it.next());
//                assertFalse(it.hasNext());
//            }
//            
//            @Test
//            public void WrappedList_two_instances() {
//                ListMultimap<String, String> map = new ListMultimap<String, String>();
//                List<String> one = map.get("foo");
//                List<String> two = map.get("foo");
//                
//                assertTrue(one.isEmpty());
//                assertTrue(two.isEmpty());
//                assertCollectionContains(map.keySet());
//                
//                one.add("1");
//                assertEquals(Arrays.asList("1"), one);
//                assertEquals(Arrays.asList("1"), two);
//                assertCollectionContains(map.keySet(), "foo");
//                
//                two.add("2");
//                assertEquals(Arrays.asList("1", "2"), one);
//                assertEquals(Arrays.asList("1", "2"), two);
//                assertCollectionContains(map.keySet(), "foo");
//                
//                one.addAll(Arrays.asList("3", "4"));
//                assertEquals(Arrays.asList("1", "2", "3", "4"), one);
//                assertEquals(Arrays.asList("1", "2", "3", "4"), two);
//                assertCollectionContains(map.keySet(), "foo");
//                
//                map.clear();
//                assertTrue(one.isEmpty());
//                assertTrue(two.isEmpty());
//                assertCollectionContains(map.keySet());
//                
//                map.put("foo", "1");
//                assertEquals(Arrays.asList("1"), one);
//                assertEquals(Arrays.asList("1"), two);
//                assertCollectionContains(map.keySet(), "foo");
//                
//                one.clear();
//                assertTrue(one.isEmpty());
//                assertTrue(two.isEmpty());
//                assertCollectionContains(map.keySet());
//            }
        }
    }
}


