#pragma once

#include <iostream>
#include "Brick.h"
#include <list>
#include "LegoBrickFactory.h"
#include "DrawImpl.h"
#include "ClayBrickFactory.h"
#include "WoodBrickFactory.h"
#include <stack>
#include "Global.h"

class Command
{
public:

    ~Command(){};
    virtual void execute() = 0;
    virtual void undo(){};
    virtual void redo(){};
    virtual void add(){m_count++;};
    virtual void remove(){m_count--;};
    virtual int getNumber(){return m_count;}

protected:
    Command(){};
    int m_count = 0;
};

class MacroCommand : public Command
{
public:

    MacroCommand(){};
    virtual ~MacroCommand(){};

    virtual void  add(Command* command)
    {
        command->add();
        commands.push_back(command);
    }  

    virtual void execute()
    {
        for(Command* command : commands)
        {
            command->execute();
        }
    }

    virtual void remove()
    {
        if(commands.size() > 0)
        {
            removedCommands.push(commands.at(commands.size() - 1));
            commands.pop_back();
            removedCommands.top()->remove();
        }
    }

    virtual void undo()
    {
        if(commands.size() > 0)
        {
            std::cout << "Undo" << std::endl;
            removedCommands.push(commands[commands.size()-1]);
            commands.at(commands.size() - 1)->undo();
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
            removedCommands.top()->redo();
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

public:
    virtual void execute()
    {
        std::cout << "Lego brick execute" << std::endl; 
        Factory* factory = new LegoBrickFactory();
        bricks.push_back(factory->getBrick());
        add();
    }

    virtual void undo()
    {
        bricks.pop_back();
        //remove();
    }
};

class BuildClayBrickCommand : public Command
{
public:
    virtual void execute()
    {
        std::cout << "Clay brick execute" << std::endl; 
        Factory* factory = new ClayBrickFactory();
        bricks.push_back(factory->getBrick());
        add();
    }

    virtual void undo()
    {
        bricks.pop_back();
        //remove();
    }
};

class BuildWoodBrickCommand : public Command
{
public:
    virtual void execute()
    {
        std::cout << "Wood brick execute" << std::endl; 
        Factory* factory = new WoodBrickFactory();
        bricks.push_back(factory->getBrick());
        add();
    }

    virtual void undo()
    {
        bricks.pop_back();
        //remove();
    }
};


