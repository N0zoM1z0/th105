#ifndef TH105_MARISA_OBJECT_ACTION_ENTRY_HPP
#define TH105_MARISA_OBJECT_ACTION_ENTRY_HPP
namespace th105 {
// Pointer-only primary call view. Never construct or embed this receiver.
class MarisaObjectEntryView {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual int select_sequence(short sequence);
 virtual void slot10(); virtual void slot14(); virtual void slot18();
 virtual int select_frame(short frame);
 virtual void slot20(); virtual void slot24(); virtual void slot28();
 virtual void slot2c(); virtual void slot30(); virtual void slot34(); virtual void slot38();
 virtual void initialize_action_entry();
 void continue_action_980();
 void replace_secondary(int key,float half_width,int divisions,int bands,int blend);
 void replace_auxiliary(short resource);
 void *spawn_parented(int action,float x,float y,unsigned char facing,int layer,const unsigned *words,int count);
 void *spawn_unparented(int action,float x,float y,unsigned char facing,int layer,const unsigned *words,int count);
 int spawn_owned(int action,float x,float y,unsigned char facing,int layer,const unsigned *words,int count);
};
class MarisaEntryMotionView { public: void set_components(float angle,float magnitude); };
int __cdecl selector_random_roll(int limit);
unsigned __cdecl mt19937_next_u32();
double __cdecl lookup_orientation_sine_quantized_abs(float phase);
extern int g_match_identifier;
}
#endif
