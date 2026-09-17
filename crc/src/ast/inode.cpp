#include "ast/inode.hpp"

void ast::INode::printTab(std::size_t indent) {
    for (std::size_t i = 0; i < indent; ++i) {
        std::print("  ");
    }
}
