#ifndef IWINDOW_H
#define IWINDOW_H

//--- SDL includes -----------------------------------------------------------
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>


class SDLWindow
{
public:

  SDLWindow(int width, int height);

  void MainLoop();
  void ExitMainLoop();
  int GetWidth() const;
  int GetHeight() const;
  virtual void Render() = 0;
  virtual void PollMessages() = 0;

protected:

  SDL_Surface *Surface();

private:

  int m_width;
  int m_height;
  int m_xcenter;
  int m_ycenter;
  SDL_Surface *m_pScreen;
  volatile bool m_bRunning;
};

#endif