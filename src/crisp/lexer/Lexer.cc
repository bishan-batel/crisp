#include "Lexer.hpp"
#include <crab/num/range.hpp>
#include <crab/result/Ok.hpp>
#include <crab/opt/boolean_constructs.hpp>
#include <utility>
#include "crisp/token/Keyword.hpp"
#include "crisp/token/Spanned.hpp"

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
      case Type::UnknownCharacter: return "String";
    }
  }

  [[nodiscard]] auto Lexer::tokenize() && -> Result<TokenList> {
    tokens.clear();

    if (source.empty()) {
      return {crab::move(tokens)};
    }

    while (not_finished()) {

      if (scan_keyword()) {
        continue;
      }

      return Error{
        Error::Type::UnknownCharacter,
        SrcSpan{crab::range(index, index + 1)},
      };
    }

    return {crab::move(tokens)};
  }

  [[nodiscard]] auto Lexer::not_finished() const -> bool {
    return index < source.length();
  }

  [[nodiscard]] auto Lexer::skip_whitespace() -> bool {
    bool scanned = false;

    while (current().is_some_and(&is_whitespace)) {
      scanned = true;
      advance();
    }

    return scanned;
  }

  [[nodiscard]] auto Lexer::scan_keyword() -> bool {
    const StringView substr = source.substr(index);

    for (const auto& [key, word]: tok::Keyword::STRING_TO_WORD) {
      if (substr.starts_with(key)) {
        continue;
      }
    }
    return false;
  }

  auto Lexer::advance(usize i) -> void {
    index += i;
  }

  [[nodiscard]] auto Lexer::current() const -> Option<char> {
    if (not_finished()) {
      return source.at(index);
    }

    return crab::none;
  }

  [[nodiscard]] auto Lexer::consume() -> Option<char> {
    Option<char> c{current()};

    advance();

    return c;
  }

  auto is_whitespace(const char c) -> bool {
    switch (c) {
      case '\t':
      case '\n':
      case '\r':
      case ' ': return true;
      default: return false;
    }
  }

  Lexer::Lexer(StringView source): source{source} {}
}
