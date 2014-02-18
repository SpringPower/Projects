#include <iostream>
#include <allegro5/allegro_primitives.h>
#include "gameloop.hpp"
#include "textdrawer.hpp"

using namespace std;

class Printer: public GameLoop::EventsListener
{
public:
    Printer(PTilesetFactory ptFactory):
        m_ptTilesetFactory(ptFactory),
        m_tDrawer(m_ptTilesetFactory),
        m_tStr("123456789012345678901234567890123456789123456789012345678912345678901234567891234567890123456789123456789012345678912345678901234567891234567890123456789123456789012345678912345678901234567891234567890123456789123456789012345678912345678901234567891234567890123456789123456789012345678912345678901234567891234567890123456789123456789012345678912345678901234567891234567890123456789")
    {}
    virtual~Printer(){}

    virtual bool AllegroEvent(
        const ALLEGRO_EVENT &crtEvent)
    {
        std::stringstream ssStream;
        switch (crtEvent.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            return false;
            break;

        case ALLEGRO_EVENT_KEY_CHAR:
        case ALLEGRO_EVENT_KEY_UP:
        case ALLEGRO_EVENT_KEY_DOWN:
            ssStream    <<"Keybaord: KC: "
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
            ssStream    <<"Joystick: TYPE: "
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
        std::cout << ssStream.str();
        //m_tStr = ssStream.str();
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
        m_tDrawer.WritePixel(m_tStr, Square(54, 54, 154, 154));
        al_flip_display();
        return true;
    }

    PTilesetFactory m_ptTilesetFactory;
    TextDrawer m_tDrawer;
    std::string m_tStr;
};

int main()
{
    cout << "Hello World!" << endl;

    ALLEGRO_FILE *ptFile = al_fopen("./resources/config.ini", "r");
    EXPECT_NOT_NULL(ptFile);

    GameLoop tLoop;

    tLoop.Initialize(ptFile);

    PTilesetFactory ptFactory;
    ptFactory = new TilesetFactory();
    Printer tPrinter(ptFactory);
    al_fclose(ptFile);

    tLoop.Start(tPrinter);

    return 0;
}

