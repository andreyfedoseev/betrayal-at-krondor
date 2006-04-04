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
 * Copyright (C) 2005-2006  Guido de Jong <guidoj@users.sf.net>
 */

#include <iomanip>
#include <sstream>

#include "AnimationResource.h"
#include "Exception.h"
#include "FontResource.h"
#include "GameApplication.h"
#include "MousePointerManager.h"
#include "MoviePlayer.h"
#include "MovieResource.h"
#include "PaletteResource.h"
#include "ResourceManager.h"
#include "ResourcePath.h"
#include "ScreenResource.h"
#include "SDL_Toolkit.h"
#include "TextArea.h"

GameApplication* GameApplication::instance = 0;

GameApplication::GameApplication()
: mediaToolkit(SDL_Toolkit::GetInstance())
, inputGrabbed(false)
, state(GS_INTRO)
, chapter(mediaToolkit)
, screenSaveCount(0)
{
  mediaToolkit->GetVideo()->SetScaling(2);
  mediaToolkit->GetVideo()->CreateScreen(VIDEO_WIDTH, VIDEO_HEIGHT);
  mediaToolkit->GetVideo()->Clear();

  PaletteResource pal;
  pal.Fill();
  pal.Activate(mediaToolkit->GetVideo(), 0, VIDEO_COLORS);
  FontResource fnt;
  ResourceManager::GetInstance()->Load(&fnt, "GAME.FNT");
  TextArea ta(240, 16, fnt);
  ta.SetText("xBaK: Betrayal at Krondor  A fan-made remake");
  ta.SetColor(15);
  ta.Draw(mediaToolkit->GetVideo(), 16, 16);
  mediaToolkit->GetVideo()->Refresh();
  mediaToolkit->GetClock()->Delay(1000);
  mediaToolkit->AddKeyboardListener(this);
  mediaToolkit->AddMouseButtonListener(this);

  MousePointerManager::GetInstance()->AddPointer("POINTER.BMX");
  MousePointerManager::GetInstance()->AddPointer("POINTERG.BMX");
  MousePointerManager::GetInstance()->Register(mediaToolkit);
}

GameApplication::~GameApplication()
{
  mediaToolkit->RemoveKeyboardListener(this);
  MousePointerManager::CleanUp();
  delete mediaToolkit;
  ResourceManager::CleanUp();
  ResourcePath::CleanUp();
}

GameApplication*
GameApplication::GetInstance()
{
  if (!instance) {
    instance = new GameApplication();
  }
  return instance;
}

void
GameApplication::CleanUp()
{
  if (instance) {
    delete instance;
    instance = 0;
  }
}

void
GameApplication::PlayIntro()
{
  try {
    AnimationResource anim;
    ResourceManager::GetInstance()->Load(&anim, "INTRO.ADS");
    MovieResource ttm;
    ResourceManager::GetInstance()->Load(&ttm, anim.GetAnimationData(1).resource);
    MoviePlayer moviePlayer(mediaToolkit);
    moviePlayer.Play(&ttm.GetMovieTags(), true);
  } catch (Exception &e) {
    e.Print("GameApplication::Intro");
  }
}

UserActionType
GameApplication::Options(const bool firstTime)
{
  try {
    mediaToolkit->GetVideo()->SetPointerPosition(0, 0);
    OptionsDialog options(mediaToolkit, firstTime);
    return options.GetUserAction();
  } catch (Exception &e) {
    e.Print("GameApplication::Run");
    return UA_QUIT;
  }
}

void
GameApplication::Run()
{
  try {
    bool firstTime = true;
    while (true) {
      switch (state) {
        case GS_CHAPTER:
          chapter.PlayIntro();
          chapter.PlayScene(1);
          state = GS_WORLD;
          break;
        case GS_COMBAT:
          state = GS_WORLD;
          break;
        case GS_INTRO:
          PlayIntro();
          state = GS_OPTIONS;
          break;
        case GS_OPTIONS:
          switch (Options(firstTime)) {
            case UA_CANCEL:
              break;
            case UA_NEW_GAME:
              state = GS_CHAPTER;
              chapter.SetCurrent(1);
              break;
            case UA_QUIT:
              return;
              break;
            case UA_RESTORE:
              break;
            case UA_SAVE:
              break;
            case UA_UNKNOWN:
              break;
          }
          firstTime = false;
          break;
        case GS_WORLD:
          return;
          break;
      }
    }
  } catch (Exception &e) {
    e.Print("GameApplication::Run");
  }
}

void
GameApplication::KeyPressed(const KeyboardEvent& kbe)
{
  switch (kbe.GetKey()){
    case KEY_F11:
      {
        screenSaveCount++;
        std::stringstream filenameStream;
        filenameStream << "xbak_" << std::setw(3) << std::setfill('0') << screenSaveCount << ".bmp";
        mediaToolkit->GetVideo()->SaveScreenShot(filenameStream.str());
      }
      break;
    case KEY_F12:
      inputGrabbed = !inputGrabbed;
      mediaToolkit->GetVideo()->GrabInput(inputGrabbed);
      break;
    default:
      break;
  }
}

void
GameApplication::KeyReleased(const KeyboardEvent& kbe)
{
  switch (kbe.GetKey()){
    default:
      break;
  }
}

void
GameApplication::MouseButtonPressed(const MouseButtonEvent& mbe)
{
  switch (mbe.GetButton()){
    case MB_LEFT:
      if (!inputGrabbed) {
        inputGrabbed = true;
        mediaToolkit->GetVideo()->GrabInput(true);
      }
      break;
    case MB_RIGHT:
      if (inputGrabbed) {
        inputGrabbed = false;
        mediaToolkit->GetVideo()->GrabInput(false);
      }
      break;
    default:
      break;
  }
}

void
GameApplication::MouseButtonReleased(const MouseButtonEvent& mbe)
{
  switch (mbe.GetButton()){
    default:
      break;
  }
}
