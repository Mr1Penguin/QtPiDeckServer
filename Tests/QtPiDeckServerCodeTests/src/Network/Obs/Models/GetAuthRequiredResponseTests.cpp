#define BOOST_TEST_MODULE GetAuthRequiredResponseTests // NOLINT
#include "BoostUnitTest.hpp"

#include "Network/Obs/Models/GetAuthRequiredResponse.hpp"
#include "Utilities/Logging.hpp"
#include "Utilities/Literals.hpp"

auto main(int argc, char* argv[]) -> int {
  QtPiDeck::Utilities::initLogging("GetAuthRequiredResponseTests");
  return boost::unit_test::unit_test_main(&init_unit_test, argc, argv);
}

auto operator<<(std::ostream& ostr, const std::optional<QString>& right) -> std::ostream& {
  using namespace QtPiDeck::Utilities::literals;
  return operator<<(ostr, right.value_or("(nil)"_qs).toStdString());
}

CT_BOOST_AUTO_TEST_SUITE(GetAuthRequiredResponseTests)

using namespace QtPiDeck::Network::Obs;
using namespace QtPiDeck::Network::Obs::Models;

CT_BOOST_AUTO_TEST_CASE(GetAuthRequiredResponseShouldBeParsedFromJson) {
  using namespace QtPiDeck::Utilities::literals;
  const auto challengeString = "12345"_qs;
  const auto json = [&challengeString]() {
    QJsonObject obj;
    obj[GetAuthRequiredResponse::authRequiredField] = false;
    obj[GetAuthRequiredResponse::challengeField] = challengeString;
    obj[GetAuthRequiredResponse::saltField] = QJsonValue::Null;
    obj[GetAuthRequiredResponse::statusField] = GetAuthRequiredResponse::successStatus;
    // omitted (no key in json)
    // obj[GetAuthRequiredResponse::errorField] = QJsonValue::Null;
    return QString{QJsonDocument{obj}.toJson()};
  }();

  const auto parsedObject = GetAuthRequiredResponse::fromJson(json);

  CT_BOOST_TEST(parsedObject.authRequired == false);
  CT_BOOST_TEST(parsedObject.challenge == challengeString);
  CT_BOOST_TEST(!parsedObject.salt.has_value());
  CT_BOOST_TEST(parsedObject.status == GetAuthRequiredResponse::successStatus);
  CT_BOOST_TEST(!parsedObject.error.has_value());
}

CT_BOOST_AUTO_TEST_SUITE_END()