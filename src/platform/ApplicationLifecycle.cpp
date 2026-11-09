// Preserve the real static object's constant-receiver construction context.
#include "platform/ApplicationInitialization.cpp"
#include "platform/ApplicationStartupOptions.cpp"
#include "platform/BattleThreadHandleRuntime.cpp"
#include "engine/CriticalSectionWrapper.cpp"

namespace th105 {
ApplicationState g_application_state;
}
