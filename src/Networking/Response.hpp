#ifndef __RESPONSE__
#define __RESPONSE__

#include <iostream>
#include <string>
#include "URL.hpp"
#include "Header.hpp"
#include "ResponseStatus.hpp"
#include "../Templates/Data.hpp"
#include "Helpers/ChunkMerger.hpp"

struct Response {
  public:
    Response() = default;
    Response(const Data<>& response, const URL& url) : url(url), response(response) {
      setStatus();
      setHeaders();
    }

    URL url;
    ResponseStatus status;
    std::vector<Header> headers;
    Data<> response;

    Data<> loadHeader(const Header::_Header& type) const;
    /**
     * Discussion:
     *   This method is suitable only to load data for save.
     *
     *
     *   There are several moments of loading content using HTTP:
     *
     *    1. Data type
     *
     *       Format:
     *         `media-type = type "/" subtype *( ";" parameter )`
     *
     *       For the text/ * data we convert from CRLF to the system encoding.
     *       If it is windows, the encoding is correct, otherwise convert to linux encoding LF
     *
     *    2. Transfer encoding:
     *       HTTP supports several transfer encoding techniques:
     *         * *Chuncked:* The content is separated in chunks separated by `length of chunk '\r\n'`
     *         * *Gzip* The content is compressed with gzip algorithm
     *         * *identity* is identity
     *         * *deflate* The content is compressed with deflate zlib algorithm
     *
     *       There can be several encodings stacked, separated by the comma. Then they are applied on by another sequentally
     *
     *    3.  Content encoding
     *
     *  Output:
     *    - @param[out] - processed data object
     */
    Data<> loadBody() const;
  private:
    enum class TransferEncodingType {
      CHUNCKED, GZIP, IDENTITY
    };
    enum class ContentType {
      TEXT, PNG, JPEG, OTHER
    };

    static const std::string separator;
    static const std::string doubleSeparator;
    static const std::string headerParametersSeparator;
    static const std::string textContentTypePrefix;

    void setStatus();
    void setHeaders();
    const std::string getHeader(const std::string& response) const;

    void processTransferEncoding(Data<>& body) const;
    /**
     *  Discussion:
     *    Converts the data format to some transfer encoding type.
     *
     *  Input:
     *    - @param[in] data - data objects containing text representation of the transfer encoding
     *
     *  Output:
     *    - @param[out] - transfer encoding type
     */
    TransferEncodingType transferEncodingType(const  Data<>& data) const;
};

#endif
