# jegp/RapidXml

Project to improve and modernize the [RapidXml 1.13](http://rapidxml.sourceforge.net/) public API.

This project uses [Semantic Versioning 2.0.0](http://semver.org/).

## Dependencies

* C++17 range-based for loop if the range is a node or attribute range.
* [GSL: Guideline Support Library](https://github.com/Microsoft/GSL)

## Features

* [String span support](#string-span-support)
* [Policy type for case sensitivity](#policy-type-for-case-sensitivity)
* Convenience `xml_document::parse` overload for constant XML strings.
* [Ranges of node children and attributes](#ranges-of-node-children-and-attributes)

### String span support

Wherever a RapidXml 1.13 member function has `const Ch*` and `std::size_t` parameter pairs representing string spans, there is an overload taking `gsl::basic_string_span<const Ch>` parameters, which passes their `data()` and `size()` values to the overloaded member function through the string span components they represent. [ Note: An empty string span can have non-`nullptr` `data()`. RapidXml functions interpret the non-`nullptr` `const Ch*` value of a string span with `0` `std::size_t` value as a [`gsl::czstring`](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#SS-views) and, if needed, attempt to calculate its size. To match this meaning of emptiness, when a `gsl::basic_string_span<const Ch>` is empty, `nullptr` is passed instead of its `data()` to the overloaded member function. -- end note ]

For `xml_base`, the `name_span` and `value_span` member functions return a `gsl::basic_string_span<Ch>` [ Note: the template argument is not `const`. -- end note ] constructed with the string span components returned from the `name` and `name_size`, and `value` and `value_size` member functions respectively.

### Policy type for case sensitivity

To request or not case sensitive comparisons, the `bool case_sensitive` parameters of the overloads with string span support have been replaced with a dedicated type, `case_sensitive_policy`.

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

### Ranges of node children and attributes

```C++
// In header <rapidxml_iterators.hpp>

//...

template<class Ch>
/*unspecified*/ node_range(const xml_node<Ch> *parent,
                           gsl::basic_string_span<const Ch> name = {}) noexcept;

template<class Ch>
/*unspecified*/ attribute_range(const xml_node<Ch> *node,
                                gsl::basic_string_span<const Ch> name = {}) noexcept;
```

The functions return a range of pointers to the children/attributes of the node, optionally filtered by `name`.

The ranges offers minimal range-based for loop support.

## Possible future work

### Backwards compatible changes

* Use other components from the [Guideline support library](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-gsl).

### Breaking changes

* In support of a vocabulary typed interface without the old ways as alternative, deprecate and remove member functions in favour of those with string span support.
    - Rename `name_span` and `value_span` to `name` and `value` respectively.
* Replace pointer to T with reference to T when the pointer can never be `nullptr`.
    - Replace pointer to T with `std::experimental::optional<std::reference_wrapper<T>>`.
* Replace `bool case_sensitive` parameters with [`case_sensitive_policy`](#policy-type-for-case-sensitivity).
* Change source code terminology.
    - Use element instead of node.
    - Use child/children when node(s) refers to them.
