// Copyright 2021 The VGC Developers
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

#include <vgc/ui/action.h>

#include <vgc/ui/menu.h>

namespace vgc::ui {

Action::Action() {
}

Action::Action(const Shortcut& shortcut)
    : shortcut_(shortcut) {
}

Action::Action(const std::string& text)
    : text_(text) {
}

Action::Action(const std::string& text, const Shortcut& shortcut)
    : text_(text)
    , shortcut_(shortcut) {
}

ActionPtr Action::create() {
    return ActionPtr(new Action());
}

ActionPtr Action::create(const Shortcut& shortcut) {
    return ActionPtr(new Action(shortcut));
}

ActionPtr Action::create(const std::string& text) {
    return ActionPtr(new Action(text));
}

ActionPtr Action::create(const std::string& text, const Shortcut& shortcut) {
    return ActionPtr(new Action(text, shortcut));
}

bool Action::trigger(Widget* from) {
    if (!isEnabled_) {
        return false;
    }
    triggered().emit(from);
    return true;
}

} // namespace vgc::ui
