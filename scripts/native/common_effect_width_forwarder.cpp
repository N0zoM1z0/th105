#include "battle/CommonFighterActionInitialization.hpp"
namespace th105 {
struct CommonEffectSinkWidthView {
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual void *emit_effect(short,float,float,unsigned char,int,void *);
};
extern CommonEffectSinkWidthView *g_effect_sink;
void CommonActionEntryView::emit_effect(short code,float x,float y,unsigned char direction,int trailing)
{g_effect_sink->emit_effect(code,x,y,direction,trailing,this);}
}
