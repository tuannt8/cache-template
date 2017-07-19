//
//  cache.hpp
//  interface_tracking
//
//  Created by Tuan Nguyen Trung on 11/7/16.
//  Copyright © 2016 Tuan Nguyen Trung. All rights reserved.
//

#ifndef cache_hpp
#define cache_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <queue>

#define CACHE_ARRAY_SIZE 1000 // Can be dynamically allocated based on the mesh size

class cache_item_base
{
public:
    cache_item_base(){};
    ~cache_item_base(){};
    
    virtual void release(){};
    virtual void * get(int idx){return nullptr;};
    virtual void set(void * newdata, int idx){};
    virtual void mark_dirty(int idx){};
};

template<typename type>
class cache_item : public cache_item_base
{
    std::vector<type *> _data;
    
public:
    cache_item(){
        _data = std::vector<type *>(CACHE_ARRAY_SIZE, nullptr);
    }
    
    ~cache_item(){
        
    }
    
    virtual void release(){
        for(auto & d : _data){
            if(d){
                delete d;
                d = nullptr;
            }
        }
    };
    
    virtual void * get(int idx){
        return _data[idx];
    }
    
    virtual void set(void * newdata, int idx){
        if(_data[idx])
        {
            delete _data[idx];
            _data[idx] = nullptr;
        }
        _data[idx] = (type*)newdata;
    };
    
    virtual void mark_dirty(int idx){
        if(_data[idx]){
            delete _data[idx];
            _data[idx] = nullptr;
        }
    }
};

class cache
{
public:
    
    static cache * get_instance(){
        static cache instance;
        return &instance;
    }

    template<typename type>
    bool add_cache_type(int id, std::function<type*(int)>compute){
        cache_item<type> * new_array = new cache_item<type>;
        _data.insert(std::make_pair(id, (cache_item_base*)new_array));
        return true;
    }

    template<typename type>
    type* get_cache(int cache_id, int item_id, std::function<type*(int)>compute)
    {
        if(!(_data[cache_id])->get(item_id))
        {
            _data[cache_id]->set((void*)compute(item_id), item_id);
        }
        
        return (type*)(_data[cache_id])->get(item_id);
    }
    
    void mark_dirty(int cache_id, int item_id)
    {
        _data[cache_id]->mark_dirty(item_id);
    }
    
private:
    std::map<int, cache_item_base*> _data;
    
    cache(){}
    ~cache(){
        for(auto it = _data.begin(); it != _data.end(); it++)
        {
            it->second->release();
            delete it->second;
        }
        _data.clear();
    }
};


#endif /* cache_hpp */
