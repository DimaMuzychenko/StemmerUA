#pragma once

#include <string>
#include <vector>

const std::wstring VALID_MID_WORD_MARKS = L"\'-";

const wchar_t EMPTY_END = '\0';

const std::vector<std::wstring> ADVERB_ENDINGS = {
	L"ши",
	L"вши",
	L"учи",
	L"ючи",
	L"ачи",
	L"ячи"
};

const std::vector<std::wstring> REFLEXIVE_VERB_ENDINGS = {
	L"сь",
	L"ся"
};

const std::vector<std::wstring> ADJECTIVE_ENDINGS = {
	L"ий",
	L"ого",
	L"ому",
	L"им",
	L"а",
	L"ої",
	L"ій",
	L"ою",
	L"ім",
	L"я",
	L"е",
	L"є",
	L"их",
	L"ими",
	L"іх",
	L"їм",
	L"іми"
};

const std::vector<std::wstring> PARTICIPLE_SUFIXES = {
	L"уч",
	L"юч",
	L"ач",
	L"яч",
	L"л",
	L"н",
	L"ен",
	L"єн",
	L"т"
};

const std::vector<std::wstring> VERB_ENDINGS = {
	L"ти",
	L"у",
	L"ю",
	L"емо",
	L"ємо",
	L"имо",
	L"їмо",
	L"еш",
	L"єш",
	L"ете",
	L"єте",
	L"иш",
	L"їш",
	L"ите",
	L"їте",
	L"е",
	L"є",
	L"уть",
	L"ють",
	L"ить",
	L"їть",
	L"ать",
	L"ять",
	L"му",
	L"меш",
	L"ме",
	L"мемо",
	L"мем",
	L"мете",
	L"муть",
	L"ви",
	L"ла",
	L"ло",
	L"ли"
};

const std::vector<std::wstring> NOUN_ENDINGS = {
	L"а",
	L"я",
	L"и",
	L"і",
	L"ї",
	L"у",
	L"ю",
	L"ою",
	L"ею",
	L"єю",
	L"е",
	L"є",
	L"ів",
	L"ей",
	L"ам",
	L"ям",
	L"ами",
	L"ями",
	L"ах",
	L"ях",
	L"о",
	L"ові",
	L"еві",
	L"єві",
	L"ом",
	L"им",
	L"ем",
	L"єм",
	L"ів",
	L"їв",
	L"ьми",
	L"има",
	L"яти",
	L"ати",
	L"ені",
	L"аті",
	L"яті",
	L"енем",
	L"ята",
	L"ата",
	L"ена",
	L"ен",
	L"енам",
	L"атам",
	L"ятам",
	L"ятами",
	L"атами",
	L"енами",
	L"ятах",
	L"атах",
	L"ми"
};