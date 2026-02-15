#include "Error.hpp"

namespace crisp::lexer {
  Error::Error(Type type, SrcSpan span): type{type}, span{crab::move(span)} {}

  [[nodiscard]] auto Error::get_type() const -> Type {
    return type;
  }

  [[nodiscard]] auto Error::get_span() const -> const SrcSpan& {
    return span;
  }

  [[nodiscard]] auto Error::what() const -> String {
    switch (type) {
      case Type::UnknownCharacter: return fmt::format("Unknown Character Found in {}", get_span());
    }
  }

}
