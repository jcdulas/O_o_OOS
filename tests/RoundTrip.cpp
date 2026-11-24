#include "oor/api/CardEdits.hpp"
#include "oor/formats/oos.hpp"
namespace adapter = oor::formats::oos;

#include <cstdio>

int main(int argc, char** argv)
{
    if (argc != 2) return 1;
    using namespace oor;
    const auto original = api::Deck::createModel();
    api::CardInput node;
    node.type = "Node";
    node.fields = {{model::FieldValue::Kind::Integer, 17, 0, {}}, {},
                   {model::FieldValue::Kind::Real, 0, 1.25, {}}};
    (void)api::insertCard(*original, node);
    original->setDocument("metadata", "stored in archive");
    if (adapter::write(*original, argv[1]).size() != 1) return 2;
    const auto copy = adapter::read(argv[1], {.strict = true});
    std::remove(argv[1]);
    if (copy->cardCounts() != original->cardCounts() || !copy->checkReferences().empty()) return 3;

    const auto card = api::findCard(*copy, "Node", 17);
    return card && card->fields.at(2) == "1.25" ? 0 : 5;
}
