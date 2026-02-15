#pragma once

#include <crab/preamble.hpp>

#include "crisp/token/IToken.hpp"
#include "crisp/token/Spanned.hpp"

namespace crisp::tok {

  class Keyword final : public IToken {

  public:

    enum class Word {
      If,
      Else,
      Let,
      Func
    };

    inline static const Dictionary<StringView, Word> STRING_TO_WORD{
      {"if",   Word::If  },
      {"else", Word::Else},
      {"let",  Word::Let },
      {"func", Word::Func},
    };

    explicit Keyword(Word word, SrcSpan span);

    [[nodiscard]] auto to_string() const -> String override;

  private:

    Word word;
  };
}
