#include "Node.h"

bool Node::operator == (const Node& node) const
{
    return this->x == node.x && this->y == node.y;
}
