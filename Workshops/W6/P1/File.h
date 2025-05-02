#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include "Resource.h"
#include <string>

namespace seneca {

    class File : public Resource {
        std::string m_contents;

    public:
        File(const std::string& name, const std::string& contents = "") : m_contents(contents) {
            m_name = name;
        }

        void update_parent_path(const std::string& path) override {
            m_parent_path = path;
        }

        NodeType type() const override {
            return NodeType::FILE;
        }

        std::string path() const override {
            return m_parent_path + m_name;
        }

        std::string name() const override {
            return m_name;
        }

        int count() const override {
            return -1; // For a file, count is not applicable
        }

        size_t size() const override {
            return m_contents.size();
        }
    };

}

#endif
