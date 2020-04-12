#ifndef __HTML_TOKEN_HPP__
#define __HTML_TOKEN_HPP__

#include <iostream>
#include <string>
#include <map>

struct HTMLToken {
  public:
    enum class HTMLTokenType {
      DOCTYPE,
      START_TAG,
      END_TAG,
      COMMENT,
      CHARACTER,
      END_OF_FILE
    };
    /**
     *  Abstract method to enable self closing flag in the start/end tokens and force quirk flag in the DOCKTYPE token
     */
    virtual void setFlagEnabled() = 0;
    virtual HTMLTokenType getType() const = 0;
    virtual ~HTMLToken() {};
};

struct HTMLDocktypeToken: public HTMLToken {
  public:
    HTMLDocktypeToken(const std::string& name, const std::string& publicId, const std::string& privateId): name(name), publicId(publicId), privateId(privateId) {}
    // Overriden
    void setFlagEnabled() override;
    HTMLTokenType getType() const override;
  private:
    std::string name = "";
    std::string publicId = "";
    std::string privateId = "";
    bool forceQuirkFlag = false;
};

struct HTMLStartTagToken: public HTMLToken {
  public:
    HTMLStartTagToken() = default;
    HTMLStartTagToken(const std::string& tagName, const std::map<std::string, std::string> attributes): tagName(tagName), attributes(attributes) {}
    // Overriden
    void setFlagEnabled() override;
    HTMLTokenType getType() const override;
  private:
    std::string tagName = "";
    std::map<std::string, std::string> attributes = {};
    bool isSelfClosed = false;
};

struct HTMLEndTagToken: public HTMLToken {
  public:
    HTMLEndTagToken() = default;
    HTMLEndTagToken(const std::string& tagName): tagName(tagName) {}
    // Overriden
    void setFlagEnabled() override;
    HTMLTokenType getType() const override;
  private:
    std::string tagName;
    bool isSelfClosed = false;
};

struct HTMLCommentToken: public HTMLToken {
  public:
    HTMLCommentToken() = default;
    HTMLCommentToken(const std::string& data): data(data) {}
    // Overriden
    void setFlagEnabled() override;
    HTMLTokenType getType() const override;
  private:
    std::string data = "";
};

struct HTMLCharacterToken: public HTMLToken {
  public:
    HTMLCharacterToken(const std::string& data): data(data) {}
    // Overriden
    void setFlagEnabled() override;
    HTMLTokenType getType() const override;
  private:
    std::string data = "";
};

struct HTMLEOFToken: public HTMLToken {
  // Overriden
  void setFlagEnabled() override;
  HTMLTokenType getType() const override;
};

#endif
