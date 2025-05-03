#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <stdexcept>

namespace seneca {

    class Utilities {
        size_t m_widthField = 1; // specifies the length of the token extracted; used for display purposes; default value is 1
        static char m_delimiter; // separates the tokens in any given std::string object. All Utilities objects in the system share the same delimiter

    public:
        // sets the field width of the current object to the value of parameter newWidth
        void setFieldWidth(size_t newWidth) {
            m_widthField = newWidth;
        }

        // returns the field width of the current object
        size_t getFieldWidth() const {
            return m_widthField;
        }

        // extracts a token from string str referred to by the first parameter.
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more) {
            if (next_pos >= str.length()) {
                more = false;
                return "";
            }

            size_t end_pos = str.find(m_delimiter, next_pos);
            if (end_pos == std::string::npos) {
                more = false;
                end_pos = str.length();
            }
            else {
                more = true;
            }

            if (next_pos == end_pos) {
                more = false;
                throw std::runtime_error("Delimiter found at next_pos");
            }

            std::string token = str.substr(next_pos, end_pos - next_pos);

            // Update the field width if necessary
            if (m_widthField < token.length()) {
                m_widthField = token.length();
            }

            next_pos = end_pos + 1;
            return token;
        }

        // sets the delimiter for this class to the character received
        static void setDelimiter(char newDelimiter) {
            m_delimiter = newDelimiter;
        }

        // returns the delimiter for this class
        static char getDelimiter() {
            return m_delimiter;
        }
        static std::string trim(const std::string& str) {
            size_t first = str.find_first_not_of(' ');
            if (std::string::npos == first) {
                return str;
            }
            size_t last = str.find_last_not_of(' ');
            return str.substr(first, (last - first + 1));
        }
    };

}

#endif // UTILITIES_H
