#include <iostream>
#include <allegro5/allegro_primitives.h>
#include "gameloop.hpp"

using namespace std;

class Printer: public GameLoop::EventsListener
{
public:
    Printer(){}
    virtual~Printer(){}

    virtual bool AllegroEvent(
        const ALLEGRO_EVENT &crtEvent)
    {
        switch (crtEvent.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            return false;
            break;

        case ALLEGRO_EVENT_KEY_CHAR:
        case ALLEGRO_EVENT_KEY_UP:
        case ALLEGRO_EVENT_KEY_DOWN:
            std::cout<<"Keybaord: KC: "
                        <<crtEvent.keyboard.keycode
                        <<" UCHAR: "
                        <<((wchar_t)crtEvent.keyboard.unichar)
                        <<" TYPE: "
                        << crtEvent.keyboard.type
                        <<" NAME: "
                        <<al_keycode_to_name(crtEvent.keyboard.keycode)
                        <<std::endl;
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
        case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
        case ALLEGRO_EVENT_MOUSE_WARPED:
            break;

        case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
            al_reconfigure_joysticks();
        case ALLEGRO_EVENT_JOYSTICK_AXIS:
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
            std::cout<<"Joystick: TYPE: "
                        <<crtEvent.joystick.type
                        <<" AXIS: "
                        <<crtEvent.joystick.axis
                        <<" BUTTON: "
                        <<crtEvent.joystick.button
                        <<" ID: "
                        <<crtEvent.joystick.id
                        <<" STICK: "
                        <<crtEvent.joystick.stick
                        <<" POS: "
                        <<crtEvent.joystick.pos
                        <<std::endl;
            break;
        }
        return true;
    }

    virtual bool LogicEvent(
        const ALLEGRO_EVENT &crtEvent,
        double              dLength)
    {
        UNREFERNCED_PARAMETER(crtEvent);
        UNREFERNCED_PARAMETER(dLength);
        return true;
    }

    virtual bool DrawEvent(
        const ALLEGRO_EVENT &crtEvent,
        ALLEGRO_DISPLAY     *&rptDisplay,
        double              dLength)
    {
        UNREFERNCED_PARAMETER(crtEvent);
        UNREFERNCED_PARAMETER(rptDisplay);
        UNREFERNCED_PARAMETER(dLength);
        al_draw_line(0, 0, 50, 100, al_map_rgb(255,0,0), 1.0);
        al_flip_display();
        return true;
    }
};

int main()
{
    cout << "Hello World!" << endl;

    ALLEGRO_FILE *ptFile = al_fopen("./resources/config.ini", "r");
    EXPECT_NOT_NULL(ptFile);

    GameLoop tLoop;
    Printer tPrinter;

    tLoop.Initialize(ptFile);

    al_fclose(ptFile);

    tLoop.Start(tPrinter);

    return 0;
}

