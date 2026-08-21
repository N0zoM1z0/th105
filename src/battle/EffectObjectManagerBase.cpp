#include "characters/TObjectManagerBase.hpp"


class CSelectObject;
class WeatherEffectObject;
class EffectObject;
class SystemEffectObject;
class EffectObjectBase;
class SystemEffectObjectBase;


template TObjectManagerBase<CSelectObject, EffectObjectBase>::TObjectManagerBase();
template TObjectManagerBase<CSelectObject, EffectObjectBase>::~TObjectManagerBase();
template TObjectManagerBase<WeatherEffectObject, EffectObjectBase>::TObjectManagerBase();
template TObjectManagerBase<WeatherEffectObject, EffectObjectBase>::~TObjectManagerBase();
template TObjectManagerBase<EffectObject, EffectObjectBase>::TObjectManagerBase();
template TObjectManagerBase<EffectObject, EffectObjectBase>::~TObjectManagerBase();
template TObjectManagerBase<SystemEffectObject, SystemEffectObjectBase>::TObjectManagerBase();
template TObjectManagerBase<SystemEffectObject, SystemEffectObjectBase>::~TObjectManagerBase();
