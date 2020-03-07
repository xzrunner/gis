#include "gis/ElevationLoader.h"

#include <boost/filesystem.hpp>

#define SWAP_2(x) ( (((x) & 0xff) << 8) | ((unsigned short)(x) >> 8) )

namespace gis
{

bool ElevationLoader::Load(const std::string& filepath,
                           size_t& width, size_t& height,
                           std::vector<int16_t>& vals)
{
    auto ext = boost::filesystem::extension(filepath);
    std::transform(ext.begin(), ext.end(), ext.begin(), tolower);
    if (ext == ".hgt") {
        return LoadFromHGT(filepath, width, height, vals);
    } else {
        return false;
    }
}

bool ElevationLoader::LoadFromHGT(const std::string& filepath,
                                  size_t& width, size_t& height,
                                  std::vector<int16_t>& vals)
{
    std::ifstream fin(filepath, std::ios::in | std::ios::binary);
    if (fin.fail()) {
        return false;
    }

    size_t file_size = static_cast<size_t>(fin.tellg());
    fin.seekg(0, std::ios::beg);

    if (file_size > 3000000) {
        width  = 3601;
        height = 3601;
    } else {
        width  = 1201;
        height = 1201;
    }

    vals.resize(width * height);

    std::vector<int16_t> buffer(width);
    for (size_t y = 0; y < height; ++y) {
        fin.read(reinterpret_cast<char*>(buffer.data()), sizeof(int16_t) * width);
        for (size_t x = 0; x < width; ++x) {
            vals[(height - 1 - y) * width + x] = SWAP_2(buffer[x]);
        }
    }

    fin.close();

    return true;
}

}