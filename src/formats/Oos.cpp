#include "oor/formats/oos.hpp"

#include "oor/base/text/TextUtilities.hpp"
#include "oor/model/core/ModelFileReader.hpp"
#include "oor/model/core/ModelFileWriter.hpp"

namespace oor::formats::oos
{
using api::Deck;
using api::DeckReadSettings;
using api::DeckWriteSettings;

std::shared_ptr<Deck> read(const std::string& path, const DeckReadSettings& settings)
{
    model::ModelReadOptions options;
    options.strict = settings.strict;
    return Deck::fromModel(
        std::make_shared<model::Model>(model::ModelFileReader::read(base::pathFromUtf8(path), options)));
}

namespace
{

model::ModelFileWriteOptions modelFileOptionsOf(const DeckWriteSettings& settings)
{
    model::ModelFileWriteOptions options;
    options.splitIncludes = settings.splitIncludes;
    options.headerComment = settings.headerComment;
    return options;
}

} // namespace

std::vector<std::string> write(const Deck& deck, const std::string& path, const DeckWriteSettings& settings)
{
    model::ModelFileWriteReport report;
    model::ModelFileWriter::write(*deck.model(), base::pathFromUtf8(path), modelFileOptionsOf(settings), &report);
    std::vector<const model::Model*> models{deck.model().get()};
    for (std::size_t i = 0; i < models.size(); ++i)
    {
        for (const auto& [name, text] : models[i]->documents())
        {
            (void)text;
            report.dropped.push_back("application document '" + name + "' is preserved only by native archives");
        }
        for (const auto& part : models[i]->parts())
            models.push_back(part.get());
    }
    return report.dropped;
}

std::string text(const Deck& deck, const DeckWriteSettings& settings)
{
    return model::ModelFileWriter::toString(*deck.model(), modelFileOptionsOf(settings));
}

} // namespace oor::formats::oos
