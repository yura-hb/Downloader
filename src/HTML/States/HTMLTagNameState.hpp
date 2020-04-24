#ifndef __HTML_TAG_NAME_STATE_HPP__
#define __HTML_TAG_NAME_STATE_HPP__

#include "HTMLTokenizerState.hpp"
#include "HTMLTagStartState.hpp"
#include "HTMLTagAttributesState.hpp"

/**
 *  Group, which handles implementation of the base tag name states, for solution reference use
 *
 *  https://html.spec.whatwg.org/multipage/parsing.html#end-tag-open-state
 *
 *  Cases 12.2.5.8, 12.2.5.11, 12.2.5.14, 12.2.5.17, 12.2.5.25
 */

struct HTMLTagNameState: public HTMLTokenizerState {
  public:
    HTMLTagNameState() = delete;
    HTMLTagNameState(HTMLTagType type): type(type) {}

    void next(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) override;

  private:
    HTMLTagType type;
    /**
     *  Action on the 0009 CHARACTER TABULATION (tab), U+000A LINE FEED (LF), U+000C FORM FEED (FF), U+0020 SPACE
     */
    void whitespaceCharacterAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     *  Action on the solidus character
     */
    void solidusCharacterAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     *  Action on the > character
     */
    void greaterThanSignAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     *  Action on the alpha upper character
     */
    void alphaAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     *  Action on the null character
     */
    void nullAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     *  Action on the eof character
     */
    void eofAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     *  Action on the other character
     */
    void otherAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
};

#endif
