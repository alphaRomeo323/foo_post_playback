#include "stdafx.h"
#include "Configuration.h"

// GUID is 64D2E619-EE22-4816-B9FA-B1047895B30F
static constexpr GUID guid_advconfig_branch = { 0x64D2E619, 0xEE22, 0x4816, { 0xB9, 0xFA, 0xB1, 0x04, 0x78, 0x95, 0xB3, 0x0F } };
// GUID is 903595CA-1E65-4602-AFFB-590BC543B36F
static constexpr GUID guid_cfg_url = { 0x903595CA, 0x1E65, 0x4602, { 0xAF, 0xFB, 0x59, 0x0B, 0xC5, 0x43, 0xB3, 0x6F } };

enum {
	order_url
};

advconfig_branch_factory g_advconfigBranch("POST Playback", guid_advconfig_branch, advconfig_branch::guid_branch_tools, 0);
	advconfig_string_factory cfg_url("URL to POST", "foo_testplugin.url", guid_cfg_url, guid_advconfig_branch, order_url, "");