#include "EffectManager.hpp"


template <typename ObjectType>
CEffectManager<ObjectType>::CEffectManager()
{
}


template <typename ObjectType>
CEffectManager<ObjectType>::~CEffectManager()
{
}


#define TH105_INSTANTIATE_EFFECT_MANAGER_LIFETIME(ObjectType) \
    template CEffectManager<ObjectType>::CEffectManager(); \
    template CEffectManager<ObjectType>::~CEffectManager()

TH105_INSTANTIATE_EFFECT_MANAGER_LIFETIME(CSelectObject);
TH105_INSTANTIATE_EFFECT_MANAGER_LIFETIME(WeatherEffectObject);
TH105_INSTANTIATE_EFFECT_MANAGER_LIFETIME(EffectObject);
TH105_INSTANTIATE_EFFECT_MANAGER_LIFETIME(InfoEffectObject);

#undef TH105_INSTANTIATE_EFFECT_MANAGER_LIFETIME
