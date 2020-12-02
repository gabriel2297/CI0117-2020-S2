#include "../include/enums.h"

std::string getStrategyAsString(Strategy strategy)
{
    switch(strategy)
    {
        case random_strategy:
            return "random_strategy";
        case less_coins:
            return "less_coins";
        case more_coins:
            return "more_coins";
        case attacker:
            return "attacker";
        default:
            return "";
    }
}

std::string getElementAsString(Element element)
{
    switch(element)
    {
        case Coin:
            return "Coin";
        case Hole:
            return "Hole";
        case LittleGoomba:
            return "Little Goomba";
        case KoopaTroopa:
            return "Koopa Troopa";
        default:
            return "None";
    }
}

std::string getActionAsString(Action action)
{
    switch(action)
    {
        case no_jump:
            return "Mario didn't jump.";
        case jump_and_hit:
            return "Mario jumped and grabbed a coin!";
        case jump_and_kill:
            return "Mario jumped and killed the ";
        case jump_and_move:
            return "Mario jumped and moved to the next position";
        default:
            return "Mario is walking.";
    }
}

Strategy getStrategyByNumber(int num)
{
    switch(num)
    {
        case 1:
            return random_strategy;
        case 2:
            return less_coins;
        case 3: 
            return more_coins;
        case 4:
            return attacker;
        default:
            return none;
    }
}

Strategy getStrategyByLetter(char* letter)
{
    switch(*letter)
    {
        case 'R':
            return random_strategy;
        case 'L':
            return less_coins;
        case 'M': 
            return more_coins;
        case 'A':
            return attacker;
        default:
            return none;
    }
}