#include "pch.h"
#include <LoggerAPI.h>
#include <I18nAPI.h>

// clang-format off
const I18N::LangData defaultLangDataTest_IdToTrans = {
    {"en", {
        {"a.b.c.d.text1", "text"},
        {"a.b.c.d.text2", "foo"},
        {"a.b.c.foo", "bar{}"},
        {"ll.loading.plugins", "Loading plugins..."},
    }},
    {"en_GB", {
        {"a.b.c.d.text1", "text(en_GB)"},
    }},
    {"zh_CN", {
        {"a.b.c.d.text1", "文本"},
        {"a.b.c.d.text2", "foo{}"},
        {"a.b.c.foo", "bar{}"},
        {"ll.loading.plugins", "加载插件..."},
    }},
};
const I18N::LangData defaultLangDataTest_SrcToTrans = {
    {"en", {
        {"text", "text"},
        {"Loading plugins...", "Loading plugins..."},
    }},
    {"en_GB", {
        {"text", "text(en_GB)"},
    }},
    {"zh_CN", {
        {"text", "文本"},
        {"Loading plugins...", "加载插件..."},
    }},
};
// clang-format on

void RunI18NTest() {
    logger.info("Running I18N Test...");
    logger.debug("System Default Locale Name: {}", GetSystemLocaleName());
    {
        logger.info("I18N Test: SimpleI18N + IdToTrans");
        auto i18n = Translation::load("plugins/LLUnitTest/I18nTest/simplei18n_lang1.json", 
                                      I18N::Pattern::IdToTrans, "zh_CN", defaultLangDataTest_IdToTrans);
        // Test default language
        RES_EQ(tr("a.b.c.d.text1"), "文本");
        // Test get
        RES_EQ(i18n->get("a.b.c.d.text1", "en_GB"), "text(en_GB)");
        // Test auto fall back
        RES_EQ(trl("en_GB", "ll.loading.plugins"), "Loading plugins...");
        // Test format
        RES_EQ(tr("a.b.c.foo", "Arg1"), "barArg1");
        // Test whether it will format when failed to get
        RES_EQ(tr("not.found", "awa"), "not.found");
    }
    {
        logger.info("I18N Test: SimpleI18N + SrcToTrans");
        auto i18n = Translation::load("plugins/LLUnitTest/I18nTest/simplei18n_lang2.json",
                                      I18N::Pattern::SrcToTrans, "en_US", defaultLangDataTest_SrcToTrans);
        // Test default language
        RES_EQ(tr("text"), "text");
        // Test get
        RES_EQ(i18n->get("text", "en_GB"), "text(en_GB)");
        // Test auto fall back
        RES_EQ(trl("zh_TW", "Loading plugins..."), "加载插件...");
        // Test if failed to get
        RES_EQ(tr("Failed to get"), "Failed to get");
    }
    {
        logger.info("I18N Test: HeavyI18N + IdToTrans");
        auto i18n = Translation::load("plugins/LLUnitTest/I18nTest/LangPack1/",
                                      I18N::Pattern::IdToTrans, "en_US", defaultLangDataTest_IdToTrans);
        // Test default language
        RES_EQ(tr("a.b.c.d.text1"), "text");
        // Test get
        RES_EQ(i18n->get("a.b.c.d.text1", "en_GB"), "text(en_GB)");
        // Test auto fall back
        RES_EQ(trl("en_GB", "ll.loading.plugins"), "Loading plugins...");
        // Test format
        RES_EQ(tr("a.b.c.foo", "Arg1"), "barArg1");
        // Test whether it will format when failed to get
        RES_EQ(tr("not.found", "awa"), "not.found");
    }
    {
        logger.info("I18N Test: HeavyI18N + NestedIdToTrans");
        auto i18n = Translation::load("plugins/LLUnitTest/I18nTest/LangPack2/",
                                      I18N::Pattern::NestedIdToTrans, "en_US", defaultLangDataTest_IdToTrans);
        // Test default language
        RES_EQ(tr("a.b.c.d.text1"), "text");
        // Test get
        RES_EQ(i18n->get("a.b.c.d.text1", "en_GB"), "text(en_GB)");
        // Test auto fall back
        RES_EQ(trl("en_GB", "ll.loading.plugins"), "Loading plugins...");
        // Test format
        RES_EQ(tr("a.b.c.foo", "Arg1"), "barArg1");
        // Test whether it will format when failed to get
        RES_EQ(tr("not.found", "awa"), "not.found");
    }
    logger.info("Done.");
}