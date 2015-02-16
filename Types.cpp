#include "Types.h"


namespace gfx
{
  //---------------------------------------------------------------------
  Color::Palette Color::s_Palette;

  //---------------------------------------------------------------------
  Color::Color(int a_r, int a_g, int a_b)
    :r(a_r)
    ,g(a_g)
    ,b(a_b)
  {}

  //---------------------------------------------------------------------
  const Color& Color::FromPalette(std::size_t idx) 
  {
    return s_Palette.m_vColors.at(idx);
  }
}