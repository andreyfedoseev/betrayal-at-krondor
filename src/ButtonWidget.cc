/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright (C) 2005-2007  Guido de Jong <guidoj@users.sf.net>
 */

#include "ButtonWidget.h"
#include "MediaToolkit.h"
#include "MousePointerManager.h"

ButtonWidget::ButtonWidget(const Rectangle &r, const int a)
: ActiveWidget(r, a)
, enabled(true)
, pressed(false)
{
}

ButtonWidget::~ButtonWidget()
{
}

int
ButtonWidget::GetAction() const
{
  return action;
}

void
ButtonWidget::SetEnabled(const bool toggle)
{
  enabled = toggle;
}

bool
ButtonWidget::IsEnabled() const
{
  return enabled;
}

void
ButtonWidget::SetPressed(const bool toggle)
{
  pressed = toggle;
}

bool
ButtonWidget::IsPressed() const
{
  return pressed;
}

void
ButtonWidget::Focus()
{
  MediaToolkit::GetInstance()->GetVideo()->SetPointerPosition(rect.GetXPos() + rect.GetWidth() / 2, rect.GetYPos() + rect.GetHeight() / 2);
}

void
ButtonWidget::GenerateActionEvent(const int a)
{
  ActionEvent ae(a);
  for (std::list<ActionEventListener *>::iterator it = actionListeners.begin(); it != actionListeners.end(); ++it) {
    (*it)->ActionPerformed(ae);
  }
}
