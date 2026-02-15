#include "Lexer.hpp"
#include <crab/assertion/todo.hpp>
#include <crab/num/range.hpp>
#include <crab/rc/Rc.hpp>
#include <crab/result/Ok.hpp>
#include <crab/opt/boolean_constructs.hpp>
#include <utility>
#include "crisp/token/Identifier.hpp"
#include "crisp/token/Keyword.hpp"
#include "crisp/token/Spanned.hpp"

namespace crisp::lexer {

  Lexer::Lexer(StringView source, Option<String> source_file): source{source}, file{crab::move(source_file)} {}

  [[nodiscard]] auto Lexer::tokenize() && -> Result<TokenList> {
    tokens.clear();

    if (source.empty()) {
      return {crab::move(tokens)};
    }

    while (not_finished()) {

      if (skip_whitespace()) {
        continue;
      }

      if (scan_keyword()) {
        continue;
      }

      return Error{
        Error::Type::UnknownCharacter,
        span(),
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
    if (not current().is_some_and(&is_identifier_char)) {
      return false;
    }

    usize start = index;

    while (current().is_some_and(&is_identifier_char)) {
      advance();
    }

    usize end = index;

    StringView identifier{source.substr(start, end - start)};

    if (identifier.empty()) {
      return false;
    }

    SrcSpan identifier_span = span(crab::range(start, end));

    fmt::println("'{}'", identifier);

    if (tok::Keyword::STRING_TO_WORD.contains(identifier)) {
      emplace<tok::Keyword>(tok::Keyword::STRING_TO_WORD.at(identifier), crab::move(identifier_span));
    } else {
      emplace<tok::Identifier>(String{identifier}, crab::move(identifier_span));
    }

    return true;
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

  [[nodiscard]] auto Lexer::span(usize length) const -> SrcSpan {
    auto start = std::min(index, source.length() - 1);
    auto end = std::min(index + length, source.length() - 1);
    return span(crab::range(start, end));
  }

  [[nodiscard]] auto Lexer::span(crab::Range<> range) const -> SrcSpan {
    return SrcSpan{range, file};
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

  auto is_identifier_char(char c) -> bool {
    if (c >= 'a' and c <= 'z') {
      return true;
    }

    if (c >= 'A' and c <= 'Z') {
      return true;
    }

    if (c >= '0' and c <= '9') {
      return true;
    }

    if (c == '_') {
      return true;
    }

    if (c == '$') {
      return true;
    }

    return false;
  }
}
