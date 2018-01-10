

#ifndef UID_ASSEMBLER_HPP
#define UID_ASSEMBLER_HPP





// DOC:
//
// uid_assembler<unsigned int> uida;
// uida.add(0);
// uida.add(1);
// uida.add(2); // add keys
// uida.set_field(0, 3); // 3 of type 0
// uida.set_field(1, 1); // 1 of type 1
// uids.set_field(2, 1); // 1 of type 2
// // uid should be: 


#include <iostream>
#include <map>
#include <vector>
#include <algorithm>



template <typename T>
class uid_assembler
{

    //int fields;
    typedef unsigned int count_type;
    std::map<T, count_type> fields;

    bool ready;
    
    // stack variable for recursion function
    std::vector<count_type> vector_counter;
    //const count_type total;
    count_type uid;

public:

    uid_assembler()
        : ready{false}
    {
    
    }
    
    void add(const T& key)
    {
        if(ready == false)
        {
            fields.insert(std::pair<T, count_type>(key, 0));
        }
        else
        {
            throw "exception";
        }
        
        //std::cout << "add called, size: " << fields.size() << std::endl;
    }
    
    void get_uid() const
    {
        if(ready == true)
        {
            
        }
        else
        {
            throw "exception";
        }
    }
    
    void finalize()
    {
        if(ready == false)
        {
            ready = true;
        }
        else
        {
            std::cerr << "Warning: finalize() called, ready flag already TRUE" << std::endl;
        }
    }
    
    //template <typename U>
    void clear_fields()
    {
        // clear the count of objects in the map
        typename std::map<T, count_type>::iterator it{fields.begin()};
        //auto it{fields.begin()};
        for(; it != fields.end(); ++ it)
        {
            it->second = 0;
        }
    }
    
    void set_field(const T& key, const count_type value)
    {
        fields.at(key) = value;
    }
    
    void increment_field(const T& key)
    {
        ++ fields.at(key);
    }
    
    count_type get(const T& key) const
    {
        return fields.at(key);
    }
    
    inline
    bool check_sequence(const std::map<T, count_type> fields_, const std::vector<count_type> vector_counter_) const
    {
        typename std::map<T, count_type>::const_iterator it1{fields_.cbegin()};
        std::vector<count_type>::const_iterator it2{vector_counter_.cbegin()};
        typename std::map<T, count_type>::const_iterator it1_end{fields_.cend()};
        std::vector<count_type>::const_iterator it2_end{vector_counter_.cend()};
        for(; /*(it1 != it1_end) || (it2 != it2_end)*/; ++ it1, ++ it2)
        {
            if(it1 == it1_end) break;
            if(it2 == it2_end) break;
        
            if(it1->second != *it2) return false;
        }
        return true;
    }
    
    // TODO: should be set_vector and take argument of U& value to set elements to
    template <typename U>
    inline
    void clear_vector(std::vector<U> &v) const
    {
        /*
        std::vector<U>::iterator it{v.begin()};
        for(; it != v.end(); ++ it)
        {
            (*it) = static_cast<U>(0);
        }
        */
        std::fill(v.begin(), v.end(), static_cast<U>(0));
    }
    
    void print_vector_counter(std::ostream &os) //, const std::vector<count_type>& vector_counter)
    {
        //std::cout << "print_vector_counter called, size: " << vector_counter.size() << std::endl;
        
        std::vector<count_type>::const_iterator it{vector_counter.cbegin()};
        for(; it != vector_counter.cend(); ++ it)
        {
            os << *it;
            if(it + 1 != vector_counter.cend())
            {
                os << " ";
            }
        }
    }
    
    void print_fields(std::ostream& os)
    {
        //std::cout << "print_fields called, size: " << fields.size() << std::endl;
        
        typename std::map<T, count_type>::const_iterator it{fields.cbegin()};
        for(; it != fields.cend(); ) //++ it)
        {
            os << it->first << ":" << it->second;
            if(++ it != fields.cend())
            {
                os << " ";
            }
        }
    }
    
    bool recurse(const count_type total) //std::vector<count_type>& vector_counter, const count_type total, count_type &uid)
    {
        //std::cout << "total=" << total << std::endl;
        std::cout << "uid=" << uid << " ";
        print_vector_counter(std::cout); //, vector_counter);
        std::cout << std::endl;
        //std::cin.get();
    
        if(check_sequence(fields, vector_counter))
        {
            //std::cout << "return TRUE" << std::endl;
            return true;
        }
        else
        {
            //std::cout << "else" << std::endl;
            // search for leftmost digit
            std::vector<count_type>::iterator it{vector_counter.end() - 1};
            for(; ; /*--it*/)
            {
                //std::cout << "index=" << std::distance(vector_counter.begin(), it) << " value=" << *it << std::endl;
                
                if(*it != 0)
                {
                    //std::cout << "found a non-zero entry at position" << std::distance(vector_counter.begin(), it) << std::endl;
                    //std::cout << "the value is: " << *it << std::endl;
                    // found a non-zero entry
                    
                    // if non-zero entry is in first position
                    // increment total and re-run algorithm
                    if(it == vector_counter.begin())
                    {
                        //std::cout << "clear, recurse" << std::endl;
                        // set all entries of vector_counter to zero
                        clear_vector(vector_counter);
                        // set final entry of vector counter to total + 1
                        vector_counter.back() = total + 1;
                        // changed contents so did not find correct sequence this function call
                        ++ uid;
                        
                        //return recurse(vector_counter, total + 1, uid);
                        return recurse(total + 1);
                    }
                    // else step to next sequence
                    else
                    {
                        //std::cout << "move sequence, recurse" << std::endl;
                    
                        //count_type temp{*it};
                        -- (*it);
                        count_type temp{*it};
                        
                        // also need to move temp to begining
                        std::fill(it, vector_counter.end(), static_cast<count_type>(0));
                        vector_counter.back() = temp;
                        
                        -- it;
                        ++ (*it); // it has moved!
                        
                        // changed contents so did not find correct sequence this function call
                        ++ uid;
                        //return recurse(vector_counter, total, uid);
                        return recurse(total);
                        //return false;
                    }
                }
                // else decrement it
                else
                {
                    //std::cout << "decrement it" << std::endl;
                    -- it; // don't need this in the else block?
                    if(it == vector_counter.begin())
                    {
                        //std::cout << "zero case, or shifted maximally, recurse" << std::endl;
                        // set all entries of vector_counter to zero
                        clear_vector(vector_counter);
                        // set final entry of vector counter to total + 1
                        vector_counter.back() = total + 1;
                        // changed contents so did not find correct sequence this function call
                        ++ uid;
                        
                        //return recurse(vector_counter, total + 1, uid);
                        return recurse(total + 1);
                    }
                }
            }
        }
    
    }
    
    count_type generate()
    {
        //std::cout << "generate" << std::endl;
    
        if(ready == false)
        {
            throw "exception";
        }
        
        //count_type uid{0};
        uid = 0;
        //std::vector<count_type> vector_counter;
        vector_counter.resize(fields.size());
        //std::fill(vector_counter.begin(); vector_counter.end(); 0);
        clear_vector(vector_counter);
        //recurse(vector_counter, 0, uid);
        recurse(0);
        
        //std::cout << "uid=" << uid << std::endl;
        
        return uid;
    }
    
    

};

#endif
