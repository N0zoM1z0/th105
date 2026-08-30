namespace th105 {
struct TileVertex28Copy { float x,y,z,rhw; unsigned int color; float u,v; };
class TileSpriteBaseCopy {
public:
    virtual ~TileSpriteBaseCopy() {}
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    unsigned int value_04;
    TileVertex28Copy vertices_08[4];
    float texture_width_78;
    float texture_height_7c;
};
class CTileCopyProbe : public TileSpriteBaseCopy {
public:
    virtual ~CTileCopyProbe() {}
    float e80,e84,e88,e8c,e90,e94,e98,e9c,ea0;
};
typedef char TileSpriteBaseCopy_size[sizeof(TileSpriteBaseCopy)==0x80?1:-1];
typedef char CTileCopyProbe_size[sizeof(CTileCopyProbe)==0xa4?1:-1];
CTileCopyProbe make_ctile_copy(const CTileCopyProbe &source) { return CTileCopyProbe(source); }
}
