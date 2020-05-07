#ifndef __DATA_HPP__
#define __DATA_HPP__

#include <iostream>
#include <string>
#include <list>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <functional>
#include <fstream>

/**
 * The wrapper around Data type, which stores raw data information and provides basic methods to format data.
 */
template <typename Comparator = std::equal_to<uint8_t>>
class Data {
  public:
    using iterator = std::list<uint8_t>::const_iterator;

    Data(): cmp() {}
    Data(const char * str, const Comparator& cmp = {}): cmp(cmp) { append(str); }
    Data(const std::string& str, const Comparator& cmp = {}): cmp(cmp) { append(str); }
    Data(const std::list<uint8_t>& store, const Comparator& cmp = {}): cmp(cmp), store(store) { }

    std::list<uint8_t> rawRepresentation() const { return store; }
    std::string stringRepresentation() const {;
      std::string result;
      return std::accumulate(store.begin(), store.end(), result, [](std::string result, uint8_t c) {
        return std::move(result) + std::string(1, c);
      });
    }
    size_t size() const {
      return store.size();
    }
    /**
     * Returns byte at specific position
     *
     * Complexity: O(n)
     */
    uint8_t at(size_t pos) const {
      auto iter = store.begin();
      std::advance(iter, pos);
      return *iter;
    }
    iterator begin() const {
      return store.begin();
    }
    iterator end() const {
      return store.end();
    }
    Data<Comparator> subsequence(const iterator& begin, const iterator& end) const {
      return Data<Comparator>(std::list<uint8_t>(begin, end), cmp);
    }
    bool empty() const { return store.empty(); }
    /**
     * Replaces one subsequence with another
     */
    void replace(const Data& oldSequence, const Data& newSequence) {
      auto iter = store.begin();
      while (iter != store.end()) {
        iter = eraseFirst(oldSequence, iter);

        for (const auto& item: newSequence)
          store.insert(iter, item);
      }
    }
    void replace(const std::string& oldSequence, const Data<Comparator>& newSequence) {
      replace(Data(oldSequence), newSequence);
    }
    /**
     * Erases all occurances of the sequence starting from position
     *
     * Complexity: O(n - position), wher n is the size of the store
     */
    void erase(const Data<Comparator>& sequence, size_t position = 0) {
      if (position >= size())
        return;

      auto iter = store.begin();
      std::advance(iter, position);
      while (iter != store.end())
        iter = eraseFirst(sequence, iter);
    }
    /**
     * Erases first occurance of the specic sequence and returns the iterator in the new sequence
     *
     * Complexity: O(n)
     */
    std::list<uint8_t>::iterator eraseFirst(const Data<Comparator>& sequence, iterator startPos) {
      auto iter = startPos;

      if ((iter = find(sequence, startPos)) != store.end()) {
        auto currentPos = iter;
        std::advance(currentPos, sequence.size());
        store.erase(iter, currentPos);

        return currentPos;
      }

      return iter;
    }
    /**
     * Find first subsequence and returns iterator to it
     *
     * Complexity: O(n)
     */
    std::list<uint8_t>::iterator find(const Data<Comparator>& sequence, iterator startPos) const {
      auto iter = startPos;

      while (iter != store.end()) {
        if (cmp(*iter, *sequence.begin())) {
          auto sequenceIter = sequence.begin();
          auto iterCopy = iter;

          while (sequenceIter != sequence.end() && iterCopy != store.end() && cmp(*sequenceIter++, *iterCopy++)) {}

          if (sequenceIter == sequence.end())
            return iter;
        }

        iter++;
      }

      return iter;
    }
    /**
     * Iterate over all intervals between specified separator
     */
    void forEachInterval(const Data<Comparator> separator, const std::function<void(Data<Comparator>)>& func) {
      auto prev = begin();
      auto next = begin();

      while ((next = find(separator, next)) != end()) {
        func(subsequence(prev, next));
        prev = next;
        std::advance(prev, separator.size());
        std::advance(next, separator.size());
      }

      func(subsequence(prev, next));
    }
    /**
     * Appends data to the storage
     *
     * Complexity: O(m), where m is size of the input string
     */
    void append(const char *str) {
      if (str == nullptr)
        return;

      append(std::string(str));
    }
    void append(const  std::string& str) {
      for (const auto& c: str)
        store.push_back(c);
    }
    /**
     * Writes data to the stream
     *
     * Complexity: O(n), where m is size of the input string
     */
    void write(std::ofstream& stream) const {
      for (const auto& c: store)
        stream << (char)c;
    }
  private:
    std::list<uint8_t> store;
    Comparator cmp;
};

#endif
