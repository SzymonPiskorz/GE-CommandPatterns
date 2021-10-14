#pragma once

#include <iostream>
#include "Brick.h"
#include <list>
#include "LegoBrickFactory.h"
#include "DrawImpl.h"
#include "ClayBrickFactory.h"
#include "WoodBrickFactory.h"

class Command
{
public:

    ~Command(){};
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;

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
    }  

     virtual void  remove(Command* command)
    {
        commands.remove(command);
    }

    virtual void excecute()
    {
        for(Command* command : commands)
        {
            command->execute();
        }
    }

protected:
    std::list<Command*> commands;
};

class BuildLegoBrickCommand : public Command
{
protected:
    std::vector<Brick*>LegoBricks;

public:
    virtual void execute()
    {
        Factory* factory = new LegoBrickFactory();
        LegoBricks = factory->getBricks(1, new DrawImpl("Lego"));
        add();
    }

    virtual void undo()
    {
        LegoBricks.pop_back();
        remove();
    }

    virtual void redo()
    {
        execute();
    }
};

class BuildClayBrickCommand : public Command
{
protected:
    std::vector<Brick*>ClayBricks;

public:
    virtual void execute()
    {
        Factory* factory = new ClayBrickFactory();
        ClayBricks = factory->getBricks(1, new DrawImpl("Clay"));
        add();
    }

    virtual void undo()
    {
        ClayBricks.pop_back();
        remove();
    }

    virtual void redo()
    {
        execute();
    }
};

class BuildWoodBrickCommand : public Command
{
protected:
    std::vector<Brick*>WoodBricks;

public:
    virtual void execute()
    {
        Factory* factory = new ClayBrickFactory();
        WoodBricks = factory->getBricks(1, new DrawImpl("Wood"));
        add();
    }

    virtual void undo()
    {
        WoodBricks.pop_back();
        remove();
    }

    virtual void redo()
    {
        execute();
    }
};


