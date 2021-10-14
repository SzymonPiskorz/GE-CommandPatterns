#pragma once

#include <iostream>
#include "Brick.h"
#include <list>
#include "LegoBrickFactory.h"
#include "DrawImpl.h"
#include "ClayBrickFactory.h"
#include "WoodBrickFactory.h"
#include <stack>

class Command
{
public:

    ~Command(){};
    virtual void execute() = 0;

    virtual void add(){m_count++;};
    virtual void remove(){m_count--;};
    virtual int getCount(){return m_count;}

protected:
    Command(){};
    int m_count;
};

class MacroCommand : public Command
{
public:

    MacroCommand();
    virtual ~MacroCommand();

    virtual void  add(Command* command)
    {
        commands.push_back(command);
        command->add();
    }  

    virtual void excecute()
    {
        for(Command* command : commands)
        {
            command->execute();
        }
    }

    virtual void undo()
    {
        if(commands.size() > 0)
        {
            std::cout << "Undo" << std::endl;
            removedCommands.push(commands[commands.size()-1]);
            commands.pop_back();
            removedCommands.top()->remove();
        }
    }

    virtual void redo()
    {
        if (removedCommands.size() > 0 )
        {
             std::cout << "Redo" << std::endl;
            removedCommands.top()->add();
            commands.push_back(removedCommands.top());
            removedCommands.pop();
        }
    }

protected:
    std::vector<Command*> commands;
    std::stack<Command*> removedCommands;
};

class BuildLegoBrickCommand : public Command
{
protected:
    std::vector<Brick*>LegoBricks;

public:
    virtual void execute()
    {
        std::cout << "Lego brick execute" << std::endl; 
        Factory* factory = new LegoBrickFactory();
        LegoBricks = factory->getBricks(1, new DrawImpl("Lego"));
        add();
    }
};

class BuildClayBrickCommand : public Command
{
protected:
    std::vector<Brick*>ClayBricks;

public:
    virtual void execute()
    {
        std::cout << "Clay brick execute" << std::endl; 
        Factory* factory = new ClayBrickFactory();
        ClayBricks = factory->getBricks(1, new DrawImpl("Clay"));
        add();
    }
};

class BuildWoodBrickCommand : public Command
{
protected:
    std::vector<Brick*>WoodBricks;

public:
    virtual void execute()
    {
        std::cout << "Wood brick execute" << std::endl; 
        Factory* factory = new ClayBrickFactory();
        WoodBricks = factory->getBricks(1, new DrawImpl("Wood"));
        add();
    }
};


