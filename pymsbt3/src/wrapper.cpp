// python wrapper for the library
#include <pybind11/cast.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <msbt/msbt.h>
#include "exio/types.h"
#include "msbt/tags.h"
#include"wrapper.h"

namespace py = pybind11;
namespace tags = oepd::msbt::tags;
constexpr auto byref = py::return_value_policy::reference;

PYBIND11_MODULE(pymsbt3, m){
    m.doc() = "Python wrapper for the msbt EPD library.";

    m.def("FromBinary", &oepd::msbt::FromBinary, py::arg("data"), py::call_guard<py::gil_scoped_release>());
    m.def("FromText", &oepd::msbt::FromText, py::arg("text"), py::call_guard<py::gil_scoped_release>());

    py::class_<oepd::msbt::MSBT>(m, "MSBT")
    .def_readonly("label_section", &oepd::msbt::MSBT::m_label_section, byref)
    //.def_readonly("m_attribute_section", &oepd::msbt::MSBT::m_attribute_section, byref)
    .def_readwrite("text_section", &oepd::msbt::MSBT::m_text_section, byref)
    .def("ToBinary", &oepd::msbt::MSBT::ToBinary, py::call_guard<py::gil_scoped_release>())
    .def("ToText", &oepd::msbt::MSBT::ToText, py::call_guard<py::gil_scoped_release>());


    auto m_tags = m.def_submodule("tags", "MSBT text entry tag classes");
    py::class_<tags::Tag>(m_tags, "Tag")
    .def("ToText", &tags::Tag::ToText, py::call_guard<py::gil_scoped_release>());

    py::class_<tags::FontTag>(m_tags, "FontTag")
    .def("ToText", &tags::FontTag::ToText, py::call_guard<py::gil_scoped_release>())
    .def_readonly("font", &tags::FontTag::m_font, byref);

    py::class_<tags::FontSizeTag>(m_tags, "FontSizeTag")
    .def("ToText", &tags::FontSizeTag::ToText, py::call_guard<py::gil_scoped_release>())
    .def_readonly("font_size", &tags::FontSizeTag::m_font_size, byref);

    py::class_<tags::UnknownTag>(m_tags, "UnknownTag")
    .def("ToText", &tags::UnknownTag::ToText, py::call_guard<py::gil_scoped_release>())
    .def_readonly("group", &tags::UnknownTag::m_group, byref)
    .def_readonly("type", &tags::UnknownTag::m_type, byref)
    .def_readonly("data", &tags::UnknownTag::m_data, byref);


    auto m_sections = m.def_submodule("sections", "Various MSBT sections.");
    py::class_<oepd::msbt::LabelSection>(m_sections, "LabelSection")
    .def(py::init())
    .def("Write", &oepd::msbt::LabelSection::Write, py::call_guard<py::gil_scoped_release>())
    .def_readonly("label_entries", &oepd::msbt::LabelSection::m_label_entries, byref);

    py::class_<oepd::msbt::TextSection>(m_sections, "TextSection")
    .def(py::init())
    .def("Write", &oepd::msbt::TextSection::Write, py::call_guard<py::gil_scoped_release>())
    .def_readwrite("text_entries", &oepd::msbt::TextSection::m_text_entries, byref);

    py::class_<oepd::msbt::TextSection::TextEntryValue>(m_sections, "TextEntryValue")
    .def_readwrite("tag", &oepd::msbt::TextSection::TextEntryValue::m_tag, byref)
    .def_readwrite("text", &oepd::msbt::TextSection::TextEntryValue::m_text, byref);

    py::class_<oepd::msbt::TextSection::TextEntry>(m_sections, "TextEntry")
    .def(py::init())
    .def("ToText", &oepd::msbt::TextSection::TextEntry::ToText, py::call_guard<py::gil_scoped_release>())
    .def_readwrite("values", &oepd::msbt::TextSection::TextEntry::m_values, byref);

}