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
#include <tuple>
#include <iterator>
#include <fstream>

/**
 * The wrapper around raw data information and provides basic methods to format data.
 *
 * The core concept is to provide faster modification, than data access.
 */
template <typename Comparator = std::equal_to<uint8_t>>
class Data {
  public:
    using iterator = std::list<uint8_t>::const_iterator;

    Data(): cmp() {}
    Data(const char * str, size_t size, const Comparator& cmp = {}): cmp(cmp) { append(str, size); }
    Data(const std::string& str, const Comparator& cmp = {}): cmp(cmp) { append(str); }
    Data(const std::list<uint8_t>& store, const Comparator& cmp = {}): store(store), cmp(cmp) { }
    /**
     * @param[out] - reference to the data raw content
     *
     * Complexity: O(n), where n is the size of the content
     */
    std::list<uint8_t> rawRepresentation() const {
      return store;
    }
    /**
     * @param[out] - accumulates the raw data to the the string
     *
     * Complexity: O(n)
     */
    std::string stringRepresentation() const {
      std::string result;
      return std::accumulate(store.begin(), store.end(), result, [](std::string result, uint8_t c) {
        return std::move(result) + std::string(1, c);
      });
    }
    /**
     * @param[out] - size of the data
     *
     * Complexity: O(1)
     */
    size_t size() const {
      return store.size();
    }
    /**
     * Input:
     *   @param[in] pos - position of the byte
     *
     * Output:
     *   @param[out] - byte at the specific position
     *
     * Complexity: O(n), where n == pos
     */
    iterator at(size_t pos) const {
      auto iter = store.begin();
      std::advance(iter, pos);
      return iter;
    }
    /**
     * Output:
     *   @param[out] - iterator to the first element
     *
     * Complexity: O(1)
     */
    iterator begin() const {
      return store.begin();
    }
    /**
     * Output:
     *   @param[out] - iterator to the last element
     *
     * Complexity: O(1)
     */
    iterator end() const {
      return store.end();
    }
    /**
     * Input:
     *   @param[in] begin - iterator pointing to the beginning of the sequence
     *   @param[in] begin - iterator pointing to the end of the sequence
     *
     * Output:
     *   @param[out] - Data object with the subsequence
     *
     * Complexity: O(n), where n is the size of the copied sequence
     */
    Data<Comparator> subsequence(const iterator& begin, const iterator& end) const {
      return Data<Comparator>(std::list<uint8_t>(begin, end), cmp);
    }
    /**
     * Output:
     *   @param[out] - true, in case if data stores no element
     *
     * Complexity: O(1)
     */
    bool empty() const { return store.empty(); }
    /**
     * Discussion:
     *   Pops the first element from the data, if exists.
     *
     * Complexity: O(1)
     */
    void popFirst() {
      if (!empty())
        store.pop_front();
    }
    /**
     * Discussion:
     *   Replaces all occurrences of the old sequence with the new sequence
     *
     * Input:
     *   @param[in] oldSequence - sequence of elements, which will be replaced
     *   @param[in] newSequence - sequence of elements, which will replace
     *
     * Complexity: O(nm), where n is the size of the sequence, m is the size of the oldSequence
     */
    void replace(const Data& oldSequence, const Data& newSequence) {
      auto iter = store.begin();
      while (iter != store.end()) {
        iter = eraseFirst(oldSequence, iter);

        for (const auto& item: newSequence)
          store.insert(iter, item);
      }
    }
    /**
     * Discussion:
     *   Replaces all occurrences of the old sequence with the new sequence
     *
     * Input:
     *   @param[in] oldSequence - string representation of data
     *   @param[in] newSequence - sequence of elements, which will replace
     *
     * Complexity: O(nm), where n is the size of the sequence, m is the size of the oldSequence
     */
    void replace(const std::string& oldSequence, const Data<Comparator>& newSequence) {
      replace(Data(oldSequence), newSequence);
    }
    /**
     * Discussion:
     *   Erases all occurrences of the sequence starting from position
     *
     * Input:
     *   @param[in] sequence - sequence of the elements to remove
     *   @param[in] position - start position from which search will begin
     *
     * Complexity: O(n - position), where n is the size of the store
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
     * Discussion:
     *   Erases data in the interval [begin, end)
     *
     * Input:
     *   @param[in] begin - iterator to the beginning of the sequence
     *   @param[in] end - iterator to the end of the sequence
     *
     * Output:
     *   @param[out] - iterator pointing to the position, where data subsequence was removed
     *
     * Complexity: O(m), where m is the distance between m and n
     */
    iterator eraseSequence(const iterator& begin, const iterator& end) {
      return store.erase(begin, end);
    }
    /**
     * Discussion:
     *   Erases first occurrence of the specic sequence and returns the iterator in the new sequence
     *
     * Input:
     *   @param[in] sequence - sequence of the elements to remove
     *   @param[in] position - iterator to the start position, from which search will begin
     *
     * Output:
     *   @param[out] - iterator pointing to the position, where data subsequence was removed
     *
     * Complexity: O(n)
     */
    iterator eraseFirst(const Data<Comparator>& sequence, iterator startPos) {
      auto iter = startPos;

      if ((iter = find(sequence, startPos)) != store.end()) {
        auto sequenceEndIter = iter;
        std::advance(sequenceEndIter, sequence.size());
        return eraseSequence(iter, sequenceEndIter);
      }

      return iter;
    }
    /**
     * Discussion:
     *   Validates, if the sequence begins with some sequence.
     *
     * Input:
     *   @param[in] sequence - sequence of the elements to find.
     *
     * Output:
     *   @param[out] - boolean, value, indicating, if the sequence begins with some subsequence
     *
     * Complexity: O(m), where m is subsequence size.
     */
    bool beginsWith(const Data<Comparator>& sequence) const {
      if (sequence.size() > size())
        return false;

      auto begin = sequence.begin();
      auto storeBegin = store.begin();

      while (begin != sequence.end() && *begin == *storeBegin) { begin++; storeBegin++; }

      return begin == sequence.end();
    }
    /**
     * Discussion:
     *   Validates, if the sequence begins with some sequence.
     *
     * Input:
     *   @param[in] sequence - sequence of the elements to find.
     *
     * Output:
     *   @param[out] - boolean, value, indicating, if the sequence ends with some subsequence
     *
     * Complexity: O(m), where m is subsequence size.
     */
    bool endsWith(const Data<Comparator>& sequence) const {
      if (sequence.size() > size())
        return false;

      auto begin = sequence.store.rbegin();
      auto storeBegin = store.rbegin();

      while (begin != sequence.store.rend() && *begin == *storeBegin) { begin++; storeBegin++; }

      return begin == sequence.store.rend();
    }
    /**
     * Discussion:
     *   Find first subsequence and returns the iterator to it
     *
     * Input:
     *   @param[in] sequence - sequence of the elements to find
     *   @param[in] startPos - iterator to the start position, from which search will begin
     *
     * Output:
     *   @param[out] - iterator pointing to the position, where data subsequence begins.
     *
     * Complexity: O(n)
     */
    iterator find(const Data<Comparator>& sequence, iterator startPos) const {
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
     * Discussion:
     *   Find first subsequence and returns the iterator to it. Adds possibility to move iterator to the end of the found sequence.
     *
     * Input:
     *   @param[in] sequence - sequence of the elements to find.
     *   @param[in] startPos - iterator to the start position, from which search will begin.
     *   @param[in] shouldAdvance - flag indicating, if the iterator, should be advances to the end of found sequence.
     *
     * Output:
     *   @param[out] - iterator pointing to the position, where data subsequence begins (ends in case, if shouldAdvance).
     *
     * Complexity: O(n)
     */
    iterator find(const Data<Comparator>& sequence, iterator startPos, bool shouldAdvance) const {
      auto iter = find(sequence, startPos);

      if (iter != store.end() && shouldAdvance) {
        auto size = 0;

        while (size != sequence.size() && iter != store.end()) { iter++; size++; }
      }

      return iter;
    }
    /**
     * Iterate over all intervals between specified separator
     *
     * Input:
     *   @param[in] separator - separator sequence, by which the parts of main sequence will returned
     *   @param[in] func - functor, which is called for each subsequence in the main sequence, separated by separators
     *
     * Complexity: O(nm), where n is the size of the stored data and m is the size of the separator
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
     * Input:
     *   @param[in] str - string from which data is taken
     *   @param[in] size - size of the buffer to read in
     *
     * Complexity: O(m), where m is size of the input string
     */
    void append(const char *str, size_t size) {
      if (str == nullptr)
        return;

      size_t i = 0;

      while (i != size) {
        store.push_back(str[i]);
        i++;
      }
    }
    /**
     * Appends data to the storage
     *
     * Input:
     *   @param[in] str - string from which data is taken
     *
     * Complexity: O(m), where m is size of the input string
     */
    void append(const  std::string& str) {
      for (const auto& c: str)
        store.push_back(c);
    }
    /**
     * Appends data to the storage
     *
     * Input:
     *   @param[in] str - data object, from which data is taken
     *
     * Complexity: O(m), where m is size of the input string
     */
    void append(const Data<>& data) {
      for (const auto& byte: data.rawRepresentation())
        store.push_back(byte);
    }
    /**
     * Writes data to the ostream from the specific sequence
     *
     * Input:
     *   @param[in] out - output stream,  where to write data
     *   @param[in] begin - start position from which to write
     *   @param[in] end - end position from which to write
     *
     * Output:
     *   @param[out] - output stream
     *
     * Complexity: O(m), where m is size of the input string
     */
    std::ostream& write(std::ostream& out, const iterator& begin, const iterator& end) const {
      //  TODO: add buf iterator in case of c++17
      std::ostream_iterator<uint8_t> output_iterator(out);
      std::copy(begin, end, output_iterator);
      return out;
    }
    /**
     * Discussion:
     *   Reads the data until some sequence is found or some error occurs
     *
     * Input:
     *   @param[in] in - input stream
     *   @param[in] sequence - the sequence of byte, when to stop reading the data from the file.
     *
     * Output:
     *   @param[out] - input stream
     *
     * Complexity: O(m), where m is size of the file
     */
    std::ifstream& readUntil(std::ifstream& in, const Data<>& sequence) {
      iterator pos = sequence.begin();

      while (in.good() && pos != sequence.end()) {
        uint8_t byte = 0;
        in.read((char *)&byte, 1);

        if (byte == *pos) {
          pos++;
        } else {
          pos = sequence.begin();
        }

        store.push_back(byte);
      }

      return in;
    }
    /**
     * Discussion:
     *   Reads the data of the specific size from the input file, in case, if some error occurs stop the read
     *
     * Input:
     *   @param[in] in - input stream
     *   @param[in] size - size of the input
     *
     * Output:
     *   @param[out] - input stream
     *
     * Complexity: O(m), where m is size of the file
     */
    std::ifstream& read(std::ifstream& in, size_t size) {
      size_t begin = 0;

      uint8_t byte = 0;
      while (in.good() && begin != size && in.read((char *)&byte, 1)) {
        store.push_back(byte);
        begin++;
      }

      return in;
    }
    /**
     * Discussion:
     *   Converts each byte in char and outputs it to the stream. Returns true, if both objects have the same data
     *
     * Input:
     *   @param[in] stream - output stream
     *   @param[in] data - data object to output
     *
     * Output:
     *   @param[out] stream - output stream
     *
     * Complexity: O(n), where n is size of the data
     */
    template <typename _Comparator = std::equal_to<uint8_t>>
    friend std::ostream& operator << (std::ostream& stream, const Data<_Comparator>& data) {
      for (const auto& c: data.rawRepresentation())
        stream << c;

      return stream;
    }
    /**
     * Discussion:
     *   Compares each char of the strings object with the data object. Returns true, if both objects have the same data
     *
     * Input:
     *   @param[in] stream - output stream
     *   @param[in] data - data object to output
     *
     * Complexity: O(n), where n is size of the data
     */
    template <typename _Comparator = std::equal_to<uint8_t>>
    friend bool operator == (const std::string& str, const Data<_Comparator>& data) {
      if (str.size() == data.size()) {
        auto i = str.begin();
        auto j = data.begin();

        while (data.cmp(*i, *j)) { i++; j++; }

        if (i != str.end())
          return false;

        return true;
      }
      return false;
    }
    bool operator == (const std::string& str) const {
      return str == *this;
    }
    bool operator == (const Data<Comparator>& data) {
      if (size() == data.size()) {
        auto i = begin();
        auto j = data.begin();

        while (data.cmp(*i, *j)) { i++; j++; }

        if (i != end())
          return false;

        return true;
      }
      return false;
    }
  private:
    /**
     * Raw data representation
     */
    std::list<uint8_t> store;
    /**
     * Comparator function
     */
    Comparator cmp;
};

#endif
