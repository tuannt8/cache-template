//
//  kernel.hpp
//  interface_tracking
//
//  Created by Tuan Nguyen Trung on 11/7/16.
//  Copyright © 2016 Tuan Nguyen Trung. All rights reserved.
//

#ifndef kernel_hpp
#define kernel_hpp

#include <stdio.h>
#include <vector>

template<typename type>
struct point2
{
    type data[2];
    point2(type d1, type d2)
    {
        data[0] = d1;
        data[1] = d2;
    }
    type operator[](int i){return data[i];}
};

typedef point2<double> point2d;
typedef point2<int> point2i;


class kernel
{
public:
    std::vector<point2d*> _points;
    std::vector<point2i*> _edges;
    
    kernel(){};
    ~kernel(){};
    
    void generate(int nb_node, int nb_edge){
        for (int i = 0; i < nb_node; i++)
        {
            _points.push_back(new point2d(((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX))));
        }
        
        for (int i = 0; i < nb_edge; i++)
        {
            int n1 = rand()%nb_node;
            int n2 = rand()%nb_node;
            
            while (n2 == n1)
            {
                n2 = rand()%nb_node;
            }
            
            _edges.push_back(new point2i(n1, n2));
        }
    };
};

#endif /* kernel_hpp */
