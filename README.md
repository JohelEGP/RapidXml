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
* [Policy type for case sensitivity](#policy-type-for-case-sensitivity)
* Convenience `xml_document::parse` overload for constant XML strings.

### String view support

Wherever a RapidXml 1.13 member function has `const Ch*` and `std::size_t` parameter pairs representing string spans, there is an overload taking `std::experimental::basic_string_view<Ch>` parameters, which passes to the overloaded member function the `data()` and `size()` values of the string views through the string spans' components they represent. [ Note: An empty string view can have non-`nullptr` `data()`. RapidXml functions interpret the non-`nullptr` `const Ch*` value of a string span with `0` `std::size_t` value as a [`gsl::czstring`](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#SS-views) and, if needed, attempt to calculate its size. To match this meaning of emptiness, when a string view is empty, `nullptr` is passed instead of its `data()` to the overloaded member function. -- end note ]

For `xml_base`, the `name_view` and `value_view` member functions return a mutable string view constructed with the string span components returned from the `name` and `name_size`, and `value` and `value_size` member functions respectively.

### Policy type for case sensitivity

To request or not case sensitive comparisons, the `bool case_sensitive` parameters of the overloads with string view support have been replaced with a dedicated type, `case_sensitive_policy`.

```C++
namespace rapidxml {

struct case_sensitive_policy { /*unspecified*/ };

// Requests that the comparisons are case sensitive (default).
constexpr case_sensitive_policy case_sensitive {/*unspecified*/};

// Requests that the comparisons are not case sensitive.
constexpr case_sensitive_policy non_case_sensitive {/*unspecified*/};

} // rapidxml namespace
```

These constants can also be used in place of the `bool case_sensitive` parameters.

## Possible future work

### Backwards compatible changes

* Use the [Guideline support library](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-gsl).

### Breaking changes

* In support of a vocabulary typed interface without the old ways as alternative, deprecate and remove member functions in favour of those with string view support.
    - Rename `name_view` and `value_view` to `name` and `value` respectively.
* Replace pointer to T with reference to T when the pointer can never be `nullptr`.
    - Replace pointer to T with `std::experimental::optional<std::reference_wrapper<T>>`.
* Replace `bool case_sensitive` parameters with [`case_sensitive_policy`](#policy-type-for-case-sensitivity).
* Change source code terminology.
    - Use element instead of node.
    - Use child/children when node(s) refers to them.
