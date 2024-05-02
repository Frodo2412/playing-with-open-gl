#include "block.h"

cube block::get_block() const
{
    return cube_;
}

aabb block::get_bounding_box() const
{
    const vector3 half_extents(size_ / 2, size_ / 2, size_ / 2);
    return {position_ - half_extents, position_ + half_extents};
};
