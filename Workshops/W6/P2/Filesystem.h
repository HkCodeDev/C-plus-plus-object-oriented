#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include "Directory.h"
#include "File.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

namespace seneca {

    class Filesystem {
        Directory* m_root;
        Directory* m_current;

    public:
        Filesystem(const std::string& fileName, const std::string& rootName = "")
            : m_root(new Directory(rootName)), m_current(m_root) {
            std::ifstream file(fileName);
            if (!file.is_open()) {
                throw std::invalid_argument("Cannot open file: " + fileName);
            }

            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string path, contents;
                if (std::getline(iss, path, '|')) {
                    std::getline(iss, contents);
                    path = trim(path);
                    contents = trim(contents);
                    addResource(path, contents);
                }
                else {
                    path = trim(line);
                    addResource(path, "");
                }
            }
        }

        ~Filesystem() {
            delete m_root;
        }

        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;

        Filesystem(Filesystem&& other) noexcept
            : m_root(other.m_root), m_current(other.m_current) {
            other.m_root = nullptr;
            other.m_current = nullptr;
        }

        Filesystem& operator=(Filesystem&& other) noexcept {
            if (this != &other) {
                delete m_root;
                m_root = other.m_root;
                m_current = other.m_current;
                other.m_root = nullptr;
                other.m_current = nullptr;
            }
            return *this;
        }

        Filesystem& operator+=(Resource* resource) {
            *m_current += resource;
            return *this;
        }

        Directory* change_directory(const std::string& dirName = "") {
            std::string trimmedDirName = trim(dirName); // Trim the directory name

            if (trimmedDirName.empty()) {
                m_current = m_root;
            }
            else {
                Resource* resource = m_current->find(trimmedDirName);
                if (!resource || resource->type() != NodeType::DIR) {
                    throw std::invalid_argument("Cannot change directory! " + trimmedDirName + " not found!");
                }
                m_current = dynamic_cast<Directory*>(resource);
            }
            return m_current;
        }


        Directory* get_current_directory() const {
            return m_current;
        }

    private:
        void addResource(const std::string& path, const std::string& contents) {
            std::istringstream iss(trim(path)); // Trim the path before processing
            std::string token;
            Directory* currentDir = m_root;

            while (std::getline(iss, token, '/')) {
                if (!token.empty()) {
                    token = trim(token); // Trim each token
                    Resource* resource = currentDir->find(token);
                    if (!resource) {
                        if (iss.peek() == EOF) { // Last token
                            if (token.find('.') == std::string::npos) { // Directory
                                Directory* newDir = new Directory(token + "/");
                                currentDir->operator+=(newDir);
                                currentDir = newDir;
                            }
                            else { // File
                                File* newFile = new File(token, trim(contents)); // Trim contents
                                currentDir->operator+=(newFile);
                            }
                        }
                        else { // Intermediate directory
                            Directory* newDir = new Directory(token + "/");
                            currentDir->operator+=(newDir);
                            currentDir = newDir;
                        }
                    }
                    else if (resource->type() == NodeType::DIR) {
                        currentDir = dynamic_cast<Directory*>(resource);
                    }
                    else {
                        throw std::invalid_argument("Conflicting resource type for " + token);
                    }
                }
            }
        }
    };

} // namespace seneca

#endif // SENECA_FILESYSTEM_H
