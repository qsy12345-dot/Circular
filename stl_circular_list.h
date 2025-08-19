#ifndef _STL_CIRCULAR_LIST_H_
#define _STL_CIRCULAR_LIST_H_ 1

#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <algorithm> 
#include <limits>
#if __cplusplus >= 201103L
#include <initializer_list>
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <forward_list>
#include <stack>
#include <deque>
#if __has_include(<circular_queue>)
#include <circular_queue>
#endif
#endif

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_CONTAINER
    template<typename _Tp>
      class circular_list
    {
        public:
            struct node
            {
                node* next;
                node* prev;
                _Tp value;
                
                template <typename... Args>
                  node(node* n = nullptr,node* p = nullptr,Args&&... args) : next(n),prev(p),value(std::forward<Args>(args)...) {}
            };
            
            class iterator
            {
	            public:
	                typedef std::bidirectional_iterator_tag iterator_category;
	                typedef _Tp value_type;
	                typedef ptrdiff_t difference_type;
	                typedef _Tp* pointer;
	                typedef _Tp& reference;
	                
	                iterator() : _node(nullptr),_head(nullptr) {}
	                iterator(node* n,node* h) : _node(n),_head(h) {}
	                reference operator*() const {return _node->value;}
	                pointer operator->() const {return &_node->value;}
	                
	                iterator& operator++()
					{
	                    _node = _node->next;
	                    if (_node == _head) _node = _head->next;
                   		return *this;
	                }
	                
	                iterator operator++(int)
					{
	                    iterator tmp = *this;
	                    ++(*this);
	                    return tmp;
	                }
	                
	                iterator& operator--()
					{
	                    _node = (_node->prev != _head) ? _node->prev : _head->prev;
	                    return *this;
	                }
	                
	                iterator operator--(int)
					{
	                    iterator tmp = *this;
	                    --(*this);
	                    return tmp;
	                }
	                
	                bool operator==(const iterator& other) const {return _node == other._node;}
	                bool operator!=(const iterator& other) const {return _node != other._node;}
	                node* get_node() const {return _node;}
	                
	            private:
	                node* _node;
	                node* _head;
	                friend class circular_list;
            };
            
            class const_iterator
            {
            public:
                typedef std::bidirectional_iterator_tag iterator_category;
                typedef const _Tp value_type;
                typedef ptrdiff_t difference_type;
                typedef const _Tp* pointer;
                typedef const _Tp& reference;
                
                const_iterator() : _node(nullptr),_head(nullptr) {}
                const_iterator(const node* n,const node* h) : _node(n),_head(h) {}
                const_iterator(const iterator& it) : _node(it.get_node()),_head(it.get_head()) {}
                
                reference operator*() const {return _node->value;}
                pointer operator->() const {return &_node->value;}
                
                const_iterator& operator++()
				{
                    _node = _node->next;
	                if (_node == _head) _node = _head->next;
                   	return *this;
                }
                
                const_iterator operator++(int)
				{
                    const_iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }
                
                const_iterator& operator--()
				{
                    _node = (_node->prev != _head) ? _node->prev : _head->prev;
                    return *this;
                }
                
                const_iterator operator--(int)
				{
                    const_iterator tmp = *this;
                    --(*this);
                    return tmp;
                }
                
                bool operator==(const const_iterator& other) const {return _node == other._node;}
                bool operator!=(const const_iterator& other) const {return _node != other._node;}
                const node* get_node() const {return _node;}
                
            private:
                const node* _node;
                const node* _head;
                friend class circular_list;
            };
            
            typedef size_t size_type;
            typedef _Tp value_type;
        
        private:
            node* head;
            size_type length;
        
        public:
            circular_list() : length(0)
            {
                head = new node(head,head);
                head->next = head;
                head->prev = head;
            }
        
            circular_list(const circular_list& other) : circular_list() {for (auto iter = other.begin();iter != other.end();++iter) push_back(*iter);}
        
#if __cplusplus >= 201103L
            circular_list(circular_list&& other) noexcept : head(other.head),length(other.length)
            {
                other.head = new node(other.head,other.head);
                other.head->next = other.head;
                other.head->prev = other.head;
                other.length = 0;
            }
            
            circular_list(std::initializer_list<value_type> init) : circular_list() {for (auto val : init) push_back(val);}
#endif
        
            ~circular_list()
            {
                clear();
                delete head;
            }
        
            circular_list& operator=(const circular_list& other)
            {
                if (this != &other)
                {
                    clear();
                    for (auto iter = other.begin();iter != other.end();++iter) push_back(*iter);
                }
                return *this;
            }
        
#if __cplusplus >= 201103L
            circular_list& operator=(circular_list&& other) noexcept
            {
                if (this != &other)
                {
                    clear();
                    delete head;
                    head = other.head;
                    length = other.length;
                    other.head = new node(other.head, other.head);
                    other.head->next = other.head;
                    other.head->prev = other.head;
                    other.length = 0;
                }
                return *this;
            }
        
            circular_list& operator=(std::initializer_list<value_type> init_list)
            {
                assign(init_list);
                return *this;
            }
#endif
        
            [[nodiscard]] bool empty() const {return head->next == head;}
            [[nodiscard]] size_type size() const {return length;}
        
            value_type& front()
            {
                if (empty()) throw std::out_of_range("List Is Empty!");
                return head->next->value;
            }
            
            const value_type& front() const
            {
                if (empty()) throw std::out_of_range("List Is Empty!");
                return head->next->value;
            }
            
            value_type& back()
            {
                if (empty()) throw std::out_of_range("List Is Empty!");
                return head->prev->value;
            }
            
            const value_type& back() const
            {
                if (empty()) throw std::out_of_range("List Is Empty!");
                return head->prev->value;
            }
        
            void clear()
            {
                node* curr = head->next;
                while (curr != head)
                {
                    node* temp = curr;
                    curr = curr->next;
                    delete temp;
                }
                head->next = head;
                head->prev = head;
                length = 0;
            }
            
            void insert(iterator pos,const value_type& val)
            {
                node* p = pos.get_node();
                if (!p || p == head) p = head;
                node* newNode = new node(p,p->prev,val);
                p->prev->next = newNode;
                p->prev = newNode;
                length++;
            }
            
#if __cplusplus >= 201103L
            void insert(iterator pos,value_type&& val)
            {
                node* p = pos.get_node();
                if (!p || p == head) p = head;
                node* newNode = new node(p, p->prev,std::move(val));
                p->prev->next = newNode;
                p->prev = newNode;
                length++;
            }
#endif
            void erase(iterator pos)
            {
                node* p = pos.get_node();
                if (!p || p == head) return;
                p->prev->next = p->next;
                p->next->prev = p->prev;
                delete p;
                length--;
            }
            
            void erase(iterator start,iterator end)
            {
                iterator curr = start;
                while (curr != end)
                {
                    iterator next = curr;
                    ++next;
                    erase(curr);
                    curr = next;
                }
            }
            
            void push_back(const value_type& val) {insert(end(),val);}
            void push_front(const value_type& val) {insert(begin(),val);}
#if __cplusplus >= 201103L
            void push_back(value_type&& val) {insert(end(),std::move(val));}
            void push_front(value_type&& val) {insert(begin(),std::move(val));}
#endif
            
            void pop_back()
            {
                if (empty()) throw std::out_of_range("List Is Empty!");
                erase(iterator(head->prev, head));
            }
            
            void pop_front()
            {
                if (empty()) throw std::out_of_range("List Is Empty!");
                erase(iterator(head->next, head));
            }
        
            iterator begin() noexcept {return iterator(head->next,head);}
            iterator end() noexcept {return iterator(head,head);}
            const_iterator begin() const noexcept {return const_iterator(head->next,head);}
            const_iterator end() const noexcept {return const_iterator(head, head);}
            const_iterator cbegin() const noexcept {return begin();}
            const_iterator cend() const noexcept {return end();}
            iterator start() noexcept {return begin();}
            iterator last() noexcept {return iterator(head->prev,head);}
        
            void assign(size_type count,const value_type& value)
            {
                clear();
                for (size_type i = 0; i < count; i++) push_back(value);
            }
        
            template <typename Iter>
              void assign(Iter first,Iter last)
            {
                clear();
                for (;first != last;++first) push_back(*first);
            }
            
            void assign(std::initializer_list<value_type> ilist)
            {
                clear();
                for (auto val : ilist) push_back(val);
            }

            void resize(size_type new_size)
            {
                if (new_size == length) return;
                if (new_size == 0) clear();
                else if (new_size < length)
                {
                    auto iter = begin();
                    for (size_type i = 0; i < new_size; i++) ++iter;
                    erase(iter, end());
                }
                else for (size_type i = length;i < new_size;i++) push_back(value_type{});
            }
            
#if __cplusplus >= 201103L
            std::vector<value_type> to_vector() const
            {
                std::vector<value_type> vec;
                for (auto iter = begin();iter != end();++iter) vec.push_back(*iter);
                return vec;
            }
            
            template <typename... Args>
              iterator emplace(iterator pos,Args&&... args)
            {
                node* p = pos.get_node();
                if (!p || p == head) p = head;
                node* newNode = new node(p,p->prev,std::forward<Args>(args)...);
                p->prev->next = newNode;
                p->prev = newNode;
                length++;
                return iterator(newNode,head);
            }
            
            template <typename... Args>
              void emplace_front(Args&&... args) {emplace(begin(), std::forward<Args>(args)...);}
            
            template <typename... Args>
              void emplace_back(Args&&... args) {emplace(end(), std::forward<Args>(args)...);}
#endif
            void sort() {sort([](const value_type& a,const value_type& b) {return a < b;});}
            
            template <typename Comp>
              void sort(Comp c)
            {
                if (length < 2) return;
                head->prev->next = nullptr;
                head->next->prev = nullptr;
                node* start = head->next;
                head->next = iterative_merge_sort(start,c);
                to_round();
            }
            
            void reverse()
            {
                if (length < 2) return;
                node* first = head->next;
                node* last = head->prev;
                first->prev = nullptr;
                last->next = nullptr;
                node* curr = first;
                node* prev = nullptr;
                node* next = nullptr;
                while (curr)
                {
                    next = curr->next;
                    curr->next = prev;
                    curr->prev = next;
                    prev = curr;
                    curr = next;
                }
                head->next = last;
                head->prev = first;
                last->prev = head;
                first->next = head;
            }
            
            template<typename Compare>
              void remove_if(Compare c)
            {
                iterator curr = begin();
                while (curr != end())
                {
                    iterator next_node = curr;
                    ++next_node;
                    if (c(*curr)) erase(curr);
                    curr = next_node;
                }
            }

            void remove(const value_type& remove_val) {remove_if([&](const value_type& a) {return a == remove_val;});}
            
            void splice(iterator iter,circular_list& other)
            {
                node* p = iter.get_node();
                if (!p) return;
                iterator curr = other.begin();
                while (curr != other.end())
                {
                    iterator next = curr;
                    ++next;
                    node* other_node = curr.get_node();
                    other_node->prev->next = other_node->next;
                    other_node->next->prev = other_node->prev;
                    other.length--;
                    other_node->prev = p->prev;
                    other_node->next = p;
                    p->prev->next = other_node;
                    p->prev = other_node;
                    length++;
                    curr = next;
                }
            }
            
            void merge(circular_list& other) {splice(end(),other);}
            
            iterator find(const value_type& val)
            {
                iterator curr = begin();
                while (curr != end())
                {
                    if (*curr == val) return curr;
                    ++curr;
                }
                return end();
            }
            
            iterator find(iterator start_iter,iterator end_iter,const value_type& val)
            {
                iterator curr = start_iter;
                while (curr != end_iter)
                {
                    if (*curr == val) return curr;
                    ++curr;
                }
                return end();
            }
            
            void swap(iterator a, iterator b) noexcept
            {
                node* na = a.get_node();
                node* nb = b.get_node();
                if (!na || !nb || na == head || nb == head || na == nb) return;
                std::swap(na->value, nb->value);
            }
            
            circular_list split(iterator start_iter,iterator end_iter) const
            {
                circular_list split_list;
                if (start_iter == end_iter) return split_list;
                iterator curr = start_iter;
                while (curr != end_iter && curr != end())
                {
                    split_list.push_back(*curr);
                    ++curr;
                }
                return split_list;
            }
            
            void unique()
            {
                if (length < 2) return;
                iterator curr = begin();
                ++curr;
                while (curr != end())
                {
                    iterator next = curr;
                    ++next;
                    iterator prev = curr;
                    --prev;
                    if (*curr == *prev) erase(curr);
                    curr = next;
                }
            }
            
            size_type max_size() const noexcept {return std::numeric_limits<size_type>::max() / sizeof(node);}
            
            value_type& operator[](int pos)
            {
                if (pos < 0 || static_cast<size_type>(pos) >= size()) throw std::out_of_range("Position out of range");
                iterator curr = begin();
                for (int i = 0;i < pos;i++) ++curr;
                return *curr;
            }
            
#if __cplusplus >= 201103L
            std::list<value_type> to_list() const
            {
                std::list<value_type> lst;
                for (auto iter = begin();iter != end();++iter) lst.push_back(*iter);
                return lst;
            }
            
            std::queue<value_type> to_queue() const
            {
                std::queue<value_type> que;
                for (auto iter = begin();iter != end();++iter) que.push(*iter);
                return que;
            }
            
            std::forward_list<value_type> to_forward_list() const
            {
                std::forward_list<value_type> fwd_lst;
                auto before_end = fwd_lst.before_begin();
                for (auto iter = begin();iter != end();++iter) before_end = fwd_lst.insert_after(before_end, *iter);
                return fwd_lst;
            }
            
            std::stack<value_type> to_stack() const
            {
                std::stack<value_type> stk;
                for (auto iter = begin();iter != end();++iter) stk.push(*iter);
                return stk;
            }

            std::deque<value_type> to_deque() const
            {
                std::deque<value_type> deq;
                for (auto iter = begin();iter != end();++iter) deq.push_back(*iter);
                return deq;
            }
#endif
        private:
            template <typename Compare>
              node* iterative_merge_sort(node* head_node,Compare c)
            {
                if (!head_node || !head_node->next) return head_node;
                size_t size = 0;
                node* temp = head_node;
                while (temp)
                {
                    size++;
                    temp = temp->next;
                }
                node dummy;
                node* tail = &dummy;
                dummy.next = nullptr;
                for (size_t block_size = 1;block_size < size;block_size <<= 1)
                {
                    tail = &dummy;
                    dummy.next = nullptr;
                    node* left = head_node;
                    node* right = head_node;
                    while (left)
                    {
                        right = advance_block(left,block_size);
                        node* next = advance_block(right,block_size);
                        tail = merge_sublists(left,right,tail,c);
                        left = next;
                    }
                    head_node = dummy.next;
                }
                return head_node;
            }
            
            node* advance_block(node* start,size_t steps)
            {
                node* prev = nullptr;
                for (size_t i = 0;i < steps && start;i++)
                {
                    prev = start;
                    start = start->next;
                }
                if (prev) prev->next = nullptr;
                return start;
            }
            
            template <typename Compare>
              node* merge_sublists(node* left,node* right,node* tail,Compare c)
            {
                while (left && right)
                {
                    if (c(left->value,right->value))
                    {
                        tail->next = left;
                        left->prev = tail;
                        tail = left;
                        left = left->next;
                    }
                    else
                    {
                        tail->next = right;
                        right->prev = tail;
                        tail = right;
                        right = right->next;
                    }
                }
                if (left)
                {
                    tail->next = left;
                    left->prev = tail;
                    while (tail->next) tail = tail->next;
                } 
                else if (right)
                {
                    tail->next = right;
                    right->prev = tail;
                    while (tail->next) tail = tail->next;
                }
                
                return tail;
            }
            
            void to_round()
            {
                if (!head->next) 
                {
                    head->next = head;
                    head->prev = head;
                    return;
                }
                node* curr = head->next;
                node* prev = head;
                while (curr && curr != head)
                {
                    curr->prev = prev;
                    prev = curr;
                    curr = curr->next;
                }
                head->next->prev = head;
                head->prev = prev;
                prev->next = head;
            }
    };
_GLIBCXX_END_NAMESPACE_CONTAINER
}
#endif
