#include "../battle/EffectSprite.hpp"
#include "Title.hpp"
namespace th105 {
class GuideLifetimeSprite94 : public IColor {
public:
 GuideLifetimeSprite94() {}
 virtual ~GuideLifetimeSprite94() {}
 virtual void set_color(unsigned);
 virtual void set_vertex_colors(const unsigned *);
 virtual void multiply_color(unsigned);
 virtual void set_texture_options(unsigned,int,int,unsigned,unsigned,int,int);
 virtual void set_texture(unsigned,int,int,int,int);
 virtual void slot_18();
 virtual void render(float,float);
 SpriteVertex28 vertices_08[4];
 float width_78,height_7c,extension_80[5];
};

struct GuideLifetimeView {
 bool visible;
 unsigned texture_04;
 GuideLifetimeSprite94 sprite_08;
 float scroll_9c,wrap_width_a0;
 unsigned char alpha_a4;
 GuideLifetimeView();
 ~GuideLifetimeView();
};
typedef char GuideSize[sizeof(GuideLifetimeView)==0xa8?1:-1];
GuideLifetimeView::GuideLifetimeView()
{
 texture_04=0;
 visible=false;
}
GuideLifetimeView::~GuideLifetimeView()
{
 if(texture_04!=0)
  g_title_resource_manager.release_title_resource_handle(texture_04);
}
}
