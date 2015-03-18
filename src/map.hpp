#ifndef MAP_HPP
#define MAP_HPP

//typedef mm::planemap<double> Map;

#include <mm/heightmap.h>
#include <mm/colormap.h>

class Map
{
public:
    Map() {}
    virtual ~Map() {}
};

class HeightMap : public Map
{
public:
    HeightMap() {}

    mm::heightmap data;
};

class ColorMap : public Map
{
public:
    ColorMap() {}

    mm::colormap data;
};

#endif // MAP_HPP
