#include "msbt/tags.h"
#include "util.h"

namespace oepd::msbt::tags {

Tag* CreateTag(u16 group_id, u16 type_id, tcb::span<const u8> data) {
  Tag* tag;
  if (group_id == 201) {
    tag = new UnknownTag;
  } else {
    tag = new UnknownTag;
  }

  tag->Fill(group_id, type_id, data);
  return tag;
}

Tag* CreateTag(std::string text) {
  Tag* tag;
  const auto tag_info = util::parse_tag(text);

  if (tag_info.first == "201") {
    tag = new UnknownTag;
  } else {
    tag = new UnknownTag;
  }

  tag->Fill(tag_info.first, tag_info.second);
  return tag;
}

void UnknownTag::Fill(u16 group_id, u16 type_id, tcb::span<const u8> data) {
  m_group = group_id;
  m_type = type_id;
  m_data = data;
}

void UnknownTag::Fill(std::string group_name, TagParams params) {
  m_group = stoi(group_name);
  for (const auto entry : params) {
    if (entry.first == "Type") {
      m_type = stoi(entry.second);
    } else if (entry.first == "Data") {
      m_private_data = util::from_hex(entry.second);
      m_data = *m_private_data;
    }
  }
}

std::string UnknownTag::ToText() {
  return "<" + std::to_string(m_group) + " Type='" + std::to_string(m_type) +
         (m_data.size() > 0 ? "' Data='" + util::to_hex(m_data) + "'/>" : "'/>");
}

void UnknownTag::ToBinary(exio::BinaryWriter& writer) {
  writer.Write<u16>(m_group);
  writer.Write<u16>(m_type);
  writer.Write<u16>(m_data.size());
  writer.WriteBytes(m_data);
}

}  // namespace oepd::msbt::tags