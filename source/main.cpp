//
//  main.cpp
//  cache
//
//  Created by Tuan Nguyen Trung on 11/7/16.
//  Copyright © 2016 Tuan Nguyen Trung. All rights reserved.
//

#include <iostream>
#include "kernel.hpp"
#include "cache.hpp"
#include "profile.h"

#include <string>

#define NEIGHBOR_EDGE_ID 0
#define GET_NEIGHBOR_CACHE(idx) cc->get_cache<std::vector<int>>(NEIGHBOR_EDGE_ID, idx, get_neighbor_edge)

#define MAX_ITER 10


using namespace std;

kernel mesh;

int * _compute(int idx)
{
    int * newv = new int;
    *newv = idx;
    return newv;
}

double * _compute_d(int idx)
{
    double * newv = new double;
    *newv = idx+0.3;
    return newv;
}

bool remove_edge(int idx)
{
    if (idx >= 0 && idx < mesh._edges.size()
        && mesh._edges[idx])
    {
        auto enodes = *mesh._edges[idx];
        // The two vertices is affected
        
        cache::get_instance()->mark_dirty(NEIGHBOR_EDGE_ID, enodes[0]);
        cache::get_instance()->mark_dirty(NEIGHBOR_EDGE_ID, enodes[1]);
        
        delete mesh._edges[idx];
        mesh._edges[idx] = nullptr;
        return true;
    }
    return false;
}

std::vector<int> * get_neighbor_edge(int idx)
{
    std::vector<int> * neighbor = new std::vector<int>();
    
    for (int i = 0; i < mesh._edges.size(); i++)
    {
        if (mesh._edges[i])
        {
            auto edge = *mesh._edges[i];
            if (edge[0] == idx || edge[1] == idx)
            {
                neighbor->push_back(i);
            }
        }
    }
    
    return neighbor;
}

int main(int argc, const char * argv[]) {

    mesh.generate(100, 200);
    
    
    for (int it = 0; it < MAX_ITER; it++)
    {
        for (int i = 0; i < mesh._points.size(); i++)
        {
            if (mesh._points[i])
            {
                profile t("get neighbor without cache-mesh");
                
                auto neighbor_edge = get_neighbor_edge(i);
                delete neighbor_edge;
            }
        }
    }
    
    auto cc = cache::get_instance();
    
    // Upgrade the get_data to cached version
    cc->add_cache_type<std::vector<int>>(NEIGHBOR_EDGE_ID, get_neighbor_edge);
    
    for (int it = 0; it < MAX_ITER; it++)
    {
        for (int i = 0; i < mesh._points.size(); i++)
        {
            if (mesh._points[i])
            {
                profile t("get neighbor with cache-mesh");
                auto neighbor_edge = GET_NEIGHBOR_CACHE(i);
            }
        }
    }
    
    // Randomly delete edge
    for (int i = 0; i < 50; i++)
    {
        remove_edge(rand() % mesh._edges.size());
    }
    
    // Loop again
    for (int it = 0; it < MAX_ITER; it++)
    {
        for (int i = 0; i < mesh._points.size(); i++)
        {
            if (mesh._points[i])
            {
                profile t("get neighbor with cache-mesh the second time");
                auto neighbor_edge = GET_NEIGHBOR_CACHE(i);
            }
        }
    }
    
    
    profile::print();
    
    return 0;
}
