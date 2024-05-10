#include "block.h"

const float block::block_size = 1.0;

cube block::get_block() const
{
    return cube_;
}

aabb block::get_bounding_box() const
{
    const vector3 half_extents(block_size / 2, block_size / 2, block_size / 2);
    return {position_ - half_extents, position_ + half_extents};
};
