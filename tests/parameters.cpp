/*
** EPITECH PROJECT, 2023
** Project
** File description:
** parameters
*/

#include <catch2/catch_test_macros.hpp>

#include <cpp-i18n/Translator.hpp>

TEST_CASE("Simple parameter", "[parameters]")
{
    i18n::LocaleConfig config;
    config.supportedLocales = {"fr", "en"};
    i18n::Translator t(config);

    REQUIRE(t("test1", "test_parameters", {{ "name", "John" }}) == "My name is John");
    t.setLocale("fr");
    REQUIRE(t("test1", "test_parameters", {{ "name", "John" }}) == "Mon nom est John");
}

TEST_CASE("Multiple parameters", "[parameters]")
{
    i18n::LocaleConfig config;
    config.supportedLocales = {"fr", "en"};
    i18n::Translator t(config);

    REQUIRE(t("test2", "test_parameters", {{ "name", "John" }, { "age", "20" }}) ==
    "My name is John and I'm 20 years old");
    t.setLocale("fr");
    REQUIRE(t("test2", "test_parameters", {{ "name", "John" }, { "age", "20" }}) == "Mon nom est John et j'ai 20 ans");
}

TEST_CASE("Missing parameter", "[parameters]")
{
    i18n::Translator t;

    REQUIRE(t("test1", "test_parameters") == "My name is {{ name }}");
}

TEST_CASE("Too many parameters given", "[parameters]")
{
    i18n::Translator t;

    REQUIRE(t("test1", "test_parameters", {{ "name", "John" }, { "age", "20" }}) == "My name is John");
}