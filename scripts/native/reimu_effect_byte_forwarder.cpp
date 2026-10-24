#include "characters/ReimuActionInitialization.hpp"
namespace th105 {
struct EffectSinkByteCall {
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual void *emit_effect(int,float,float,unsigned char,int,void *);
};
extern EffectSinkByteCall *g_effect_sink;
void ReimuFinalizationView::emit_effect(int code,float x,float y,unsigned char direction,int trailing)
{
 g_effect_sink->emit_effect(code,x,y,direction,trailing,this);
}
}
