#include <stdio.h>

typedef enum
{
  RED,
  GREEN,
  YELLOW
} TrafficLightState;

TrafficLightState nextState(TrafficLightState current);
void printState(TrafficLightState state);
int getDuration(TrafficLightState state);
TrafficLightState oppositeState(TrafficLightState state);

int main()
{
  TrafficLightState state = RED;
  int ticks = getDuration(state); // скільки тіків поточний стан

  for (int i = 0; i < 20; i++) // 20 ітерацій для тесту
  {
    printState(state);

    ticks--;
    if (ticks == 0)
    {
      state = nextState(state);
      ticks = getDuration(state);
    }
  }

  return 0;
}

TrafficLightState nextState(TrafficLightState current)
{
  switch (current)
  {
  case RED:
    return GREEN;
  case GREEN:
    return YELLOW;
  case YELLOW:
    return RED;
  default:
    return RED;
  }
}

int getDuration(TrafficLightState state)
{
  switch (state)
  {
  case RED:
    return 3;
  case GREEN:
    return 3;
  case YELLOW:
    return 1;
  default:
    return 1;
  }
}

const char* stateToString(TrafficLightState state)
{
    switch (state) {
        case RED:    return "RED";
        case GREEN:  return "GREEN";
        case YELLOW: return "YELLOW";
        default:     return "UNKNOWN";
    }
}

void printState(TrafficLightState state)
{
    TrafficLightState state2 = oppositeState(state);
    printf("Світлофор 1: %s | Світлофор 2: %s\n",
           stateToString(state), stateToString(state2));
}

TrafficLightState oppositeState(TrafficLightState state)
{
  switch (state)
  {
  case RED:
    return GREEN;
  case GREEN:
    return RED;
  case YELLOW:
    return YELLOW; // обидва жовті одночасно
  default:
    return RED;
  }
}