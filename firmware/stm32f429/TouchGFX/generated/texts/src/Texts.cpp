/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/Texts.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/TypedText.hpp>
#include <texts/TypedTextDatabase.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/TextProvider.hpp>

touchgfx::Font::StringWidthFunctionPointer touchgfx::Font::getStringWidthFunction = &touchgfx::Font::getStringWidthLTR;
touchgfx::LCD::DrawStringFunctionPointer touchgfx::LCD::drawStringFunction = &touchgfx::LCD::drawStringLTR;
touchgfx::TextProvider::UnicodeConverterInitFunctionPointer touchgfx::TextProvider::unicodeConverterInitFunction = static_cast<touchgfx::TextProvider::UnicodeConverterInitFunctionPointer>(0);
touchgfx::TextProvider::UnicodeConverterFunctionPointer touchgfx::TextProvider::unicodeConverterFunction = static_cast<touchgfx::TextProvider::UnicodeConverterFunctionPointer>(0);

//Default typed text database
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
    0x53, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x20, 0x69, 0x6e, 0x69, 0x74, 0x69, 0x61, 0x74, 0x69, 0x6e, 0x67, 0x2e, 0x2e, 0x2e, 0x0, // @0 "System initiating..."
    0x4e, 0x65, 0x77, 0x20, 0x54, 0x65, 0x78, 0x74, 0x0, // @21 "New Text"
    0x2, 0x0, // @30 "<>"
    0x43, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x0, // @32 "Control"
    0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x0, // @40 "Status"
    0x54, 0x65, 0x6d, 0x70, 0x3a, 0x20, 0x0, // @47 "Temp: "
    0x41, 0x6d, 0x62, 0x69, 0x3a, 0x0, // @54 "Ambi:"
    0x43, 0x6c, 0x65, 0x61, 0x72, 0x0, // @60 "Clear"
    0x48, 0x75, 0x6d, 0x69, 0x3a, 0x0, // @66 "Humi:"
    0x41, 0x75, 0x74, 0x6f, 0x0, // @72 "Auto"
    0x2, 0x25, 0x0, // @77 "<>%"
    0x4c, 0x6f, 0x67, 0x0, // @80 "Log"
    0x2, 0x43, 0x0, // @84 "<>C"
    0x36, 0x30, 0x0, // @87 "60"
    0x47, 0x0, // @90 "G"
    0x42, 0x0, // @92 "B"
    0x56, 0x0, // @94 "V"
    0x52, 0x0 // @96 "R"
};
extern uint32_t const indicesGb[];

//array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

//Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] =
{
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            //dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            //compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}

