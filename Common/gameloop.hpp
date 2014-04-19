#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include <allegro5/allegro5.h>
#include "common.hpp"
#include "config.hpp"

class GameLoop
{
public:

    class EventsListener
    {
    public:
        EventsListener(){}
        virtual~EventsListener(){}

        // Return false to stop the loop
        virtual bool AllegroEvent(
            const ALLEGRO_EVENT &crtEvent)
        {
            UNREFERNCED_PARAMETER(crtEvent);
            return true;
        }

        // Return false to stop the loop
        virtual bool LogicEvent(
            const ALLEGRO_EVENT &crtEvent,
            double              dLength)
        {
            UNREFERNCED_PARAMETER(crtEvent);
            UNREFERNCED_PARAMETER(dLength);
            return true;
        }

        // Return false to stop the loop
        virtual bool DrawEvent(
            const ALLEGRO_EVENT &crtEvent,
            ALLEGRO_DISPLAY     *&rptDisplay,
            double              dLength)
        {
            UNREFERNCED_PARAMETER(crtEvent);
            UNREFERNCED_PARAMETER(rptDisplay);
            UNREFERNCED_PARAMETER(dLength);
            return true;
        }
    };

public:
    GameLoop();

    void
    Initialize(
        ALLEGRO_FILE    *ptConfigPath);

    void
    Shutdown();

    void
    Start(
        EventsListener  &rtListener);

private:
    CONFIG m_tConfig;
    ALLEGRO_DISPLAY *m_ptDisplay;
};

#endif // GAMELOOP_HPP
