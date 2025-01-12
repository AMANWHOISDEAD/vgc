// Copyright 2022 The VGC Developers
// See the COPYRIGHT file at the top-level directory of this distribution
// and at https://github.com/vgc/vgc/blob/master/COPYRIGHT
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <vgc/ui/shortcut.h>

#include <vgc/core/os.h>

namespace vgc::ui {

VGC_DEFINE_ENUM(
    ShortcutContext,
    (Application, "Application"),
    (Window, "Window"),
    (Widget, "Widget"))

namespace {

void appendString(std::string& res, std::string& separator, std::string_view str) {
    res += separator;
    res += str;
#ifndef VGC_CORE_OS_MACOS
    separator = "+";
#else
    separator = " ";
#endif
}

} // namespace

namespace detail {

std::string toString(const Shortcut& shortcut) {
    Key key = shortcut.key();
    if (key == Key::None) {
        return "";
    }
    ModifierKeys modifiers = shortcut.modifiers();
    std::string res;
    std::string separator = "";
    // Note:
    // - on Windows, we want the order Ctrl + Alt + Shift + Meta
    // - on macOS, on Windows, we want the order Control + Alt + Shift + Command
#ifndef VGC_CORE_OS_MACOS
    if (modifiers.has(ModifierKey::Ctrl)) {
        appendString(res, separator, "Ctrl");
    }
    if (modifiers.has(ModifierKey::Alt)) {
        appendString(res, separator, "Alt");
    }
    if (modifiers.has(ModifierKey::Shift)) {
        appendString(res, separator, "Shift");
    }
    if (modifiers.has(ModifierKey::Meta)) {
        appendString(res, separator, "Meta");
    }
#else
    if (modifiers.has(ModifierKey::Meta)) {
        appendString(res, separator, "⌃"); // U+2303 Control / Ctrl
    }
    if (modifiers.has(ModifierKey::Alt)) {
        appendString(res, separator, "⌥"); // U+2325 Option / Alt
    }
    if (modifiers.has(ModifierKey::Shift)) {
        appendString(res, separator, "⇧"); // U+21E7 Shift
    }
    if (modifiers.has(ModifierKey::Ctrl)) {
        appendString(res, separator, "⌘"); // U+2318 Command / Cmd
    }
#endif
    appendString(res, separator, core::Enum::prettyName(key));
    return res;
}

} // namespace detail

} // namespace vgc::ui
