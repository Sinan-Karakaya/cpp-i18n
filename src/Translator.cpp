/*
** cpp-i18n, 2023
** cpp-i18n
** File description:
** App
*/

#include "../include/cpp-i18n/Translator.hpp"

namespace i18n
{
    Translator::Translator(const LocaleConfig &localeConfig)
    {
        if (localeConfig.localesDirectory != m_localeConfig.localesDirectory)
            m_localeConfig.localesDirectory = localeConfig.localesDirectory;
        if (localeConfig.currentLocale != m_localeConfig.currentLocale)
            m_localeConfig.currentLocale = localeConfig.currentLocale;
        if (localeConfig.supportedLocales != m_localeConfig.supportedLocales)
            m_localeConfig.supportedLocales = localeConfig.supportedLocales;

        m_loadLocalesDirectory();
    }

    bool Translator::setLocalesDirectory(const std::string &localesDirectory)
    {
        const std::string backupLocalesDirectory = m_localeConfig.localesDirectory;
        if (localesDirectory[localesDirectory.size() - 1] != '/') {
            m_localeConfig.localesDirectory = localesDirectory + '/';
        } else {
            m_localeConfig.localesDirectory = localesDirectory;
        }

        m_locales.clear();
        if (!m_loadLocalesDirectory()) {
            m_locales.clear();
            return false;
        }
        return true;
    }

    bool Translator::setLocale(const std::string &currentLocale)
    {
        if (std::find(m_localeConfig.supportedLocales.begin(), m_localeConfig.supportedLocales.end(), currentLocale)
        == m_localeConfig.supportedLocales.end()) {
            m_printError("The locale '" + currentLocale + "' is not supported. Please see the method 'setSupportedLocales'.");
            return false;
        }

        m_localeConfig.currentLocale = currentLocale;
        return true;
    }

    bool Translator::setSupportedLocales(const std::vector<std::string> &supportedLocales)
    {
        if (supportedLocales.empty()) {
            m_printError("The supported locales vector is empty.");
            return false;
        }
        m_localeConfig.supportedLocales = supportedLocales;
        m_locales.clear();
        m_loadLocalesDirectory();
        return true;
    }

    bool Translator::addSupportedLocale(const std::string &supportedLocale)
    {
        if (std::find(m_localeConfig.supportedLocales.begin(), m_localeConfig.supportedLocales.end(), supportedLocale)
        != m_localeConfig.supportedLocales.end()) {
            m_printError("The locale '" + supportedLocale + "' is already supported.");
            return false;
        }

        m_localeConfig.supportedLocales.push_back(supportedLocale);
        m_loadLocale(supportedLocale);
        return true;
    }

    bool Translator::removeSupportedLocale(const std::string &supportedLocale)
    {
        if (std::find(m_localeConfig.supportedLocales.begin(), m_localeConfig.supportedLocales.end(), supportedLocale)
        == m_localeConfig.supportedLocales.end()) {
            m_printError("The locale '" + supportedLocale + "' is already not supported.");
            return false;
        }

        m_localeConfig.supportedLocales.erase(std::remove(m_localeConfig.supportedLocales.begin(),
        m_localeConfig.supportedLocales.end(), supportedLocale), m_localeConfig.supportedLocales.end());
        m_locales.erase(supportedLocale);
        return true;
    }

    bool Translator::autoDetectLocale()
    {
        std::string locale = std::locale("").name();

        if (locale.empty()) {
            m_printError("The locale could not be auto-detected.");
            return false;
        }

        if (std::find(m_localeConfig.supportedLocales.begin(), m_localeConfig.supportedLocales.end(), locale)
        == m_localeConfig.supportedLocales.end()) {
            m_printError("The locale '" + locale + "' is not supported. Please see the method 'setSupportedLocales'.");
            return false;
        }

        return setLocale(locale);
    }

    const std::string &Translator::getLocalesDirectory() const
    {
        return m_localeConfig.localesDirectory;
    }

    const std::string &Translator::getCurrentLocale() const
    {
        return m_localeConfig.currentLocale;
    }

    const std::vector<std::string> &Translator::getSupportedLocales() const
    {
        return m_localeConfig.supportedLocales;
    }

    std::string Translator::translate(const std::string &key, const std::string &ns, const
    std::unordered_map<std::string, std::string> &args)
    {
        if (m_locales.find(m_localeConfig.currentLocale) == m_locales.end()) {
            m_printError("The locale '" + m_localeConfig.currentLocale + "' is not loaded.");
            return ns + "." + key;
        }

        if (m_locales.at(m_localeConfig.currentLocale).find(ns) == m_locales.at(m_localeConfig.currentLocale).end()) {
            m_printError("The namespace '" + ns + "' is not loaded.");
            return ns + "." + key;
        }

        if (args.empty())
            return m_locales[m_localeConfig.currentLocale][ns][key].get<std::string>();
        std::string rawString = m_locales[m_localeConfig.currentLocale][ns][key].get<std::string>();
        return m_replaceArgs(rawString, args);
    }

    std::string Translator::operator()(const std::string &key, const std::string &ns, const
    std::unordered_map<std::string, std::string> &args)
    {
        return translate(key, ns, args);
    }

    std::string Translator::m_replaceArgs(const std::string &rawString, const std::unordered_map<std::string, std::string> &args) const
    {
        std::string result = rawString;
        for (const auto &arg : args) {
            std::string key = "{{ " + arg.first + " }}";
            std::size_t pos = result.find(key);
            if (pos == std::string::npos)
                continue;
            result.replace(pos, key.size(), arg.second);
        }
        return result;
    }

    bool Translator::m_loadLocalesDirectory()
    {
        for (const auto &locale : m_localeConfig.supportedLocales) {
            std::filesystem::path localePath = m_localeConfig.localesDirectory + locale;
            if (!std::filesystem::exists(localePath) || !std::filesystem::is_directory(localePath)) {
                m_printError("The directory '" + localePath.string() + "' does not exist or is not a directory.");
                return false;
            }

            if (!m_loadNamespaces(localePath, locale))
                return false;
        }
        return true;
    }

    void Translator::m_printError(const std::string &message) const
    {
#ifndef NDEBUG
        std::cout << "\033[1;31m" << "cpp-i18n[ERROR]: " << message << "\033[0m" << std::endl;
#endif
        (void)message;
    }

    void Translator::m_printWarning(const std::string &message) const
    {
#ifndef NDEBUG
        std::cout << "\033[1;33m" << "cpp-i18n[WARN]: " << message << "\033[0m" << std::endl;
#endif
        (void)message;
    }

    bool Translator::m_loadLocale(const std::string &locale)
    {
        std::filesystem::path localePath = m_localeConfig.localesDirectory + locale;
        if (!std::filesystem::exists(localePath) || !std::filesystem::is_directory(localePath)) {
            m_printError("The directory '" + localePath.string() + "' does not exist or is not a directory.");
            return false;
        }

        return m_loadNamespaces(localePath, locale);
    }

    bool Translator::m_loadNamespaces(const std::filesystem::path &localePath, const std::string &locale)
    {
        for (const auto &entry : std::filesystem::directory_iterator(localePath)) {
            if (!std::filesystem::is_regular_file(entry)) {
                m_printError("The file '" + entry.path().string() + "' is not a regular file.");
                return false;
            }

            std::ifstream file(entry.path());
            if (!file.is_open()) {
                m_printError("The file '" + entry.path().string() + "' cannot be opened.");
                return false;
            }

            json localeJson;
            try {
                file >> localeJson;
            } catch (const std::exception &e) {
                m_printError("The file '" + entry.path().string() + "' is not a valid JSON file.");
                return false;
            }

            if (!localeJson.is_object()) {
                m_printError("The file '" + entry.path().string() + "' is not a valid JSON file.");
                return false;
            }

            std::string namespaceName = entry.path().filename().string();
            namespaceName.erase(namespaceName.find_last_of('.'), std::string::npos);
            m_locales[locale][namespaceName] = localeJson;

//            for (const auto &key : localeJson.items()) {
//                if (!key.value().is_string()) {
//                    m_printError("The value of key '" + key.key() + "' in file '" + entry.path().string() + "is not a"
//                                                                                                            " string.");
//                    return false;
//                }
//                m_locales[locale][entry.path().filename().string()] = key;
//            }
        }
        return true;
    }
} // i18n