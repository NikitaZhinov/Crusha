#pragma once

#include <list>
#include <string>

namespace crc {
    class ParsingTree {
        struct Node {
            std::list<Node*> children;
            std::wstring funciton;

            Node() = default;
            Node(const std::wstring &func);
        };

        Node _root;

    public:
        ParsingTree() = default;
        ParsingTree(const std::wstring function);
    };
}  // namespace crc
