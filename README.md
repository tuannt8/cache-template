# Caching mesh
This class is made for being primarily used with a `3D mesh` (tetrahedral mesh), but it can be used with any type of software caching. The caching entities are pointers, so it can refer to any type of data.

# Why caching mesh
A 3D mesh consists of elements (`vertices`, `edges`, `faces` and `volumes`) and a `topology` that connect these elements. The types of topological relation are huge, so we could not store all of it. Generally we store only some compact sets of topological data, e.g. vertices on an edge, faces on a volume, etc. Other topological relation must be built on demand, and it is the bottle neck of a mesh framework.

Certianly we want an optimal data strucutre that stores all the frequently-referred topological data. However, one may not predict the reference statistic when he start a problem. A mesh framework, which can **adapt** its data structure to any problem would be more an ideal choice. Cache can help adapting the data structure by caching the topological data.

# Who should target caching for their mesh frame work
A mesh framework that is distributed for public.

# How to use mesh cache
