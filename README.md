# jegp/RapidXml

Project to improve and modernize the [RapidXml 1.13](http://rapidxml.sourceforge.net/) public API.

## Dependencies

* [jegp 1.2.0](https://github.com/johelegp/jegp)
    - Partial C++17 support
        + Variable type traits
    - Technical Specifications
        + Library Fundamentals
            * `<experimental/string_view>`

## Features

* [String view support](#string-view-support)

### String view support

Wherever a RapidXml 1.13 member function has `const Ch*` and `std::size_t` parameter pairs representing string spans, there is an overload taking `std::experimental::basic_string_view<Ch>` parameters, which passes to the overloaded member function the `data()` and `size()` values of the string views through the string spans' components they represent. [ Note: An empty string view can have non-`nullptr` `data()`. RapidXml functions interpret the non-`nullptr` `const Ch*` value of a string span with `0` `std::size_t` value as a [`gsl::czstring`](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#SS-views) and, if needed, attempt to calculate its size. To match this meaning of emptiness, when a string view is empty, `nullptr` is passed instead of its `data()` to the overloaded member function. -- end note ]

For `xml_base`, the `name_view` and `value_view` member functions return a mutable string view constructed with the string span components returned from the `name` and `name_size`, and `value` and `value_size` member functions respectively.

## Possible future work

### Backwards compatible changes

* Use the [Guideline support library](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-gsl).

### Breaking changes

* In support of a vocabulary typed interface without the old ways as alternative, deprecate and remove member functions in favour of those with string view support.
    - Rename `name_view` and `value_view` to `name` and `value` respectively.
* Replace pointer to T with reference to T when the pointer can never be `nullptr`.
    - Replace pointer to T with `std::experimental::optional<std::reference_wrapper<T>>`.
* Replace `bool case_sensitive` parameters with a new, dedicated type.
* Change source code terminology.
    - Use element instead of node.
    - Use child/children when node(s) refers to them.
