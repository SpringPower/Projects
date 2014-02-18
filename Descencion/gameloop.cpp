#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "gameloop.hpp"

GameLoop::GameLoop():
    m_ptDisplay(NULL)
{
}

void GameLoop::Initialize(ALLEGRO_FILE *ptConfigPath)
{
    LoadConfig(ptConfigPath, m_tConfig);

    EXPECT_TRUE(al_init());
    EXPECT_TRUE(al_init_image_addon());
    EXPECT_TRUE(al_install_keyboard());
    EXPECT_TRUE(al_install_mouse());
    EXPECT_TRUE(al_install_joystick());
    EXPECT_TRUE(al_init_primitives_addon());

    al_set_new_display_adapter(m_tConfig.ulCreationDisplay);

    al_set_new_display_flags(m_tConfig.ulWindowed | ALLEGRO_OPENGL);

    if (m_tConfig.ulVsync)
    {
        al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    }

    m_ptDisplay = al_create_display(m_tConfig.ulWidth, m_tConfig.ulHeight);
    EXPECT_NOT_NULL(m_ptDisplay);
}

void GameLoop::Shutdown()
{
    al_destroy_display(m_ptDisplay);

    al_shutdown_primitives_addon();
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_uninstall_system();
}

void GameLoop::Start(
    EventsListener &rtListener)
{
    ALLEGRO_EVENT_QUEUE *ptEventQueue = al_create_event_queue();
    EXPECT_NOT_NULL(ptEventQueue);

    ALLEGRO_EVENT_SOURCE *ptKeyboardEventSource = al_get_keyboard_event_source();
    EXPECT_NOT_NULL(ptKeyboardEventSource);

    ALLEGRO_EVENT_SOURCE *ptMouseEventSource = al_get_mouse_event_source();
    EXPECT_NOT_NULL(ptMouseEventSource);

    ALLEGRO_EVENT_SOURCE *ptJoystickEventSource = al_get_joystick_event_source();
    EXPECT_NOT_NULL(ptJoystickEventSource);

    ALLEGRO_EVENT_SOURCE *ptDisplayEventSource = al_get_display_event_source(m_ptDisplay);
    EXPECT_NOT_NULL(ptDisplayEventSource);

    ALLEGRO_TIMER *ptTimer = al_create_timer(1.0 / m_tConfig.ulMaxFps);
    ALLEGRO_EVENT_SOURCE *ptTimerEventSource = al_get_timer_event_source(ptTimer);
    EXPECT_NOT_NULL(ptTimerEventSource);

    al_register_event_source(ptEventQueue, ptKeyboardEventSource);
    al_register_event_source(ptEventQueue, ptMouseEventSource);
    al_register_event_source(ptEventQueue, ptJoystickEventSource);
    al_register_event_source(ptEventQueue, ptDisplayEventSource);
    al_register_event_source(ptEventQueue, ptTimerEventSource);

    al_start_timer(ptTimer);

    bool bRunning = true;

    while (bRunning)
    {
        ALLEGRO_EVENT tEvent;
        al_wait_for_event(ptEventQueue, &tEvent);
        switch(tEvent.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (tEvent.timer.timestamp < al_get_time() - 1.0/m_tConfig.ulMinFps)
            {
                break;
            }
            bRunning = rtListener.LogicEvent(tEvent, 1.0/m_tConfig.ulMaxFps);

            if (bRunning)
            {
                bRunning = rtListener.DrawEvent(tEvent, m_ptDisplay, 1.0/m_tConfig.ulMaxFps);
            }

            break;

        default:
            bRunning = rtListener.AllegroEvent(tEvent);
            break;
        }
    }

    al_destroy_timer(ptTimer);
    al_destroy_event_queue(ptEventQueue);
}
