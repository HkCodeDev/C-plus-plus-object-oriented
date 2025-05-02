#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include "Resource.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>

namespace seneca {

    inline std::string trim(const std::string& str) {
        const auto strBegin = str.find_first_not_of(" \t");
        if (strBegin == std::string::npos) return "";

        const auto strEnd = str.find_last_not_of(" \t");
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }

    class Directory : public Resource {
        std::vector<Resource*> m_contents;

    public:
        Directory(const std::string& name) {
            m_name = name;
        }

        ~Directory() {
            for (auto resource : m_contents) {
                delete resource;
            }
        }

        void update_parent_path(const std::string& parentPath) override {
            m_parent_path = parentPath;
            for (auto resource : m_contents) {
                resource->update_parent_path(path());
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
            for (auto resource : m_contents) {
                totalSize += resource->size();
            }
            return totalSize;
        }

        Directory& operator+=(Resource* resource) {
            resource->update_parent_path(path());
            m_contents.push_back(resource);
            return *this;
        }

        Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {}) {
            std::string trimmedName = trim(name); // Trim the name parameter

            for (auto resource : m_contents) {
                if (resource->name() == trimmedName) {
                    return resource;
                }
            }

            if (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end()) {
                for (auto resource : m_contents) {
                    if (resource->type() == NodeType::DIR) {
                        Resource* found = dynamic_cast<Directory*>(resource)->find(trimmedName, flags);
                        if (found) {
                            return found;
                        }
                    }
                }
            }
            return nullptr;
        }


        void remove(const std::string& name, const std::vector<OpFlags>& flags = {}) {
            auto it = std::find_if(m_contents.begin(), m_contents.end(), [&name](Resource* resource) { return resource->name() == name; });
            if (it == m_contents.end()) {
                throw std::invalid_argument(name + " does not exist in " + this->name());
            }
            if ((*it)->type() == NodeType::DIR && std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) == flags.end()) {
                throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
            }
            delete* it;
            m_contents.erase(it);
        }

        void display(std::ostream& os, const std::vector<FormatFlags>& flags = {}) const {
            os << "Total size: " << size() << " bytes\n";
            std::set<std::string> displayedNames;

            for (const auto& resource : m_contents) {
                std::string resourceName = trim(resource->name()); // Trim resource names before displaying
                if (displayedNames.find(resourceName) == displayedNames.end()) {
                    displayedNames.insert(resourceName);
                    if (resource->type() == NodeType::DIR) {
                        os << "D | " << std::left << std::setw(15) << resourceName << " | "
                            << std::right << std::setw(2) << resource->count() << " | "
                            << std::right << std::setw(10) << resource->size() << " bytes |";
                    }
                    else if (resource->type() == NodeType::FILE) {
                        os << "F | " << std::left << std::setw(14) << resourceName << " | "
                            << "    | " // Empty space for file
                            << std::right << std::setw(4) << resource->size() << " bytes |";
                    }
                    os << "\n";
                }
            }
        }


    };

} // namespace seneca

#endif // SENECA_DIRECTORY_H
