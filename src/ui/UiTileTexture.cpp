#include "Tile.hpp"
void CTile::set_texture(unsigned handle,int x,int y,int width,int height)
{
 set_texture_options(handle,x,y,width,height,0,0);
}
