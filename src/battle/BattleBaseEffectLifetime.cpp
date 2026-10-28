#include "audio/DirectSound.hpp"
#include "engine/D3DBackendListenerRuntime.hpp"

namespace th105 {

// D3DX effect COM prefix used by the two device-reset callbacks.
// Slot order is corroborated by the installed MinGW d3dx9effect.h; only
// OnLostDevice/OnResetDevice are invoked here. No full object layout is claimed.
typedef const char *EffectHandle;
struct D3DXEFFECT_DESC;
struct D3DXPARAMETER_DESC;
struct D3DXTECHNIQUE_DESC;
struct D3DXPASS_DESC;
struct D3DXFUNCTION_DESC;
struct D3DXVECTOR4;
struct D3DXMATRIX;
struct IDirect3DBaseTexture9;
struct IDirect3DPixelShader9;
struct IDirect3DVertexShader9;
struct ID3DXEffectPool;
struct IDirect3DDevice9;
struct EffectResetInterface : UnknownInterface {
    virtual HResult __stdcall GetDesc(D3DXEFFECT_DESC* desc) = 0;
    virtual HResult __stdcall GetParameterDesc(EffectHandle parameter, D3DXPARAMETER_DESC* desc) = 0;
    virtual HResult __stdcall GetTechniqueDesc(EffectHandle technique, D3DXTECHNIQUE_DESC* desc) = 0;
    virtual HResult __stdcall GetPassDesc(EffectHandle pass, D3DXPASS_DESC* desc) = 0;
    virtual HResult __stdcall GetFunctionDesc(EffectHandle shader, D3DXFUNCTION_DESC* desc) = 0;
    virtual EffectHandle __stdcall GetParameter(EffectHandle parameter, unsigned index) = 0;
    virtual EffectHandle __stdcall GetParameterByName(EffectHandle parameter, const char *name) = 0;
    virtual EffectHandle __stdcall GetParameterBySemantic(EffectHandle parameter, const char *semantic) = 0;
    virtual EffectHandle __stdcall GetParameterElement(EffectHandle parameter, unsigned index) = 0;
    virtual EffectHandle __stdcall GetTechnique(unsigned index) = 0;
    virtual EffectHandle __stdcall GetTechniqueByName(const char *name) = 0;
    virtual EffectHandle __stdcall GetPass(EffectHandle technique, unsigned index) = 0;
    virtual EffectHandle __stdcall GetPassByName(EffectHandle technique, const char *name) = 0;
    virtual EffectHandle __stdcall GetFunction(unsigned index) = 0;
    virtual EffectHandle __stdcall GetFunctionByName(const char *name) = 0;
    virtual EffectHandle __stdcall GetAnnotation(EffectHandle object, unsigned index) = 0;
    virtual EffectHandle __stdcall GetAnnotationByName(EffectHandle object, const char *name) = 0;
    virtual HResult __stdcall SetValue(EffectHandle parameter, const void *data, unsigned bytes) = 0;
    virtual HResult __stdcall GetValue(EffectHandle parameter, void *data, unsigned bytes) = 0;
    virtual HResult __stdcall SetBool(EffectHandle parameter, int b) = 0;
    virtual HResult __stdcall GetBool(EffectHandle parameter, int* b) = 0;
    virtual HResult __stdcall SetBoolArray(EffectHandle parameter, const int *b, unsigned count) = 0;
    virtual HResult __stdcall GetBoolArray(EffectHandle parameter, int* b, unsigned count) = 0;
    virtual HResult __stdcall SetInt(EffectHandle parameter, int n) = 0;
    virtual HResult __stdcall GetInt(EffectHandle parameter, int* n) = 0;
    virtual HResult __stdcall SetIntArray(EffectHandle parameter, const int *n, unsigned count) = 0;
    virtual HResult __stdcall GetIntArray(EffectHandle parameter, int* n, unsigned count) = 0;
    virtual HResult __stdcall SetFloat(EffectHandle parameter, float f) = 0;
    virtual HResult __stdcall GetFloat(EffectHandle parameter, float* f) = 0;
    virtual HResult __stdcall SetFloatArray(EffectHandle parameter, const float *f, unsigned count) = 0;
    virtual HResult __stdcall GetFloatArray(EffectHandle parameter, float* f, unsigned count) = 0;
    virtual HResult __stdcall SetVector(EffectHandle parameter, const D3DXVECTOR4 *vector) = 0;
    virtual HResult __stdcall GetVector(EffectHandle parameter, D3DXVECTOR4* vector) = 0;
    virtual HResult __stdcall SetVectorArray(EffectHandle parameter, const D3DXVECTOR4 *vector, unsigned count) = 0;
    virtual HResult __stdcall GetVectorArray(EffectHandle parameter, D3DXVECTOR4* vector, unsigned count) = 0;
    virtual HResult __stdcall SetMatrix(EffectHandle parameter, const D3DXMATRIX *matrix) = 0;
    virtual HResult __stdcall GetMatrix(EffectHandle parameter, D3DXMATRIX* matrix) = 0;
    virtual HResult __stdcall SetMatrixArray(EffectHandle parameter, const D3DXMATRIX *matrix, unsigned count) = 0;
    virtual HResult __stdcall GetMatrixArray(EffectHandle parameter, D3DXMATRIX* matrix, unsigned count) = 0;
    virtual HResult __stdcall SetMatrixPointerArray(EffectHandle parameter, const D3DXMATRIX **matrix, unsigned count) = 0;
    virtual HResult __stdcall GetMatrixPointerArray(EffectHandle parameter, D3DXMATRIX** matrix, unsigned count) = 0;
    virtual HResult __stdcall SetMatrixTranspose(EffectHandle parameter, const D3DXMATRIX *matrix) = 0;
    virtual HResult __stdcall GetMatrixTranspose(EffectHandle parameter, D3DXMATRIX* matrix) = 0;
    virtual HResult __stdcall SetMatrixTransposeArray(EffectHandle parameter, const D3DXMATRIX *matrix, unsigned count) = 0;
    virtual HResult __stdcall GetMatrixTransposeArray(EffectHandle parameter, D3DXMATRIX* matrix, unsigned count) = 0;
    virtual HResult __stdcall SetMatrixTransposePointerArray(EffectHandle parameter, const D3DXMATRIX **matrix, unsigned count) = 0;
    virtual HResult __stdcall GetMatrixTransposePointerArray(EffectHandle parameter, D3DXMATRIX** matrix, unsigned count) = 0;
    virtual HResult __stdcall SetString(EffectHandle parameter, const char *string) = 0;
    virtual HResult __stdcall GetString(EffectHandle parameter, const char **string) = 0;
    virtual HResult __stdcall SetTexture(EffectHandle parameter, struct IDirect3DBaseTexture9 *texture) = 0;
    virtual HResult __stdcall GetTexture(EffectHandle parameter, struct IDirect3DBaseTexture9 **texture) = 0;
    virtual HResult __stdcall GetPixelShader(EffectHandle parameter, struct IDirect3DPixelShader9 **shader) = 0;
    virtual HResult __stdcall GetVertexShader(EffectHandle parameter, struct IDirect3DVertexShader9 **shader) = 0;
    virtual HResult __stdcall SetArrayRange(EffectHandle parameter, unsigned start, unsigned end) = 0;
    virtual HResult __stdcall GetPool(ID3DXEffectPool **pool) = 0;
    virtual HResult __stdcall SetTechnique(EffectHandle technique) = 0;
    virtual EffectHandle __stdcall GetCurrentTechnique() = 0;
    virtual HResult __stdcall ValidateTechnique(EffectHandle technique) = 0;
    virtual HResult __stdcall FindNextValidTechnique(EffectHandle technique, EffectHandle* next_technique) = 0;
    virtual int __stdcall IsParameterUsed(EffectHandle parameter, EffectHandle technique) = 0;
    virtual HResult __stdcall Begin(unsigned *passes, ULong flags) = 0;
    virtual HResult __stdcall BeginPass(unsigned pass) = 0;
    virtual HResult __stdcall CommitChanges() = 0;
    virtual HResult __stdcall EndPass() = 0;
    virtual HResult __stdcall End() = 0;
    virtual HResult __stdcall GetDevice(struct IDirect3DDevice9 **device) = 0;
    virtual HResult __stdcall OnLostDevice() = 0;
    virtual HResult __stdcall OnResetDevice() = 0;
};


class BattleBaseEffectLifetimeView {
public:
    BattleBaseEffectLifetimeView();
    ~BattleBaseEffectLifetimeView();
    virtual void control_a();
    virtual void control_b();

    bool initialize(const void *data, unsigned size);
    void shutdown();

private:
    UnknownInterface *effect_04;
};

extern "C" void __stdcall remove_battle_base_effect(
    BattleBaseEffectLifetimeView *effect);

BattleBaseEffectLifetimeView::BattleBaseEffectLifetimeView()
    : effect_04(0)
{
}

BattleBaseEffectLifetimeView::~BattleBaseEffectLifetimeView()
{
    if (effect_04 != 0) {
        effect_04->release();
        effect_04 = 0;
    }
}

void BattleBaseEffectLifetimeView::control_a()
{
    if (effect_04 != 0)
        static_cast<EffectResetInterface *>(effect_04)->OnLostDevice();
}

void BattleBaseEffectLifetimeView::control_b()
{
    if (effect_04 != 0)
        static_cast<EffectResetInterface *>(effect_04)->OnResetDevice();
}

extern "C" long __stdcall D3DXCreateEffect(
    D3DDevice9 *device,
    const void *source_data,
    unsigned source_size,
    const void *defines,
    void *include_handler,
    unsigned flags,
    void *effect_pool,
    UnknownInterface **effect,
    void **errors);

bool BattleBaseEffectLifetimeView::initialize(const void *data, unsigned size)
{
    if (effect_04 != 0)
        return false;
    d3d_backend_listener_runtime()->register_reset_listener(
        reinterpret_cast<DeviceResetListener *>(this));
    return D3DXCreateEffect(
        g_d3d_backend.device_020, data, size, 0, 0, 0, 0, &effect_04, 0) == 0;
}

void BattleBaseEffectLifetimeView::shutdown()
{
    remove_battle_base_effect(this);
    if (effect_04 != 0) {
        effect_04->release();
        effect_04 = 0;
    }
}

} // namespace th105
