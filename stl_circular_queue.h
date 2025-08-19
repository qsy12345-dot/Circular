#if __has_include(<circular_list>)
#ifndef _STL_CIRCULAR_QUEUE_H_
#define _STL_CIRCULAR_QUEUE_H_ 1

#include <circular_list>

namespace std
{
	template <typename _Tp>
	  class circular_queue
	{
		private:
		    std::circular_list<_Tp> lst;
		    size_t capacity;
		    size_t current_size;
		
		public:
			typedef size_t size_type;
			typedef _Tp* pointer;
			typedef _Tp& reference;
			typedef _Tp value_type;
			
		    explicit circular_queue(size_type cap) : capacity(cap),current_size(0) {if (cap == 0) throw std::invalid_argument("Capacity must be at least 1");}
		
		    bool enqueue(const value_type& value)
			{
		        if (is_full()) return false;
		        lst.push_back(value);
		        current_size++;
		        return true;
		    }
		
		    bool dequeue()
			{
		        if (isEmpty()) return false;
		        lst.pop_front();
		        current_size--;
		        return true;
		    }
		
		    value_type front() const
			{
		        if (isEmpty()) throw std::runtime_error("Queue is empty");
		        return lst.front();
		    }
		    
		    value_type rear() const
			{
		        if (isEmpty()) throw std::runtime_error("Queue is empty");
		        return lst.back();
		    }
		
		    bool isEmpty() const {return current_size == 0;}
		    bool is_full() const {return current_size == capacity;}
		    size_type size() const {return current_size;}
		    size_type getcapacity() const {return capacity;}
		    
		    void setcapacity(const size_type& size) const
			{
				if (size == 0) throw std::runtime_error("Cannot set size to 0");
				current_size = size;
				lst.resize(size);
			}
			
			std::circular_list<value_type> to_circular_list() const {return lst;}
			void sort() {lst.sort();};
	};
}
#endif
#endif
