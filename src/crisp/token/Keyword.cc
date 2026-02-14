#include "Keyword.hpp"
#include <crab/core/unreachable.hpp>

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

  Keyword::Keyword(Word word): word{word} {}
}
