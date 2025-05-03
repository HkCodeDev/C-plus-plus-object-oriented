#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <stdexcept>

namespace seneca {

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder() : m_name{ "" }, m_product{ "" }, m_cntItem{ 0 }, m_lstItem{ nullptr } {}

    CustomerOrder::CustomerOrder(const std::string& record) : CustomerOrder() {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_name = util.extractToken(record, next_pos, more);
        m_product = util.extractToken(record, next_pos, more);
        m_cntItem = std::count(record.begin() + next_pos, record.end(), util.getDelimiter()) + 1;

        m_lstItem = new Item * [m_cntItem];
        for (size_t i = 0; i < m_cntItem && more; ++i) {
            m_lstItem[i] = new Item(util.extractToken(record, next_pos, more));
        }

        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& other) {
        throw std::runtime_error("Copy operations are not allowed");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        *this = std::move(other);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }


    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName) {
                std::cout << "Checking item " << m_lstItem[i]->m_itemName << " - Filled: " << m_lstItem[i]->m_isFilled << "\n";
                if (!m_lstItem[i]->m_isFilled) {
                    return false;
                }
            }
        }
        return true;
    }


    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        std::string stationItemName = Utilities::trim(station.getItemName());

        for (size_t i = 0; i < m_cntItem; ++i) {
            std::string orderItemName = Utilities::trim(m_lstItem[i]->m_itemName);

            if (orderItemName == stationItemName && !m_lstItem[i]->m_isFilled) {

                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();

                    os << "    Filled " << Utilities::trim(m_name) << ", " << Utilities::trim(m_product) << " [" << orderItemName << "]\n";
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << orderItemName << "]\n";
                }

                // Exit after finding and filling the item
                break;
            }
        }
    }
    void CustomerOrder::display(std::ostream& os) const {
        std::string trimmedName = Utilities::trim(m_name);
        std::string trimmedProduct = Utilities::trim(m_product);

        os << trimmedName << " - " << trimmedProduct << "\n";
        for (size_t i = 0; i < m_cntItem; ++i) {
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
                << std::setw(30) << std::setfill(' ') << std::left << Utilities::trim(m_lstItem[i]->m_itemName) << " - "
                << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << "\n";
        }
    }


}
