#include "settings.h"

namespace settings {
// Game
  float CellSize = 100.0f;
  float HeroesSize = 100.0f;
  float BuffSize = 50.0f;
  int BuffQuantity = 300;

// Debug
  bool IsDebug = false;
  bool DDrawCoordsGrid = false && IsDebug;
  bool DAlwaysDrawBuffs = true && IsDebug;
  bool DDrawPlayerOrigin = true && IsDebug;
  bool DDrawBotTurn = false;
} // namespace
