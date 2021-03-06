//
//  profile.cpp
//  DSC
//
//  Created by Tuan Nguyen Trung on 2/4/16.
//  Copyright © 2016 Asger Nyman Christiansen. All rights reserved.
//

#include "profile.h"
#include <iostream>
#include <map>

using namespace std;


std::map<std::string, profile_att> profile::m_objects;

profile::profile(std::string name)
{
    m_name = name;
    profile_att * cur_p = get_object(name);
    cur_p->count ++;
    cur_p->m_start = P_TIME_NOW;
}

profile::~profile()
{
        done();
}

void profile::done()
{
        // close
        profile_att * cur_p = get_object(m_name);
        p_duration_t t = P_TIME_NOW - cur_p->m_start;
        cur_p->total_time += t.count();
}

void profile::change(std::string name)
{
    done();
    
    {
        m_name = name;
        profile_att * cur_p = get_object(name);
        cur_p->count ++;
        cur_p->m_start = P_TIME_NOW;
    }
}

profile_att * profile::get_object(const std::string &  name )
{
    if (m_objects.find(name) == m_objects.end())
    {
        // Not found
        profile_att newO;
        m_objects.insert(std::make_pair(name, newO));
    }

    return &m_objects[name];
}

void profile::init()
{

}

profile::profile()
{
    
}



void profile::print()
{

    for (auto & p:m_objects)
    {
        printf("%s: %f in %d iters; avg: %f \n", p.first.c_str(), p.second.total_time, p.second.count,
               p.second.total_time / p.second.count);
    }
    
}
