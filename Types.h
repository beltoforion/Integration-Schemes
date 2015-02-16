#ifndef _TYPES_H
#define _TYPES_H

#include <stdexcept>
#include <vector>


namespace gfx
{

  //----------------------------------------------------------------------
  class Color
  {
  public:
      
    typedef std::vector<Color> vec_type;

    Color(int r = 0, int g = 0, int b = 0);
    static const Color& FromPalette(std::size_t idx);
 
    int r,g,b;

  private:

    class Palette
    {
    public:

      Palette()
      {
      m_vColors.push_back( Color(179, 178, 86) );
      m_vColors.push_back( Color(131, 255,   0) );
      m_vColors.push_back( Color(255, 194,   0) );
      m_vColors.push_back( Color(255,   0,   0) );
      m_vColors.push_back( Color(255,   0, 162) );
      m_vColors.push_back( Color(152,   0, 255) );
      m_vColors.push_back( Color(  0,  67, 255) );
      m_vColors.push_back( Color(0, 245, 255) );
      m_vColors.push_back( Color(0, 255,76) );
      m_vColors.push_back( Color(179, 134, 86) );

      m_vColors.push_back( Color(  0,  64,  64) );
      m_vColors.push_back( Color(133, 147, 142) );
      m_vColors.push_back( Color(128,   0,  64) );
      m_vColors.push_back( Color(255,   0,   0) );
      m_vColors.push_back( Color(  0,   0,   0) );
      }

      vec_type m_vColors;
    } static s_Palette;
  };
}

#endif