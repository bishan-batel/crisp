#include "Spanned.hpp"

namespace crisp {
  auto format_as(const SrcSpan& span) -> String {
    return fmt::format(
      "Source(content={:?}, range=[{}..{}], file={:?})",
      span.source_file.as_ref().map([&](const StringView source) {
        return source.substr(span.range.upper_bound(), span.range.lower_bound());
      }),
      span.range.lower_bound(),
      span.range.upper_bound(),
      span.source_file
    );
  }
}
