/*
** cpp-i18n, 2023
** cpp-i18n
** File description:
** basic
*/

#include <catch2/catch_test_macros.hpp>

#include <cpp-i18n/Translator.hpp>

TEST_CASE("basic", "[basic]")
{
    i18n::Translator t;

    REQUIRE(true);
}

TEST_CASE("basic translation", "[basic]")
{
    i18n::Translator t;

    REQUIRE(t("test1", "test_basic") == "This is a test");
}

TEST_CASE("change language", "[basic]")
{
    i18n::LocaleConfig config;
    config.supportedLocales = {"fr", "en"};
    i18n::Translator t(config);

    t.setLocale("fr");
    REQUIRE(t("test1", "test_basic") == "Ceci est un test");
}

TEST_CASE("change language with unsupported locale", "[basic]")
{
    i18n::LocaleConfig config;
    config.supportedLocales = {"fr", "en"};
    i18n::Translator t(config);

    REQUIRE(t.setLocale("de") == false);
}

TEST_CASE("change supported locale with empty vector", "[basic]")
{
    i18n::Translator t;

    REQUIRE(t.setSupportedLocales({}) == false);
}

TEST_CASE("change locale directory (invalid)", "[basic]")
{
    i18n::Translator t;

    REQUIRE(t.setLocalesDirectory("invalid/") == false);
    REQUIRE(t("test1", "test_basic") == "test_basic.test1");
}

TEST_CASE("change locale directory (valid)", "[basic]")
{
    i18n::Translator t;

    REQUIRE(t.setLocalesDirectory("./assets/locales/") == true);
    REQUIRE(t("test1", "test_basic") == "This is a test");
}

TEST_CASE("change locale directory with missing trailing slash", "[basic]")
{
    i18n::Translator t;

    REQUIRE(t.setLocalesDirectory("./assets/locales") == true);
    REQUIRE(t("test1", "test_basic") == "This is a test");
}

TEST_CASE("Add supported locale", "[basic]")
{
    i18n::Translator t;

    REQUIRE(t.addSupportedLocale("fr") == true);
    REQUIRE(t.setLocale("fr") == true);
    REQUIRE(t("test1", "test_basic") == "Ceci est un test");
}

TEST_CASE("remove supported locale", "[basic]")
{
    i18n::LocaleConfig config;
    config.supportedLocales = {"fr", "en"};
    i18n::Translator t(config);

    t.setLocale("fr");
    REQUIRE(t("test1", "test_basic") == "Ceci est un test");
    t.removeSupportedLocale("fr");
    REQUIRE(t("test1", "test_basic") == "test_basic.test1");
}

TEST_CASE("Get locales directory", "[basic]")
{
    i18n::Translator t;

    REQUIRE(t.getLocalesDirectory() == "./assets/locales/");
}

TEST_CASE("Get current locale", "[basic]")
{
    i18n::LocaleConfig config;
    config.supportedLocales = {"fr", "en"};
    i18n::Translator t(config);

    REQUIRE(t.getCurrentLocale() == "en");
    REQUIRE(t.setLocale("fr") == true);
    REQUIRE(t.getCurrentLocale() == "fr");
}

TEST_CASE("Get supported locales", "[basic]")
{
    i18n::LocaleConfig config;
    config.supportedLocales = {"fr", "en"};
    i18n::Translator t(config);

    REQUIRE(t.getSupportedLocales() == config.supportedLocales);
}

TEST_CASE("Auto detect locale", "[basic]")
{
    i18n::LocaleConfig config;
    config.supportedLocales = {"fr", "en"};
    i18n::Translator t(config);

    REQUIRE(t.autoDetectLocale() == false);
    REQUIRE(t.getCurrentLocale() == "en");
}
