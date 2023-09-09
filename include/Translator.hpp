/*
** cpp-i18n, 2023
** cpp-i18n
** File description:
** App
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace i18n
{

    /**
     * @brief Parameters to configure the translator.
     */
    struct LocaleConfig
    {
        /**
         * @brief The directory where the locales are stored. Namespaces must be stored in subdirectories (e.g.
         * ./assets/locales/en/namespace.json).
         */
        std::string localesDirectory = "./assets/locales/";

        /**
         * @brief The current locale which will use the translator. Must be supported.
         */
        std::string currentLocale = "en";

        /**
         * @brief List of supported locales. Will trigger an error during loading if the current locale or fallback
         * locale is not supported. (e.g. if there is a missing directory in the locales directory).
         */
        std::vector<std::string> supportedLocales = { "en" };
    };

    class Translator
    {
    public:
        /**
         * @brief Construct a new Translator object with default parameters if no parameters are given. Will load
         * translations from the default locales directory. (./assets/locales/)
         * @param localeConfig Parameters to configure the translator.
         */
        Translator(const LocaleConfig &localeConfig = LocaleConfig());
        ~Translator() = default;

        /**
         * @brief Set the locales directory. Will load translations from the given directory.
         * @param localesDirectory Directory where the locales are stored. Each locale is a subdirectory. Namespaces
         * are file inside the locale subdirectories. (e.g. ./assets/locales/en/namespace.json)
         * @return true if the directory exists and is valid.
         */
        bool setLocalesDirectory(const std::string &localesDirectory);

        /**
         * @brief Set the current locale.
         * @param currentLocale locale to use. Must be supported.
         * @return true if the locale is supported.
         */
        bool setLocale(const std::string &currentLocale);

        /**
         * @brief Set the supported locales. Will trigger a reload of the translations.
         * @param supportedLocales List of supported locales. (e.g. { "en", "fr" })
         * @return true if the locales are valid.
         */
        bool setSupportedLocales(const std::vector<std::string> &supportedLocales);

        /**
         * @brief Add a supported locale. Will trigger a single reload of the translation.
         * @param supportedLocale locale to add. Must be valid. (e.g. "en")
         * @return true if the locale is valid.
         */
        bool addSupportedLocale(const std::string &supportedLocale);

        /**
         * @brief Remove a supported locale.
         * @param supportedLocale locale to remove. Must be valid. (e.g. "en")
         * @return true if the locale was supported.
         */
        bool removeSupportedLocale(const std::string &supportedLocale);

        /**
         * @brief Get the locales directory
         * @return Path to the locales directory. (e.g. "./assets/locales/")
         */
        const std::string &getLocalesDirectory() const;

        /**
         * @brief Get the current locale
         * @return returns the locale currently used. (e.g. "en")
         */
        const std::string &getCurrentLocale() const;

        /**
         * @brief Get the supported locales
         * @return List of supported locales. (e.g. { "en", "fr" })
         */
        const std::vector<std::string> &getSupportedLocales() const;

        /**
         * @brief Get the translation of a key in a namespace.
         * @param key Key to translate. (e.g. "hello")
         * @param ns Namespace of the key. (e.g. "home")
         * @return Translation of the key in the namespace. (e.g. "Hello")
         */
        std::string translate(const std::string &key, const std::string &ns = "");

        /**
         * @brief Get the translation of a key in a namespace.
         * @param key Key to translate. (e.g. "hello")
         * @param ns Namespace of the key. (e.g. "home")
         * @return Translation of the key in the namespace. (e.g. "Hello")
         */
        std::string operator()(const std::string &key, const std::string &ns = "");

    private:
        bool m_loadLocalesDirectory();
        bool m_loadLocale(const std::string &locale);
        bool m_loadNamespaces(const std::filesystem::path &localePath, const std::string &locale);

        void m_printError(const std::string &message) const;
        void m_printWarning(const std::string &message) const;

    private:
        LocaleConfig m_localeConfig;

        // <locale, <namespace, json>>
        std::unordered_map<std::string, std::unordered_map<std::string, json>> m_locales;
    };

} // i18n
