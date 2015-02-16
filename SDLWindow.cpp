#include "SDLWindow.hpp"

//--- Standard includes -------------------------------------------------
#include <stdexcept>


//-----------------------------------------------------------------------
SDLWindow::SDLWindow(int width, int height)
  :m_width(0)
  ,m_height(0)
  ,m_xcenter(0)
  ,m_ycenter(0)
  ,m_pScreen(NULL)
  ,m_bRunning(true)
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw std::runtime_error(SDL_GetError());

  atexit(SDL_Quit);

  m_pScreen = SDL_SetVideoMode(width, height, 16, SDL_HWSURFACE);
  if (!m_pScreen)
    throw std::runtime_error(SDL_GetError());

  m_width = width;
  m_height = height;
  m_xcenter = width >> 1;
  m_ycenter = height >> 1;
}

//-----------------------------------------------------------------------
void SDLWindow::MainLoop()
{
  while (m_bRunning)
  {
    Render();
    PollMessages();
  }
}

//-----------------------------------------------------------------------
SDL_Surface *SDLWindow::Surface()
{
    return m_pScreen;
}

//-----------------------------------------------------------------------
int SDLWindow::GetWidth() const
{
    return m_width;
}

//-----------------------------------------------------------------------
int SDLWindow::GetHeight() const
{
    return m_height;
}

//-----------------------------------------------------------------------
void SDLWindow::ExitMainLoop()
{
  m_bRunning = false;
}

