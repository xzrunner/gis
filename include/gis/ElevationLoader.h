#pragma once

#include <string>
#include <vector>

namespace gis
{

class ElevationLoader
{
public:
    static bool Load(const std::string& filepath,
        size_t& width, size_t& height, std::vector<int16_t>& vals);

private:
    static bool LoadFromHGT(const std::string& filepath,
        size_t& width, size_t& height, std::vector<int16_t>& vals);

}; // ElevationLoader

}