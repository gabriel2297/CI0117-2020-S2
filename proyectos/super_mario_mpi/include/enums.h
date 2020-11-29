#ifndef ENUMS_H
#define ENUMS_H
#include <string>

enum Element
{
    None,
    Coin,
    Hole,
    LittleGoomba,
    KoopaTroopa,
    Flag
};
enum Action
{
    no_jump,
    jump_and_hit,
    jump_and_kill,
    jump_and_move
};
enum Strategy
{
    random_strategy,
    less_coins,
    more_coins,
    attacker,
    none
};

std::string getStrategyAsString(Strategy strategy);
std::string getElementAsString(Element element);
std::string getActionAsString(Action action);
Strategy getStrategyByNumber(int num);
Strategy getStrategyByLetter(char* letter);



#endif
