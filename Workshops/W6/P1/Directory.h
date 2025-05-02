#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include "Resource.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace seneca {

    class Directory : public Resource {
        std::vector<Resource*> m_contents;

    public:
        Directory(const std::string& name) {
            m_name = name;
            if (!name.empty() && name.back() != '/')
                m_name += '/';
        }

        void update_parent_path(const std::string& path) override {
            m_parent_path = path;
            for (auto& resource : m_contents) {
                resource->update_parent_path(path + m_name);
            }
        }

        NodeType type() const override {
            return NodeType::DIR;
        }

        std::string path() const override {
            return m_parent_path + m_name;
        }

        std::string name() const override {
            return m_name;
        }

        int count() const override {
            return static_cast<int>(m_contents.size());
        }

        size_t size() const override {
            size_t totalSize = 0;
            for (auto& resource : m_contents) {
                totalSize += resource->size();
            }
            return totalSize;
        }

        Directory& operator+=(Resource* resource) {
            auto it = std::find_if(m_contents.begin(), m_contents.end(), [&](Resource* res) {
                return res->name() == resource->name();
                });
            if (it != m_contents.end()) {
                throw std::runtime_error("Resource with the same name already exists in the directory.");
            }
            m_contents.push_back(resource);
            resource->update_parent_path(m_parent_path + m_name);
            return *this;
        }

        Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {}) {
            auto it = std::find_if(m_contents.begin(), m_contents.end(), [&](Resource* res) {
                return res->name() == name;
                });

            if (it != m_contents.end()) {
                return *it;
            }

            if (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end()) {
                for (auto& resource : m_contents) {
                    if (resource->type() == NodeType::DIR) {
                        auto found = static_cast<Directory*>(resource)->find(name, flags);
                        if (found != nullptr) {
                            return found;
                        }
                    }
                }
            }

            return nullptr;
        }

        ~Directory() {
            for (auto& resource : m_contents) {
                delete resource;
            }
        }

        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;
        Directory(Directory&&) = delete;
        Directory& operator=(Directory&&) = delete;
    };

}

#endif
