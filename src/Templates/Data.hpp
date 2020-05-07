#ifndef __DATA_HPP__
#define __DATA_HPP__

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

template <typename Comparator = std::equal_to<uint8_t>>
class Data {
  public:
    Data() = default;
    Data(const char * str, const Comparator& cmp): cmp(cmp) { fillStore(str); };
    Data(const std::string& str, const Comparator& cmp): cmp(cmp) { fillStore(str); };
    Data(const std::list<uint8_t>& store, const Comparator& cmp): cmp(cmp), store(store) { };

    std::vector<uint8_t> rawRepresentation() const { return store; }
    std::string stringRepresentation() const {
      std::string result;

      std::accumulate(store.begin(), store.end(), "", [](std::string result, uint8_t c) {
        return std::move(result) + std::string(1, c);
      });
    }
    size_t size() const {
      return store.size();
    }
    bool empty() const { return store.empty(); }
    /**
     * Replaces one subsequence with another
     */
    void replace(const Data& oldSequence, const Data& newSequence) {

    }
    void replace(const std::string& oldSequence, const Data& newSequence) {
      replace(Data(oldSequence), newSequence);
    }
    /**
     * Erases all occurances of the sequence starting from position
     *
     * Complexity O(n), wher n is the size of the store
     */
    void erase(const Data& sequence, size_t position = 0) {
      auto iterator = std::advance(store.begin(), position);


    }
    /**
     * Appends data to the storage
     *
     * Complexity O(m), where m is size of the input string
     */
    void append(const char * str) {
      char *pointer = str;

      while (*pointer != nullptr)
        store.push_back(*pointer);
    }
    /**
     * Writes data to the stream
     *
     * Complexity O(n), where m is size of the input string
     */
    void write(std::ofstream& stream) {
      for (const auto& c: store)
        stream << (char)c;
    }
  private:
    const std::list<uint8_t> store;
    const Comparator& cmp;

    void fillStore(const char * str) {

    }
};

#endif
