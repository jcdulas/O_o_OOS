#pragma once

#include "oor/base/diagnostics/DiagnosticSink.hpp"
#include "oor/base/threading/CancellationToken.hpp"

#include "oor/deck/records/ModelText.hpp"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace oor::deck
{

// The extension of a model file.
inline constexpr std::string_view MODEL_FILE_EXTENSION = ".oos";
// True when `path` names a model file (its extension is .oos, in any case).
[[nodiscard]] bool isModelFile(const std::filesystem::path& path);

// Reads a model file (.oos) and every file an Include record names, into items (docs/model-format.md):
//
//   - one record per line, values separated by ';' (RecordText);
//   - '#' first on a line (after spaces) makes it a comment, which belongs to the item after it;
//   - empty lines are ignored;
//   - a line in brackets opens a section;
//   - `Include;path` inserts the items of another model file, its path relative to the including file (or absolute).
//
// A problem in the text is a diagnostic (the line is skipped); a main file that cannot be read throws IoError.
struct ModelFileLexer
{
    // The name of the record that includes a file.
    static constexpr std::string_view INCLUDE_RECORD = deck::INCLUDE_RECORD;

    [[nodiscard]] static ModelText read(const std::filesystem::path& mainFile, const ReadOptions& options,
                                        base::DiagnosticSink& sink, const base::CancellationToken* token = nullptr);
    // The items of a text that is not in a file (an Include in it is looked up from `folder`).
    [[nodiscard]] static ModelText readText(std::string_view text, const std::filesystem::path& folder,
                                            base::DiagnosticSink& sink);
};

} // namespace oor::deck
