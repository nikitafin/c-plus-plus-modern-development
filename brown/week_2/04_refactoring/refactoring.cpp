#include "json.h"
#include "xml.h"

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace Xml {
using Attributes = std::unordered_map<std::string, std::string>;
}

Json::Document XmlToJson(const Xml::Document& doc) {
  std::vector<Json::Node> result;

  for (const Xml::Node& node : doc.GetRoot().Children()) {
    result.emplace_back(std::map<std::string, Json::Node>{
        {"category", Json::Node{node.AttributeValue<std::string>("category")}},
        {"amount", Json::Node(node.AttributeValue<int>("amount"))}});
  }

  return Json::Document{Json::Node(std::move(result))};
}

Xml::Document JsonToXml(const Json::Document& doc, std::string root_name) {
  Xml::Node root(std::move(root_name), {});
  for (const auto& node : doc.GetRoot().AsArray()) {
    const std::map<std::string, Json::Node>& entry = node.AsMap();

    Xml::Attributes attr;
    attr["category"] = entry.at("category").AsString();
    attr["amount"] = std::to_string(entry.at("amount").AsInt());
    Xml::Node xml_node{"spend", std::move(attr)};
    root.AddChild(std::move(xml_node));
  }

  return Xml::Document{root};
}

#if !defined(WITH_TESTS)
#  include "test_runner.h"

void TestXmlToJson() {
  Xml::Node root("july", {});
  root.AddChild({"spend", {{"category", "travel"}, {"amount", "23400"}}});
  root.AddChild({"spend", {{"category", "food"}, {"amount", "5000"}}});
  root.AddChild({"spend", {{"category", "transport"}, {"amount", "1150"}}});
  root.AddChild({"spend", {{"category", "sport"}, {"amount", "12000"}}});
  const Xml::Document xml_doc(std::move(root));

  const auto json_doc = XmlToJson(xml_doc);

  const auto& items = json_doc.GetRoot().AsArray();
  ASSERT_EQUAL(items.size(), 4U);

  const std::vector<std::string> expected_category = {"travel", "food",
                                                      "transport", "sport"};
  const std::vector<int> expected_amount = {23400, 5000, 1150, 12000};

  for (size_t i = 0; i < items.size(); ++i) {
    const std::map<std::string, Json::Node>& item = items[i].AsMap();
    const std::string feedback_msg = "i = " + std::to_string(i);
    AssertEqual(item.at("category").AsString(), expected_category[i],
                feedback_msg);
    AssertEqual(item.at("amount").AsInt(), expected_amount[i], feedback_msg);
  }
}

void TestJsonToXml() {
  const Json::Document json_doc{Json::Node(std::vector<Json::Node>{
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("food")}, {"amount", Json::Node(2500)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("transport")}, {"amount", Json::Node(1150)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("restaurants")},
          {"amount", Json::Node(5780)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("clothes")}, {"amount", Json::Node(7500)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("travel")}, {"amount", Json::Node(23740)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("sport")}, {"amount", Json::Node(12000)}}),
  })};

  const std::string root_name = "month";
  const Xml::Document xml_doc = JsonToXml(json_doc, root_name);
  const Xml::Node& root = xml_doc.GetRoot();

  ASSERT_EQUAL(root.Name(), root_name);
  const std::vector<Xml::Node>& children = root.Children();
  ASSERT_EQUAL(children.size(), 6U);

  const std::vector<std::string> expected_category = {
      "food", "transport", "restaurants", "clothes", "travel", "sport"};
  const std::vector<int> expected_amount = {2500, 1150,  5780,
                                            7500, 23740, 12000};

  for (size_t i = 0; i < children.size(); ++i) {
    const std::string feedback_msg = "i = " + std::to_string(i);
    const Xml::Node& child = children[i];
    AssertEqual(child.Name(), "spend", feedback_msg);
    AssertEqual(child.AttributeValue<std::string>("category"),
                expected_category[i], feedback_msg);
    AssertEqual(child.AttributeValue<int>("amount"), expected_amount[i],
                feedback_msg);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestJsonToXml);
  RUN_TEST(tr, TestXmlToJson);
}

#else

#  include <gtest/gtest.h>

TEST(UnittestRefactoring, TestXmlToJson) {
  Xml::Node root("july", {});
  root.AddChild({"spend", {{"category", "travel"}, {"amount", "23400"}}});
  root.AddChild({"spend", {{"category", "food"}, {"amount", "5000"}}});
  root.AddChild({"spend", {{"category", "transport"}, {"amount", "1150"}}});
  root.AddChild({"spend", {{"category", "sport"}, {"amount", "12000"}}});
  const Xml::Document xml_doc(std::move(root));

  const auto json_doc = XmlToJson(xml_doc);

  const auto& items = json_doc.GetRoot().AsArray();
  ASSERT_EQ(items.size(), 4U);

  const std::vector<std::string> expected_category = {"travel", "food",
                                                      "transport", "sport"};
  const std::vector<int> expected_amount = {23400, 5000, 1150, 12000};

  for (size_t i = 0; i < items.size(); ++i) {
    const std::map<std::string, Json::Node>& item = items[i].AsMap();
    const std::string feedback_msg = "i = " + std::to_string(i);
    ASSERT_EQ(item.at("category").AsString(), expected_category[i])
        << feedback_msg;
    ASSERT_EQ(item.at("amount").AsInt(), expected_amount[i]) << feedback_msg;
  }
}

TEST(UnittestRefactoring, TestJsonToXml) {
  const Json::Document json_doc{Json::Node(std::vector<Json::Node>{
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("food")}, {"amount", Json::Node(2500)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("transport")}, {"amount", Json::Node(1150)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("restaurants")},
          {"amount", Json::Node(5780)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("clothes")}, {"amount", Json::Node(7500)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("travel")}, {"amount", Json::Node(23740)}}),
      Json::Node(std::map<std::string, Json::Node>{
          {"category", Json::Node("sport")}, {"amount", Json::Node(12000)}}),
  })};

  const std::string root_name = "month";
  const Xml::Document xml_doc = JsonToXml(json_doc, root_name);
  const Xml::Node& root = xml_doc.GetRoot();

  ASSERT_EQ(root.Name(), root_name);
  const std::vector<Xml::Node>& children = root.Children();
  ASSERT_EQ(children.size(), 6U);

  const std::vector<std::string> expected_category = {
      "food", "transport", "restaurants", "clothes", "travel", "sport"};
  const std::vector<int> expected_amount = {2500, 1150,  5780,
                                            7500, 23740, 12000};

  for (size_t i = 0; i < children.size(); ++i) {
    const std::string feedback_msg = "i = " + std::to_string(i);
    const Xml::Node& child = children[i];
    ASSERT_EQ(child.Name(), "spend") << feedback_msg;
    ASSERT_EQ(child.AttributeValue<std::string>("category"),
              expected_category[i])
        << feedback_msg;
    ASSERT_EQ(child.AttributeValue<int>("amount"), expected_amount[i])
        << feedback_msg;
  }
}

#endif