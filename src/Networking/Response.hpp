#ifndef __RESPONSE__
#define __RESPONSE__

#include <iostream>
#include <string>
#include "URL.hpp"
#include "Header.hpp"
#include "ResponseStatus.hpp"
#include "../Templates/Data.hpp"

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

    std::string loadHeader(const Header::_Header& type) const;
    /**
     * This method is suitable only to load data for save.
     *
     *
     * There are several moments of loading content using HTTP:
     *
     *  1. Data type
     *
     *     Format:
     *       `media-type = type "/" subtype *( ";" parameter )`
     *
     *     For the text/ * data we convert from CRLF to the system encoding.
     *     If it is windows, the encoding is correct, otherwise convert to linux encoding LF
     *
     *  2. Transfer encoding:
     *     HTTP supports several transfer encoding techniques:
     *       * *Chuncked:* The content is separated in chunks separated by `length of chunk '\r\n'`
     *       * *Deflate:* The content is compressed with zlib deflate algorithm
     *       * *Gzip* The content is compressed with gzim algorithm
     *       * *identity* is identity
     *
     *     There can be several encodings stacked, separated by the comma. Then they are applied on by another sequentally
     */
    Data<> loadBody() const;
  private:
    enum class TransferEncodingTypes {
      CHUNCKED, DEFLATE, GZIP, IDENTITY
    };

    static const std::string separator;
    static const std::string doubleSeparator;
    static const std::string headerParametersSeparator;
    static const std::string textContentTypePrefix;

    void setStatus();
    void setHeaders();
    void processTransferEncoding(std::string& body) const;
    const std::string getHeader(const std::string& response) const;
};

#endif
