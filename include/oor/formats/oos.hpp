#pragma once

#include "oor/api/Deck.hpp"

namespace oor::formats::oos
{
[[nodiscard]] std::shared_ptr<api::Deck> read(const std::string& path, const api::DeckReadSettings& settings = {});
std::vector<std::string> write(const api::Deck& deck, const std::string& path,
                               const api::DeckWriteSettings& settings = {});
std::string text(const api::Deck& deck, const api::DeckWriteSettings& settings = {});
} // namespace oor::formats::oos
