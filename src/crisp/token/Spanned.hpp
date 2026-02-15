#pragma once

#include <crab/preamble.hpp>
#include <crab/opt/Option.hpp>
#include <crab/num/range.hpp>
#include <utility>

namespace crisp {

  struct SrcSpan final {

    explicit SrcSpan(Range<> range, Option<String> source_file = crab::none):
        range{range}, source_file{crab::move(source_file)} {}

    Range<> range;
    Option<String> source_file{};
  };
}
