// $Id: listmap.h,v 1.15 2019-02-21 17:28:55-08 - - $

#ifndef __LISTMAP_H__
#define __LISTMAP_H__
#include "xless.h"
#include "xpair.h"

template <typename Key, typename Value, class Less = xless<Key>>
class listmap {
public:
     using key_type = Key;
     using mapped_type = Value;
     using value_type = xpair<const key_type, mapped_type>;
private:
     Less less;
     struct node;
     struct link {
          node* next{};
          node* prev{};
          link(node* next_, node* prev_) : next(next_), prev(prev_) {}
     };
     struct node : link {
          value_type value{};
          node(node* next, node* prev, const value_type&);
     };
     node* anchor() { return static_cast<node*> (&anchor_); }
     link anchor_{ anchor(), anchor() };
public:
     class iterator;
     listmap() {};
     listmap(const listmap&);
     ~listmap();
     iterator insert(const value_type&);
     iterator find(const key_type&);
     iterator erase(iterator position);
     iterator begin() { return anchor()->next; }
     iterator end() { return anchor(); }
     bool empty() { return begin() == end(); }
};


template <typename Key, typename Value, class Less>
class listmap<Key, Value, Less>::iterator {
private:
     friend class listmap<Key, Value, Less>;
     listmap<Key, Value, Less>::node* where{ nullptr };
     iterator(node* where_) : where(where_) {};
public:
     iterator() {}
     value_type& operator*();
     value_type* operator->();
     //iterator& operator=(value_type *that);
     iterator& operator+(const int& that);
     iterator& operator++(); //++itor
     iterator& operator--(); //--itor
     void erase();
     bool operator== (const iterator&) const;
     bool operator!= (const iterator&) const;
};

#include "listmap.tcc"
#endif

