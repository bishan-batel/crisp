#include "Keyword.hpp"
#include <crab/core/unreachable.hpp>
#include <crab/preamble.hpp>
#include <crab/mem/move.hpp>

namespace crisp::tok {

  [[nodiscard]] auto Keyword::to_string() const -> String {
    switch (word) {
      case Word::If: return "if";
      case Word::Else: return "else";
      case Word::Let: return "let";
      case Word::Func: return "func";
    }

    crab::unreachable();
  }

  Keyword::Keyword(Word word, SrcSpan span): IToken{crab::move(span)}, word{word} {}
}
