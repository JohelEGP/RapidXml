#include <vector>
#include "../../rapidxml_iterators.hpp"
#include "../test_utils.hpp"

using namespace std;
using namespace rapidxml;

int main()
{
    vector<string_view> names{"elem1", "elem2", "attr1", "attr2"};
    vector<string_view> values{"elemval1", "elemval2", "attrval1", "attrval2"};

    auto name_it{names.begin()};
    auto value_it{values.begin()};

    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element, *name_it++, *value_it++);
    xml_node<char> *node2 = doc.allocate_node(node_element, *name_it++, *value_it++);
    node1->append_attribute(doc.allocate_attribute(*name_it++, *value_it++));
    node2->append_attribute(doc.allocate_attribute(*name_it++, *value_it++));
    doc.append_node(node1);
    doc.append_node(node2);

    auto elem_name_it{names.begin()};
    auto attr_name_it{names.begin() + 2};
    auto elem_value_it{values.begin()};
    auto attr_value_it{values.begin() + 2};

    for (auto &child : node_range(&doc))
    {
        CHECK(*elem_name_it++ == child.name_ref());
        CHECK(*elem_value_it++ == child.value_ref());

        for (auto attr : attribute_range(&child))
        {
            CHECK(*attr_name_it++ == attr.name_ref());
            CHECK(*attr_value_it++ == attr.value_ref());
        }
    }

    return test::final_results();
}
