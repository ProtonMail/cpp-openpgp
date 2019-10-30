//
//  list_multi_map.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/19/17.
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

#ifndef list_multi_map_hpp
#define list_multi_map_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <type_traits>
#include <ostream>

template <class K, class V>
class ListMultimap {
private:
    std::unordered_map<K, std::vector<V>> _map;
    
public:
    //
    //    /**
    //     * Creates an empty multimap.
    //     */
    //    public ListMultimap() {
    //        this(new LinkedHashMap<K, List<V>>());
    //    }
    //
    //    /**
    //     * Creates an empty multimap.
    //     * @param initialCapacity the initial capacity of the underlying map.
    //     */
    //    public ListMultimap(int initialCapacity) {
    //        this(new LinkedHashMap<K, List<V>>(initialCapacity));
    //    }
    //
    //    /**
    //     * Creates a copy of an existing multimap.
    //     * @param orig the multimap to copy from
    //     */
    //    public ListMultimap(ListMultimap<K, V> orig) {
    //        this(copy(orig.map));
    //    }
    //
    //    private static <K, V> Map<K, List<V>> copy(Map<K, List<V>> orig) {
    //        Map<K, List<V>> map = new LinkedHashMap<K, List<V>>(orig.size());
    //        for (Map.Entry<K, List<V>> entry : orig.entrySet()) {
    //            List<V> values = new ArrayList<V>(entry.getValue());
    //            map.put(entry.getKey(), values);
    //        }
    //        return map;
    //    }
    //
    //    /**
    //     * <p>
    //     * Creates a new multimap backed by the given map. Changes made to the given
    //     * map will effect the multimap and vice versa.
    //     * </p>
    //     * <p>
    //     * To avoid problems, it is highly recommended that the given map NOT be
    //     * modified by anything other than this {@link ListMultimap} class after
    //     * being passed into this constructor.
    //     * </p>
    //     * @param map the backing map
    //     */
    //    public ListMultimap(Map<K, List<V>> map) {
    //        this.map = map;
    //    }
    //
    /**
     * Adds a value to the multimap.
     * @param key the key
     * @param value the value to add
     */
    void put(K key, V value) {
        auto new_key = sanitizeKey(key);
        auto found = _map.find(new_key);
        if (found != _map.end()) {
            found->second.push_back(value);
        } else {
            auto new_list = std::vector<V>();
            new_list.push_back(value);
            _map.insert(_map.begin(), std::make_pair(new_key, new_list));
        }
    }
    
    /**
     * Adds multiple values to the multimap.
     * @param key the key
     * @param values the values to add
     */
    void putAll(K key, std::vector<V> values) {
        if (values.empty()) {
            return;
        }
        auto new_key = sanitizeKey(key);
        auto found = _map.find(new_key);
        if (found != _map.end()) {
            found->second.insert(found->second.end(), values.begin(), values.end());
        } else {
            _map.insert(_map.begin(),std::make_pair(key, values));
        }
    }
    
    /**
     * Gets the values associated with the key. Changes to the returned list
     * will update the underlying multimap, and vice versa.
     * @param key the key
     * @return the list of values or empty list if the key doesn't exist
     */
    std::vector<V> get(K key) {
        auto new_key = sanitizeKey(key);
        auto found = _map.find(new_key);
        if (found != _map.end()) {
            return found->second;
        }
        return std::vector<V>();
    }

    template<class C>
    std::vector<std::shared_ptr<C>> get(K key) {
        auto new_key = sanitizeKey(key);
        auto found = _map.find(new_key);
        std::vector<std::shared_ptr<C>> out;
        if (found != _map.end()) {
            for (auto f : found->second) {
                if (std::shared_ptr<C> o = std::dynamic_pointer_cast<C>(f)) {
                    out.push_back(o);
                }
            }
            return out;
        }
        return out;
    }
    
    /**
     * Gets the first value that's associated with a key.
     * @param key the key
     * @return the first value or null if the key doesn't exist
     */
    V first(K key) {
        auto new_key = sanitizeKey(key);
        auto found = _map.find(new_key);
        if (found != _map.end()) {
            return found->second.front();
        }
        if (typeid(int) == typeid(V)) {
            return 0;
        } else if (typeid(std::string) == typeid(V)) {
            return V();
        }
        return nullptr;
    }
    
    /**
     * Determines whether the given key exists.
     * @param key the key
     * @return true if the key exists, false if not
     */
    bool containsKey(K key) {
        auto new_key = sanitizeKey(key);
        auto found = _map.find(new_key);
        if (found != _map.end()) {
            return true;
        }
        return false;
    }
    
    /**
     * Removes a particular value.
     * @param key the key
     * @param value the value to remove
     * @return true if the multimap contained the value, false if not
     */
    bool remove(K key, V value) {
        auto new_key = sanitizeKey(key);
        auto found = _map.find(new_key);
        if (found != _map.end()) {
            auto f = std::find(found->second.begin(), found->second.end(), value);
            if (f != found->second.end()) {
                found->second.erase(f);
                if (found->second.size() <= 0) {
                    _map.erase(found);
                }
                return true;
            }
        }
        return false;
    }
    
    /**
     * Removes all the values associated with a key
     * @param key the key to remove
     * @return the removed values or an empty list if the key doesn't exist
     * (this list is immutable)
     */
    std::vector<V> removeAll(K key) {
        auto new_key = sanitizeKey(key);
        auto found = _map.find(new_key);
        if (found != _map.end()) {
            auto out_list = found->second;
            _map.erase(found);
            return out_list;
        }
        return std::vector<V>();
    }
    
    /**
     * Replaces all values with the given value.
     * @param key the key
     * @param value the value with which to replace all existing values, or null
     * to remove all values
     * @return the values that were replaced (this list is immutable)
     */
    std::vector<V> replace(K key, V value) {
        std::vector<V> replaced = removeAll(key);
        if (typeid(std::string) == typeid(V)) {
            if (value != V()) {
                put(key, value);
            }
        } else {
            put(key, value);
        }
        return replaced;
    }
    
    /**
     * Replaces all values with the given values.
     * @param key the key
     * @param values the values with which to replace all existing values
     * @return the values that were replaced (this list is immutable)
     */
    std::vector<V> replace(K key, std::vector<V> values) {
        std::vector<V> replaced = removeAll(key);
        putAll(key, values);
        return replaced;
    }
    
    /**
     * Clears all entries from the multimap.
     */
    void clear() {
        _map.clear();
    }
    
    /**
     * Gets all the keys in the multimap.
     * @return the keys (this set is immutable)
     */
    std::vector<K> keySet() {
        std::vector<K> v;
        for(auto it = _map.begin(); it != _map.end(); ++it) {
            v.insert(v.begin(), it->first);
        }
        return v;
    }
    
    /**
     * Gets all the values in the multimap.
     * @return the values (this list is immutable)
     */
    std::vector<V> values() {
        std::vector<V> list;
        for(auto it = _map.begin(); it != _map.end(); ++it) {
            list.insert(list.end(), it->second.begin(), it->second.end());
        }
        return list;
    }
    
    /**
     * Determines if the multimap is empty or not.
     * @return true if it's empty, false if not
     */
    bool isEmpty() {
        return _map.size() == 0;
    }
    
    /**
     * Gets the number of values in the map.
     * @return the number of values
     */
    int size() {
        int size = 0;
        for (auto it = _map.begin(); it != _map.end(); ++it) {
            auto list = it->second;
            size += list.size();
        }
        return size;
    }
    //
    //    /**
    //     * Gets an immutable view of the underlying {@link Map} object.
    //     * @return an immutable map
    //     */
    //    public Map<K, List<V>> asMap() {
    //        Map<K, List<V>> view = new LinkedHashMap<K, List<V>>(map.size());
    //        for (Map.Entry<K, List<V>> entry : map.entrySet()) {
    //            K key = entry.getKey();
    //            List<V> value = entry.getValue();
    //            view.put(key, Collections.unmodifiableList(value));
    //        }
    //        return Collections.unmodifiableMap(view);
    //    }
    
    /**
     * Gets the {@link Map} that backs this multimap. This method is here for
     * performances reasons. The returned map should NOT be modified by anything
     * other than the {@link ListMultimap} object that owns it.
     * @return the map
     */
    
    std::unordered_map<K, std::vector<V>> getMap() const {
        return _map;
    }
    
    /**
     * Modifies a given key before it is used to interact with the internal map.
     * This method is meant to be overridden by child classes if necessary.
     * @param key the key
     * @return the modified key (by default, the key is returned as-is)
     */
protected:
    K sanitizeKey(K key) {
        return key;
    }
    
    //    /**
    //     * Gets an iterator for iterating over the entries in the map. This iterator
    //     * iterates over an immutable view of the map.
    //     * @return the iterator
    //     */
    //    //@Override
    //    public Iterator<Map.Entry<K, List<V>>> iterator() {
    //        final Iterator<Map.Entry<K, List<V>>> it = map.entrySet().iterator();
    //        return new Iterator<Map.Entry<K, List<V>>>() {
    //            public boolean hasNext() {
    //                return it.hasNext();
    //            }
    //
    //            public Entry<K, List<V>> next() {
    //                final Entry<K, List<V>> next = it.next();
    //                return new Entry<K, List<V>>() {
    //                    public K getKey() {
    //                        return next.getKey();
    //                    }
    //
    //                    public List<V> getValue() {
    //                        return Collections.unmodifiableList(next.getValue());
    //                    }
    //
    //                    public List<V> setValue(List<V> value) {
    //                        throw new UnsupportedOperationException();
    //                    }
    //                };
    //            }
    //
    //            public void remove() {
    //                throw new UnsupportedOperationException();
    //            }
    //        };
    //    }
    //
    //    @Override
    //    public String toString() {
    //        return map.toString();
    //    }
    //
    //    @Override
    //    public int hashCode() {
    //        return map.hashCode();
    //    }
    //
    //    @Override
    //    public boolean equals(Object obj) {
    //        if (this == obj) return true;
    //        if (obj == null) return false;
    //        if (getClass() != obj.getClass()) return false;
    //
    //        ListMultimap<?, ?> other = (ListMultimap<?, ?>) obj;
    //        return map.equals(other.map);
    //    }
};





#endif /* list_multi_map_hpp */
